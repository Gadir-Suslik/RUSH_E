#pragma once

#include "DataTypes.hpp"
#include <string>

struct Node {
    virtual DataTypes* Eval() = 0;
};

struct NumberNode : public Node {
public:
    NumberNode(long double val){
        data = new DoubleType(val);
    }

    NumberNode(string val){
        data = new StringType(val);
    }

    NumberNode(bool ch){
        data = new Boolean(ch);
    }

    DataTypes* Eval() override {
        return data;
    }
private:
    DataTypes* data;
};

struct BinaryOperatorNode : public Node {
public:
    BinaryOperatorNode(Node* l, Node* r, char oper){
        left = l;
        right = r;
        op = oper;
    }

    DataTypes* Eval() override {

        DataTypes* leftData = left->Eval();
        DataTypes* rightData = right->Eval();
        if (dynamic_cast<StringType*>(leftData) != nullptr){
            switch (op)
            {
            case '+' :
                return new StringType(leftData->tostring() + rightData->tostring());
            case '*' :
                stringstream str;
                for (int i = 0; i < right->Eval()->ld(); i++){
                    str << leftData->tostring();
                }
                return new StringType(str.str());
            }
        }        

        switch (op){
            case '+' : return new DoubleType(left->Eval()->ld() + right->Eval()->ld());
            case '-' : return new DoubleType(left->Eval()->ld() - right->Eval()->ld());
            case '*' : return new DoubleType(left->Eval()->ld() * right->Eval()->ld());
            case '/' : return new DoubleType(left->Eval()->ld() / right->Eval()->ld());
            default:
                return new DoubleType(left->Eval()->ld() + right->Eval()->ld());
        }
    }

private:
    Node* left;
    Node* right;
    char op;
};

struct CondititonNode : public Node {
public:
    CondititonNode(Node* l, Node* r, char oper){
            left = l;
            right = r;
            op = oper;
    }


    DataTypes* Eval() override {

        DataTypes* leftData = left->Eval();
        DataTypes* rightData = right->Eval();
        if (dynamic_cast<StringType*>(leftData) != nullptr){
            switch (op)
            {
            case '=' :
                return new Boolean(left->Eval()->tostring() == right->Eval()->tostring());
            }
        } 

        switch (op){
            case '=' : return new Boolean(left->Eval()->ld() == right->Eval()->ld());
            case '>' : return new Boolean(left->Eval()->ld() > right->Eval()->ld());
            case '<' : return new Boolean(left->Eval()->ld() < right->Eval()->ld());
            default:
                return new Boolean(left->Eval()->ld() == right->Eval()->ld());
        }
    }

private:
    Node* left;
    Node* right;
    char op;
};

struct ConstNode : public Node {
    ConstNode(string k){
        key = k;
    }

    DataTypes* Eval() override {
        return vars[key];
    }
private:

    string key;
};

struct UnaryOperatorNode : public Node {

    UnaryOperatorNode(Node* l, char oper){
        left = l;
        op = oper;
    }

    DataTypes* Eval() override {
        switch (op){
            case '+' : return new DoubleType(left->Eval()->ld());
            case '-' : return new DoubleType(-left->Eval()->ld());
            default:
                return new DoubleType(left->Eval()->ld());
        }
    }

private:
    Node* left;
    char op;
};


