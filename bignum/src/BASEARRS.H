//--------------------------------------------
//  Template Class:  BaseArray<T>
//
//     Simplified array template class, 
//     with dynamic memory handling. Can
//     be used as base for any (direct)
//     one-dimensional array in C++.
//--------------------------------------------
//               Harris Georgiou, 1996.
//--------------------------------------------



#ifndef     __ABSTRACT_ARRAY_H
#define     __ABSTRACT_ARRAY_H


template <class T> class AbstractArray
{
    // We can declare only general member functions
    // that is functions that do not contain class' name

    public:
        virtual int  IsVoid( void )=0;
        virtual int  IsValid( void )=0;

        virtual int  Alloc( int size )=0;
        virtual void Init( T &initVal, int startFrom=0 )=0;
        virtual void Done( void )=0;
        virtual int  GetSize( void )=0;
        virtual int  Resize( int newsize )=0;
        virtual T &  ItemAt( int idx )=0;
    
        virtual operator int()=0;
        virtual T & operator []( int idx )=0;
        virtual T & operator ()( int idx )=0;
    
};


#endif


#ifndef     __BASEARRAYS_H
#define     __BASEARRAYS_H

#include <memory.h>
// #include "_func.h"


template <class T> class BaseArray : public AbstractArray<T>
{
    protected:
        T       *arr;
        int     sz;

    public:
        BaseArray()                     {  arr=NULL;  sz=0;  }
        BaseArray( int size )           {  arr=NULL;  sz=0;  Resize(size);  }
        BaseArray( BaseArray &a )       {  arr=NULL;  sz=0;  Copy(a);  }

        ~BaseArray()                    {  delete [] arr;  }

        int  IsVoid( void )             {  return(arr==NULL);  }
        int  IsValid( void )            {  return((arr!=NULL)&&(sz>0));  }

        int  Alloc( int size );
        void Init( T &initVal, int startFrom=0 );
        void Done( void )               {  if (arr) delete [] arr;  sz=0;  }
        int  Copy( BaseArray &a );
        int  GetSize( void )            {  return(sz);  }
        int  Resize( int newsize );
        T &  ItemAt( int idx )          {  return(arr[idx]);  }
    
        operator int()                  {  return(IsValid());  }
        BaseArray & operator =( BaseArray &a )          {  Copy(a); return(a);  }
        T & operator []( int idx )      {  return(ItemAt(idx));  }
        T & operator ()( int idx )      {  return(ItemAt(idx));  }
};



template <class T>
int BaseArray<T>::Alloc( int size )
{
    if ((size>0)&&(IsVoid()))
    {  arr=new T[size];
       if (arr)  sz=size;  else  sz=0;  }
    return(sz);  
}


template <class T>
void BaseArray<T>::Init( T &initVal, int startFrom=0 )
{
    if (IsValid())
    for (int c=((startFrom>=0)?startFrom:0); c<sz; c++ )
        arr[c]=initVal;
}


template <class T>
int BaseArray<T>::Copy( BaseArray<T> &a )
{
    if (sz!=a.GetSize())
       {  Done();  Alloc(a.GetSize());  }
       
    if (sz!=a.GetSize())  return(-1);
    else  {
    for (int c=0; c<a.GetSize(); c++)  arr[c]=a.ItemAt(c);
    return(sz);  }
}


template <class T>
int BaseArray<T>::Resize( int newSize )
{
    T   *newarr;


    if (IsVoid())  return(Alloc(newSize));
    else
    {
        if ((newSize>0)&&(newSize!=sz))
        {  
            // The following alternative does not work (Null pointer assignment)
            // if (realloc(arr,newSize*sizeof(T))!=NULL)   sz=newSize;

            newarr = new T[newSize];
            if (newarr!=NULL)
            {
                for ( int i=0; (i<newSize)&&(i<sz); i++ )
                    newarr[i] = arr[i];

                Done(); 
                arr = newarr;
                sz = newSize;
            }
        }
        
        return(sz);
    }
}


#endif


