#include<string>
#include<iostream>
#include<cstring>
#include<cstdarg>
#include<fstream>
#include<vector>

class AST 
{
public:
    int line_no;

    AST(int line_no){
        this->line_no = line_no;
    }
};

class IntVariable: public AST
{
public:
    std::string token;
    int value;

    IntVariable(std::string token, int value, int line_no):
        AST { line_no }, 
        token ( token ),
        value ( value ) {}
};

class FloatVariable: public AST
{
public:
    std::string token;
    double value;

    FloatVariable(std::string token, double value, int line_no):
        AST { line_no }, 
        token ( token ),
        value ( value ) {}
};

class BinaryExp: public AST
{
public:
    AST left;
    std::string op; // operator
    AST right;

    BinaryExp(const AST &left, std::string op, const AST &right):
        AST { line_no },
        left ( left ),
        op ( op ),
        right ( right ) {}
};

class VariableDec: public AST
{
public:
    AST var_node;
    AST type_node;

    VariableDec(const AST &var_node, const AST &type_node):
        AST { line_no },
        var_node ( var_node ),
        type_node ( type_node ) {}
};

//DecList?

class Block: public AST
{
public:
    std::vector<AST> dec_list;
    std::vector<AST> stmt_list;

    Block(const std::vector<AST> &dec_list, const std::vector<AST> &stmt_list, int line_no):
        AST {line_no},
        dec_list ( dec_list ),
        stmt_list ( stmt_list ) {}
};

class Param: public AST
{
public:
    AST VarNode;
    AST TypeNode;

    Param(const AST &VarNode, const AST &TypeNode):
        AST { line_no },
        VarNode ( VarNode ),
        TypeNode ( TypeNode ) {}
};

class FunctionDec: public AST
{
public:
    AST ret_type;
    std::string func_name;
    std::vector<AST> params;
    AST block;

    FunctionDec(const AST &ret_type, 
                             const std::string &func_name, 
                             const std::vector<AST> &params, 
                             const AST &block, int line_no): 
        AST { line_no },
        ret_type ( ret_type ),
        func_name ( func_name ),
        params ( params ),
        block ( block ) {}
};

class Struct: public AST
{
public:
    std::string name;
    AST dec_block;

    Struct(const std::string &name, const AST &dec_block, int line_no):
        AST { line_no },
        name ( name ),
        dec_block ( dec_block ) {}
};