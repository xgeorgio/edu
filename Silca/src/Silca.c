/*
    SIMPLE INTERNAL LIGHTS CALCULATOR

    ver 1.1 (beta) - Harris Georgiou (c) 2001

    Description:
        The program is a simple internal lights calculator. It
        uses the standard engineering tables for internal lights
        of various types and configurations. According to the
        given specifications and room setups, it calculates the
        necessary lighting installation. The program itself is
        written as simple as possible for demonstration purposes.
*/

//---------------------------------------------------------------------------

#include "silca.h"

int main( void )
{
    char    resp[5];
    float   Fval, Dval, Lval, Hval, Hlim, Sval, Eval, Aval, fp, nf40, nf80;
    int     Nval, Nl, Nd, N0, np, nf, ppos, Gval;


    printf("SILCA, v1.1b - Harris Georgiou (c) 2001\n\n");

    do { printf(" Give area length L (m): "); scanf("%f",&Lval); }
    while (Lval<0);

    do { printf("  Give area width D (m): "); scanf("%f",&Dval); }
    while (Dval<0);

    do { printf(" Give area height H (m): "); scanf("%f",&Hval); }
    while (Hval<0);

    do { printf("Give total E value (LX): "); scanf("%f",&Eval); }
    while (Eval<0);

    do { printf("Give efficiency A value (0-1): "); scanf("%f",&Aval); }
    while ((Aval<0)||(Aval>1));

    do { printf("Group N fluoro-lights together: "); scanf("%d",&Gval); }
    while (Gval<=0);

    do { printf("Are there working stations near walls? (y/n): "); scanf("%s",resp); }
    while ((resp[0]!='y')&&(resp[0]!='Y')&&(resp[0]!='n')&&(resp[0]!='N'));

    switch (resp[0])
    {
        case 'y':
        case 'Y': Hlim=0.5;
                  Nd=(int)round((2*Dval)/(3*Hval));
                  if (Nd<=0) Nd=1;
                  Nl=(int)round((2*Lval)/(3*Hval));
                  if (Nl<=0) Nl=1;
                  N0=Nd*Nl;
                  break;
        case 'n':
        case 'N':
         default: Hlim=0.75;
                  Nd=(int)round((2*Dval)/(3*Hval)+1.0/3.0);
                  if (Nd<=0) Nd=1;
                  Nl=(int)round((2*Lval)/(3*Hval)+1.0/3.0);
                  if (Nl<=0) Nl=1;
                  N0=Nd*Nl;
                  break;
    }

    Sval=Dval*Lval;
    Fval=Eval*Sval/Aval;

    printf("\nLighting specifications:\n");
    printf("\tArea = %d (m^2) , E = %d (LX) , F = %d (Lm)\n\n",(int)Sval,(int)Eval,(int)Fval);

    //... thermo-lights calculations ...
    np=N0;
    fp=Fval/np;
    while (fp>light[LIGHTS_F-1][C_LM220V])  { np++; fp=Fval/np; }

    Nd=(int)ceil(sqrt(np*Dval/Lval));
    Nl=(int)ceil(np/Nd);
    np=Nd*Nl;
    fp=Fval/np;

    for ( ppos=0; (ppos<LIGHTS_F)&&(fp>light[ppos][C_LM220V]); ppos++ );

    printf("Thermo-lights grid:\n");
    printf("\tN=%dx%d , %dW (%dV) : %dLm , %dx%d (mm)\n",
        Nd, Nl, light[ppos][C_WATT], 220, light[ppos][C_LM220V],
        light[ppos][C_DIAM], light[ppos][C_LEN]);
    printf("\tSpacing=%3.1fm (edge=%3.1fm) , Lighting level=%5.1f%%\n\n",
        1.5*Hval, Hlim*Hval, Nd*Nl*light[ppos][C_LM220V]/Fval*100);

    //... fluoro-lights calculations (40W) ...
    nf40=Fval/light[LIGHTS_F][C_LM220V];
    nf=(int)ceil(nf40/Gval);

    //printf("nf=%d\n",nf);
    Nd=(int)ceil(sqrt(nf*Dval/Lval));
    Nl=(int)ceil((float)nf/Nd);
    //nf=Nd*Nl;
    //fp=Fval/nf;   //-> light power already selected (40W), divisor search not used here.
    ppos=LIGHTS_F;

    printf("Fluoro-lights grid (%dx%dW):\n",Gval,40);
    printf("\tN=%dx%d(x%d) , %dW (%dV) : %dLm , %dx%d (mm)\n",
        Nd, Nl, Gval, light[ppos][C_WATT], 220, light[ppos][C_LM220V],
        light[ppos][C_DIAM], light[ppos][C_LEN]);
    printf("\tSpacing=%3.1fm (edge=%3.1fm) , Lighting level=%5.1f%%\n\n",
        1.5*Hval, Hlim*Hval, Nd*Nl*Gval*light[ppos][C_LM220V]/Fval*100);

    //... fluoro-lights calculations (80W) ...
    nf80=Fval/light[LIGHTS_F+1][C_LM220V];
    nf=(int)ceil(nf80/Gval);

    Nd=(int)round(sqrt(nf*Dval/Lval));
    Nl=(int)round((float)nf/Nd);
    //nf=Nd*Nl;
    //fp=Fval/nf;   //-> light power already selected (80W), divisor search not used here.    fp=Fval/nf;
    ppos=LIGHTS_F+1;

    printf("Fluoro-lights grid (%dx%dW):\n",Gval,80);
    printf("\tN=%dx%d(x%d) , %dW (%dV) : %dLm , %dx%d (mm)\n",
        Nd, Nl, Gval, light[ppos][C_WATT], 220, light[ppos][C_LM220V],
        light[ppos][C_DIAM], light[ppos][C_LEN]);
    printf("\tSpacing=%3.1fm (edge=%3.1fm) , Lighting level=%5.1f%%\n\n",
        1.5*Hval, Hlim*Hval, Nd*Nl*Gval*light[ppos][C_LM220V]/Fval*100);

    return(0);
}
//---------------------------------------------------------------------------
