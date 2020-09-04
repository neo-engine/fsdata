// Old lady giving the player a chesto berry
#include "scriptlib.m4.h"

CHECK_FLAG( 43, 1, 3 )
    MESSAGE( 197, 0 )
    GIVE_ITEM( I_CHESTO_BERRY, 1 )
    SET_FLAG( 43, 1 )
MESSAGE( 198, 0 )
END_OF_PROGRAM
