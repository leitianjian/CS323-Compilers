#include "ICG.h"

using namespace Compiler;

/**
 * Instruction section
*/
Instruction::Instruction()
{}

Instruction::~Instruction()
{}

Instruction::Instruction(const std::string &instruction):
    m_instruction ( instruction )
{}

/**
 * Variable section
*/
V::V()
{}

V::~V()
{}

V::V(int count):
    m_isTemp ( 0 ),
    m_count ( count ),
    m_name ( "v" + std::to_string(count) )
{}

V::V(int count, int is_temp):
    m_isTemp ( is_temp ),
    m_count ( count ),
    m_name ( ((is_temp) ? "t" : "v") + std::to_string(count) )
{}

/**
 * Label section
*/
Label::Label()
{}

Label::~Label()
{}

Label::Label(int count):
    m_count ( count ),
    m_labelName ( "lb_" + std::to_string(count) )
{}

/**
 * Intermediate code generator
*/
ICG::ICG()
{}

ICG::~ICG()
{}

V ICG::new_variable()
{
    return V(v_count++);
}

V ICG::new_variable(int count)
{
    return V(count);
}

V ICG::new_temp_variable()
{
    return V(t_count++, 1);
}

Label ICG::new_label()
{
    return Label(label_count++);
}

void ICG::appendCode(Instruction &ins)
{
    m_genCodes.push_back(ins);
}

void ICG::appendCode(const std::string &ins)
{
    m_genCodes.push_back(Instruction(ins));
}

void ICG::register_variable(const std::string &name, int v_n)
{
    std::cout << "trying to insert key=" << name << " to symbol table" << std::endl;
    m_variable_dict.insert_or_assign(name, v_n);
    return;
}

void ICG::translate_Program(ASTNode *program)
{
    std::cout << "visit program node" << std::endl;
    ASTNode *extDefList = program->m_child;
    translate_ExtDefList(extDefList);
    return;
}

void ICG::translate_ExtDefList(ASTNode *extDefList)
{
    std::cout << "visit extDefList node" << std::endl;
    if (extDefList->m_childCount == 2) {
        ASTNode *extDef = extDefList->m_child;
        ASTNode *c_extDefList = extDefList->m_child->m_sibling;

        translate_ExtDef(extDef);
        translate_ExtDefList(c_extDefList);
        return;  
    }
}

// struct related
void ICG::translate_ExtDef(ASTNode *extDef)
{
    std::cout << "visit extDef node" << std::endl;
    // Specifier SEMI 
    if (extDef->m_childCount == 2) {
        translate_Specifier(extDef->m_child);
        return;
    }

    if (extDef->m_childCount == 3) {
        // Specifier FunDec CompSt
        if (extDef->m_child->m_type.compare("Specifier") == 0 && 
            extDef->m_child->m_sibling->m_type.compare("FunDec") == 0 &&
            extDef->m_child->m_sibling->m_sibling->m_type.compare("CompSt") == 0)
        {
            ASTNode *specifier = extDef->m_child;
            ASTNode *funDec = extDef->m_child->m_sibling;
            ASTNode *compSt = extDef->m_child->m_sibling->m_sibling;

            translate_Specifier(specifier);
            translate_FuncDec(funDec);
            translate_CompSt(compSt);
            return;
        }

        // Specifier ExtDecList SEMI: variable declare.
        if (extDef->m_child->m_type.compare("Specifier") == 0 && 
            extDef->m_child->m_sibling->m_type.compare("ExtDecList") == 0 &&
            extDef->m_child->m_sibling->m_sibling->m_type.compare("SEMI") == 0)
        {
            ASTNode *specifier = extDef->m_child;
            ASTNode *extDecList = extDef->m_child->m_sibling;

            translate_Specifier(specifier);
            translate_ExtDecList(extDecList);
            return;
        }
    }
}

