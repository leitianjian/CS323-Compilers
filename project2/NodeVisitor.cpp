#include "NodeVisitor.h"

using namespace Compiler;

NodeVisitor::~NodeVisitor()
{}

void NodeVisitor::visit(ASTNode *node)
{
    std::cout << "OOOPS NodeVisitor's visit method" << std::endl;
}

void NodeVisitor::appendErrorMsg(int errTypeno, int lineno, std::string msg) 
{
    std::stringstream ss;
    ss << "Error type " << errTypeno << " at Line " << lineno << ": " << msg << std::endl;
    sematicErrorMsg.append(ss.str());
}

IntVisitor::IntVisitor()
{}

IntVisitor::~IntVisitor()
{}

void IntVisitor::visit(ASTNode *node)
{
    value = std::stoi(node->m_value);
}

/**
 * Program visitor section
*/

ProgramVisitor::ProgramVisitor()
{}

ProgramVisitor::~ProgramVisitor()
{}

void ProgramVisitor::visit (ASTNode *node) 
{
    if (node->m_childCount == 1) {
        std::cout << "program visitor evoked" << std::endl;
        ASTNode *extDefList = node->m_child;

        ExtDefListVisitor edlv;
        edlv.visit(extDefList);
        return;
    }
}

/**
 * ExtDefList visitor section
*/

ExtDefListVisitor::ExtDefListVisitor()
{}

ExtDefListVisitor::~ExtDefListVisitor()
{}

void ExtDefListVisitor::visit (ASTNode *node) 
{
    // null
    if (node->m_childCount == 0) {
        return;
    }

    // ExtDef ExtDefList
    if (node->m_childCount == 2) {
        ASTNode *extDef = node->m_child;
        ASTNode *extDefList = node->m_child->m_sibling;

        ExtDefVisitor edv;
        ExtDefListVisitor edlv;
        edv.visit(extDef);
        edlv.visit(extDefList);
        return;
    }
}

/**
 * ExtDef visitor section
*/
ExtDefVisitor::ExtDefVisitor()
{}

ExtDefVisitor::~ExtDefVisitor()
{}

void ExtDefVisitor::visit (ASTNode *node)
{
    // Specifier SEMI 
    if (node->m_childCount == 2) {
        SpecifierVisitor sv;
        sv.visit(node->m_child);

        if (sv.m_type != DataType::STRUCTURE) {
            NodeVisitor::appendErrorMsg(15, node->m_row, "invalid define");
            return;
        }

        // STRUCT ID
        if (sv.m_isDefine != 1) {
            VAL_T *value = currentScope->lookup(sv.m_name, 1); // 当前scope没有，就可以重新定义
            // 当前scope有这个name的structure
            if (value != nullptr) { // 如果当前scope有一个同名structure，报错
                NodeVisitor::appendErrorMsg(15, node->m_row, "redefine the same structure type");
                return;
            }
            

            Structure s(sv.m_name, nullptr);
            value = new VAL_T(EntryType::STRUCTURE, s);
            currentScope->insert(sv.m_name, *value);
        }
    }

    if (node->m_childCount == 3) {
        // Specifier FunDec CompSt
        if (node->m_child->m_type.compare("Specifier") == 0 && 
            node->m_child->m_sibling->m_type.compare("FunDec") == 0 &&
            node->m_child->m_sibling->m_sibling->m_type.compare("CompSt") == 0)
        {
            SpecifierVisitor sv;
            FuncDecVisitor fdv;
            CompStVisitor csv;
            sv.visit(node->m_child);
            fdv.visit(node->m_child->m_sibling);
            /**
             * test case:
             * struct a {} hello(){}
             * struct a b; should report: struct a not define and define a structure in return type
             * 
             * struct a;
             * struct a {} hello() {}
             * struct a b; report: struct a not define and define a structure in return type
            */
            if (sv.m_isDefine == 1) {
                NodeVisitor::appendErrorMsg(16, node->m_row, "define a structure in return type");
                // 插入的symbol table元素不合法，要删掉
                currentScope->remove(sv.m_name);
            }

            // register a function at current scope (name, ret, params_type)
            std::string structName = (sv.m_type == DataType::STRUCTURE) ? sv.m_name : "";
            if (currentScope->lookup(fdv.m_funcName, 0) != nullptr) {
                std::string errorMsg = fdv.m_funcName + " function is redefined";
                NodeVisitor::appendErrorMsg(4, node->m_row, errorMsg);
            }
            std::cout << "function name: " << fdv.m_funcName << " type: " << sv.m_type << std::endl;
            currentScope->registerFunction(fdv.m_funcName, sv.m_type, structName, fdv.m_params);
            std::cout << std::get<Function>(currentScope->lookup(fdv.m_funcName, 1)->m_val).m_retType << std::endl;

            // new a scoped symbol table
            SymTab *symTab = new SymTab(fdv.m_funcName, currentScope->m_scope_level + 1);
            std::string retName("ret_");
            symTab->registerFunction(retName, sv.m_type, structName, fdv.m_params);
            std::cout << "trying to register function paramter into symbol table" << std::endl;
            // insert params to the newed symbol table
            symTab->registerVariables(fdv.m_paramNames, fdv.m_params);

            // swith current symTab to new symTab and visit CompSt
            symTab->m_enclosing_scope = currentScope;
            currentScope = symTab;
            csv.visit(node->m_child->m_sibling->m_sibling);

            // // check return whether return type is ok
            // std::string s("return");
            // VAL_T *ret = currentScope->lookup(s, 0);
            // if (ret == nullptr || ret->m_valType != EntryType::VARIABLE) {
            //     NodeVisitor::appendErrorMsg(8, node->m_child->m_row, "the function’s return value type mismatches the declared type");
            //     return;
            // } else {
            //     Variable v = std::get<Variable>(ret->m_val);
            //     if (v.m_type != sv.m_type) {
            //         NodeVisitor::appendErrorMsg(8, node->m_child->m_row, "the function’s return value type mismatches the declared type");
            //         return;
            //     }
            // }
            
            // return to the previous symTab
            currentScope = currentScope->m_enclosing_scope;
            return;
        }

        // Specifier ExtDecList SEMI: variable declare.
        if (node->m_child->m_type.compare("Specifier") == 0 && 
            node->m_child->m_sibling->m_type.compare("ExtDecList") == 0 &&
            node->m_child->m_sibling->m_sibling->m_type.compare("SEMI") == 0)
        {
            ASTNode *specifier = node->m_child;
            ASTNode *extDecList = node->m_child->m_sibling;
            SpecifierVisitor sv;
            ExtDecListVisitor edlv;
            sv.visit(specifier);
            edlv.visit(extDecList);
            
            int varNum = edlv.m_vars.size();
            // check if we have same variable (func struct have preffix)
            // 如果是普通类型的variable：check本作用域内有没有声明过
            // register any variable if no exist in same scope

            // if exist in same scope report error
            for (int i = 0; i < varNum; ++ i) {
                VAL_T *v = currentScope->lookup(edlv.m_names[i], 1);
                // 声明过就报错
                if (v != nullptr) {
                    NodeVisitor::appendErrorMsg(3, extDecList->m_row, "variable is redeﬁned in the same scope");
                    // return;
                }
                // 插入variable （redeclare）
                Variable var = edlv.m_vars[i];
                if (var.m_dimension == 0) {
                    var.m_type = sv.m_type;
                    var.m_eleType = sv.m_type;
                } else {
                    var.m_eleType = sv.m_type;
                }
                var.m_structName = (sv.m_type == DataType::STRUCTURE) ? sv.m_name : "";
                VAL_T value(EntryType::VARIABLE, var);
                currentScope->insert(edlv.m_names[i], value);
            }
            return;
        }
    }
}

