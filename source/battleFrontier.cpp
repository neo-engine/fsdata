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

map<pair<u16, u8>, pkmnEvolveData> pkmn_evolve;

map<u16, names>  class_names;
map<string, int> classes;

map<string, int> abilities;
vector<names>    ability_names;

map<string, int> items;
vector<names>    item_names;

map<string, int> moves;
map<string, int> alt_moves; // alternative move names
vector<names>    move_names;

map<string, int>      pkmns;
vector<names>         pkmn_names;
vector<vector<names>> forme_names;

struct bfPokemon {
    u16 m_speciesId;
    u16 m_heldItem;
    u8  m_forme;
    u8  m_nature;
    u16 m_moves[ 4 ];
    u8  m_ev; // evs are either 0 or 252
};

u8 parseNature( char* p_str ) {
    if( !strcmp( p_str, "Hardy" ) ) { return 0; }
    if( !strcmp( p_str, "Lonely" ) ) { return 1; }
    if( !strcmp( p_str, "Brave" ) ) { return 2; }
    if( !strcmp( p_str, "Adamant" ) ) { return 3; }
    if( !strcmp( p_str, "Naughty" ) ) { return 4; }
    if( !strcmp( p_str, "Bold" ) ) { return 5; }
    if( !strcmp( p_str, "Docile" ) ) { return 6; }
    if( !strcmp( p_str, "Relaxed" ) ) { return 7; }
    if( !strcmp( p_str, "Impish" ) ) { return 8; }
    if( !strcmp( p_str, "Lax" ) ) { return 9; }
    if( !strcmp( p_str, "Timid" ) ) { return 10; }
    if( !strcmp( p_str, "Hasty" ) ) { return 11; }
    if( !strcmp( p_str, "Serious" ) ) { return 12; }
    if( !strcmp( p_str, "Jolly" ) ) { return 13; }
    if( !strcmp( p_str, "Naive" ) ) { return 14; }
    if( !strcmp( p_str, "Modest" ) ) { return 15; }
    if( !strcmp( p_str, "Mild" ) ) { return 16; }
    if( !strcmp( p_str, "Quiet" ) ) { return 17; }
    if( !strcmp( p_str, "Bashful" ) ) { return 18; }
    if( !strcmp( p_str, "Rash" ) ) { return 19; }
    if( !strcmp( p_str, "Calm" ) ) { return 20; }
    if( !strcmp( p_str, "Gentle" ) ) { return 21; }
    if( !strcmp( p_str, "Sassy" ) ) { return 22; }
    if( !strcmp( p_str, "Careful" ) ) { return 23; }
    if( !strcmp( p_str, "Quirky" ) ) { return 24; }

    fprintf( stderr, "unknown nature %s\n", p_str );
    return 0;
}

