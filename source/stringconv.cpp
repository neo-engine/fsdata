#include <cassert>
#include <cstdio>
#include <cstring>
#include <vector>
#include "fsdata.h"

std::string PATH;
std::string NAME;
u16         STRING_LEN = 100;

int main( int p_argc, char** p_argv ) {
    if( p_argc < 5 ) {
        fprintf( stderr, "too few args. (file, outpath, out file name, max string len)" );
        return 1;
    }
    PATH = string( p_argv[ 2 ] );
    NAME = string( p_argv[ 3 ] );
    sscanf( p_argv[ 4 ], "%hu", &STRING_LEN );
    FILE* f = fopen( p_argv[ 1 ], "r" );
    if( !f ) {
        fprintf( stderr, "input file unreadable" );
        return 1;
    }

    char buffer[ NUM_LANGUAGES * STRING_LEN + 10 ] = { 0 };
    char writebuffer[ STRING_LEN + 10 ]            = { 0 };
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

    // u16 id = 0;
    while( f && fgets( buffer, sizeof( buffer ), f ) ) {
        //    printf( "/%s/ %lu %hu\n", buffer, sizeof(buffer), STRING_LEN );
        char* tok = strtok( buffer, ";" );
        //        FILE* fo  = getFilePtr( std::string( FSROOT ) + PATH, id, 2, ".str" );
        //        assert( fo );
        for( int i = 0; i < NUM_LANGUAGES; ++i ) {
            std::memset( writebuffer, 0, sizeof( writebuffer ) );
            if( strcmp( "^", tok ) ) { std::strncpy( writebuffer, tok, STRING_LEN ); }

            fwrite( fixEncoding( writebuffer ), sizeof( u8 ), STRING_LEN, outfiles[ i ] );
            tok = strtok( NULL, ";" );
        }
        // fclose( fo );
        std::memset( writebuffer, 0, sizeof( writebuffer ) );
        // ++id;
    }
    for( int i = 0; i < NUM_LANGUAGES; ++i ) { fclose( outfiles[ i ] ); }
    fclose( f );
}
