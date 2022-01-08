/*
	--------------------------------------------
		MINISQL v1.0
		Header File

		This file defines all necessary
		constants and data types that
		are used in main program.
	--------------------------------------------
*/

#define		_MINISQL_H

#include		<stdio.h>
#include		<stdlib.h>
#include		<string.h>
#include		<ctype.h>


#define		DEF_DATAFILE   "minisql.dat"

#define		ERR_NULL	0		/* No error */
#define		ERR_IO		-1		/* I/O error */
#define		ERR_MEM		-2		/* Memory error */
#define		ERR_PRM		-3		/* Invalid parameter(s) error */
#define		ERR_INV		-4		/* Invalid data error */
#define		ERR_FULL	-5		/* Out of memory error (array pool is full) */



#ifndef		MAXSTRLEN
#define		MAXSTRLEN		255
#endif

#define		MAXNAMELEN		15


#define		MAXRECNUM		100
#define		MAXFLDNUM		30
#define		MAXARRNUM		20


#define		FLD_NULL		0
#define		FLD_CHAR		1
#define		FLD_NUM			2

#define         DEC_POINTS              2

#ifndef		BYTE
typedef		unsigned char			BYTE;
#endif

typedef		char					TSTRING[ MAXSTRLEN ];

typedef		int					TARRNUM;
typedef		int					TFLDNUM;
typedef		int					TRECNUM;

typedef		char					TFLDNAME[ MAXNAMELEN ];
typedef		BYTE					TSTRPOS;
typedef		BYTE					TSTRLEN;
typedef		BYTE					TFLDTYPE;

typedef		struct {
				TFLDNAME		name;
				TSTRPOS		spos;
				TSTRLEN		len;
				TFLDTYPE		type;  }		TFIELDESC;

typedef		char					TARRNAME[ MAXNAMELEN ];
typedef		int					TARRNREC;
typedef		int					TARRNFLD;
typedef		TFIELDESC				TARRFLDS[ MAXFLDNUM ];

typedef		struct {
				TARRNAME		name;
				TARRNREC		numrecords;
				TARRNFLD		numfields;
				TARRFLDS		fields;  }	TARRDESC;

typedef		TSTRING				TARRDATA[ MAXRECNUM ];


typedef		struct {
				TARRDESC		desc;
				TARRDATA		data;  }		TARRAY;

typedef	     TARRAY						TARRPOOL[ MAXARRNUM ];



/* ----- Add some subprograms definition files (support code) ----- */

#include		"msql_fil.c"
#include		"msql_mem.c"
#include		"msql_gpr.c"



