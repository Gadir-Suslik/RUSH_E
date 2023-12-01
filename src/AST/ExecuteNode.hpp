#pragma once

#include <iostream>

struct ExecuteNode {
    virtual void Execute() = 0;
};

struct NoneNode : public ExecuteNode{
    void Execute() override {

    }
};

struct PrintLineNode : public ExecuteNode{
public:
    PrintLineNode(Node* node){
        n = node;
    }

    void Execute() override {
        cout << n->Eval()->tostring() << endl;
    }
private:
    Node* n;
};

struct PrintNode : public ExecuteNode{
public:
    PrintNode(Node* node){
        n = node;
    }

    void Execute() {
        cout << n->Eval()->tostring();
    }
private:
    Node* n;
};

struct InputNode : public ExecuteNode {
public:
    InputNode(){

    }
    string strg;

    void Execute() override {
        getline(cin, strg);
    }

    Node* getCin() {
        getline(cin, strg);
        Node* res = new NumberNode(strg);
        return res;
    }
};

struct CreateVar : public ExecuteNode {
    std::string varname;
    DataTypes* datat;

    CreateVar(string name, DataTypes* d){
        datat = d;
        varname = name;
    }

    void Execute() override {
        vars[varname] = datat;
    }
};

struct InputVar : public ExecuteNode {
    std::string varname;
    DataTypes* datat;

    InputVar(string name){
        varname = name;
    }

    void Execute() override {
        InputNode* n = new InputNode();
        datat = n->getCin()->Eval();
        vars[varname] = datat;
    }
};

struct ConditionOperatorStatement : public ExecuteNode
{
public:
    Node* node;
    ExecuteNode* exeif;
    ExecuteNode* exeelse;

    ConditionOperatorStatement(Node* node, ExecuteNode* exeif, ExecuteNode* exeelse){
        this->node = node;
        this->exeif = exeif;
        this->exeelse = exeelse;
    }


    void Execute() override {
        double check = node->Eval()->ld();
        if(check != 0){
            exeif->Execute();
        }
        else if (exeelse != nullptr){
            exeelse->Execute();
        }
    }
};
