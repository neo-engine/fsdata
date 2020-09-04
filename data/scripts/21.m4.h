// pokemart dude in oldale giving the player a tour and a potion
#include "scriptlib.m4.h"

CHECK_FLAG( 18, 1, 2 )
    MESSAGE( 94, 0 )
    GIVE_ITEM( I_POTION, 3 )
MESSAGE( 95, 0 )
SET_FLAG( 18, 1 )
END_OF_PROGRAM
