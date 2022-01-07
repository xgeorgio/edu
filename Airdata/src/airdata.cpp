/*
    ATMOSPHERIC DATA CALCULATIONS

    ver 1.3 - Harris Georgiou (c) 2001

    Description:
        The program is a simple atmospheric model calculator. It
        implements the general and analytical systems and includes
        non-linear (exponential) models for pressure, density
        and temperature. The program itself is written as simple as
        possible for C++ I/O streams demonstration.
*/

//===========================================================================

#include    <iostream>
#include    <iomanip>
#include    <math.h>


const   float   r0=1.225000;            //---> Kg/m^3
const   float   P0=1.013E+5;            //---> N/m^2
const   float   T0=288.000;             //---> K

const   float   L=0.0065;               //---> K/m
const   float   R=287.000;              //---> m^2/(sec.K)
const   float   g=9.810;                //---> m/sec^2


using namespace std;


int main( void )
{
	double  alt1, alt2, dev;
	double  calt, cp, cr, ct, temp[6], mode_a, mode_p, mode_r, mode_t;
	int     flr, grads;


	cout<< "       +-------------------------------------------------------+\n";
	cout<< "       |              ATMOSPHERIC DATA MODELLING               |\n";
	cout<< "       |     version 1.3 (beta) - Harris Georgiou (c) 2001     |\n";
	cout<< "       +-------------------------------------------------------+\n";

	cout<< "\n\tSelect calculation system ( General=0, Analytical=1 ) : ";
	cin >> grads;

	if(grads==1) cout<< "\n\tGive STARTING altitude (in meters) : ";
	else cout<< "\n\tGive STARTING altitude (in feet) : ";
	cin >> temp[0];

	if(grads==1) cout<< "\n\tGive ENDING altitude (in meters) : ";
	else cout<< "\n\t Give ENDING altitude (in feet) : ";
	cin >> temp[1];

	cout<< "\n\tGive altitude divisions count : ";
	cin >> flr;

	if( temp[0]<0.0 || temp[1]<0.0 ) { cout <<endl<<"Error: Altitude must be a positive numbers."<<endl<<endl; exit(1); }

	if( flr<0 ) { cout <<endl<<"Error: Divisions must be a positive number."<<endl<<endl; exit(1); }

	if( grads==1 ) { mode_a=mode_p=mode_r=1.0; mode_t=0.0; }
	else { mode_a=0.3048; mode_p=P0; mode_r=0.001; mode_t=-273.000; }

	alt1 = mode_a*temp[0];
	alt2 = mode_a*temp[1];

	cout<< "\n\tATMOSPHERIC MODEL ANALYSIS"<<endl<<endl;
	if(grads==1) {
		cout<< "\t From altitude: "<<alt1<<" (m), to: "<<alt2<<" (m)."<<endl<<endl;
		cout<< "\t    Legend: "<<endl;
		cout<< "\t\t Alt = Altitude ( m )" <<endl;
		cout<< "\t\t  P  = Air Pressure ( N/m^2 )" <<endl;
		cout<< "\t\t  d  = Air Density ( kgr/m^3 )" <<endl;
		cout<< "\t\t  T  = Air Temperature ( K )" <<endl<<endl; }
	else {
		cout<< "\t From altitude: "<<alt1<<" (ft), to: "<<alt2<<" (ft)."<<endl<<endl;
		cout<< "\t    Legend: "<<endl;
		cout<< "\t\t Alt = Altitude ( ft )" <<endl;
		cout<< "\t\t  P  = Air Pressure ( atm )" <<endl;
		cout<< "\t\t  d  = Air Density ( gr/cm^3 )" <<endl;
		cout<< "\t\t  T  = Air Temperature ( C )" <<endl<<endl; }


	cout<< "          Alt       |        P        |        d        |         T        "<<endl;	cout<< "  +-----------------+-----------------+-----------------+-----------------+"<<endl;

	alt1 = mode_a*temp[0];
	alt2 = mode_a*temp[1];
	dev = (alt2-alt1)/flr;

	temp[0] = 0.0;
	temp[1] = g/(R*L);
	temp[2] = (g-R*L)/(R*L);

	temp[3] = 1-L*11000.000/T0;
	temp[4] = P0*pow(temp[3], temp[1]);
	temp[5] = r0*pow(temp[3], temp[2]);

	cout.precision(6);

	for( int count=0; count<=flr; count++ )
	{
		calt=alt1+count*dev;

		if( calt<=11000.000 )
		{
			temp[0] = 1-L*calt/T0;
			cp = P0*pow(temp[0], temp[1])/mode_p;
			cr = r0*pow(temp[0], temp[2])*mode_r;
			ct = (T0-L*calt)+mode_t;
		}

		else
		{
			temp[0] = (11000.000-calt)/(R*216.500);
			cp = temp[4]*exp(temp[0])/mode_p;
			cr = temp[5]*exp(temp[0])*mode_r;
			ct = 216.500+mode_t;
		}

		if(grads==1) temp[0]=calt;
		else temp[0]=calt/mode_a;

		cout<<  "   "<< setw(15)<<temp[0]
					   << " : " << setw(15)<<cp
					   << " : " << setw(15)<<cr
					   << " : " << setw(15)<<ct
					   <<endl;
	}

	return(0);
}



