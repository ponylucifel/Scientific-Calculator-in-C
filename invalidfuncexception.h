#ifndef INVALIDFUNCEXCEPTION_H
#define INVALIDFUNCEXCEPTION_H
#include <iostream>

using namespace std;

class InvalidFuncException{
public:
    InvalidFuncException();
    InvalidFuncException(string s);
    string GetInvalidFunc();
private:
    string _s;
};

InvalidFuncException::InvalidFuncException()
{
    _s = "";
}

InvalidFuncException::InvalidFuncException(string s): _s(s)
{
    //left blank
}

string InvalidFuncException::GetInvalidFunc()
{
    cout<< "This token contains invalid function expression: "<< _s<<endl;
    return _s;
}

#endif // INVALIDFUNCEXCEPTION_H


