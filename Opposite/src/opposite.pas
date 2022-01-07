(*
   * * * * * * * * * * * * * * * * * * * * * * * *
   *                                             *
   *      ApplName:  OPPOSITE                    *
   *      FileName:  opposite.pas                *
   *   Description:  Main form (program)         *
   *                                             *
   *        Author:  Harris Georgiou (c) 2000.   *
   *                                             *
   * * * * * * * * * * * * * * * * * * * * * * * *
*)


unit opposite;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  ExtCtrls, Menus, StdCtrls, About, Math, Defines, Minimax;

type

  TMainForm = class(TForm)
    MainMenu1: TMainMenu;
    N1: TMenuItem;
    N2: TMenuItem;
    N3: TMenuItem;
    N4: TMenuItem;
    N5: TMenuItem;
    N7: TMenuItem;
    StatusLine: TPanel;
    Bevel1: TBevel;
    Grid: TImage;
    Tag1: TGroupBox;
    Tag2: TGroupBox;
    Label1: TLabel;
    Label2: TLabel;
    scoreBlack: TLabel;
    scoreWhite: TLabel;
    statR1: TLabel;
    statM1: TLabel;
    StatRounds: TLabel;
    statMoves: TLabel;
    Label3: TLabel;
    statChanged: TLabel;
    Label4: TLabel;
    statLast: TLabel;
    GroupBox1: TGroupBox;
    Memo1: TMemo;
    Settings1: TMenuItem;
    lblPlay1: TLabel;
    lblPlay2: TLabel;
    procedure N5Click(Sender: TObject);
    procedure FormPaint(Sender: TObject);

    procedure Initialize;
    procedure ClearPanel;
    procedure InitGame;
    procedure NewGame;
    procedure DrawPawn(x,y,val: Integer);
    procedure DrawScore;
    procedure DrawPanel;
    procedure DrawAll;
    procedure placePawn( x, y, player : Integer );
    procedure updateStatus( x, y : Integer );
    procedure doMove( x, y : Integer );
    function tryMove( x, y, plays : Integer ) : Boolean;
    function pawnConversions( x, y : Integer; modifyPanel : Boolean ) : Integer;
    procedure updateCounts;
    function checkWinner : Integer;
    function hasFreeMoves( player : Integer ) : Boolean;
    function doComputerMove : Boolean;
    {function costFunction1( x, y, player : Integer ) : Integer;
    function costFunction2( x, y, player : Integer ) : Integer;
    function costFunction3( x, y, player : Integer ) : Integer;
    function costFunction4( x, y, player : Integer ) : Integer;
    function costFunction( x, y, player : Integer ) : Integer;}

    procedure GridMouseDown(Sender: TObject; Button: TMouseButton;
      Shift: TShiftState; X, Y: Integer);
    procedure GridMouseMove(Sender: TObject; Shift: TShiftState; X,
      Y: Integer);
    procedure FormCreate(Sender: TObject);
    procedure N3Click(Sender: TObject);
    procedure N7Click(Sender: TObject);
    procedure Settings1Click(Sender: TObject);

  private
    { Private declarations }
  public
    { Public declarations }
    GamePanel : TGamePanel;
    nextPlays : Integer;                { who plays next? }
    pnBlacks, pnWhites : Integer;       { score variables }
    stChanged : Integer;                { last change on board }
    playing : Boolean;                  { is the game active? }
    computing : Boolean;                { is the computer player thinking? }
    playType : array [cBlack..cWhite] of Integer;       { human or computer? }
    playLevel : array [cBlack..cWhite] of Integer;      { computer level? }
    stLastX, stLastY : Integer;         { most recent move }
    useEdges : Boolean;
  end;

  procedure copyGamePanel( var datafrom, datato : TGamePanel );
  function tryNewMove( var GamePanel : TGamePanel; x, y, plays : Integer ) : Boolean;
  function makePawnConversions( var GamePanel : TGamePanel; x, y : Integer; modifyPanel : Boolean ) : Integer;
  function createNextMoves( var currentGame : TGamePanel; player : Integer; var newmoves : TGameMoves ) : Integer;
  function createNextGames( var currentGame : TGamePanel; player : Integer; var newmoves : TGameMoves; var newgames : TGameSet ) : Integer;
  function currentGameScore( var currentGame : TGamePanel; plays : Integer; useEdges : Boolean ) : Integer;
  {function closedSides( var GamePanel : TGamePanel; x, y : Integer ) : Integer;
  function openedSides( var GamePanel : TGamePanel; x, y : Integer ) : Integer;}

var
  MainForm: TMainForm;


{.......................................}


implementation

uses setup;

{$R *.DFM}