/**
 * ExtDecList visitor section
*/
ExtDecListVisitor::ExtDecListVisitor()
{}

ExtDecListVisitor::~ExtDecListVisitor()
{}

void ExtDecListVisitor::visit (ASTNode *node)
{
    VarDecVisitor vdv;
    // VarDec
    if (node->m_childCount == 1) {
        vdv.visit(node->m_child);

        m_names.push_back(vdv.m_name);
        m_vars.push_back(vdv.toVariable());
        return;
    }

    // VarDec COMMA ExtDecList
    if (node->m_childCount == 3) {
        ExtDecListVisitor edlv;
        vdv.visit(node->m_child);
        edlv.visit(node->m_child->m_sibling->m_sibling);

        m_names.push_back(vdv.m_name);
        m_vars.push_back(vdv.toVariable());

        m_names.insert(m_names.end(), edlv.m_names.begin(), edlv.m_names.end());
        m_vars.insert(m_vars.end(), edlv.m_vars.begin(), edlv.m_vars.end());
        return;
    }
}

/**
 * Specifier visitor
*/
SpecifierVisitor::SpecifierVisitor(): 
    m_isDefine ( 0 )
{}

SpecifierVisitor::~SpecifierVisitor()
{}

void SpecifierVisitor::visit (ASTNode *node) 
{
    ASTNode *child = node->m_child;
    if (child->m_type.compare("TYPE") == 0) {
        if (child->m_value.compare("int") == 0) {
            m_type = DataType::INT;
            return;
        }

        if (child->m_value.compare("char") == 0) {
            m_type = DataType::CHAR;
            return;
        }

        if (child->m_value.compare("float") == 0) {
            m_type = DataType::FLOAT;
            return;
        }
    }

    if (child->m_type.compare("StructSpecifier") == 0) {
        StructSpecifierVisitor ssv;
        ssv.visit (child);

        m_type = DataType::STRUCTURE;
        m_name = ssv.m_name;
        m_isDefine = ssv.m_isDefine;
        return;
    }
}

/**
 * Structure Specifier visitor section
*/
StructSpecifierVisitor::StructSpecifierVisitor()
{}

StructSpecifierVisitor::~StructSpecifierVisitor()
{}

