// Team Aqua grunt encounter in Petalburg woods
#include "scriptlib.m4.h"

MOVE_PLAYER( UP, 0 )
GET_MAPOBJECT( 2, 29, 3 ) // devon scientist
    WAIT( 60 )
    LOCK_R( 0 )
    MESSAGE( 175, 0 )
    MOVE_MAPOBJECT_R( 0, DOWN, 1 )
    MESSAGE( 176, 0 )
    COPY_REGISTER( 0, 1 )
    SPAWN_MAPOBJECT( 24, 1, 25 ) // Aqua grunt
    MOVE_MAPOBJECT_R( 0, DOWN, 1 )
    MOVE_MAPOBJECT_R( 0, RIGHT, 1 )
    MOVE_MAPOBJECT_R( 0, DOWN, 1 )
    PLAY_MUSIC( BGM_ENCOUNTER_TEAM_A )
    MESSAGE( 177, 0 )
    MOVE_MAPOBJECT_R( 0, DOWN, 2 )
    MOVE_MAPOBJECT_R( 1, UP, 0 )
    MESSAGE( 178, 0 )
    MOVE_MAPOBJECT_FAST_R( 1, RIGHT, 1 )
    HIDE_PKMN
    MOVE_MAPOBJECT_FAST_R( 1, DOWN, 2 )
    MOVE_MAPOBJECT_FAST_R( 1, LEFT, 1 )
    MOVE_MAPOBJECT_FAST_R( 1, UP, 0 )
    MESSAGE( 179, 0 )
    COPY_REGISTER( 0, 2 )
    SET_FLAG( 35, 1 )
    YES_NO_MESSAGE( 180, 1, 31 ) // Ask if the player wants to help
        // Player doesn't want to help
        HIDE_PKMN
        MOVE_PLAYER( RIGHT, 1 )
        MOVE_PLAYER( DOWN, 0 )
        GET_MAPOBJECT( 2, 29, 3 )
        COPY_REGISTER( 0, 2 )
        MOVE_MAPOBJECT_R( 2, DOWN, 2 )
        MOVE_MAPOBJECT_FAST_R( 2, DOWN, 1 )
        MOVE_MAPOBJECT_FAST_R( 2, UP, 1 )
        MOVE_MAPOBJECT_R( 2, DOWN, 0 )
        SET_FLAG( 36, 0 )
        SET_FLAG( 38, 1 )
        MESSAGE( 190, 0 )
        MESSAGE( 187, 1 )
        WAIT( 20 )
        MESSAGE( 188, 0 )
        MOVE_MAPOBJECT_FAST_R( 2, UP, 5 )
        MOVE_MAPOBJECT_FAST_R( 2, LEFT, 5 )
        DESTROY_MAPOBJECT_R( 2 )
        RESTORE_MUSIC
        MOVE_MAPOBJECT_R( 1, UP, 1 )
        MOVE_MAPOBJECT_R( 1, RIGHT, 0 )
        MOVE_PLAYER( LEFT, 0 )
        MESSAGE( 189, 0 )
        GIVE_ITEM( I_EXP_ALL, 1 )
        MESSAGE( 184, 0 )
        MESSAGE( 185, 0 )
        MOVE_MAPOBJECT_FAST_R( 1, UP, 5 )
        MOVE_MAPOBJECT_FAST_R( 1, LEFT, 5 )
        DESTROY_MAPOBJECT_R( 1 )
        REDRAW_OBJECTS
        JUMP_TO_END
    // else (player wants to help
        MOVE_MAPOBJECT_R( 2, DOWN, 1 )
        MESSAGE( 181, 0 )
        SET_FLAG( 36, 1 )
        BATTLE_TRAINER( 15, SINGLE )
        HIDE_PKMN
        PLAY_MUSIC( BGM_ENCOUNTER_TEAM_A )
        REDRAW_OBJECTS
        // Check if the player managed to win
        CHECK_REGISTER( 0, 1, 34 )
            // They didn't
            HEAL_TEAM
            GET_MAPOBJECT( 2, 32, 3 ) // Devon scientist
            COPY_REGISTER( 0, 1 )
            MOVE_MAPOBJECT_R( 1, UP, 0 )
            SET_FLAG( 37, 1 )
            GET_MAPOBJECT( 2, 30, 3 ) // aqua grunt
            COPY_REGISTER( 0, 2 )
            MESSAGE( 186, 0 )
            MOVE_PLAYER( RIGHT, 1 )
            MOVE_PLAYER( DOWN, 0 )
            MOVE_MAPOBJECT_R( 2, DOWN, 1 )
            MOVE_MAPOBJECT_FAST_R( 2, DOWN, 1 )
            MOVE_MAPOBJECT_FAST_R( 2, UP, 1 )
            MOVE_MAPOBJECT_R( 2, DOWN, 0 )
            MESSAGE( 190, 0 )
            MESSAGE( 187, 1 )
            MESSAGE( 188, 0 )
            MOVE_MAPOBJECT_FAST_R( 2, UP, 5 )
            MOVE_MAPOBJECT_FAST_R( 2, LEFT, 5 )
            DESTROY_MAPOBJECT_R( 2 )
            RESTORE_MUSIC
            MOVE_MAPOBJECT_R( 1, UP, 1 )
            MOVE_MAPOBJECT_R( 1, RIGHT, 0 )
            MOVE_PLAYER( LEFT, 0 )
            MESSAGE( 189, 0 )
            GIVE_ITEM( I_EXP_ALL, 1 )
            MESSAGE( 184, 0 )
            MESSAGE( 185, 0 )
            MOVE_MAPOBJECT_FAST_R( 1, UP, 5 )
            MOVE_MAPOBJECT_FAST_R( 1, LEFT, 5 )
            DESTROY_MAPOBJECT_R( 1 )
            SET_FLAG( 38, 1 )
            REDRAW_OBJECTS
            JUMP_TO_END
        // else (player managed to win)
            GET_MAPOBJECT( 2, 32, 3 ) // Devon scientist
            COPY_REGISTER( 0, 1 )
            MOVE_MAPOBJECT_R( 1, UP, 0 )
            SET_FLAG( 37, 1 )
            GET_MAPOBJECT( 2, 30, 3 ) // aqua grunt
            COPY_REGISTER( 0, 2 )
            MOVE_MAPOBJECT_R( 2, UP, 1 )
            MOVE_MAPOBJECT_R( 2, DOWN, 0 )
            MESSAGE( 182, 0 )
            MOVE_MAPOBJECT_FAST_R( 2, UP, 3 )
            MOVE_MAPOBJECT_FAST_R( 2, LEFT, 5 )
            DESTROY_MAPOBJECT_R( 2 )
            RESTORE_MUSIC
            MOVE_PLAYER( RIGHT, 1 )
            MOVE_PLAYER( LEFT, 0 )
            MOVE_MAPOBJECT_R( 1, UP, 1 )
            MOVE_MAPOBJECT_R( 1, RIGHT, 0 )
            MESSAGE( 183, 0 )
            GIVE_ITEM( I_EXP_ALL, 1 )
            MESSAGE( 184, 0 )
            MESSAGE( 185, 0 )
            MOVE_MAPOBJECT_FAST_R( 1, UP, 5 )
            MOVE_MAPOBJECT_FAST_R( 1, LEFT, 5 )
            DESTROY_MAPOBJECT_R( 1 )
            SET_FLAG( 38, 1 )
            REDRAW_OBJECTS
END_OF_PROGRAM

