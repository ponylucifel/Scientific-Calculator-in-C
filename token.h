#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>
#include <string>

using namespace std;

class Token
{
public:
    Token();
    Token(string s, int type);
    Token(char ch, int type = 0);
    //BIG THREE

    //MEMBER FUNCTIONS
    friend ostream& operator <<(ostream& outs, const Token& t);
    int& Type();
    string& TokenString();

    //INHERITANCE FUNCTIONS
    virtual int TypeOf();
    virtual void Print();

private:
    string _token;
    int _type;
};


Token::Token(){
//    cout<<"Defualt CTOR gets called"<<endl;
    _token = "";
    _type = 0;
}

Token::Token(string s, int type = 0){
    _token = s;
    _type = type;
}

Token::Token(char ch, int type){
    _token = "";
    _token += ch;
    _type = type;
}

ostream& operator <<(ostream& outs, const Token& t){
//    outs << "{ [" << t._token << "] "<< t._type<<" }";
    outs << t._token;
    return outs;
}

int& Token::Type(){
    return _type;
}

string& Token::TokenString(){
    return _token;
}

int Token::TypeOf()
{
    //BOGUS
}

void Token::Print()
{
    //BOGUS
}

#endif // TOKEN_H
