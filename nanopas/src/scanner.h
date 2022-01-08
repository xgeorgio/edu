
#include <stdio.h>
#include <ctype.h>

#define         MAX_TOKNUM            21


extern YYSTYPE  yylval;

char    *reserved_words[MAX_TOKNUM] =
            {   "true", "var", "of", "not",
                "or", "and", "function", "procedure",
                "bool", "int", "char", "array",
                "do", "while", "else", "then",
                "if", "end", "begin", "mod", "false"    }; 

int     tokens[MAX_TOKNUM] =
            {   TOKTRUE, TOKVAR, TOKOF, TOKNOT,
                TOKOR, TOKAND, TOKFUNCTION, TOKPROCEDURE,
                TOKBOOL, TOKINT, TOKCHAR, TOKARRAY,
                TOKDO, TOKWHILE, TOKELSE, TOKTHEN,
                TOKIF, TOKEND, TOKBEGIN, TOKMOD, TOKFALSE   }; 



int return_token( int tokname, char *toktext )
{
    strcpy(yylval.en.name,toktext);
    return(tokname);
}

 
int find_symbol( char *yytext )
{
    int     len;
    int     i, num;


    len=strlen(yytext);
    for ( i=0; i<len; i++ )
        yytext[i] = tolower(yytext[i]);
       
    for ( num=0; num<MAX_TOKNUM; num++ )
    {
        if ( strcmp(yytext,reserved_words[num])==0 )
            return( tokens[num] );
    }

    return(-1);
}

 
void clean_yytext( char *str )
{
    int     i, count;
    int     flag=0;
    int     len, m;


    len = strlen(str);
    for ( i=0,count=0; count<len-1,i<len-1; count++ )
    {
        if ((str[i]=='\'') && (str[i+1]=='\'') && (flag==0))
        {
            flag=1;
            for ( m=i; m<len; m++ )  str[m]=str[m+1];
            len--;
        }
        else
        {
            flag=0;
            str[i] = str[i+1];
            i++;
        }
    }

    str[len-2]='\0';
}


