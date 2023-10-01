// E4 Glacia on room enter
#include "scriptlib.m4.h"

#define V_HALL_OF_FAME_VICTORIES 37
SET_TRAINER_FLAG( 76, 0 )
SET_TRAINER_FLAG( 69, 0 )

MOVE_PLAYER( UP, 6 )

// lock door
SET_BLOCK( 14, 21, 0x2D7 )
SET_BLOCK( 14, 22, 0x2DF )
SET_BLOCK( 15, 21, 0x206 )
SET_BLOCK( 15, 22, 0x20E )
SET_BLOCK( 16, 21, 0x2E5 )
SET_BLOCK( 16, 22, 0x2E6 )
// after battle message

END_OF_PROGRAM
