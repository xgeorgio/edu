#include "entry.h"

/* A Bison parser, made by GNU Bison 2.4.2.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2006, 2009-2010 Free Software
   Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     TOKTRUE = 301,
     TOKVAR = 302,
     TOKOF = 303,
     TOKNOT = 304,
     TOKOR = 305,
     TOKAND = 306,
     TOKFUNCTION = 307,
     TOKPROCEDURE = 308,
     TOKBOOL = 309,
     TOKINT = 310,
     TOKCHAR = 311,
     TOKARRAY = 312,
     TOKDO = 313,
     TOKWHILE = 314,
     TOKELSE = 315,
     TOKTHEN = 316,
     TOKIF = 317,
     TOKEND = 318,
     TOKBEGIN = 319,
     TOKMOD = 320,
     TOKFALSE = 321,
     IDENTIFIER = 322,
     PLUS = 323,
     MINUS = 324,
     MULTIPLY = 325,
     DIVIDE = 326,
     LES = 327,
     LEQ = 328,
     EQ = 329,
     GT = 330,
     GE = 331,
     NEQ = 332,
     COMMA = 333,
     SEMI = 334,
     OPENPAR = 335,
     CLOSEPAR = 336,
     COLON = 337,
     ASSIGNOP = 338,
     STRINGTOK = 339,
     INTCONST = 340,
     LB = 341,
     RB = 342,
     UMINUS = 344
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1685 of yacc.c  */
#line 51 "parser.y"

    int     i;
    ENTRY   en; 


/* Line 1685 of yacc.c  */
#line 102 "parser.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


