// devon corp 3f, player getting TM protect
#include "scriptlib.m4.h"

HIDE_PKMN
CHECK_FLAG( 164, 0, 1 )
    JUMP_TO_END
MOVE_PLAYER( RIGHT, 0 )
// ask player if they want to deliver the goods to slateport
YES_NO_MESSAGE_N( 383, 0, 32 )
    // player wants to help
    CHECK_ITEM( I_DEVON_GOODS, 1, 2 )
        MESSAGE( 384, 0 )
        SKIP( 2 )
        MESSAGE( 408, 0 )
        GIVE_ITEM( I_DEVON_GOODS, 1 )
    MESSAGE( 385, 0 )
    GET_MAPOBJECT( 9, 14, 3 )
    COPY_REGISTER( 0, 1 )
    MOVE_MAPOBJECT_R( 1, DOWN, 1 )
    MOVE_MAPOBJECT_R( 1, RIGHT, 8 )
    MOVE_MAPOBJECT_R( 1, LEFT, 8 )
    MOVE_MAPOBJECT_R( 1, UP, 1 )
    MOVE_MAPOBJECT_R( 1, LEFT, 0 )
    MESSAGE( 386, 0 )
    ATTACH_PLAYER
    MOVE_MAPOBJECT_R( 1, DOWN, 1 )
    MOVE_MAPOBJECT_R( 1, RIGHT, 12 )
    REMOVE_PLAYER
    MOVE_MAPOBJECT_R( 1, LEFT, 0 )
    MESSAGE( 387, 0 )
    MOVE_PLAYER( DOWN, 2 )
    MOVE_PLAYER( RIGHT, 0 )
    MESSAGE( 388, 0 )
    GIVE_ITEM( I_LETTER, 1 )
    MESSAGE( 389, 0 )
    GIVE_ITEM( I_TM25, 1 )
    MESSAGE( 390, 0 )
    SET_FLAG( 165, 1 )
    SET_FLAG( 170, 1 )
    SET_ROUTE( 1 )
    SKIP( 27 )
    // player doesn't want to help
    MESSAGE( 409, 0 )
    CHECK_ITEM( I_DEVON_GOODS, 1, 2 )
        MESSAGE( 410, 0 )
        TAKE_ITEM( I_DEVON_GOODS, 1 )
    MESSAGE( 385, 0 )
    GET_MAPOBJECT( 9, 14, 3 )
    COPY_REGISTER( 0, 1 )
    MOVE_MAPOBJECT_R( 1, DOWN, 1 )
    MOVE_MAPOBJECT_R( 1, RIGHT, 8 )
    MOVE_MAPOBJECT_R( 1, LEFT, 8 )
    MOVE_MAPOBJECT_R( 1, UP, 1 )
    MOVE_MAPOBJECT_R( 1, LEFT, 0 )
    MESSAGE( 386, 0 )
    ATTACH_PLAYER
    MOVE_MAPOBJECT_R( 1, DOWN, 1 )
    MOVE_MAPOBJECT_R( 1, RIGHT, 12 )
    REMOVE_PLAYER
    MOVE_MAPOBJECT_R( 1, LEFT, 0 )
    MESSAGE( 387, 0 )
    MOVE_PLAYER( DOWN, 2 )
    MOVE_PLAYER( RIGHT, 0 )
    MESSAGE( 411, 0 )
    GIVE_ITEM( I_TM25, 1 )
    MESSAGE( 390, 0 )
    SET_FLAG( 166, 1 )
    SET_ROUTE( 2 )

SET_FLAG( 164, 1 )
WARP_CROSSBANK( 10, 0x44,0xc0, 3 )
MOVE_PLAYER( DOWN, 0 )
END_OF_PROGRAM