void StructSpecifierVisitor::visit (ASTNode *node) 
{
    // // SymTab *symTab = new SymTab(currentScope->m_scope_level + 1);
    // // symTab->m_enclosing_scope = currentScope;
    std::string name = "struct_" + node->m_child->m_sibling->m_value;
    
    // STRUCT ID
    // 有可能是struct声明或者使用，所以要去symbolTable里面查一下
    if (node->m_childCount == 2) {
        m_name = name;
        m_isDefine = -1;
        return;
    }

    // STRUCT ID LC DefList RC
    if (node->m_childCount == 5) {
        VAL_T *value = currentScope->lookup(name, 1); // 当前scope没有，就可以重新定义
        m_name = name;
        m_isDefine = 1;
        // 当前scope有这个name的structure
        if (value != nullptr) { // 如果当前scope有一个同名structure，报错
            NodeVisitor::appendErrorMsg(15, node->m_row, "redefine the same structure type");
            // return;
        }

        ASTNode *defListNode = node->m_child->m_sibling->m_sibling->m_sibling;
        // new define
        SymTab *symTab = new SymTab(name, currentScope->m_scope_level + 1);
        symTab->m_enclosing_scope = currentScope;

        Structure s(name, symTab);
        value = new VAL_T(EntryType::STRUCTURE, s);
        currentScope->insert(name, *value);
        currentScope = symTab;

        // 把新的def加入symboltable
        DefListVisitor defListVisitor;
        defListVisitor.visit(defListNode);

        // 重新跳回来
        currentScope = currentScope->m_enclosing_scope;
        return;
    }
}

/**
 * VarDec visitor section
*/
VarDecVisitor::VarDecVisitor()
{}

VarDecVisitor::~VarDecVisitor()
{}

void VarDecVisitor::visit(ASTNode *node)
{
    // ID UNKNOW
    if (node->m_childCount == 1) {  
        // std::cout << "find variable dec with name: " << node->m_value << " type: " << node->m_type << std::endl;
        m_name = node->m_child->m_value;
        m_dimension = 0;
        return;
    }

    // VarDec LB INT RB
    if (node->m_childCount == 4) {
        VarDecVisitor varDecVisitor;
        varDecVisitor.visit(node->m_child);

        IntVisitor intVisitor;
        intVisitor.visit(node->m_child->m_sibling->m_sibling);

        m_dimension = varDecVisitor.m_dimension + 1;
        m_name = varDecVisitor.m_name;
        m_size = varDecVisitor.m_size;
        m_size.insert(m_size.end(), intVisitor.value);
        return;
    }
}

Variable VarDecVisitor::toVariable ()
{
    Variable v = Variable();
    v.m_name = m_name;
    v.m_dimension = m_dimension;
    v.m_size = m_size;
    v.m_eleType = DataType::UNKNOW;
    v.m_type = (m_dimension == 0) ? DataType::UNKNOW : DataType::ARRAY;
    v.m_structName = "";
    return v;
}

/**
 * FuncDec visitor section
*/
FuncDecVisitor::FuncDecVisitor()
{}

FuncDecVisitor::~FuncDecVisitor()
{}

void FuncDecVisitor::visit(ASTNode *node)
{
    m_funcName = node->m_child->m_value;
    std::cout << "visit funcDec node Function name: " << m_funcName << " " << node->m_childCount << std::endl;

    // ID LP VarList RP 
    if (node->m_childCount == 4) {
        VarListVisitor vlv;
        vlv.visit(node->m_child->m_sibling->m_sibling);
        m_paramNames = vlv.m_names;
        m_params = vlv.m_params;
        return;
    }

    // ID LP RP 
    if (node->m_childCount == 3) {
        return;
    }
}

/**
 * Variable list visitor section
*/

VarListVisitor::VarListVisitor()
{}

VarListVisitor::~VarListVisitor()
{}

void VarListVisitor::visit (ASTNode *node)
{
    ParamDecVisitor pdv;
    // ParamDec
    if (node->m_childCount == 1) {
        pdv.visit(node->m_child);

        m_names.push_back(pdv.m_name);
        m_params.push_back(pdv.m_param);
        return;
    }

    // ParamDec COMMA VarList
    if (node->m_childCount == 3) {
        VarListVisitor vlv;
        pdv.visit(node->m_child);
        vlv.visit(node->m_child->m_sibling->m_sibling);

        m_params.push_back(pdv.m_param);
        m_names.push_back(pdv.m_name);
        m_params.insert(m_params.end(), vlv.m_params.begin(), vlv.m_params.end());
        m_names.insert(m_names.end(), vlv.m_names.begin(), vlv.m_names.end());
        return;
    }
}

/**
 * Parameter Declare visitor section
*/
ParamDecVisitor::ParamDecVisitor()
{}

ParamDecVisitor::~ParamDecVisitor()
{}

void ParamDecVisitor::visit (ASTNode *node)
{
    // Specifier VarDec
    SpecifierVisitor specifierVisitor;
    specifierVisitor.visit(node->m_child);

    VarDecVisitor varDecVisitor;
    varDecVisitor.visit(node->m_child->m_sibling);
    m_name = varDecVisitor.m_name;

    if (specifierVisitor.m_type != DataType::STRUCTURE) {
        DataType::Type eleType = specifierVisitor.m_type;
        m_param = Variable(varDecVisitor.m_dimension, varDecVisitor.m_size, varDecVisitor.m_name, eleType);
        return;
    }

    if (specifierVisitor.m_type == DataType::STRUCTURE) {

        Variable v(varDecVisitor.m_dimension, 
           varDecVisitor.m_size, 
           varDecVisitor.m_name, 
           specifierVisitor.m_name);
        
        // 不能在声明参数的同时声明结构体
        if (specifierVisitor.m_isDefine) {
            NodeVisitor::appendErrorMsg(16, node->m_row, "define a structure in parameter");
            // 插入的symbol table元素不合法，要删掉
            currentScope->remove(specifierVisitor.m_name);
            m_param = v;
            return;
        }

        VAL_T *value = currentScope->lookup(specifierVisitor.m_name, 0);
        // 查不到defined structure
        if (value == nullptr) {
            NodeVisitor::appendErrorMsg(16, node->m_row, "undefined structure in parameter");
            m_param = v;
            return;
        }

        m_param = v;
        return;
    }
    
}

