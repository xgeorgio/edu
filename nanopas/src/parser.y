%{
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


%} 

%union {
    int     i;
    ENTRY   en; }

%token  <en>    TOKTRUE         301
%token  <en>    TOKVAR          302
%token  <en>    TOKOF           303
%token  <en>    TOKNOT          304
%token  <en>    TOKOR           305
%token  <en>    TOKAND          306
%token  <en>    TOKFUNCTION     307
%token  <en>    TOKPROCEDURE    308 
%token  <en>    TOKBOOL         309
%token  <en>    TOKINT          310
%token  <en>    TOKCHAR         311
%token  <en>    TOKARRAY        312 
%token  <en>    TOKDO           313
%token  <en>    TOKWHILE        314
%token  <en>    TOKELSE         315
%token  <en>    TOKTHEN         316
%token  <en>    TOKIF           317
%token  <en>    TOKEND          318
%token  <en>    TOKBEGIN        319 
%token  <en>    TOKMOD          320
%token  <en>    TOKFALSE        321
%token  <en>    IDENTIFIER      322
%token  <en>    PLUS            323
%token  <en>    MINUS           324
%token  <en>    MULTIPLY        325
%token  <en>    DIVIDE          326
%token  <en>    LES             327
%token  <en>    LEQ             328
%token  <en>    EQ              329
%token  <en>    GT              330
%token  <en>    GE              331
%token  <en>    NEQ             332
%token  <en>    COMMA           333
%token  <en>    SEMI            334
%token  <en>    OPENPAR         335
%token  <en>    CLOSEPAR        336
%token  <en>    COLON           337
%token  <en>    ASSIGNOP        338
%token  <en>    STRINGTOK       339
%token  <i>     INTCONST        340
%token  <en>    LB              341
%token  <en>    RB              342

%left LES LEQ EQ GT GE NEQ
%left TOKOR MINUS PLUS
%left TOKAND MULTIPLY DIVIDE TOKMOD
%left TOKNOT UMINUS

%type   <en>    boolexpr
%type   <en>    rel_op   
%type   <en>    leftexpr
%type   <en>    r_expr
%type   <en>    stmt
%type   <en>    stmt_block
%type   <en>    type
%type   <en>    constant
%type   <en>    simple_type
%type   <en>    array_declare
%type   <en>    formal_rec
%type   <en>    var_decl
%type   <en>    actual_par_list
%type   <en>    formal_par_list
%type   <en>    assgmnt_stmt
%type   <en>    procedure
%type   <en>    function
%type   <en>    forward_function
%type   <en>    forward_procedure
%type   <en>    declaration
%type   <en>    fun_declare
%type   <en>    compound_stmt
%type   <en>    if_stmt
%type   <en>    while_stmt
%type   <en>    tail

%%


program: TOKPROCEDURE IDENTIFIER 
            declaration
            compound_stmt 
        |TOKPROCEDURE error {syntax_error(1);}
            declaration
            compound_stmt
        ;


procedure: TOKPROCEDURE IDENTIFIER formal_par_list
                declaration 
                compound_stmt
            | TOKPROCEDURE  error formal_par_list {syntax_error(2);}  
                declaration
                compound_stmt
        ;


forward_procedure: TOKPROCEDURE IDENTIFIER  formal_par_list SEMI
            | TOKPROCEDURE error SEMI {syntax_error(3);}
        ;


function: fun_declare declaration compound_stmt
        ;


forward_function: fun_declare SEMI
        ;


fun_declare: TOKFUNCTION IDENTIFIER  formal_par_list COLON simple_type
        ;
 

declaration: procedure
        | function
        | forward_procedure
        | forward_function 
        | var_decl
        | declaration procedure 
        | declaration function
        | declaration forward_procedure
        | declaration forward_function 
        | declaration var_decl
        ;


