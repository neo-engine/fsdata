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

u8 parseGender( char* p_buffer ) {
    if( !strcmp( p_buffer, "Female" ) ) { return 0; }
    if( !strcmp( p_buffer, "Genderless" ) ) { return 1; }
    if( !strcmp( p_buffer, "Male" ) ) { return 2; }
    if( !strcmp( p_buffer, "female" ) ) { return 0; }
    if( !strcmp( p_buffer, "genderless" ) ) { return 1; }
    if( !strcmp( p_buffer, "male" ) ) { return 2; }

    fprintf( stderr, "[%s] Unknown gender \"%s\"\n", FILENAME.c_str( ), p_buffer );
    return 0;
}

trainerPokemon parseTrainerPokemon( char* p_buffer ) {
    trainerPokemon res;
    char           speciesbuf[ 50 ] = { 0 }, genderbuf[ 20 ] = { 0 }, abilitybuf[ 50 ] = { 0 },
                        itembuf[ 50 ] = { 0 };
    char mvbuf1[ 50 ] = { 0 }, mvbuf2[ 50 ] = { 0 }, mvbuf3[ 50 ] = { 0 }, mvbuf4[ 50 ] = { 0 };

    sscanf( p_buffer,
            "%[^,],%[^,],%hhu,%hhu,%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%hhu,%hhu,%hhu,"
            "%hhu,%hhu,%hhu,"
            "%hhu,%hhu,%hhu,%hhu,%hhu,%hhu,%hhu,%hhu",
            speciesbuf, genderbuf, &res.m_forme, &res.m_level, abilitybuf, itembuf, mvbuf1, mvbuf2,
            mvbuf3, mvbuf4, &res.m_ev[ 0 ], &res.m_ev[ 1 ], &res.m_ev[ 2 ], &res.m_ev[ 3 ],
            &res.m_ev[ 4 ], &res.m_ev[ 5 ], &res.m_iv[ 0 ], &res.m_iv[ 1 ], &res.m_iv[ 2 ],
            &res.m_iv[ 3 ], &res.m_iv[ 4 ], &res.m_iv[ 5 ], &res.m_shiny, &res.m_nature );

    res.m_speciesId = pkmns[ string( fixEncoding( speciesbuf ) ) ];
    if( !res.m_speciesId ) {
        fprintf( stderr, "[%s] Unknown pokemon \"%s\"\n", FILENAME.c_str( ), speciesbuf );
    }
    res.m_ability = abilities[ string( fixEncoding( abilitybuf ) ) ];
    if( !res.m_ability ) {
        fprintf( stderr, "[%s|%s] Unknown item \"%s\"\n", FILENAME.c_str( ), speciesbuf,
                 abilitybuf );
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

    switch( parseGender( fixEncoding( genderbuf ) ) ) {
    case 1:
        res.m_forme |= ( 1 << 7 );
        break;
    case 0:
        res.m_forme |= ( 1 << 6 );
        break;
    default:
        break;
    }

    return res;
}

std::vector<trainerData> parseBattleTrainer( const char* p_path ) {
    FILE* f             = fopen( p_path, "r" );
    char  buffer[ 500 ] = { 0 };

    trainerData rdata_easy   = trainerData( );
    trainerData rdata_normal = trainerData( );
    trainerData rdata_hard   = trainerData( );
    // trainer data

    u8  numpok, ailevel, plat1, plat2;
    u16 battlebg, money, trainerbg;

    fgets( buffer, sizeof( buffer ), f );
    char tclassbuffer[ 50 ] = { 0 }, itm1[ 50 ] = { 0 }, itm2[ 50 ] = { 0 }, itm3[ 50 ] = { 0 },
                          itm4[ 50 ] = { 0 }, itm5[ 50 ] = { 0 };
    sscanf( buffer, "%[^,],%hhu,%hhu,%[^,],%[^,],%[^,],%[^,],%[^,],%hu,%hu,%hhu,%hhu,%hu",
            tclassbuffer, &ailevel, &numpok, itm1, itm2, itm3, itm4, itm5, &money, &battlebg,
            &plat1, &plat2, &trainerbg );

    rdata_normal.m_numPokemon      = numpok;
    rdata_normal.m_AILevel         = ailevel;
    rdata_normal.m_battlePlat1     = plat1;
    rdata_normal.m_battlePlat2     = plat2;
    rdata_normal.m_trainerBG       = trainerbg;
    rdata_normal.m_battleBG        = battlebg;
    rdata_normal.m_moneyMultiplier = money;

    rdata_hard.m_numPokemon      = numpok;
    rdata_hard.m_AILevel         = std::min( 8, ailevel + 1 );
    rdata_hard.m_battlePlat1     = plat1;
    rdata_hard.m_battlePlat2     = plat2;
    rdata_hard.m_trainerBG       = trainerbg;
    rdata_hard.m_battleBG        = battlebg;
    rdata_hard.m_moneyMultiplier = money;

    rdata_easy.m_numPokemon      = numpok;
    rdata_easy.m_AILevel         = std::max( 1, ailevel - 1 );
    rdata_easy.m_battlePlat1     = plat1;
    rdata_easy.m_battlePlat2     = plat2;
    rdata_easy.m_trainerBG       = trainerbg;
    rdata_easy.m_battleBG        = battlebg;
    rdata_easy.m_moneyMultiplier = money;

    auto cn = string( fixEncoding( tclassbuffer ) );
    if( !classes.count( cn ) ) {
        fprintf( stderr, "[%s] Unknown trainer class \"%s\"\n", FILENAME.c_str( ), tclassbuffer );
    } else {
        rdata_easy.m_trainerClass   = classes[ cn ];
        rdata_normal.m_trainerClass = classes[ cn ];
        rdata_hard.m_trainerClass   = classes[ cn ];
    }
    rdata_normal.m_items[ 0 ] = items[ string( fixEncoding( itm1 ) ) ];
    rdata_hard.m_items[ 0 ]   = items[ string( fixEncoding( itm1 ) ) ];
    if( !rdata_hard.m_items[ 0 ] && strcmp( fixEncoding( itm1 ), "none" ) ) {
        fprintf( stderr, "[%s] Unknown item \"%s\"\n", FILENAME.c_str( ), itm1 );
    }
    rdata_normal.m_items[ 1 ] = items[ string( fixEncoding( itm2 ) ) ];
    rdata_hard.m_items[ 1 ]   = items[ string( fixEncoding( itm2 ) ) ];
    if( !rdata_hard.m_items[ 1 ] && strcmp( fixEncoding( itm2 ), "none" ) ) {
        fprintf( stderr, "[%s] Unknown item \"%s\"\n", FILENAME.c_str( ), itm2 );
    }
    rdata_normal.m_items[ 2 ] = items[ string( fixEncoding( itm3 ) ) ];
    rdata_hard.m_items[ 2 ]   = items[ string( fixEncoding( itm3 ) ) ];
    if( !rdata_hard.m_items[ 2 ] && strcmp( fixEncoding( itm3 ), "none" ) ) {
        fprintf( stderr, "[%s] Unknown item \"%s\"\n", FILENAME.c_str( ), itm3 );
    }
    rdata_hard.m_items[ 3 ] = items[ string( fixEncoding( itm4 ) ) ];
    if( !rdata_hard.m_items[ 3 ] && strcmp( fixEncoding( itm4 ), "none" ) ) {
        fprintf( stderr, "[%s] Unknown item \"%s\"\n", FILENAME.c_str( ), itm4 );
    }
    rdata_hard.m_items[ 4 ] = items[ string( fixEncoding( itm5 ) ) ];
    if( !rdata_hard.m_items[ 4 ] && strcmp( fixEncoding( itm5 ), "none" ) ) {
        fprintf( stderr, "[%s] Unknown item \"%s\"\n", FILENAME.c_str( ), itm5 );
    }

    for( u8 i = 0; i < numpok; ++i ) {
        fgets( buffer, sizeof( buffer ), f );
        if( i < 2 || i < numpok - 1 ) { rdata_easy.m_pokemon[ i ] = parseTrainerPokemon( buffer ); }
        rdata_normal.m_pokemon[ i ] = parseTrainerPokemon( buffer );
        rdata_hard.m_pokemon[ i ]   = parseTrainerPokemon( buffer );
    }

    // hard difficulty may use this hidden extra pokemon
    if( numpok < 6 && fgets( buffer, sizeof( buffer ), f ) ) {
        rdata_hard.m_pokemon[ rdata_hard.m_numPokemon ] = parseTrainerPokemon( buffer );
        ++rdata_hard.m_numPokemon;
    }

    if( numpok >= 2 ) { --rdata_easy.m_numPokemon; }

    fclose( f );
    return { rdata_easy, rdata_normal, rdata_hard };
}

void printTrainerData( const trainerData& p_trainerData, u16 p_id,
                       u8 p_difficulty = 1 /* normal */ ) {
    char prefix[ 60 ];
    snprintf( prefix, 55, "%s/TRNR_DATA/%hhu/", FSROOT, p_difficulty );
    FILE* f = getFilePtr( prefix, p_id, 2, ".trnr.data" );
    assert( f );
    fwrite( &p_trainerData, sizeof( trainerData ), 1, f );
    fclose( f );
}

int main( int p_argc, char** p_argv ) {
    if( p_argc < 7 ) {
        fprintf( stderr, "too few args." );
        return 1;
    }
    FILENAME = string( p_argv[ 6 ] );

    readNames( p_argv[ 1 ], pkmn_names );
    for( size_t i = 0; i < pkmn_names.size( ); ++i ) pkmns[ pkmn_names[ i ].m_name[ 0 ] ] = i;
    readNames( p_argv[ 2 ], ability_names );
    for( size_t i = 0; i < ability_names.size( ); ++i )
        abilities[ ability_names[ i ].m_name[ 0 ] ] = i;
    readNames( p_argv[ 3 ], move_names );
    for( size_t i = 0; i < move_names.size( ); ++i ) moves[ move_names[ i ].m_name[ 0 ] ] = i;

    readNames( p_argv[ 4 ], item_names, 29, 1 );
    for( size_t i = 0; i < item_names.size( ); ++i ) { items[ item_names[ i ].m_name[ 0 ] ] = i; }

    readNames( p_argv[ 5 ], class_names );
    for( auto i : class_names ) classes[ i.second.m_name[ 0 ] ] = i.first;

    FILE* g = fopen( OUT "/trainerClassNames.h", "w" );
    fprintf( g, "#pragma once\n" );
    for( size_t i = 0; i < class_names.size( ); ++i ) {
        fprintf( g, "#define TC_" );
        char* s = class_names[ i ].m_name[ 0 ];
        printNormalized( s, g );
        fprintf( g, " %lu\n", i );
    }
    fclose( g );

    auto tdata = parseBattleTrainer( p_argv[ 6 ] );
    u16  idx   = 0;
    sscanf( p_argv[ 6 ], "%*[^0-9]%hu", &idx );
    //    printf( "[%s] Saving to %hu\n", p_argv[ 6 ], idx );

    for( auto i = 0; i < tdata.size( ); ++i ) { printTrainerData( tdata[ i ], idx, i ); }
}
