// Team Aqua grunt encounter in rusturf tunnel
#include "scriptlib.m4.h"

PLAY_MUSIC( MOD_ENCOUNTER_TEAM_AM )
MESSAGE( 266, 0 )
YES_NO_MESSAGE_N( 375, 1, 11 ) // Ask if the player wants to battle
    SET_FLAG( 159, 1 )
    // Player wants to battle
    BATTLE_TRAINER( 48, SINGLE )
    // Check if the player managed to win
    PLAY_MUSIC( MOD_ENCOUNTER_TEAM_AM )
    CHECK_REGISTER( 0, 1, 4 )
        // They didn't
        HEAL_TEAM
        SET_FLAG( 160, 1 )
        MESSAGE( 376, 0 )
        SKIP( 2 )
    MESSAGE( 267, 0 )
    GIVE_ITEM( I_DEVON_GOODS, 1 )
    SKIP( 1 )
    // no battle
    MESSAGE( 377, 0 )

SET_FLAG( 161, 1 )
// aqua grunt disappears
HIDE_PKMN
MOVE_PLAYER( UP, 1 )
MOVE_PLAYER( DOWN, 0 )
GET_MAPOBJECT( 13, 10, 3 )
    COPY_REGISTER( 0, 1 )
    MOVE_MAPOBJECT_FAST_R( 1, LEFT, 7 )
    MOVE_MAPOBJECT_FAST_R( 1, DOWN, 5 )
    DESTROY_MAPOBJECT_R( 1 )
RESTORE_MUSIC

// old dude collects his wingull
SPAWN_MAPOBJECT( 62, 6, 15 )
    COPY_REGISTER( 0, 1 )
    MOVE_MAPOBJECT_FAST_R( 1, UP, 5 )
    MOVE_MAPOBJECT_FAST_R( 1, RIGHT, 7 )
    MOVE_MAPOBJECT_FAST_R( 1, UP, 0 )
    GET_MAPOBJECT( 13, 9, 3 )
    MOVE_MAPOBJECT_R( 0, DOWN, 0 )
    LOCK_R( 0 )
    PLAY_MUSIC( MOD_UNWAVERING_EMOTIONS )
    MESSAGE( 370, 0 )
    MOVE_MAPOBJECT_FAST_R( 1, LEFT, 1 )
    MOVE_MAPOBJECT_FAST_R( 1, UP, 0 )
    MESSAGE( 371, 0 )
    MOVE_MAPOBJECT_FAST_R( 1, RIGHT, 1 )
    MOVE_MAPOBJECT_FAST_R( 1, UP, 0 )
    MESSAGE( 372, 0 )
    DESTROY_MAPOBJECT_R( 0 )
    MOVE_MAPOBJECT_R( 1, LEFT, 7 )
    MOVE_MAPOBJECT_R( 1, DOWN, 5 )
    DESTROY_MAPOBJECT_R( 1 )

RESTORE_MUSIC
REDRAW_OBJECTS
END_OF_PROGRAM