{... calculate 'closed' sides for current position ...}
(*function closedSides( var GamePanel : TGamePanel; x, y : Integer ) : Integer;
var
    cx, cy, securedsides : Integer;
    secured : Boolean;
    {str1, str2, str3 : String;}
begin
    securedsides:=0;

    {... check: [CP->'E'] ...}
    cx:=x+1;  cy:=y;  secured:=true;
    while (cx<=cPanelSize) do
        if (GamePanel[cx,cy]=cEmpty) then
            begin secured:=false; break; end
        else
            begin Inc(cx); end;
    if (secured) then Inc(securedsides);

    {... check: [CP->'SE'] ...}
    cx:=x+1;  cy:=y+1;  secured:=true;
    while ((cx<=cPanelSize)and(cy<=cPanelSize)) do
        if (GamePanel[cx,cy]=cEmpty) then
            begin secured:=false; break; end
        else
            begin Inc(cx); Inc(cy); end;
    if (secured) then Inc(securedsides);

    {... check: [CP->'S'] ...}
    cx:=x;  cy:=y+1;  secured:=true;
    while (cy<=cPanelSize) do
        if (GamePanel[cx,cy]=cEmpty) then
            begin secured:=false; break; end
        else
            begin Inc(cy); end;
    if (secured) then Inc(securedsides);

    {... check: [CP->'SW'] ...}
    cx:=x-1;  cy:=y+1;  secured:=true;
    while ((cx>=1)and(cy<=cPanelSize)) do
        if (GamePanel[cx,cy]=cEmpty) then
            begin secured:=false; break; end
        else
            begin Dec(cx); Inc(cy); end;
    if (secured) then Inc(securedsides);

    {... check: [CP->'W'] ...}
    cx:=x-1;  cy:=y;  secured:=true;
    while (cx>=1) do
        if (GamePanel[cx,cy]=cEmpty) then
            begin secured:=false; break; end
        else
            begin Dec(cx); end;
    if (secured) then Inc(securedsides);

    {... check: [CP->'NW'] ...}
    cx:=x-1;  cy:=y-1;  secured:=true;
    while ((cx>=1)and(cy>=1)) do
        if (GamePanel[cx,cy]=cEmpty) then
            begin secured:=false; break; end
        else
            begin Dec(cx); Dec(cy); end;
    if (secured) then Inc(securedsides);

    {... check: [CP->'N'] ...}
    cx:=x;  cy:=y-1;  secured:=true;
    while (cy>=1) do
        if (GamePanel[cx,cy]=cEmpty) then
            begin secured:=false; break; end
        else
            begin Dec(cy); end;
    if (secured) then Inc(securedsides);

    {... check: [CP->'NE'] ...}
    cx:=x+1;  cy:=y-1;  secured:=true;
    while ((cx<=cPanelSize)and(cy>=1)) do
        if (GamePanel[cx,cy]=cEmpty) then
            begin secured:=false; break; end
        else
            begin Inc(cx); Dec(cy); end;
    if (secured) then Inc(securedsides);

    {Str(x,str1); Str(y,str2); Str(securedsides,str3);
    ShowMessage('secured: '+str1+','+str2+' -> '+str3);}

    closedSides:=securedsides;
end;
*)

{... calculate 'closed' sides for current position ...}
(*function openedSides( var GamePanel : TGamePanel; x, y : Integer ) : Integer;
var
    cx, cy, opensides : Integer;
    isopen : Boolean;
    {str1, str2, str3 : String;}
begin
    opensides:=0;

    {... check: [CP->'E'] ...}
    cx:=x+1;  cy:=y;  isopen:=true;
    while (cx<=cPanelSize) do
        if (GamePanel[cx,cy]=GamePanel[x,y]) then
            begin isopen:=false; break; end
        else
            begin Inc(cx); end;
    if (isopen) then Inc(opensides,cx-x-1);

    {... check: [CP->'SE'] ...}
    cx:=x+1;  cy:=y+1;  isopen:=true;
    while ((cx<=cPanelSize)and(cy<=cPanelSize)) do
        if (GamePanel[cx,cy]=GamePanel[x,y]) then
            begin isopen:=false; break; end
        else
            begin Inc(cx); Inc(cy); end;
    if (isopen) then Inc(opensides,min(cx-x-1,cy-y-1));

    {... check: [CP->'S'] ...}
    cx:=x;  cy:=y+1;  isopen:=true;
    while (cy<=cPanelSize) do
        if (GamePanel[cx,cy]=GamePanel[x,y]) then
            begin isopen:=false; break; end
        else
            begin Inc(cy); end;
    if (isopen) then Inc(opensides,cy-y-1);

    {... check: [CP->'SW'] ...}
    cx:=x-1;  cy:=y+1;  isopen:=true;
    while ((cx>=1)and(cy<=cPanelSize)) do
        if (GamePanel[cx,cy]=GamePanel[x,y]) then
            begin isopen:=false; break; end
        else
            begin Dec(cx); Inc(cy); end;
    if (isopen) then Inc(opensides,min(-(cx-x-1),cy-y-1));

    {... check: [CP->'W'] ...}
    cx:=x-1;  cy:=y;  isopen:=true;
    while (cx>=1) do
        if (GamePanel[cx,cy]=GamePanel[x,y]) then
            begin isopen:=false; break; end
        else
            begin Dec(cx); end;
    if (isopen) then Inc(opensides,-(cx-x-1));

    {... check: [CP->'NW'] ...}
    cx:=x-1;  cy:=y-1;  isopen:=true;
    while ((cx>=1)and(cy>=1)) do
        if (GamePanel[cx,cy]=GamePanel[x,y]) then
            begin isopen:=false; break; end
        else
            begin Dec(cx); Dec(cy); end;
    if (isopen) then Inc(opensides,min(-(cx-x-1),-(cy-y-1)));

    {... check: [CP->'N'] ...}
    cx:=x;  cy:=y-1;  isopen:=true;
    while (cy>=1) do
        if (GamePanel[cx,cy]=GamePanel[x,y]) then
            begin isopen:=false; break; end
        else
            begin Dec(cy); end;
    if (isopen) then Inc(opensides,-(cy-y-1));

    {... check: [CP->'NE'] ...}
    cx:=x+1;  cy:=y-1;  isopen:=true;
    while ((cx<=cPanelSize)and(cy>=1)) do
        if (GamePanel[cx,cy]=GamePanel[x,y]) then
            begin isopen:=false; break; end
        else
            begin Inc(cx); Dec(cy); end;
    if (isopen) then Inc(opensides,min(cx-x-1,-(cy-y-1)));

    {Str(x,str1); Str(y,str2); Str(opensides,str3);
    ShowMessage('open: '+str1+','+str2+' -> '+str3);}

    openedSides:=opensides;
end;
*)

