// slateport fan club chairman
#include "scriptlib.m4.h"

// check if all scarfs collected
CHECK_FLAG( 358, 0, 6 )
    CHECK_FLAG( 359, 0, 5 )
        CHECK_FLAG( 360, 0, 4 )
            CHECK_FLAG( 361, 0, 3 )
                CHECK_FLAG( 362, 0, 2 )
                    MESSAGE( 838, 0 )
                    JUMP_TO_END

CHECK_FLAG( 363, 1, 4 )
    // rant not seen yet
    MESSAGE( 839, 0 )
    SET_FLAG( 363, 1 )
    CHECK_FLAG( 365, 1, 1 )
        // not yet participated in contest
        JUMP_TO_END

CHECK_FLAG( 365, 1, 2 )
    MESSAGE( 840, 0 )
    JUMP_TO_END

CHECK_FLAG( 364, 1, 3 )
    MESSAGE( 841, 0 )
    SET_FLAG( 364, 1 )
    SKIP( 1 )
// else
    MESSAGE( 842, 0 )

// check condition of pkmn 1
IS_EGG( 0 )
CHECK_REGISTER( 0, 0, 2 )
    MESSAGE( 850, 0 )
    JUMP_TO_END

CHECK_FLAG( 358, 1, 7 )
    GET_CONTEST_STAT( 0, 0 )
    CHECK_REGISTER_N( 0, 255, 5 )
        // hand out red scarf
        MESSAGE( 843, 0 )
        GIVE_ITEM( I_RED_SCARF, 1 )
        SET_FLAG( 358, 1 )
        MESSAGE( 844, 0 )
        JUMP_TO_END

CHECK_FLAG( 359, 1, 7 )
    GET_CONTEST_STAT( 0, 1 )
    CHECK_REGISTER_N( 0, 255, 5 )
        // hand out blue scarf
        MESSAGE( 843, 0 )
        GIVE_ITEM( I_BLUE_SCARF, 1 )
        SET_FLAG( 359, 1 )
        MESSAGE( 845, 0 )
        JUMP_TO_END

CHECK_FLAG( 360, 1, 7 )
    GET_CONTEST_STAT( 0, 2 )
    CHECK_REGISTER_N( 0, 255, 5 )
        // hand out pink scarf
        MESSAGE( 843, 0 )
        GIVE_ITEM( I_PINK_SCARF, 1 )
        SET_FLAG( 360, 1 )
        MESSAGE( 846, 0 )
        JUMP_TO_END

CHECK_FLAG( 361, 1, 7 )
    GET_CONTEST_STAT( 0, 3 )
    CHECK_REGISTER_N( 0, 255, 5 )
        // hand out blue scarf
        MESSAGE( 843, 0 )
        GIVE_ITEM( I_GREEN_SCARF, 1 )
        SET_FLAG( 361, 1 )
        MESSAGE( 847, 0 )
        JUMP_TO_END

CHECK_FLAG( 362, 1, 7 )
    GET_CONTEST_STAT( 0, 4 )
    CHECK_REGISTER_N( 0, 255, 5 )
        // hand out blue scarf
        MESSAGE( 843, 0 )
        GIVE_ITEM( I_YELLOW_SCARF, 1 )
        SET_FLAG( 362, 1 )
        MESSAGE( 848, 0 )
        JUMP_TO_END

MESSAGE( 849, 0 )
