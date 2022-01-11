// -------------------------------------------------
//
//
// -------------------------------------------------
//                         Harris Georgiou, 1997.
// -------------------------------------------------



#ifndef     __GAME_TREENODE_SET_HPP__
#define     __GAME_TREENODE_SET_HPP__

#include "baselist.hpp"


class GameTreeNode;

#define     GameTreeNodeSetNode     BaseListNode<GameTreeNode>



/*........... GAME STATUS SET ...........*/


class GameTreeNodeSet : BaseList<GameTreeNode>
{
    public:
        GameTreeNodeSet() 
            : BaseList<GameTreeNode>()      { }
        GameTreeNodeSet( GameTreeNodeSet &gsl ) 
            : BaseList<GameTreeNode>(gsl)      { }
        
        //~GameTreeNodeSet()   { }

        GameTreeNodeSetNode * add( GameTreeNode &newnode )
            { return(addAtHead(newnode)); }
        GameTreeNodeSetNode * addUnique( GameTreeNode &newnode );
        GameTreeNodeSetNode * addSorted( GameTreeNode &newnode );
        GameTreeNodeSetNode * addUniqueSorted( GameTreeNode &newnode );

        //void clear( void );

};



GameTreeNodeSetNode * GameTreeNodeSet::addUnique( GameTreeNode &newnode )
{
    GameTreeNodeSetNode *gn=findItem(newnode);
    
    if (gn)  return(gn);
    else  return(addAtHead(newnode));
}


GameTreeNodeSetNode * GameTreeNodeSet::addSorted( GameTreeNode &newnode )
{
    GameTreeNodeSetNode    *p;

    p=head;
    while (p!=NULL)
    {
        if (newnode.current.value()>(*(p->data)).current.value())  break;
        else  p=p->next;
    }
    
    return(addBefore(newnode,*p));
}


GameTreeNodeSetNode * GameTreeNodeSet::addUniqueSorted( GameTreeNode &newnode )
{
    GameTreeNodeSetNode *p=findItem(newnode);
    
    
    if (p==NULL)
    {
        p=head;
        while (p!=NULL)
        {
            if (newnode.current.value()>(*(p->data)).current.value())  break;
            else  p=p->next;
        }
        p=addBefore(newnode,*p);
    }

    return(p);
}


/*
void GameTreeNodeSet::clear( void )
{
    GameTreeNodeSetNode    *p;

    if (countItems()>0)
    {
        p=head;
        while (p!=NULL)
        {
            if ((p->data).hasChildren())  (p->data).children.clear();
            p=p->next;
        }
        done();
    }
}
*/



#endif


