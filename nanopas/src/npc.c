#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "npcshell.h"

#define         MAX_CMDLINE         128
#define         DEF_CMDSTR          "nano.bin <"


void usage( void )
{
    printf("Usage:   NPC  <sourcefile>  [<objectfile>]\n\n");
    printf("    <sourcefile> = Text file with nano-pascal source code\n");
    printf("    <objectfile> = Generated symbolic code output file (quad form)\n\n");
    printf("  Example:\n");
    printf("            npc  hello.np  hello.obj\n\n");
}



int main( int argc, char **argv )
{
    char        cmdstr[MAX_CMDLINE];
    char        infname[MAX_CMDLINE], outfname[MAX_CMDLINE];
    int         outgiven, exitval;


    printf("Nano-Pascal Compiler, version 1.9 (Beta) - Harris Georgiou, 1996\n\n");

    strcpy(cmdstr,DEF_CMDSTR);
    if ( (argc<2)||(argc>3) )
    {
        printf("Fatal Error: Invalid number of command-line parameters\n\n");
        usage();
        return(1);
    }
    else if (argc==2)
    {
        strcpy( infname, argv[1] );
        strcpy( outfname, DEF_OUTFILENAME );
        outgiven = 0;
    }
    else if (argc==3)
    {
        strcpy( infname, argv[1] );
        strcpy( outfname, argv[2] );
        outgiven = 1;
    }

    if ( (infname[0]=='-') && ((infname[1]=='?')||(infname[1]=='h')||(infname[1]=='H')) )
    {
        usage();
        return(0);
    }
    else
    {
        strcpy( cmdstr, DEF_CMDSTR );
        strcat( cmdstr, infname );
        /*printf("Executing comand: %s\n",cmdstr);*/
        exitval = system( cmdstr );
        if (exitval)
        {
            printf("\nFile contains errors, no output written to object file (%s)\n\n",outfname);
            return(1);
        }
        else
        {
            if (outgiven)
            {
                if ( rename(DEF_OUTFILENAME,outfname) )
                {
                    printf("\nFatal Error: Cannot write to output file (%s)\n",outfname);
                    return(2);
                }
                else
                    remove(DEF_OUTFILENAME);
            }

            printf("Object code written to output file (%s)\n\n",outfname);
            return(0);
         }
    }
}

