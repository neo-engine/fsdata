// lilycove ferry terminal
#include "scriptlib.m4.h"

// script to warp to new lilycove

YES_NO_MESSAGE( 1051, 0, 2 )
MESSAGE( 1050, 0 )
JUMP_TO_END

MESSAGE( 1053, 0 )

GET_CURRENT_MAPOBJECT
FIX_MAPOBJECT_R( 0 )
ATTACH_PLAYER
MOVE_MAPOBJECT_R( 0, UP, 1 )
UNFIX_MAPOBJECT_R( 0 )
DESTROY_MAPOBJECT( 0 )
MOVE_PLAYER( UP, 1 )
HIDE_PLAYER

WARP_CROSSBANK( 20, 14 * 32 + 13, 10 * 32 + 21, 3 )
MOVE_PLAYER( DOWN, 0 )

// add options

// new lilycove
// slateport (post-game)
// battle frontier (post game)