{... static cost function: combine board score & edge pawns ...}
{ Notes:  depth is doubled, always finish with the same player }
function currentGameScore( var currentGame : TGamePanel; plays : Integer; useEdges : Boolean ) : Integer;
const
    cEdgeInc = 3;             { best choice between 2 and 5  = 3 }
    cCornerInc = cEdgeInc*2;  { calculate as 'double' edge }
    totalmoves = cPanelSize*cPanelSize;
var
    scoreMAXblack, scoreMINwhite, scoreTotal : Integer;
    edgesMAXblack, edgesMINwhite, edgesTotal : Integer;
    x, y, currentmoves : Integer;
begin
    scoreMAXblack:=0;  scoreMINwhite:=0;
    for x:=1 to cPanelSize do
        for y:=1 to cPanelSize do
            case currentGame[x,y] of
                cBlack:  Inc(scoreMAXblack);
                cWhite:  Inc(scoreMINwhite);
            end;

    if (useEdges) then
    begin
      edgesMAXblack:=0;  edgesMINwhite:=0;

      { check top and bottom rows }
      for x:=2 to cPanelSize do
      begin
        case currentGame[x,1] of
          cBlack:  Inc(edgesMAXblack,cEdgeInc);
          cWhite:  Inc(edgesMINwhite,cEdgeInc);
        end;

        case currentGame[x,cPanelSize] of
          cBlack:  Inc(edgesMAXblack,cEdgeInc);
          cWhite:  Inc(edgesMINwhite,cEdgeInc);
        end;
      end;

     { check left and right columns }
      for y:=2 to cPanelSize-1 do
      begin
        case currentGame[1,y] of
          cBlack:  Inc(edgesMAXblack,cEdgeInc);
          cWhite:  Inc(edgesMINwhite,cEdgeInc);
        end;

        case currentGame[cPanelSize,y] of
          cBlack:  Inc(edgesMAXblack,cEdgeInc);
          cWhite:  Inc(edgesMINwhite,cEdgeInc);
        end;
      end;

      { check all corners }
      case currentGame[1,1] of
        cBlack:  Inc(edgesMAXblack,cCornerInc);
        cWhite:  Inc(edgesMINwhite,cCornerInc);
      end;

      case currentGame[1,cPanelSize] of
        cBlack:  Inc(edgesMAXblack,cCornerInc);
        cWhite:  Inc(edgesMINwhite,cCornerInc);
      end;

      case currentGame[cPanelSize,1] of
        cBlack:  Inc(edgesMAXblack,cCornerInc);
        cWhite:  Inc(edgesMINwhite,cCornerInc);
      end;

      case currentGame[cPanelSize,cPanelSize] of
        cBlack:  Inc(edgesMAXblack,cCornerInc);
        cWhite:  Inc(edgesMINwhite,cCornerInc);
      end;

      { adaptive strategy: occupy edges/corners when winning or try to avoid elimination when loosing }
      currentmoves:=scoreMAXblack+scoreMINwhite;
      edgesTotal:=Round(edgesMAXblack*(scoreMAXblack/currentmoves+0.5)-edgesMINwhite*(scoreMINwhite/currentmoves+0.5));
    end
    else edgesTotal:=0;  { no effect when not using edge calculations }

    { check for premature wins }
    if (scoreMINwhite=0) then scoreTotal:=MaxInt
    else if (scoreMAXblack=0) then scoreTotal:=-MaxInt
    else
      begin
        { selectively use extended function in only one of the players }
        {case plays of
            cBlack: scoreTotal:=(scoreMAXblack-scoreMINwhite);
            cWhite: scoreTotal:=(scoreMAXblack-scoreMINwhite);
            else scoreTotal:=(scoreMAXblack-scoreMINwhite)+edgesTotal;
        end;}

        { or play normal, both cBlack and cWhite are treated the same }
        scoreTotal:=(scoreMAXblack-scoreMINwhite)+edgesTotal;
      end;

    currentGameScore:=scoreTotal;
end;

{... clone game boards ...}
procedure copyGamePanel( var datafrom, datato : TGamePanel );
var
    x, y : Integer;
begin
    for x:=1 to cPanelSize do
        for y:=1 to cPanelSize do
            datato[x,y] := datafrom[x,y];
end;

{... make or just calculate pawn conversions from recent move ...}
function makePawnConversions( var GamePanel : TGamePanel; x, y : Integer; modifyPanel : Boolean ) : Integer;
var
    cx, cy, convs, nconv, begpos, endpos, currplay, nextplay : Integer;
