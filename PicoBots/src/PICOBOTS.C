/* -----------------------------------------------------------------------

	Project: PICOBOTS
	Package: (main)
	Module:  picobots.c

	Version: 0.13 (alpha)

	Inputs:  (see source code - global defs)

	Output:  (see source code - main loop)

	Author: Harris Georgiou (c) 2016

   ----------------------------------------------------------------------- */


/* ----------  GLOBAL INCLUDES  ---------- */
#include <limits.h>
#include <float.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#if		defined(MSDOS)||defined(_MSDOS)||defined(__MSDOS__)
#define		_IS_MSDOS				1
#endif

#ifdef		_IS_MSDOS
#include <alloc.h>		/* used for coreleft() */
#endif

/* ----------  GLOBAL DEFINES  ---------- */

/*... comment this to avoid main() inclusion ...*/
#define		_PBOTS_STANDALONE		1

#ifndef		_PBOTS_STANDALONE
#define		_PBOTS_H				1
#endif

#define		_VER_MAJOR				0
#define		_VER_MINOR				13
#define		_VER_LABEL				"2017.12.24-Alpha-T64K"

#ifdef		__STDC__
#define		_VER_CODE				"(ANSI C)"
#else
#define		_VER_CODE				"(generic C)"
#endif

#define		_PBOTS_COPYRIGHT		"Copyright (c) 2017 by Harris Georgiou - http://xgeorgio.info"
#define		_PBOTS_LICENSE			"Licensed under Creative Commons (CC-BY-SA) v4.0i"

/*... common definitions (if not present) ...*/
#ifndef		FALSE
#define		FALSE		0
#define		TRUE		!FALSE
#endif

#ifndef		NULL
#define		NULL		0
#endif

/*** compatibility options for DOS/Unix definitions *
#if 	!defined(CLOCKS_PER_SEC) && defined(CLK_TCK)
#define 	CLOCKS_PER_SEC 			CLK_TCK
#elif	!defined(CLOCKS_PER_SEC) && !defined(CLK_TCK)
#define		CLOCKS_PER_SEC			1000000L
#endif
***/

/*... conditional code inclusions (implementation options) ...*/

/* Option: Use stdlib implementation of various math functions
   Code overhead (tiny model): sin(x) = +1606 bytes for
   stdlib (math.h) or +304 bytes for internal/approx implem.
   If undefined, use internal approximate sin(x) (slower). */
#define		_USE_MATH_STDLIB		1

/* Option: Use stdlib implementation of qsort()
   Code overhead (tiny model) = +385 bytes
   Note: May cause stack overflow in tiny model.
   If undefined, use internal selection sort (slower). */
/*** #define		_USE_QSORT_STDLIB		1 */

/* Option: Use stdlib implementation of bsearch()
   Code overhead (tiny model) = . (currently disabled)
   If undefined, use internal linear search (slower). */
/*** #define		_USE_BSEARCH_STDLIB		1 */

/* Option: Use high-quality PRNG engine (TT800-96)
   Code overhead (tiny model) = +502 bytes
   If undefined, use standard stdlib rand() */
#define		_USE_TTRAND_EXT			1

#ifdef		_USE_QSORT_STDLIB
#define		sort_modestr		"QSORT-STDLIB"
#else
#define		sort_modestr		"SSORT-INTRNL"
#endif

#ifdef		_USE_MATH_STDLIB
#define		math_modestr		"MATH-STDLIB"
#else
#define		math_modestr		"MATH-INTRNL"
#endif

/*... application-specific constants ...*/
/* Note: Current max working pool size = 55x25 bots (ver 0.05a)*/
#define		cScreenSizeX		29		/* use half the max column */
#define		cScreenSizeY        5		/* use max line number

#define		cUseBufferedIO		1       /* unset to use setvbuf()=0 */

#define		cUseDump			1		/* complete env/bots saves */

#ifdef		cUseDump
#define		cUseDumpEvery		100		/* env dump interval */
#define		cUseDumpMax			1		/* max saved env dumps to keep */
#endif

/*... platform-specific definitions ...*/
#define		cBotsN				(cScreenSizeX*cScreenSizeY)

#define		cPosPackBase		(ui16_t)cScreenSizeX
#define		mPosPack(r,c)		((r)*cPosPackBase+(c))  /* keep parentheses for correct eval */
#define		mPosRow(p)			((p) / cPosPackBase)
#define		mPosCol(p)			((p) % cPosPackBase)

#define		mBotID(r,c)			mPosPack(r,c)
#define		mBotRow(p)			mPosRow(p)
#define		mBotCol(p)			mPosCol(p)
#define		cBotID_NULL			ui16_max		/* empty-pos marker */

#define		mSpotID(r,c)		mPosPack(r,c)
#define		mSpotRow(p)			mPosRow(p)
#define		mSpotCol(p)			mPosCol(p)
#define		cSpotID_NULL		ui8_max	    	/* empty-pos marker */

#define     cSpotMax            ((TSpot)100)    /* translated to 'elevation' */
#define     cSpotMin            ((TSpot)0)
/*#define     cSpotNULL           ((TSpot)0)*/

/*... platform-specific typedefs ...*/
typedef		unsigned char		ui8_t;
typedef		unsigned short		ui16_t;
typedef		unsigned long       ui32_t;

