#ifndef ICG_H
#define ICG_H

#include <vector>
#include <iostream>
#include <unordered_map>
#include "ASTNode.h"

namespace Compiler
{

class Instruction
{
public:
    std::string m_instruction;

    Instruction();
    ~Instruction();
    Instruction(const std::string &instruction);
};

class V
{
public:
    int m_isTemp;
    int m_count;

    std::string m_name;

    V();
    ~V();
    V(int count);
    V(int count, int is_temp);
};

class Label
{
public:
    int m_count;
    std::string m_labelName;

    Label();
    ~Label();
    Label(int count);
};

class ICG
{
public:
    std::vector<Instruction> m_genCodes;
    std::unordered_map<std::string, int> m_variable_dict; // 保存变量名和对应的v number
    int t_count = 0;
    int v_count = 0;
    int label_count = 0;

    ICG();
    ~ICG();
    V new_variable();
    V new_variable(int count);
    V new_temp_variable();
    Label new_label();
    void appendCode(Instruction &instruction);
    void appendCode(const std::string &instruction);
    std::string get_variable_from_dict(const std::string &v_name);
    void register_variable(const std::string &name, int v_n);

    int judge_condition_exp(ASTNode *exp);

    void translate_Program(ASTNode *program);
    void translate_ExtDefList(ASTNode *extDefList);
    void translate_ExtDef(ASTNode *extDef);
    void translate_ExtDecList(ASTNode *extDecList);
    void translate_Specifier(ASTNode *specifier);
    void translate_StructSpecifier(ASTNode *structSpecifier);
    void translate_VarDec(ASTNode *varDec, const V &place); //初试化variable和v的对应
    void translate_FuncDec(ASTNode *funcDec);
    std::vector<V> translate_VarList(ASTNode *varList);
    V translate_ParamDec(ASTNode *paramDec);
    void translate_CompSt(ASTNode *compSt);
    void translate_StmtList(ASTNode *stmtList);
    void translate_Stmt(ASTNode *stmt);
    void translate_DefList(ASTNode *defList);
    void translate_Def(ASTNode *def);
    void translate_DecList(ASTNode *decList);
    void translate_Dec(ASTNode *dec);
    void translate_Exp(ASTNode *exp, const V &place);
    void translate_cond_Exp(ASTNode *exp, Label lb_true, Label lb_false);
    std::vector<V> translate_Args(ASTNode *args);
    std::string translate_token(std::string token);
};

}
#endif