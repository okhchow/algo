#include <fstream>
#include <iostream>

using namespace std;

int main()
{
    ifstream file( "test.txt" );
    int i;
    file >> i;
    string s;
    getline( file, s );
    cout << s << endl;
}
