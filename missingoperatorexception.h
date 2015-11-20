#ifndef MISSINGOPERATOREXCEPTION_H
#define MISSINGOPERATOREXCEPTION_H
#include <iostream>

using namespace std;

class MissingOperatorException{
public:
    MissingOperatorException(char s);
    char GetExtraNumber();
private:
    char _s;
};

#endif // MISSINGOPERATOREXCEPTION_H

MissingOperatorException::MissingOperatorException(char s)
{
    _s = s;
}

char MissingOperatorException::GetExtraNumber()
{
    cout<< "This number "<<_s<<" is missing an operator to matched."<<endl;
    return _s;
}
