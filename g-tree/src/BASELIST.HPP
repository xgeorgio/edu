// -------------------------------------------------
//
//
// -------------------------------------------------
//                         Harris Georgiou, 1997.
// -------------------------------------------------



#ifndef     _BASE_LIST
#define     _BASE_LIST


#include <_null.h>          // "NULL" macro definition

#ifndef     TCount         
#define     TCount      long
#endif



template <class D> class BaseListNode
{
	public:
		D               *data;
		BaseListNode    *prev;
		BaseListNode    *next;

	public:
		BaseListNode()
			{  init();  } 
		BaseListNode( D &newdata )
			{  init();  data=new D(newdata);  }
		BaseListNode( BaseListNode &node )
			{  copy(node);  }

		~BaseListNode()
			{  done();  }

		virtual void init( void )
			{  prev=NULL; next=NULL; data=NULL;  }
		virtual void done( void )
			{  if (data)  delete data;  }
		virtual void copy( BaseListNode &node )
			{  if (!data)  data=new D;  *data=*(node.data);  }
		
		virtual BaseListNode & operator =( BaseListNode &node )
			{  data=node.data;  return(node);  }
		virtual void operator =( D &newdata )
			{  if (!data)  data=new D;  *data=newdata;  }

		/***** These can only apply for simple types & classes *****
		int operator ==( BaseListNode &othernode )
			{  return( *data == *(othernode.data) );  }
		int operator <( BaseListNode &othernode )
			{  return( *data < *(othernode.data) );  }
		int operator >( BaseListNode &othernode )
			{  return( *data > *(othernode.data) );  }
		int operator <=( BaseListNode &othernode )
			{  return( *data <= *(othernode.data) );  }
		int operator >=( BaseListNode &othernode )
			{  return( *data >= *(othernode.data) );  }
		*****/

};



/*.........................................*/


template <class D> class BaseList
{
	public:
		BaseListNode<D>     *head;
		BaseListNode<D>     *tail;
		TCount              nodes;

	public:
		BaseList() 
			{  init();  }
		BaseList( BaseList &list )
			{  init(); copy(list);  }

		~BaseList()
			{  done();  }

		void init( void )
			{  head=NULL; tail=NULL; nodes=(TCount)0;  }
		void done( void );
		int isEmpty( void )
			{  return( (head==NULL)||(tail==NULL) );  }
		TCount countItems( void )
			{  return(nodes);  }
		
		void attachAtHead( BaseListNode<D> &node );
		void attachAtTail( BaseListNode<D> &node );
		void attachBefore( BaseListNode<D> &tolink, BaseListNode<D> &posnode );
		void attachAfter( BaseListNode<D> &tolink, BaseListNode<D> &posnode );
		
		BaseListNode<D> * detachFromHead( void );
		BaseListNode<D> * detachFromTail( void );
		BaseListNode<D> * detach( BaseListNode<D> &node );

		BaseListNode<D> * addAtHead( D &newdata ) 
			{  BaseListNode<D>  *p=new BaseListNode<D>(newdata);
			   if (p) attachAtHead(*p);  return(p);  }
		BaseListNode<D> * addAtTail( D &newdata ) 
			{  BaseListNode<D>  *p=new BaseListNode<D>(newdata);
			   if (p) attachAtTail(*p);  return(p);  }
		BaseListNode<D> * addBefore( D &newdata, BaseListNode<D> &posnode ) 
			{  BaseListNode<D>  *p=new BaseListNode<D>(newdata);
			   if (p) attachBefore(*p,posnode);  return(p);  }
		BaseListNode<D> * addAfter( D &newdata, BaseListNode<D> &posnode ) 
			{  BaseListNode<D>  *p=new BaseListNode<D>(newdata);
			   if (p) attachAfter(*p,posnode);  return(p);  }

		D * removeFromHead( void )
			{  D  *t=NULL;  BaseListNode<D> *n=detachFromHead();
			   if (n)  { t=(n->data); delete n; }
			   return(t);  }
		D * removeFromTail( void )
			{  D  *t=NULL;  BaseListNode<D> *n=detachFromTail();
			   if (n)  { t=(n->data); delete n; }
			   return(t);  }
		D * remove( D &remdata )
			{  D  *t=NULL;  BaseListNode<D> *n=findItem(remdata);
			   if (n)  { detach(*n); t=(n->data); delete n; }
			   return(t);  }

		void destroyFromHead( void )
			{  D  *t=removeFromHead();  if (t)  delete t;  }
		void destroyFromTail( void )
			{  D  *t=removeFromTail();  if (t)  delete t;  }
		void destroy( D &remdata )
			{  D  *t=remove(remdata);  if (t)  delete t;  }

		void copy( BaseList &list );
		BaseList & operator =( BaseList<D> &list )
			{  copy(list);  return(list);  }
			
		BaseListNode<D> * findItem( D &testdata );
		int hasItem( D &testdata )
			{  BaseListNode<D> *nptr=findItem(testdata);
			   if (nptr==NULL)  return(0);
			   else  return(1);  }
		D * peekHead( void )
			{  if (head) return(head->data);  else return(NULL);  }
		D * peekTail( void )
			{  if (tail) return(tail->data);  else return(NULL);  }
		D * operator []( int idx )
			{  return(getItem(idx));  }
		
		D * getFirst( void );
		D * getLast( void );
		D * getItem( int idx );

};


