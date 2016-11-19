#include "Document.h"
#include <fstream>

using namespace std;

void MyDocument :: openFile(const string name)
{
    if(!_fstream.is_open()) _fstream.open(name.c_str(), ifstream::in);
}
bool MyDocument :: canOpenDocument(const string name)
{
    bool f = false;
    _fstream.open(name.c_str(), fstream::in);
    if(_fstream.is_open()) f = true;
    _fstream.close();
    return f;
}
string MyDocument :: readFile()
{
    string result;
    string buffer;
    string name = "test.txt";
    while (getline(_fstream, buffer)) result += buffer;
    _fstream.close();
    return result;
}