begin
    convs:=0;
    if (GamePanel[x,y]<>cEmpty) then
    begin
        currplay:=GamePanel[x,y];  nextplay:=(currplay+1) mod 2;

        {... check: [CP->'E'] ...}
        cx:=x+1;  cy:=y;  begpos:=x;  endpos:=begpos;
        while (cx<=cPanelSize) do
        begin
            if (GamePanel[cx,cy]=nextplay) then Inc(cx)
            else if (GamePanel[cx,cy]=currplay) then
                begin endpos:=cx-1; break; end
            else break;
        end;
        if (endpos>begpos) then
        begin
            if (modifyPanel) then begin
              cx:=x+1;
              while (cx<=endpos) do
                begin GamePanel[cx,cy]:=GamePanel[x,y]; Inc(cx); end;
            end;

            nconv:=abs(endpos-begpos);
            convs:=convs+nconv;
        end;

        {... check: [CP->'SE'] ...}
        cx:=x+1;  cy:=y+1;  begpos:=x;  endpos:=begpos;
        while ((cx<=cPanelSize)and(cy<=cPanelSize)) do
        begin
            if (GamePanel[cx,cy]=nextplay) then
                begin Inc(cx); Inc(cy); end
            else if (GamePanel[cx,cy]=currplay) then
                begin endpos:=cx-1; break; end
            else break;
        end;
        if (endpos>begpos) then
        begin
            if (modifyPanel) then begin
              cx:=x+1;  cy:=y+1;
              while (cx<=endpos) do
                begin GamePanel[cx,cy]:=GamePanel[x,y]; Inc(cx); Inc(cy); end;
            end;

            nconv:=abs(endpos-begpos);
            convs:=convs+nconv;
        end;

        {... check: [CP->'S'] ...}
        cx:=x;  cy:=y+1;  begpos:=y;  endpos:=begpos;
        while (cy<=cPanelSize) do
        begin
            if (GamePanel[cx,cy]=nextplay) then Inc(cy)
            else if (GamePanel[cx,cy]=currplay) then
                begin endpos:=cy-1; break; end
            else break;
        end;
        if (endpos>begpos) then
        begin
            if (modifyPanel) then begin
              cy:=y+1;
              while (cy<=endpos) do
                begin GamePanel[cx,cy]:=GamePanel[x,y]; Inc(cy); end;
            end;

            nconv:=abs(endpos-begpos);
            convs:=convs+nconv;
        end;

        {... check: [CP->'SW'] ...}
        cx:=x-1;  cy:=y+1;  begpos:=y;  endpos:=begpos;
        while ((cx>=1)and(cy<=cPanelSize)) do
        begin
            if (GamePanel[cx,cy]=nextplay) then
                begin Dec(cx); Inc(cy); end
            else if (GamePanel[cx,cy]=currplay) then
                begin endpos:=cy-1; break; end
            else break;
        end;
        if (endpos>begpos) then
        begin
            if (modifyPanel) then begin
              cx:=x-1;  cy:=y+1;
              while (cy<=endpos) do
                begin GamePanel[cx,cy]:=GamePanel[x,y]; Dec(cx); Inc(cy); end;
            end;

            nconv:=abs(endpos-begpos);
            convs:=convs+nconv;
        end;

        {... check: [CP->'W'] ...}
        cx:=x-1;  cy:=y;  begpos:=x;  endpos:=begpos;
        while (cx>=1) do
        begin
            if (GamePanel[cx,cy]=nextplay) then Dec(cx)
            else if (GamePanel[cx,cy]=currplay) then
                begin endpos:=cx+1; break; end
            else break;
        end;
        if (endpos<begpos) then
        begin
            if (modifyPanel) then begin
              cx:=x-1;
              while (cx>=endpos) do
                begin GamePanel[cx,cy]:=GamePanel[x,y]; Dec(cx); end;
            end;

            nconv:=abs(endpos-begpos);
            convs:=convs+nconv;
        end;

        {... check: [CP->'NW'] ...}
        cx:=x-1;  cy:=y-1;  begpos:=x;  endpos:=begpos;
        while ((cx>=1)and(cy>=1)) do
        begin
            if (GamePanel[cx,cy]=nextplay) then
                begin Dec(cx); Dec(cy); end
            else if (GamePanel[cx,cy]=currplay) then
                begin endpos:=cx+1; break; end
            else break;
        end;
        if (endpos<begpos) then
        begin
            if (modifyPanel) then begin
              cx:=x-1;  cy:=y-1;
              while (cx>=endpos) do
                begin GamePanel[cx,cy]:=GamePanel[x,y]; Dec(cx); Dec(cy); end;
            end;

            nconv:=abs(endpos-begpos);
            convs:=convs+nconv;
        end;

        {... check: [CP->'N'] ...}
        cx:=x;  cy:=y-1;  begpos:=y;  endpos:=begpos;
        while (cy>=1) do
        begin
            if (GamePanel[cx,cy]=nextplay) then Dec(cy)
            else if (GamePanel[cx,cy]=currplay) then
                begin endpos:=cy+1; break; end
            else break;
        end;
        if (endpos<begpos) then
        begin
            if (modifyPanel) then begin
              cy:=y-1;
              while (cy>=endpos) do
                begin GamePanel[cx,cy]:=GamePanel[x,y]; Dec(cy); end;
            end;

            nconv:=abs(endpos-begpos);
            convs:=convs+nconv;
        end;

        {... check: [CP->'NE'] ...}
        cx:=x+1;  cy:=y-1;  begpos:=x;  endpos:=begpos;
        while ((cx<=cPanelSize)and(cy>=1)) do
        begin
            if (GamePanel[cx,cy]=nextplay) then
                begin Inc(cx); Dec(cy); end
            else if (GamePanel[cx,cy]=currplay) then
                begin endpos:=cx-1; break; end
            else break;
        end;
        if (endpos>begpos) then
        begin
            if (modifyPanel) then begin
              cx:=x+1;  cy:=y-1;
              while (cx<=endpos) do
                begin GamePanel[cx,cy]:=GamePanel[x,y]; Inc(cx); Dec(cy); end;
            end;

            nconv:=abs(endpos-begpos);
            convs:=convs+nconv;
        end;
    end;

    makePawnConversions:=convs;
