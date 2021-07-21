// Player's mom
#include "scriptlib.m4.h"

CHECK_FLAG( 17, 0, 5 ) // Player obtained first pkmn
    MESSAGE( 89, 0 )
    PLAY_MUSIC_ONESHOT( BGM_OS_HEAL_PKMN, 60 )
    HEAL_TEAM
    MESSAGE( 90, 0 )
    JUMP_TO_END
CHECK_FLAG( 14, 0, 2 ) // Player met rival
    MESSAGE( 112, 0 )
    JUMP_TO_END
MESSAGE( 52, 0 )
END_OF_PROGRAM
