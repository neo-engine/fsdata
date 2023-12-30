#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <filesystem>
#include <map>
#include <string>
#include <vector>

#include "fsdata.h"

std::string PATH;
std::string NAME;
std::string HFILEN;
std::string DEFPRE;
u16         STRING_LEN = 100;

int main( int p_argc, char** p_argv ) {
    if( p_argc < 7 ) {
        fprintf( stderr, "too few args. (file, outpath, out file name, max string len)" );
        return 1;
    }
    PATH   = string( p_argv[ 2 ] );
    NAME   = string( p_argv[ 3 ] );
    HFILEN = string( p_argv[ 4 ] );
    DEFPRE = string( p_argv[ 5 ] );
    sscanf( p_argv[ 6 ], "%hu", &STRING_LEN );
    FILE* f = fopen( p_argv[ 1 ], "r" );
    if( !f ) {
        fprintf( stderr, "input file unreadable\n" );
        return 1;
    }

    char buffer[ NUM_LANGUAGES * STRING_LEN + 10 ];
    memset( buffer, 0, sizeof( buffer ) );
    char writebuffer[ STRING_LEN + 10 ];
    memset( writebuffer, 0, sizeof( writebuffer ) );
    //  printf( "/%s/ %lu %hu\n", buffer, sizeof(buffer), STRING_LEN );

    std::vector<FILE*> outfiles;

    for( int i = 0; i < NUM_LANGUAGES; ++i ) {
        fs::create_directories( std::string( FSROOT ) + PATH );
        FILE* fo = fopen(
            ( std::string( FSROOT ) + PATH + NAME + "." + std::to_string( i ) + ".strb" ).c_str( ),
            "wb" );
        assert( fo );
        outfiles.push_back( fo );
    }

    std::string hepa = ( std::string( OUT ) + "/" + HFILEN );

    FILE* header = fopen( hepa.c_str( ), "w" );

    if( !header ) {
        fprintf( stderr, "output file %s unreadable\n", hepa.c_str( ) );
        return 1;
    }
    fprintf( header, "#pragma once\n" );

    auto count = 0;
    while( f && fgets( buffer, sizeof( buffer ), f ) ) {
        char* tok = strtok( buffer, ";" );
        for( int i = 0; i < NUM_LANGUAGES; ++i ) {
            bool catname = false;
            if( tok && *tok == '@' ) {
                ++tok;
                catname = true;
            }

            std::memset( writebuffer, 0, sizeof( writebuffer ) );
            if( strcmp( "^", tok ) ) { std::strncpy( writebuffer, tok, STRING_LEN ); }

            fwrite( fixEncoding( writebuffer ), sizeof( u8 ), STRING_LEN, outfiles[ i ] );
            if( catname ) {
                fprintf( header, "#define " );
                fprintf( header, "%s", DEFPRE.c_str( ) );
                printNormalized( writebuffer, header );
                fprintf( header, " %i\n", count );
            }
            tok = strtok( NULL, ";" );
        }
        count++;
        std::memset( writebuffer, 0, sizeof( writebuffer ) );
    }
    for( int i = 0; i < NUM_LANGUAGES; ++i ) { fclose( outfiles[ i ] ); }
    fclose( f );
    fclose( header );
}