typedef		signed char			si8_t;
typedef		signed short		si16_t;
typedef		signed long			si32_t;

typedef		float				real32_t;

#ifndef		USHRT_MIN
#define		USHRT_MIN			0
#endif

#define		ui8_bits			CHAR_BIT
#define		si8_bits			CHAR_BIT

#define		ui8_min				(ui8_t)UCHAR_MIN
#define		ui8_max				(ui8_t)UCHAR_MAX
#define		ui16_min			(ui16_t)USHRT_MIN
#define		ui16_max			(ui16_t)USHRT_MAX
#define		ui32_min			(ui32_t)ULONG_MIN
#define		ui32_max			(ui32_t)ULONG_MAX

#define		si8_min				(si8_t)SCHAR_MIN
#define		si8_max				(si8_t)SCHAR_MAX
#define		si16_min			(si16_t)SHRT_MIN
#define		si16_max			(si16_t)SHRT_MAX
#define		si32_min			(si32_t)LONG_MIN
#define		si32_max			(si32_t)LONG_MAX

#define		real32_min			(real32_t)FLT_MIN
#define		real32_max			(real32_t)FLT_MAX
#define		real32_eps			(real32_t)FLT_EPSILON

#ifndef		BOOL
#define		BOOL				ui8_t
#endif

/*... platform-specific macros ...*/
#define		mCircEast(x)		((x>1)?x-1:cScreenSizeX)
#define		mCircWest(x)		((x<cScreenSizeX)?x+1:1)
#define		mCircNorth(y)		((y>1)?y-1:cScreenSizeY)
#define		mCircSouth(y)		((y<cScreenSizeY)?y+1:1)

#define		mSwap(x,t,y)		{t=x;x=y;y=t;}

#define		cEnergyMin			ui16_min        /* bot energy ranges */
#define		cEnergyMax			(ui16_max-5)	/* keep top values for guards */
#define		cEnergy_NULL		ui16_max		/* empty-pos marker */
#define     mBot_isEmpty(p)     (Bots[p].en==cEnergy_NULL)

#define     cAmbientMin         ui16_min/100        /* ambient energy ranges */
#define		cAmbientMax			(ui16_max/100-5)	/* keep top values for guards */
#define		cAmbient_NULL		ui16_max/100		/* null-energy marker */

#define		cAgeMin				ui16_min        /* bot age ranges */
#define		cAgeMax				(ui16_max-5)    /* keep top values for guards */
#define		cAge_NULL		    ui16_max		/* null-age marker */

#define		mIsOdd(x)			(x % 2)
#define		mIsEven(x)			!mIsOdd(x)
#define		mIsSameParity(x,y)	mIsEven(x+y)

/*... Q-Learning framework: Global actions ...*/
#define		QLA_ACTION_UNSET	255     /* set to a value out-of-range */
#define		QLA_ACTION_IDLE		0       /* 'idle' is the baseline (zero) */
#define		QLA_ACTION_MOVE		QLA_ACTION_IDLE+1
#define		QLA_ACTION_GAME		QLA_ACTION_IDLE+2
#define		QLA_ACTION_MATE		QLA_ACTION_IDLE+3

#define		QLA_ACTIONS_N		4       /* last action ID +1 for 'idle' */

typedef		ui8_t				TActionID;
typedef		ui16_t				TProp;
typedef		ui16_t				TQPar;

#define		cPropMin			ui16_min
#define		cPropMax			ui16_max

typedef   struct qla_t {
		TProp		p[QLA_ACTIONS_N];
		TQPar		cfL, cfE, cfA, varA; }		Tqla;

/*... Q-Learning framework: Gaming actions ...*/
#define		QLG_ACTION_UNSET	255     /* set to a value out-of-range */
#define		QLG_ACTION_OPT0		0       /* '0' is the baseline (zero) */
#define		QLG_ACTION_OPT1		QLG_ACTION_OPT0+1

#define		QLG_ACTIONS_N		2       /* last action ID +1 for '0' */

typedef		ui16_t				TBotID;
typedef		ui8_t				TBotPos;

typedef		ui16_t				TAge;
typedef		ui16_t				TEnergy;

typedef   struct qlg_t {
		TProp		p[QLG_ACTIONS_N]; }	Tqlg;

/*... main framework data structures ...*/
typedef   struct Bot_t {		/* bot structure (core) */
		TAge		age;
		TEnergy		en;
		Tqla		act;
		Tqlg		play;	}	TBot;

typedef		ui8_t				TSpot;		/* environment spot */

/* ----------  GLOBAL VARIABLES  ---------- */

TBot 	* Bots;			/* main pool of bots */
TSpot 	* Spots;        /* main world matrix */
TBotID	* BotQ;         /* bots pqueue idx */
TActionID * avec;       /* used by: select_prop_action() */
TProp	* pvec;			/* used by: select_prop_action() */
TBotPos * BotA, * bAsz;   /* used by: bot_generate_qla_actions() */

ui8_t   * scrbuff;      /* screen buffer */
ui16_t	mem_alloc, env_age, env_ambient;
ui32_t	env_epoch;
time_t	boottime, laptime;

/* ----------  ERROR-HANDLING FUNCTIONS  ---------- */

#define		_ERR_NONE				0

