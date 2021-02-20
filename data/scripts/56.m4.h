// set weather to sandstorm, move player 2 sq left if they lack the go-goggles
#include "scriptlib.m4.h"
SET_WEATHER( WEATHER_SANDSTORM )
CHECK_ITEM( I_GO_GOGGLES, 1, 1 )
    JUMP_TO_END
MESSAGE( 275, 0 )
MOVE_PLAYER( LEFT, 2 )
END_OF_PROGRAM
