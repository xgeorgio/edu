/*        ******************************************************************
	  ***                                                            ***
	  ***         3rd-degree Spline Interpolation - Best fit         ***
	  ***         ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~         ***
	  ***                                                            ***
	  ******************************************************************



		DESCRIPTION:
									
			(See source code file description and on-line comments)



------------------------------------------------------------------------------
*/

#ifndef     _SPLINES_H
#define     _SPLINES_H

#include    <float.h>

typedef         double              TDATA;          /* basic data type */
typedef         unsigned int        TSIZE;          /* basic counter type */

#define         DEF_DXMINLIMIT      (TDATA)FLT_EPSILON      /* default DXmin */
#define         DEF_DXMAXLIMIT      (TDATA)1                /* default DXmax */



/*----------------------------------------------------------------*/


/***   Check DX values for a set of data (x,y)   ***
Parameters:   n = number N of data (i=0,1,...,N-1)
			x[] = data array of X
			dxminlimit = minimum allowed DX
			dxmaxlimit = maximum allowed DX
			*dx_min = minimum DX found
			*minpos = position of minimum DX in X array
			*dx_max = maximum DX found
			*maxpos = position of maximum DX in X array
			
			res=0  ==> valid values found
			res=-1 ==> constrains are not valid
			res=-2 ==> constrain for minimum DX not satisfied
			res=-3 ==> constrain for maximum DX not satisfied
*/
int check_dx_data( const TSIZE n, const TDATA *x, const TDATA dxminlimit, const TDATA dxmaxlimit,
				   TDATA *dx_min, TSIZE *minpos, TDATA *dx_max, TSIZE *maxpos );



/***   Check DY values for a set of data (x,y)   ***
Parameters:   n = number N of data (i=0,1,...,N-1)
			y[] = data array of X
			dx_min = minimum DX found previously
			dx_max = maximum DX found previously
			*y_projerr = projected Y error for 3rd-degree spline
			*sdigits = signifficant decimal digits for spline-Y (from error)
			
			res=0  ==> valid values found
			res=1  ==> negative sdigits value found (major Y error)
			res=-1 ==> DX values are not valid
*/
int check_dy_data( const TSIZE n, const TDATA *y, const TDATA dx_min,
					const TDATA dx_max, TDATA *y_projerr );



/***   Sort a set of (x,y) data according to (x)   ***
Notes:  We use "stdlib" function qsort(). We can sort by
		a temporary array_xy, but the compare and move costs
		are great. However, if we use array_xi for sorting
		and a newy array to adjust y-array after the (first)
		sort, we loose an array_n in space but we gain in
		speed during the sort. In any case, a O(N) factor is
		added to the O(NlogN) of the qsort() algorithm.

			  n = number of data (n=0,1,2,...N-1)
			x[] = data array for X
			y[] = data array for Y

			res=0 ==> array sorted correctly
			res=-1 ==> not enough memory (array unchanged)
*/
int sort_xy_data( const TSIZE n, TDATA *x, TDATA *y );



/***   Create 3rd-degree spline for a set of data (x,y)   ***
Parameters:   n = number N of data (i=0,1,...,N-1)
			x[] = data array of X
			y[] = data array of Y
			a[] = data array for A
			b[] = data array for B*(x-xi)
			c[] = data array for C*(x-xi)^2
			d[] = data array for D*(x-xi)^3

			res=1 ==> N<=1  (no calculation)
			res=2 ==> N==2  (linear interpolation)
			res=3 ==> N>=3  (normal mode)

Note:  |x[i+k]-x[i]|>EPS {k=1,2,3} , to avoid FP errors (divide by 0)
*/
int create_spline( const TSIZE n, const TDATA *x, const TDATA *y,
					TDATA *a, TDATA *b, TDATA *c, TDATA *d );



