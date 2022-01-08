/* A Bison parser, made by GNU Bison 2.4.2.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.4.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 1 "parser.y"

#include <stdio.h>
#include <string.h>
#include "types.h"
#include "errors.h"
#include "hashtab.h"
#include "symcode.h"

#define     isTYPEsame(x,y)         (x.type ==y.type &&  x.type  && y.type)
#define     isCLASSsame(x,y)        (x.class==y.class && x.class  && y.class)
#define     isASIZEsame(x,y)        (x.asize==y.asize)
#define     isTYPECLASSsame(x,y)    (x.type==y.type && x.class==y.class)
#define     IsErrorFree             (!syntaxErr && !semErr && !lexerr)


extern      buff;
extern      lineno;
extern      lexerr;
extern      syntaxErr;
extern      semErr;
extern      nextQUAD;

int         dcount=0;
HASH_TAB    *symtab;
char        vlist[20][MAX_NAME];
char        tempREXPR[MAX_NAME];


void HashToTable( char *name, int type, int class, int asize )
{
    int     exists;

    exists=insert_to_table(symtab,name,type,class,asize);
    if(exists)
    {
        printf("Line %5i: SYNTAX ERROR: Variable '%s' is redefined here as ",lineno,name);
        switch(type)
        {
            case INTEGER:   printf("INTEGER");  break;
            case CHAR:      printf("CHARACTER");  break;
            case BOOLEAN:   printf("BOOLEAN");  break;
            default:        printf("??? (unknown type)");  break;
        }
        printf("\n");
    }
}




/* Line 189 of yacc.c  */
#line 123 "parser.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


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

/* Line 214 of yacc.c  */
#line 51 "parser.y"

    int     i;
    ENTRY   en; 


