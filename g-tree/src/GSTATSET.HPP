// -------------------------------------------------
//
//
// -------------------------------------------------
//                         Harris Georgiou, 1997.
// -------------------------------------------------



#ifndef     _GAME_STATUS_H
#define     _GAME_STATUS_H

#include "baselist.hpp"


class GameStatus;

typedef     BaseListNode<GameStatus>       GameStatusSetNode;



/*........... GAME STATUS SET ...........*/


class GameStatusSet : BaseList<GameStatus>
{
    public:
        GameStatusSet() 
            : BaseList<GameStatus>()      { }
        GameStatusSet( GameStatusSet &gsl ) 
            : BaseList<GameStatus>(gsl)      { }
        
        //~GameStatusSet()   { }

        GameStatusSetNode * add( GameStatus &newstat )
            { return(addAtHead(newstat)); }
        GameStatusSetNode * addUnique( GameStatus &newstat );
        GameStatusSetNode * addSorted( GameStatus &newstat );
        GameStatusSetNode * addUniqueSorted( GameStatus &newstat );

};



GameStatusSetNode * GameStatusSet::addUnique( GameStatus &newstat )
{
    GameStatusSetNode *gn=findItem(newstat);
    
    if (gn)  return(gn);
    else  return(addAtHead(newstat));
}


GameStatusSetNode * GameStatusSet::addSorted( GameStatus &newstat )
{
    GameStatusSetNode    *p;

    p=head;
    while (p!=NULL)
    {
        if (newstat.value()>(*(p->data)).value())  break;
        else  p=p->next;
    }
    
    return(addBefore(newstat,*p));
}


GameStatusSetNode * GameStatusSet::addUniqueSorted( GameStatus &newstat )
{
    GameStatusSetNode *p=findItem(newstat);
    
    
    if (p==NULL)
    {
        p=head;
        while (p!=NULL)
        {
            if (newstat.value()>(*(p->data)).value())  break;
            else  p=p->next;
        }
        p=addBefore(newstat,*p);
    }

    return(p);
}




#endif


