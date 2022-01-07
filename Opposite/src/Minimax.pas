(*
   * * * * * * * * * * * * * * * * * * * * * * * *
   *                                             *
   *      ApplName:  OPPOSITE                    *
   *      FileName:  minimax.pas                 *
   *   Description:  Game search trees           *
   *                                             *
   *        Author:  Harris Georgiou (c) 2000.   *
   *                                             *
   * * * * * * * * * * * * * * * * * * * * * * * *
*)


unit Minimax;

interface

uses Defines, windows;

function SelectMove_Minimax( var currentGame : TGamePanel; plays : Integer; todepth : Integer; var bestmove : TPoint ) : Boolean;

implementation

uses opposite, Dialogs;

{...........................}

procedure GNode_Init( var node : GNode );
var
    i : Integer;
begin
    node.prev:=cNullNode;
    node.cost:=0;  node.nextPlays:=0;  node.depth:=0;
    node.moveX:=0;  node.moveY:=0;  node.follow:=0;
    SetLength(node.next,cListGrow);
    for i:=0 to High(node.next) do node.next[i]:=cNullNode;
end;

procedure GTree_Init( var tree : GTree );
var
    i : Integer;
begin
    tree.root:=cNullNode;  tree.nextfree:=0;
    tree.moveX:=0;  tree.moveY:=0;  tree.follow:=cNullNode;
    SetLength(tree.pool,cPoolGrow);
    for i:=0 to High(tree.pool) do GNode_Init(tree.pool[i]);
end;

function GTree_SetRoot( var tree : GTree; var rootGame : TGamePanel; plays : Integer ) : Integer;
begin
    tree.root:=tree.nextfree;
    copyGamePanel(rootGame,tree.pool[tree.root].game);
    tree.pool[tree.root].nextPlays:=plays;
    tree.pool[tree.root].depth:=0;
    Inc(tree.nextfree);
    GTree_SetRoot:=tree.root;
end;


function GTree_AddNode( var tree : GTree; var currentGame : TGamePanel; currentMove : TPoint; depth : Integer ) : Integer;
begin
    if (tree.nextfree>High(tree.pool)) then
        SetLength(tree.pool,High(tree.pool)+cPoolGrow);

    GNode_Init(tree.pool[tree.nextfree]);
    copyGamePanel(currentGame,tree.pool[tree.nextfree].game);
    tree.pool[tree.nextfree].prev:=tree.nextfree;
    tree.pool[tree.nextfree].depth:=depth;
    tree.pool[tree.nextfree].moveX:=currentMove.x;
    tree.pool[tree.nextfree].moveY:=currentMove.y;
    Inc(tree.nextfree);
    GTree_AddNode:=tree.nextfree-1;
end;

procedure GTree_ExpandNode( var tree : GTree; nodeidx : Integer; todepth : Integer );
var
    i, a : Integer;
    newmoves : TGameMoves;
    newgames : TGameSet;
    {str1, str2 : String;}
begin
    if (todepth=tree.pool[nodeidx].depth) then Exit;

    createNextMoves(tree.pool[nodeidx].game,tree.pool[nodeidx].nextPlays,newmoves);
    createNextGames(tree.pool[nodeidx].game,tree.pool[nodeidx].nextPlays,newmoves,newgames);

    {Str(High(newmoves)+1,str1);  Str(High(newgames)+1,str2);
    ShowMessage('found next: '+str1+' moves, '+str2+' games');}

    SetLength(tree.pool[nodeidx].next,High(newgames)+1);
    for i:=0 to High(newgames) do
        begin
        a:=GTree_AddNode(tree,newgames[i],newmoves[i],tree.pool[nodeidx].depth+1);
        tree.pool[nodeidx].next[i]:=a;
        tree.pool[a].prev:=nodeidx;
        tree.pool[a].nextPlays:=(tree.pool[nodeidx].nextPlays+1) mod 2;
        end;

    for i:=0 to High(tree.pool[nodeidx].next) do GTree_ExpandNode(tree,tree.pool[nodeidx].next[i],todepth);
end;

procedure GTree_Expand( var tree : GTree; todepth : Integer );
begin
    GTree_ExpandNode(tree,tree.root,todepth);
end;

procedure GTree_EvaluateNode( var tree : GTree; nodeidx : Integer );
var
    c : Integer;
begin
    tree.pool[nodeidx].cost:=currentGameScore(tree.pool[nodeidx].game,tree.pool[nodeidx].nextPlays,MainForm.useEdges);
    for c:=0 to High(tree.pool[nodeidx].next) do
        if (tree.pool[nodeidx].next[c]<>cNullNode) then GTree_EvaluateNode(tree,tree.pool[nodeidx].next[c]);
end;

procedure GTree_Evaluate( var tree : GTree );
begin
    if (tree.root<>cNullNode) then GTree_EvaluateNode(tree,tree.root);
end;

