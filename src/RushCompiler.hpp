#include "Lexer.hpp"
#include "Parser.hpp"
#include "AST/ExecuteNode.hpp"
#include <iostream>
#include <sstream>
#include <fstream>
using namespace std;

void RUN(vector<string> lines) {
    for (string line : lines){
        Lexer l(line);
        vector<Token> LexerResult = l.Tokenize();
        vector<ExecuteNode*> ast = Parser(LexerResult).BuildAST();
        for (ExecuteNode* node : ast){
            node->Execute();
        }
    }
}