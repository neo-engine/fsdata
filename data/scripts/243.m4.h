// mauville move tutor rollout
#include "scriptlib.m4.h"

GET_CURRENT_MAPOBJECT
LOCK_R( 0 )

MESSAGE( 898, 0 )
YES_NO_MESSAGE( 899, 0, 2 )
    MESSAGE( 900, 0 )
    JUMP_TO_END

MESSAGE( 901, 0 )
MOVE_TUTOR( M_ROLLOUT )

CHECK_REGISTER( 0, 1, 2 )
    MESSAGE( 900, 0 )
    SKIP( 1 )
// else
    MESSAGE( 902, 0 )

GET_CURRENT_MAPOBJECT
UNLOCK_R( 0 )
