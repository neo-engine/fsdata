// verdanturf move tutor fury cutter
#include "scriptlib.m4.h"

GET_CURRENT_MAPOBJECT
LOCK_R( 0 )

MESSAGE( 930, 0 )
YES_NO_MESSAGE( 931, 0, 2 )
    MESSAGE( 932, 0 )
    JUMP_TO_END

MESSAGE( 933, 0 )
MOVE_TUTOR( M_FURY_CUTTER )

CHECK_REGISTER( 0, 1, 2 )
    MESSAGE( 932, 0 )
    SKIP( 1 )
// else
    MESSAGE( 934, 0 )

GET_CURRENT_MAPOBJECT
UNLOCK_R( 0 )