function GTree_SelectBestOfNext( var tree : GTree; nodeidx : Integer; var bestidx : Integer; var bestcost : Integer ) : Integer;
var
    c : Integer;
    {str1, str2, str3 : String;}
begin
    if (tree.pool[nodeidx].nextPlays=cBlack) then  { play for MAX(0), select max }
      begin
        bestcost:=-MaxInt;  bestidx:=0;
        for c:=0 to High(tree.pool[nodeidx].next) do
        begin
            if (tree.pool[nodeidx].next[c]=cNullNode) then continue
            else if (tree.pool[tree.pool[nodeidx].next[c]].cost>bestcost) then
              begin bestcost:=tree.pool[tree.pool[nodeidx].next[c]].cost; bestidx:=c; end;
        end
      end
    else if (tree.pool[nodeidx].nextPlays=cWhite) then  { play for MIN(1), select min }
      begin
        bestcost:=MaxInt;  bestidx:=0;
        for c:=0 to High(tree.pool[nodeidx].next) do
        begin
            if (tree.pool[nodeidx].next[c]=cNullNode) then continue
            else if (tree.pool[tree.pool[nodeidx].next[c]].cost<bestcost) then
              begin bestcost:=tree.pool[tree.pool[nodeidx].next[c]].cost; bestidx:=c; end;
        end
      end
    else
      begin
        bestidx:=cNullNode;  bestcost:=0;
      end;

    if (bestidx<>cNullNode) then tree.pool[nodeidx].follow:=bestidx;

    {Str(bestidx+1,str1);  ShowMessage('best move is at index '+str1);

    Str(tree.pool[tree.pool[nodeidx].next[tree.pool[nodeidx].follow]].moveX,str1);
    Str(tree.pool[tree.pool[nodeidx].next[tree.pool[nodeidx].follow]].moveY,str2);
    Str(tree.pool[tree.pool[nodeidx].next[tree.pool[nodeidx].follow]].cost,str3);
    ShowMessage('Move to ['+str1+','+str2+'] -> newscore='+str3);}

    GTree_SelectBestOfNext:=bestidx;
end;

procedure GTree_BackpropBest( var tree : GTree; nodeidx : Integer; todepth : Integer;
             var bestidx : Integer; var bestcost : Integer );
var
    c : Integer;
begin
    {writeln('searching for node:',nodeidx,' at depth:',todepth);}

    if (tree.pool[nodeidx].depth=todepth-1) then
      begin
        GTree_SelectBestOfNext(tree,nodeidx,bestidx,bestcost);
        tree.pool[nodeidx].cost:=bestcost;
        if (tree.pool[nodeidx].prev<>cNullNode) then
            GTree_BackpropBest(tree,tree.pool[nodeidx].prev,todepth-1,bestidx,bestcost);
      end
    else if (tree.pool[nodeidx].depth<todepth-1) then
      begin
        for c:=0 to High(tree.pool[nodeidx].next) do
            GTree_BackpropBest(tree,tree.pool[nodeidx].next[c],todepth,bestidx,bestcost);
      end;
end;

function GTree_Minimax( var tree : GTree; todepth : Integer ) : TPoint;
var
    bestidx : Integer;
    bestcost : Integer;
    bestmove : TPoint;
    {str1, str2, str3 : String;}
begin
    GTree_BackpropBest(tree,tree.root,todepth,bestidx,bestcost);
    tree.follow:=bestidx;
    bestmove.x:=tree.pool[tree.pool[tree.root].next[tree.pool[tree.root].follow]].moveX;
    bestmove.y:=tree.pool[tree.pool[tree.root].next[tree.pool[tree.root].follow]].moveY;

    {Str(tree.pool[tree.pool[tree.root].next[tree.pool[tree.root].follow]].moveX,str1);
    Str(tree.pool[tree.pool[tree.root].next[tree.pool[tree.root].follow]].moveY,str2);
    Str(tree.pool[tree.pool[tree.root].next[tree.pool[tree.root].follow]].cost,str3);
    ShowMessage('Minimax: Move to ['+str1+','+str2+'] -> newscore='+str3);}

    GTree_Minimax:=bestmove;
end;

function SelectMove_Minimax( var currentGame : TGamePanel; plays : Integer; todepth : Integer; var bestmove : TPoint ) : Boolean;
var
    minimaxTree : GTree;
    hasMoved    : Boolean;
begin
    {... Minimax search for optimum next move ...}
    GTree_Init(minimaxTree);
    GTree_SetRoot(minimaxTree,currentGame,plays);
    GTree_Expand(minimaxTree,todepth);
    GTree_Evaluate(minimaxTree);
    bestmove:=GTree_Minimax(minimaxTree,todepth);

    if ((bestmove.x>=1)and(bestmove.x<=cPanelSize)and(bestmove.y>=1)and(bestmove.y<=cPanelSize)) then
        hasMoved:=true
    else hasMoved:=false;

    SelectMove_Minimax:=hasMoved;
end;

{..........................}

begin

end.

