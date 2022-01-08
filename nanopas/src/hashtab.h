#include <stdio.h>
#include <ctype.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"


typedef     struct SYMBUFF {
    struct SYMBUFF   *next;
    struct SYMBUFF   **prev;
                        }  SYMBUFF;

typedef     struct hash_tab {
    int         size;
    int         cursymno;
    unsigned    (*hash)();
    int         (*cmp)();
    SYMBUFF      *table[1];
                        }  HASH_TAB;



int cmp( char *name, ENTRY *symbol )
{
    return( strcmp(name,symbol->name) );    /* case-sensitive var comparisons */
}


unsigned int hash( ENTRY *symbol )
{
    unsigned int    h;
    unsigned char   *tmp=symbol->name;

    for (h=0; *tmp; h+=*tmp++);
    return( h );
} 


void *new_symbol( int size )
{
    SYMBUFF      *b;
        
    if( !(b=(SYMBUFF *)calloc(sizeof(SYMBUFF) + size,1)) )
    {
        printf("Fatal Error: Out of memory\n");
        return( NULL );
    }

    return( (void *)(b + 1) );
}


void free_symbol( void *sym )
{
    free( (SYMBUFF *)sym - 1 );
}       


HASH_TAB *create_table( unsigned max_symbol, unsigned (*hash_fun)(), int (*cmp_fun)() )
{
    HASH_TAB    *p;
        

    if (!max_symbol)  max_symbol=127;
       
    if ( p=(HASH_TAB *)calloc(1,(max_symbol*sizeof(SYMBUFF *))+sizeof(HASH_TAB)) )
    {
        p->size = max_symbol;
        p->cursymno = 0;
        p->hash = hash_fun;
        p->cmp = cmp_fun;
    } 
    else 
    { 
        printf("Fatal Error: Cannot allocate memory for symbol table\n");
        return( NULL );
    }
        
    return( p );
}   

      
void *insert( HASH_TAB *tabp, void *isym )
{
    SYMBUFF      **p, *tmp;
    SYMBUFF      *sym=(SYMBUFF *)isym;


    p = &(tabp->table)[(*tabp->hash)(sym--) % tabp->size];

    tmp = *p;
    *p = sym;
    sym->prev = p;
    sym->next = tmp;

    if (tmp)  tmp->prev = &sym->next;
    tabp->cursymno++;

    return( (void *)(sym+1) );
}


void *lookupsymbol( HASH_TAB *tabp, void *lsym )
{
    SYMBUFF *p;
   

    if (!tabp)  return( NULL ); 
    p = (tabp->table)[(*tabp->hash)(lsym) % tabp->size];

    while (p && (*tabp->cmp)(lsym,p+1))
        p = p->next;

    return( (void *)(p ? p+1 : NULL) );
}


void *lookup( HASH_TAB *tabp, char *name )
{
    ENTRY   *tmp=(ENTRY *)new_symbol(sizeof(ENTRY));

    strcpy(tmp->name,name);
    return( (ENTRY *)lookupsymbol(tabp,tmp) );
}


void *delete( HASH_TAB *tabp, void *dsymbol )
{
    SYMBUFF *sym = (SYMBUFF *)dsymbol;
  
    if (tabp && sym)
    {
        --tabp->cursymno;
        --sym;
        if ( *(sym->prev) = sym->next )
            sym->next->prev = sym->prev;
    }
} 


int insert_to_table( HASH_TAB *tabp, char *name, int type, int class, int asize )
{
    ENTRY   *tmp;


    tmp = lookup(tabp,name);
    if (tmp)  return(1);

    tmp = (ENTRY *)new_symbol(sizeof(ENTRY));
    tmp->type = type;
    tmp->asize = asize;

    if (!class)
        tmp->class = IDENT;
    else
        tmp->class=class;

    strcpy(tmp->name,name);
    insert(tabp,tmp);
    return(0);
}



