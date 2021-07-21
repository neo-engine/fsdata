// rival's entry
#include "scriptlib.m4.h"

CHECK_FLAG( 5, 1, 1 ) // Should only activate when the rival has appearance 0
    JUMP_TO_END
CHECK_FLAG( 12, 0, 1 )
    JUMP_TO_END
SPAWN_MAPOBJECT( 1, 12, 27 )
    MOVE_MAPOBJECT_R( 0, UP, 2 )
    EXCLAMATION_R( 0 ) // Show exclamation mark
    MESSAGE( 74, 0 )
    PLAY_MUSIC( BGM_ENCOUNTER_MAY )
    // Check where the player is standing, move May accordingly
    MOVE_PLAYER( DOWN, 1 )
    MOVE_MAPOBJECT_R( 0, UP, 1 )
    MESSAGE( 67, 0 )
    MOVE_MAPOBJECT_R( 0, RIGHT, 1 )
    MOVE_MAPOBJECT_R( 0, UP, 2 )
    MOVE_MAPOBJECT_R( 0, LEFT, 1 )
    MOVE_MAPOBJECT_R( 0, UP, 1 )
    PLAY_SOUND_EFFECT( SFX_CAVE_WARP )
    SET_FLAG( 12, 1 )
DESTROY_MAPOBJECT_R( 0 )
REDRAW_OBJECTS
RESTORE_MUSIC
END_OF_PROGRAM
