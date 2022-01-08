#ifndef      __BIT_ARRAY_H
#define     __BIT_ARRAY_H


#include <math.h>
#include <cstring>
#include <iostream>
#include <stdio.h>
#include <ctype.h>
#include "basearrs.h"


typedef     unsigned char       byte;
typedef     unsigned int        word;
typedef     unsigned long       dword;

typedef     int                 TPos;

// typedef     enum { zero=0, one=1 }      TBit;
typedef     byte        TBit;
#define     zero        (byte)0
#define     one         (byte)1


/*** works fine for: i=0,1,...,31 ***/
#define     bitSetAt(i)         ((dword)pow(2,i))


#define     BITS_PER_BYTE       sizeof(byte)*8
#define     BITS_PER_WORD       sizeof(word)*8
#define     BITS_PER_DWORD      sizeof(dword)*8


string reverse( string str )
{
    string      rstr;
    int         i;

    for ( i=0; i<str.length(); i++ )
        rstr.prepend(str(i));

    return(rstr);
}


class BitArray : public BaseArray<byte>
{
    public:
        BitArray()
            : BaseArray<byte>()             {  }
        BitArray( TPos size_in_bits )
            : BaseArray<byte>(size_in_bits)            {  }
        BitArray( BitArray & a)
            : BaseArray<byte>(a)            {  }

        TPos size( void )
            {  return((TPos)GetSize());  }
        TBit & bit( TPos idx )
            {  /*if (idx>=size())  return(zero);
               else*/  return((TBit)ItemAt(idx));  }

        TPos setBin( string binstr );
        TPos setHex( string hexstr );
        TPos set( BitArray & a );
        TPos set( long num );
        string toBin( void );
        string toHex( void );

        TBit shiftUp( void );
        TBit shiftDown( void );

        int bitCompare( BitArray & a );

        void bitNot( void );
        TBit bitAdd( BitArray & a, TBit carry );
};


TPos BitArray::set( BitArray & a )
{
    TPos    i;

    if (size()!=a.size())  Resize(a.size());
    for ( i=0; i<size(); i++ )
        bit(i)=a.bit(i);

    return(size());
}


TPos BitArray::set( long num )
{
    char    str[10];
    string  sres;

    if (num<0)  num = -num;
    sprintf(str,"%lX",num);
    sres.append(str);
    setHex(sres);

    return(size());
}


TPos BitArray::setBin( string binstr )
{
    TPos    i=0;

    binstr=reverse(binstr);
    while (i<size())
    {
        if (i<binstr.length())
            bit(i) = ((binstr(i)=='1')?1:0);
        else
            bit(i) = 0;

        i++;
    }

    return(size());
}


TPos BitArray::setHex( string hexstr )
{
    TPos    i=0;
    char    s;
        

    for ( i=1; i<=size()%4; i++ )
        bit(size()-i)=zero;

    hexstr=reverse(hexstr);
    for ( i=0; (i+3)<size(); i=i+4 )
    {
        if ( ((int)i/4) < hexstr.length() )
        {
            s=toupper(hexstr((int)i/4));
            switch (s)
            {
                case '0': bit(i)=zero; bit(i+1)=zero; bit(i+2)=zero; bit(i+3)=zero;
                          break;
                case '1': bit(i)=one; bit(i+1)=zero; bit(i+2)=zero; bit(i+3)=zero;
                          break;
                case '2': bit(i)=zero; bit(i+1)=one; bit(i+2)=zero; bit(i+3)=zero;
                          break;
                case '3': bit(i)=one; bit(i+1)=one; bit(i+2)=zero; bit(i+3)=zero;
                          break;
                case '4': bit(i)=zero; bit(i+1)=zero; bit(i+2)=one; bit(i+3)=zero;
                          break;
                case '5': bit(i)=one; bit(i+1)=zero; bit(i+2)=one; bit(i+3)=zero;
                          break;
                case '6': bit(i)=zero; bit(i+1)=one; bit(i+2)=one; bit(i+3)=zero;
                          break;
                case '7': bit(i)=one; bit(i+1)=one; bit(i+2)=one; bit(i+3)=zero;
                          break;
                case '8': bit(i)=zero; bit(i+1)=zero; bit(i+2)=zero; bit(i+3)=one;
                          break;
                case '9': bit(i)=one; bit(i+1)=zero; bit(i+2)=zero; bit(i+3)=one;
                          break;
                case 'A': bit(i)=zero; bit(i+1)=one; bit(i+2)=zero; bit(i+3)=one;
                          break;
                case 'B': bit(i)=one; bit(i+1)=one; bit(i+2)=zero; bit(i+3)=one;
                          break;
                case 'C': bit(i)=zero; bit(i+1)=zero; bit(i+2)=one; bit(i+3)=one;
                          break;
                case 'D': bit(i)=one; bit(i+1)=zero; bit(i+2)=one; bit(i+3)=one;
                          break;
                case 'E': bit(i)=zero; bit(i+1)=one; bit(i+2)=one; bit(i+3)=one;
                          break;
                case 'F': bit(i)=one; bit(i+1)=one; bit(i+2)=one; bit(i+3)=one;
                          break;
                default:  bit(i)=zero; bit(i+1)=zero; bit(i+2)=zero; bit(i+3)=zero;
                          break;
            }
        }
        else
        {
            bit(i)=zero; bit(i+1)=zero; bit(i+2)=zero; bit(i+3)=zero;
        }
    }

    return(size());
}


