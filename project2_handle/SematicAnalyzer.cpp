#include "SematicAnalyzer.h"

using namespace Compiler;

void SematicAnalyzer::visit(ASTNode *root){
    ProgramVisitor pv;
    pv.visit(root);
    return;
}