// slateport fan club soothe bell
#include "scriptlib.m4.h"

CHECK_FLAG( 357, 0, 2 )
    // bell obtained
    MESSAGE( 835, 0 )
    JUMP_TO_END

MESSAGE( 836, 0 )

IS_EGG( 0 )
CHECK_REGISTER( 0, 0, 1 )
    JUMP_TO_END

GET_FRIENDSHIP( 0 )
// check if friendship is at least 200
CHECK_REGISTER_G( 0, 199, 1 )
    JUMP_TO_END
//else
    GET_CURRENT_MAPOBJECT
    EXCLAMATION_R( 0 )
    MESSAGE( 837, 0 )
    GIVE_ITEM( I_SOOTHE_BELL, 1 )
    SET_FLAG( 357, 1 )
    JUMP_TO_END
