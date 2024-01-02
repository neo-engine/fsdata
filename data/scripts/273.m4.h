// rival battle r110 (left tile)
#include "scriptlib.m4.h"

GET_MAPOBJECT( 2, 14, 3 )
COPY_REGISTER( 0, 1 )
LOCK_R( 1 )

MOVE_MAPOBJECT_R( 1, DOWN, 0 )
EXCLAMATION_R( 1 )
MOVE_MAPOBJECT_R( 1, LEFT, 1 )
MOVE_MAPOBJECT_R( 1, DOWN, 1 )

CHECK_FLAG( 5, 0, 13 )
    // Rival is may
    MESSAGE( 1069, 0 )
    CHECK_VAR_N( 0, 1, 1 ) // player chose treecko
        BATTLE_TRAINER( 107, SINGLE )
    CHECK_VAR_N( 0, 2, 1 ) // player chose torchic
        BATTLE_TRAINER( 108, SINGLE )
    CHECK_VAR_N( 0, 3, 1 ) // player chose mudkip
        BATTLE_TRAINER( 109, SINGLE )

    CHECK_REGISTER( 0, 1, 2 )
        FAINT_PLAYER
        JUMP_TO_END

    MESSAGE( 1070, 0 )
    GIVE_ITEM( I_POKE_RADAR, 1 )
    MESSAGE( 1071, 0 )

CHECK_FLAG( 5, 1, 13 )
    // Rival is brendan
    MESSAGE( 1072, 0 )
    CHECK_VAR_N( 0, 1, 1 ) // player chose treecko
        BATTLE_TRAINER( 110, SINGLE )
    CHECK_VAR_N( 0, 2, 1 ) // player chose torchic
        BATTLE_TRAINER( 111, SINGLE )
    CHECK_VAR_N( 0, 3, 1 ) // player chose mudkip
        BATTLE_TRAINER( 112, SINGLE )

    CHECK_REGISTER( 0, 1, 2 )
        FAINT_PLAYER
        JUMP_TO_END

    MESSAGE( 1073, 0 )
    GIVE_ITEM( I_POKE_RADAR, 1 )
    MESSAGE( 1074, 0 )


GET_MAPOBJECT( 1, 15, 3 )
MOVE_MAPOBJECT_R( 0, UP, 7 )
DESTROY_MAPOBJECT_R( 0 )
SET_FLAG( 388, 1 )

END_OF_PROGRAM

