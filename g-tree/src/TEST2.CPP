// -------------------------------------------------
//
//
// -------------------------------------------------
//                         Harris Georgiou, 1997.
// -------------------------------------------------



/*.......... file: qzstatus.hpp ..........*/
#include "gstatus.hpp"

class QuizStatus : public GameStatus
{
    public:
        QuizStatus() : GameStatus()     {}
        QuizStatus( QuizStatus &qs ) : GameStatus(qs)   {}

        //~QuizStatus()     {}
};

#define     TGameStatus     QuizStatus
/*.......... end-of-file ..........*/


#include "gstatset.hpp"


void main( void )
{
    QuizStatus  qs;


    cout << qs;
}


