// mr brine
#include "scriptlib.m4.h"

// check if one or two options are available
// (i.e. whether the mission in dewford is done already)
SET_REGISTER( 4, 0 )
CHECK_FLAG( 166, 0, 3 )
    CHECK_FLAG( 150, 0, 2 )
        SET_REGISTER( 4, 1 )
        SKIP( 2 )
    CHECK_FLAG( 172, 0, 1 )
        SET_REGISTER( 4, 1 )

CHECK_REGISTER( 4, 0, 8 )
    // player has two options, build choice box
    MESSAGE( 431, 0 )
    CBOX_BEGIN( 439, 0 )
    CBOX_ITEM( 435, 1 )
    CBOX_ITEM( 436, 2 )
    CBOX_ITEM( 437, 0 )
    CBOX_RUN
    COPY_REGISTER( 1, EVAL_REG )
    SKIP( 4 )

CHECK_FLAG( 166, 1, 2 )
    YES_NO_MESSAGE_D( 418, 0 )
    SKIP( 1 )
    YES_NO_MESSAGE_D( 421, 0 )

CHECK_REGISTER_N( EVAL_REG, 0, 8 )
    // player doesn't want to sail back
    CHECK_REGISTER( 4, 0, 2 )
        MESSAGE( 433, 0 )
        JUMP_TO_END
    CHECK_FLAG( 166, 1, 2 )
        MESSAGE( 419, 0 )
        JUMP_TO_END
        MESSAGE( 429, 0 )
    JUMP_TO_END

CHECK_REGISTER_N( EVAL_REG, 1, 46 )
    // player wants to sail back to r104
    MESSAGE( 420, 0 )
    HIDE_PKMN
        WALK_PLAYER( UP, 1 )
        HIDE_PLAYER
        GET_MAPOBJECT( 1, 9, 3 )
            COPY_REGISTER( 0, 1 )
            MOVE_MAPOBJECT_R( 1, LEFT, 1 )
            MOVE_MAPOBJECT_R( 1, UP, 1 )
        DESTROY_MAPOBJECT_R( 1 )
    // start boat trip
    SET_FLAG( 168, 1 )
    SET_FLAG( 169, 1 )
    PLAY_MUSIC( BGM_SAILING )
        GET_MAPOBJECT( 0, 8, 5 )
            COPY_REGISTER( 0, 1 )
            FIX_MAPOBJECT_R( 1 )
            ATTACH_PLAYER
            MOVE_MAPOBJECT_R( 1, UP, 5 )
            MOVE_MAPOBJECT_FAST_R( 1, UP, 9 )
            MOVE_MAPOBJECT_R( 1, UP, 5 )
            MOVE_MAPOBJECT_R( 1, LEFT, 5 )
            MOVE_MAPOBJECT_FAST_R( 1, LEFT, 40 )
            MOVE_MAPOBJECT_R( 1, LEFT, 5 )
            MOVE_MAPOBJECT_R( 1, UP, 5 )
            MOVE_MAPOBJECT_FAST_R( 1, UP, 78 )
            MOVE_MAPOBJECT_R( 1, UP, 5 )
            MOVE_MAPOBJECT_R( 1, LEFT, 10 )
            MOVE_MAPOBJECT_R( 1, UP, 5 )
            MOVE_MAPOBJECT_FAST_R( 1, UP, 17 )
            MOVE_MAPOBJECT_R( 1, UP, 5 )
        REMOVE_PLAYER
    RESTORE_MUSIC
    SET_FLAG( 168, 0 )
    SET_FLAG( 169, 0 )
    SPAWN_MAPOBJECT( 62, 4, 1 )
        COPY_REGISTER( 0, 2 )
        MOVE_MAPOBJECT_R( 2, UP, 1 )
        MOVE_MAPOBJECT_R( 2, RIGHT, 1 )
        MOVE_MAPOBJECT_R( 2, LEFT, 0 )
    UNFIX_MAPOBJECT_R( 1 )
    UNFIX_MAPOBJECT_R( 2 )
    SHOW_PLAYER
    WALK_PLAYER( UP, 2 )
    MOVE_PLAYER( RIGHT, 0 )

    WARP_CROSSBANK( 20, 0x2f, 0x110, 3 )
    JUMP_TO_END

// player wants to sail to slateport
MESSAGE( 430, 0 )
HIDE_PKMN

    WALK_PLAYER( UP, 1 )
    HIDE_PLAYER
    GET_MAPOBJECT( 1, 9, 3 )
        COPY_REGISTER( 0, 1 )
        MOVE_MAPOBJECT_R( 1, LEFT, 1 )
        MOVE_MAPOBJECT_R( 1, UP, 1 )
    DESTROY_MAPOBJECT_R( 1 )
// start boat trip
SET_FLAG( 168, 1 )
SET_FLAG( 169, 1 )
PLAY_MUSIC( BGM_SAILING )
    GET_MAPOBJECT( 0, 8, 5 )
        COPY_REGISTER( 0, 1 )
        FIX_MAPOBJECT_R( 1 )
        ATTACH_PLAYER
            MOVE_MAPOBJECT_R( 1, RIGHT, 5 )
            MOVE_MAPOBJECT_FAST_R( 1, RIGHT, 138 )
            MOVE_MAPOBJECT_R( 1, RIGHT, 5 )
            MOVE_MAPOBJECT_R( 1, UP, 5 )
            MOVE_MAPOBJECT_FAST_R( 1, UP, 12 )
            MOVE_MAPOBJECT_R( 1, UP, 5 )
        REMOVE_PLAYER
    RESTORE_MUSIC
    SHOW_PLAYER
    WALK_PLAYER( UP, 3 )
    MOVE_PLAYER( DOWN, 0 )
    SET_FLAG( 168, 0 )
    SET_FLAG( 169, 0 )
    SPAWN_MAPOBJECT( 62, 20, 17 )
        COPY_REGISTER( 0, 2 )
        MOVE_MAPOBJECT_R( 2, UP, 1 )
    MESSAGE( 441, 0 )

    UNFIX_MAPOBJECT_R( 1 )
    UNFIX_MAPOBJECT_R( 2 )
    DESTROY_MAPOBJECT_R( 1 )
    DESTROY_MAPOBJECT_R( 2 )
REDRAW_OBJECTS
JUMP_TO_END
