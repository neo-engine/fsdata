// rescue wailmer
#include "scriptlib.m4.h"

MESSAGE( 447, 0 )

SET_REGISTER( 4, 0 )
CHECK_ITEM( I_POTION, 1, 5 )
    YES_NO_MESSAGE( 448, 0, 1 )
        JUMP_TO_END
    USE_ITEM( I_POTION, 1 )
    SKIP( 6 )

CHECK_ITEM( I_SUPER_POTION, 1, 5 )
    YES_NO_MESSAGE( 448, 0, 1 )
        JUMP_TO_END
    USE_ITEM( I_SUPER_POTION, 1 )
    SKIP( 6 )

CHECK_ITEM( I_HYPER_POTION, 1, 5 )
    YES_NO_MESSAGE( 448, 0, 1 )
        JUMP_TO_END
    USE_ITEM( I_HYPER_POTION, 1 )
    SKIP( 6 )

CHECK_ITEM( I_MAX_POTION, 1, 5 )
    YES_NO_MESSAGE( 448, 0, 1 )
        JUMP_TO_END
    USE_ITEM( I_MAX_POTION, 1 )
    SKIP( 6 )

CHECK_ITEM( I_FULL_RESTORE, 1, 5 )
    YES_NO_MESSAGE( 448, 0, 1 )
        JUMP_TO_END
    USE_ITEM( I_FULL_RESTORE, 1 )

// battle wailmer
MESSAGE( 449, 0 )
SET_FLAG( 173, 1 )
PLAY_MUSIC( BGM_BATTLE_WILD )
BATTLE_PKMN( 320, 15 )
RESTORE_MUSIC
CHECK_REGISTER( 0, 1, 3 )
    SET_FLAG( 173, 0 )
    FAINT_PLAYER
    JUMP_TO_END

CHECK_REGISTER( 1, 1, 1 )
    // player did not capture wailmer
    MESSAGE( 450, 0 )

END_OF_PROGRAM
