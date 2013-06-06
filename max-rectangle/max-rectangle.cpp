#include <iostream>
#include <string>
#include <stack>
#include <cstdlib>
#include <cassert>

using namespace std;

const char MARKED_POS = '#';
const char EMPTY_POS = ' ';

char** randGrid( int N, int M )
{
    char** grid = new char*[ N ];
    for( int i = 0; i < N; ++i )
        grid[ i ] = new char[ M ];

    for( int i = 0; i < N; ++i )
    {
        for( int j = 0; j < M; ++j )
        {
            int randNum = rand() % 4 + 1;
            if( randNum == 4 )
                grid[ i ][ j ] = EMPTY_POS;
            else
                grid[ i ][ j ] = MARKED_POS;
        }
    }

    return grid;
}

void printGrid( char** grid, int N, int M )
{
    for( int i = 0; i < N; ++i )
    {
        for( int j = 0; j < M; ++j )
        {
            cout << grid[ i ][ j ];
        }
        cout << endl;
    }
    cout << endl;
}

void freeGrid( char** grid, int N, int M )
{
    for( int i = 0; i < N; ++i )
        delete grid[ i ];
    delete grid;
}

int main()
{
    int N = 10;
    int M = 10;

    char** grid = randGrid( N, M );
    printGrid( grid, N, M );

    //-----------------------------------
    // ALGORITHM
    int bestArea = -1;
    int bestLLx = -1;
    int bestLLy = -1;
    int bestURx = -1;
    int bestURy = -1;
    stack< int > widthStack;
    stack< int > posStack;
    int* cache = new int[ N ];
    for( int i = 0; i < N; ++i )
        cache[ i ] = 0;

    for( int j = M-1; j >= 0; --j )
    {
        int width = 0;
        for( int k = 0; k < N; ++k )
        {
            if( grid[ k ][ j ] == MARKED_POS )
                ++cache[ k ];
            else
                cache[ k ] = 0;
        }

        for( int i = N-1; i >= 0; --i )
        {
            if( cache[ i ] > width )
            {
                widthStack.push( cache[ i ] );
                posStack.push( i );
                cerr << "pushed: (" << i << "," << cache[ i ] << ")" << endl;
                width = cache[ i ];
            }
            else if( cache[ i ] < width )
            {
                int lastPos = -1;

                while( !widthStack.empty() && widthStack.top() > cache[ i ] )
                {
                    int currArea = ( posStack.top() - i ) * widthStack.top();
                    cerr << "pop: (" << posStack.top() << "," << widthStack.top() << ")" << endl;
                    if( currArea > bestArea )
                    {
                        bestArea = currArea;
                        bestLLx = j;
                        bestLLy = posStack.top();
                        bestURx = j+widthStack.top()-1;
                        bestURy = i+1;
                    }
                    lastPos = posStack.top();
                    posStack.pop();
                    widthStack.pop();
                }

                width = cache[ i ];
                if( width )
                {
                    assert( lastPos != -1 );
                    widthStack.push( width );
                    posStack.push( lastPos );
                    cerr << "pushed: (" << lastPos << "," << width << ")" << endl;
                }
            }
        }

        while( !widthStack.empty() )
        {
            int currArea = ( posStack.top() + 1 ) * widthStack.top();
            cerr << "pop: (" << posStack.top() << "," << widthStack.top() << ")" << endl;
            if( currArea > bestArea )
            {
                bestArea = currArea;
                bestLLx = j;
                bestLLy = posStack.top();
                bestURx = j+widthStack.top()-1;
                bestURy = 0;
            }
            posStack.pop();
            widthStack.pop();
        }
    }

    delete cache;

    cout << "area = " << bestArea << endl;
    cout << "LL = " << bestLLx << "," << bestLLy << endl;
    cout << "UR = " << bestURx << "," << bestURy << endl;
    //-----------------------------------

    freeGrid( grid, N, M );
}