#define		_ERR_WARN_0				10
#define		_ERR_W_INVPROPTYPE		_ERR_WARN_0+1
#define     _ERR_W_MEMNOTINIT       _ERR_WARN_0+2

#define		_ERR_FATAL_0			100
#define		_ERR_F_OUTOFMEMORY		_ERR_FATAL_0+1
#define		_ERR_F_BDATAEMPTY		_ERR_FATAL_0+2
#define		_ERR_F_BQUEUEMPTY       _ERR_FATAL_0+3
#define		_ERR_F_SDATAEMPTY		_ERR_FATAL_0+4

void env_shutdown( void );		/* forward declaration, needed here */

ui8_t	error_handler( ui8_t errtype, ui8_t exitlimit )
{
	switch (errtype)
	{
		case _ERR_NONE:
			printf("Error: None\n");
			break;
		case _ERR_WARN_0:
			printf("Warning: Unknown\n");
			break;
		case _ERR_W_INVPROPTYPE:
			printf("Warning: Invalid propensity vector type.\n");
			break;
		case _ERR_W_MEMNOTINIT:
			printf("Warning: Memory is not initialized.\n");
			break;
		case _ERR_FATAL_0:
			printf("Fatal Error: Unknown\n");
			break;
		case _ERR_F_OUTOFMEMORY:
			printf("Fatal Error: Out of memory\n");
			break;
		case _ERR_F_BDATAEMPTY:
			printf("Fatal Error: Bots container empty.\n");
			break;
		case _ERR_F_BQUEUEMPTY:
			printf("Fatal Error: Bots queue empty.\n");
			break;
		case _ERR_F_SDATAEMPTY:
			printf("Fatal Error: Spots container empty.\n");
			break;
		default:
			printf("Error: Unknown\n");
			/*break;*/
	}

	if (errtype>exitlimit)
	{
		env_shutdown();
		exit(errtype);
	}

	return(errtype);
}


/* ----------  GENERAL MATH FRAMEWORK (BUILT-IN APPROX)  ---------- */

#ifdef         _USE_MATH_STDLIB

#include <math.h>
#define        sinx(x)          sin(x)

#else

#define        cFactN3                6         /* 3! = 1*2*3 = 6 */
#define        cFactN5                120       /* 5! = 3!*4*5 = 120 */
#define        cFactN7                5040L     /* 7! = 5!*6*7 = 5040 */

real32_t       sinx_apr( real32_t x )
{
	/* spare some stack memory (16 bytes) for faster calculations */
    real32_t    x2, x3, x5, x7;

    x2=x*x;  x3=x*x2;
    x5=x3*x2;  x7=x5*x2;

    return( x - x3/cFactN3 + x5/cFactN5 - x7/cFactN7 );
}
#define       sinx(x)           sinx_apr(x)

#endif

#define       mAbs(x)           ((x<0)?-x:x)
#define		  mMax(x,y)			((x>=y)?x:y)
#define		  mMin(x,y)			((x<=y)?x:y)

#ifndef       _PI
#define       _PI               ((real32_t)3.1415926535)
#endif

/* ----------  RANDOM NUMBER GENERATOR  ---------- */

#ifdef		_USE_TTRAND_EXT

/*
   This is an adaptation of the TT800 implementation for strong
   PRNG functions with fast and small-fingerprint code:
   ----------

   C-program for TT800 : July 8th 1996 Version
   by M. Matsumoto, email: m-mat @ math.sci.hiroshima-u.ac.jp
   Copyright (C) 1996, Makoto Matsumoto - All rights reserved.

   genrand() generate one pseudorandom number with double precision
   which is uniformly distributed on [0,1]-interval for each call.
   One may choose any initial 25 seeds except all zeros.

   See: ACM Transactions on Modelling and Computer Simulation,
   Vol. 4, No. 3, 1994, pages 254-266.
*/

#define		rand_N 		25
#define 	rand_M 		7

int		rand_k = 0;
unsigned long 	rand_x[rand_N]={ /* initial 25 seeds, change as you wish */
	0x95f24dabL, 0x0b685215L, 0xe76ccae7L, 0xaf3ec239L, 0x715fad23L,
	0x24a590adL, 0x69e4b5efL, 0xbf456141L, 0x96bc1b7bL, 0xa7bdf825L,
	0xc1de75b7L, 0x8858a9c9L, 0x2da87693L, 0xb657f9ddL, 0xffdc8a9fL,
	0x8121da71L, 0x8b823ecbL, 0x885d05f5L, 0x4e20cd47L, 0x5a9ad5d9L,
	0x512c0c03L, 0xea857ccdL, 0x4cc1d30fL, 0x8891a8a1L, 0xa6b7aadbL  };

unsigned long rand_mag01[2]={  /* this is magic vector `a', don't change */
    0x0L, 0x8ebfd028L  };

