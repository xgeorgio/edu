/*        ******************************************************************
	  ***                                                            ***
	  ***         3rd-degree Spline Interpolation - Example          ***
	  ***         ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~          ***
	  ***                                                            ***
	  ******************************************************************



		DESCRIPTION:
									
			(See source code file description and on-line comments)



------------------------------------------------------------------------------
*/

#include    <conio.h>
#include    <stdio.h>

#include    "splines.c"         /*--> used if source code is to be used */
/*#include    "splines.h" */    /*--> used if library is to be used */


TDATA read_realnum( void )
{
	char    s[30];

	scanf("%s",s);
	return( (TDATA)atof(s) );
}

TDATA func( TDATA x )
{
	return( (TDATA)(x*exp(-x)) );
}




#define         NUM         700
#define         STEP        FLT_EPSILON*1000
#define         DX_MIN      DEF_DXMINLIMIT
#define         DX_MAX      DEF_DXMAXLIMIT


void main( void )
{
	TDATA       x[NUM], y[NUM];
	TDATA       sx[NUM], a[NUM], b[NUM], c[NUM], d[NUM];
	TDATA       xval=0.0, yval=0.0, xa, xb, xstep, splerror, realerr;
	TSIZE       snum, count=0, res=0, N=0;
	char        str[10];
	TDATA       dxmaxlimit=DX_MAX, dxminlimit=DX_MIN, dx_min=0.0, dx_max=0.0;
	TSIZE       minpos, maxpos;
	int         sdigits;

	
	printf("Cubic Spline Curve Fit, version (BETA) 1.0 - Harris Georgiou (c) 1999.\n");
	printf("----------------------------------------------------------------------\n\n");

	do {
	    printf("Give number of points (N>=4): ");
	    scanf("%u",&N); }
	while (N<4);
	
	for ( count=0; count<N; count++ )
	{
	    printf("\tGive point #%u (x,y): ",count+1);
	    x[count]=read_realnum();
	    y[count]=read_realnum();
	}

    printf("Curve points:\n");
	for ( count=0; count<N; count++ )
	    printf("\tpoint #%u (x,y):  [ %f , %f ]\n",count+1,x[count],y[count]);
	
	printf("\n...<press any key to check DX data>..."); getch();
	printf("\nChecking DX data (DXminL=%g  DXmaxL=%g)... ",
						(TDATA)dxminlimit, (TDATA)dxmaxlimit);
/**/res = check_dx_data( N, x, dxminlimit, dxmaxlimit,
							&dx_min, &minpos, &dx_max, &maxpos );
	printf("Done! (code=%d)\n",res);
	printf("Found:   DXmin=%g  (pos=%u)  ,  DXmax=%g  (pos=%u)  ==> ",
				(TDATA)dx_min, (TSIZE)minpos, (TDATA)dx_max, (TSIZE)maxpos);
	if (res==0)  printf("OK\n");
	else  printf("ERROR!\n");

	printf("\n...<press any key to check DY data>..."); getch();
	printf("\nChecking DY data (with DXmin=%g  DXmax=%g)... ",
						(TDATA)dx_min, (TDATA)dx_max);
/**/res = check_dy_data( N, y, dx_min, dx_max, &splerror );
	printf("Done! (code=%d)\n",res);

	printf("\n...<press any key to sort data>..."); getch();
	printf("\nSorting Data...");
/**/res = sort_xy_data( N, x, y );
	printf("Done! (code=%d)\n",res);
	/*for ( count=0; count<NUM; count++ )
		printf("   ( X%d , Y%d ) = ( %g , %g )\n", 
							count+1, count+1, x[count], y[count]);*/
	
	printf("\n...<press any key to create spline>..."); getch();
	printf("\nCreating Spline...");
	realerr = splerror;
	snum = N;
/**/res = create_best_spline( N,x,y,splerror,2*splerror,&snum,sx,a,b,c,d,&realerr );
	/*res = create_spline( N,x,y,a,b,c,d );*/
	printf("Done! (code=%d)\n",res);

	printf("Final N = %u\nTotal S(x) error: %g\n",snum,realerr);
	printf("(Projected Y error for S(X): %g)\n",(TDATA)splerror);
	printf("Spline Y-values have ");
	if ( realerr != 0 )
	{
		sdigits = (int)(-log10(realerr));
		printf("%d correct decimal places.\n",sdigits);
	}
	else
		printf("ALL decimal places correct.\n",sdigits);

	printf("\n...<press any key to evaluate spline>..."); getch();
	printf("\nEvaluating Spline...");
	do        
	{
		printf("\nGive x-value: ");
		xval=read_realnum();
		/*yval = eval_spline( xval, N, x, a, b, c, d );*/
/**/    yval = eval_spline( xval, snum, sx, a, b, c, d );
		printf("\tX = %g , S(X) = %g\n", xval, yval);
		
		printf("\t\t\tAnother point? (y/n): ");
		scanf("%s",str);
	}
	while ((str[0]!='n')&&(str[0]!='Y'));
	printf("Done!\n\n");

}
