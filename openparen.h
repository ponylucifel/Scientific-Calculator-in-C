#ifndef OPENPAREN_H
#define OPENPAREN_H
#include "token.h"

class OpenParen: public Token{
public:
    OpenParen();
    OpenParen(string str);
    int TypeOf();
    void Print();
    char LParen();
private:
    char myLParen;
};
#endif // OPENPAREN_H


OpenParen::OpenParen()
{
    myLParen = TokenString().at(0);
}

OpenParen::OpenParen(string str)
{
    myLParen = str.at(0);
}

int OpenParen::TypeOf()
{
    return 3; // indicating that this is an open paren
}

void OpenParen::Print()
{
    cout<< myLParen;
}

char OpenParen::LParen(){
    return myLParen;
}