double genrand( void )
{
	unsigned long y;

	if (rand_k==rand_N)  /* generate N words at one time */
	{
		int kk;
		for (kk=0;kk<rand_N-rand_M;kk++)
		{
			rand_x[kk] = rand_x[kk+rand_M] ^ (rand_x[kk] >> 1) ^ rand_mag01[(int)(rand_x[kk] % 2)];
		}
		for (; kk<rand_N;kk++)
		{
			rand_x[kk] = rand_x[kk+(rand_M-rand_N)] ^ (rand_x[kk] >> 1) ^ rand_mag01[(int)(rand_x[kk] % 2)];
		}
		rand_k=0;
    }

	y = rand_x[rand_k];
    y ^= (y << 7) & 0x2b5b2500L; 	/* s and b, magic vectors */
    y ^= (y << 15) & 0xdb8b0000L; 	/* t and c, magic vectors */
    y &= 0xffffffffL; 	/* you may delete this line if word size = 32 */
    y ^= (y >> 16);		/* added to the 1994 version */
	rand_k++;

	return( (double)y / (unsigned long)0xffffffffL );
}

#define			randf()			((real32_t)genrand())
#define			rand_modestr	"TT800-96"
#else
#define			randf()			((real32_t)rand()/RAND_MAX)
#define			rand_modestr	"STDLIB"
#endif

real32_t	rand_init( const time_t currtime )
{
	unsigned int    rc;
	real32_t	    tmp;

#ifdef		_USE_TTRAND_EXT
#define		rand_init_loops		rand_N*25+13	/* use at least rand_N for proper init */
	/* seed = mask internal pool with given clock */
	for ( rc=0; rc<rand_N; rc++ )
        rand_x[rc]=rand_x[rc]^(unsigned long)currtime;
#else
#define		rand_init_loops		3*25+13			/* arbitrary value, can be 0 (disabled) */
	/* seed = higher bits of current clock */
	srand((unsigned int)(currtime % UINT_MAX));
#endif
	for ( rc=0; rc<rand_init_loops; rc++ )  tmp=randf();
        /*{ tmp=randf(); printf("%g ",tmp); }
    printf("\n");*/

	return(tmp);
}


/* ----------  DYNAMIC MEMORY MANAGEMENT  ---------- */

#define		ACTIONS_MAX			((QLA_ACTIONS_N>QLG_ACTIONS_N)?QLA_ACTIONS_N:QLG_ACTIONS_N)

ui16_t	mem_init( void )
{
    /* allocate main data pools */
	if ((Bots=(TBot*)malloc(cBotsN*sizeof(TBot)))==NULL)
		error_handler(_ERR_F_OUTOFMEMORY,_ERR_FATAL_0);
	else if ((Spots=(TSpot*)malloc(cBotsN*sizeof(TSpot)))==NULL)
		error_handler(_ERR_F_OUTOFMEMORY,_ERR_FATAL_0);
	else if ((BotQ=(TBotID*)malloc(cBotsN*sizeof(TBotID)))==NULL)
		error_handler(_ERR_F_OUTOFMEMORY,_ERR_FATAL_0);
	else if ((BotA=(TBotPos*)malloc((QLA_ACTIONS_N-1)*8*sizeof(TBotPos)))==NULL)
		error_handler(_ERR_F_OUTOFMEMORY,_ERR_FATAL_0);
	else if ((bAsz=(TBotPos*)malloc((QLA_ACTIONS_N-1)*sizeof(TBotPos)))==NULL)
		error_handler(_ERR_F_OUTOFMEMORY,_ERR_FATAL_0);
	else if ((pvec=(TProp*)malloc(ACTIONS_MAX*sizeof(TProp)))==NULL)
		error_handler(_ERR_F_OUTOFMEMORY,_ERR_FATAL_0);
	else if ((avec=(TActionID*)malloc(ACTIONS_MAX*sizeof(TActionID)))==NULL)
		error_handler(_ERR_F_OUTOFMEMORY,_ERR_FATAL_0);
	else if ((scrbuff=(ui8_t*)malloc(cScreenSizeY*cScreenSizeX*sizeof(ui8_t)))==NULL)
		error_handler(_ERR_F_OUTOFMEMORY,_ERR_FATAL_0);

    /* add various global vars sizes */
	mem_alloc = cBotsN*(sizeof(TBot)+sizeof(TSpot)+sizeof(TBotID)); /* Bots[], Spots[], BotQ[] */
    mem_alloc += ACTIONS_MAX*(sizeof(TProp)+sizeof(TActionID)); /* avec[], pvec[] */

    mem_alloc += (QLA_ACTIONS_N-1)*(8+1)*sizeof(TBotPos); /* BotA[], bAsz[] */
    mem_alloc += cScreenSizeY*cScreenSizeX*sizeof(ui8_t);  /* scrbuff[] */
    mem_alloc += 3*sizeof(ui16_t);  /* env_age, env_ambient, mem_alloc */
    mem_alloc += 1*sizeof(ui32_t);  /* env_epoch */
    mem_alloc += 2*sizeof(time_t);  /* boottime, laptime */

#ifdef		rand_N
    mem_alloc += (rand_N+2)*sizeof(unsigned long); /* rand_x[], rand_mag01[] */
    mem_alloc += 1*sizeof(int);  /* rand_k */
#endif

	return(mem_alloc);
}

void	mem_cleanup( void )
{
	if (Bots!=NULL)   free(Bots);
	if (Spots!=NULL)  free(Spots);
	if (BotQ!=NULL)   free(BotQ);
    if (BotA!=NULL)   free(BotA);
	if (bAsz!=NULL)   free(bAsz);
	if (pvec!=NULL)   free(pvec);
	if (avec!=NULL)   free(avec);
	if (scrbuff!=NULL)  free(scrbuff);

	mem_alloc=0;
}


