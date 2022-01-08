#include <stdio.h>
#include "bitfunc.h"

int main( void )
{
    int       A, B, C;


    /*************************/
    printf("  A   B  |  not.A  |  A.or.B  |  A.and.B  |  A.xor.B  \n");
    printf("------------------------------------------------------\n");
    
    A=0; B=0;
    printf("  %d   %d  |    %d    |    %d     |     %d     |     %d     \n",
        A, B, bitNOT(A), bitOR(A,B), bitAND(A,B), bitXOR(A,B) );

    A=0; B=1;
    printf("  %d   %d  |    %d    |    %d     |     %d     |     %d     \n",
        A, B, bitNOT(A), bitOR(A,B), bitAND(A,B), bitXOR(A,B) );

    A=1; B=0;
    printf("  %d   %d  |    %d    |    %d     |     %d     |     %d     \n",
        A, B, bitNOT(A), bitOR(A,B), bitAND(A,B), bitXOR(A,B) );

    A=1; B=1;
    printf("  %d   %d  |    %d    |    %d     |     %d     |     %d     \n",
        A, B, bitNOT(A), bitOR(A,B), bitAND(A,B), bitXOR(A,B) );

    printf("\n");


    /*************************/
    printf("  A   B  |  Hadd_S(A,B)  |  Hadd_C(A,B)  \n");
    printf("-----------------------------------------\n");
    
    A=0; B=0;
    printf("  %d   %d  |       %d       |       %d       \n",
        A, B, bitHALF_ADD_S(A,B), bitHALF_ADD_C(A,B) );

    A=0; B=1;
    printf("  %d   %d  |       %d       |       %d       \n",
        A, B, bitHALF_ADD_S(A,B), bitHALF_ADD_C(A,B) );

    A=1; B=0;
    printf("  %d   %d  |       %d       |       %d       \n",
        A, B, bitHALF_ADD_S(A,B), bitHALF_ADD_C(A,B) );

    A=1; B=1;
    printf("  %d   %d  |       %d       |       %d       \n",
        A, B, bitHALF_ADD_S(A,B), bitHALF_ADD_C(A,B) );

    printf("\n");


    /*************************/
    printf("  A   B   C  | Fadd_S(A,B,C) | Fadd_C(A,B,C) \n");
    printf("---------------------------------------------\n");
    
    A=0; B=0; C=0;
    printf("  %d   %d   %d  |       %d       |       %d       \n",
        A, B, C, bitFULL_ADD_S(A,B,C), bitFULL_ADD_C(A,B,C) );

    A=0; B=1; C=0;
    printf("  %d   %d   %d  |       %d       |       %d       \n",
        A, B, C, bitFULL_ADD_S(A,B,C), bitFULL_ADD_C(A,B,C) );

    A=1; B=0; C=0;
    printf("  %d   %d   %d  |       %d       |       %d       \n",
        A, B, C, bitFULL_ADD_S(A,B,C), bitFULL_ADD_C(A,B,C) );

    A=1; B=1; C=0;
    printf("  %d   %d   %d  |       %d       |       %d       \n",
        A, B, C, bitFULL_ADD_S(A,B,C), bitFULL_ADD_C(A,B,C) );

    A=0; B=0; C=1;
    printf("  %d   %d   %d  |       %d       |       %d       \n",
        A, B, C, bitFULL_ADD_S(A,B,C), bitFULL_ADD_C(A,B,C) );

    A=0; B=1; C=1;
    printf("  %d   %d   %d  |       %d       |       %d       \n",
        A, B, C, bitFULL_ADD_S(A,B,C), bitFULL_ADD_C(A,B,C) );

    A=1; B=0; C=1;
    printf("  %d   %d   %d  |       %d       |       %d       \n",
        A, B, C, bitFULL_ADD_S(A,B,C), bitFULL_ADD_C(A,B,C) );

    A=1; B=1; C=1;
    printf("  %d   %d   %d  |       %d       |       %d       \n",
        A, B, C, bitFULL_ADD_S(A,B,C), bitFULL_ADD_C(A,B,C) );

    printf("\n");
	return(0);
}



