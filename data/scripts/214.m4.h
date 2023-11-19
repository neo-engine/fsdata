// (route 2)
// aqua grunt offering ride to lilycove
#include "scriptlib.m4.h"

CHECK_FLAG( 326, 1, 1 )
    MESSAGE( 677, 0 )
SET_FLAG( 326, 1 )
YES_NO_MESSAGE( 678, 0, 2 )
    MESSAGE( 679, 0 )
    JUMP_TO_END
MESSAGE( 680, 0 )
WARP_CROSSBANK( 10, 0x259, 0x8d, 3 )
// warp to lilycove