/* ----------  BOTS FRAMEWORK  ---------- */

#define         cInitEnergyLimit          0.5

void	bot_init( TBotID botid )
{
	Bots[botid].age=cAgeMin;
	Bots[botid].en=(TEnergy)((cEnergyMax-cEnergyMin)*randf()*cInitEnergyLimit+cEnergyMin);
}

TActionID	select_prop_action( TActionID maxid, BOOL flag_rnd )
{
	/* using global pvec[] as values vector */
	TActionID	i;
	ui32_t		sum, idx, slack=0;

	if (flag_rnd)
	{
		/* calculate the current sum of propensities */
		for ( sum=0,i=0; i<maxid; i++ )
            if ((avec[i]!=QLA_ACTION_UNSET)&&(avec[i]!=QLG_ACTION_UNSET))
               sum=sum+pvec[i];

		/* cdf-based non-uniform random selection */
		idx=randf()*sum; /* sel=(sum-0)/(1.0-0.0)*(rndf-0.0)+0 */

		printf("sum=%lu idx=%lu\n",sum,idx);

		/* translate selection into action ID */
		for ( sum=0,i=0; i<maxid; i++ )
		{
            if ((avec[i]!=QLA_ACTION_UNSET)&&(avec[i]!=QLG_ACTION_UNSET))
				sum=sum+pvec[i];
			else
				slack++;	/* compensate for jumps due to 'unset' conditions */
			
			if (sum>=idx)  break;
		}
		idx=i+slack;
	}
	else	/* deterministic (max) selection of action */
	{
		/* locate max-propensity action */
		for ( idx=0,i=0; i<maxid; i++ )
			if ((avec[i]!=QLA_ACTION_UNSET)&&(avec[i]!=QLG_ACTION_UNSET)&&(pvec[i]>pvec[(TActionID)idx]))
               idx=i;   /* already skipping 'unset' conditions */

	}
	i=(TActionID)idx;

	return(i);
}

/* Global energy thresholds (min available) for each action */
#define         cMaxTiltMove        (TSpot)((cSpotMax-cSpotMin)*0.15)       /* large => more mobility */
#define         cMoveEnergyLimit    (TEnergy)((cEnergyMax-cEnergyMin)*0.05)
#define         cGameEnergyLimit    (TEnergy)((cEnergyMax-cEnergyMin)*0.10)
#define         cMateEnergyLimit    (TEnergy)((cEnergyMax-cEnergyMin)*0.15)

void      bot_generate_qla_actions( TBotID botid )
{
    TBotPos    r, c, rn, rs, ce, cw, i;
    TBotID     tmpid[8];

    /* generate valid actions in 3x3 neighborhood */
    /* Note: spare some stack space instead of multiple macro-inline code */
    r=mBotRow(botid);  c=mBotCol(botid);
    rn=mCircNorth(r);  rs=mCircSouth(r);
    ce=mCircEast(c);   cw=mCircWest(c);

    tmpid[0] = mSpotID(rn,ce);    /* NE corner, work clockwise */
    tmpid[1] = mSpotID(rn,c);
    tmpid[2] = mSpotID(rn,cw);
    tmpid[3] = mSpotID(r,ce);
    tmpid[4] = mSpotID(r,cw);
    tmpid[5] = mSpotID(rs,ce);
    tmpid[6] = mSpotID(rs,c);
    tmpid[7] = mSpotID(rs,cw);

    /* Note: QLA_ACTION_IDLE is always available at current pos */
    /* Assumed actions list:
       QLA_ACTIONS_N=4 / (QLA_ACTION_UNSET=-1, QLA_ACTION_IDLE=0)
       -> QLA_ACTION_MOVE=1, QLA_ACTION_GAME=2, QLA_ACTION_MATE=3 */
    for ( i=0; i<8; i++ )
    {
        BotA[(QLA_ACTION_MOVE-1)*8+i]=QLA_ACTION_UNSET;    /* 1st segment  (0...7): 'move' */
        BotA[(QLA_ACTION_GAME-1)*8+i]=QLA_ACTION_UNSET;    /* 2nd segment (8...15): 'game' */
        BotA[(QLA_ACTION_MATE-1)*8+i]=QLA_ACTION_UNSET;    /* 3rd segment (16..23): 'mate' */
    }
    bAsz[QLA_ACTION_MOVE-1]=0;
    bAsz[QLA_ACTION_GAME-1]=0;
    bAsz[QLA_ACTION_MATE-1]=0;

    for ( i=0; i<8; i++ )
    {
        /* evaluate action: QLA_ACTION_MOVE */
        /* constraint: tilt must be <= max allowable */
        if ( (mAbs(Spots[botid]-Spots[tmpid[i]])<=cMaxTiltMove) && (Bots[botid].en>=cMoveEnergyLimit) )
        {
           BotA[(QLA_ACTION_MOVE-1)*8+i]=QLA_ACTION_MOVE;
           bAsz[QLA_ACTION_MOVE-1]++;
        }

        /* evaluate action: QLA_ACTION_GAME */
        /* constraint: bot must be present (non-empty spot) */
        if ( (!mBot_isEmpty(tmpid[i])) && (Bots[botid].en>=cGameEnergyLimit) )
        {
           BotA[(QLA_ACTION_GAME-1)*8+i]=QLA_ACTION_GAME;
           bAsz[QLA_ACTION_GAME-1]++;
        }

        /* evaluate action: QLA_ACTION_MATE */
        /* constraint: bot must be present (non-empty spot) */
        if ( (!mBot_isEmpty(tmpid[i])) && (Bots[botid].en>=cMateEnergyLimit) )
        {
           BotA[(QLA_ACTION_MATE-1)*8+i]=QLA_ACTION_MATE;
           bAsz[QLA_ACTION_MATE-1]++;
        }
    }
}

