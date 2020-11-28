#ifndef NODEVISITOR_H
#define NODEVISITOR_H

#include <vector>
#include <variant>
#include <string>
#include <sstream>
#include <iostream>
#include "ASTNode.h"
#include "SymTab.h"

namespace Compiler {

extern SymTab *currentScope;
extern std::string sematicErrorMsg;
// extern int sematicErrorFlag;
// extern std::string sematicWarningMsg;

class NodeVisitor;
class ProgramVisitor;
class ExtDefListVisitor;
class ExtDefVisitor;
class ExtDecListVisitor;
class SpecifierVisitor;
class StructSpecifierVisitor;
class VarDecVisitor;
class FuncDecVisitor; 
class VarListVisitor;
class ParamDecVisitor;
class StmtVisitor;
class CompStVisitor;
class StmtVisitor; 
class DefListVisitor;
class DefVisitor;
class DecListVisitor;
class DecVisitor;
class ExpVisitor;
class ArgsVisitor;

class NodeVisitor
{
public:
    virtual ~NodeVisitor();
    virtual void visit(ASTNode *node);
    void appendErrorMsg(int errTypeno, int lineno, std::string msg);
};

class IntVisitor: public NodeVisitor
{
public:
    int value;

    IntVisitor();
    ~IntVisitor();
    void visit (ASTNode *IntegerNode);
};

class ProgramVisitor: public NodeVisitor
{
public:
    ProgramVisitor();
    ~ProgramVisitor();
    void visit (ASTNode *node);
};

class ExtDefListVisitor: public NodeVisitor
{
public:
    ExtDefListVisitor();
    ~ExtDefListVisitor();
    void visit (ASTNode *node);
};

class ExtDefVisitor: public NodeVisitor
{
public:
    ExtDefVisitor();
    ~ExtDefVisitor();
    void visit (ASTNode *node);
};

class ExtDecListVisitor: public NodeVisitor
{
public:
    std::vector<std::string> m_names;
    std::vector<Variable> m_vars;
    
    ExtDecListVisitor();
    ~ExtDecListVisitor();
    void visit (ASTNode *node);
};

class SpecifierVisitor: public NodeVisitor
{
public:
    DataType::Type m_type;

    // only avail when m_type is structure
    std::string m_name;
    int m_isDefine;


    SpecifierVisitor();
    ~SpecifierVisitor();
    void visit (ASTNode *node);
};

class StructSpecifierVisitor: public NodeVisitor
{
public:
    std::string m_name;
    int m_isDefine; // 0: no  1: yes  -1: unknow

    StructSpecifierVisitor();
    ~StructSpecifierVisitor();
    void visit (ASTNode *node);
};

// class FuncExpVisitor: public NodeVisitor
// {
// public:
//     std::string funcName;
//     std::vector<Variable> args;

//     void visit (ASTNode *node);
// };

// class BinaryOpVisitor: public NodeVisitor
// {
// public:
//     DataType leftType;
//     DataType rightType;
//     std::string operand;
//     DataType resType;

//     BinaryOpVisitor();
//     ~BinaryOpVisitor();
//     void visit (ASTNode *node);
// };


class VarDecVisitor : public NodeVisitor
{
public:
    std::string m_name;
    int m_dimension;
    std::vector<int> m_size;

    VarDecVisitor();
    ~VarDecVisitor();
    void visit (ASTNode *node);
    Variable toVariable ();
};

class FuncDecVisitor : public NodeVisitor
{
public:
    std::string m_funcName;
    std::vector<std::string> m_paramNames;
    std::vector<Variable> m_params;

    FuncDecVisitor();
    ~FuncDecVisitor();
    void visit (ASTNode *node);
};

class VarListVisitor: public NodeVisitor
{
public:
    std::vector<std::string> m_names;
    std::vector<Variable> m_params;

    VarListVisitor();
    ~VarListVisitor();
    void visit (ASTNode *node);
};

class ParamDecVisitor: public NodeVisitor
{
public:
    // Type varType;
    // std::string m_name;
    // int m_dimension;
    // std::vector<int> m_size;
    std::string m_name;
    Variable m_param;

    ParamDecVisitor();
    ~ParamDecVisitor();
    void visit (ASTNode *node);
};

class CompStVisitor: public NodeVisitor
{
public:
    CompStVisitor();
    ~CompStVisitor();
    void visit (ASTNode *node);
};

class StmtListVisitor: public NodeVisitor
{
public:
    StmtListVisitor();
    ~StmtListVisitor();
    void visit (ASTNode *node);
};

class StmtVisitor: public NodeVisitor
{
public:
    StmtVisitor();
    ~StmtVisitor();
    void visit (ASTNode *node);
};

class DefListVisitor: public NodeVisitor
{
public:
    std::vector<std::string> m_names;
    std::vector<Variable> m_def;

    DefListVisitor();
    ~DefListVisitor();
    void visit (ASTNode *node);
};

class DefVisitor: public NodeVisitor
{
public:
    std::vector<std::string> m_names;
    std::vector<Variable> m_def;

    DefVisitor();
    ~DefVisitor();
    void visit (ASTNode *node);
};

class DecListVisitor: public NodeVisitor
{
public:
    std::vector<DecVisitor> m_decList; // 如果有初试化赋值，需要在这里保存rvalue，去和DefList中的Specifer的type校验

    DecListVisitor();
    ~DecListVisitor();
    void visit (ASTNode *node);
};

class ExpVisitor: public NodeVisitor
{
public:
    int m_isRvalue; // rvalue: INT CHAR FLOAT (Exp op Exp)
    DataType::Type m_retType;
    VAL_T *m_expValue;

    ExpVisitor();
    ~ExpVisitor();
    void visit (ASTNode *node);
    int compare (ExpVisitor &visitor);
};

class DecVisitor: public NodeVisitor
{
public:
    int m_initialized;
    VarDecVisitor m_varDec;
    ExpVisitor m_rvalue;
    // std::vector<Variable> decList; // 如果有初试化赋值，需要在这里保存rvalue，去和DefList中的Specifer的type校验

    DecVisitor();
    ~DecVisitor();
    void visit (ASTNode *node);
};

class ArgsVisitor: public NodeVisitor
{
public:
    std::vector<DataType::Type> m_argsType;

    ArgsVisitor();
    ~ArgsVisitor();
    void visit (ASTNode *node);
};
}
#endif