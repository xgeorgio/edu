#include <iostream>
#include "bitarray.cpp"


using namespace std;


void PrintBinStr( BitArray &ba )
{
    TCount      i;

    
    switch(ba.Sign())
    {
        case _POSITIVE: cout << "+"; break;
        case _NEGATIVE: cout << "-"; break;
        default:        cout << "_"; break;
    }

    for ( i=(TCount)0; i<ba.GetSize(); i++ )
    {
        switch(ba(i))
        {
            case (TBitValue)0: cout << "0"; break;
            case (TBitValue)1: cout << "1"; break;
            default:           cout << "?"; break;
        }
    }

    cout << "b";
}


void PrintHexStr( BitArray &ba )
{
    TCount      i;
    int         t, r, h[]={ 1, 2, 4, 8 };
    char        ch;

    
    switch(ba.Sign())
    {
        case _POSITIVE: cout << "+"; break;
        case _NEGATIVE: cout << "-"; break;
        default:        cout << "_"; break;
    }

    i=(TCount)0; t=0; r=0; 
    while (i<ba.GetSize())
    {
        r = r + ba(i)*h[t];
        
        if ((i+1)%4==0)
        {
            if (r<10)  { ch='0'+r;  cout << ch; }
            else  { ch='A'+(r-10);  cout << ch; }
            
            r=0;
        }
        
        t=t+1;  if (t==4) t=0;
        i++;
    }

    if (r)
    {
        if (r<10)  { ch='0'+r;  cout << ch; }
        else  { ch='A'+(r-10);  cout << ch; }
    }

    cout << "h";
}

    


/***********************************************************/

#include <stdio.h>


int main( void )
{
    BitArray        A, B;
    TCount          i;


    A.Resize(65);
    for ( i=(TCount)0; i<A.GetSize(); i++ )
        A.SetBit(i,(TCount)1);
    A.Sign()=_NEGATIVE;

    B=A;
    B.Sign()=_POSITIVE;

    cout << "\n\t ";
    for ( i=(TCount)0; i<A.GetSize(); i++ )
        printf("%u",i%10);
    cout << "\n\n";
    
    cout << "BitArray A:\n\t";
    PrintBinStr(A); cout << "\n\t";
    PrintHexStr(A); cout << "\n\n";
    /*cout << "BitArray A:\n\t" << ((A.Sign()==_POSITIVE)?"+":"-");
    for ( i=(TCount)0; i<A.GetSize(); i++ )
        printf("%u",A(i));
    cout << "\n\n";*/

    cout << "BitArray B:\n\t";
    PrintBinStr(B); cout << "\n\t";
    PrintHexStr(B); cout << "\n\n";
    /*cout << "BitArray B:\n\t" << ((B.Sign()==_POSITIVE)?"+":"-");
    for ( i=(TCount)0; i<B.GetSize(); i++ )
        printf("%u",B(i));
    cout << "\n\n";*/
	
	return(0);
}




