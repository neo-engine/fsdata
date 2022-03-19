// slateport battle tent, tent clerk
#include "scriptlib.m4.h"

// ask player if they want

MESSAGE( 510, 0 )
CBOX_BEGIN( 511, 0 )
CBOX_ITEM( 512, 1 )
CBOX_ITEM( 513, 2 )
CBOX_ITEM( 514, 0 )
CBOX_RUN
COPY_REGISTER( 1, EVAL_REG )

CHECK_REGISTER_N( EVAL_REG, 0, 2 )
    MESSAGE( 517, 0 )
    JUMP_TO_END
CHECK_REGISTER_N( EVAL_REG, 2, 2 )
    MESSAGE( 516, 0 )
    JUMP_TO_END

// ask player if they want to save the game
YES_NO_MESSAGE( 515, 0, 2 )
    MESSAGE( 517, 0 )
    JUMP_TO_END

// Mark current battle tent streak as ended
CHECK_FLAG( 194, 0, 1 )
    SET_REGISTER( 2, 1 )
SET_FLAG( 194, 0 )
FORCE_SAVE_GAME
CHECK_REGISTER_N( 2, 1, 1 )
    SET_FLAG( 194, 1 )

CHECK_REGISTER_N( 0, 1, 22 )
    MESSAGE( 518, 0 )
    GET_MAPOBJECT( 15, 24, 3 )
    COPY_REGISTER( 0, 3 )
    MOVE_MAPOBJECT_R( 3, UP, 1 )
    MOVE_MAPOBJECT_R( 3, RIGHT, 1 )
    MOVE_MAPOBJECT_R( 3, LEFT, 0 )
    HIDE_PKMN
    MOVE_PLAYER( UP, 10 )
    MOVE_PLAYER( RIGHT, 0 )
    REDRAW_OBJECTS
    MOVE_MAPOBJECT_R( 3, LEFT, 1 )
    MOVE_MAPOBJECT_R( 3, DOWN, 1 )

    // run the actual battle factory script
    BATTLE_FACTORY( 0, 3 )

    // script returned

    MOVE_PLAYER( DOWN, 6 )
    GET_MAPOBJECT( 15, 24, 3 )
    COPY_REGISTER( 0, 3 )
    MOVE_MAPOBJECT_R( 3, UP, 1 )
    MOVE_MAPOBJECT_R( 3, RIGHT, 1 )
    MOVE_MAPOBJECT_R( 3, LEFT, 0 )
    MOVE_PLAYER( DOWN, 3 )
    MOVE_PLAYER( UP, 0 )
    MOVE_MAPOBJECT_R( 3, LEFT, 1 )
    MOVE_MAPOBJECT_R( 3, DOWN, 1 )
    FORCE_SAVE_GAME

// saving aborted / failed
MESSAGE( 517, 0 )
END_OF_PROGRAM

