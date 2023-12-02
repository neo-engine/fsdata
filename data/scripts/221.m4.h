// infinity cave hiker
#include "scriptlib.m4.h"

MESSAGE( 690, 0 )

// Obtain current best streak, hand out TMs for every 10 rooms clreared
#define V_INFINITY_CAVE_MAX_LAYER 38
CHECK_FLAG( 349, 1, 6 )
    CHECK_VAR_L( V_INFINITY_CAVE_MAX_LAYER, 90, 5 )
        MESSAGE( 692, 0 )
        GIVE_ITEM( I_TM37, 1 )
        SET_FLAG( 349, 1 )
        MESSAGE( 693, 0 )
    JUMP_TO_END

CHECK_FLAG( 348, 1, 6 )
    CHECK_VAR_L( V_INFINITY_CAVE_MAX_LAYER, 80, 5 )
        MESSAGE( 692, 0 )
        GIVE_ITEM( I_TM08, 1 )
        SET_FLAG( 348, 1 )
        MESSAGE( 693, 0 )
    JUMP_TO_END


CHECK_FLAG( 347, 1, 6 )
    CHECK_VAR_L( V_INFINITY_CAVE_MAX_LAYER, 70, 5 )
        MESSAGE( 692, 0 )
        GIVE_ITEM( I_TM94, 1 )
        SET_FLAG( 347, 1 )
        MESSAGE( 693, 0 )
    JUMP_TO_END


CHECK_FLAG( 346, 1, 6 )
    CHECK_VAR_L( V_INFINITY_CAVE_MAX_LAYER, 60, 5 )
        MESSAGE( 692, 0 )
        GIVE_ITEM( I_TM77, 1 )
        SET_FLAG( 346, 1 )
        MESSAGE( 693, 0 )
    JUMP_TO_END


CHECK_FLAG( 345, 1, 6 )
    CHECK_VAR_L( V_INFINITY_CAVE_MAX_LAYER, 50, 5 )
        MESSAGE( 692, 0 )
        GIVE_ITEM( I_TM85, 1 )
        SET_FLAG( 345, 1 )
        MESSAGE( 693, 0 )
    JUMP_TO_END


CHECK_FLAG( 344, 1, 6 )
    CHECK_VAR_L( V_INFINITY_CAVE_MAX_LAYER, 40, 5 )
        MESSAGE( 692, 0 )
        GIVE_ITEM( I_TM86, 1 )
        SET_FLAG( 344, 1 )
        MESSAGE( 693, 0 )
    JUMP_TO_END


CHECK_FLAG( 343, 1, 6 )
    CHECK_VAR_L( V_INFINITY_CAVE_MAX_LAYER, 30, 5 )
        MESSAGE( 692, 0 )
        GIVE_ITEM( I_TM93, 1 )
        SET_FLAG( 343, 1 )
        MESSAGE( 693, 0 )
    JUMP_TO_END


CHECK_FLAG( 342, 1, 6 )
    CHECK_VAR_L( V_INFINITY_CAVE_MAX_LAYER, 20, 5 )
        MESSAGE( 692, 0 )
        GIVE_ITEM( I_TM18, 1 )
        SET_FLAG( 342, 1 )
        MESSAGE( 693, 0 )
        JUMP_TO_END


CHECK_VAR_L( V_INFINITY_CAVE_MAX_LAYER, 10, 6 )
    CHECK_FLAG( 341, 1, 2 )
        MESSAGE( 692, 0 )
        GIVE_ITEM( I_TM17, 1 )
        SET_FLAG( 341, 1 )
        MESSAGE( 693, 0 )
    JUMP_TO_END


MESSAGE( 691, 0 )
