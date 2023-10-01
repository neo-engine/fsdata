// enter hall of fame (steven)
#include "scriptlib.m4.h"

SPAWN_MAPOBJECT( 23, 16, 20 )
MOVE_MAPOBJECT_R( 1, LEFT, 0 )
MOVE_PLAYER( RIGHT, 0 )
MESSAGE( 665, 0 )

MOVE_PLAYER( UP, 11 )
HALL_OF_FAME

END_OF_PROGRAM
