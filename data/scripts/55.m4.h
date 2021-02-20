// set weather to sandstorm, move player 1 sq down if they lack the go-goggles
#include "scriptlib.m4.h"
SET_WEATHER( WEATHER_SANDSTORM )
CHECK_ITEM( I_GO_GOGGLES, 1, 1 )
    JUMP_TO_END
MESSAGE( 275, 0 )
MOVE_PLAYER( DOWN, 1 )
END_OF_PROGRAM
