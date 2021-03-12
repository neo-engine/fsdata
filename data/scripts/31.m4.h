// Scott stopping the player when leaving petalburg city
#include "scriptlib.m4.h"

SPAWN_MAPOBJECT( 238, 10, 10 ) // Scott
    MOVE_MAPOBJECT_R( 0, LEFT, 7 )
    HIDE_PKMN
    MOVE_MAPOBJECT_R( 0, LEFT, 1 )
    MOVE_PLAYER( RIGHT, 0 )
    MESSAGE( 158, 0 )
    MOVE_MAPOBJECT_R( 0, RIGHT, 0 )
    MESSAGE( 159, 0 )
    MOVE_MAPOBJECT_R( 0, LEFT, 0 )
    MESSAGE( 160, 0 )
    MOVE_MAPOBJECT_R( 0, DOWN, 1 )
    MOVE_MAPOBJECT_R( 0, LEFT, 10 )
    DESTROY_MAPOBJECT_R( 0 )
    SET_FLAG( 28, 1 )
END_OF_PROGRAM
