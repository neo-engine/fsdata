// Farewell from mom (where the player does not obtain the running shoes, because they are
// enabled by default)
#include "scriptlib.m4.h"

GET_MAPOBJECT( 25, 3, 3 )
    EXCLAMATION_R( 0 )
    MOVE_PLAYER( RIGHT, 0 )
    MESSAGE( 108, 0 )
    MOVE_MAPOBJECT_R( 0, LEFT, 1 )
    MESSAGE( 109, 0 )
    MOVE_MAPOBJECT_R( 0, RIGHT, 4 )
    MOVE_MAPOBJECT_R( 0, UP, 8 )
SET_FLAG( 22, 1 )
REDRAW_OBJECTS
END_OF_PROGRAM

