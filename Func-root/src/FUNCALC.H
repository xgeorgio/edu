#include <math.h>

#define         ERR_NONE            0
#define         ERR_INVPAR          -1
#define         ERR_NOROOT          -2

#define         ERR_NOMIN           -12

typedef         double      REAL;
typedef         long        COUNTER;


int nr_root( REAL (* func)(REAL), REAL x0, REAL eps, REAL hlim, 
                COUNTER n, REAL *root )
{
    REAL        x, fx, dfx, r, upperf, lowerf;
    COUNTER     i, res;


    if ( (n<1)||(eps<0)||(hlim<=0) )
        res = ERR_INVPAR;
    else
    {
        r = x0;
        i = (COUNTER)1;
        
        while (1)
        {
/*** DEBUGINFO **   printf("%d  ",i);*/
            x = r;
            fx = (*func)(x);

/*** DEBUGINFO **    printf("\tX = %g\t\tF(X) = %g\n",x,fx);*/

            if (i>n)
            {
                res = ERR_NOROOT;
                break;
            }
            else if ( fx==0 )
            {
                *root = x;
                res = ERR_NONE;
                break;
            }
            else
            {
                upperf = (*func)(x+hlim);
                lowerf = (*func)(x-hlim);
                dfx = (upperf-lowerf)/(2*hlim);
                
                r = x - fx/dfx;
                i++;

                if ( fabs(x-r)<=eps )
                {
                    *root = r;
                    res = ERR_NONE;
                    break;
                }
            }
        }
    }

    return(res);
}


int bd_root( REAL (* func)(REAL), REAL a, REAL b, REAL eps, COUNTER n, REAL *root )
{
    REAL        x, m, fax, fbx, fmx;
    COUNTER     i, res;


    if ( (n<1)||(b<a)||(eps<0) )
        res = ERR_INVPAR;
    else
    {
        fax = (*func)(a);
        fbx = (*func)(b);

        if ( fax*fbx > 0 )
            res = ERR_NOROOT;
        else if ( fax*fbx == 0 )
        {
            if (fax==0)  *root=a;
            else  *root=b;
            res = ERR_NONE;
        }
        else
        {
            i = (COUNTER)1;
            
            while(1)
            {
/*** DEBUGINFO **   printf("%d  ",i);*/                            
                m = (a+b)/2;
                fmx = (*func)(m);

/*** DEBUGINFO **   printf("\t[A,B] = [ %g , %g ]\n",a,b);*/

                if (i>n)
                {
                    res = ERR_NOROOT;
                    break;
                }
                else if ( (fmx==0)||(fabs(a-b)<=eps) )
                {
                    *root = m;
                    res = ERR_NONE;
                    break;
                }
                else 
                {
                    if (fax*fmx>0)  a = m;
                    else  b = m;

                    fax = (*func)(a);
                    fbx = (*func)(b);
                    i++;
                }
            }
        }
    }

    return(res);
}



int funmin( REAL (* func)(REAL), REAL a, REAL b, REAL eps, COUNTER n, 
                REAL *xmin, REAL *fmin )
{
    REAL        c, d, fc, fd, t;
    COUNTER     i, res;


    if ( (n<1)||(b<a)||(eps<0) )
        res = ERR_INVPAR;
    else
    {
        t = (sqrt(5)-1)/2;
        c = a + (1-t)*(b-a);
        fc = (*func)(c);
        d = b - (1-t)*(b-a);
        fd = (*func)(d);

        i = (COUNTER)1;

        while(1)
        {
/*** DEBUGINFO **   printf("%d  ",i);*/
            
/*** DEBUGINFO **   printf("\t[A,B] = [ %g , %g ]\n",a,b);*/
            
            if (i>n)
            {
                res = ERR_NOROOT;
                break;
            }
            else
            {
                if (fc<fd)
                {
                    b = d;
                    d = c;
                    c = a + (1-t)*(b-a);
                    fd = fc;
                    fc = (*func)(c);
                }
                else
                {
                    a = c;
                    c = d;
                    d = b - (1-t)*(b-a);
                    fc = fd;
                    fd = (*func)(d);
                }

                if ( (b-a)<eps )
                {
                    *xmin = (a+b)/2;
                    *fmin = (*func)(*xmin);
                    res = ERR_NONE;
                    break;
                }
                else
                    i++;
            }
        }
    }

    return(res);
}



