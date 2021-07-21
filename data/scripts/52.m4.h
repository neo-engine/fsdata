// rival entry
#include "scriptlib.m4.h"

CHECK_FLAG( 5, 1, 1 ) // Should only activate when the rival has appearance 0
    JUMP_TO_END
CHECK_FLAG( 12, 0, 2 )
    // Player has already met rival
    MESSAGE( 68, 0 )
    JUMP_TO_END
SPAWN_MAPOBJECT( 1, 11, 6 )
    COPY_REGISTER( 0, 1 )
    MOVE_MAPOBJECT_R( 1, DOWN, 1 )
    EXCLAMATION_R( 1 ) // Show exclamation mark
    MESSAGE( 74, 0 )
    PLAY_MUSIC( BGM_ENCOUNTER_MAY )
    // Check where the player is standing, move Brendan accordingly
    CHECK_PLAYER_POS( 13, 9, 3 )
    CHECK_REGISTER( 0, 0, 3 )
        MOVE_PLAYER( LEFT, 0 )
        MOVE_MAPOBJECT_R( 1, DOWN, 2 )
        MOVE_MAPOBJECT_R( 1, RIGHT, 1 )
    CHECK_PLAYER_POS( 14, 10, 3 )
    CHECK_REGISTER( 0, 0, 4 )
        MOVE_PLAYER( UP, 0 )
        MOVE_MAPOBJECT_R( 1, DOWN, 2 )
        MOVE_MAPOBJECT_R( 1, RIGHT, 3 )
        MOVE_MAPOBJECT_R( 1, DOWN, 0 )
    CHECK_PLAYER_POS( 12, 10, 3 )
    CHECK_REGISTER( 0, 0, 4 )
        MOVE_PLAYER( UP, 0 )
        MOVE_MAPOBJECT_R( 1, DOWN, 2 )
        MOVE_MAPOBJECT_R( 1, RIGHT, 1 )
        MOVE_MAPOBJECT_R( 1, DOWN, 0 )
    CHECK_PLAYER_POS( 13, 11, 3 )
    CHECK_REGISTER( 0, 0, 3 )
        MOVE_PLAYER( LEFT, 0 )
        MOVE_MAPOBJECT_R( 1, DOWN, 4 )
        MOVE_MAPOBJECT_R( 1, RIGHT, 1 )

    MESSAGE( 67, 0 )

    CHECK_PLAYER_POS( 13, 9, 3 )
    CHECK_REGISTER( 0, 0, 2 )
        MOVE_MAPOBJECT_R( 1, UP, 2 )
        MOVE_MAPOBJECT_R( 1, RIGHT, 6 )
    CHECK_PLAYER_POS( 14, 10, 3 )
    CHECK_REGISTER( 0, 0, 2 )
        MOVE_MAPOBJECT_R( 1, UP, 2 )
        MOVE_MAPOBJECT_R( 1, RIGHT, 4 )
    CHECK_PLAYER_POS( 12, 10, 3 )
    CHECK_REGISTER( 0, 0, 2 )
        MOVE_MAPOBJECT_R( 1, UP, 2 )
        MOVE_MAPOBJECT_R( 1, RIGHT, 6 )
    CHECK_PLAYER_POS( 13, 11, 3 )
    CHECK_REGISTER( 0, 0, 3 )
        MOVE_PLAYER( UP, 0 )
        MOVE_MAPOBJECT_R( 1, UP, 4 )
        MOVE_MAPOBJECT_R( 1, RIGHT, 6 )

    MOVE_MAPOBJECT_R( 1, UP, 0 )
    SET_FLAG( 12, 1 )
    REDRAW_OBJECTS
    RESTORE_MUSIC
DESTROY_MAPOBJECT_R( 1 )
END_OF_PROGRAM
