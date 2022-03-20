// Arguments
// pkmnnames.csv abtynames.csv movenames.csv itemnames.csv pkmndata.csv pkmndescr.csv
// pkmnformnames.csv pkmnformes.csv itemdata_medicine.csv

#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <filesystem>
#include <map>
#include <string>
#include <vector>
#include "fsdata.h"

struct locationData {
    u16 m_bgmNameIdx = 0;
    u8  m_frameType  = 0;
    u8  m_mugType    = 0;
};

map<u16, names>             location_names;
map<u16, locationData>      location_data;
vector<pair<string, names>> bgm_names;
map<string, u16>            bgm_names_map;

void printLocationData( ) {
    fs::create_directories( std::string( OUT ) );
    FILE* g = fopen( OUT "/locationNames.h", "w" );
    fprintf( g, "#pragma once\n" );

    auto outf = vector<FILE*>( );
    fs::create_directories( std::string( FSROOT ) );
    fs::create_directories( std::string( FSROOT "/LOC_NAME/" ) );
    auto dataf = fopen( FSROOT "/location.datab", "wb" );
    assert( dataf );
    for( int j = 0; j < NUM_LANGUAGES; ++j ) {
        FILE* fo = fopen(
            ( std::string( FSROOT "/LOC_NAME/locname." ) + std::to_string( j ) + ".strb" ).c_str( ),
            "wb" );
        assert( fo );
        outf.push_back( fo );
    }

    map<string, int> duplicates = map<string, int>( );
    u16              mx         = 0;
    for( auto i = location_names.begin( ); i != location_names.end( ); ++i ) {
        mx = max( mx, i->first );
        if( i->first && strcmp( i->second.m_name[ 0 ], "???" ) ) {
            fprintf( g, "#define L_" );
            char* s = i->second.m_name[ 0 ];
            printNormalized( s, g );
            if( duplicates.count( i->second.m_name[ 0 ] ) ) {
                fprintf( g, "%d %hu\n", duplicates[ i->second.m_name[ 0 ] ] + 1, i->first );
            } else {
                fprintf( g, " %hu\n", i->first );
            }
            duplicates[ i->second.m_name[ 0 ] ]++;
        }
    }

    for( u16 i = 0; i <= mx; ++i ) {
        names n;
        for( int i = 0; i < NUM_LANGUAGES; ++i ) {
            n.m_name[ i ] = new char[ 40 ];
            std::memset( n.m_name[ i ], 0, 40 );
        }

        locationData l = locationData( );

        if( location_names.count( i ) ) { n = location_names[ i ]; }
        if( location_data.count( i ) ) { l = location_data[ i ]; }

        assert( fwrite( &l, sizeof( locationData ), 1, dataf ) );
        for( int j = 0; j < NUM_LANGUAGES; ++j ) {
            assert( fwrite( n.m_name[ j ], 1, 25, outf[ j ] ) );
        }
    }

    fclose( g );
    fclose( dataf );
    for( int j = 0; j < NUM_LANGUAGES; ++j ) { fclose( outf[ j ] ); }
}

void printBGMData( ) {
    fs::create_directories( std::string( OUT ) );
    fs::create_directories( std::string( FSROOT "/BGM_NAME/" ) );
    FILE* n    = fopen( OUT "/bgmNames.h", "w" );
    FILE* g    = fopen( OUT "/bgmTranslation.h", "w" );
    auto  outf = vector<FILE*>( );
    for( int j = 0; j < NUM_LANGUAGES; ++j ) {
        FILE* fo
            = fopen( ( std::string( FSROOT "/BGM_NAME/bgmnames." ) + std::to_string( j ) + ".strb" )
                         .c_str( ),
                     "wb" );
        assert( fo );
        outf.push_back( fo );
    }

    fprintf( g, "#pragma once\n"
                "#ifndef NO_SOUND\n"
                "#include \"bgmNames.h\"\n"
                "#ifdef MMOD\n"
                "#include \"soundbank.h\"\n"
                "#endif\n\n"
                "#define MOD_NONE -1\n\n"
                "#ifdef MMOD\n"
                "constexpr int BGMIndexForName( unsigned p_name ) {\n"
                "    switch( p_name ) {\n"
                "    default: return -1;\n" );
    fprintf( n, "#pragma once\n\n" );

    int count = 0;
    for( const auto& [ id, names ] : bgm_names ) {
        for( int j = 0; j < NUM_LANGUAGES; ++j ) {
            assert( fwrite( names.m_name[ j ], 1, 25, outf[ j ] ) );
        }

        string nname = "BGM_" + id.substr( 4 );

        if( id[ 0 ] == 'M' ) { // ow bgm exists only as sseq
            fprintf( n, ( "#define "s + nname + " " + std::to_string( count++ ) + "\n" ).c_str( ) );
            fprintf( g, ( "    case "s + nname + ": return " + id + ";\n" ).c_str( ) );
        }
    }
    fprintf( g, "    }\n"
                "}\n"
                "#endif\n"
                "#endif\n" );

    fprintf( n, ( "\n#define MAX_BGM "s + std::to_string( count - 1 ) + "\n" ).c_str( ) );

    fclose( g );
    fclose( n );
    for( int j = 0; j < NUM_LANGUAGES; ++j ) { fclose( outf[ j ] ); }
}

void readLocationData( char* p_path, map<u16, locationData>& p_out ) {
    FILE* f             = fopen( p_path, "r" );
    char  buffer[ 500 ] = { 0 };
    while( fgets( buffer, sizeof( buffer ), f ) ) {
        u16          id;
        locationData n = locationData( );

        char b1[ 50 ] = { 0 }, b2[ 50 ] = { 0 };
        sscanf( buffer, "%hu;%*[^;];%[^;];%[^;];%hhu;", &id, b1, b2, &n.m_mugType );
        n.m_bgmNameIdx = bgm_names_map[ string( b1 ) ];
        if( !n.m_bgmNameIdx ) { printf( "%s Unknown BGM \"%s\"\n", buffer, b1 ); }
        n.m_frameType = getFrameType( b2 );

        p_out[ id ] = n;
    }
    // fprintf( stderr, "read %lu objects from %s\n", p_out.size( ), p_path );
    fclose( f );
}

int main( int p_argc, char** p_argv ) {
    if( p_argc < 4 ) {
        fprintf( stderr, "too few args." );
        return 1;
    }

    readNames( p_argv[ 1 ], bgm_names );
    for( u16 i = 0; i < bgm_names.size( ); ++i ) {
        string nname           = "BGM_" + bgm_names[ i ].first.substr( 4 );
        bgm_names_map[ nname ] = i;
    }

    readNames( p_argv[ 2 ], location_names );
    readLocationData( p_argv[ 3 ], location_data );
    printLocationData( );
    printBGMData( );
}
