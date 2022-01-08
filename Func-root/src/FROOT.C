#include <stdio.h>
#include "funcalc.h"


REAL x2_4( REAL x )
{
    return( x*x );
}


void main( void )
{
    REAL        eps=1e-9, hlim=1e-9, x0=5.0, a=-1.0, b=5.0, root;
    REAL        xmin, fmin;
    COUNTER     n=100;
    int         res;

    printf("Root Finders - Test function: f(x)=x^2\n\n");
    
    printf("Newton-Raphson method:\n");
    res = nr_root( x2_4, x0, eps, hlim, n, &root );
    printf("Search completed ");
    if (res==ERR_NONE)
        printf("SUCCESSFULLY:  Root=%g\n",root);
    else
        printf("UNSUCCESSFULLY!  (code=%d)\n",res);
    printf("\n");

    printf("Binary-Division method:\n");
    res = bd_root( x2_4, a, b, eps, n, &root );
    printf("Search completed ");
    if (res==ERR_NONE)
        printf("SUCCESSFULLY:  Root=%g\n",root);
    else
        printf("UNSUCCESSFULLY!  (code=%d)\n",res);
    printf("\n");

    printf("Function Minimum Finder:\n");
    res = funmin( x2_4, a, b, eps, n, &xmin, &fmin );
    printf("Search completed ");
    if (res==ERR_NONE)
        printf("SUCCESSFULLY:  Fmin=%g  at  Xmin=%g\n",fmin,xmin);
    else
        printf("UNSUCCESSFULLY!  (code=%d)\n",res);
    printf("\n\n");
}



