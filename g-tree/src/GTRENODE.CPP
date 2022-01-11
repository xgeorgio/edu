// -------------------------------------------------
//
//
// -------------------------------------------------
//                         Harris Georgiou, 1997.
// -------------------------------------------------



#ifndef     __GAME_TREENODE_HPP__
#define     __GAME_TREENODE_HPP__


#include "baselist.hpp"
#include "gstatus.hpp"


/*........... GAME TREE NODE ...........*/


class GameTreeNodeSet;

class GameTreeNode : public GameStatus
{
    public:
        GameTreeNode        *parent;
        BaleList<GameTreeNode>     children;

    public:
        GameTreeNode()
            : current(), parent(NULL)           {}
        GameTreeNode( GameTreeNode &gtn )
            : current(gtn.current), parent(&gtn), children(gtn.children)  {}
        
        ~GameTreeNode()     { parent=NULL; }

        int hasParent( void )
            {  return(parent!=NULL);  }
        int hasChildren( void )
            {  return(children.countItems()>(TCount)0); }

        int operator ==( GameTreeNode &gtn )
            { return(isEqualBoard((GameStatus)gtn)); }
        int operator !=( GameTreeNode &gtn )
            { return(!isEqualBoard((GameStatus)gtn)); }
        
        //..........
        virtual GameTreeNodeSet next( void )
            { GameTreeNodeSet gtns;  return(gtns); }
        //..........
        
        friend ostream & operator <<( ostream &os, GameTreeNode &gtn );

};



ostream & operator <<( ostream &os, GameTreeNode &gtn )
{
    os << gtn.current << endl;
    return(os);
}



//#include "gtrndset.cpp"



#endif


void main( void )
{
    GameTreeNode    gtn;

    cout << gtn << endl;
}