string BitArray::toBin( void )
{
    string  res;
    TPos    i=0;     

    while (i<size())
    {
        switch (bit(i))
        {
            case zero: res.append("0"); break;
            case one:  res.append("1"); break;
            default:   res.append("?"); break;
        }

        i++;
    }
    res=reverse(res);

    return(res);
}


string BitArray::toHex( void )
{
    string  res;
    TPos    i=0;
    int     h=0, s=0;
        
    for ( i=0,s=0,h=0; i<size(); i++ )
    {
        if (bit(i)==one)
            s = s + (int)bitSetAt(h);
        h++;

        if (h==4)
        {
            switch (s)
            {
                case 0:  res.append("0");  break;
                case 1:  res.append("1");  break;
                case 2:  res.append("2");  break;
                case 3:  res.append("3");  break;
                case 4:  res.append("4");  break;
                case 5:  res.append("5");  break;
                case 6:  res.append("6");  break;
                case 7:  res.append("7");  break;
                case 8:  res.append("8");  break;
                case 9:  res.append("9");  break;
                case 10: res.append("A");  break;
                case 11: res.append("B");  break;
                case 12: res.append("C");  break;
                case 13: res.append("D");  break;
                case 14: res.append("E");  break;
                case 15: res.append("F");  break;
                default: res.append("?");  break;
            }

            h=0;  s=0;
        }
    }
    res=reverse(res);

    return(res);
}


TBit BitArray::shiftUp( void )
{
    TBit    carry;
    TPos    i;


    carry=bit(size()-1);
    for ( i=size()-1; i>0; i-- )
        bit(i)=bit(i-1);
    bit(0)=zero;

    return(carry);
}


TBit BitArray::shiftDown( void )
{
    TBit    carry;
    TPos    i;


    carry=bit(0);
    for ( i=0; i<size()-1; i++ )
        bit(i)=bit(i+1);
    bit(size()-1)=zero;

    return(carry);
}


int BitArray::bitCompare( BitArray & a )
{
    TPos    i, lim;
    int     res;


    /*** compare as if they are of different rank **/
    lim = min(size(),a.size());

    if (size()>a.size())
    {
        for ( i=size()-1; i>=lim; i-- )
            if (bit(i)==one)  return(1);
    }
    else if (size()<a.size())
    {
        for ( i=a.size()-1; i>=lim; i-- )
            if (a.bit(i)==one)  return(-1);
    }

    /*** compare as same rank ***/
    for ( i=lim-1; i>=0; i-- )
    {
        if (bit(i)!=a.bit(i))
        {
            if (bit(i)==one)  return(1);
            else  return(-1);
        }
    }

    return(0);
}



void BitArray::bitNot( void )
{
    for ( TPos i=0; i<size(); i++ )
        bit(i) = ((bit(i)==zero)?one:zero);
}


TBit BitArray::bitAdd( BitArray & a, TBit carry )
{
    TPos    i, lim;
    TBit    ncarry=carry;
    int     s;


    lim = min(size(),a.size());

    for ( i=0; i<lim; i++ )
    {
        s = (int)bit(i) + (int)a.bit(i) + (int)ncarry;
        bit(i) = (TBit)(s%2);
        ncarry = (TBit)(s/2);
    }

    if (lim<size())
    {
        bit(lim)=ncarry;
        ncarry=zero;

        for ( i=lim+1; i<size(); i++ )
            bit(i)=zero;
    }

    return(ncarry);
}



/******************************************/

/*
void main( void )
{
    BitArray    n, a, b;
    TPos        i;
    string      str;
    TBit        carry;
    unsigned long    ival;


    cout << "Give number of bits:  ";
    cin >> i;
    n.Resize(i);
    cout << "Number with " << n.size() << " bits created" << endl << endl;

    cout << "Give a DEC value to assign:  ";
    cin >> ival;
    cout << "Assigning " << ival << endl;
    n.set(ival);
    cout << "Current value (bin) is:  " << n.toBin() << endl;
    cout << "Current value (hex) is:  " << n.toHex() << endl << endl;

    a.set(n);
    a.shiftDown();
    cout << a.toBin() << " .REL_OP. " << n.toBin() << " = " << a.bitCompare(n) << endl;
    cout << n.toBin() << " .REL_OP. " << a.toBin() << " = " << n.bitCompare(a) << endl;
    cout << a.toBin() << " .REL_OP. " << a.toBin() << " = " << a.bitCompare(a) << endl << endl;
    a.bit(a.GetSize()-1)=one;
    cout << a.toBin() << " .REL_OP. " << n.toBin() << " = " << a.bitCompare(n) << endl;
    cout << n.toBin() << " .REL_OP. " << a.toBin() << " = " << n.bitCompare(a) << endl;
    cout << a.toBin() << " .REL_OP. " << a.toBin() << " = " << a.bitCompare(a) << endl << endl;
    cout << n.toBin() << " + " << a.toBin() << " = ";
    carry=n.bitAdd(a,zero);
    cout << n.toBin() << " (carry=" << (int)carry << ")\n";

    cout << "Current value (bin) is:  " << n.toBin() << endl;
    cout << "Current value (hex) is:  " << n.toHex() << endl << endl;
}

*/


#endif


