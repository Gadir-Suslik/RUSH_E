#include "Lexer.hpp"
#include "Parser.hpp"
#include "AST/ExecuteNode.hpp"
#include "AST/Node.hpp"
#include <iostream>
#include <sstream>
#include <fstream>
using namespace std;



int main(int argc, char* argv[]) {
    if (argc != 2){
        cerr << "Incorrect Usage!\nrush <filename.e>\n";
        system("pause");
        exit(EXIT_FAILURE);
    }
    stringstream fileContents;
    {
        fstream code(argv[1], ios::in);
        if (!code) {
            cerr << "No .e file here!" << endl;
            exit(EXIT_FAILURE);
        }
        fileContents << code.rdbuf();
    }


    vector<string> lines;
    string line;

    while (getline(fileContents, line, ';'))
    {
        lines.push_back(line);
    }
    
    for (string line : lines){
        Lexer l(line);
        vector<Token> LexerResult = l.Tokenize();
        vector<ExecuteNode*> ast = Parser(LexerResult).BuildAST();
        for (ExecuteNode* node : ast){
            node->Execute();
        }
    }
    exit(EXIT_SUCCESS);
}