template <class D>
void BaseList<D>::done( void )
{
	BaseListNode<D>     *p;

	p = head;
	while (p!=tail)
		{  p = p->next;   delete  p->prev;  }
	if (p)  delete p;

	init();
}


template <class D>
void BaseList<D>::copy( BaseList<D> &list )
{
	BaseListNode<D>     *p, *n;

	done();
	p = list.head;
	while ((p!=NULL)&&(p!=list.tail))
		{  n=new BaseListNode<D>(*(p->data));
		   if (n)  { attachAtTail(*n); p=p->next; }  }
}


template <class D>
void BaseList<D>::attachBefore( BaseListNode<D> &tolink, BaseListNode<D> &posnode )
{  
	if (&posnode==head)  attachAtHead(tolink);
	else if (&posnode==tail)  attachAtTail(tolink);
	else
	{   
		tolink.prev=posnode.prev; tolink.next=&posnode;
		if (posnode.prev) posnode.prev->next=&tolink;
		posnode.prev=&tolink; 
		nodes++;
	}
}


template <class D>
void BaseList<D>::attachAfter( BaseListNode<D> &tolink, BaseListNode<D> &posnode )
{    
	if (&posnode==head)  attachAtHead(tolink);
	else if (&posnode==tail)  attachAtTail(tolink);
	else
	{   
		tolink.prev=&posnode; tolink.next=posnode.next;
		if (posnode.next) posnode.next->prev=&tolink;
		posnode.next=&tolink; 
		nodes++;
	}
}


template <class D>
void BaseList<D>::attachAtHead( BaseListNode<D> &node )
{  
	if (head==NULL)
		{  head=&node;  if (tail==NULL) tail=&node;  }
	else
		{  node.prev=NULL; node.next=head;
		   head->prev=&node; head=&node;  }
			
	nodes++;
}


template <class D>
void BaseList<D>::attachAtTail( BaseListNode<D> &node )
{
	if (tail==NULL) 
		{  tail=&node;  if (head==NULL) head=&node;  }
	else  
		{  node.prev=tail; node.next=NULL;
		   tail->next=&node; tail=&node; nodes++;  }

	nodes++;
}


template <class D>
BaseListNode<D> * BaseList<D>::detachFromHead( void )
{
	BaseListNode<D>     *p;

	if (nodes==0)
		{  p=NULL;  }
	else if (nodes==1)
		{  p=head; head=NULL; tail=NULL; nodes--;  }
	else  /*nodes>1*/
		{  p=head; head=p->next; head->prev=NULL; nodes--; }

	return(p);
}


template <class D>
BaseListNode<D> * BaseList<D>::detachFromTail( void )
{
	BaseListNode<D>     *p;

	if (nodes==0)
		{  p=NULL;  }
	else if (nodes==1)
		{  p=tail; head=NULL; tail=NULL; nodes--;  }
	else  /*nodes>1*/
		{  p=tail; head=p->prev; tail->next=NULL; nodes--; }

	return(p);
}


template <class D>
BaseListNode<D> * BaseList<D>::detach( BaseListNode<D> &node )
{
	if (&node==head)  return(detachFromHead());
	else if (&node==tail)  return(detachFromTail());
	else
	{   
		if (node.prev)  node.prev->next=node.next;
		if (node.next)  node.next->prev=node.prev;
		nodes--;  return(&node);
	}
}



template <class D>
D * BaseList<D>::getFirst( void ) 
{
	if (head==NULL)  return(NULL);
	else  return(head->data);
}


template <class D>
D * BaseList<D>::getLast( void ) 
{
	if (tail==NULL)  return(NULL);
	else  return(tail->data);
}


template <class D>
D * BaseList<D>::getItem( int idx )
{
	BaseListNode<D>     *p;
	TCount              count;

	
	if ((nodes>0)&&(idx<=nodes))
	{
		p=head;  count=(TCount)1; 
		while ((p!=NULL)&&(count<idx)) 
			{  p=p->next;  count++;  }

		return(p->data);
	}
	else
		return(NULL);
}


template <class D>
BaseListNode<D> * BaseList<D>::findItem( D &testdata )
{
	BaseListNode<D>     *p;

	
	p=head;
	while (p!=NULL) 
	{
		if (*(p->data) == testdata)  return(p);
		else  p=p->next;
	}

	p=NULL;
	return(p);
}




#endif



/*******************************************************/

/*****
#include <stdio.h>


void main( void )
{
	BaseList<int>   L;
	BaseListNode<int>   *p;
	int             i;

	
	printf("BASELIST v2.5 - Template Class for DoubleLinkedList\n");
	
	printf("\nInitializing list...");
	L.init();
	printf("done.\n");

	printf("\nAdding 10 integers to the list...\n");
	for ( i=0; i<10; i++ )
		{  printf("%d  ",i);  L.addAfter(i,*(L.head));  }
	printf("\ndone. (items: %d)\n",i);

	printf("\nRetrieving 10 integers from the list...\n");
	for ( p=L.head; p!=NULL; p=p->next )
		{  printf("%d  ",*(p->data));  }
	printf("\ndone. (list items: %ld)\n",L.countItems());

	printf("\nSearching 6 integers in the list...\n");
	for ( i=-2; i<10; i=i+2 )
		{  printf("%d ?  %s\n",i,((L.hasItem(i))?"Found":"Not found"));  }
	printf("done.\n");
	
	printf("\nDestroying list...");
	L.done();
	printf("done.\n\n");

}
*****/