assgmnt_stmt:  leftexpr ASSIGNOP r_expr
        { if (!isTYPEsame($1,$3)) semantic_error(S_ASSIGN);

          if (!isCLASSsame($1,$3))
          {
              printf("Line %5i: SYNTAX ERROR: Assignment allowed only bettween identifiers of the same class\n",lineno);
              semErr++;
          }

          if ($1.class==ARRAY && $3.class==ARRAY)
          {
              if (!isASIZEsame($1,$3))
              {
                  semErr++;
                  printf("Line %5i: SYNTAX ERROR: Arrays in assignment must be of the same size\n",lineno);
              }
          }

          if ($1.asize!=0 && $1.class!=ARRAY) 
              genQUAD("INDEX2",$1.name,tempREXPR,$3.name);
          else
              genQUAD("ASSIGN",$3.name,$1.name,"-");
		}

        | leftexpr error r_expr 
        { syntax_error(11);
          if (!isTYPEsame($1,$3)) semantic_error(S_ASSIGN);
          if (!isCLASSsame($1,$3)) 
              printf("Line %5i: SYNTAX ERROR: Assignment allowed only bettween identifiers of the same class\n",lineno);
          if ($1.class==ARRAY && $3.class==ARRAY)
          {
              if (!isASIZEsame($1,$3)) 
              printf("Line %5i: SYNTAX ERROR: Arrays in assignment must be of the same size\n",lineno);
          }
		}
        ;


actual_par_list:  r_expr
        | actual_par_list COMMA r_expr
        ;


compound_stmt: TOKBEGIN TOKEND
        | TOKBEGIN stmt_block TOKEND
        ;


stmt_block: stmt
        | stmt_block SEMI stmt
        | stmt_block stmt           {syntax_error(0);}
        | error SEMI                {syntax_error(27);} 
        ;


stmt:  compound_stmt
        | assgmnt_stmt
        | if_stmt
        | while_stmt 
        | IDENTIFIER OPENPAR actual_par_list CLOSEPAR
        | IDENTIFIER OPENPAR CLOSEPAR
        ;


if_stmt: TOKIF boolexpr
        { char s[MAX_NAME];
          sprintf(s,"%i",nextQUAD+2);
          genQUAD("JUMP0",$2.name,s,"");
          $2.asize=nextQUAD;
          genQUAD("JUMP","-","-","-");
        } 
        TOKTHEN stmt
        { char s[MAX_NAME];
          sprintf(s,"%i",nextQUAD+1);
          strcpy(quads[$2.asize].arg1,s);
          $4.asize=nextQUAD;
          genQUAD("JUMP","-","-","-");
        }
        tail
        { char s[MAX_NAME];
          sprintf(s,"%i",nextQUAD);
          strcpy(quads[$4.asize].arg1,s);
		}
        |TOKIF boolexpr TOKELSE stmt        {syntax_error(8);}
        |TOKIF boolexpr stmt TOKELSE stmt   {syntax_error(9);}
        |TOKIF error SEMI                   {printf("error\n");}
        ;


tail:                       {strcpy($$.name,"empty");}
        | TOKELSE stmt      {strcpy($$.name,"else");}
        ;


while_stmt: TOKWHILE {$1.asize=nextQUAD;}
        boolexpr TOKDO
        { char s[MAX_NAME];
          sprintf(s,"%i",nextQUAD+2);
          genQUAD("JUMP0",$3.name,s,"-");
          $3.asize=nextQUAD;
          genQUAD("JUMP","-","-","-");
        } 
        stmt
        { char s[MAX_NAME];
          sprintf(s,"%i",nextQUAD+1);
          strcpy(quads[$3.asize].arg1,s);
          sprintf(s,"%i",$1.asize);
          genQUAD("JUMP",s,"-","-");
        }
        |TOKWHILE  {} boolexpr error stmt   {syntax_error(10);}
        |TOKWHILE  {} boolexpr stmt         {syntax_error(10);} 
        ;


var_decl: IDENTIFIER COLON type  SEMI
        { HashToTable($1.name,$3.type,$3.class,$3.asize); }
        | IDENTIFIER var_list  COLON type  SEMI
        { HashToTable($1.name,$4.type,$4.class,$4.asize);
          if (dcount!=0)
          {
              int i;
              for (i=0;i<dcount;i++)
              {
                  HashToTable(vlist[i],$4.type,$4.class,$4.asize);
                  strcpy(vlist[i],"");
              }
          }
          dcount=0;
		}
        | IDENTIFIER COLON type          {syntax_error(20);}
        | IDENTIFIER var_list type       {syntax_error(21);}
        ;


