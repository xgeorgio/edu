#include <stdio.h>
//#include <values.h>
#include <limits.h>
#include <float.h> 

#ifndef         _TYPES_H
#define         _TYPES_H

#define         MAX_NAME            128

/*****   Entry Data Types   *****/
#define         ERROR_TYPE          -1
#define         INTEGER             11
#define         CHAR                12
#define         BOOLEAN             13

/*****   Entry Class-ID   *****/
#define         STRING              21
#define         IDENT               22
#define         ARRAY               23
#define         FUNCT               24
#define         PROC                25

#include "entry.h"

#endif
