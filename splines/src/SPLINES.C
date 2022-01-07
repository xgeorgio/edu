/*        ******************************************************************
	  ***                                                            ***
	  ***         3rd-degree Spline Interpolation - Best fit         ***
	  ***         ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~         ***
	  ***                                                            ***
	  ******************************************************************



		DESCRIPTION:

			This file contains all source code needed to implement
		  3rd-degree spline interpolation.

			The program defines all basic procedures to create and
		  evaluate splines for given X and Y data arrays. The evaluation
		  is made by continiously dividing X data until a x[i] is found
		  with requested x is:  x[i] <= x < x[i+1]  . So the X and Y data
		  arrays have to be sorted before S(x) is created. If requested
		  x is not in X array (out of interpolation data), extrapolation
		  is used to make an estimation of S(x).

			Furthermore, there are some other useful procedures that
		  complete the study for these splines. There is a procedure to
		  test if all DX values for the X data array satisfy certain minimum 
		  and maximum constrains. A procedure to make an estimation of the
		  interpolation error (linear to D(4)y) for any 3rd-degree spline
		  (which can be called "internal" S(x) error). A procedure to
		  calculate maximum the error of S(x) given a "more complete" set 
		  of XY data (which can be called "external" S(x) error). Also,
		  there is a procedure that creates a spline of M nodes given a
		  XY data set of N nodes, where M<=N.

			Finally, there is a general procedure that creates a spline
		  for a set of XY data, using the minimum number of data nodes
		  so that a maximum total S(x) error constraint is satisfied.
		  The success of this procedure depends on the size of XY data
		  set, the requested error constraint and of course the ability
		  to approximate the ("unknown") function f(x) with a 3rd-degree
		  spline S(x).


		NOTE: Some functions have internal "printf" instructions used when
			  a progress indicator is needed. When these functions are not
			  used during debugging, these instructions should be commented
			  or removed to avoid unexpected output in a "main" program.


------------------------------------------------------------------------------
*/

#ifndef     _SPLINES_C
#define     _SPLINES_C

#include    <stdlib.h>
#include    <math.h>
#include    <float.h>

typedef         double              TDATA;          /* basic data type */
typedef         unsigned int        TSIZE;          /* basic counter type */

#define         DEF_DXMINLIMIT      (TDATA)FLT_EPSILON      /* default DXmin */
#define         DEF_DXMAXLIMIT      (TDATA)1                /* default DXmax */



struct point_xi {                               /* internal structure for point_xi_...() */
	TSIZE       i;
	TDATA       x; };

typedef     struct point_xi     Tpoint_xi;      /* internal structure for point_xi_...() */



/*----------------------------------------------------------------*/

/***   Internal function, used by: point_xi_qsort()   ***
	Note: Due to very strict point-conversion rules in
		  some compilers, this function must be declared
		  with "void" pointers, which can be typecasted
		  internally.
*/
int point_xi_compare( const void *vp1, const void *vp2 )
{
	if ( (((Tpoint_xi *)vp1)->x) < (((Tpoint_xi *)vp2)->x) )
		return( -1 );
	else if ( (((Tpoint_xi *)vp1)->x) == (((Tpoint_xi *)vp2)->x) )
		return( 0 );
	else /*( (((Tpoint_xi *)vp1)->x) > (((Tpoint_xi *)vp2)->x) )*/
		return( 1 );
}

/***   Internal function, used by: sort_xy_data()   ***/
void point_xi_qsort( Tpoint_xi *arrxi, TSIZE n )
{
	qsort( arrxi, n, sizeof(Tpoint_xi), point_xi_compare );
}


