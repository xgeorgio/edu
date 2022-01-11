/*
---------------------------------------------------------------------------
    FILE:           'resampl1.c'
    PURPOSE:        Provide 1-pass fixed-rate linear resampling
    VERSION:        1.0

    AUTHOR:         Harris Georgiou (MSc,PhD) - IS/IT Engineer (R&D)
    COPYRIGHT:      Data Science Lab @ UniPi (c) 2017 - http://datastories.org

---------------------------------------------------------------------------
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#ifndef     FALSE
#define     FALSE       0
#define     TRUE        !FALSE
#endif

#define     EXIT_OK         0
#define     EXIT_NARGS      1
#define     EXIT_FILES      2
#define     EXIT_OPTIONS    3
#define     EXIT_PARSE      4

#define     buffsz          1023
#define     ncolmax         100

typedef struct {
    char    inpfname[buffsz], outfname[buffsz];
    FILE    *inpf, *outf;
    
    int     colX, colD[ncolmax], colDsz;
    char    grcsv;
    
    double  newrate, x0, x1, x, y0, y1, y;
}  TParams;


void version_info( void )
{
    printf("CSV importer/resampler v0.1a - Harris Georgiou (c) 2016, CC-BY-SA 4.0\n\n");
}

void usage( void )
{
    printf("Usage:  resampl1 <inpfile.csv> <outfile.csv> [options]\n\n");
}

void error_exit( int errcode )
{
    switch(errcode)
    {
        case EXIT_NARGS:
            printf("Error: Invalid number of arguments.\n");
            break;
        case EXIT_FILES:
            printf("Error: Invalid file name(s).\n");
            break;
        case EXIT_OPTIONS:
            printf("Error: Invalid configuration options.\n");
            break;
        case EXIT_PARSE:
            printf("Error: Invalid input, parsing aborted.\n");
            break;
        default:
            printf("Process completed successfully.\n");
    }
    
    exit(errcode);
}

TParams *update_params( TParams *par, char *strarg )
{
    char    ctag, *cval;
    int     clen;
    
    printf("cmdarg: %s\n",strarg);
    
    clen=strlen(strarg);
    if (clen>=2)
    {
        if ( (strarg[0]=='/')||(strarg[0]=='-') )
        {
            ctag=toupper(strarg[1]);
            if (clen>2)
            {  
                cval=&(strarg[2]);
            }
            else
            {
                cval=NULL;
            }
            
            switch(ctag)
            {
                case 'A':
                    printf("option:A\n");
                    break;
                case 'B':
                    printf("option:B, value:%s\n",cval);
                    break;
                default:
                    error_exit(EXIT_OPTIONS);
            }            
        }
    }
    
    return(par);
}


int main( int argc, char **argv, char **env )
{
    TParams     params;
    int         k;
    
    version_info();
    if (argc<3)
    {
        usage();
        error_exit(EXIT_NARGS);
    }
    
    strncpy(params.inpfname,argv[1],buffsz);
    strncpy(params.outfname,argv[2],buffsz);
    
    for ( k=3; k<argc; k++ )
    {
        update_params(&params,argv[k]);
    }    
    
    return(0);
}