/***   Evaluate a 3rd-degree spline for a set of data (x,y)   ***
Parameters:   n = number N of data  (i=0,1,2,...,N-1)
			x[] = data array of X
			y[] = data array of Y
			a[] = data array for A      (Y can be used as input)
			b[] = data array for B*(x-xi)
			c[] = data array for C*(x-xi)^2
			d[] = data array for D*(x-xi)^3
			  u = point (x) where to evaluate spline

			res = evaluated value (may be from extra-polation)
*/
TDATA eval_spline( const TDATA u, const TSIZE n, const TDATA *x, const TDATA *a, 
					const TDATA *b, const TDATA *c, const TDATA *d );



/***   Calculate maximum error of spline S(x), given a set of data (x,y)   ***
Parameters:   sn = number M of spline nodes  (i=0,1,2,...,M-1)
			sx[] = spline data array of X
			 a[] = spline data array for A
			 b[] = spline data array for B*(x-xi)
			 c[] = spline data array for C*(x-xi)^2
			 d[] = spline data array for D*(x-xi)^3
			  tn = number N of given nodes  (i=0,1,2,...,N-1)
			 x[] = given data array of X
			 y[] = given data array of Y
	   
	   *y_splerr = maximum S(x) error found
*/
void calc_spline_diff( const TSIZE sn, const TDATA *sx, const TDATA *a,
						const TDATA *b, const TDATA *c, const TDATA *d,
						const TSIZE tn, const TDATA *tx, const TDATA *ty,
						TDATA *y_splerr );



/***   Create 3rd-degree spline with M nodes for a set of N data (x,y)   ***
Parameters:   tn = number N of given data (i=0,1,...,N-1)
			tx[] = given data array of X
			ty[] = given data array of Y
			  sn = requested M nodes for spline
			 a[] = data array for A
			 b[] = data array for B*(x-xi)
			 c[] = data array for C*(x-xi)^2
			 d[] = data array for D*(x-xi)^3
			*y_splerr = calculated maximum error (due to M<=N)

			res=-1 ==> Not enough memory
			res=-2 ==> Not valid M for N (M>N)
			res=1 ==> N<=1  (no calculation)
			res=2 ==> N==2  (linear interpolation)
			res=3 ==> N>=3  (normal mode)

Note:  |x[i+k]-x[i]|>EPS {k=1,2,3} , to avoid FP errors (divide by 0)
*/
int create_semi_spline( const TSIZE tn, const TDATA *tx, const TDATA *ty, 
						const TSIZE sn, TDATA *sx, TDATA *a, TDATA *b,
						TDATA *c, TDATA *d, TDATA *y_splerr );



/***   Create 3rd-degree spline for a set of N data (x,y), 
						given a maximum (total) error for S(x)    ***
Parameters:   tn = number N of given data (i=0,1,...,N-1)
			tx[] = given data array of X
			ty[] = given data array of Y
	y_int_splerr = maximum spline(3) interpolation error
		y_maxerr = requested maximum total S(x) error
			  sn = final (M) nodes used for spline
			  sx = final X data array for calculated S(x)
			 a[] = data array for A
			 b[] = data array for B*(x-xi)
			 c[] = data array for C*(x-xi)^2
			 d[] = data array for D*(x-xi)^3
	  *y_realerr = calculated maximum total error (<= y_maxerr)

			res=-1 ==> interpolation error already above requested (y_maxerr)
			res=1 ==> N<=1  (no calculation)
			res=2 ==> N==2  (linear interpolation)
			res=3 ==> N>=3  (normal mode)

Note:  |x[i+k]-x[i]|>EPS {k=1,2,3} , to avoid FP errors (divide by 0)
*/
int create_best_spline( const TSIZE tn, const TDATA *tx, const TDATA *ty,
						const TDATA y_int_splerr, const TDATA y_maxerr,
						TSIZE *sn, TDATA *sx, TDATA *a, TDATA *b, TDATA *c, 
						TDATA *d, TDATA *y_realerr );



#endif

