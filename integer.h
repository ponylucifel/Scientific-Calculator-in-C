#ifndef INTEGER_H
#define INTEGER_H
#include "token.h"

class Integer: public Token{
public:
    Integer();
    Integer(string str);
    int TypeOf();
    void Print();
    int MyInt();
private:
    int myInt;
};


Integer::Integer()
{
    myInt = std::atoi(TokenString().c_str());
    cout<< "TokenString(): "<<TokenString()<<endl ;
}

Integer::Integer(string str)
{
    myInt = std::atoi(str.c_str());
}

int Integer::TypeOf()
{
    return 1; // indicating that this is an integer value
}

void Integer::Print(){
    cout<< "["<<myInt<<"] ";
}

int Integer::MyInt()
{
    return myInt;
}

#endif // INTEGER_H


