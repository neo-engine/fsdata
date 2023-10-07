// enter hall of fame (Wallace)
#include "scriptlib.m4.h"

SPAWN_MAPOBJECT( 14, 16, 20 )
MOVE_MAPOBJECT_R( 1, LEFT, 0 )
MOVE_PLAYER( RIGHT, 0 )
MESSAGE( 661, 0 )

MOVE_PLAYER( UP, 11 )
HALL_OF_FAME

END_OF_PROGRAM