/* Line 214 of yacc.c  */
#line 210 "parser.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 222 "parser.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   338

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  46
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  42
/* YYNRULES -- Number of rules.  */
#define YYNRULES  121
/* YYNRULES -- Number of states.  */
#define YYNSTATES  219

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   344

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,     2,    45
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     8,     9,    15,    21,    22,    29,    34,
      38,    42,    45,    51,    53,    55,    57,    59,    61,    64,
      67,    70,    73,    76,    80,    84,    86,    90,    93,    97,
      99,   103,   106,   109,   111,   113,   115,   117,   122,   126,
     127,   128,   136,   141,   147,   151,   152,   155,   156,   157,
     164,   165,   171,   172,   177,   182,   188,   192,   196,   199,
     203,   205,   207,   209,   211,   213,   215,   217,   224,   225,
     233,   234,   242,   243,   250,   257,   263,   264,   272,   273,
     280,   281,   287,   291,   293,   298,   302,   306,   308,   310,
     314,   318,   322,   326,   330,   334,   338,   343,   346,   349,
     353,   358,   362,   368,   374,   376,   378,   380,   382,   386,
     388,   390,   392,   394,   396,   398,   401,   405,   410,   412,
     415,   419
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      47,     0,    -1,    10,    24,    55,    58,    -1,    -1,    10,
       1,    48,    55,    58,    -1,    10,    24,    86,    55,    58,
      -1,    -1,    10,     1,    86,    50,    55,    58,    -1,    10,
      24,    86,    36,    -1,    10,     1,    36,    -1,    54,    55,
      58,    -1,    54,    36,    -1,     9,    24,    86,    39,    73,
      -1,    49,    -1,    52,    -1,    51,    -1,    53,    -1,    70,
      -1,    55,    49,    -1,    55,    52,    -1,    55,    51,    -1,
      55,    53,    -1,    55,    70,    -1,    81,    40,    82,    -1,
      81,     1,    82,    -1,    82,    -1,    57,    35,    82,    -1,
      21,    20,    -1,    21,    59,    20,    -1,    60,    -1,    59,
      36,    60,    -1,    59,    60,    -1,     1,    36,    -1,    58,
      -1,    56,    -1,    61,    -1,    65,    -1,    24,    37,    57,
      38,    -1,    24,    37,    38,    -1,    -1,    -1,    19,    84,
      62,    18,    60,    63,    64,    -1,    19,    84,    17,    60,
      -1,    19,    84,    60,    17,    60,    -1,    19,     1,    36,
      -1,    -1,    17,    60,    -1,    -1,    -1,    16,    66,    84,
      15,    67,    60,    -1,    -1,    16,    68,    84,     1,    60,
      -1,    -1,    16,    69,    84,    60,    -1,    24,    39,    72,
      36,    -1,    24,    71,    39,    72,    36,    -1,    24,    39,
      72,    -1,    24,    71,    72,    -1,    35,    24,    -1,    71,
      35,    24,    -1,    24,    -1,    73,    -1,    74,    -1,    13,
      -1,    12,    -1,    11,    -1,     1,    -1,    14,    43,    42,
      44,     5,    73,    -1,    -1,    14,     1,    42,    75,    44,
       5,    73,    -1,    -1,    14,    43,    42,     1,     5,    76,
      73,    -1,    -1,    14,     1,    42,    77,     5,    73,    -1,
      14,    43,    42,    44,     1,    73,    -1,    14,     1,    42,
       1,    73,    -1,    -1,    14,    43,     1,    44,    78,     5,
      73,    -1,    -1,    14,     1,    44,    79,     5,    73,    -1,
      -1,    14,     1,     5,    80,    73,    -1,    14,     1,    73,
      -1,    24,    -1,    24,    43,    82,    44,    -1,    24,    43,
      82,    -1,    24,    82,    44,    -1,    83,    -1,    24,    -1,
      82,    27,    82,    -1,    82,    28,    82,    -1,    82,    25,
      82,    -1,    82,    26,    82,    -1,    82,    22,    82,    -1,
      82,     8,    82,    -1,    82,     7,    82,    -1,    24,    43,
      82,    44,    -1,     6,    82,    -1,    26,    82,    -1,    37,
      82,    38,    -1,    24,    37,    57,    38,    -1,    37,    82,
      36,    -1,    24,    43,    82,     1,    36,    -1,    24,    37,
      57,     1,    36,    -1,    42,    -1,    41,    -1,     3,    -1,
      23,    -1,    82,    85,    82,    -1,    29,    -1,    30,    -1,
      31,    -1,    32,    -1,    33,    -1,    34,    -1,    37,    38,
      -1,    37,    87,    38,    -1,    37,    87,     1,    36,    -1,
      70,    -1,     4,    70,    -1,    87,     4,    70,    -1,    87,
      70,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   132,   132,   135,   135,   141,   144,   144,   150,   151,
     155,   159,   163,   167,   168,   169,   170,   171,   172,   173,
     174,   175,   176,   180,   204,   218,   219,   223,   224,   228,
     229,   230,   231,   235,   236,   237,   238,   239,   240,   245,
     252,   244,   263,   264,   265,   269,   270,   274,   276,   274,
     289,   289,   290,   290,   294,   296,   309,   310,   314,   316,
     318,   324,   327,   334,   335,   336,   337,   341,   343,   343,
     344,   344,   345,   345,   346,   347,   348,   348,   349,   349,
     350,   350,   351,   355,   379,   400,   401,   405,   419,   443,
     457,   471,   485,   499,   513,   527,   541,   561,   573,   586,
     587,   588,   589,   590,   594,   600,   605,   610,   618,   637,
     638,   639,   640,   641,   642,   646,   647,   648,   651,   652,
     653,   654
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TOKTRUE", "TOKVAR", "TOKOF", "TOKNOT",
  "TOKOR", "TOKAND", "TOKFUNCTION", "TOKPROCEDURE", "TOKBOOL", "TOKINT",
  "TOKCHAR", "TOKARRAY", "TOKDO", "TOKWHILE", "TOKELSE", "TOKTHEN",
  "TOKIF", "TOKEND", "TOKBEGIN", "TOKMOD", "TOKFALSE", "IDENTIFIER",
  "PLUS", "MINUS", "MULTIPLY", "DIVIDE", "LES", "LEQ", "EQ", "GT", "GE",
  "NEQ", "COMMA", "SEMI", "OPENPAR", "CLOSEPAR", "COLON", "ASSIGNOP",
  "STRINGTOK", "INTCONST", "LB", "RB", "UMINUS", "$accept", "program",
  "$@1", "procedure", "$@2", "forward_procedure", "function",
  "forward_function", "fun_declare", "declaration", "assgmnt_stmt",
  "actual_par_list", "compound_stmt", "stmt_block", "stmt", "if_stmt",
  "$@3", "$@4", "tail", "while_stmt", "$@5", "$@6", "$@7", "$@8",
  "var_decl", "var_list", "type", "simple_type", "array_declare", "$@9",
  "$@10", "$@11", "$@12", "$@13", "$@14", "leftexpr", "r_expr", "constant",
  "boolexpr", "rel_op", "formal_par_list", "formal_rec", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   343,   301,   302,   303,   304,   305,   306,   307,
     308,   309,   310,   311,   312,   313,   314,   315,   316,   317,
     318,   319,   320,   321,   322,   323,   324,   325,   326,   327,
     328,   329,   330,   331,   332,   333,   334,   335,   336,   337,
     338,   339,   340,   341,   342,   344
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    46,    47,    48,    47,    49,    50,    49,    51,    51,
      52,    53,    54,    55,    55,    55,    55,    55,    55,    55,
      55,    55,    55,    56,    56,    57,    57,    58,    58,    59,
      59,    59,    59,    60,    60,    60,    60,    60,    60,    62,
      63,    61,    61,    61,    61,    64,    64,    66,    67,    65,
      68,    65,    69,    65,    70,    70,    70,    70,    71,    71,
      71,    72,    72,    73,    73,    73,    73,    74,    75,    74,
      76,    74,    77,    74,    74,    74,    78,    74,    79,    74,
      80,    74,    74,    81,    81,    81,    81,    82,    82,    82,
      82,    82,    82,    82,    82,    82,    82,    82,    82,    82,
      82,    82,    82,    82,    83,    83,    83,    83,    84,    85,
      85,    85,    85,    85,    85,    86,    86,    86,    87,    87,
      87,    87
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     4,     0,     5,     5,     0,     6,     4,     3,
       3,     2,     5,     1,     1,     1,     1,     1,     2,     2,
       2,     2,     2,     3,     3,     1,     3,     2,     3,     1,
       3,     2,     2,     1,     1,     1,     1,     4,     3,     0,
       0,     7,     4,     5,     3,     0,     2,     0,     0,     6,
       0,     5,     0,     4,     4,     5,     3,     3,     2,     3,
       1,     1,     1,     1,     1,     1,     1,     6,     0,     7,
       0,     7,     0,     6,     6,     5,     0,     7,     0,     6,
       0,     5,     3,     1,     4,     3,     3,     1,     1,     3,
       3,     3,     3,     3,     3,     3,     4,     2,     2,     3,
       4,     3,     5,     5,     1,     1,     1,     1,     3,     1,
       1,     1,     1,     1,     1,     2,     3,     4,     1,     2,
       3,     2
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     3,     0,     1,     0,     0,     0,     0,
      13,    15,    14,    16,     0,     0,    17,     0,     0,     0,
       0,    60,     0,     0,     0,    11,     0,     0,    18,    20,
      19,    21,     2,    22,     4,     0,     0,     9,     6,     0,
      58,    66,    65,    64,    63,     0,    56,    61,    62,     0,
       0,    57,    10,     0,    47,     0,    27,    83,    34,    33,
       0,    29,    35,    36,     0,     0,   115,   118,     0,     0,
       0,     8,     0,     0,     0,    54,    59,     0,    32,     0,
       0,     0,     0,   106,     0,   107,    88,     0,     0,   105,
     104,     0,    87,    39,     0,     0,     0,    28,     0,    31,
       0,     0,   119,     0,     0,   116,   121,    12,     0,     5,
      80,     0,    78,    82,     0,     0,    55,     0,     0,     0,
      44,    97,     0,     0,    98,     0,     0,     0,     0,     0,
       0,     0,     0,   109,   110,   111,   112,   113,   114,     0,
       0,     0,     0,    38,     0,    25,    85,    86,    30,    24,
      23,   117,   120,     7,     0,     0,     0,     0,     0,    76,
       0,     0,    48,     0,    53,     0,    25,     0,   101,    99,
      95,    94,    93,    91,    92,    89,    90,   108,    42,     0,
       0,     0,    37,    84,    81,    75,     0,     0,     0,     0,
      70,     0,     0,     0,    51,     0,   100,     0,    96,    43,
      40,    26,     0,    73,    79,     0,     0,    74,    67,    49,
     103,   102,    45,    69,    77,    71,     0,    41,    46
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     6,    10,    70,    11,    12,    13,    14,    15,
      58,   144,    59,    60,    61,    62,   142,   212,   217,    63,
      79,   193,    80,    81,    16,    24,    46,    47,    48,   156,
     206,   157,   189,   158,   154,    64,    91,    92,    93,   139,
      36,    68
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -67
static const yytype_int16 yypact[] =
{
      13,    12,    32,   -67,    89,   -67,    89,    16,    20,    57,
     -67,   -67,   -67,   -67,    58,   150,   -67,   150,    46,   139,
      46,   -67,    61,   222,   206,   -67,   150,   253,   -67,   -67,
     -67,   -67,   -67,   -67,   -67,   127,    56,   -67,   -67,    81,
     -67,   -67,   -67,   -67,   -67,    21,    78,   -67,   -67,    92,
     222,   -67,   -67,    88,   -67,   131,   -67,   155,   -67,   -67,
     302,   -67,   -67,   -67,    17,   103,   -67,   -67,   114,   215,
      89,   -67,   150,    99,     4,   -67,   -67,   110,   -67,   188,
     188,   188,   117,   -67,   188,   -67,   -13,   188,   188,   -67,
     -67,   276,   -67,   270,   164,   188,   224,   -67,   161,   -67,
     188,   188,   -67,   133,   103,   -67,   -67,   -67,   150,   -67,
     -67,     1,   -67,   -67,    91,    11,   -67,   168,   183,   161,
     -67,   -67,   188,   188,   -67,   254,   188,   188,   188,   188,
     188,   188,   188,   -67,   -67,   -67,   -67,   -67,   -67,   188,
     161,   169,   175,   -67,    18,   254,   231,   -67,   -67,   289,
     289,   -67,   -67,   -67,   215,   215,   151,   199,   205,   -67,
     208,    38,   -67,   161,   -67,    49,   289,   122,   -67,   -67,
     181,   -67,   -67,   181,   181,   -67,   -67,   289,   -67,   161,
     161,   188,   -67,   -67,   -67,   -67,   210,   215,   215,   216,
     -67,   215,   215,   161,   -67,   186,   -67,   201,   -67,   -67,
     -67,   289,   215,   -67,   -67,   215,   215,   -67,   -67,   -67,
     -67,   -67,   207,   -67,   -67,   -67,   161,   -67,   -67
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -67,   -67,   -67,    -6,   -67,    -1,     0,    34,   -67,    23,
     -67,   118,    37,   -67,   -60,   -67,   -67,   -67,   -67,   -67,
     -67,   -67,   -67,   -67,    -7,   -67,   -23,   -66,   -67,   -67,
     -67,   -67,   -67,   -67,   -67,   -67,   -53,   -67,    83,   -67,
     180,   -67
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -73
static const yytype_int16 yytable[] =
{
      99,    51,   155,   107,    96,   114,   -72,   113,    33,    28,
      33,    28,   160,     3,    29,    30,    29,    30,   100,    33,
      28,    19,    73,     1,   122,    29,    30,    77,    67,    17,
     123,   121,     5,   141,   124,   125,     4,    26,   148,   191,
      18,   145,   146,   192,    20,   -68,   115,   149,   150,    31,
     195,    31,    32,   181,    34,   161,   182,   101,   102,   164,
      31,   106,    72,    52,    74,    33,    28,     7,     8,   166,
     167,    29,    30,   170,   171,   172,   173,   174,   175,   176,
     178,    21,     9,    35,   181,    40,   177,   196,   184,   185,
       7,     8,    22,   108,    25,    69,    23,   152,     7,     8,
      41,    33,    28,   194,   110,     9,    31,    29,    30,   109,
      42,    43,    44,     9,    75,   103,    76,    71,   104,   199,
     200,   203,   204,   197,    78,   207,   208,     9,   201,   126,
     127,    65,    82,   209,    83,   159,   213,    84,     9,   214,
     215,   111,    31,   112,   128,   153,   116,   129,   130,   131,
     132,     9,   105,   120,    85,    86,   218,    87,    83,     7,
       8,    84,   117,   118,   119,    66,   198,    83,    88,   151,
      84,    27,    89,    90,     9,    37,    35,    54,    85,    86,
      55,    87,    27,   162,   163,    57,   179,    85,    86,   127,
      87,    83,    94,   180,    84,   186,    89,    90,    95,    38,
      39,    88,   143,   128,   187,    89,    90,    41,   131,   132,
     188,    85,    86,   190,    87,   202,    41,    42,    43,    44,
      45,   205,   210,    41,   216,    88,    42,    43,    44,    89,
      90,   126,   127,    42,    43,    44,    45,   211,   126,   127,
     165,    49,     0,     0,     0,    50,   128,     0,     0,   129,
     130,   131,   132,   128,    53,     0,   129,   130,   131,   132,
       0,   126,   127,     0,     0,     0,     0,     0,   147,    54,
       0,     0,    55,    56,    27,   183,   128,    57,     0,   129,
     130,   131,   132,   126,   127,     0,    54,   140,     0,    55,
     168,    27,   169,     0,    57,     0,   126,   127,   128,     0,
       0,   129,   130,   131,   132,   133,   134,   135,   136,   137,
     138,   128,     0,     0,   129,   130,   131,   132,    54,     0,
       0,    55,    97,    27,     0,     0,    57,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    98
};

static const yytype_int16 yycheck[] =
{
      60,    24,     1,    69,    57,     1,     5,    73,    15,    15,
      17,    17,     1,     1,    15,    15,    17,    17,     1,    26,
      26,     1,     1,    10,    37,    26,    26,    50,    35,     6,
      43,    84,     0,    93,    87,    88,    24,    14,    98,     1,
      24,    94,    95,     5,    24,    44,    42,   100,   101,    15,
       1,    17,    15,    35,    17,    44,    38,    40,    65,   119,
      26,    68,    39,    26,    43,    72,    72,     9,    10,   122,
     123,    72,    72,   126,   127,   128,   129,   130,   131,   132,
     140,    24,    24,    37,    35,    24,   139,    38,   154,   155,
       9,    10,    35,    70,    36,    39,    39,   104,     9,    10,
       1,   108,   108,   163,     5,    24,    72,   108,   108,    72,
      11,    12,    13,    24,    36,     1,    24,    36,     4,   179,
     180,   187,   188,     1,    36,   191,   192,    24,   181,     7,
       8,     4,     1,   193,     3,    44,   202,     6,    24,   205,
     206,    42,   108,    44,    22,   108,    36,    25,    26,    27,
      28,    24,    38,    36,    23,    24,   216,    26,     3,     9,
      10,     6,    79,    80,    81,    38,    44,     3,    37,    36,
       6,    21,    41,    42,    24,    36,    37,    16,    23,    24,
      19,    26,    21,    15,     1,    24,    17,    23,    24,     8,
      26,     3,    37,    18,     6,    44,    41,    42,    43,    19,
      20,    37,    38,    22,     5,    41,    42,     1,    27,    28,
       5,    23,    24,     5,    26,     5,     1,    11,    12,    13,
      14,     5,    36,     1,    17,    37,    11,    12,    13,    41,
      42,     7,     8,    11,    12,    13,    14,    36,     7,     8,
     122,    35,    -1,    -1,    -1,    39,    22,    -1,    -1,    25,
      26,    27,    28,    22,     1,    -1,    25,    26,    27,    28,
      -1,     7,     8,    -1,    -1,    -1,    -1,    -1,    44,    16,
      -1,    -1,    19,    20,    21,    44,    22,    24,    -1,    25,
      26,    27,    28,     7,     8,    -1,    16,    17,    -1,    19,
      36,    21,    38,    -1,    24,    -1,     7,     8,    22,    -1,
      -1,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    22,    -1,    -1,    25,    26,    27,    28,    16,    -1,
      -1,    19,    20,    21,    -1,    -1,    24,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    36
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    10,    47,     1,    24,     0,    48,     9,    10,    24,
      49,    51,    52,    53,    54,    55,    70,    55,    24,     1,
      24,    24,    35,    39,    71,    36,    55,    21,    49,    51,
      52,    53,    58,    70,    58,    37,    86,    36,    86,    86,
      24,     1,    11,    12,    13,    14,    72,    73,    74,    35,
      39,    72,    58,     1,    16,    19,    20,    24,    56,    58,
      59,    60,    61,    65,    81,     4,    38,    70,    87,    39,
      50,    36,    55,     1,    43,    36,    24,    72,    36,    66,
      68,    69,     1,     3,     6,    23,    24,    26,    37,    41,
      42,    82,    83,    84,    37,    43,    82,    20,    36,    60,
       1,    40,    70,     1,     4,    38,    70,    73,    55,    58,
       5,    42,    44,    73,     1,    42,    36,    84,    84,    84,
      36,    82,    37,    43,    82,    82,     7,     8,    22,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    85,
      17,    60,    62,    38,    57,    82,    82,    44,    60,    82,
      82,    36,    70,    58,    80,     1,    75,    77,    79,    44,
       1,    44,    15,     1,    60,    57,    82,    82,    36,    38,
      82,    82,    82,    82,    82,    82,    82,    82,    60,    17,
      18,    35,    38,    44,    73,    73,    44,     5,     5,    78,
       5,     1,     5,    67,    60,     1,    38,     1,    44,    60,
      60,    82,     5,    73,    73,     5,    76,    73,    73,    60,
      36,    36,    63,    73,    73,    73,    17,    64,    60
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 3:

/* Line 1464 of yacc.c  */
#line 135 "parser.y"
    {syntax_error(1);;}
    break;

  case 6:

/* Line 1464 of yacc.c  */
#line 144 "parser.y"
    {syntax_error(2);;}
    break;

  case 9:

/* Line 1464 of yacc.c  */
#line 151 "parser.y"
    {syntax_error(3);;}
    break;

  case 23:

/* Line 1464 of yacc.c  */
#line 181 "parser.y"
    { if (!isTYPEsame((yyvsp[(1) - (3)].en),(yyvsp[(3) - (3)].en))) semantic_error(S_ASSIGN);

          if (!isCLASSsame((yyvsp[(1) - (3)].en),(yyvsp[(3) - (3)].en)))
          {
              printf("Line %5i: SYNTAX ERROR: Assignment allowed only bettween identifiers of the same class\n",lineno);
              semErr++;
          }

          if ((yyvsp[(1) - (3)].en).class==ARRAY && (yyvsp[(3) - (3)].en).class==ARRAY)
          {
              if (!isASIZEsame((yyvsp[(1) - (3)].en),(yyvsp[(3) - (3)].en)))
              {
                  semErr++;
                  printf("Line %5i: SYNTAX ERROR: Arrays in assignment must be of the same size\n",lineno);
              }
          }

          if ((yyvsp[(1) - (3)].en).asize!=0 && (yyvsp[(1) - (3)].en).class!=ARRAY) 
              genQUAD("INDEX2",(yyvsp[(1) - (3)].en).name,tempREXPR,(yyvsp[(3) - (3)].en).name);
          else
              genQUAD("ASSIGN",(yyvsp[(3) - (3)].en).name,(yyvsp[(1) - (3)].en).name,"-");
		;}
    break;

  case 24:

/* Line 1464 of yacc.c  */
#line 205 "parser.y"
    { syntax_error(11);
          if (!isTYPEsame((yyvsp[(1) - (3)].en),(yyvsp[(3) - (3)].en))) semantic_error(S_ASSIGN);
          if (!isCLASSsame((yyvsp[(1) - (3)].en),(yyvsp[(3) - (3)].en))) 
              printf("Line %5i: SYNTAX ERROR: Assignment allowed only bettween identifiers of the same class\n",lineno);
          if ((yyvsp[(1) - (3)].en).class==ARRAY && (yyvsp[(3) - (3)].en).class==ARRAY)
          {
              if (!isASIZEsame((yyvsp[(1) - (3)].en),(yyvsp[(3) - (3)].en))) 
              printf("Line %5i: SYNTAX ERROR: Arrays in assignment must be of the same size\n",lineno);
          }
		;}
    break;

  case 31:

/* Line 1464 of yacc.c  */
#line 230 "parser.y"
    {syntax_error(0);;}
    break;

  case 32:

/* Line 1464 of yacc.c  */
#line 231 "parser.y"
    {syntax_error(27);;}
    break;

  case 39:

/* Line 1464 of yacc.c  */
#line 245 "parser.y"
    { char s[MAX_NAME];
          sprintf(s,"%i",nextQUAD+2);
          genQUAD("JUMP0",(yyvsp[(2) - (2)].en).name,s,"");
          (yyvsp[(2) - (2)].en).asize=nextQUAD;
          genQUAD("JUMP","-","-","-");
        ;}
    break;

  case 40:

/* Line 1464 of yacc.c  */
#line 252 "parser.y"
    { char s[MAX_NAME];
          sprintf(s,"%i",nextQUAD+1);
          strcpy(quads[(yyvsp[(2) - (5)].en).asize].arg1,s);
          (yyvsp[(4) - (5)].en).asize=nextQUAD;
          genQUAD("JUMP","-","-","-");
        ;}
    break;

  case 41:

/* Line 1464 of yacc.c  */
#line 259 "parser.y"
    { char s[MAX_NAME];
          sprintf(s,"%i",nextQUAD);
          strcpy(quads[(yyvsp[(4) - (7)].en).asize].arg1,s);
		;}
    break;

  case 42:

/* Line 1464 of yacc.c  */
#line 263 "parser.y"
    {syntax_error(8);;}
    break;

  case 43:

/* Line 1464 of yacc.c  */
#line 264 "parser.y"
    {syntax_error(9);;}
    break;

  case 44:

/* Line 1464 of yacc.c  */
#line 265 "parser.y"
    {printf("error\n");;}
    break;

  case 45:

/* Line 1464 of yacc.c  */
#line 269 "parser.y"
    {strcpy((yyval.en).name,"empty");;}
    break;

  case 46:

/* Line 1464 of yacc.c  */
#line 270 "parser.y"
    {strcpy((yyval.en).name,"else");;}
    break;

  case 47:

/* Line 1464 of yacc.c  */
#line 274 "parser.y"
    {(yyvsp[(1) - (1)].en).asize=nextQUAD;;}
    break;

  case 48:

/* Line 1464 of yacc.c  */
#line 276 "parser.y"
    { char s[MAX_NAME];
          sprintf(s,"%i",nextQUAD+2);
          genQUAD("JUMP0",(yyvsp[(3) - (4)].en).name,s,"-");
          (yyvsp[(3) - (4)].en).asize=nextQUAD;
          genQUAD("JUMP","-","-","-");
        ;}
    break;

  case 49:

/* Line 1464 of yacc.c  */
#line 283 "parser.y"
    { char s[MAX_NAME];
          sprintf(s,"%i",nextQUAD+1);
          strcpy(quads[(yyvsp[(3) - (6)].en).asize].arg1,s);
          sprintf(s,"%i",(yyvsp[(1) - (6)].en).asize);
          genQUAD("JUMP",s,"-","-");
        ;}
    break;

  case 50:

/* Line 1464 of yacc.c  */
#line 289 "parser.y"
    {;}
    break;

  case 51:

/* Line 1464 of yacc.c  */
#line 289 "parser.y"
    {syntax_error(10);;}
    break;

  case 52:

/* Line 1464 of yacc.c  */
#line 290 "parser.y"
    {;}
    break;

  case 53:

/* Line 1464 of yacc.c  */
#line 290 "parser.y"
    {syntax_error(10);;}
    break;

  case 54:

/* Line 1464 of yacc.c  */
#line 295 "parser.y"
    { HashToTable((yyvsp[(1) - (4)].en).name,(yyvsp[(3) - (4)].en).type,(yyvsp[(3) - (4)].en).class,(yyvsp[(3) - (4)].en).asize); ;}
    break;

  case 55:

/* Line 1464 of yacc.c  */
#line 297 "parser.y"
    { HashToTable((yyvsp[(1) - (5)].en).name,(yyvsp[(4) - (5)].en).type,(yyvsp[(4) - (5)].en).class,(yyvsp[(4) - (5)].en).asize);
          if (dcount!=0)
          {
              int i;
              for (i=0;i<dcount;i++)
              {
                  HashToTable(vlist[i],(yyvsp[(4) - (5)].en).type,(yyvsp[(4) - (5)].en).class,(yyvsp[(4) - (5)].en).asize);
                  strcpy(vlist[i],"");
              }
          }
          dcount=0;
		;}
    break;

  case 56:

/* Line 1464 of yacc.c  */
#line 309 "parser.y"
    {syntax_error(20);;}
    break;

  case 57:

/* Line 1464 of yacc.c  */
#line 310 "parser.y"
    {syntax_error(21);;}
    break;

  case 58:

/* Line 1464 of yacc.c  */
#line 315 "parser.y"
    { strcpy(vlist[dcount++],(yyvsp[(2) - (2)].en).name); ;}
    break;

  case 59:

/* Line 1464 of yacc.c  */
#line 317 "parser.y"
    { strcpy(vlist[dcount++],(yyvsp[(3) - (3)].en).name); ;}
    break;

  case 60:

/* Line 1464 of yacc.c  */
#line 319 "parser.y"
    { syntax_error(21);
              strcpy(vlist[dcount++],(yyvsp[(1) - (1)].en).name); ;}
    break;

  case 61:

/* Line 1464 of yacc.c  */
#line 325 "parser.y"
    { (yyval.en).class=IDENT;
              (yyval.en).type=(yyvsp[(1) - (1)].en).type; ;}
    break;

  case 62:

/* Line 1464 of yacc.c  */
#line 328 "parser.y"
    { (yyval.en).class=(yyvsp[(1) - (1)].en).class;
              (yyval.en).asize=(yyvsp[(1) - (1)].en).asize;
              (yyval.en).type =(yyvsp[(1) - (1)].en).type; ;}
    break;

  case 63:

/* Line 1464 of yacc.c  */
#line 334 "parser.y"
    {(yyval.en).type=CHAR;;}
    break;

  case 64:

/* Line 1464 of yacc.c  */
#line 335 "parser.y"
    {(yyval.en).type=INTEGER;;}
    break;

  case 65:

/* Line 1464 of yacc.c  */
#line 336 "parser.y"
    {(yyval.en).type=BOOLEAN;;}
    break;

  case 66:

/* Line 1464 of yacc.c  */
#line 337 "parser.y"
    {(yyval.en).type=ERROR_TYPE;;}
    break;

  case 67:

/* Line 1464 of yacc.c  */
#line 342 "parser.y"
    { (yyval.en).type=(yyvsp[(6) - (6)].en).type;  (yyval.en).class=ARRAY;  (yyval.en).asize=(yyvsp[(3) - (6)].i); ;}
    break;

  case 68:

/* Line 1464 of yacc.c  */
#line 343 "parser.y"
    {syntax_error(14);;}
    break;

  case 70:

/* Line 1464 of yacc.c  */
#line 344 "parser.y"
    {syntax_error(14);;}
    break;

  case 72:

/* Line 1464 of yacc.c  */
#line 345 "parser.y"
    {syntax_error(14);;}
    break;

  case 74:

/* Line 1464 of yacc.c  */
#line 346 "parser.y"
    {syntax_error(12);;}
    break;

  case 75:

/* Line 1464 of yacc.c  */
#line 347 "parser.y"
    {syntax_error(13);;}
    break;

  case 76:

/* Line 1464 of yacc.c  */
#line 348 "parser.y"
    {syntax_error(15);;}
    break;

  case 78:

/* Line 1464 of yacc.c  */
#line 349 "parser.y"
    {syntax_error(13);;}
    break;

  case 80:

/* Line 1464 of yacc.c  */
#line 350 "parser.y"
    {syntax_error(13);;}
    break;

  case 82:

/* Line 1464 of yacc.c  */
#line 351 "parser.y"
    {syntax_error(13);;}
    break;

  case 83:

/* Line 1464 of yacc.c  */
#line 356 "parser.y"
    { ENTRY *tmp=(ENTRY *) lookup(symtab, (yyvsp[(1) - (1)].en).name);
          if (tmp) 
          {
              if (tmp->type)
              {
                  (yyval.en).type=tmp->type;
                  (yyval.en).class=tmp->class;
                  (yyval.en).asize=tmp->asize;
                  strcpy((yyval.en).name,(yyvsp[(1) - (1)].en).name);
              }
              else
              {
                  (yyval.en).type=ERROR_TYPE;
                  (yyval.en).class=IDENT;
                  semErr++;
              }
          }
          else
          {
              undef_error((yyvsp[(1) - (1)].en).name);
              (yyval.en).class=IDENT;
          }
		;}
    break;

  case 84:

/* Line 1464 of yacc.c  */
#line 380 "parser.y"
    { ENTRY *tmp=(ENTRY *) lookup(symtab, (yyvsp[(1) - (4)].en).name);
          if(tmp)
          {
              if (tmp->class==ARRAY) 
              {
                  (yyval.en).type=tmp->type;
                  (yyval.en).asize=tmp->asize;
                  strcpy((yyval.en).name,(yyvsp[(1) - (4)].en).name);
              }
              else
                  arrcls_error(NOT_ARRAY,(yyvsp[(1) - (4)].en).name);
		  }
          else
              undef_error((yyvsp[(1) - (4)].en).name);
		
          (yyval.en).class=IDENT;
          if ((yyvsp[(3) - (4)].en).type!=INTEGER || (yyvsp[(3) - (4)].en).class!=IDENT) 
              arrcls_error(S_EXPINT,(yyvsp[(1) - (4)].en).name);
          strcpy(tempREXPR,(yyvsp[(3) - (4)].en).name);
		;}
    break;

  case 85:

/* Line 1464 of yacc.c  */
#line 400 "parser.y"
    {syntax_error(23);;}
    break;

  case 86:

/* Line 1464 of yacc.c  */
#line 401 "parser.y"
    {syntax_error(23);;}
    break;

  case 87:

/* Line 1464 of yacc.c  */
#line 406 "parser.y"
    { (yyval.en).type=(yyvsp[(1) - (1)].en).type;
          if ((yyvsp[(1) - (1)].en).class==STRING) 
          {
              (yyval.en).asize=(yyvsp[(1) - (1)].en).asize;
              (yyval.en).class=ARRAY;
              strcpy((yyval.en).name,(yyvsp[(1) - (1)].en).name);
          }
          else
          {
              (yyval.en).class=IDENT;
              strcpy((yyval.en).name,(yyvsp[(1) - (1)].en).name);
          }
		;}
    break;

  case 88:

/* Line 1464 of yacc.c  */
#line 420 "parser.y"
    { ENTRY *tmp=(ENTRY *) lookup(symtab, (yyvsp[(1) - (1)].en).name);
          if (tmp) 
          {
              if (tmp->type)
              {
                  (yyval.en).type=tmp->type;
                  (yyval.en).class=tmp->class;
                  (yyval.en).asize=tmp->asize;
                  strcpy((yyval.en).name,(yyvsp[(1) - (1)].en).name);
              }
              else
              {
                  (yyval.en).type=ERROR_TYPE;
                  (yyval.en).class=IDENT;
                  semErr++;
              }
          }
          else
          {
              undef_error((yyvsp[(1) - (1)].en).name);
              (yyval.en).class=IDENT;
          }
		;}
    break;

  case 89:

/* Line 1464 of yacc.c  */
#line 444 "parser.y"
    { if (!isCLASSsame((yyvsp[(1) - (3)].en),(yyvsp[(3) - (3)].en))) 
              printf("Line %5i: SYNTAX ERROR: Numerical operators allowed only between identifiers or constants\n",lineno);
          else
              if ((yyvsp[(1) - (3)].en).type==INTEGER && (yyvsp[(3) - (3)].en).type==INTEGER)
                  (yyval.en).type=(yyvsp[(1) - (3)].en).type;
              else
                  printf("Line %5i: SYNTAX ERROR: Numerical operators allowed only between integers\n",lineno);
	
          (yyval.en).type=INTEGER;
          (yyval.en).class=IDENT;
          sprintf((yyval.en).name,"$%i",buff++);
          genQUAD("MULT",(yyvsp[(1) - (3)].en).name,(yyvsp[(3) - (3)].en).name,(yyval.en).name);
        ;}
    break;

  case 90:

/* Line 1464 of yacc.c  */
#line 458 "parser.y"
    { if (!isCLASSsame((yyvsp[(1) - (3)].en),(yyvsp[(3) - (3)].en))) 
              printf("Line %5i: SYNTAX ERROR: Numerical operators allowed only between identifiers or constants\n",lineno);
          else
              if ((yyvsp[(1) - (3)].en).type==INTEGER && (yyvsp[(3) - (3)].en).type==INTEGER)
                  (yyval.en).type=(yyvsp[(1) - (3)].en).type;
              else
                  printf("Line %5i: SYNTAX ERROR: Numerical operators allowed only between integers\n",lineno);
	
          (yyval.en).type=INTEGER;
          (yyval.en).class=IDENT;
          sprintf((yyval.en).name,"$%i",buff++);
          genQUAD("DIV",(yyvsp[(1) - (3)].en).name,(yyvsp[(3) - (3)].en).name,(yyval.en).name);
        ;}
    break;

  case 91:

/* Line 1464 of yacc.c  */
#line 472 "parser.y"
    { if (!isCLASSsame((yyvsp[(1) - (3)].en),(yyvsp[(3) - (3)].en))) 
              printf("Line %5i: SYNTAX ERROR: Numerical operators allowed only between\n\t\tidentifiers or constants\n",lineno);
          else
              if ((yyvsp[(1) - (3)].en).type==INTEGER && (yyvsp[(3) - (3)].en).type==INTEGER)
                  (yyval.en).type=(yyvsp[(1) - (3)].en).type;
              else
                  printf("Line %5i: SYNTAX ERROR: Numerical operators allowed only between integers\n",lineno);
	
          (yyval.en).type=INTEGER;
          (yyval.en).class=IDENT;
          sprintf((yyval.en).name,"$%i",buff++);
          genQUAD("ADD",(yyvsp[(1) - (3)].en).name,(yyvsp[(3) - (3)].en).name,(yyval.en).name);
        ;}
    break;

  case 92:

/* Line 1464 of yacc.c  */
#line 486 "parser.y"
    { if (!isCLASSsame((yyvsp[(1) - (3)].en),(yyvsp[(3) - (3)].en))) 
              printf("Line %5i: SYNTAX ERROR: Numerical operators allowed only between\n\t\tidentifiers or constants\n",lineno);
          else
              if ((yyvsp[(1) - (3)].en).type==INTEGER && (yyvsp[(3) - (3)].en).type==INTEGER)
                  (yyval.en).type=(yyvsp[(1) - (3)].en).type;
              else
                  printf("Line %5i: SYNTAX ERROR: Numerical operators allowed only between integers\n",lineno);
	
          (yyval.en).type=INTEGER;
          (yyval.en).class=IDENT;
          sprintf((yyval.en).name,"$%i",buff++);
          genQUAD("SUB",(yyvsp[(1) - (3)].en).name,(yyvsp[(3) - (3)].en).name,(yyval.en).name);
        ;}
    break;

  case 93:

/* Line 1464 of yacc.c  */
#line 500 "parser.y"
    { if (!isCLASSsame((yyvsp[(1) - (3)].en),(yyvsp[(3) - (3)].en))) 
              printf("Line %5i: SYNTAX ERROR: Numerical operators allowed only between\n\t\tidentifiers or constants\n",lineno);
          else
              if ((yyvsp[(1) - (3)].en).type==INTEGER && (yyvsp[(3) - (3)].en).type==INTEGER)
                  (yyval.en).type=(yyvsp[(1) - (3)].en).type;
              else
                  printf("Line %5i: SYNTAX ERROR: Numerical operators allowed only between integers\n",lineno);
	
          (yyval.en).type=INTEGER;
          (yyval.en).class=IDENT;
          sprintf((yyval.en).name,"$%i",buff++);
          genQUAD("MOD",(yyvsp[(1) - (3)].en).name,(yyvsp[(3) - (3)].en).name,(yyval.en).name);
        ;}
    break;

  case 94:

/* Line 1464 of yacc.c  */
#line 514 "parser.y"
    { if (!isCLASSsame((yyvsp[(1) - (3)].en),(yyvsp[(3) - (3)].en)))
              printf("Line %5i: SYNTAX ERROR: Logical operators allowed only between\n\t\t boolean  identifiers or constants\n",lineno);
          else
              if ((yyvsp[(1) - (3)].en).type==BOOLEAN && (yyvsp[(3) - (3)].en).type==BOOLEAN)
                  (yyval.en).type=(yyvsp[(1) - (3)].en).type;
              else 
                  printf("Line %5i: SYNTAX ERROR: Logical operators allowed only between\n\t\t boolean  identifiers or constants\n",lineno);

          (yyval.en).type=BOOLEAN;
          (yyval.en).class=IDENT;
          sprintf((yyval.en).name,"$%i",buff++);
          genQUAD("AND",(yyvsp[(1) - (3)].en).name,(yyvsp[(3) - (3)].en).name,(yyval.en).name);
        ;}
    break;

  case 95:

/* Line 1464 of yacc.c  */
#line 528 "parser.y"
    { if (!isCLASSsame((yyvsp[(1) - (3)].en),(yyvsp[(3) - (3)].en)))
              printf("Line %5i: SYNTAX ERROR: Logical operators allowed only between\n\t\t boolean  identifiers or constants\n",lineno);
          else
              if ((yyvsp[(1) - (3)].en).type==BOOLEAN && (yyvsp[(3) - (3)].en).type==BOOLEAN)
                  (yyval.en).type=(yyvsp[(1) - (3)].en).type;
              else 
                  printf("Line %5i: SYNTAX ERROR: Logical operators allowed only between\n\t\t boolean  identifiers or constants\n",lineno);

          (yyval.en).type=BOOLEAN;
          (yyval.en).class=IDENT;
          sprintf((yyval.en).name,"$%i",buff++);
          genQUAD("OR",(yyvsp[(1) - (3)].en).name,(yyvsp[(3) - (3)].en).name,(yyval.en).name);
        ;}
    break;

  case 96:

/* Line 1464 of yacc.c  */
#line 542 "parser.y"
    { ENTRY *tmp=(ENTRY *)lookup(symtab, (yyvsp[(1) - (4)].en).name);
          if(tmp)
          {
              if (tmp->class==ARRAY)
                  (yyval.en).type=tmp->type;
              else
                  arrcls_error(NOT_ARRAY,(yyvsp[(1) - (4)].en).name);
		  }
          else
              undef_error((yyvsp[(1) - (4)].en).name);
		
          if ((yyvsp[(3) - (4)].en).type!=INTEGER || (yyvsp[(3) - (4)].en).class!=IDENT) 
              arrcls_error(S_EXPINT,(yyvsp[(1) - (4)].en).name);

          (yyval.en).class=IDENT;
          sprintf((yyval.en).name,"$%i",buff++);
          genQUAD("INDEX1",(yyval.en).name,(yyvsp[(1) - (4)].en).name,(yyvsp[(3) - (4)].en).name);
		;}
    break;

  case 97:

/* Line 1464 of yacc.c  */
#line 562 "parser.y"
    { if ((yyvsp[(2) - (2)].en).type==BOOLEAN  && (yyvsp[(2) - (2)].en).class==IDENT)  (yyval.en)=(yyvsp[(2) - (2)].en);
          else
          {
              printf("Line %5i: SYNTAX ERROR: 'NOT' allowed only to boolean identifiers or constants\n",lineno);
          }

          (yyval.en).type=BOOLEAN;
          (yyval.en).class=IDENT;
          sprintf((yyval.en).name,"$%i",buff++);
          genQUAD("NOT",(yyval.en).name,(yyvsp[(2) - (2)].en).name,"-");
        ;}
    break;

  case 98:

/* Line 1464 of yacc.c  */
#line 574 "parser.y"
    { if ((yyvsp[(2) - (2)].en).type==INTEGER && (yyvsp[(2) - (2)].en).class==IDENT) (yyval.en)=(yyvsp[(2) - (2)].en);
          else
          {
              printf("Line %5i: SYNTAX ERROR: Unary '-' allowed only to integer  identifiers or constants\n",lineno);
          }

          (yyval.en).type=INTEGER;
          (yyval.en).class=IDENT;

          sprintf((yyval.en).name,"$%i",buff++);
          genQUAD("UMINUS",(yyval.en).name,(yyvsp[(2) - (2)].en).name,"-");
        ;}
    break;

  case 99:

/* Line 1464 of yacc.c  */
#line 586 "parser.y"
    {(yyval.en)=(yyvsp[(2) - (3)].en);;}
    break;

  case 101:

/* Line 1464 of yacc.c  */
#line 588 "parser.y"
    {syntax_error(16);;}
    break;

  case 102:

/* Line 1464 of yacc.c  */
#line 589 "parser.y"
    {syntax_error(17);;}
    break;

  case 103:

/* Line 1464 of yacc.c  */
#line 590 "parser.y"
    {syntax_error(16);;}
    break;

  case 104:

/* Line 1464 of yacc.c  */
#line 595 "parser.y"
    { int i=(yyvsp[(1) - (1)].i);
          (yyval.en).type=INTEGER;
          (yyval.en).class=IDENT;
          (yyval.en).asize=0;
          sprintf((yyval.en).name,"%i",(yyvsp[(1) - (1)].i)); ;}
    break;

  case 105:

/* Line 1464 of yacc.c  */
#line 601 "parser.y"
    { (yyval.en).type=CHAR;
          (yyval.en).class=STRING;
          (yyval.en).asize=strlen((yyvsp[(1) - (1)].en).name);
          strcpy((yyval.en).name,(yyvsp[(1) - (1)].en).name); ;}
    break;

  case 106:

/* Line 1464 of yacc.c  */
#line 606 "parser.y"
    { (yyval.en).type=BOOLEAN;
          (yyval.en).class=IDENT;
          (yyval.en).asize=0;
          strcpy((yyval.en).name,"true"); ;}
    break;

  case 107:

/* Line 1464 of yacc.c  */
#line 611 "parser.y"
    { (yyval.en).type=BOOLEAN;
          (yyval.en).class=IDENT;
          (yyval.en).asize=0;
          strcpy((yyval.en).name,"false"); ;}
    break;

  case 108:

/* Line 1464 of yacc.c  */
#line 619 "parser.y"
    { if (!isCLASSsame((yyvsp[(1) - (3)].en),(yyvsp[(3) - (3)].en)))
              printf("Line %5i: SYNTAX ERROR: Relational operators allowed only between\n\t\t identifiers or constants of the same class\n",lineno);
          else
              if ( ((yyvsp[(1) - (3)].en).type==BOOLEAN && (yyvsp[(3) - (3)].en).type==BOOLEAN)||((yyvsp[(1) - (3)].en).type==INTEGER && (yyvsp[(3) - (3)].en).type==INTEGER) )
                  (yyval.en).type=BOOLEAN;
              else
              {
                  printf("Line %5i: SYNTAX ERROR: Relational operators allowed only between\n\t\t integers or boolean constants\n",lineno);
                  (yyval.en).type=BOOLEAN;
              }

          (yyval.en).type=BOOLEAN;
          sprintf((yyval.en).name,"$%i",buff++);
          genQUAD((yyvsp[(2) - (3)].en).name,(yyvsp[(1) - (3)].en).name,(yyvsp[(3) - (3)].en).name,(yyval.en).name);
        ;}
    break;

  case 109:

/* Line 1464 of yacc.c  */
#line 637 "parser.y"
    {strcpy((yyval.en).name,"LT");;}
    break;

  case 110:

/* Line 1464 of yacc.c  */
#line 638 "parser.y"
    {strcpy((yyval.en).name,"LE");;}
    break;

  case 111:

/* Line 1464 of yacc.c  */
#line 639 "parser.y"
    {strcpy((yyval.en).name,"EQ");;}
    break;

  case 112:

/* Line 1464 of yacc.c  */
#line 640 "parser.y"
    {strcpy((yyval.en).name,"GT");;}
    break;

  case 113:

/* Line 1464 of yacc.c  */
#line 641 "parser.y"
    {strcpy((yyval.en).name,"GE");;}
    break;

  case 114:

/* Line 1464 of yacc.c  */
#line 642 "parser.y"
    {strcpy((yyval.en).name,"NE");;}
    break;

  case 117:

/* Line 1464 of yacc.c  */
#line 648 "parser.y"
    {syntax_error(18);;}
    break;



/* Line 1464 of yacc.c  */
#line 2491 "parser.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1684 of yacc.c  */
#line 658 "parser.y"


#include "npcshell.h"


int yyerror()   {  /* dummy procedure */  }


int main( void )
{
    symtab=create_table(127,hash,cmp);
    yyparse();

    printf("Compiling process finished : %s found\n", IsErrorFree?"No errors":"Errors");
    genQUAD("PGREND","-","-","-");
    if (!IsErrorFree)
    {
        printf("\n\tSyntax: %i\tLexical: %i\tSemantic: %i\n",syntaxErr,lexerr,semErr);
        return(1);
    }
    else
    {
        printCODE(DEF_OUTFILENAME);
        return(0);
    }

}



