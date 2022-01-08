#ifndef     _BIT_ARRAY_H
#define     _BIT_ARRAY_H

#include "basearrs.cpp"
#include <values.h>
#include <limits.h>


typedef     unsigned char       TBitValue;
#define     BITVALUE_MAX        (TBitValue)UCHAR_MAX

typedef     unsigned char       TBitBlock;
#define     BITBLOCK_MAX        (TBitBlock)UCHAR_MAX

typedef     unsigned long       TCount;

#define     _BITBLOCKSIZE       (TCount)(sizeof(TBitBlock)*BITSPERBYTE)

#define     _NEGATIVE           (TBitValue)1
#define     _POSITIVE           (TBitValue)0


#endif



