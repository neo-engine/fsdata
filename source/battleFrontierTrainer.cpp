#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <filesystem>
#include <map>
#include <string>
#include <vector>

#include "fsdata.h"

string FILENAME;

map<u16, names>  class_names;
map<string, int> classes;

struct easyChatMessage {
    u32 m_sentenceId : 8;
    u32 m_word1Id : 12;
    u32 m_word2Id : 12;
};

struct bfTrainer {
    easyChatMessage m_beforeBattle;
    easyChatMessage m_onWinAgainstPlayer;
    easyChatMessage m_onLoseAgainstPlayer;
    u16             m_trainerClass : 7;
    u16             m_trainerNameIdx : 9;
    u16             m_trainerBG : 8; // in-battle pic
    u16             m_picnum : 8;    // ow sprite num
};

struct bfTrainerClass {
    u16 m_beforeBattle;
    u16 m_onWinAgainstPlayer;
    u16 m_onLoseAgainstPlayer;
    u16 m_trainerBG; // in-battle pic
    u16 m_picnum;    // ow sprite num
};

const u16 MAX_WORD = 338;

const map<string, string> TCLASS_TRANSLATION = {
    { "Aroma Lady", "Aroma Lady" },
    { "Battle Girl", "Battle Girl" },
    { "Beauty", "Beauty" },
    { "Bird Keeper", "Bird Keeper" },
    { "Black Belt", "Black Belt" },
    { "Bug Catcher", "Bug Catcher" },
    { "Bug Maniac", "Bug Maniac" },
    { "Camper", "Camper" },
    { "Collector", "Collector" },
    { "Ace Trainer m", "Ace Trainer" },
    { "Ace Trainer f", " Ace Trainer" },
    { "Dragon Tamer", "Dragon Tamer" },
    { "Expert m", "Expert" },
    { "Expert f", " Expert" },
    { "Fisherman", "Fisherman" },
    { "Gentleman", "Gentleman" },
    { "Guitarist", "Guitarist" },
    { "Hex Maniac", "Hex Maniac" },
    { "Hiker", "Hiker" },
    { "Kindler", "Kindler" },
    { "Lady", "Lady" },
    { "Lass", "Lass" },
    { "Ninja Boy", "Ninja Boy" },
    { "Parasol Lady", "Parasol Lady" },
    { "Picnicker", "Picnicker" },
    { "Poke Fan m", "Pok_an" },
    { "Poke Fan f", "Pok_an" },
    { "Poke Maniac", "Pok_aniac" },
    { "PKMN Breeder m", "Pok_n Breeder" },
    { "PKMN Breeder f", " Pok_n Breeder" },
    { "PKMN Ranger m", "Pok_n Ranger" },
    { "PKMN Ranger f", "Pok_n Ranger" },
    { "Psychic m", "Psychic" },
    { "Psychic f", "Psychic" },
    { "Rich Boy", "Rich Boy" },
    { "Ruin Maniac", "Ruin Maniac" },
    { "Sailor", "Sailor" },
    { "Schoolboy", "Schoolboy" },
    { "Schoolgirl", "Schoolgirl" },
    { "Swimmer m", "Swimmer" },
    { "Swimmer f", " Swimmer" },
    { "Triathlete m", "Triathlete" },
    { "Triathlete f", "Triathlete" },
    { "Tuber m", "Tuber" },
    { "Tuber f", " Tuber" },
    { "Youngster", "Youngster" },
};

const map<string, bfTrainerClass> BF_PKMN_IDX_FOR_TCLASS = {
    { "Aroma Lady", { 43, 65, 85, 76, 39 } },     { "Battle Girl", { 44, 66, 86, 58, 95 } },
    { "Beauty", { 48, 64, 87, 37, 79 } },         { "Bird Keeper", { 50, 67, 88, 67, 107 } },
    { "Black Belt", { 59, 66, 89, 47, 47 } },     { "Bug Catcher", { 61, 68, 90, 43, 70 } },
    { "Bug Maniac", { 54, 69, 91, 70, 72 } },     { "Camper", { 56, 70, 92, 82, 74 } },
    { "Collector", { 57, 71, 93, 72, 72 } },      { "Ace Trainer m", { 58, 67, 94, 78, 78 } },
    { "Ace Trainer f", { 58, 67, 94, 79, 50 } },  { "Dragon Tamer", { 49, 67, 95, 66, 78 } },
    { "Expert m", { 60, 72, 96, 62, 62 } },       { "Expert f", { 60, 72, 96, 63, 63 } },
    { "Fisherman", { 51, 73, 97, 38, 38 } },      { "Gentleman", { 62, 74, 98, 55, 55 } },
    { "Guitarist", { 53, 75, 99, 54, 107 } },     { "Hex Maniac", { 9, 76, 100, 49, 105 } },
    { "Hiker", { 13, 77, 101, 36, 36 } },         { "Kindler", { 24, 78, 102, 81, 107 } },
    { "Lady", { 15, 79, 103, 39, 76 } },          { "Lass", { 34, 80, 104, 34, 34 } },
    { "Ninja Boy", { 39, 68, 104, 68, 92 } },     { "Parasol Lady", { 19, 79, 85, 69, 50 } },
    { "Picnicker", { 45, 81, 86, 83, 75 } },      { "Poke Fan m", { 47, 82, 87, 87, 73 } },
    { "Poke Fan f", { 60, 83, 88, 61, 229 } },    { "Poke Maniac", { 61, 64, 89, 80, 72 } },
    { "PKMN Breeder m", { 46, 65, 90, 73, 96 } }, { "PKMN Breeder f", { 47, 66, 91, 50, 76 } },
    { "PKMN Ranger m", { 50, 67, 92, 74, 74 } },  { "PKMN Ranger f", { 50, 68, 93, 75, 75 } },
    { "Psychic m", { 18, 69, 94, 84, 85 } },      { "Psychic f", { 50, 75, 102, 85, 34 } },
    { "Rich Boy", { 5, 70, 95, 45, 93 } },        { "Ruin Maniac", { 9, 71, 96, 77, 36 } },
    { "Sailor", { 3, 72, 97, 71, 71 } },          { "Schoolboy", { 11, 73, 98, 44, 44 } },
    { "Schoolgirl", { 17, 74, 99, 86, 95 } },     { "Swimmer m", { 23, 75, 100, 60, 44 } },
    { "Swimmer f", { 24, 76, 101, 42, 95 } },     { "Triathlete m", { 32, 77, 102, 40, 206 } },
    { "Triathlete f", { 33, 78, 103, 59, 205 } }, { "Tuber m", { 36, 79, 103, 52, 52 } },
    { "Tuber f", { 46, 80, 103, 48, 90 } },       { "Youngster", { 49, 81, 104, 35, 35 } },
};

