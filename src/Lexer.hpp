#pragma once

#include "Token.hpp"
#include <string>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

class Lexer {
public:
    Lexer(string _code){
        code = _code;
    }


    vector<Token> Tokenize(){
        while(pos < code.length()){
            NextToken();
        }
        return ListTok;
    }

    bool NextToken(){

        string Tokenstr = "";

            char c = peek(0); // current char
            if (isalpha(c)){
                while (isalnum(peek(0)) || peek(0) == '_'){
                    Tokenstr += peek(0);
                    pos++;
                }
                if (Tokenstr == "println"){
                    ListTok.push_back(Token(TokenTypeList::PRINTLN, Tokenstr));
                    Tokenstr = "";
                }
                else if (Tokenstr == "read"){
                    ListTok.push_back(Token(TokenTypeList::INPUT, Tokenstr));
                    Tokenstr = "";
                }
                else if (Tokenstr == "print"){
                    ListTok.push_back(Token(TokenTypeList::PRINT, Tokenstr));
                    Tokenstr = "";
                }
                else if (Tokenstr == "if"){
                    ListTok.push_back(Token(TokenTypeList::IF, Tokenstr));
                    Tokenstr = "";
                }
                else if (Tokenstr == "else"){
                    ListTok.push_back(Token(TokenTypeList::ELSE, Tokenstr));
                    Tokenstr = "";
                }
                else {
                    ListTok.push_back(Token(TokenTypeList::ID, Tokenstr));
                    Tokenstr = "";
                }
            }
            else if (isdigit(c) || c == '.'){
                while (isdigit(peek(0)) || peek(0) == '.'){
                    if (peek(0) == '.' && Tokenstr.find('.') != -1){
                        cerr << "Invalid double!" << endl;
                        exit(EXIT_FAILURE);
                    }
                    Tokenstr += peek(0);
                    pos++;
                }
                Token add = Token(TokenTypeList::NUM, Tokenstr);
                ListTok.push_back(add);
                Tokenstr = "";
            }
            else if (c == '"'){
                pos++;
                while (peek(0) != '"'){
                    Tokenstr += peek(0);
                    pos++;
                }
                ListTok.push_back(Token(TokenTypeList::STR ,Tokenstr));
                Tokenstr = "";
                pos++;
            }
            else if (c == '~'){
                pos++;
                while (peek(0) != '\n')
                {
                    pos++;
                }
                pos++;
            }
            else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')' || c == '=' || c == '<' || c == '>' || c == '!' || c == '|' || c == '&') {
                if(c == '+') ListTok.push_back(Token(TokenTypeList::PLUS, "+"));
                if(c == '-') ListTok.push_back(Token(TokenTypeList::MINUS, "-"));
                if(c == '*') ListTok.push_back(Token(TokenTypeList::MUL, "*"));
                if(c == '/') ListTok.push_back(Token(TokenTypeList::DIV, "/"));
                if(c == '(') ListTok.push_back(Token(TokenTypeList::LPAR, "("));
                if(c == ')') ListTok.push_back(Token(TokenTypeList::RPAR, ")"));
                if(c == '=') ListTok.push_back(Token(TokenTypeList::ASSIGN, "="));
                if(c == '<') ListTok.push_back(Token(TokenTypeList::LESS, "<"));
                if(c == '>') ListTok.push_back(Token(TokenTypeList::GREATER, ">"));
                if(c == '!') ListTok.push_back(Token(TokenTypeList::NOT, "!"));
                if(c == '&') ListTok.push_back(Token(TokenTypeList::AND, "&"));
                if(c == '|') ListTok.push_back(Token(TokenTypeList::OR, "|"));
                pos++;
            }
            else{
                pos++;
            }
            return true;
    }


    char peek(int relative){
        int position = relative + pos;
        if (position < code.length()) return code[position];
        return ' ';
    }


private:
    int pos = 0;
    string code;
    vector<Token> ListTok;
};