void ICG::translate_ExtDecList(ASTNode *extDecList) 
{
    std::cout << "visit extDecList node" << std::endl;
    if (extDecList->m_childCount == 1) {
        ASTNode *varDec = extDecList->m_child;

        V v = new_variable();
        translate_VarDec(varDec, v);
        return;
    }

    if (extDecList->m_childCount == 3) {
        ASTNode *varDec = extDecList->m_child;
        ASTNode *c_extDecList = extDecList->m_child->m_sibling->m_sibling;

        V v = new_variable();
        translate_VarDec(varDec, v);
        translate_ExtDecList(c_extDecList);
        return;
    }
}

// structure related
void ICG::translate_Specifier(ASTNode *specifier)
{
    std::cout << "visit specifier node" << std::endl;
    return;
}

void ICG::translate_StructSpecifier(ASTNode *structSpecifier)
{
    std::cout << "visit structSpecifier node" << std::endl;
    return;
}

// array related
void ICG::translate_VarDec(ASTNode *varDec, const V &place)
{
    std::cout << "visit varDec node" << std::endl;

    if (varDec->m_childCount == 1) {
        this->register_variable(varDec->m_child->m_value, place.m_count);
        return;
    }

    if (varDec->m_childCount == 4) {
        return;
    }
}

void ICG::translate_FuncDec(ASTNode *funcDec)
{
    std::cout << "visit funcDec node" << std::endl;
    if (funcDec->m_childCount == 3) {
        appendCode("FUNCTION " + funcDec->m_child->m_value + " :");
        return;
    }

    if (funcDec->m_childCount == 4) {
        appendCode("FUNCTION " + funcDec->m_child->m_value + " :");
        std::vector<V> vl = translate_VarList(funcDec->m_child->m_sibling->m_sibling);
        
        // std::vector<V>::reverse_iterator iter = vl.rbegin();
        // for (; iter != vl.rend(); ++iter)
        std::vector<V>::iterator iter = vl.begin();
        for (; iter != vl.end(); ++iter)
        {
            appendCode("PARAM " + iter->m_name);
        }
        return;
    }
}

std::vector<V> ICG::translate_VarList(ASTNode *varList)
{
    std::cout << "visit varList node" << std::endl;
    if (varList->m_childCount == 3) {
        ASTNode *paramDec = varList->m_child;
        ASTNode *c_varList = varList->m_child->m_sibling->m_sibling;

        V v = translate_ParamDec(paramDec);
        std::vector<V> vl = translate_VarList(c_varList);
        vl.push_back(v);
        return vl;
    }

    if (varList->m_childCount == 1) {
        ASTNode *paramDec = varList->m_child;

        V v = translate_ParamDec(paramDec);
        return std::vector<V>(1, v);
    }
}

V ICG::translate_ParamDec(ASTNode *paramDec)
{
    std::cout << "visit pavramDec node" << std::endl;
    if (paramDec->m_childCount == 2) {
        ASTNode *specifier = paramDec->m_child;
        ASTNode *varDec = paramDec->m_child->m_sibling;

        V v = new_variable();
        translate_Specifier(specifier);
        translate_VarDec(varDec, v);
        return v;
    }
}

void ICG::translate_CompSt(ASTNode *compSt)
{
    std::cout << "visit compSt node" << std::endl;
    if (compSt->m_childCount == 4) {
        ASTNode *defList = compSt->m_child->m_sibling;
        ASTNode *stmtList = compSt->m_child->m_sibling->m_sibling;

        translate_DefList(defList);
        translate_StmtList(stmtList);
        return;
    }
}

void ICG::translate_StmtList(ASTNode *stmtList)
{
    std::cout << "visit stmtList node" << std::endl;
    if (stmtList->m_childCount == 2) {
        ASTNode *stmt = stmtList->m_child;
        ASTNode *c_stmtList = stmtList->m_child->m_sibling;

        translate_Stmt(stmt);
        translate_StmtList(c_stmtList);
        return;
    }
}

