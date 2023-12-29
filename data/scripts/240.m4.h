// slateport fan club move tutor swagger
#include "scriptlib.m4.h"

GET_CURRENT_MAPOBJECT
LOCK_R( 0 )

MESSAGE( 851, 0 )
YES_NO_MESSAGE( 852, 0, 2 )
    MESSAGE( 853, 0 )
    JUMP_TO_END

MESSAGE( 854, 0 )
MOVE_TUTOR( M_SWAGGER )

CHECK_REGISTER( 0, 1, 1 )
    MESSAGE( 853, 0 )

GET_CURRENT_MAPOBJECT
UNLOCK_R( 0 )
