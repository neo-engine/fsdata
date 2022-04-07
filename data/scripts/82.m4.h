// aqua grunt running out of devon corp
// (topmost trigger)
#include "scriptlib.m4.h"

// check if player defeated roxanne
CHECK_FLAG( 55, 1, 1 )
    JUMP_TO_END
// check if player has seen the cutscene
CHECK_FLAG( 156, 0, 1 )
    JUMP_TO_END

MESSAGE( 364, 0 )
PLAY_MUSIC( BGM_ENCOUNTER_TEAM_A )
SPAWN_MAPOBJECT( 24, 6, 5 )
    COPY_REGISTER( 0, 1 )
    MOVE_MAPOBJECT_FAST_R( 1, RIGHT, 7 )
    MOVE_MAPOBJECT_FAST_R( 1, UP, 8 )
    DESTROY_MAPOBJECT_R( 1 )
SPAWN_MAPOBJECT( 231, 6, 5 )
    COPY_REGISTER( 0, 1 )
    MOVE_MAPOBJECT_FAST_R( 1, RIGHT, 7 )
    MOVE_MAPOBJECT_R( 1, UP, 0 )
MESSAGE( 365, 0 )
    MOVE_MAPOBJECT_FAST_R( 1, UP, 8 )
    DESTROY_MAPOBJECT_R( 1 )
SET_FLAG( 156, 1 )
REDRAW_OBJECTS
RESTORE_MUSIC
END_OF_PROGRAM
