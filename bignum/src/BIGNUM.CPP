#ifndef     __BIGNUM_H
#define     __BIGNUM_H

#include "bitarray.cpp"


class BigNumber : public BitArray
{
    public:
        BigNumber() : BitArray()              {}
        BigNumber( TCount numbits ) : BitArray(numbits)     {}
        BigNumber( BigNumber &bn ) : BitArray(bn)           {}

        // ~BigNumber()

        TCount GetNumBits( void )
            {  return(number.GetSize());  }
        

};



#endif



