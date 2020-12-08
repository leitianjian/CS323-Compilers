#ifndef SEMATICANALYZER_H
#define SEMATICANALYZER_H
#include <vector>
#include <variant>
#include "ASTNode.h"
#include "NodeVisitor.h"
#include "SymTab.h"

namespace Compiler {

class SematicAnalyzer
{
public:
    void visit(ASTNode *root);
};

}
#endif