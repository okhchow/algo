#include <iostream>
#include <cstdlib>
#include <cassert>

using namespace std;

int my_atoi( char* str )
{
    int ret = 0;

    for( int i = 0; str[ i ] >= '0' && str[ i ] <= '9'; ++i )
    {
        ret *= 10;
        ret += (int)( str[ i ] - '0' );
    }

    return ret;
}

int main( int argc, char** argv )
{
    for( int i = 1; i < argc; ++i )
    {
        int sys = atoi( argv[ i ] );
        int my = atoi( argv[ i ] );
        cout << sys << " | " << my << endl;
        assert( sys == my );
    }
}