end;

{... check is a move is possible ...}
function tryNewMove( var GamePanel : TGamePanel; x, y, plays : Integer ) : Boolean;
var
    validmove : Boolean;
begin
    if (GamePanel[x,y]<>cEmpty) then validmove:=false
    else
      begin
        GamePanel[x,y]:=plays;
        if (makePawnConversions(GamePanel,x,y,false)>0) then validmove:=true
        else  validmove:=false;
        GamePanel[x,y]:=cEmpty;
      end;
    tryNewMove:=validmove;
end;

{... create set of 'next' game moves ...}
function createNextMoves( var currentGame : TGamePanel; player : Integer; var newmoves : TGameMoves ) : Integer;
var
    x, y, c : Integer;
begin
    c:=0;  SetLength(newmoves,cListGrow);
    for x:=1 to cPanelSize do
        for y:=1 to cPanelSize do
            if (tryNewMove(currentGame,x,y,player)) then
              begin
                if (c>High(newmoves)) then SetLength(newmoves,High(newmoves)+cListGrow);
                newmoves[c].x:=x;  newmoves[c].y:=y;
                Inc(c);
              end;

    SetLength(newmoves,c);
    createNextMoves:=c;
end;

{... create set of 'next' game boards ...}
function createNextGames( var currentGame : TGamePanel; player : Integer; var newmoves : TGameMoves; var newgames : TGameSet ) : Integer;
var
    c : Integer;
begin
    SetLength(newgames,High(newmoves)+1);
    for c:=0 to High(newgames) do
    begin
        copyGamePanel(currentGame,newgames[c]);
        newgames[c][newmoves[c].x,newmoves[c].y]:=player;
        makePawnConversions(newgames[c],newmoves[c].x,newmoves[c].y,true);
    end;

    createNextGames:=High(newmoves)+1;
end;

{********************************************************}

{... begin application ...}
procedure TMainForm.Initialize;
begin
    {cursorThread:=CursorShape.Create(false);}
    InitGame;
    DrawAll;
end;

{... begin game (1st time) ...}
procedure TMainForm.InitGame;
begin
    NewGame;
    playType[cBlack]:=cUserPlayer;  playLevel[cBlack]:=2;
    playType[cWhite]:=cComputerPlayer;  playLevel[cWhite]:=2;
end;

{... begin new game ...}
procedure TMainForm.NewGame;
var
    x, y : Integer;
begin
    for x:=1 to cPanelSize do
        for y:=1 to cPanelSize do
            GamePanel[x,y] := cEmpty;

    GamePanel[4,4]:=cWhite;
    GamePanel[5,4]:=cWhite;
    GamePanel[4,5]:=cBlack;
    GamePanel[5,5]:=cBlack;
    updateCounts;  stChanged:=0;  nextPlays:=cBlack;
    stLastX:=0; stLastY:=0;
    playing:=true;  computing:=false;
end;

{... clear & redraw game panel ...}
procedure TMainForm.ClearPanel;
var
    p1, p2 : TPoint;
    x, y : Integer;
    rect : TRect;
begin
    with MainForm.Grid do begin
      rect.top:=0;  rect.left:=0;
      rect.bottom:=Height-1;  rect.right:=Width-1;
      Canvas.Brush.Color := clGray;
      Canvas.Brush.Style := bsSolid;
      Canvas.FillRect(rect);

      Canvas.Pen.Color:=clBlack;
      for x:=1 to cPanelSize do
      begin
          p1.x:=(x-1)*cBoxSize;  p2.x:=p1.x+cBoxSize;
          for y:=1 to cPanelSize do
          begin
              p1.y:=(y-1)*cBoxSize;  p2.y:=p1.y;
              Canvas.PenPos:=p1;
              Canvas.LineTo(p2.x,p2.y);
          end;
          p1.x:=0;  p2.x:=Width-1;
          p1.y:=Height-1;  p2.y:=p1.y;
          Canvas.PenPos:=p1;
          Canvas.LineTo(p2.x,p2.y);
      end;

      for y:=1 to cPanelSize do
      begin
          p1.y:=(y-1)*cBoxSize;  p2.y:=p1.y+cBoxSize;
          for x:=1 to cPanelSize do
          begin
              p1.x:=(x-1)*cBoxSize;  p2.x:=p1.x;
              Canvas.PenPos:=p1;
              Canvas.LineTo(p2.x,p2.y);
          end;
          p1.x:=Width-1;  p2.x:=p1.x;
          p1.y:=0;  p2.y:=Height;  {+1 point to cover conver}
          Canvas.PenPos:=p1;
          Canvas.LineTo(p2.x,p2.y);
      end;
    end;
