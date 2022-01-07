/*
    QUANTUM NUMBERS CALCULATIONS

    ver 1.2 - Harris Georgiou (c) 2001

    Description:
        The program is a simple quantum numbers calculator. Given
        primary quantum number (energy level), it iterates through
        the complete list of quantum quads. The program itself is
        written as simple as possible for C++ I/O streams demonstration.
*/

//===========================================================================

#include    <iostream>
#include    <iomanip>


using namespace std;


int main( void )
{
	int nn=0;
	unsigned long   count=0;

	cout<< "       +---------------------------------------------------------+ \n";
	cout<< "       |               QUANTUM NUMBERS CALCULATOR                | \n";
	cout<< "       |        ver 1.2 (beta) - Harris Georgiou (c) 2001        | \n";
	cout<< "       +---------------------------------------------------------+ \n";

	cout<< "\n\tGive Main Quantum Number (P.Q.N.) { 1,2,3,... } : ";
	cin >> nn;
	if(nn<1) { cout <<endl<<"Error: Main quantum number must be a positive integer."<<endl<<endl; exit(1); }

	cout<< "\n\tQUANTUM QUADS CALCULATION : "<<nn<<endl<<endl;
	cout<< "\t    Legend: "<<endl;
	cout<< "\t\t n  = Main Quantum Number (P.Q.N.)" <<endl;
	cout<< "\t\t l  = Secondary Quantum Number (S.Q.N.)" <<endl;
	cout<< "\t\t ml = Magnetic Quantum Number (M.Q.N.)" <<endl;
	cout<< "\t\t ms = Quantum Spin Number (Q.S.N.)" <<endl<<endl;

	cout<< "\t            n    |    l     |    ml    |    ms     "<<endl;
	cout<< "\t       +---------+----------+----------+----------+"<<endl;

	for( int l=0; l <= (nn-1); l++ )
	{
		for( long ml=-l; ml <= l; ml++ )
		{
			for( float ms=-0.5; ms <= 0.5; ms++ )
			{
				cout << "\t       " << setw(5) << nn << "     :"
					<< setw(5) << l  << "     :"
					<< setw(5) << ml << "     :"
					<< setw(7) << setprecision(1) << ms << endl;
				count++;
			}
		}
	}

	cout<< endl<< "A total of "<<count<<" quantum quads were calculated." <<endl;

	return(0);

}



