// first rival battle on route 103
#include "scriptlib.m4.h"

MESSAGE( 96, 0 )
GET_MAPOBJECT( 31, 24, 3 )
EXCLAMATION_R( 0 )
LOCK_R( 0 )
MOVE_MAPOBJECT_R( 0, LEFT, 0 )
CHECK_FLAG( 5, 1, 1 )
    PLAY_MUSIC( BGM_ENCOUNTER_BRENDAN )
CHECK_FLAG( 5, 0, 1 )
    PLAY_MUSIC( BGM_ENCOUNTER_MAY )
MESSAGE( 97, 0 )
// Rival's team changes depending on the initial starter selection of the player
CHECK_FLAG( 5, 1, 6 ) // Rival is Brendan
    CHECK_VAR_N( 0, 1, 1 ) // player chose treecko
        BATTLE_TRAINER( 1, SINGLE )
    CHECK_VAR_N( 0, 2, 1 ) // player chose torchic
        BATTLE_TRAINER( 2, SINGLE )
    CHECK_VAR_N( 0, 3, 1 ) // player chose mudkip
        BATTLE_TRAINER( 3, SINGLE )
CHECK_FLAG( 5, 0, 6 ) // Rival is May
    CHECK_VAR_N( 0, 1, 1 ) // player chose treecko
        BATTLE_TRAINER( 4, SINGLE )
    CHECK_VAR_N( 0, 2, 1 ) // player chose torchic
        BATTLE_TRAINER( 5, SINGLE )
    CHECK_VAR_N( 0, 3, 1 ) // player chose mudkip
        BATTLE_TRAINER( 6, SINGLE )
// Check if the player managed to win
CHECK_REGISTER( 0, 1, 2 )
    FAINT_PLAYER
    JUMP_TO_END
// player won
GET_MAPOBJECT( 31, 24, 3 )
    MOVE_MAPOBJECT_R( 0, LEFT, 0 )
CHECK_FLAG( 5, 1, 1 )
    PLAY_MUSIC( BGM_ENCOUNTER_BRENDAN )
CHECK_FLAG( 5, 0, 1 )
    PLAY_MUSIC( BGM_ENCOUNTER_MAY )
MESSAGE( 98, 0 )
SET_FLAG( 21, 1 )
WARP_CROSSBANK( 20, 0x30, 0xd0, 3 )
RESTORE_MUSIC
MOVE_PLAYER( UP, 0 )
MESSAGE( 101, 0 )
PLAY_SOUND_EFFECT( SFX_OBTAIN_KEY_ITEM )
SET_FLAG( 3, 1 )
INIT_BOT
MESSAGE( 102, 1 )
MESSAGE( 103, 0 )
GET_MAPOBJECT( 17, 15, 3 )
    LOCK_R( 0 )
    MOVE_MAPOBJECT_R( 0, DOWN, 1 )
    MOVE_MAPOBJECT_R( 0, LEFT, 0 )
    MOVE_PLAYER( RIGHT, 0 )
    MESSAGE( 104, 0 )
    GIVE_ITEM( I_POKE_BALL, 5 )
    MESSAGE( 105, 0 )
    UNLOCK_R( 0 )
END_OF_PROGRAM
