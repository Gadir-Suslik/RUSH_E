#pragma once
#include "Lexer.hpp"
#include "AST/Node.hpp"
#include "AST/ExecuteNode.hpp"

using namespace std;

class Parser {
public:
    Parser(vector<Token> tl){
        TokenList = tl;
    }

    vector<ExecuteNode*> BuildAST(){
        vector<ExecuteNode*> AST;
        while (!isMatch(TokenTypeList::END))
        {
            AST.push_back(exe());
        }
        return AST;
    }

    ExecuteNode* exe(){
        if (isMatch(TokenTypeList::PRINTLN)){
            Node* result = ParseExpression();
            return new PrintLineNode(result);
        }
        else if (isMatch(TokenTypeList::PRINT)){
            Node* result = ParseExpression();
            return new PrintNode(result);
        }
        else if (isMatch(TokenTypeList::INPUT)){
            return new InputNode();
        }
        else if (isMatch(TokenTypeList::ID)){
            pos--;
            return Createv();
        }
        else if (isMatch(TokenTypeList::IF)){
            return IF_ELSE();
        }
        return new NoneNode();
    }

    ExecuteNode* IF_ELSE(){
        Node* ifblock = ParseExpression();
        ExecuteNode* exeIf = exe();
        ExecuteNode* exeElse;

        if (isMatch(TokenTypeList::ELSE)){
            exeElse = exe();
        }
        else{
            exeElse = nullptr;
        }
        return new ConditionOperatorStatement(ifblock, exeIf, exeElse);
    }

    ExecuteNode* Createv(){
            if (getToken(0).Type == TokenTypeList::ID && getToken(1).Type == TokenTypeList::ASSIGN){
                string name = getToken(0).content;
                isMatch(TokenTypeList::ID);
                isMatch(TokenTypeList::ASSIGN); 
                if (isMatch(TokenTypeList::INPUT)){
                    return new InputVar(name);
                }
                Node* result = ParseExpression();
                return new CreateVar(name, result->Eval());
            }
        
        cerr << "Unknown Declaration!" << getToken(1).content << endl;
        exit(EXIT_FAILURE);
    }

    Node* ParseExpression(){
        Node* res = ParseCondition();
        return res;
    }

    Node* ParseCondition(){
        Node* left = ParseAdd();

        while (isMatch(TokenTypeList::LESS) || isMatch(TokenTypeList::GREATER) || isMatch(TokenTypeList::ASSIGN))
        {
            pos--;
            if (isMatch(TokenTypeList::ASSIGN)){
                Node* right = ParseAdd();
                left = new CondititonNode(left, right, '=');
            }
            else if (isMatch(TokenTypeList::LESS)){
                Node* right = ParseAdd();
                left = new CondititonNode(left, right, '<');
            }
            else if (isMatch(TokenTypeList::GREATER)){
                Node* right = ParseAdd();
                left = new CondititonNode(left, right, '>');
            }
        }
        return left;
    }

    Node* ParseAdd(){
        Node* left = ParseMulti();

        while (isMatch(TokenTypeList::PLUS) || isMatch(TokenTypeList::MINUS))
        {
            pos--;
            if (isMatch(TokenTypeList::PLUS)){
                Node* right = ParseMulti();
                left = new BinaryOperatorNode(left, right, '+');
            }
            else if (isMatch(TokenTypeList::MINUS)){
                Node* right = ParseMulti();
                left = new BinaryOperatorNode(left, right, '-');
            }
        }
        return left;
    }

    Node* ParseMulti(){
        Node* left = ParseUnary();

        while (isMatch(TokenTypeList::MUL) || isMatch(TokenTypeList::DIV))
        {
            pos--;
            if (isMatch(TokenTypeList::MUL)){
                Node* right = ParseUnary();
                left = new BinaryOperatorNode(left, right, '*');
            }
            else if (isMatch(TokenTypeList::DIV)){
                Node* right = ParseUnary();
                const DataTypes* zero = new DoubleType((double)0);
                if (right->Eval() != zero){
                    left = new BinaryOperatorNode(left, right, '/');
                } else {
                    cerr << "Error : Division by zero!" << right->Eval()->ld() << endl;
                    exit(EXIT_FAILURE);
                }
            }
        }
        return left;
    }

    Node* ParseUnary(){
        if (isMatch(TokenTypeList::MINUS)){
            return new UnaryOperatorNode(ParseValue(), '-');
        }
        return ParseValue();
    }

    Node* ParseValue(){
        Token t = getToken(0);
        if (isMatch(TokenTypeList::NUM)){
            return new NumberNode(stold(t.content));
        }
        else if (isMatch(TokenTypeList::LPAR)){
            Node* n = ParseExpression();
            if (isMatch(RPAR)) return n;
            else cerr << "Missed Right Paren!";
            exit(EXIT_FAILURE);
        }
        else if (isMatch(TokenTypeList::STR)){
            return new NumberNode(t.content);
        }
        else if (isMatch(TokenTypeList::ID)){            
            return new ConstNode(t.content);
        }

        throw "Undefined Expression!";
    }

    bool isMatch(TokenTypeList type){
        if (getToken(0).Type == type){
            pos++;
            return true;
        }
        return false;
    }
    
    Token getToken(int rp){
        int posit = pos + rp;
        if (posit < TokenList.size()){
            Token t = TokenList[posit];
            return t;
        }
        return Token(TokenTypeList::END, "");
    }
private:
    vector<Token> TokenList;
    int pos = 0;
};