/***   A simple rounding function to convert TDATA to TSIZE   ***/
TSIZE round( TDATA dval )
{
	if ( dval <= ((TDATA)( (TSIZE)dval + (TDATA)0.5 )) )
		return( (TSIZE)dval );
	else
		return( (TSIZE)dval+1 );
}



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
				   TDATA *dx_min, TSIZE *minpos, TDATA *dx_max, TSIZE *maxpos )
{
	TSIZE           count;
	TDATA           dx;
	int             res, error;

	
	if ( (dxminlimit<0)||(dxmaxlimit<0)||(dxminlimit>dxmaxlimit) )
		res = -1;
	else    
	{
		*dx_min = (TDATA)FLT_MAX;
		*dx_max = (TDATA)(-FLT_MAX);
		*maxpos = (TSIZE)0;
		*minpos = (TSIZE)0;
		error = 0;
	
		for ( count=1; (count<n)&&(!error); count++ )
		{
			dx = (TDATA)fabs(x[count]-x[count-1]);
			/*printf("\nPOS=%ld DX=%g DXmin=%g DXmaxL=%g\n",(TSIZE)count,dx,*dx_min,*dx_max); getch();*/
			if (dx < (*dx_min))
			{
				*dx_min = dx;
				*minpos = count;
			}
			if (dx > (*dx_max))
			{       
				*dx_max = dx;
				*maxpos = count;
			}

			if ((*dx_min) < dxminlimit)
			{
				/*printf("\n(error: *dx_min=%g )\n",*dx_min);*/
				res = -2;
				error = 1;
			}
			else if ((*dx_max) > dxmaxlimit)
			{
				/*printf("\n(error: *dx_max=%g )\n",*dx_max);*/
				res=-3;
				error=1;
			}
		}

		if (!error)
			res = 0;
	}

	return( res );
}




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
					const TDATA dx_max, TDATA *y_projerr )
{
	TSIZE           i;
	TDATA           d4y, d4y_max;
	int             res;
	

	if ( (dx_min<0)||(dx_max<0)||(dx_min>dx_max) )
		res = -1;
	else
	{
		d4y_max = (TDATA)0;
		for ( i=1; i<=n-4; i++ )
		{
			d4y = y[i+3] - 4*y[i+2] + 6*y[i+1] - 4*y[i] + y[i-1];
			d4y = (TDATA)fabs( d4y );
			if ( d4y > d4y_max )
				d4y_max = d4y;
		}

		*y_projerr = (TDATA)( d4y_max*((TDATA)pow( (dx_max/dx_min), 4 ))/24 );
		
		res = 0;
	}

	return( res );
}




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
int sort_xy_data( const TSIZE n, TDATA *x, TDATA *y )
{
	Tpoint_xi       *arrxi;
	TDATA           *newy;
	TSIZE           count, i;
	int             res;


	if ( (arrxi = (Tpoint_xi *)calloc(n,sizeof(Tpoint_xi)))==NULL )
		res = -1;
	else if ( (newy = (TDATA *)calloc(n,sizeof(TDATA)))==NULL )
	{
		free( arrxi);
		res = -1;
	}
	else
	{
		for ( count=0; count<n; count++ )   /* create intermediate table "arrxi" */
		{
			arrxi[count].i = count;
			arrxi[count].x = x[count];
		}

		point_xi_qsort( arrxi, n );         /* sort intermediate table */

		for ( count=0; count<n; count++ )   /* update intermediate Y-array after sorting */
		{
			i = arrxi[count].i;
			if (count != i)             /* change only if moved */
				newy[count] = y[i];
		}                
		for ( count=0; count<n; count++ )   /* create final X and Y arrays */
		{
			i = arrxi[count].i;
			if (count != i)             /* change only if moved */
			{
				x[count] = arrxi[count].x;  /* = x[ arrxi[count].i ] */
				y[count] = newy[count];
			}
		}                

		free( arrxi);
		free( newy );
		res = 1;
	}

	return( res );
}



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
					TDATA *a, TDATA *b, TDATA *c, TDATA *d )
{
	TSIZE       ib=0, i=0;
	int         res=0;
	TDATA       t=0.0;


	for ( i=0; i<n; i++ )  a[i] = y[i];

	if ( n<=1 )  res=1;                 /* res=1 ==> N<=1 */
	else if ( n==2 )
	{
		b[0] = (y[1]-y[0])/(x[1]-x[0]);
		c[0] = 0.0;
		d[0] = 0.0;

		b[1] = b[0];
		c[1] = 0.0;
		d[1] = 0.0;

		res=2;                          /* res=2 ==> N=2 */
	}
	else  /* if ( n>=3 ) */
	{
		d[0] = x[1]-x[0];
		c[1] = ( y[1]-y[0] )/d[0];
		for ( i=1; i<n-1; i++ )
		{
			d[i] = x[i+1]-x[i];
			b[i] = 2*( d[i-1]+d[i] );
			c[i+1] = ( y[i+1]-y[i] )/d[i];
			c[i] = c[i+1]-c[i];
		}

		b[0] = -d[0];
		b[n-1] = -d[n-2];
		c[0] = 0.0;
		c[n-1] = 0.0;
		if ( n!=3 )
		{
			c[0] = c[2]/(x[3]-x[1]) - c[1]/(x[2]-x[0]);
			c[n-1] = c[n-2]/(x[n-1]-x[n-3]) - c[n-3]/(x[n-2]-x[n-4]);
			c[0] = c[0]*(d[0]*d[0])/(x[3]-x[0]);
			c[n-1] = -c[n-1]*(d[n-2]*d[n-2])/(x[n-1]-x[n-4]);
		}


		for ( i=1; i<n; i++ )
		{
			t = d[i-1]/b[i-1];
			b[i] = b[i] - t*d[i-1];
			c[i] = c[i] - t*c[i-1];
		}

		c[n-1] = c[n-1]/b[n-1];
		for ( ib=1; ib<=n-1; ib++ )
		{
			i = (n-1)-ib;
			c[i] = ( c[i] - d[i]*c[i+1] )/b[i];
		}

		b[n-1] = (y[n-1]-y[n-2])/d[n-2] + d[n-2]*(c[n-2]+2*c[n-1]);
		for ( i=0; i<n-1; i++ )
		{
			b[i] = (y[i+1]-y[i])/d[i] - d[i]*(c[i+1]+2*c[i]);
			d[i] = (c[i+1]-c[i])/d[i];
			c[i] = 3*c[i];
		}
		c[n-1] = 3*c[n-1];
		d[n-1] = d[n-2];

		res=3;                          /* res=3 ==> N>=3 */
	}

	return( res );
}



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
					const TDATA *b, const TDATA *c, const TDATA *d )
{
	TSIZE       i=0, j=0, k=0;
	TDATA       dx=0.0, res=0.0;


	if ( u<=x[0] )  i=0;
	else if ( u>=x[n-1] )  i=n-1;
	else
	{
		i=0;  j=n;
		
		do {
			k = (TSIZE)((i+j)/2);
			if ( x[k]<=u )  i=k;
			else            j=k;  }
		while ( j > i+1 );
	}

	dx = u-x[i];
	res = a[i] + dx*( b[i] + dx*( c[i] + dx*d[i] ) );

	return( res );
}




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
						TDATA *y_splerr )
{
	TSIZE       ti;
	TDATA       yval, ydiff;


	*y_splerr = (TDATA)0;
	for ( ti=0; ti<tn; ti++ )
	{
		yval = eval_spline( tx[ti], sn, sx, a, b, c, d );

		ydiff = (TDATA)fabs( ty[ti]-yval );
		if ( (*y_splerr) < ydiff )
			*y_splerr = ydiff;
	}
}



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
						TDATA *c, TDATA *d, TDATA *y_splerr )
{
	TDATA       *sy;
	TSIZE       ti, si;
	double      istep, idist;
	int         res;


	if ( (sy = (TDATA *)calloc(sn,sizeof(TDATA)))==NULL )
		res = -1;
	else if ( sn>tn )
	{
		free( sy );
		res = -2;
	}
	else
	{
		istep = ((double)tn-1)/(sn-1);
		
		for ( si=0; si<=sn-1; si++ )
		{
			idist = si*istep;
			ti = (TSIZE)(round(idist));
			sx[si] = tx[ti];
			sy[si] = ty[ti];
		}

		res = create_spline( sn, sx, sy, a, b, c, d );
		calc_spline_diff( sn,sx,a,b,c,d,tn,tx,ty,y_splerr );
	
		free( sy );
	}

	return( res );
}




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
						TDATA *d, TDATA *y_realerr )
{
	TSIZE       tryn, uppern, lowern;
	TDATA       y_ext_splerr, y_tot_splerr;
	int         fin, res;


	
	if ( y_int_splerr > y_maxerr )
	{
		res = -1;
		return( res );
	}
	
	lowern = 4;  uppern = 4;
	
	fin = 0;  tryn = lowern;
	/*printf("\n");*/
	do
	{
		/*printf("lowerN = %u  ,  upperN = %u\n",lowern,uppern);*/
		create_semi_spline( tn,tx,ty,tryn,sx,a,b,c,d,&y_ext_splerr );

		y_tot_splerr = y_int_splerr + y_ext_splerr;
		if ( y_tot_splerr <= y_maxerr )
		{
			uppern = tryn;
			fin = 1;
		}
		else
		{
			/* tryn=tn --> error=0 --> terminate */
			lowern = tryn;
			tryn = 2*tryn;
			if ( tryn > tn )  tryn = tn;
		}
	}
	while (!fin);

	while ( (uppern-lowern)>1 )
	{
		/*printf("\tlowerN = %u  ,  upperN = %u\n",lowern,uppern);*/
		tryn = (TSIZE)((lowern+uppern)/2);

		create_semi_spline( tn,tx,ty,tryn,sx,a,b,c,d,&y_ext_splerr );

		y_tot_splerr = y_int_splerr + y_ext_splerr;
		if ( y_tot_splerr <= y_maxerr )
			uppern = tryn;
		else
			lowern = tryn;
	}

	/*printf("\tlowerN = %u  ,  upperN = %u\n",lowern,uppern);*/

	*sn = uppern;       /* use upper bound of M to calculate final S(x) */
	res = create_semi_spline( tn,tx,ty,*sn,sx,a,b,c,d,&y_ext_splerr );
	*y_realerr = y_int_splerr + y_ext_splerr;

	return( res );
}



#endif