void ICG::translate_Stmt(ASTNode *stmt)
{
    std::cout << "translate stmt visitor on " << stmt->m_type <<std::endl;
    // CompSt
    if (stmt->m_childCount == 1) {
        ASTNode *compSt = stmt->m_child;
        translate_CompSt(compSt);
        return;
    }

    // Exp Semi
    if (stmt->m_childCount == 2) {
        ASTNode *exp = stmt->m_child;
        V t = new_temp_variable();
        translate_Exp(exp, t);
        return;
    }

    // RETURN Exp SEMI
    if (stmt->m_childCount == 3) {
        ASTNode *exp = stmt->m_child->m_sibling;
        V t = new_temp_variable();
        translate_Exp(exp, t);
        appendCode("RETURN " + t.m_name);
    }

    if (stmt->m_childCount == 5) {
        // WHILE LP Exp RP Stmt
        if (stmt->m_child->m_type.compare("WHILE") == 0) {
            ASTNode *exp = stmt->m_child->m_sibling->m_sibling;
            ASTNode *c_stmt = stmt->m_child->m_sibling->m_sibling->m_sibling->m_sibling;

            Label lb1 = new_label();
            Label lb2 = new_label();
            Label lb3 = new_label();
            appendCode("LABEL " + lb1.m_labelName + " :");
            translate_cond_Exp(exp, lb2, lb3);
            appendCode("LABEL " + lb2.m_labelName + " :");
            translate_Stmt(c_stmt);
            appendCode("GOTO " + lb1.m_labelName);
            appendCode("LABEL " + lb3.m_labelName + " :");
            return;
        }

        // IF LP Exp RP Stmt
        if (stmt->m_child->m_type.compare("IF") == 0) {
            ASTNode *exp = stmt->m_child->m_sibling->m_sibling;
            ASTNode *c_stmt = stmt->m_child->m_sibling->m_sibling->m_sibling->m_sibling;

            Label lb1 = new_label();
            Label lb2 = new_label();
            translate_cond_Exp(exp, lb1, lb2);
            appendCode("LABEL " + lb1.m_labelName + " :");
            translate_Stmt(c_stmt);
            appendCode("LABEL " + lb2.m_labelName + " :");
            return;
        }
    }

    // IF LP Exp RP Stmt ELSE Stmt
    if (stmt->m_childCount == 7) {
        ASTNode *exp = stmt->m_child->m_sibling->m_sibling;
        ASTNode *stmt1 = stmt->m_child->m_sibling->m_sibling->m_sibling->m_sibling;
        ASTNode *stmt2 = stmt->m_child->m_sibling->m_sibling->m_sibling->m_sibling->m_sibling->m_sibling;

        Label lb1 = new_label();
        Label lb2 = new_label();
        Label lb3 = new_label();

        translate_cond_Exp(exp, lb1, lb2);
        appendCode("LABEL " + lb1.m_labelName + " :");
        translate_Stmt(stmt1);
        appendCode("GOTO " + lb3.m_labelName);
        appendCode("LABEL " + lb2.m_labelName + " :");
        translate_Stmt(stmt2);
        appendCode("LABEL " + lb3.m_labelName + " :");
        return;
    }
}

void ICG::translate_DefList(ASTNode *defList)
{
    std::cout << "visit defList node" << std::endl;
    if (defList->m_childCount == 2) {
        ASTNode *def = defList->m_child;
        ASTNode *c_defList = defList->m_child->m_sibling;

        translate_Def(def);
        translate_DefList(c_defList);
        return;
    }

    if (defList->m_childCount == 0) {
        return;
    }
}

void ICG::translate_Def(ASTNode *def)
{
    std::cout << "visit def node" << std::endl;
    if (def->m_childCount == 3) {
        ASTNode *specifier = def->m_child;
        ASTNode *decList = def->m_child->m_sibling;

        translate_Specifier(specifier);
        translate_DecList(decList);
        return;
    }
}

