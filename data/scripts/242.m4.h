// icave scientist trading cherish balls for premier balls
#include "scriptlib.m4.h"
#define V_INFINITY_CAVE_MAX_LAYER 38

// unless explored 30 rooms, trade is not available
CHECK_VAR_G( V_INFINITY_CAVE_MAX_LAYER, 14, 2 )
    MESSAGE( 877, 0 )
    JUMP_TO_END

CHECK_VAR_G( V_INFINITY_CAVE_MAX_LAYER, 29, 2 )
    MESSAGE( 878, 0 )
    JUMP_TO_END

MESSAGE( 879, 0 )

CHECK_ITEM( I_PREMIER_BALL, 1, 1 )
    SKIP( 1 )
// else
    JUMP_TO_END

// check if the player has a premier ball

YES_NO_MESSAGE( 880, 1, 1 )
    JUMP_TO_END

TAKE_ITEM( I_PREMIER_BALL, 1 )
MESSAGE( 881, 0 )
GIVE_ITEM( I_INFINITY_BALL, 1 )
MESSAGE( 882, 0 )