var_list:  COMMA IDENTIFIER
            { strcpy(vlist[dcount++],$2.name); }
        | var_list COMMA IDENTIFIER 
            { strcpy(vlist[dcount++],$3.name); }
        | IDENTIFIER
            { syntax_error(21);
              strcpy(vlist[dcount++],$1.name); } 
        ;


type:   simple_type
            { $$.class=IDENT;
              $$.type=$1.type; }
        | array_declare
            { $$.class=$1.class;
              $$.asize=$1.asize;
              $$.type =$1.type; }
        ;


simple_type:  TOKCHAR           {$$.type=CHAR;}
        | TOKINT                {$$.type=INTEGER;}
        | TOKBOOL               {$$.type=BOOLEAN;}
        | error                 {$$.type=ERROR_TYPE;}
        ;


array_declare: TOKARRAY  LB INTCONST  RB TOKOF simple_type
            { $$.type=$6.type;  $$.class=ARRAY;  $$.asize=$3; }
        | TOKARRAY  error INTCONST {syntax_error(14);} RB TOKOF simple_type 
        | TOKARRAY  LB    INTCONST error TOKOF {syntax_error(14);} simple_type
        | TOKARRAY  error INTCONST {syntax_error(14);} TOKOF simple_type 
        | TOKARRAY  LB    INTCONST RB  error simple_type {syntax_error(12);} 
        | TOKARRAY  error INTCONST error simple_type {syntax_error(13);}  
        | TOKARRAY  LB error  RB {syntax_error(15);} TOKOF simple_type 
        | TOKARRAY  error  RB {syntax_error(13);} TOKOF simple_type 
        | TOKARRAY  error  TOKOF {syntax_error(13);} simple_type 
        | TOKARRAY  error  simple_type {syntax_error(13);}
        ;


leftexpr: IDENTIFIER                        
        { ENTRY *tmp=(ENTRY *) lookup(symtab, $1.name);
          if (tmp) 
          {
              if (tmp->type)
              {
                  $$.type=tmp->type;
                  $$.class=tmp->class;
                  $$.asize=tmp->asize;
                  strcpy($$.name,$1.name);
              }
              else
              {
                  $$.type=ERROR_TYPE;
                  $$.class=IDENT;
                  semErr++;
              }
          }
          else
          {
              undef_error($1.name);
              $$.class=IDENT;
          }
		}
        | IDENTIFIER LB r_expr RB  
        { ENTRY *tmp=(ENTRY *) lookup(symtab, $1.name);
          if(tmp)
          {
              if (tmp->class==ARRAY) 
              {
                  $$.type=tmp->type;
                  $$.asize=tmp->asize;
                  strcpy($$.name,$1.name);
              }
              else
                  arrcls_error(NOT_ARRAY,$1.name);
		  }
          else
              undef_error($1.name);
		
          $$.class=IDENT;
          if ($3.type!=INTEGER || $3.class!=IDENT) 
              arrcls_error(S_EXPINT,$1.name);
          strcpy(tempREXPR,$3.name);
		}
        | IDENTIFIER LB r_expr          {syntax_error(23);}
        | IDENTIFIER r_expr RB          {syntax_error(23);}
        ;