TActionID	bot_select_qla_action( TBotID botid, BOOL flag_rnd )
{
	TActionID	i;

	/* calculate the current sum of propensities */
    /* TODO: check bAsz[] for valid actions, fill-in
       avec[] and pvec[], prepare for spot-selection */
	for ( i=0; i<QLA_ACTIONS_N; i++ )
    {
        avec[i]=QLA_ACTION_MOVE;    /* <= TEST: to be removed, defined prior */
		pvec[i]=Bots[botid].act.p[i];
    }
    /*avec[1]=QLA_ACTION_UNSET;*/       /* <= TEST: random 'null' in actions */

	return(select_prop_action(QLA_ACTIONS_N,flag_rnd));
}

TActionID	bot_select_qlg_play( TBotID botid, BOOL flag_rnd )
{
	TActionID	i;

	/* calculate the current sum of propensities */
    /* TODO: check bAsz[] for valid actions, fill-in
       avec[] and pvec[], prepare for post-processing */
	for ( i=0; i<QLG_ACTIONS_N; i++ )
    {
        avec[i]=QLG_ACTION_OPT0;    /* <= TEST: to be removed, defined prior */
		pvec[i]=Bots[botid].play.p[i];
    }
    /*avec[1]=QLA_ACTION_UNSET;*/       /* <= TEST: random 'null' in actions */

	return(select_prop_action(QLG_ACTIONS_N,flag_rnd));
}


/* ----------  ENVIRONMENT FRAMEWORK  ---------- */

TBotID	env_bots_init( void )
{
	TBotID		p;

	for ( p=0; p<cBotsN; p++ )	bot_init(p);

	return(cBotsN);
}

#define         ENV_SMLOOP_N        3

void    env_generate_world( void )
{
    si8_t    count;      /* Note(!): must keep signed if ENV_SMLOOP_N=0 for 'for' */
    TBotPos  r, rn, rs, c, ce, cw;
    TBotID   i;
    ui32_t   sum;
    TSpot    * tmpSpots;     /* temp buffer, no global decl (one-time use) */

    /* Note: memory should already be initialized */
    if ((tmpSpots=(TSpot*)malloc(cBotsN*sizeof(TSpot)))==NULL)
		error_handler(_ERR_F_OUTOFMEMORY,_ERR_FATAL_0);
    else if (mem_alloc==0)
		error_handler(_ERR_W_MEMNOTINIT,_ERR_FATAL_0);
    else
    {
        printf(".");
        /* fill the area with uniform random [min...max] values */
        for ( r=0; r<cScreenSizeY; r++ )
            for ( c=0; c<cScreenSizeX; c++ )
            {
                /* initialize plane with random elevations */
                Spots[mSpotID(r,c)]=(TSpot)((cSpotMax-cSpotMin)*randf()+cSpotMin);
                /* initialize bots in main pool with random energies */
                Bots[mBotID(r,c)].en=(TEnergy)((cEnergyMax-cEnergyMin)*randf()+cEnergyMin);
            }
        /* iterative smoothing loop */
        for ( count=0; count<ENV_SMLOOP_N; count++ )
        {
            printf(".");
            /* perform smoothing by 3x3 avg mask */
            for ( r=0; r<cScreenSizeY; r++ )
                for ( c=0; c<cScreenSizeX; c++ )
                {
                    rn=mCircNorth(r);  rs=mCircSouth(r);
                    ce=mCircEast(c);   cw=mCircWest(c);

                    sum =  Spots[mSpotID(rn,ce)];
                    sum += Spots[mSpotID(rn,c)];
                    sum += Spots[mSpotID(rn,cw)];
                    sum += Spots[mSpotID(r,ce)];
                    sum += Spots[mSpotID(r,c)];
                    sum += Spots[mSpotID(r,cw)];
                    sum += Spots[mSpotID(rs,ce)];
                    sum += Spots[mSpotID(rs,c)];
                    sum += Spots[mSpotID(rs,cw)];

                    tmpSpots[mSpotID(r,c)]=(TSpot)(sum/9);
                }

            /* copy result (smoothed) to main pool before next loop, check for overflows */
            for ( i=0; i<cBotsN; i++ )  Spots[i]=((tmpSpots[i]<=cSpotMax)?tmpSpots[i]:cSpotMax);
        }

        free(tmpSpots);
    }
}

#define     ASCII_CHAR_0            ((ui8_t)'0')
#define     ASCII_CHAR_a            ((ui8_t)'a')
#define     ASCII_CHAR_A            ((ui8_t)'A')

#define     ASCII_CHAR_NULL         ((ui8_t)'.')
#define     ASCII_CHAR_IDLE         ((ui8_t)'%')
#define     ASCII_CHAR_MOVE         ((ui8_t)'&')
#define     ASCII_CHAR_GAME         ((ui8_t)'#')
#define     ASCII_CHAR_MATE         ((ui8_t)'@')