void ICG::translate_DecList(ASTNode *decList)
{
    std::cout << "visit decList node" << std::endl;
    if (decList->m_childCount == 3) {
        ASTNode *dec = decList->m_child;
        ASTNode *c_decList = decList->m_child->m_sibling->m_sibling;

        translate_Dec(dec);
        translate_DecList(c_decList);
        return;
    }

    if (decList->m_childCount == 1) {
        ASTNode *dec = decList->m_child;

        translate_Dec(dec);
        return;
    }
}

void ICG::translate_Dec(ASTNode *dec)
{
    std::cout << "visit dec node" << std::endl;
    // VarDec ASSIGN Exp
    if (dec->m_childCount == 3) {
        ASTNode *varDec = dec->m_child;
        ASTNode *exp = dec->m_child->m_sibling->m_sibling;

        V v = new_variable();
        translate_VarDec(varDec, v);
        // V t = new_temp_variable();
        translate_Exp(exp, v);
        
        return;
    }
    // VarDec
    if (dec->m_childCount == 1) {
        ASTNode *varDec = dec->m_child;

        V v = new_variable();
        translate_VarDec(varDec, v);
        return;
    }
}

std::string ICG::get_variable_from_dict(const std::string &v_name)
{
    auto ele = m_variable_dict.find(v_name);
    if (ele != m_variable_dict.end()){
        return "v" + std::to_string(ele->second);
    } else {
        std::cout << "translator not find variable in dictionary, error!" << std::endl;
    }
}

std::vector<V> ICG::translate_Args(ASTNode *args)
{
    std::cout << "visit args node" << std::endl;
    // Exp
    if (args->m_childCount == 1) {
        ASTNode *exp = args->m_child;
        V t1 = new_temp_variable();
        translate_Exp(exp, t1);
        return std::vector<V>(1, t1);
    }

    // Exp COMMA Args
    if (args->m_childCount == 3) {
        ASTNode *exp = args->m_child;
        ASTNode *a = args->m_child->m_sibling->m_sibling;

        V t1 = new_temp_variable();
        translate_Exp(exp, t1);
        std::vector<V> vec = translate_Args(a);
        vec.push_back(t1); // 与args exp是反着的
        return vec;
    }
}

void ICG::translate_cond_Exp(ASTNode *exp, Label lb_true, Label lb_false)
{
    std::cout << "translate cond exp " << exp->m_childCount << exp->m_type << std::endl;
    if (exp->m_childCount == 2) {
        // Not exp
        if (exp->m_child->m_type.compare("NOT") == 0 && 
            exp->m_child->m_sibling->m_type.compare("Exp") == 0)
        {
            translate_cond_Exp(exp, lb_false, lb_true);
            return;
        }
    }

    if (exp->m_childCount == 3) {
        // Exp AND exp
        if (exp->m_child->m_type.compare("Exp") == 0 && 
            exp->m_child->m_sibling->m_type.compare("AND") == 0 &&
            exp->m_child->m_sibling->m_sibling->m_type.compare("Exp") == 0)
        {
            ASTNode *exp1 = exp->m_child;
            ASTNode *exp2 = exp->m_child->m_sibling->m_sibling;
            Label lb1 = new_label();
            translate_cond_Exp(exp1, lb1, lb_false);
            appendCode("LABEL " + lb1.m_labelName + " :");
            translate_cond_Exp(exp2, lb_true, lb_false);
            return;
        }
        // Exp OR Exp
        if (exp->m_child->m_type.compare("Exp") == 0 && 
            exp->m_child->m_sibling->m_type.compare("OR") == 0 &&
            exp->m_child->m_sibling->m_sibling->m_type.compare("Exp") == 0)
        {
            ASTNode *exp1 = exp->m_child;
            ASTNode *exp2 = exp->m_child->m_sibling->m_sibling;
            Label lb1 = new_label();
            translate_cond_Exp(exp1, lb_true, lb1);
            appendCode("LABEL " + lb1.m_labelName + " :");
            translate_cond_Exp(exp2, lb_true, lb_false);
            return;
        }

        // Exp LT Exp
        if (exp->m_child->m_type.compare("Exp") == 0 && 
            std::string("LT LE GT GE NE EQ").find(exp->m_child->m_sibling->m_type) != -1 &&
            exp->m_child->m_sibling->m_sibling->m_type.compare("Exp") == 0)
        {
            ASTNode *exp1 = exp->m_child;
            ASTNode *exp2 = exp->m_child->m_sibling->m_sibling;
            std::string op = translate_token(exp->m_child->m_sibling->m_type);
            V t1 = new_temp_variable();
            V t2 = new_temp_variable();

            translate_Exp(exp1, t1);
            translate_Exp(exp2, t2);
            appendCode("IF " + t1.m_name + " " + op + " " + t2.m_name + " GOTO " + lb_true.m_labelName);
            appendCode("GOTO " + lb_false.m_labelName);
            return;
        }

        // LP Exp RP
        if (exp->m_child->m_type.compare("LP") == 0 && 
            exp->m_child->m_sibling->m_type.compare("Exp") == 0 &&
            exp->m_child->m_sibling->m_sibling->m_type.compare("RP") == 0)
        {
            ASTNode *exp = exp->m_child->m_sibling;
            translate_cond_Exp(exp, lb_true, lb_false);
            return;
        }
        
    }
}

