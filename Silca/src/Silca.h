/*
    SIMPLE INTERNAL LIGHTS CALCULATOR

    ver 1.0 (beta) - Harris Georgiou (c) 2001

    Description:
        The program is a simple internal lights calculator. It
        uses the standard engineering tables for internal lights
        of various types and configurations. According to the
        given specifications and room setups, it calculates the
        necessary lighting installation. The program itself is
        written as simple as possible for demonstration purposes.
*/

//---------------------------------------------------------------------------

#ifndef     _SILCA_H
#define     _SILCA_H

#include <stdio.h>
#include <math.h>

#define     round(x)        floor(x+0.5)

#define     LIGHTS_P        0
#define     LIGHTS_F        12
#define     LIGHTS_SZ       14

#define     C_WATT          0
#define     C_LM110V        1
#define     C_LM220V        2
#define     C_DIAM          3
#define     C_LEN           4

const int light[LIGHTS_SZ][5] =
    { {  15,     135,    115,    55,     97    },
      {  25,     235,    210,    60,     105   },
      {  40,     430,    340,    60,     115   },
      {  60,     740,    590,    75,     122   },
      {  75,     990,    800,    70,     130   },
      {  100,    1420,   1180,   75,     142   },
      {  150,    2250,   1950,   80,     160   },
      {  200,    3100,   2750,   90,     178   },
      {  300,    5100,   4500,   110,    233   },
      {  500,    9000,   8100,   130,    267   },
      {  750,    14000,  13000,  150,    300   },
      {  1000,   20000,  18000,  150,    300   },
      {  40,     -1,     1200,   1220,   38    },
      {  80,     -1,     1920,   1525,   38    }  };

#endif
