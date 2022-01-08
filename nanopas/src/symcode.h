#include <stdio.h>

#include "types.h"
#include "errors.h"

#ifndef _SYMCODE_H
#define _SYMCODE_H

#define         MAX_OP          20
#define         MAX_QUAD        2048

typedef struct QUAD {
      char op[MAX_OP];
      char arg1[MAX_NAME];
      char arg2[MAX_NAME];
      char arg3[MAX_NAME];  
    } QUAD;


extern  syntaxErr;
extern  semErr;
extern  lexerr;

int     buff=1;
int     nextQUAD=0;
QUAD    quads[MAX_QUAD];


/***  Print a generated quad  ***/
void printQUAD( FILE *outfile, int quadno )
{
    fprintf( outfile, "%-5d:\t( %13s , %13s , %13s , %13s )\n",
        quadno, quads[quadno].op, quads[quadno].arg1,
        quads[quadno].arg2, quads[quadno].arg3 );
}


/***  Generate quad from arguments  ***/
void genQUAD( char *op, char *arg1, char *arg2, char *arg3 )
{
    if ( (!syntaxErr) && (!semErr) && (!lexerr) )
	{
        strcpy( quads[nextQUAD].op, op );
        strcpy( quads[nextQUAD].arg1, arg1 );
        strcpy( quads[nextQUAD].arg2, arg2 );
        strcpy( quads[nextQUAD].arg3, arg3 );
        nextQUAD++;
	}
}


/***  Print all generated quads (formated output)  ***/
void printCODE( char *outfilename )
{
    int     count;
    FILE    *outfile;


    if (!syntaxErr && !semErr && !lexerr)
	{
        if ( (outfile=fopen(outfilename,"w+t"))==NULL )
            printf("Fatal Error: Cannot write to output file (%s)\n",outfilename);
        else
        {
            for ( count=0; count<nextQUAD; count++)
                printQUAD( outfile, count );
            /*printf("\nObject code written to output file (%s)\n",outfilename);*/
        }
    }
    else
        printf("\nFatal Error: Errors found, no output written to intermediate file\n");
}


#endif
