#include <iostream>
#include <cstdlib>
#include <stack>
#include <cassert>

using namespace std;

// 3 towers
stack< int >* s;

void move( int a, int b, int n )
{
    if( n < 1 )
        return;

    int temp_tower = 3 - a - b;
    move( a, temp_tower, n-1 );
    assert( s[ a ].top() == n );

    // cout << "s[ " << a << " ] => " << n << " => s[ " << b << " ]" << endl;
    s[ b ].push( s[ a ].top() );
    s[ a ].pop();
    move( temp_tower, b, n-1 );
}

int main( int argc, char** argv )
{
    assert( argc == 2 );
    int numDiscs = atoi( argv[ 1 ] );
    s = new stack< int >[ 3 ];

    // initialize
    for( int i = numDiscs; i > 0; --i )
        s[ 0 ].push( i );

    move( 0, 2, numDiscs );

    for( int i = 1; i <= numDiscs; ++i )
    {
        assert( s[ 2 ].top() == i );
        s[ 2 ].pop();
    }
}
