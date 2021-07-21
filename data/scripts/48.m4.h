// rival battle in rustboro
#include "scriptlib.m4.h"

HIDE_PKMN
CHECK_FLAG( 5, 1, 1 )
    SPAWN_MAPOBJECT( 0, 13, 12 )
CHECK_FLAG( 5, 0, 1 )
    SPAWN_MAPOBJECT( 1, 13, 12 )
MOVE_MAPOBJECT_R( 0, UP, 7 )
MOVE_MAPOBJECT_R( 0, RIGHT, 0 )
EXCLAMATION_R( 0 )
CHECK_FLAG( 5, 1, 1 )
    PLAY_MUSIC( BGM_ENCOUNTER_BRENDAN )
CHECK_FLAG( 5, 0, 1 )
    PLAY_MUSIC( BGM_ENCOUNTER_MAY )
MOVE_PLAYER( LEFT, 0 )
MOVE_MAPOBJECT_R( 0, RIGHT, 5 )
MESSAGE( 260, 0 )
// Rival's team changes depending on the initial starter selection of the player
CHECK_FLAG( 5, 1, 9 ) // Rival is Brendan
    CHECK_VAR_N( 0, 1, 1 ) // player chose treecko
        BATTLE_TRAINER( 27, SINGLE )
    CHECK_VAR_N( 0, 2, 1 ) // player chose torchic
        BATTLE_TRAINER( 28, SINGLE )
    CHECK_VAR_N( 0, 3, 1 ) // player chose mudkip
        BATTLE_TRAINER( 29, SINGLE )
    CHECK_REGISTER( 0, 1, 2 )
        FAINT_PLAYER
        JUMP_TO_END
CHECK_FLAG( 5, 0, 9 ) // Rival is May
    CHECK_VAR_N( 0, 1, 1 ) // player chose treecko
        BATTLE_TRAINER( 30, SINGLE )
    CHECK_VAR_N( 0, 2, 1 ) // player chose torchic
        BATTLE_TRAINER( 31, SINGLE )
    CHECK_VAR_N( 0, 3, 1 ) // player chose mudkip
        BATTLE_TRAINER( 32, SINGLE )
// Check if the player managed to win
    CHECK_REGISTER( 0, 1, 2 )
        FAINT_PLAYER
        JUMP_TO_END
SET_FLAG( 56, 1 )
// player won
CHECK_FLAG( 5, 1, 1 )
    PLAY_MUSIC( BGM_ENCOUNTER_BRENDAN )
CHECK_FLAG( 5, 0, 1 )
    PLAY_MUSIC( BGM_ENCOUNTER_MAY )
GET_MAPOBJECT( 18, 5, 3 )
    MOVE_MAPOBJECT_R( 0, RIGHT, 0 )
    MESSAGE( 261, 0 )
    MOVE_MAPOBJECT_R( 0, LEFT, 5 )
    MOVE_MAPOBJECT_R( 0, UP, 7 )
    DESTROY_MAPOBJECT_R( 0 )
RESTORE_MUSIC
END_OF_PROGRAM
