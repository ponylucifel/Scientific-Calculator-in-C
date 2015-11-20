#ifndef FUNCTION_H
#define FUNCTION_H
#include "token.h"

class Function:public Token
{
public:
    Function();
    Function(string str);
    int TypeOf();
    void Print();
    string MyFunc();
    int PresidenceVal();

private:
    string myFunc;
    int presidence;
};
#endif // FUNCTION_H


Function::Function()
{
    myFunc = TokenString();
    if(myFunc == "sin" || myFunc == "cos"
            || myFunc == "tan" || myFunc == "sec"
            || myFunc == "csc" || myFunc == "cot"){
        presidence = 5;
        //throw an exception for anything other than this for now
    }
    else
        presidence = -1;
}

Function::Function(string str)
{
    myFunc = str;
    if(myFunc == "sin" || myFunc == "cos"
            || myFunc == "tan" || myFunc == "sec"
            || myFunc == "csc" || myFunc == "cot"){
        presidence = 5;
    }
    else if(myFunc == "sqrt")
        presidence = 4;
    else
        presidence = -1;
}

int Function::TypeOf()
{
    return 5;
}

void Function::Print()
{
    cout<<"("<<myFunc<<") ";
}

string Function::MyFunc()
{
    return myFunc;
}

int Function::PresidenceVal()
{
    return presidence;
}
