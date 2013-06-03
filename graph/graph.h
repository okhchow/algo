#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <cassert>

class StaticGraph
{
public:
    StaticGraph( int numVerts );
    ~StaticGraph();

public:
    bool edgeExists( int v1, int v2 );
    int cost( int v1, int v2 );
    void addEdge( int v1, int v2, int cost );
    void removeEdge( int v1, int v2 );

public:
    int numVerts() { return m_vsize; }
    int numEdges() { return m_esize; }

private:
    void order( int& v1, int& v2 );

private:
    int** m_adjs;
    int** m_costs;
    int m_vsize;
    int m_esize;
};


StaticGraph::StaticGraph( int numVerts )
{
    m_adjs = new int*[ numVerts ];
    m_costs = new int*[ numVerts ];
    for( int i = 0; i < numVerts; ++i )
    {
        m_adjs[ i ] = new int[ numVerts ];
        m_costs[ i ] = new int[ numVerts ];
        for( int j = 0; j < numVerts; ++j )
        {
            m_adjs[ i ][ j ] = 0;
            m_costs[ i ][ j ] = 0;
        }
    }

    m_vsize = numVerts;
    m_esize = 0;
}

StaticGraph::~StaticGraph()
{
    for( int i = 0; i < m_vsize; ++i )
    {
        delete m_adjs[ i ];
        delete m_costs[ i ];
    }
    delete m_adjs;
    delete m_costs;
}

bool StaticGraph::edgeExists( int v1, int v2 )
{
    assert( v1 >= 0 && v1 < m_vsize );
    assert( v2 >= 0 && v2 < m_vsize );

    if( v1 == v2 )
        return false;

    order( v1, v2 );
    return m_adjs[ v1 ][ v2 ] == 1;
}

int StaticGraph::cost( int v1, int v2 )
{
    assert( v1 >= 0 && v1 < m_vsize );
    assert( v2 >= 0 && v2 < m_vsize );

    assert( v1 != v2 );
    assert( edgeExists( v1, v2 ) );

    order( v1, v2 );
    return m_costs[ v1 ][ v2 ];
}

void StaticGraph::addEdge( int v1, int v2, int cost )
{
    assert( v1 >= 0 && v1 < m_vsize );
    assert( v2 >= 0 && v2 < m_vsize );

    if( v1 == v2 )
        return;

    order( v1, v2 );
    m_adjs[ v1 ][ v2 ] = 1;
    m_costs[ v1 ][ v2 ] = cost;
    ++m_esize;
}

void StaticGraph::removeEdge( int v1, int v2 )
{
    assert( v1 >= 0 && v1 < m_vsize );
    assert( v2 >= 0 && v2 < m_vsize );

    if( v1 == v2 )
        return;

    order( v1, v2 );
    
    if( m_adjs[ v1 ][ v2 ] != 1 )
        return;
    else
    {
        m_adjs[ v1 ][ v2 ] = 0;
        m_costs[ v1 ][ v2 ] = 0;
        --m_esize;
    }
}

void StaticGraph::order( int& v1, int& v2 )
{
    if( v1 <= v2 )
        return;
    else
    {
        int temp = v1;
        v1 = v2;
        v2 = temp;
    }
}

#endif
