// Player's pc
#include "scriptlib.m4.h"

CHECK_FLAG( 5, 0, 2 ) // Should only activate when the rival has appearance 0
    MESSAGE( 51, 0 )
    JUMP_TO_END
PLAY_SOUND_EFFECT( SFX_PC_OPEN )
MESSAGE( 33, 1 )
CHECK_FLAG( 9, 1, 2 ) // Potion already obtained
    MESSAGE( 34, 0 )
    GIVE_ITEM( I_POTION, 1 )
GET_INITGAME_ITEMCOUNT
CHECK_REGISTER( 0, 0, 6 )
    GET_INITGAME_ITEM
    CHECK_REGISTER( 0, 0, 4 )
        MESSAGE( 38, 0 )
        SET_REGISTER( 1, 1 )
        GIVE_ITEM_R( 0 )
        REWIND( 8 )
PLAY_SOUND_EFFECT( SFX_PC_CLOSE )
WAIT( 50 )
CHECK_FLAG( 9, 0, 2 ) // Potion already obtained
    MESSAGE( 274, 0 )
    JUMP_TO_END
SET_FLAG( 9, 1 )
REDRAW_OBJECTS // Remove Vigoroths from downstairs room
SPAWN_MAPOBJECT( 227, 11, 6 )
    MOVE_MAPOBJECT_R( 0, DOWN, 1 )
    MOVE_PLAYER( LEFT, 0 )
    MOVE_MAPOBJECT_R( 0, RIGHT, 6 )
    MESSAGE( 40, 0 )
    ATTACH_PLAYER
        MOVE_MAPOBJECT_R( 0, LEFT, 6 )
    REMOVE_PLAYER
    MOVE_MAPOBJECT_R( 0, UP, 1 )
    MOVE_PLAYER( LEFT, 1 )
DESTROY_MAPOBJECT_R( 0 )
// already spawn map object on bottom floor to avoid "pop in" effect
SPAWN_MAPOBJECT( 227, 15, 24 )
    MOVE_PLAYER( UP, 1 )
    GET_MAPOBJECT( 15, 24, 3 )
// warp to bottom room
    MOVE_MAPOBJECT_R( 0, RIGHT, 1 )
    MOVE_MAPOBJECT_R( 0, UP, 0 )
    EXCLAMATION_R( 0 ) // Show exclamation mark
    MESSAGE( 45, 0 )
    MOVE_PLAYER( DOWN, 1 )
    MOVE_PLAYER( RIGHT, 2 )
    MOVE_PLAYER( DOWN, 1 )
    MOVE_PLAYER( RIGHT, 1 )
    ATTACH_PLAYER
        MOVE_MAPOBJECT_R( 0, RIGHT, 1 )
    REMOVE_PLAYER
    MOVE_PLAYER( UP, 0 )
    MOVE_MAPOBJECT_R( 0, LEFT, 0 )
    MESSAGE( 54, 0 )
    MOVE_PLAYER( RIGHT, 0 )
    MESSAGE( 47, 0 )
    MOVE_MAPOBJECT_R( 0, RIGHT, 1 )
    MOVE_MAPOBJECT_R( 0, DOWN, 1 )
    MOVE_MAPOBJECT_R( 0, LEFT, 0 )
    SET_FLAG( 10, 1 )
REDRAW_OBJECTS
DESTROY_MAPOBJECT_R( 0 )
END_OF_PROGRAM
