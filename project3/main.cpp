#include <iostream>
#include <fstream>
#include <sstream>
#include "scanner.h"
#include "parser.hpp"
#include "interpreter.h"
#include "SematicAnalyzer.h"
#include "ICG.h"

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
        std::stringstream intermediate_code;
        if (interpreter.errorFlag() == 1) {
            res = interpreter.errorMsg();
        } else {
            res = interpreter.str();
            std::cout << res;
            // SematicAnalyzer sa;
            // sa.visit(interpreter.m_rootNode);
            ICG codeGenerator = ICG();
            codeGenerator.translate_Program(interpreter.m_rootNode);

            for (Instruction s: codeGenerator.m_genCodes){
                intermediate_code << s.m_instruction << std::endl;
                std::cout << s.m_instruction << std::endl;
            }
        }
        // std::string output1 = input.replace(input.find(".spl"), 5, ".out1");
        // ofstream onf;
        // onf.open(output1);
        // onf << res;
        // std::cout << input << std::endl;
        std::string output2 = input.replace(input.find(".spl"), 5, ".ir");
        ofstream onf1;
        onf1.open(output2);
        onf1 << intermediate_code.str();
        sematicErrorMsg = "";
        currentScope = new SymTab(0);
    }
    
    return 0;
}