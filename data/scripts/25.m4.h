// Dude stopping player from leaving petalburg city before visiting the gym
#include "scriptlib.m4.h"

GET_MAPOBJECT( 5, 9, 3 )
    EXCLAMATION_R( 0 )
    LOCK_R( 0 )
    MOVE_MAPOBJECT_R( 0, RIGHT, 1 )
    MOVE_MAPOBJECT_R( 0, UP, 1 )
    MOVE_MAPOBJECT_R( 0, RIGHT, 1 )
    HIDE_PKMN
    MOVE_PLAYER( LEFT, 0 )
    MESSAGE( 119, 0 )
    MOVE_MAPOBJECT_R( 0, DOWN, 1 )
    MOVE_MAPOBJECT_R( 0, RIGHT, 2 )
    MOVE_MAPOBJECT_R( 0, UP, 1 )
    MOVE_MAPOBJECT_R( 0, RIGHT, 0 )
    MOVE_PLAYER( RIGHT, 0 )
    ATTACH_PLAYER
    MOVE_MAPOBJECT_R( 0, RIGHT, 6 )
    REMOVE_PLAYER
    MOVE_MAPOBJECT_R( 0, UP, 0 )
    MOVE_PLAYER( UP, 0 )
    MESSAGE( 120, 0 )
    MOVE_MAPOBJECT_R( 0, DOWN, 1 )
    MOVE_PLAYER( DOWN, 0 )
    MOVE_MAPOBJECT_R( 0, LEFT, 10 )
    UNLOCK_R( 0 )
END_OF_PROGRAM

