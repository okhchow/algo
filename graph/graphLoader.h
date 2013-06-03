#ifndef ___GRAPH_LOADER_H__
#define ___GRAPH_LOADER_H__

/*
|| File format:
|| <num verts>
|| <vert #> <num edges>
|| <dest vert> <cost>
|| <dest vert> <cost>
|| ...
*/

#include "graph.h"
#include <string>
#include <fstream>
#include <sstream>
#include <cassert>

#include <iostream>

StaticGraph* loadGraph( std::string filepath )
{
    std::ifstream file( filepath.c_str() );
    assert( file.is_open() && "Unable to open file" );

    int numVerts;
    file >> numVerts;

    StaticGraph* sg = new StaticGraph( numVerts );

    std::string line;
    std::getline( file, line );
    std::cout << "DEL line \"" << line << "\"" << std::endl;

    while( !file.eof() )
    {
        std::getline( file, line );
        std::stringstream ss( line );

        int v;
        int numEdges;
        ss >> v;
        ss >> numEdges;
        std::cout << "FOR v" << v << " " << numEdges << " edges" << std::endl;

        for( int e = 0; e < numEdges; ++e )
        {
            std::getline( file, line );
            std::stringstream ss( line );
            int destVert;
            int cost;
            ss >> destVert;
            ss >> cost;
            std::cout << "ADD edge(" << v << "," << destVert << ")" << std::endl;
            sg->addEdge( v, destVert, cost );
        }
    }

    std::cout << "END" << std::endl;
}

#endif
