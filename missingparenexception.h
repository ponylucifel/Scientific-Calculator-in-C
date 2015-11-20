#ifndef MISSINGPARENEXCEPTION_H
#define MISSINGPARENEXCEPTION_H
#include <iostream>
using namespace std;

class MissingParenException{
public:
    MissingParenException(char s);
    void GetMissing();
private:
    char _s;
};

MissingParenException::MissingParenException(char s):_s(s)
{
    //left blank
}

void MissingParenException::GetMissing()
{
    if(_s ==')')
        cout<< "Left paren is missing."<<endl;
    if(_s == '(')
        cout<< "Right paren is missing."<<endl;
}

#endif // MISSINGPARENEXCEPTION_H