bfPokemon parseFrontierPokemon( char* p_buffer ) {
    bfPokemon res;
    char      speciesbuf[ 50 ] = { 0 }, itembuf[ 50 ] = { 0 };
    char mvbuf1[ 50 ] = { 0 }, mvbuf2[ 50 ] = { 0 }, mvbuf3[ 50 ] = { 0 }, mvbuf4[ 50 ] = { 0 },
                    naturebuf[ 50 ] = { 0 };
    u8 ev[ 6 ]                      = { 0 };

    sscanf( p_buffer,
            "%*[^;];%[^;];%hhu;%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%hhu;%hhu;%hhu;"
            "%hhu;%hhu;%hhu;",
            speciesbuf, &res.m_forme, itembuf, mvbuf1, mvbuf2, mvbuf3, mvbuf4, naturebuf, &ev[ 0 ],
            &ev[ 1 ], &ev[ 2 ], &ev[ 3 ], &ev[ 4 ], &ev[ 5 ] );

    res.m_speciesId = pkmns[ string( fixEncoding( speciesbuf ) ) ];
    if( !res.m_speciesId ) {
        fprintf( stderr, "[%s] Unknown pokemon \"%s\"\n", FILENAME.c_str( ), speciesbuf );
    }
    res.m_heldItem = items[ string( fixEncoding( itembuf ) ) ];
    if( !res.m_heldItem && strcmp( fixEncoding( itembuf ), "none" ) ) {
        fprintf( stderr, "[%s|%s] Unknown held item \"%s\"\n", FILENAME.c_str( ), speciesbuf,
                 itembuf );
    }
    res.m_moves[ 0 ] = moves[ string( fixEncoding( mvbuf1 ) ) ];
    if( !res.m_moves[ 0 ] && strcmp( fixEncoding( mvbuf1 ), "none" ) ) {
        fprintf( stderr, "[%s|%s] Unknown move \"%s\"\n", FILENAME.c_str( ), speciesbuf, mvbuf1 );
    }
    res.m_moves[ 1 ] = moves[ string( fixEncoding( mvbuf2 ) ) ];
    if( !res.m_moves[ 1 ] && strcmp( fixEncoding( mvbuf2 ), "none" ) ) {
        fprintf( stderr, "[%s|%s] Unknown move \"%s\"\n", FILENAME.c_str( ), speciesbuf, mvbuf2 );
    }
    res.m_moves[ 2 ] = moves[ string( fixEncoding( mvbuf3 ) ) ];
    if( !res.m_moves[ 2 ] && strcmp( fixEncoding( mvbuf3 ), "none" ) ) {
        fprintf( stderr, "[%s|%s] Unknown move \"%s\"\n", FILENAME.c_str( ), speciesbuf, mvbuf3 );
    }
    res.m_moves[ 3 ] = moves[ string( fixEncoding( mvbuf4 ) ) ];
    if( !res.m_moves[ 3 ] && strcmp( fixEncoding( mvbuf4 ), "none" ) ) {
        fprintf( stderr, "[%s|%s] Unknown move \"%s\"\n", FILENAME.c_str( ), speciesbuf, mvbuf4 );
    }

    res.m_nature = parseNature( naturebuf );
    res.m_ev     = 0;
    for( auto i = 0; i < 6; ++i ) {
        if( ev[ i ] ) { res.m_ev |= ( 1 << i ); }
    }

    return res;
}

int main( int p_argc, char** p_argv ) {
    if( p_argc < 6 ) {
        fprintf( stderr, "too few args." );
        return 1;
    }
    readNames( p_argv[ 1 ], pkmn_names );
    for( size_t i = 0; i < pkmn_names.size( ); ++i ) pkmns[ pkmn_names[ i ].m_name[ 0 ] ] = i;

    readNames( p_argv[ 2 ], move_names );
    for( size_t i = 0; i < move_names.size( ); ++i ) moves[ move_names[ i ].m_name[ 0 ] ] = i;

    readNames( p_argv[ 3 ], item_names, 29, 1 );
    for( size_t i = 0; i < item_names.size( ); ++i ) { items[ item_names[ i ].m_name[ 0 ] ] = i; }

    readNames( p_argv[ 4 ], class_names );
    for( auto i : class_names ) classes[ i.second.m_name[ 0 ] ] = i.first;

    FILE* f = fopen( p_argv[ 5 ], "r" );
    if( !f ) {
        fprintf( stderr, "input file unreadable" );
        return 1;
    }

    fs::create_directories( std::string( FSROOT "/BFTR_PKMN/" ) );

    auto outf = fopen( FSROOT "/BFTR_PKMN/bfpoke.datab", "wb" );
    assert( outf );

    char buffer[ 200 ];
    while( f && fgets( buffer, sizeof( buffer ), f ) ) {
        auto pkmn = parseFrontierPokemon( buffer );
        fwrite( &pkmn, 1, sizeof( bfPokemon ), outf );
    }
    fclose( f );
    fclose( outf );
}
