// force player to bike and lock the move mode
#include "scriptlib.m4.h"

// check if the player is currently biking

CHECK_CURRENT_MOVE_MODE_N( MOVEMODE_WALK, 23 ) // not walking means cycling
    // check if the player owns a bike
    CHECK_ITEM( I_MACH_BIKE, 1, 3 )
        CHANGE_MOVE_MODE( MOVEMODE_MACH_BIKE )
        FORCE_MOVE_MODE
        JUMP_TO_END
    CHECK_ITEM( I_ACRO_BIKE, 1, 3 )
        CHANGE_MOVE_MODE( MOVEMODE_ACRO_BIKE )
        FORCE_MOVE_MODE
        JUMP_TO_END
    CHECK_ITEM( I_BIKE, 1, 3 )
        CHANGE_MOVE_MODE( MOVEMODE_BIKE )
        FORCE_MOVE_MODE
        JUMP_TO_END
    CHECK_ITEM( I_BIKE2, 1, 3 )
        CHANGE_MOVE_MODE( MOVEMODE_BIKE )
        FORCE_MOVE_MODE
        JUMP_TO_END
    // player has no bike, scold them and send them back
    MOVE_PLAYER( UP, 0 )
    MESSAGE( 494, 0 )
    MOVE_PLAYER( LEFT, 1 )
FORCE_MOVE_MODE
END_OF_PROGRAM
