// old dude w/ old sea map
#include "scriptlib.m4.h"

CHECK_FLAG( 50, 0, 2 )
    MESSAGE( 224, 0 )
    JUMP_TO_END
MESSAGE( 221, 0 )
CHECK_ITEM( I_WISHING_CHARM, 1, 7 )
    YES_NO_MESSAGE( 222, 1, 1 )
        JUMP_TO_END
    MESSAGE( 223, 0 )
    GIVE_ITEM( I_OLD_SEA_MAP, 1 )
    MESSAGE( 224, 0 )
    SET_FLAG( 50, 1 )
END_OF_PROGRAM