int ICG::judge_condition_exp(ASTNode *exp)
{
    if (exp->m_childCount == 2) {
        if (exp->m_child->m_type.compare("NOT") == 0 && 
            exp->m_child->m_sibling->m_type.compare("Exp") == 0)
        {
            return 1;
        }
    }

    if (exp->m_childCount == 3) {
        if (exp->m_child->m_type.compare("Exp") == 0 && 
            exp->m_child->m_sibling->m_type.compare("AND") == 0 &&
            exp->m_child->m_sibling->m_sibling->m_type.compare("Exp") == 0)
        {
            return 1;
        }

        if (exp->m_child->m_type.compare("Exp") == 0 && 
            exp->m_child->m_sibling->m_type.compare("OR") == 0 &&
            exp->m_child->m_sibling->m_sibling->m_type.compare("Exp") == 0)
        {
            return 1;
        }

        if (exp->m_child->m_type.compare("Exp") == 0 && 
            std::string("LT LE GT GE NE EQ").find(exp->m_child->m_sibling->m_type) != -1 &&
            exp->m_child->m_sibling->m_sibling->m_type.compare("Exp") == 0)
        {
            return 1;
        }
    }
    return 0;
}

void ICG::translate_Exp(ASTNode *exp, const V &place)
{
    std::cout << "visit exp node" << std::endl;
    if (exp->m_childCount == 1) {
        if (exp->m_child->m_type.compare("INT") == 0)
        {
            int value = std::stoi(exp->m_child->m_value);
            appendCode(place.m_name + " := #" + exp->m_child->m_value);
            return;
        }

        if (exp->m_child->m_type.compare("ID") == 0) // 这个时候对应表中应该一定能查到，因为前面有declare
        {
            std::string v_name = exp->m_child->m_value;
            appendCode(place.m_name + " := " + get_variable_from_dict(v_name));
            return;
        }
    }

    if (exp->m_childCount == 2) {
        if (exp->m_child->m_type.compare("MINUS") == 0 && 
            exp->m_child->m_sibling->m_type.compare("Exp") == 0)
        {
            ASTNode *c_exp = exp->m_child->m_sibling;
            V t = new_temp_variable();
            translate_Exp(c_exp, t);
            appendCode(place.m_name + " := #0 - " + t.m_name);
            return;
        }
    }

    if (exp->m_childCount == 3) {
        // Exp ASSIGN Exp
        if (exp->m_child->m_type.compare("Exp") == 0 && 
            exp->m_child->m_sibling->m_type.compare("ASSIGN") == 0 &&
            exp->m_child->m_sibling->m_sibling->m_type.compare("Exp") == 0)
        {
            // 只考虑了变量
            ASTNode *exp_l = exp->m_child;
            ASTNode *exp_r = exp->m_child->m_sibling->m_sibling;

            if (exp_l->m_childCount == 1 &&
                exp_l->m_child->m_type == "ID")
            {
                std::string name = exp_l->m_child->m_value;
                V v = new_variable(m_variable_dict[name]);
                translate_Exp(exp_r, v);
                appendCode(place.m_name + " := " + v.m_name);
                return;
            }
        }

        // Exp MINUS Exp (PLUS MUL DIV)
        if (exp->m_child->m_type.compare("Exp") == 0 && 
            std::string("PLUS MINUS MUL DIV").find(exp->m_child->m_sibling->m_type) != -1 &&
            exp->m_child->m_sibling->m_sibling->m_type.compare("Exp") == 0)
        {
            ASTNode *exp_l = exp->m_child;
            ASTNode *exp_r = exp->m_child->m_sibling->m_sibling;
            V t1 = new_temp_variable();
            V t2 = new_temp_variable();
            translate_Exp(exp_l, t1);
            translate_Exp(exp_r, t2);
            appendCode(place.m_name + " := " + 
                       t1.m_name + " " +
                       translate_token(exp->m_child->m_sibling->m_type) + 
                       " " +
                       t2.m_name);
            return;
        }

        // LP Exp RP
        if (exp->m_child->m_type.compare("LP") == 0 && 
            exp->m_child->m_sibling->m_type.compare("Exp") == 0 &&
            exp->m_child->m_sibling->m_sibling->m_type.compare("RP") == 0)
        {
            ASTNode *c_exp = exp->m_child->m_sibling;
            translate_Exp(c_exp, place);
            return;
        }

        // ID LP RP
        if (exp->m_child->m_type.compare("ID") == 0 && 
            exp->m_child->m_sibling->m_type.compare("LP") == 0 &&
            exp->m_child->m_sibling->m_sibling->m_type.compare("RP") == 0)
        {
            // READ function
            if (exp->m_child->m_value.compare("read") == 0) {
                appendCode("READ " + place.m_name);
            } else {
                appendCode(place.m_name + " := CALL " + exp->m_child->m_value);
            }
        }
    }

    if (exp->m_childCount == 4) {
        // ID LP RP
        if (exp->m_child->m_type.compare("ID") == 0 && 
            exp->m_child->m_sibling->m_type.compare("LP") == 0 &&
            exp->m_child->m_sibling->m_sibling->m_type.compare("Args") == 0 &&
            exp->m_child->m_sibling->m_sibling->m_sibling->m_type.compare("RP") == 0)
        {
            ASTNode *args = exp->m_child->m_sibling->m_sibling;
            // write function
            if (exp->m_child->m_value.compare("write") == 0) {
                V t1 = new_temp_variable();
                translate_Exp(args->m_child, t1);
                appendCode("WRITE " + t1.m_name);
            } else {
                std::vector<V> arg_list = translate_Args(args);
                int len = arg_list.size();
                for (int i = len - 1; i >= 0; -- i) {
                    appendCode("ARG " + arg_list[i].m_name);
                }
                appendCode(place.m_name + " := CALL " + exp->m_child->m_value);
            }
        }
    }

    // cond. Exp
    if (judge_condition_exp(exp)){
        Label lb1 = new_label();
        Label lb2 = new_label();
        appendCode(place.m_name + " := #0");
        translate_cond_Exp(exp, lb1, lb2);
        appendCode("LABEL " + lb1.m_labelName + " :");
        appendCode(place.m_name + " := #1");
        appendCode("LABEL" + lb2.m_labelName + " :");
    }

}

std::string ICG::translate_token(std::string token)
{
    if (token == "LT")
        return "<";
    else if (token == "LE")
        return "<=";
    else if (token == "GT")
        return ">";
    else if (token == "GE")
        return ">=";
    else if (token == "NE")
        return "!=";
    else if (token == "EQ")
        return "==";
    else if (token == "PLUS")
        return "+";
    else if (token == "MUL")
        return "*";
    else if (token == "DIV")
        return "/";
    else if (token == "MINUS")
        return "-";
}