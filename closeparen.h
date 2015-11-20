#ifndef CLOSEPAREN_H
#define CLOSEPAREN_H
#include "token.h"

class CloseParen: public Token{
public:
    CloseParen();
    CloseParen(string str);
    int TypeOf();
    void Print();
    char RParen();

private:
    char myRParen;
};



CloseParen::CloseParen()
{
    myRParen = TokenString().at(0);
}

CloseParen::CloseParen(string str)
{
    myRParen = str.at(0);
}

int CloseParen::TypeOf()
{
    return 4; // indicating that this is a close paren
}

void CloseParen::Print()
{
    cout<< myRParen;
}

char CloseParen::RParen()
{
    return myRParen;
}
#endif // CLOSEPAREN_H


