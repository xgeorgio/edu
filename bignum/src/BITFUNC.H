#ifndef     _BIT_FUNC_H
#define     _BIT_FUNC_H


#define     bitNOT(a)           ((a)?0:1)
#define     bitOR(a,b)          ((a||b)?1:0)
#define     bitAND(a,b)         ((a&&b)?1:0)
#define     bitXOR(a,b)         ((((a)&&(!b))||((!a)&&(b)))?1:0)

#define     bitHALF_ADD_S(a,b)      ( ((a)&&(!b))||((!a)&&(b)) )
#define     bitHALF_ADD_C(a,b)      ( (a)&&(b) )

#define     bitFULL_ADD_S(a,b,c)    ( ((!a)&&(!b)&&(c))||((!a)&&(b)&&(!c))||((a)&&(!b)&&(!c))||((a)&&(b)&&(c)) )
#define     bitFULL_ADD_C(a,b,c)    ( ((a)&&(b))||((a)&&(c))||((b)&&(c)) )


#endif


