#include "graph.h"
#include "graphLoader.h"
#include <cassert>

using namespace std;

int main()
{
    StaticGraph* sg = loadGraph( "graphTest.txt" );

    assert( sg );

    assert( sg->numVerts() == 5 );
    assert( sg->numEdges() == 5 );

    for( int i = 0; i < 5; ++i )
    {
        int a1 = (i+2)%5;
        int a2 = (i+3)%5;
        assert( sg->edgeExists( i, a1 ) );
        assert( sg->cost( i, a1 ) == 1 );
        assert( sg->edgeExists( i, a2 ) );
        assert( sg->cost( i, a2 ) == 1 );
    }

    delete sg;
}
