#include <cstdio>
#include <cassert>
#include <cstring>
#include "fsdata.h"

std::string PATH;
u16 STRING_LEN = 100;

int main( int p_argc, char** p_argv ) {
    if( p_argc < 4 ) {
        fprintf( stderr, "too few args. (file, outpath, max string len)" );
        return 1;
    }
    PATH = string( p_argv[ 2 ] );
    sscanf( p_argv[ 3 ], "%hu", &STRING_LEN );
    FILE* f = fopen( p_argv[ 1 ], "r" );

    char buffer[ NUM_LANGUAGES * STRING_LEN + 10 ] = { 0 };
    char writebuffer[ STRING_LEN + 10 ] = { 0 };
   //  printf( "/%s/ %lu %hu\n", buffer, sizeof(buffer), STRING_LEN );

    u16 id = 0;
    while( f && fgets( buffer, sizeof( buffer ), f ) ) {
    //    printf( "/%s/ %lu %hu\n", buffer, sizeof(buffer), STRING_LEN );
        char* tok = strtok( buffer, ";" );
        FILE* fo = getFilePtr( std::string( FSROOT ) + PATH, id, 2, ".str" );
        assert( fo );
        for( int i = 0; i < NUM_LANGUAGES; ++i ) {
            std::memset( writebuffer, 0, sizeof( writebuffer ) );
            std::strncpy( writebuffer, tok, STRING_LEN );
      //      printf( "->%s<-\n",  tok );

            fwrite( fixEncoding( writebuffer ), sizeof( u8 ), STRING_LEN, fo );
            tok = strtok( NULL, ";" );
        }
        fclose( fo );
        std::memset( writebuffer, 0, sizeof( writebuffer ) );
        ++id;
    }
    fclose( f );
}