end;

{... show game board on panel ...}
procedure TMainForm.DrawPanel;
var
    x, y : Integer;
begin
    for x:=1 to cPanelSize do
        for y:=1 to cPanelSize do
            placePawn(x,y,GamePanel[x,y]);
end;

{... draw all statistics & score ...}
procedure TMainForm.DrawScore;
var
    str1, str2, str3 : String;
begin
    Str(pnBlacks,str1);  scoreBlack.Caption:=str1;
    Str(pnWhites,str2);  scoreWhite.Caption:=str2;

    Str(pnBlacks+pnWhites,str1);        statMoves.Caption:=str1;
    Str((pnBlacks+pnWhites) div 2,str2);  statRounds.Caption:=str2;

    Str(stChanged,str1);  statChanged.Caption:=str1;

    if ((stLastX=0)or(stLastY=0)) then
        statLast.Caption:='(none)'
    else
      begin
        Str(stLastX,str1);  Str(stLastY,str2);
        case nextPlays of    {-> show last player (current)}
            cBlack: str3:='BLACK';
            cWhite: str3:='WHITE';
        end;
        statLast.Caption:=str3+' @ ['+str1+','+str2+']';
      end;

    if (playType[cBlack]=cUserPlayer) then lblPlay1.Caption:='(human)'
    else lblPlay1.Caption:='(computer)';

    if (playType[cWhite]=cUserPlayer) then lblPlay2.Caption:='(human)'
    else lblPlay2.Caption:='(computer)';
end;

{... draw all game components (window)  ...}
procedure TMainForm.DrawAll;
begin
    ClearPanel;
    DrawPanel;
    DrawScore;
end;

{... draw individual pawn (no checks) ...}
procedure TMainForm.DrawPawn( x, y, val : Integer );
var
    p1, p2 : TPoint;
    rect : TRect;
    color : TColor;
begin
    with MainForm.Grid do begin
        if (val=cBlack) then color:=clNavy
        else  {val=cWhite}  color:=clWhite;

        p1.x:=(x-1)*cBoxSize+2;  p1.y:=(y-1)*cBoxSize+2;
        p2.x:=p1.x+cBoxSize-3;   p2.y:=p1.y+cBoxSize-3;

        Canvas.Pen.Color:=color;
        rect.top:=p1.y;  rect.left:=p1.x;
        rect.bottom:=p2.y;  rect.right:=p2.x;
        Canvas.Ellipse(rect);

        Canvas.Brush.Color := color;
        Canvas.Brush.Style := bsSolid;
        Canvas.FloodFill(p1.x+(cBoxSize div 2),p1.y+(cBoxSize div 2),color,fsBorder);

        Canvas.Pen.Color:=clBlack;
        Canvas.Ellipse(rect);
        rect.top:=p1.y;  rect.left:=p1.x;
        rect.bottom:=p2.y-5;  rect.right:=p2.x;
        Canvas.Ellipse(rect);
    end;
end;

{... place individual pawn on board (checked) ...}
procedure TMainForm.placePawn( x, y, player : Integer );
begin
    if (((player=cBlack)or(player=cWhite))
        and(x>=1)and(x<=cPanelSize)and(y>=1)and(y<=cPanelSize)) then
    begin
        DrawPawn(x,y,player);
    end;
end;

{... recalculate current score ...}
procedure TMainForm.updateCounts;
var
    x, y : Integer;
begin
    pnBlacks:=0;  pnWhites:=0;
    for x:=1 to cPanelSize do
        for y:=1 to cPanelSize do
            case GamePanel[x,y] of
                cBlack: Inc(pnBlacks);
                cWhite: Inc(pnWhites);
            end;
end;

{... make or just calculate pawn conversions from recent move ...}
function TMainForm.pawnConversions( x, y : Integer; modifyPanel : Boolean ) : Integer;
begin
    pawnConversions:=makePawnConversions(GamePanel,x,y,modifyPanel);
end;

function TMainForm.tryMove( x, y, plays : Integer ) : Boolean;
begin
    tryMove:=tryNewMove(GamePanel,x,y,plays);
end;

{... make a move for current player ...}
procedure TMainForm.doMove( x, y : Integer );
var
    px, py : Integer;
    str1 : String;