/**
 * CompSt visitor section
*/
CompStVisitor::CompStVisitor()
{}

CompStVisitor::~CompStVisitor()
{}

void CompStVisitor::visit (ASTNode *node)
{
    // LC DefList StmtList RC
    if (node->m_childCount == 4) {
        ASTNode *defList = node->m_child->m_sibling;
        ASTNode *stmtList = node->m_child->m_sibling->m_sibling;

        DefListVisitor dlv;
        StmtListVisitor slv;
        dlv.visit(defList);
        slv.visit(stmtList);
        return;
    }
}

/**
 * StmtList visitor section
*/
StmtListVisitor::StmtListVisitor()
{}

StmtListVisitor::~StmtListVisitor()
{}

void StmtListVisitor::visit (ASTNode *node)
{
    if (node->m_childCount == 0) {
        return;
    }

    // Stmt StmtList
    if (node->m_childCount == 2) {
        ASTNode *stmt = node->m_child;
        ASTNode *stmtList = node->m_child->m_sibling;

        StmtVisitor sv;
        StmtListVisitor slv;
        sv.visit(stmt);
        slv.visit(stmtList);
        return;
    }
}

/**
 * Stmt visitor section
*/
StmtVisitor::StmtVisitor()
{}

StmtVisitor::~StmtVisitor()
{}

void StmtVisitor::visit (ASTNode *node)
{
    std::cout << "evoke stmt visitor on " << node->m_type <<std::endl;
    // CompSt
    if (node->m_childCount == 1) {
        ASTNode *compSt = node->m_child;

        CompStVisitor csv;
        csv.visit(compSt);
        return;
    }

    // Exp Semi
    if (node->m_childCount == 2) {
        ASTNode *exp = node->m_child;

        ExpVisitor ev;
        ev.visit(exp);
        return;
    }

    // RETURN Exp SEMI
    if (node->m_childCount == 3) {
        ASTNode *exp = node->m_child->m_sibling;
        ExpVisitor ev;
        // VAL_T *val = currentScope->lookup(currentScope->m_scope_name, 0);
        // if (val == nullptr) {
        //     std::cout << "RETURN Exp SEMI: func not inserted" << std::endl;
        //     return;
        // }
        // Function func = std::get<Function>(val->m_val);

        ev.visit(exp);
        // std::string s("return");
        std::string s("ret_");
        VAL_T *decRet = currentScope->lookup(s, 0);
        if (decRet->m_valType != EntryType::FUNCTION) {
            return;
        }

        Function func = std::get<Function>(decRet->m_val);
        std::cout << "return type: " << ev.m_retType << " function return: " << func.m_retType <<std::endl;
        if (ev.m_retType != func.m_retType) {
            NodeVisitor::appendErrorMsg(8, exp->m_row, "function return type is not matched");
            return; 
        }
        
        // VAL_T *retVal = ev.m_expValue;
        // if (retVal == nullptr) {
        //     // constant return;
        //     Variable v(s, ev.m_retType);
        //     retVal = new VAL_T(EntryType::VARIABLE, v);
        // }
        // // std::cout << "return exp ptr " << ev.m_expValue << std::endl;
        // currentScope->insert(s, *retVal);
        
        // if (ev.m_retType != func.m_retType) {
        //     NodeVisitor::appendErrorMsg(18, exp->m_row, "function return type is not matched");
        //     return;
        // }
    }

    if (node->m_childCount == 5) {
        // WHILE LP Exp RP Stmt
        if (node->m_child->m_type.compare("WHILE") == 0) {
            ASTNode *exp = node->m_child->m_sibling->m_sibling;
            ASTNode *stmt = node->m_child->m_sibling->m_sibling->m_sibling->m_sibling;

            ExpVisitor ev;
            StmtVisitor sv;
            ev.visit(exp);
            SymTab *symTab = new SymTab(currentScope->m_scope_level + 1);
            symTab->m_enclosing_scope = currentScope;
            currentScope = symTab;
            sv.visit(stmt);
            currentScope = currentScope->m_enclosing_scope;

            if (ev.m_retType != DataType::INT) {
                NodeVisitor::appendErrorMsg(17, exp->m_row, "only int can do boolean operation");
                return;
            }
            return;
        }

        // IF LP Exp RP Stmt
        if (node->m_child->m_type.compare("IF") == 0) {
            ASTNode *exp = node->m_child->m_sibling->m_sibling;
            ASTNode *stmt = node->m_child->m_sibling->m_sibling->m_sibling->m_sibling;

            std::cout << "exp value name=" << exp->m_type << "stmt value name=" << stmt->m_type << std::endl;

            ExpVisitor ev;
            StmtVisitor sv;
            ev.visit(exp);
            SymTab *symTab = new SymTab(currentScope->m_scope_level + 1);
            symTab->m_enclosing_scope = currentScope;
            currentScope = symTab;
            sv.visit(stmt);
            currentScope = currentScope->m_enclosing_scope;
            if (ev.m_retType != DataType::INT) {
                NodeVisitor::appendErrorMsg(17, exp->m_row, "only int can do boolean operation1");
                return;
            }
            return;
        }
    }

    // IF LP Exp RP Stmt ELSE Stmt
    if (node->m_childCount == 7) {
        ASTNode *exp = node->m_child->m_sibling->m_sibling;
        ASTNode *stmt1 = node->m_child->m_sibling->m_sibling->m_sibling->m_sibling;
        ASTNode *stmt2 = node->m_child->m_sibling->m_sibling->m_sibling->m_sibling->m_sibling->m_sibling;
        std::cout << exp->m_type << std::endl;

        ExpVisitor ev;
        StmtVisitor sv1;
        StmtVisitor sv2;
        ev.visit(exp);
        SymTab *symTab1 = new SymTab(currentScope->m_scope_level + 1);
        symTab1->m_enclosing_scope = currentScope;
        currentScope = symTab1;
        sv1.visit(stmt1);
        currentScope = currentScope->m_enclosing_scope;

        SymTab *symTab2 = new SymTab(currentScope->m_scope_level + 1);
        symTab2->m_enclosing_scope = currentScope;
        currentScope = symTab2;
        sv2.visit(stmt2);
        currentScope = currentScope->m_enclosing_scope;

        if (ev.m_retType != DataType::INT) {
            NodeVisitor::appendErrorMsg(17, exp->m_row, "only int can do boolean operation2");
            return;
        }
        return;
    }
}