#define     mSpot2Char(n)           ((ui8_t)(ASCII_CHAR_0+n))
#define     mBot2LChar(n)           ((ui8_t)(ASCII_CHAR_a+n))
#define     mBot2UChar(n)           ((ui8_t)(ASCII_CHAR_A+n))

void    env_display_world( void )
{
    TBotPos  r, c;
    ui16_t   p, b;

    printf("\n");
    for ( r=0; r<cScreenSizeY; r++ )
    {
        for ( c=0; c<cScreenSizeX; c++ )
        {
            /* Note: keep intermediate operations with 'long' to avoid overflows */
            /* translate current spot value to char '0-9' and display ASCII: '9'-'0' = 57-48 = 9 */
            p=(ui16_t)((Spots[mSpotID(r,c)]-cSpotMin)*9.0/(cSpotMax-cSpotMin));
			/*if (p>9)
                printf("(r,c)=(%u,%u) => [%u]=%u => [[%u]]='%c'\n",r,c,mSpotID(r,c),Spots[mSpotID(r,c)],p,mSpot2Char(p));*/

            /* translate current bot energy value to char 'a-z' and display ASCII: 'z'-'a' = 122-97 = 25 , 'Z'-'A' = 90-65 = 25 */
            b=(ui16_t)((Bots[mBotID(r,c)].en-cEnergyMin)*25.0/(cEnergyMax-cEnergyMin));
            /*if (b>25)
				printf("Bot(r,c)=(%u,%u) => [%u]=%u => [[%u]]='%c'\n",r,c,mBotID(r,c),Bots[mSpotID(r,c)].en,b,mBot2UChar(b));*/

            printf("%c%c",mSpot2Char((TBotPos)p),mBot2LChar((TBotPos)b));
        }
        printf("\n");
    }
}

void    env_display_scrbuff( void )
{
    TBotPos   r, c;

    printf("\n");
    for ( r=0; r<cScreenSizeY; r++ )
    {
        for ( c=0; c<cScreenSizeX; c++ )
            printf("%c",scrbuff[mSpotID(r,c)]);
        printf("\n");
    }
}

void    env_clear_scrbuff( void )
{
    TBotPos   r, c;

    for ( r=0; r<cScreenSizeY; r++ )
        for ( c=0; c<cScreenSizeX; c++ )
            scrbuff[mSpotID(r,c)]=ASCII_CHAR_NULL;
}

#define         cAmbientLowLimit          0.05      /* no ambient energy below that % */

TEnergy     env_spot_ambient( TBotID sid )
{
    real32_t    c;

    /* convert env.age to 0...1 */
    c=((real32_t)env_age-cAgeMin)/(cAgeMax-cAgeMin);
    /* apply periodic transition, then return to 0...1 */
    c=(2*c-1)*_PI;     /* map: [0,1] -> [-pi,+pi] */
    c=(sinx(c+_PI/2)+1)/2;     /* add phase for: env_age=0 => c=0 */
    /* adjust for current spot elevation, keep in 0...1 */
    c=((real32_t)Spots[sid]-cSpotMin)/(cSpotMax-cSpotMin)*c;
    /* check if ambient lower than limit */
    if (c<cAmbientLowLimit)  c=0;
    /* finally convert to ambient range */
    return( (TEnergy)((cAmbientMax-cAmbientMin)*c+cAmbientMin) );
}

void	env_init( void )
{
	real32_t	tt;

	printf("PBenv: Initializing...\n");
	mem_init();
	printf("PBenv: Using %s sorting, %s math lib, %s prng engine.\n",sort_modestr,math_modestr,rand_modestr);
	printf("PBenv: Dynamic memory allocated = %u bytes\n",mem_alloc);
	printf("PBenv: Created %u picobots in pool.\n",env_bots_init());
	env_age=0;
    env_ambient=0;
	env_epoch=0;
    laptime=0;

	boottime=time(NULL);
	tt=rand_init(boottime);
	printf("PBenv: PRNG initialized (lastrnd=%g)\n",tt);

	printf("PBenv: Generating world (%ux%u)",cScreenSizeY,cScreenSizeX);
    env_generate_world();
    /*env_display_world();*/

	printf("\n\nPBenv: Kernel started successfully, %s\n",ctime(&boottime));
}

void	env_shutdown( void )
{
	printf("\nPBenv: Shutting down...\n");
	mem_cleanup();
}

#if		defined(_USE_QSORT_STDLIB)||defined(_USE_BSEARCH_STDLIB)
int		BotQ_compare( const void *v1, const void *v2 )
{
	if ( *(TBotID*)v1 < *(TBotID*)v2 ) return(-1);
	else if ( *(TBotID*)v1 > *(TBotID*)v2 ) return(1);
	else return(0);
}
#endif

