#pragma once
#include <string>
#include <unordered_map>
using namespace std;

enum TokenTypeList : int {
    NUM,
    STR,

    PLUS,
    MINUS,
    MUL,
    DIV,
    ASSIGN,

    LPAR,
    RPAR,
    ID,
    IF,
    ELSE,

    EQUAL,
    LESSEQ,
    GRETEQ,
    NOT,
    NOTEQ,
    AND,
    OR,
    LESS,
    GREATER,

    ANDAND,
    OROR,

    PRINT,
    PRINTLN,
    INPUT,

    END,

};

unordered_map<string, TokenTypeList> operators = {
    {"+", TokenTypeList::PLUS},
    {"-", TokenTypeList::MINUS},
    {"*", TokenTypeList::MUL},
    {"/", TokenTypeList::DIV},
    {"(", TokenTypeList::LPAR},
    {")", TokenTypeList::RPAR},
    {">", TokenTypeList::GREATER},
    {"<", TokenTypeList::LESS},
    {"!", TokenTypeList::NOT},
    {"=", TokenTypeList::ASSIGN},
    {"==", TokenTypeList::EQUAL},
    {"!=", TokenTypeList::NOTEQ},
    {">=", TokenTypeList::GRETEQ},
    {"<=", TokenTypeList::LESSEQ},
    {"&", TokenTypeList::AND},
    {"|", TokenTypeList::OR},
    {"&&", TokenTypeList::ANDAND},
    {"||", TokenTypeList::OROR},
};
 
class Token {
public:
    TokenTypeList Type;
    string content;

    Token(){

    };
    Token(TokenTypeList t, string v){
        Type = t;
        content = v;
    }
};

