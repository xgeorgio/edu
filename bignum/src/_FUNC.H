#ifndef         __MINMAX_H
#define         __MINMAX_H


template <class T>
T min( T a, T b )     {  return( (a<b)?a:b );  }


template <class T>
T max( T a, T b )     {  return( (a<b)?b:a );  }


#endif


