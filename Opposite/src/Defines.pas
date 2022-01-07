(*
   * * * * * * * * * * * * * * * * * * * * * * * *
   *                                             *
   *      ApplName:  OPPOSITE                    *
   *      FileName:  defines.pas                 *
   *   Description:  Shared definitions          *
   *                                             *
   *        Author:  Harris Georgiou (c) 2000.   *
   *                                             *
   * * * * * * * * * * * * * * * * * * * * * * * *
*)


unit Defines;

interface

uses windows;

const
    {... OPPOSITE unit constants definitions ...}
    cPanelSize = 8;   { 8x8 grid panel }
    cBoxSize   = 50;  {= 400 div cPanelSize}

    cEmpty = -1;        { should be < cBlack }
    cBlack = 0;
    cWhite = 1;         { should be cBlack+1 }
    cDraw = 100;

    cUserPlayer = 1;
    cComputerPlayer = 2;

    {... MINIMAX unit constants definitions ...}
    cPoolGrow = 1000;
    cListGrow = 20;

    cNullNode = -1;
    cNullData = '';

    cMaxDepth = 4;   { should be same as diff.levels max (setup form }

type
    {... OPPOSITE unit type definitions ...}
    TGamePanel = array [1..cPanelSize,1..cPanelSize] of ShortInt;

    TGameSet = array of TGamePanel;
    TGameMoves = array of TPoint;

    {... MINIMAX unit type definitions ...}
    GNodeList = array of Integer;

    GNode = record
        game : TGamePanel;
        prev : Integer;
        depth : Integer;
        moveX, moveY : Integer;
        follow : Integer;
        cost : Integer;
        nextPlays : Integer;  { next player (for new nodes), used for minimax }
        next : GNodeList;
        end;

    GNodePool = array of GNode;

    GTree = record
        pool : GNodePool;
        root : Integer;
        nextfree : Integer;
        moveX, moveY : Integer;
        follow : Integer;
        end;

implementation

end.