bfTrainer parseBFTrainer( char* p_buffer ) {
    bfTrainer res{ };
    u16       id;
    char      classbuff[ 50 ] = { 0 };

    sscanf( p_buffer, "%hu;%[^;];", &id, classbuff );
    res.m_trainerNameIdx = id;

    if( !TCLASS_TRANSLATION.count( string( classbuff ) ) ) {
        fprintf( stderr, "[%s] Unknown trainer class \"%s\"\n", FILENAME.c_str( ), classbuff );
        res.m_trainerClass = 0;
    } else if( !classes.count( TCLASS_TRANSLATION.at( string( classbuff ) ) ) ) {
        fprintf( stderr, "[%s] Unknown trainer class (3) \"%s\"\n", FILENAME.c_str( ),
                 TCLASS_TRANSLATION.at( string( classbuff ) ).c_str( ) );
        res.m_trainerClass = 0;
    } else {
        res.m_trainerClass = classes[ TCLASS_TRANSLATION.at( string( classbuff ) ) ];
    }

    if( !BF_PKMN_IDX_FOR_TCLASS.count( string( classbuff ) ) ) {
        fprintf( stderr, "[%s] Unknown trainer class (2) \"%s\"\n", FILENAME.c_str( ), classbuff );
        return res;
    }

    auto data = BF_PKMN_IDX_FOR_TCLASS.at( string( classbuff ) );

    res.m_beforeBattle
        = easyChatMessage{ data.m_beforeBattle, static_cast<u32>( 1 + rand( ) % MAX_WORD ),
                           static_cast<u32>( 1 + rand( ) % MAX_WORD ) };
    res.m_onWinAgainstPlayer
        = easyChatMessage{ data.m_onWinAgainstPlayer, static_cast<u32>( 1 + rand( ) % MAX_WORD ),
                           static_cast<u32>( 1 + rand( ) % MAX_WORD ) };
    res.m_onLoseAgainstPlayer
        = easyChatMessage{ data.m_onLoseAgainstPlayer, static_cast<u32>( 1 + rand( ) % MAX_WORD ),
                           static_cast<u32>( 1 + rand( ) % MAX_WORD ) };
    res.m_trainerBG = data.m_trainerBG; // in-battle pic
    res.m_picnum    = data.m_picnum;    // ow sprite num

    return res;
}

int main( int p_argc, char** p_argv ) {
    if( p_argc < 3 ) {
        fprintf( stderr, "too few args." );
        return 1;
    }

    FILENAME = std::string( p_argv[ 0 ] );

    auto RANDOM_SEED = 42;
    srand( RANDOM_SEED );

    readNames( p_argv[ 1 ], class_names );
    for( auto i : class_names ) { classes[ fixEncoding( i.second.m_name[ 0 ] ) ] = i.first; }

    FILE* f = fopen( p_argv[ 2 ], "r" );
    if( !f ) {
        fprintf( stderr, "input file unreadable" );
        return 1;
    }

    fs::create_directories( std::string( FSROOT "/BFTR PKMN/" ) );

    auto outf = fopen(
        ( std::string( FSROOT "/BFTR_PKMN/" ) + std::string( p_argv[ 3 ] ) ).c_str( ), "wb" );
    assert( outf );

    char buffer[ 200 ];
    memset( buffer, 0, sizeof( buffer ) );
    while( f && fgets( buffer, sizeof( buffer ), f ) ) {
        auto pkmn = parseBFTrainer( buffer );
        fwrite( &pkmn, 1, sizeof( bfTrainer ), outf );
    }
    fclose( f );
    fclose( outf );
}
