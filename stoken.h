#ifndef STOKEN_H
#define STOKEN_H


#include <iostream>
#include <string>
#include "token.h"

class STokenize
{
public:
    STokenize();
    STokenize(const string s);
    int GetTokenType(char ch);
    string GetThisToken(string charSet);
    Token NextToken();
    bool Fail();
    bool More();
    int& Pos();

private:
    string _s;
    int _pos;
    bool _more;
};


STokenize::STokenize(){
    _s = "";
    _pos = 0;
    _more = true;

}

STokenize::STokenize(const string s){
    _s = s;
    _pos = 0;
    _more = true;

}

int STokenize::GetTokenType(char ch){

    //Initialize charLists
    string alpha("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");
    string num("0123456789");
    string punc("*+-/^");
    string lParen("({[");
    string rParen(")}]");


    int isAlpha = alpha.find(ch);   // ////////////////////////
    int isNum = num.find(ch);       //    find the type of the
    int isPunc = punc.find(ch);     //    char_type variable
    int isLParen = lParen.find(ch);   // ////////////////////////
    int isRParen = rParen.find(ch);

    if(isAlpha >-1)
        return 0;
    else if(isNum > -1)      // ///////////////////////////////////////////////////
        return 1;            //
    else if(isPunc >-1)      // returns an int when the char is found in a charset
        return 2;            //
    else if(isLParen >-1)     // ///////////////////////////////////////////////////
        return 3;
    else if(isRParen >-1)
        return 4;
    else
        return -1;
}

string STokenize::GetThisToken(string charSet){

//    cout<< "GetThisToken"<<endl;
    int start = _s.find_first_of(charSet, Pos()), end = _s.find_first_not_of(charSet, Pos());
//    cout<< "start position = "<< start << " and end position = "<< end<<"length(): "<<_s.length()<<endl;
    string tokenHolder(_s.substr(start, end-start));
//    cout<< "tokenHolder = "<< tokenHolder <<endl<<endl;

    if(end> _s.length())
        Pos() = -1;
    else
        Pos() = end;
    return tokenHolder;
}


Token STokenize::NextToken(){

    int type = GetTokenType(_s[_pos]);
    Token tokenHolder;

    //Initialize charLists
    string alpha("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");
    string num("0123456789");
    string punc("*+-/^");
    string lParen("({[");
    string rParen(")}]");

    switch (type) {
    case 0:
//        cout<< " (alphabets)"<<endl;
        tokenHolder.TokenString() = GetThisToken(alpha);
        if(tokenHolder.TokenString().length() == 1)
            tokenHolder.Type() = 0;
        if(tokenHolder.TokenString().length()>1)
            tokenHolder.Type() = 5;
        return tokenHolder;
        break;
    case 1:
//        cout<< " (numbers)"<<endl;
        tokenHolder.TokenString() = GetThisToken(num);
        tokenHolder.Type() = 1;
        return tokenHolder;
        break;
    case 2:
//        cout<< " (punctuations)"<<endl;
        tokenHolder.TokenString() = GetThisToken(punc);
        tokenHolder.Type() = 2;
        return tokenHolder;
        break;
    case 3:
//        cout<< " (lParen)"<<endl;
        tokenHolder.TokenString() = GetThisToken(lParen);
        if(tokenHolder.TokenString().length() >1){
            Pos() -= tokenHolder.TokenString().length()-1;
        }
        tokenHolder.Type() =3;
        return tokenHolder;
        break;
    case 4:
//        cout<< " (rParen)"<<endl;
        tokenHolder.TokenString() = GetThisToken(rParen);
        if(tokenHolder.TokenString().length() >1){
            Pos() -= tokenHolder.TokenString().length()-1;
        }
        tokenHolder.Type() =4;
        return tokenHolder;
        break;
    default:
        _more = false;
        return tokenHolder;
        break;
    }
}

bool STokenize::Fail(){
    if(More())
        return false;
    else
        return true;
}

bool STokenize::More(){
    if(_pos == -1){
        _more = false;
    }
    else
        _more = true;

    return _more;
}

int& STokenize::Pos(){
    return _pos;
}

#endif // STOKEN_H
