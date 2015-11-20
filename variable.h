#ifndef VARIABLE_H
#define VARIABLE_H
#include "token.h"

class Variable:public Token
{
public:
    Variable();
    Variable(string str);
    int TypeOf();
    void Print();
    char MyVar();
    double &MyValue();
private:
    char myVar;
    double myValue;
};


#endif // VARIABLE_H


Variable::Variable()
{
    myVar = TokenString().at(0);
}

Variable::Variable(string str)
{
    myVar = str.at(0);
}

int Variable::TypeOf()
{
    return 0;
}

void Variable::Print()
{
    cout<<"["<<myVar<<"] ";
}

char Variable::MyVar()
{
    return myVar;
}

double& Variable::MyValue()
{
    return myValue;
}
