#include "bitarray.cpp"

#ifndef     FALSE
#define     FALSE   0
#endif
#ifndef     TRUE
#define     TRUE    !FALSE
#endif


static TBit     oflag;
static TBit     cflag;


class BigInt : public BitArray
{
    public:
        TBit            sign;

    public:
        BigInt()
            : BitArray()                {  reset();  }
        BigInt( TPos size_in_bits )
            : BitArray(size_in_bits)    {  reset();  }
        BigInt( BigInt & a)
            : BitArray(a),sign(a.sign)  {  reset();  }

        void reset( void )
            {  oflag=zero;  cflag=zero;  }
        int OvrFlow( void )
            {  return( ((oflag==one)?1:0) );  }
        int Carry( void )
            {  return( ((cflag==zero)?0:1) );  }
        int Sign( void )
            {  return( ((sign==zero)?1:-1) );  }
        char signChar( void )
            {  return( ((sign==zero)?'+':'-') );  }

        inline BigInt & operator =( string str );
        inline BigInt & operator =( BigInt & a );
        inline BigInt & operator =( long ival );

        friend inline BigInt operator +( BigInt a, BigInt b );

        inline string printAsHex( int sgn, int metr );
        inline string printAsBin( int sgn, int metr );
        friend ostream & operator << ( ostream & os, BigInt & a );
        friend istream & operator >> ( istream & is, BigInt & a );

};



BigInt & BigInt::operator =( string str )
{
    if ((str(str.length()-1)=='h')||(str(str.length()-1)=='H'))
    {
        if (str(0)=='+')
        {
            sign=zero;
            setHex(str.substr(1,str.length()-2));
        }
        else if (str(0)=='-')
        {
            sign=one;
            setHex(str.substr(1,str.length()-2));
        }
        else /*if (isxdigit(str(0)))*/
        {
            sign=zero;
            setHex(str.substr(0,str.length()-1));
        }
    }
    else if ((str(str.length()-1)=='b')||(str(str.length()-1)=='B'))
    {
        if (str(0)=='+')
        {
            sign=zero;
            setBin(str.substr(1,str.length()-2));
        }
        else if (str(0)=='-')
        {
            sign=one;
            setBin(str.substr(1,str.length()-2));
        }
        else /*if ((str(0)=='0')||(str(0)=='1'))*/
        {
            sign=zero;
            setBin(str.substr(0,str.length()-1));
        }
    }
    else
    {
        set(0L);
        sign=zero;
    }

    return(*this);
}


BigInt & BigInt::operator =( long ival )
{
    sign = ((ival<0)?one:zero);
    set((long)ival);

    return(*this);
}


BigInt & BigInt::operator =( BigInt & a )
{
    sign=a.sign;
    set(a);

    return(*this);
}


BigInt operator +( BigInt a, BigInt b )
{
    BigInt      i(a.size());
    TBit        c;


    a.reset();  i=0L;
    if (a.size()!=b.size())  return(i);

    if (a.sign==b.sign)
    {
        cflag = a.bitAdd(b,zero);
        oflag = cflag;
    }
    else
    {
        oflag = zero;
        i=1L;
        b.bitNot();
        c = a.bitAdd(i,zero);
        c = a.bitAdd(b,c);
        cflag = c;

        if ( a.Carry()==0 )
        {
            i=1L;
            a.bitNot();
            cflag = a.bitAdd(i,zero);
            a.sign = ((a.sign==zero)?one:zero);
        }
    }

    return(a);
}


string BigInt::printAsHex( int sgn=TRUE, int metr=TRUE )
{
    string  res;

    if (sgn)  res.append(signChar());
    res.append(toHex());
    if (metr)  res.append('h');
    return(res);
}


string BigInt::printAsBin( int sgn=TRUE, int metr=TRUE )
{
    string  res;

    if (sgn)  res.append(signChar());
    res.append(toBin());
    if (metr)  res.append('b');
    return(res);
}


ostream & operator << ( ostream & os, BigInt & a )
{
    os << a.printAsHex(TRUE,TRUE);
    return(os);
}


istream & operator >> ( istream & is, BigInt & a )
{
    string  inp;

    is >> inp;
    a = inp;
    return(is);
}



/******************************************/

using namespace std;

void main( void )
{
    BigInt      n, a, b;
    string      str;
    TPos        i;


    cout << "Give number of bits:  ";
    cin >> i;
    n.Resize(i);  a.Resize(i);  b.Resize(i);

    cout << "Number with " << n.size() << " bits created" << endl << endl;

    cout << "Give a (formatted) value A:  ";
    cin >> a;
    cout << "Current value (bin) is:  " << a.printAsBin() << endl;
    cout << "Current value (hex) is:  " << a << endl << endl;

    cout << "Give a (formatted) value B:  ";
    cin >> b;
    cout << "Current value (bin) is:  " << b.printAsBin() << endl;
    cout << "Current value (hex) is:  " << b << endl << endl;

    cout << "Calculating A+B ..." << endl;
    n = a + b;
    cout << "N=A+B : value (bin) is:  " << n.printAsBin() << endl;
    cout << "N=A+B : value (hex) is:  " << n << endl << endl;

}