/**
 * DefList: Def DefList
*/
DefListVisitor::DefListVisitor()
{}

DefListVisitor::~DefListVisitor()
{}

void DefListVisitor::visit (ASTNode *node)
{
    if (node->m_childCount == 0) {
        return;
    }

    // Def DefList
    if (node->m_childCount == 2) {
        ASTNode *def = node->m_child;
        ASTNode *defList = node->m_child->m_sibling;

        DefVisitor dv;
        DefListVisitor dlv;
        dv.visit(def);
        dlv.visit(defList);
        return;
    }
}

/**
 * Variable define visitor section
*/
DefVisitor::DefVisitor()
{}

DefVisitor::~DefVisitor()
{}

void DefVisitor::visit (ASTNode *node)
{
    // Specifier DecList SEMI
    if (node->m_childCount == 3) {
        ASTNode *specifier = node->m_child;
        ASTNode *decList = node->m_child->m_sibling;

        SpecifierVisitor sv;
        DecListVisitor dlv;
        sv.visit(specifier);
        dlv.visit(decList);
        std::cout << "evoke def visitor node with size: " << dlv.m_decList.size() << std::endl;

        // 如果有初试化，检查初试化的赋值是否符合给定的参数，插入符号表
        for (DecVisitor dv: dlv.m_decList) {
            std::cout << "intialize value type " << sv.m_type << " " << dv.m_rvalue.m_retType << std::endl;
            if (dv.m_initialized && sv.m_type != dv.m_rvalue.m_retType) {
                NodeVisitor::appendErrorMsg(5, decList->m_row, "unmatching types on both sides of assignment operator (=)");
            }
            
            Variable v = dv.m_varDec.toVariable();
            v.m_structName = sv.m_name;
            v.m_eleType = sv.m_type;

            if (v.m_dimension == 0) {
                v.m_type = v.m_eleType;
            }
            VAL_T val(EntryType::VARIABLE, v);
            
            if (currentScope->lookup(v.m_name, 1) != nullptr) {
                std::string errorMsg = v.m_name + " variable is redefined in the same scope";
                NodeVisitor::appendErrorMsg(3, decList->m_row, errorMsg);
            }
            std::cout << "decList name: " << dv.m_varDec.m_name << " insert node with name: " << v.m_name << std::endl;
            std::cout << "         " << val.getType() << std::endl;
            currentScope->insert(v.m_name, val);
        }
        return;
    }
}

/**
 * Declare list visitor section
*/
DecListVisitor::DecListVisitor()
{}

DecListVisitor::~DecListVisitor()
{}

void DecListVisitor::visit(ASTNode *node) 
{
    // Dec COMMA DecList
    if (node->m_childCount == 3) { 
        ASTNode *dec = node->m_child;
        ASTNode *decList = node->m_child->m_sibling->m_sibling;
        DecVisitor dv;
        DecListVisitor dlv;
        dv.visit(dec);
        dlv.visit(decList);
        m_decList.push_back(dv);
        
        m_decList.insert(m_decList.end(), dlv.m_decList.begin(), dlv.m_decList.end());
        return;
    }

    if (node->m_childCount == 1) { // Dec
        ASTNode *dec = node->m_child;
        DecVisitor dv;
        dv.visit(dec);
        m_decList.push_back(dv);
        return;
    }
}

/**
 * Dec visitor section
*/
DecVisitor::DecVisitor()
{}

DecVisitor::~DecVisitor()
{}

