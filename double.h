#ifndef DOUBLE_H
#define DOUBLE_H
#include "token.h"

class Double: public Token{
public:
    Double();
    Double(string str);
    int TypeOf();
    void Print();
private:
    double myDouble;
};

#endif // DOUBLE_H


Double::Double()
{
    myDouble = (double)(atoi(TokenString().c_str()));
}

Double::Double(string str)
{
    myDouble = (double)(atoi(str.c_str()));
}

int Double::TypeOf()
{
    return 0; // indicating this is a double value
}

void Double::Print()
{
    cout <<myDouble;
}
