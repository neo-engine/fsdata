// jirachi in crystal cavern
#include "scriptlib.m4.h"

// Check if all 4 crystals are activated
CHECK_FLAG( 216, 0, 4 )
CHECK_FLAG( 217, 0, 3 )
CHECK_FLAG( 218, 0, 2 )
CHECK_FLAG( 219, 0, 1 )

SKIP( 3 )
    MESSAGE( 533, 0 )
    REGISTER_SEEN( PKMN_JIRACHI )
    JUMP_TO_END

CHECK_FLAG( 220, 1, 2 )
    MESSAGE( 535, 0 )
    SKIP( 1 )
    MESSAGE( 536, 0 )
SET_FLAG( 220, 1 )
PLAY_MUSIC( BGM_BATTLE_WILD_ALT )
BATTLE_PKMN( PKMN_JIRACHI, 15 )
RESTORE_MUSIC

CHECK_REGISTER( 0, 1, 3 )
    // player somehow managed to lose against Jirachi
    MESSAGE( 537, 0 )
    FAINT_PLAYER
    JUMP_TO_END

CHECK_REGISTER( 1, 1, 2 )
    // player did not capture jirachi
    MESSAGE( 537, 0 )
    JUMP_TO_END

SET_FLAG( 215, 1 )
REDRAW_OBJECTS
END_OF_PROGRAM