begin
    px:=(x div cBoxSize)+1;  py:=(y div cBoxSize)+1;
    if (GamePanel[px,py]=cEmpty) then
    begin
        if (tryMove(px,py,nextPlays)) then
        begin
            { actual move procedures are here }
            GamePanel[px,py]:=nextPlays;
            stChanged:=pawnConversions(px,py,true);
            stLastX:=px;  stLastY:=py;
            updateCounts;
            DrawAll;

            { check #1: someone has won }
            if (checkWinner<>-1) then
              begin updateStatus(px,py); playing:=false; end
            else
              begin
                { check #2: play continues, but can next player play? }
                nextPlays:=(nextPlays+1)mod(2);
                if (not hasFreeMoves(nextPlays)) then
                  begin
                    case nextPlays of
                        cBlack: str1:='BLACK';
                        cWhite: str1:='WHITE';
                    end;
                    if ((pnBlacks+pnWhites)<(cPanelSize*cPanelSize)) then
                        ShowMessage('Player '+str1+' looses this turn');
                    nextPlays:=(nextPlays+1)mod(2);
                  end;

                { check #3: if player replays, is there any valid move? }
                if (not hasFreeMoves(nextPlays)) then
                  begin
                    if ((pnBlacks+pnWhites)<(cPanelSize*cPanelSize)) then
                        ShowMessage('No player can play!');
                    if (pnBlacks>pnWhites) then str1:='Game finished: winner is BLACK'
                    else if (pnBlacks<pnWhites) then  str1:='Game finished: winner is WHITE'
                    else  str1:='Game finished: it is a draw!';
                    StatusLine.Caption:=str1;  ShowMessage(str1);
                    playing:=false;
                  end;
              end;
        end;
    end;
end;

{... cost function #1: select maximum conversions ...}
{ Notes: aggressive play, generally effective }
{function TMainForm.costFunction1( x, y, player : Integer ) : Integer;
var
    movecost : Integer;
begin
    GamePanel[x,y]:=nextPlays;
    movecost:=pawnConversions(x,y,false);
    GamePanel[x,y]:=cEmpty;

    costFunction1:=movecost;
end;
}

{... cost function #2: select maximum conversions, prefer sides ...}
{ Notes: aggressive play, prefers closed sides, very effective }
{function TMainForm.costFunction2( x, y, player : Integer ) : Integer;
var
    movecost : Integer;
begin
    GamePanel[x,y]:=nextPlays;
    movecost:=pawnConversions(x,y,false);
    Inc(movecost,closedSides(GamePanel,x,y));
    GamePanel[x,y]:=cEmpty;

    costFunction2:=movecost;
end;
}

{... cost function #3: select minimum next damage ...}
{ Notes: good when playing for Black, a little better than #1 in general }
(*function TMainForm.costFunction3( x, y, player : Integer ) : Integer;
var
    cx, cy, movecost, otherPlayer : Integer;
    gpanel : TGamePanel;
    {str1, str2, str3 : String;}
begin
    for cx:=1 to cPanelSize do
        for cy:=1 to cPanelSize do
            gpanel[cx,cy]:=GamePanel[cx,cy];  { backup current board }

    GamePanel[x,y]:=nextPlays;
    pawnConversions(x,y,true);   { make temporary move }

    otherPlayer:=(nextPlays+1) mod 2;
    movecost:=1;  { force at least one selected move }
    for cx:=1 to cPanelSize do
        for cy:=1 to cPanelSize do
            if (not tryMove(cx,cy,otherPlayer)) then continue
            else movecost:=Max(movecost,costFunction1(cx,cy,otherPlayer));  { select min 'damage' }

    {Str(x,str1); Str(y,str2); Str(movecost,str3);
    ShowMessage('move: ['+str1+','+str2+']  ->  gain = '+str3);}

    for cx:=1 to cPanelSize do
        for cy:=1 to cPanelSize do
            GamePanel[cx,cy]:=gpanel[cx,cy];   { restore board }

    costFunction3:=30-movecost;  { max possible conversions minus max damage, return as gain }
end;
*)

{... cost function #4: select maximum 'open' positions ...}
{ Notes: bad behaviour generally (not currently utilized) }
(*function TMainForm.costFunction4( x, y, player : Integer ) : Integer;
var
    cx, cy, movecost {, otherPlayer} : Integer;
    gpanel : TGamePanel;
    {str1, str2, str3 : String;}
begin
    for cx:=1 to cPanelSize do
        for cy:=1 to cPanelSize do
            gpanel[cx,cy]:=GamePanel[cx,cy];  { backup current board }

    GamePanel[x,y]:=nextPlays;
    pawnConversions(x,y,true);   { make temporary move }

    {otherPlayer:=(nextPlays+1) mod 2;}
    movecost:=1;  { force at least one selected move }
    for cx:=1 to cPanelSize do
        for cy:=1 to cPanelSize do
            if (not tryMove(cx,cy,nextPlays)) then continue
            else Inc(movecost,costFunction1(cx,cy,nextPlays));  { select max 'open' positions }

    {Str(x,str1); Str(y,str2); Str(movecost,str3);
    ShowMessage('move: ['+str1+','+str2+']  ->  gain = '+str3);}

    for cx:=1 to cPanelSize do
        for cy:=1 to cPanelSize do
            GamePanel[cx,cy]:=gpanel[cx,cy];   { restore board }

    costFunction4:=movecost;  { max 'open' positions, return as gain }
end;
*)

{... generic cost function: a weighted combination ...}
{ Notes: use functions #1 and #3 in weighted sum }
(*function TMainForm.costFunction( x, y, player : Integer ) : Integer;
var
    mc1, mc2, movecost : Integer;
    w1, w2 : Real;
    {str1, str2 ,str3 : String;}
begin
    mc1:=costFunction1(x,y,player);
    mc2:=costFunction3(x,y,player);

    { adaptive strategy: select max conversion when in danger, max open moves when not }
    if (player=cBlack) then w1:=pnBlacks/(pnBlacks+pnWhites)
    else w1:=pnWhites/(pnBlacks+pnWhites);
    w2:=1-w1;

    movecost:=Round(mc1*w1+mc2*w2);   { weighted cost }

    {Str(x,str1); Str(y,str2); Str(movecost,str3);
    ShowMessage('move: ['+str1+','+str2+']  ->  gain = '+str3);}

    costFunction:=movecost;
end;
*)

{... make an optimal move for computer player  ...}
function TMainForm.doComputerMove : Boolean;
var
    {x, y, newvalue, t, p, rx, ry : Integer;}
    newmove : TPoint;
    canmove : Boolean;
    {str1, str2 : String;}
    bestmove : TPoint;
    todepth : Integer;
    curcursor : TCursor;
begin
    {... Minimax search for optimum next move ...}
    { Note: only even depths given good results, use edges for level>50% }
    curcursor:=Screen.Cursor;
    Screen.Cursor:=crHourGlass;
    StatusLine.Caption:='Trying new move...';
    StatusLine.Invalidate;

    useEdges:=((playLevel[nextPlays] mod 2)=0);
    todepth:=((playLevel[nextPlays]+1) div 2)*2;
    canmove:=SelectMove_Minimax(GamePanel,nextPlays,todepth,bestmove);
    newmove.x:=bestmove.x;  newmove.y:=bestmove.y;

    Screen.Cursor:=curcursor;
    StatusLine.Caption:='Trying new move... done!';
    StatusLine.Invalidate;

    {Str(newmove.x,str1);  Str(newmove.y,str2);
    ShowMessage('Minimax decided: best move is @['+str1+','+str2+']');}

    {... perform optimal move or resign ...}
    if (canmove) then
        doMove((newmove.x-1)*cBoxSize,(newmove.y-1)*cBoxSize)
    else  { no valid move found }
        ShowMessage('Computer player has resigned!');

    doComputerMove:=canmove;
end;

{... show game status (status line) ...}
procedure TMainForm.updateStatus( x, y : Integer );
var
    str1, str2, str3 : String;
    px, py, wincond : Integer;
begin
    px:=(x div cBoxSize)+1;  py:=(y div cBoxSize)+1;

    wincond:=checkWinner;
    if (wincond<>-1) then
      begin
        case wincond of
            cBlack: str3:='Game finished: winner is BLACK';
            cWhite: str3:='Game finished: winner is WHITE';
             cDraw: str3:='Game finished: it is a draw!';
        end;
        StatusLine.Caption:=str3;  ShowMessage(str3);
      end
    else
      begin
        Str(px,str1); Str(py,str2);
        case nextPlays of
            cBlack: str3:='BLACK';
            cWhite: str3:='WHITE';
        end;
        StatusLine.Caption:=Concat('Next plays: ',str3,' at: [',str1,',',str2,']');
      end;

    if (tryMove(px,py,nextPlays)) then Grid.Cursor:=crHandPoint
    else Grid.Cursor:=crNoDrop;
end;

{... check for winning conditions (game end) ...}
function TMainForm.checkWinner : Integer;
var
    checkres : Integer;
begin
    if ((pnBlacks=0)or(((pnBlacks+pnWhites)=(cPanelSize*cPanelSize))and(pnWhites>pnBlacks))) then
      begin checkres:=cWhite; end
    else if (((pnWhites=0)or((pnBlacks+pnWhites)=(cPanelSize*cPanelSize))and(pnWhites<pnBlacks))) then
      begin checkres:=cBlack; end
    else if (((pnBlacks+pnWhites)=(cPanelSize*cPanelSize))and(pnWhites=pnBlacks)) then
      begin checkres:=cDraw; end
    else  checkres:=-1;

    checkWinner:=checkres;
end;

{... check for available moves ...}
function TMainForm.hasFreeMoves( player : Integer ) : Boolean;
var
    x, y : Integer;
    canmove : Boolean;
begin
    canmove:=false;
    for x:=1 to cPanelSize do
        for y:=1 to cPanelSize do
        begin
            if (canmove) then continue
            else canmove:=tryMove(x,y,player);
        end;
    hasFreeMoves:=canmove;
end;

{... Menu: Game->Exit ...}
procedure TMainForm.N5Click(Sender: TObject);
begin
    Halt(0);
end;

{... client window repaint ...}
procedure TMainForm.FormPaint(Sender: TObject);
begin
    DrawAll;
end;

{... mouse click inside game panel (select move) ...}
procedure TMainForm.GridMouseDown(Sender: TObject; Button: TMouseButton;
  Shift: TShiftState; X, Y: Integer);
begin
    if (playing) then
    begin
        if ((playType[nextPlays]=cUserPlayer)and(Button=mbLeft)) then
            doMove(X,Y)
        else if (playType[nextPlays]=cComputerPlayer) then
            doComputerMove;
    end;
end;

{... track mouse while inside game panel ...}
procedure TMainForm.GridMouseMove(Sender: TObject; Shift: TShiftState; X, Y: Integer);
begin
    if (playing) then updateStatus(X,Y);
end;

{... begin application ...}
procedure TMainForm.FormCreate(Sender: TObject);
begin
    Initialize;
end;

{... Menu: Game->New ...}
procedure TMainForm.N3Click(Sender: TObject);
begin
    NewGame;
    DrawAll;
end;

{... Menu: Help->About ...}
procedure TMainForm.N7Click(Sender: TObject);
begin
    AboutBox.ShowModal;
end;

{... Menu: Game->Settings ...}
procedure TMainForm.Settings1Click(Sender: TObject);
begin
    SetupForm.Show;
end;

end.
