#include <iostream>
#include <fstream>
#include "scanner.h"
#include "parser.hpp"
#include "interpreter.h"
#include "SematicAnalyzer.h"
namespace Compiler {
    SymTab *currentScope = new SymTab(0);
    std::string sematicErrorMsg;
}

using namespace Compiler;

int main(int argc, char **argv) {
    if(argc == 1) {
        std::cerr << "Usage: " << argv[0] << " <file_path>\n" << std::endl;
        exit(-1);
    }
    Interpreter interpreter;
    
    for (int i = 1; i < argc; ++ i) {
        interpreter.clear();
        std::string input(argv[i]);
        ifstream inf;
        inf.open(input);
        interpreter.switchInputStream(&inf);
        interpreter.parse();
        std::string res;
        if (interpreter.errorFlag() == 1) {
            res = interpreter.errorMsg();
        } else {
            res = interpreter.str();
            std::cout << res;
            SematicAnalyzer sa;
            sa.visit(interpreter.m_rootNode);
        }
        std::string output1 = input.replace(input.find(".spl"), 5, ".out1");
        ofstream onf;
        onf.open(output1);
        onf << res;
        // std::cout << input << std::endl;
        std::string output2 = input.replace(input.find(".out1"), 5, ".out2");
        ofstream onf1;
        onf1.open(output2);
        onf1 << sematicErrorMsg;
        sematicErrorMsg = "";
        currentScope = new SymTab(0);
    }
    
    return 0;
    // inf.open("test_1_r05.spl");
    // i.switchInputStream(&inf);
    // int res = i.parse();

    // std::string temp = i.str();
    // if (temp.empty()) {
    //     std::cout << "empty tree" << std::endl;
    // }
    // std::cout << temp << std::endl;
    // std::cout << "Parse complete. Result = " << res << endl;
    // return res;
}