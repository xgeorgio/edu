
%{
#include <stdio.h>
#include <string.h> 
#include <stdlib.h>
#include "parser.tab.h"
#include "scanner.h"
%}

 int lineno=1;
 int lexerr=0;
 int cEND=0;
 int cBEGIN=0;


DIGIT [0-9]

ID [a-zA-Z]([a-zA-Z0-9])*(_([a-zA-Z0-9])+)*

%%

{DIGIT}+                { yylval.i = atoi(yytext);
                          return(INTCONST); }

"'"(''|[^'\n])*"'"      { clean_yytext(yytext);
                          return (return_token(STRINGTOK,yytext)); }

"'"(''|[^'\n])*[\r\n]   { int len=strlen(yytext); 
                          yytext[len-1]='\0';
                          printf("Line %5i: LEXICAL ERROR: Unexpected <EOL>, string '%s' not terminated\n",lineno,yytext);
                          lexerr++; } 

{ID}                    { int inum;
                          inum=find_symbol(yytext);    
                          if (inum != -1) 
                              return( return_token(inum,yytext) ); 
                          else  
                              return( return_token(IDENTIFIER,yytext) ); }
 
"+"                     { return( return_token(PLUS,yytext) ); }
"-"                     { return( return_token(MINUS,yytext) ); }
"*"                     { return( return_token(MULTIPLY,yytext) ); }
"/"                     { return( return_token(DIVIDE,yytext) ); }
"<>"                    { return( return_token(NEQ,yytext) ); }
"<="                    { return( return_token(LEQ,yytext) ); }
"<"                     { return( return_token(LES,yytext) ); }
">="                    { return( return_token(GE,yytext) ); }
">"                     { return( return_token(GT,yytext) ); }
":="                    { return( return_token(ASSIGNOP,yytext) ); }
":"                     { return( return_token(COLON,yytext) ); }
"="                     { return( return_token(EQ,yytext) ); }
","                     { return( return_token(COMMA,yytext) ); }
";"                     { return( return_token(SEMI,yytext) ); }
"("                     { return( return_token(OPENPAR,yytext) ); }
")"                     { return( return_token(CLOSEPAR,yytext) ); }
"["                     { return( return_token(LB,yytext) ); }
"]"                     { return( return_token(RB,yytext) ); }
"(*"                    { register int c;
                          for(;;)
                          {
                              while( (c=input())!='*' && c!=EOF )
                                  if(c=='\n') lineno++;
                              if (c=='*')
                              {
                                  while((c=input())=='*');
                                  if ( c==')' )  break;
                              }
                              if (c==EOF)  
                              {
                                  printf("line %5i: LEXICAL ERROR:  Unexpected <EOF>, comment not terminated\n",lineno);
                                  lexerr++;
                                  break;
                              }
                          }
                        }

[ \t]                   {  /* do nothing */  }

\n                      { lineno++; }

.                       { lexerr++;
                          printf("line %5i: LEXICAL ERROR: Token '%s' not recognized\n",lineno,yytext); }

%%

yywrap()                {  /* dummy procedure */  }




