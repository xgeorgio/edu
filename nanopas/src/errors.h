#include <stdio.h>
#include "types.h"

#ifndef _ERRORS_H
#define _ERRORS_H

enum semantic_errors_set {
    S_MISMATCH,     /* general type mismatch (general) */
    S_REXPR,        /* relational expresion type mismatch */
    S_EXPR,         /* expresion type mismatch */
    S_EXPINT,       /* integer index in array expected */
    S_ASSIGN,       /* assignment type mismatch */
    S_BOOL,         /* boolean expresion type mismatch */
    S_EXPBOOL,      /* boolean expresion expected */
    NOT_ARRAY       /* variable is not an array */
	 };

extern int  lineno;
int         syntaxErr=0;
int         semErr=0;


void syntax_error( int stxerrno )
{
    static int      errline=0;

    syntaxErr++;
    if (errline != lineno)
    {
        printf("Line %5i: SYNTAX ERROR %3i: ",lineno,stxerrno);
        switch (stxerrno)
        {
            case 0:  printf("Semicolon expected");
                     break;
            case 1:  printf("Error in declaration");
                     break;
            case 2:  printf("Invalid PROCEDURE name");
                     break;
            case 3:  printf("Invalid PROCEDURE declaration");
                     break;
            case 4:  printf("Invalid FUNCTION name");
                     break;
            case 5:  printf("Colon expected in FUNCTION declaration");
                     break;
            case 6:  printf("Unbalanced BEGIN-END");
                     break;
            case 7:  printf("Main BEGIN-END block not found");
                     break;
            case 8:  printf("IF-THEN-ELSE without THEN");
                     break;
            case 9:  printf("IF-THEN without THEN");
                     break;
            case 10: printf("WHILE without DO");
                     break;
            case 11: printf("Invalid assignment command");
                     break;
            case 12: printf("OF expected in ARRAY declaration");
                     break;
            case 13: printf("Invalid ARRAY declaration");
                     break;
            case 14: printf("Brackets not found in ARRAY declaration");
                     break;
            case 15: printf("Expected INTEGER constant in ARRAY index");
                     break;
            case 16: printf("Unbalanced parenthesis");
                     break;
            case 17: printf("Brackets not found in ARRAY parameter");
                     break;
            case 18: printf("Unbalanced parenthesis in SUBROUTINE");
                     break;
            case 19: printf("Invalid parameter list");
                     break;
            case 20: printf("Internal: Missing semi at var_decl");
                     break;
            case 21: printf("Missing COMMA at variable list");
                     break;
            case 22: printf("Internal: Missing COLON at var decl");
                     break;
            case 23: printf("Brackets not found in ARRAY expression");
                     break;
            case 24: printf("Invalid data type");
                     break;
            case 25: printf("Invalid data type in declaration");
                     break;
            case 26: printf("Constant expected");
                     break;
            case 27: printf("Error in statement");
                     break;
            default: printf("Unknown syntax error");
                     break;
        }

        printf("\n");
        errline=lineno;
    }
}


void semantic_error( int serror )
{
    static int errline=0;

    semErr++;
    printf("Line %5i: ERROR %3i: ",lineno,serror);
    switch(serror)
    {
        case S_MISMATCH: printf("Type mismatch");
                         break;
        case S_ASSIGN  : printf("Type mismatch in assignment");
                         break;
        case S_EXPR    : printf("Type mismatch in expresion");
                         break;
        case S_REXPR   : printf("Type mismatch in relational expresion");
                         break;
        case S_BOOL    : printf("Types mismatch in boolean expresion");
                         break;
        case S_EXPBOOL : printf("Boolean expresion expected");
                         break;
        default        : printf("Unknown semantic error");
                         break;
    }

    printf("\n");
    errline=lineno;
}


void undef_error( char *varname )
{
    semErr++;
    printf("Line %5i: ERROR 30: Undefined variable '%s'\n",lineno,varname);
}



void arrcls_error( int cls_error, char *varname )
{
    semErr++;
    printf("Line %4i: ERROR %3i: ",lineno,cls_error);
    switch(cls_error)
    {
        case NOT_ARRAY: printf("Variable '%s' is not an ARRAY",varname);
                        break;
        case S_EXPINT : printf("INTEGER index expected in ARRAY '%s'",varname);
                        break;
        default       : printf("Unknown definition class in expresion");
                        break;
    }

    printf("\n");
}


#endif



