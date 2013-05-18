#include "equ_to_tree.h"
#include <iostream>
#include <deque>
#include <cassert>

#define DEBUG

using namespace std;

void printTree( Node* head )
{
    deque< Node* > q;
    deque< int > qi;
    int depth = 0;

    q.push_back( head );
    qi.push_back( depth );

    while( !q.empty() )
    {
        Node* n = q.front();
        int d = qi.front();
        q.pop_front();
        qi.pop_front();
        
        if( d > depth )
        {
            depth = d;
            cout << endl;
        }
        else if( d != 0 )
            cout << " ";
        cout << n->value;
        
        if( n->child[ LEFT ] )
        {
            q.push_back( n->child[ LEFT ] );
            qi.push_back( d+1 );
        }
        if( n->child[ RIGHT ] )
        {
            q.push_back( n->child[ RIGHT ] );
            qi.push_back( d+1 );
        }
    }
}

void freeTree( Node* head )
{
    if( !head )
        return;

    freeTree( head->child[ LEFT ] );
    freeTree( head->child[ RIGHT ] );

    delete head;
}

Node* divExpr( string expr )
{
    for( int i = 0; i < BEDMAS_SIZE; ++i )
    {
        int b_count = 0;
        for( int cidx = 0; cidx < expr.length(); ++cidx )
        {
            char c = expr[ cidx ];
            if( c == '(' )
                ++b_count;
            else if( c == ')' )
                --b_count;

            if( b_count > 0 )
                continue;

            if( bedmas[ i ].find( c ) == string::npos )
                continue;

            Node* curr = new Node();
            curr->value = c;
            curr->child[ LEFT ] = divExpr( expr.substr( 0, cidx ) );
            curr->child[ RIGHT ] = divExpr( expr.substr( cidx+1, string::npos ) );

            return curr;
        }
    }

    if( expr[ 0 ] == '(' )
    {
        assert( expr[ expr.length()-1 ] == ')' );
        return divExpr( expr.substr( 1, expr.length()-2 ) );
    }
    else
    {
        assert( expr.find( '(' ) == string::npos );
        Node* curr = new Node();
        curr->value = expr;
        curr->child[ LEFT ] = NULL;
        curr->child[ RIGHT ] = NULL;
        return curr;
    }
}

int main( int argc, char* argv[] )
{
    if( argc != 2 )
    {
        cerr << "Bad arguments" << endl;
        return -1;
    }

    string expression = argv[1];

    #ifdef DEBUG
    cout << "expr[ " << expression.length() << " ] = " << expression << endl;
    #endif

    Node* tree = divExpr( expression );
    printTree( tree );

    freeTree( tree );

    cout << endl;
}