void DecVisitor::visit(ASTNode *node) 
{
    if (node->m_childCount == 3) { // VarDec ASSIGN Exp
        ASTNode *varDec = node->m_child;
        ASTNode *exp = node->m_child->m_sibling->m_sibling;

        VarDecVisitor varDecVisitor;
        ExpVisitor expVisitor;
        varDecVisitor.visit(varDec);
        expVisitor.visit(exp);
        m_initialized = 1;
        m_varDec = varDecVisitor;
        m_rvalue = expVisitor;
        return;
    }

    if (node->m_childCount == 1) { // VarDec
        VarDecVisitor varDecVisitor;
        varDecVisitor.visit(node->m_child);
        m_initialized = 0;
        m_varDec = varDecVisitor;
        return;
    }
}

/**
 * Exp Visitor section
*/
ExpVisitor::ExpVisitor():
    m_isRvalue ( 0 ),
    m_retType ( DataType::UNKNOW ),
    m_expValue ( nullptr )
{}

ExpVisitor::~ExpVisitor()
{}

int ExpVisitor::compare (ExpVisitor &visitor)
{
    if (m_retType == visitor.m_retType)
        return 0;
    else
        return 1;
}

void ExpVisitor::visit(ASTNode *node)
{    
    std::cout << "evoke exp visitor " << node->m_childCount << node->m_type << std::endl;
    if (node->m_childCount == 1) {
        ASTNode *child = node->m_child;
        std::cout << child->m_type << " " << child->m_value << std::endl;

        if (child->m_type.compare("INT") == 0) {
            m_retType = DataType::INT;
            m_isRvalue = 1;
            return;
        }

        if (child->m_type.compare("FLOAT") == 0) {
            m_retType = DataType::FLOAT;
            m_isRvalue = 1;
            return;
        }

        if (child->m_type.compare("CHAR") == 0) {
            m_retType = DataType::CHAR;
            m_isRvalue = 1;
            return;
        }

        if (child->m_type.compare("ID") == 0) {  
            // access to the variable, not declare
            // 只可能是variable，不可能是function或者structure
            std::string key = child->m_value;
            std::cout << key << std::endl;
            VAL_T *value = currentScope->lookup(key, 0);
            if (value != nullptr) {
                m_retType = value->getType();
            } else {
                std::string errorMsg = key + " variable is used without definition";
                NodeVisitor::appendErrorMsg(1, node->m_row, errorMsg);
                m_retType = DataType::UNKNOW;
            }
            m_expValue = value;
            m_isRvalue = 0;
            return;
        }
    }

    if (node->m_childCount == 2) {
        // MINUS Exp
        if (node->m_child->m_type.compare("MINUS") == 0 && 
            node->m_child->m_sibling->m_type.compare("Exp") == 0)
        {
            ASTNode *child = node->m_child->m_sibling;

            ExpVisitor visitor;
            visitor.visit(child);
            
            if (visitor.m_retType != DataType::INT && visitor.m_retType != DataType::FLOAT) {
                NodeVisitor::appendErrorMsg(7, child->m_row, "unmatching operands, nagate an non-digit");
                m_retType = DataType::UNKNOW;
                m_isRvalue = 0;
                return;
            }  else {
                m_retType = visitor.m_retType;
                m_isRvalue = 1;
                return;
            }
        }

        // NOT Exp
        if (node->m_child->m_type.compare("NOT") == 0 && 
            node->m_child->m_sibling->m_type.compare("Exp") == 0)
        {
            ASTNode *child = node->m_child->m_sibling;

            ExpVisitor visitor;
            visitor.visit(child);

            if (visitor.m_retType != DataType::INT) {
                NodeVisitor::appendErrorMsg(7, child->m_row, "unmatching operands for boolean operator");
                m_retType = DataType::UNKNOW;
                m_isRvalue = 0;
                return;
            } else {
                m_retType = DataType::INT;
                m_isRvalue = 1;
                return;
            }
        }

    }

    if (node->m_childCount == 3) {
        // Exp op Exp
        if (node->m_child->m_type.compare("Exp") == 0 && 
            node->m_child->m_type.compare(node->m_child->m_sibling->m_sibling->m_type) == 0)
        {
            ASTNode *leftExp = node->m_child;
            ASTNode *rightExp = node->m_child->m_sibling->m_sibling;
            std::string op = node->m_child->m_sibling->m_type;
            std::cout << op << std::endl;

            ExpVisitor leftExpVisitor;
            leftExpVisitor.visit(leftExp);

            ExpVisitor rightExpVisitor;
            rightExpVisitor.visit(rightExp);

            if (op.compare("ASSIGN") == 0) { // check whether left type equal right value
                std::cout << "left type: " << leftExpVisitor.m_retType << "; right type: " << rightExpVisitor.m_retType << std::endl;
                if (leftExpVisitor.m_isRvalue == 1) {
                    NodeVisitor::appendErrorMsg(6, leftExp->m_row, "rvalue on the left side of assignment operator");
                    m_retType = DataType::UNKNOW;
                    m_isRvalue = 0;
                    return;
                }

                if (leftExpVisitor.compare(rightExpVisitor) != 0) {
                    NodeVisitor::appendErrorMsg(5, leftExp->m_row, "unmatching type on both sides of assignment");
                    m_retType = DataType::UNKNOW;
                    m_isRvalue = 0;
                    return;
                }

                m_retType = leftExpVisitor.m_retType;
                m_isRvalue = 1;
            }

            if (std::string("AND OR").find(op) != -1) { // left and right should be int
                if (leftExpVisitor.m_retType != DataType::INT || rightExpVisitor.m_retType != DataType::INT) {
                    NodeVisitor::appendErrorMsg(7, leftExp->m_row, "unmatching operands for boolean operator");
                    m_retType = DataType::UNKNOW;
                    m_isRvalue = 0;
                    return;
                } else {
                    m_retType = DataType::INT;
                    m_isRvalue = 1;
                    return;
                }
            }
            if (std::string("LT LE GT GE NE EQ").find(op) != -1) {
                m_retType = DataType::INT;
                m_isRvalue = 1;
                return;
            }

            if (std::string("PLUS MINUS MUL DIV").find(op) != -1) {
                std::cout << "left exp visitor: " << leftExpVisitor.m_retType << " right exp visitor: " << rightExpVisitor.m_retType << std::endl;
                if (leftExpVisitor.m_retType >= DataType::ARRAY || rightExpVisitor.m_retType >= DataType::ARRAY) {
                    std::cout << 1 << std::endl;
                    NodeVisitor::appendErrorMsg(7, leftExp->m_row, "unsupported type of operands for arithmatic operator");
                    m_retType = DataType::UNKNOW;
                    m_isRvalue = 0;
                    return;
                }

                if (leftExpVisitor.m_retType == DataType::FLOAT || rightExpVisitor.m_retType == DataType::FLOAT) {
                    m_retType = DataType::FLOAT;
                    m_isRvalue = 1;
                    return;
                }

                if (leftExpVisitor.m_retType == DataType::INT || rightExpVisitor.m_retType == DataType::INT) {
                    m_retType = DataType::INT;
                    m_isRvalue = 1;
                    return;
                }
            }
        }

        // LP Exp RP
        if (node->m_child->m_type.compare("LP") == 0 && 
            node->m_child->m_sibling->m_type.compare("Exp") == 0 &&
            node->m_child->m_sibling->m_sibling->m_type.compare("RP") == 0)
        {
            ASTNode *child = node->m_child->m_sibling;

            ExpVisitor visitor;
            visitor.visit(child);

            m_retType = visitor.m_retType;
            m_isRvalue = visitor.m_isRvalue;
            return;
        }

        // ID LP RP    function invoke
        if (node->m_child->m_type.compare("ID") == 0 && 
            node->m_child->m_sibling->m_type.compare("LP") == 0 && 
            node->m_child->m_sibling->m_sibling->m_type.compare("RP") == 0) 
        {
            ASTNode *child = node->m_child;

            std::string key = child->m_value;
            VAL_T *value = currentScope->lookup(key, 0);

            if (value->m_valType != EntryType::FUNCTION) {
                NodeVisitor::appendErrorMsg(11, child->m_row, "applying function invocation operator (foo(...)) on non-function names");
                m_retType = DataType::UNKNOW;
                m_isRvalue = 0;
                return;
            }

            Function func = std::get<Function>(value->m_val);

            // check whether parameter match
            if (func.m_params.size() != 0) {
                NodeVisitor::appendErrorMsg(9, child->m_row, "the function’s arguments mismatch the declared parameters");
                m_retType = DataType::UNKNOW;
                m_isRvalue = 0;
                return;
            }
            std::cout << "invoke function " << func.m_name << "without arguments returns " << func.m_retType << std::endl;
            
            m_retType = func.m_retType;
            m_expValue = value;
            m_isRvalue = 1;
            return;
        }

        // Exp DOT ID    struture access to items
        if (node->m_child->m_type.compare("Exp") == 0 && 
            node->m_child->m_sibling->m_type.compare("DOT") == 0 && 
            node->m_child->m_sibling->m_sibling->m_type.compare("ID") == 0)
        {
            ASTNode *exp = node->m_child;
            ASTNode *idNode = node->m_child->m_sibling->m_sibling;
            ExpVisitor ev;
            ev.visit(exp);
            std::string id = idNode->m_value;
            VAL_T *value = ev.m_expValue;
            std::cout << id << std::endl;
            if (value->getType() != DataType::STRUCTURE) {
                NodeVisitor::appendErrorMsg(13, exp->m_row, "accessing member of non-structure variable");
                m_retType = DataType::UNKNOW;
                m_isRvalue = 0;
                return;
            }
            VAL_T *structPtr;
            // structure (array indexing)
            if (value->m_val.index() == 1) {
                Variable v = std::get<Variable>(value->m_val);
                structPtr = currentScope->lookup(v.m_structName, 0); 
            } else {
                structPtr = value;
            }
            Structure s = std::get<Structure>(structPtr->m_val);
            VAL_T* idPtr = s.m_symTab->lookup(id, 1);
            if (idPtr != nullptr) {
                std::cout << idPtr->getType() << std::endl;
                m_expValue = idPtr;
                m_isRvalue = 0;
                m_retType = idPtr->getType();
            } else {
                NodeVisitor::appendErrorMsg(13, exp->m_row, "accessing an undefined structure member");
                m_retType = DataType::UNKNOW;
                m_isRvalue = 0;
                return;
            }
        }
    }

    if (node->m_childCount == 4) {  
        // ID LP Args RP function invoke
        if (node->m_child->m_type.compare("ID") == 0 && 
            node->m_child->m_sibling->m_type.compare("LP") == 0 && 
            node->m_child->m_sibling->m_sibling->m_type.compare("Args") == 0 &&
            node->m_child->m_sibling->m_sibling->m_sibling->m_type.compare("RP") == 0)
        {
            ASTNode *id = node->m_child;
            ASTNode *args = node->m_child->m_sibling->m_sibling;

            std::string key = id->m_value;
            VAL_T *value = currentScope->lookup(key, 0);

            ArgsVisitor visitor;
            visitor.visit(args);

            if (value == nullptr) {
                std::string s = key + " function is invoked without deﬁnition";
                NodeVisitor::appendErrorMsg(2, node->m_row, s);
                m_retType = DataType::UNKNOW;
                m_isRvalue = 0;
                return;
            }

            if (value->m_valType != EntryType::FUNCTION) {
                NodeVisitor::appendErrorMsg(11, id->m_row, "applying function invocation operator (foo(...)) on non-function names");
                m_retType = DataType::UNKNOW;
                m_isRvalue = 0;
                return;
            }

            Function func = std::get<Function>(value->m_val);
            
            // check parameter size equality
            if (func.m_params.size() == visitor.m_argsType.size()) {
                // check type equality
                int len = func.m_params.size();
                for (int i = 0; i < len; ++ i) {
                    if (func.m_params[i].m_type != visitor.m_argsType[i]) {
                        NodeVisitor::appendErrorMsg(9, node->m_row, "the function’s arguments mismatch the declared parameters");
                        m_retType = DataType::UNKNOW;
                        m_isRvalue = 0;
                        return;
                    }
                }
            } else {
                NodeVisitor::appendErrorMsg(9, node->m_row, "the function’s arguments mismatch the declared parameters");
                m_retType = DataType::UNKNOW;
                m_isRvalue = 0;
                return;
            }
            m_retType = func.m_retType;
            m_expValue = value; // 应该构建func的返回值的一个VAL_T而不是function本身
            m_isRvalue = 1;
            return;
        }

        // Exp LB Exp RB     array indexing
        if (node->m_child->m_type.compare("Exp") == 0 && 
            node->m_child->m_sibling->m_type.compare("LB") == 0 && 
            node->m_child->m_sibling->m_sibling->m_type.compare("Exp") == 0 &&
            node->m_child->m_sibling->m_sibling->m_sibling->m_type.compare("RB") == 0)
        {
            ASTNode *arrayNode = node->m_child;
            ASTNode *index = node->m_child->m_sibling->m_sibling;

            ExpVisitor arrayVisitor;
            ExpVisitor indexVisitor;

            arrayVisitor.visit(arrayNode);
            indexVisitor.visit(index);

            // indexing an non array variable
            if (arrayVisitor.m_retType != DataType::ARRAY) {
                NodeVisitor::appendErrorMsg(10, arrayNode->m_row, "applying indexing operator ([...]) on non-array type variables");
                m_retType = DataType::UNKNOW;
                m_isRvalue = 0;
                return;
            }

            // index is non-interger expression
            if (indexVisitor.m_retType != DataType::INT) {
                NodeVisitor::appendErrorMsg(12, arrayNode->m_row, "array indexing with non-integer type expression");
                m_retType = DataType::UNKNOW;
                m_isRvalue = 0;
                return;
            }
            
            Variable array = std::get<Variable>(arrayVisitor.m_expValue->m_val);
            std::cout << array.m_dimension << " " << array.m_eleType << std::endl;
            if (array.m_dimension == 1) {
                m_retType = array.m_eleType;
                m_isRvalue = 0;
                if (m_retType == DataType::STRUCTURE) {
                    m_expValue = currentScope->lookup(array.m_structName, 0);
                }
                return;
            }

            if (array.m_dimension > 1) {
                std::vector<int> retSize = std::vector<int>(array.m_size.begin() + 1, array.m_size.end());
                Variable v(array.m_dimension - 1, retSize, array.m_name, array.m_eleType);
                m_expValue = new VAL_T(EntryType::VARIABLE, v);
                m_retType = m_expValue->getType();
                m_isRvalue = 0;
                return;
            }

            if (array.m_dimension == 0) {
                NodeVisitor::appendErrorMsg(10, arrayNode->m_row, "applying indexing operator ([...]) on non-array type variables");
                m_retType = DataType::UNKNOW;
                m_isRvalue = 0;
                std::cout << "Variable with dimension zero but type is not INT: internel error" << std::endl;
                return;
            }

        }
    }

}

ArgsVisitor::ArgsVisitor()
{}

ArgsVisitor::~ArgsVisitor()
{}

void ArgsVisitor::visit (ASTNode *node) 
{
    ExpVisitor ev;
    std::cout << "evoke args visitor " << node->m_childCount << std::endl;
    // Exp
    if (node->m_childCount == 1) {
        ev.visit(node->m_child);
        m_argsType.push_back(ev.m_retType);
        return;
    }

    // Exp COMMA Args
    if (node->m_childCount == 3) {
        ArgsVisitor av;

        ev.visit(node->m_child);
        av.visit(node->m_child->m_sibling->m_sibling);

        m_argsType.push_back(ev.m_retType);
        m_argsType.insert(m_argsType.end(), av.m_argsType.begin(), av.m_argsType.end());
        return;
    }
}