r_expr: constant 
        { $$.type=$1.type;
          if ($1.class==STRING) 
          {
              $$.asize=$1.asize;
              $$.class=ARRAY;
              strcpy($$.name,$1.name);
          }
          else
          {
              $$.class=IDENT;
              strcpy($$.name,$1.name);
          }
		}
        | IDENTIFIER
        { ENTRY *tmp=(ENTRY *) lookup(symtab, $1.name);
          if (tmp) 
          {
              if (tmp->type)
              {
                  $$.type=tmp->type;
                  $$.class=tmp->class;
                  $$.asize=tmp->asize;
                  strcpy($$.name,$1.name);
              }
              else
              {
                  $$.type=ERROR_TYPE;
                  $$.class=IDENT;
                  semErr++;
              }
          }
          else
          {
              undef_error($1.name);
              $$.class=IDENT;
          }
		}
        | r_expr MULTIPLY r_expr
        { if (!isCLASSsame($1,$3)) 
              printf("Line %5i: SYNTAX ERROR: Numerical operators allowed only between identifiers or constants\n",lineno);
          else
              if ($1.type==INTEGER && $3.type==INTEGER)
                  $$.type=$1.type;
              else
                  printf("Line %5i: SYNTAX ERROR: Numerical operators allowed only between integers\n",lineno);
	
          $$.type=INTEGER;
          $$.class=IDENT;
          sprintf($$.name,"$%i",buff++);
          genQUAD("MULT",$1.name,$3.name,$$.name);
        }
        | r_expr DIVIDE r_expr
        { if (!isCLASSsame($1,$3)) 
              printf("Line %5i: SYNTAX ERROR: Numerical operators allowed only between identifiers or constants\n",lineno);
          else
              if ($1.type==INTEGER && $3.type==INTEGER)
                  $$.type=$1.type;
              else
                  printf("Line %5i: SYNTAX ERROR: Numerical operators allowed only between integers\n",lineno);
	
          $$.type=INTEGER;
          $$.class=IDENT;
          sprintf($$.name,"$%i",buff++);
          genQUAD("DIV",$1.name,$3.name,$$.name);
        }
        | r_expr PLUS r_expr
        { if (!isCLASSsame($1,$3)) 
              printf("Line %5i: SYNTAX ERROR: Numerical operators allowed only between\n\t\tidentifiers or constants\n",lineno);
          else
              if ($1.type==INTEGER && $3.type==INTEGER)
                  $$.type=$1.type;
              else
                  printf("Line %5i: SYNTAX ERROR: Numerical operators allowed only between integers\n",lineno);
	
          $$.type=INTEGER;
          $$.class=IDENT;
          sprintf($$.name,"$%i",buff++);
          genQUAD("ADD",$1.name,$3.name,$$.name);
        }
        | r_expr MINUS r_expr
        { if (!isCLASSsame($1,$3)) 
              printf("Line %5i: SYNTAX ERROR: Numerical operators allowed only between\n\t\tidentifiers or constants\n",lineno);
          else
              if ($1.type==INTEGER && $3.type==INTEGER)
                  $$.type=$1.type;
              else
                  printf("Line %5i: SYNTAX ERROR: Numerical operators allowed only between integers\n",lineno);
	
          $$.type=INTEGER;
          $$.class=IDENT;
          sprintf($$.name,"$%i",buff++);
          genQUAD("SUB",$1.name,$3.name,$$.name);
        }
        | r_expr TOKMOD r_expr
        { if (!isCLASSsame($1,$3)) 
              printf("Line %5i: SYNTAX ERROR: Numerical operators allowed only between\n\t\tidentifiers or constants\n",lineno);
          else
              if ($1.type==INTEGER && $3.type==INTEGER)
                  $$.type=$1.type;
              else
                  printf("Line %5i: SYNTAX ERROR: Numerical operators allowed only between integers\n",lineno);
	
          $$.type=INTEGER;
          $$.class=IDENT;
          sprintf($$.name,"$%i",buff++);
          genQUAD("MOD",$1.name,$3.name,$$.name);
        }
        | r_expr TOKAND r_expr       
        { if (!isCLASSsame($1,$3))
              printf("Line %5i: SYNTAX ERROR: Logical operators allowed only between\n\t\t boolean  identifiers or constants\n",lineno);
          else
              if ($1.type==BOOLEAN && $3.type==BOOLEAN)
                  $$.type=$1.type;
              else 
                  printf("Line %5i: SYNTAX ERROR: Logical operators allowed only between\n\t\t boolean  identifiers or constants\n",lineno);

          $$.type=BOOLEAN;
          $$.class=IDENT;
          sprintf($$.name,"$%i",buff++);
          genQUAD("AND",$1.name,$3.name,$$.name);
        }
        | r_expr TOKOR r_expr       
        { if (!isCLASSsame($1,$3))
              printf("Line %5i: SYNTAX ERROR: Logical operators allowed only between\n\t\t boolean  identifiers or constants\n",lineno);
          else
              if ($1.type==BOOLEAN && $3.type==BOOLEAN)
                  $$.type=$1.type;
              else 
                  printf("Line %5i: SYNTAX ERROR: Logical operators allowed only between\n\t\t boolean  identifiers or constants\n",lineno);

          $$.type=BOOLEAN;
          $$.class=IDENT;
          sprintf($$.name,"$%i",buff++);
          genQUAD("OR",$1.name,$3.name,$$.name);
        }
        | IDENTIFIER LB r_expr RB
        { ENTRY *tmp=(ENTRY *)lookup(symtab, $1.name);
          if(tmp)
          {
              if (tmp->class==ARRAY)
                  $$.type=tmp->type;
              else
                  arrcls_error(NOT_ARRAY,$1.name);
		  }
          else
              undef_error($1.name);
		
          if ($3.type!=INTEGER || $3.class!=IDENT) 
              arrcls_error(S_EXPINT,$1.name);

          $$.class=IDENT;
          sprintf($$.name,"$%i",buff++);
          genQUAD("INDEX1",$$.name,$1.name,$3.name);
		}

        | TOKNOT r_expr
        { if ($2.type==BOOLEAN  && $2.class==IDENT)  $$=$2;
          else
          {
              printf("Line %5i: SYNTAX ERROR: 'NOT' allowed only to boolean identifiers or constants\n",lineno);
          }

          $$.type=BOOLEAN;
          $$.class=IDENT;
          sprintf($$.name,"$%i",buff++);
          genQUAD("NOT",$$.name,$2.name,"-");
        }
        | MINUS r_expr  %prec UMINUS
        { if ($2.type==INTEGER && $2.class==IDENT) $$=$2;
          else
          {
              printf("Line %5i: SYNTAX ERROR: Unary '-' allowed only to integer  identifiers or constants\n",lineno);
          }

          $$.type=INTEGER;
          $$.class=IDENT;

          sprintf($$.name,"$%i",buff++);
          genQUAD("UMINUS",$$.name,$2.name,"-");
        }
        | OPENPAR r_expr CLOSEPAR                       {$$=$2;}
        | IDENTIFIER OPENPAR  actual_par_list CLOSEPAR
        | OPENPAR r_expr SEMI                           {syntax_error(16);}
        | IDENTIFIER LB r_expr error SEMI               {syntax_error(17);}
        | IDENTIFIER OPENPAR actual_par_list error SEMI {syntax_error(16);}
        ;


