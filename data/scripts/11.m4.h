// rival entry
#include "scriptlib.m4.h"

CHECK_FLAG( 5, 0, 1 ) // Should only activate when the rival has appearance 0
    JUMP_TO_END
CHECK_FLAG( 12, 0, 2 )
    // Player has already met rival
    MESSAGE( 68, 0 )
    JUMP_TO_END
SPAWN_MAPOBJECT( 0, 17, 6 )
    COPY_REGISTER( 0, 1 )
    MOVE_MAPOBJECT_R( 1, DOWN, 1 )
    EXCLAMATION_R( 1 ) // Show exclamation mark
    MESSAGE( 74, 0 )
    PLAY_MUSIC( BGM_ENCOUNTER_BRENDAN )
    // Check where the player is standing, move Brendan accordingly
    CHECK_PLAYER_POS( 15, 9, 3 )
    CHECK_REGISTER( 0, 0, 3 )
        MOVE_PLAYER( RIGHT, 0 )
        MOVE_MAPOBJECT_R( 1, DOWN, 2 )
        MOVE_MAPOBJECT_R( 1, LEFT, 1 )
    CHECK_PLAYER_POS( 14, 10, 3 )
    CHECK_REGISTER( 0, 0, 4 )
        MOVE_PLAYER( UP, 0 )
        MOVE_MAPOBJECT_R( 1, DOWN, 2 )
        MOVE_MAPOBJECT_R( 1, LEFT, 3 )
        MOVE_MAPOBJECT_R( 1, DOWN, 0 )
    CHECK_PLAYER_POS( 16, 10, 3 )
    CHECK_REGISTER( 0, 0, 4 )
        MOVE_PLAYER( UP, 0 )
        MOVE_MAPOBJECT_R( 1, DOWN, 2 )
        MOVE_MAPOBJECT_R( 1, LEFT, 1 )
        MOVE_MAPOBJECT_R( 1, DOWN, 0 )
    CHECK_PLAYER_POS( 15, 11, 3 )
    CHECK_REGISTER( 0, 0, 3 )
        MOVE_PLAYER( RIGHT, 0 )
        MOVE_MAPOBJECT_R( 1, DOWN, 4 )
        MOVE_MAPOBJECT_R( 1, LEFT, 1 )

    MESSAGE( 67, 0 )

    CHECK_PLAYER_POS( 15, 9, 3 )
    CHECK_REGISTER( 0, 0, 2 )
        MOVE_MAPOBJECT_R( 1, UP, 2 )
        MOVE_MAPOBJECT_R( 1, LEFT, 6 )
    CHECK_PLAYER_POS( 14, 10, 3 )
    CHECK_REGISTER( 0, 0, 2 )
        MOVE_MAPOBJECT_R( 1, UP, 2 )
        MOVE_MAPOBJECT_R( 1, LEFT, 4 )
    CHECK_PLAYER_POS( 16, 10, 3 )
    CHECK_REGISTER( 0, 0, 2 )
        MOVE_MAPOBJECT_R( 1, UP, 2 )
        MOVE_MAPOBJECT_R( 1, LEFT, 6 )
    CHECK_PLAYER_POS( 15, 11, 3 )
    CHECK_REGISTER( 0, 0, 3 )
        MOVE_PLAYER( RIGHT, 0 )
        MOVE_MAPOBJECT_R( 1, UP, 4 )
        MOVE_MAPOBJECT_R( 1, LEFT, 6 )

    MOVE_MAPOBJECT_R( 1, UP, 0 )
    SET_FLAG( 12, 1 )
    REDRAW_OBJECTS
    RESTORE_MUSIC
DESTROY_MAPOBJECT_R( 1 )
END_OF_PROGRAM
