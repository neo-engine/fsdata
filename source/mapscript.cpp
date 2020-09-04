#include <cstdio>
#include <cassert>
#include "fsdata.h"

#define MAX_SCRIPT_SIZE 128

std::string FILENAME;

void printMapScript( u32* p_script, u16 p_id ) {
    FILE* f = getFilePtr( FSROOT "/MAP_SCRIPT/", p_id, 2, ".mapscr" );
    assert( f );
    fwrite( p_script, sizeof( u32 ), MAX_SCRIPT_SIZE, f );
    fclose( f );
}

int main( int p_argc, char** p_argv ) {
    if( p_argc < 2 ) {
        fprintf( stderr, "too few args." );
        return 1;
    }
    FILENAME = string( p_argv[ 1 ] );

    u32 SCRIPT[ MAX_SCRIPT_SIZE ] = { 0 };

    FILE* f = fopen( p_argv[ 1 ], "r" );
    assert( f );

    for( u8 i = 0; i < MAX_SCRIPT_SIZE && fscanf( f, "%u", &SCRIPT[ i ] ) != EOF; ++i ) {
//        printf( "[%s] Read %08x\n", FILENAME.c_str( ), SCRIPT[ i ] );
    }

    u16 idx = 0;
    sscanf( p_argv[ 1 ], "%*[^0-9]%hu", &idx );
    printf( "[%s] Saving to %hu\n", p_argv[ 1 ], idx );

    printMapScript( SCRIPT, idx );
}