constant: INTCONST
        { int i=$1;
          $$.type=INTEGER;
          $$.class=IDENT;
          $$.asize=0;
          sprintf($$.name,"%i",$1); }
        | STRINGTOK
        { $$.type=CHAR;
          $$.class=STRING;
          $$.asize=strlen($1.name);
          strcpy($$.name,$1.name); }
        | TOKTRUE
        { $$.type=BOOLEAN;
          $$.class=IDENT;
          $$.asize=0;
          strcpy($$.name,"true"); }
        | TOKFALSE
        { $$.type=BOOLEAN;
          $$.class=IDENT;
          $$.asize=0;
          strcpy($$.name,"false"); }
        ;


boolexpr:  r_expr rel_op r_expr
        { if (!isCLASSsame($1,$3))
              printf("Line %5i: SYNTAX ERROR: Relational operators allowed only between\n\t\t identifiers or constants of the same class\n",lineno);
          else
              if ( ($1.type==BOOLEAN && $3.type==BOOLEAN)||($1.type==INTEGER && $3.type==INTEGER) )
                  $$.type=BOOLEAN;
              else
              {
                  printf("Line %5i: SYNTAX ERROR: Relational operators allowed only between\n\t\t integers or boolean constants\n",lineno);
                  $$.type=BOOLEAN;
              }

          $$.type=BOOLEAN;
          sprintf($$.name,"$%i",buff++);
          genQUAD($2.name,$1.name,$3.name,$$.name);
        } 
        ;


rel_op:  LES        {strcpy($$.name,"LT");}
        | LEQ       {strcpy($$.name,"LE");}
        | EQ        {strcpy($$.name,"EQ");}
        | GT        {strcpy($$.name,"GT");}
        | GE        {strcpy($$.name,"GE");}
        | NEQ       {strcpy($$.name,"NE");}
        ;


formal_par_list: OPENPAR CLOSEPAR
        | OPENPAR formal_rec CLOSEPAR
        | OPENPAR formal_rec error SEMI     {syntax_error(18);}
        ;

formal_rec: var_decl
        | TOKVAR var_decl
        | formal_rec TOKVAR var_decl
        | formal_rec var_decl
        ;


%%

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