void	env_bqueue_createsorted( void )
{
#ifndef		_USE_QSORT_STDLIB
	TBotID		mx, t, top;
#endif
	TBotID		p;

	if (!BotQ)  error_handler(_ERR_F_BQUEUEMPTY,_ERR_FATAL_0);

	/* initialize vector with relevant values (unsorted) */
	for ( p=0; p<cBotsN; p++ )  BotQ[p]=Bots[p].en;

#ifdef		_USE_QSORT_STDLIB
	qsort(BotQ,cBotsN,sizeof(TBotID),BotQ_compare);
#else
	/* sort vector, selection sort O(N*N) */
	for ( top=0; top<cBotsN; top++ )
	{
		for ( mx=top,p=top+1; p<cBotsN; p++ )
			if (BotQ[p]<BotQ[mx]) mx=p;

   		if (top!=mx) mSwap(BotQ[top],t,BotQ[mx]);
	} /* end selection sort */
#endif
}

/***
BOOL	env_bqueue_exists( ui16_t botid )
{
#ifndef		_USE_BSEARCH_STDLIB
	*** standard linear search, O(N) *
	TBotID		p;
	for ( p=0; p<cBotsN; p++ )
		if (BotQ[p]==botid)  return(TRUE);
	return(FALSE);
#else
	*** binary search (assumed sorted), O(N.logN) *
	*** for full pos info, BotQ needs to be two-field record vector *
	if (bsearch(&botid,BotQ,cBotsN,sizeof(TBotID),BotQ_compare))
		return(TRUE);
	else  return(FALSE);
#endif
}
***/

BOOL	env_bots_hasplayed( TBotPos row, TBotPos col )
{
	return( mIsSameParity( Bots[mBotID(row,col)].age, env_age ) );
}

void	show_app_info( void )
{
	printf("PICOBOTS v%d.%02d (%s) - Tiny model variant %s\n%s\n%s\n\n",_VER_MAJOR,_VER_MINOR,_VER_LABEL,_VER_CODE,_PBOTS_COPYRIGHT,_PBOTS_LICENSE);
}


/* ----------  MAIN ROUTINE (STANDALONE MODE)  ---------- */
#ifdef		_PBOTS_STANDALONE

/*int main( int argc, char *argv[] )*/
int main( void )
{
	TBotID		bid;
	TActionID	aid;

	show_app_info();
#ifdef		_IS_MSDOS
	printf("Heap memory available: %u\n\n",coreleft());
#endif

	env_init();
    env_bots_init();

	/*... testing action-selection functions ...***/
	bid=5;
	for (aid=0;aid<QLA_ACTIONS_N;aid++) Bots[bid].act.p[aid]=cPropMax*randf()+cPropMin;
	for (aid=0;aid<QLG_ACTIONS_N;aid++) Bots[bid].play.p[aid]=cPropMax*randf()+cPropMin;

	printf("bot %u: QLA={ ",bid);
	for (aid=0;aid<QLA_ACTIONS_N;aid++) printf("%u ",Bots[bid].act.p[aid]);
	printf("}  QLG={ ");
	for (aid=0;aid<QLG_ACTIONS_N;aid++) printf("%u ",Bots[bid].play.p[aid]);
	printf("}\n");

	aid=bot_select_qla_action(bid,FALSE);  printf("\tQLA action: maxID=%u ",aid);
	aid=bot_select_qla_action(bid,TRUE);   printf("\t\trndID=%u\n",aid);

	aid=bot_select_qlg_play(bid,FALSE);  printf("\tQLG play: maxID=%u ",aid);
	aid=bot_select_qlg_play(bid,TRUE);   printf("\t\trndID=%u\n",aid);

	printf("TEST: env_bqueue_createsorted()\n");
    env_bqueue_createsorted();

	printf("TEST: bot_generate_qla_actions()\n");
    bot_generate_qla_actions(bid);
    printf("BotA{move}:\t%d %d %d %d %d %d %d %d : (sz=%d)\n",BotA[0],BotA[1],BotA[2],BotA[3],BotA[4],BotA[5],BotA[6],BotA[7],bAsz[0]);
    printf("BotA{game}:\t%d %d %d %d %d %d %d %d : (sz=%d)\n",BotA[8],BotA[9],BotA[10],BotA[11],BotA[12],BotA[13],BotA[14],BotA[15],bAsz[1]);
    printf("BotA{mate}:\t%d %d %d %d %d %d %d %d : (sz=%d)\n\n",BotA[16],BotA[17],BotA[18],BotA[19],BotA[20],BotA[21],BotA[22],BotA[23],bAsz[2]);

	printf("TEST: env_spot_ambient()\n");
    printf("ambient energy (env.age=%u): %u\n",env_age,env_spot_ambient(bid));
    env_age=(TAge)(cAgeMax*randf());
    printf("ambient energy (env.age=%u): %u  [%u...%u]\n",env_age,env_spot_ambient(bid),cAmbientMin,cAmbientMax);
    printf("TEST: sin(-pi)=%g , sin(0)=%g , sin(+pi)=%g , sin(randf())=%g\n",sinx(-_PI),sinx(0),sinx(_PI),sinx(randf()));

    laptime=time(NULL)-boottime+1;
	printf("PBenv: Processing speed is %g picobots per second.\n",cBotsN/(double)laptime);

    env_clear_scrbuff();
    env_display_scrbuff();
	printf("\n");
	env_display_world();
#ifdef		_IS_MSDOS
	printf("Heap memory available: %u\n\n",coreleft());
#endif

	env_shutdown();

#ifdef		_IS_MSDOS
	printf("Heap memory available: %u\n\n",coreleft());
#endif

	return(0);
}

#endif
