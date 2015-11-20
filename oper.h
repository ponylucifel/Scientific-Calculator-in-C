#ifndef OPER_H
#define OPER_H
#include "token.h"

class Oper: public Token{
public:
    Oper();
    Oper(string str);
    int TypeOf();
    void Print();
    int PresidenceVal();
    char MyOper();
private:
    char myOper;
    int presidence;
};
#endif // OPER_H


Oper::Oper():presidence(0)
{
    myOper = TokenString().at(0);
    if(myOper == '+' || myOper == '-')
        presidence = 1;
    if(myOper == '*' || myOper == '/')
        presidence = 2;
    if(myOper == '^')
        presidence = 3;
}

Oper::Oper(string str):presidence(0)
{
    myOper = str.at(0);
    if(myOper == '+' || myOper == '-')
        presidence = 1;
    if(myOper == '*' || myOper == '/')
        presidence = 2;
    if(myOper == '^')
        presidence = 3;
}

int Oper::TypeOf()
{
    return 2; //indicating that this is an operator sign
}

void Oper::Print()
{
    cout<<"("<< myOper<<") ";
}

int Oper::PresidenceVal()
{
    return presidence;
}

char Oper::MyOper()
{
    return myOper;
}
