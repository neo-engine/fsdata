// enter hall of fame (acerola)
#include "scriptlib.m4.h"

SPAWN_MAPOBJECT( 40, 16, 20 )
MOVE_MAPOBJECT_R( 1, LEFT, 0 )
MOVE_PLAYER( RIGHT, 0 )
MESSAGE( 669, 0 )

MOVE_PLAYER( UP, 11 )
HALL_OF_FAME

END_OF_PROGRAM
