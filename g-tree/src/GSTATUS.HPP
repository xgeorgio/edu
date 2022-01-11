// -------------------------------------------------
//
//
// -------------------------------------------------
//                         Harris Georgiou, 1997.
// -------------------------------------------------



#ifndef     __GAME_STATUS_HPP__
#define     __GAME_STATUS_HPP__

#include <iostream.h>
#include "gamedefs.h"



/*........... GAME STATUS ...........*/


class GameStatusSet;

class GameStatus
{
    public:
        TBoard   gBoard[gSizeZ][gSizeY][gSizeX];
        TValue   gValue;

    public:
        GameStatus()
            { init();  gValue=cDefGameValue; }
        GameStatus( GameStatus &gs )
            { copy(gs); gValue=gs.value(); }

        //~GameStatus()     {}

    //..........
        virtual void init( TBoard initVal=cDefBoardValue );
        virtual void copy( GameStatus &gs );
        virtual void printOn( ostream &os );
        virtual int isEqualBoard( GameStatus &gs );
        virtual TValue value()          { return(gValue); }
        virtual TValue evaluate()       { return(cDefGameValue); }
        virtual GameStatusSet next()    { GameStatusSet gss; return(gss); }
    //..........

        int operator ==( GameStatus &other )
            { return(isEqualBoard(other)); }
        int operator !=( GameStatus &other )
            { return(!isEqualBoard(other)); }

        friend ostream & operator <<( ostream &os, GameStatus &gs );

};



void GameStatus::init( TBoard initVal )
{
    TSize      x, y, z;

    for ( z=0; z<gSizeZ; z++ )
        for ( y=0; y<gSizeY; y++ )
            for ( x=0; x<gSizeX; x++ )
                gBoard[z][y][x]=initVal;
}


void GameStatus::copy( GameStatus &gs )
{
    TSize      x, y, z;

    for ( z=0; z<gSizeZ; z++ )
        for ( y=0; y<gSizeY; y++ )
            for ( x=0; x<gSizeX; x++ )
                gBoard[z][y][x]=gs.gBoard[z][y][x];
}


int GameStatus::isEqualBoard( GameStatus &gs )
{
    TSize      x, y, z;
    int        res=1;

    for ( z=0; (z<gSizeZ)&&(res); z++ )
        for ( y=0; (y<gSizeY)&&(res); y++ )
            for ( x=0; (x<gSizeX)&&(res); x++ )
                res=(gBoard[z][y][x]==gs.gBoard[z][y][x]);
    
    return(res);
}



void GameStatus::printOn( ostream &os )
{
    TSize      x, y, z;

    for ( z=0; z<gSizeZ; z++ )
    {
        os << "BoardPlane=" << z+1 << endl;
        for ( y=0; y<gSizeY; y++ )
        {
            for ( x=0; x<gSizeX; x++ )
                os << gBoard[z][y][x] << " ";
            os << endl;
        }
    }
    os << "Value=" << gValue << endl;
}



ostream & operator <<( ostream &os, GameStatus &gs )
{
    gs.printOn(os);
    return(os);
}




#endif


