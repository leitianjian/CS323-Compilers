#include "instruction.h"

using namespace Compiler;

/**
 * Instruction section
*/
Instruction::Instruction()
{}

Instruction::~Instruction()
{}

// LABEL x :    FUNCTION x :
Instruction::Instruction(OpType::Type opType, std::string name) :
    m_opType ( opType ),
    m_result ( name ),
    m_prev_ins ( nullptr ),
    m_next_ins ( nullptr )
{
    if (opType == OpType::LABEL) {
        m_instruction = "LABEL " + name + " :";
    } else if (opType == OpType::FUNC) {
        m_instruction = "FUNCTION " + name + " :";
    }
}

// x := CALL f
Instruction::Instruction(OpType::Type opType, std::string functName, V result) :
    m_opType ( opType ),
    m_result ( result ),
    m_prev_ins ( nullptr ),
    m_next_ins ( nullptr )
{
    V v = V();
    v.m_name = functName;
    m_arg1 = std::variant<int, V>(v);
    m_instruction = result.m_name + " := CALL " + functName;
}

// ASSI
Instruction::Instruction(OpType::Type opType, V args, V result) :
    m_opType ( opType ),
    m_result ( result ),
    m_arg1 ( args ),
    m_prev_ins ( nullptr ),
    m_next_ins ( nullptr )
{
    m_instruction = result.m_name + " := " + args.m_name;
}
    
Instruction::Instruction(OpType::Type opType, int args, V result) :
    m_opType ( opType ),
    m_result ( result ),
    m_arg1 ( args ),
    m_prev_ins ( nullptr ),
    m_next_ins ( nullptr )
{
    m_instruction = result.m_name + " := #" + std::to_string(args);
}

Instruction::Instruction(OpType::Type opType, V args1, V args2, V result) :
    m_opType ( opType ),
    m_result ( result ),
    m_arg1 ( args1 ),
    m_arg2 ( args2 ),
    m_prev_ins ( nullptr ),
    m_next_ins ( nullptr )
{
    std::string op;
    if (opType == OpType::PLUS) {
        op = "+";
    } else if (opType == OpType::MINUS) {
        op = "-";
    } else if (opType == OpType::MUL) {
        op = "*";
    } else if (opType == OpType::DIV) {
        op = "/";
    }
    m_instruction = result.m_name + " := " + args1.m_name + " " + op + " " + args2.m_name;
}

Instruction::Instruction(OpType::Type opType, int args1, int args2, V result) :
    m_opType ( opType ),
    m_result ( result ),
    m_arg1 ( args1 ),
    m_arg2 ( args2 ),
    m_prev_ins ( nullptr ),
    m_next_ins ( nullptr )
{
    std::string op;
    if (opType == OpType::PLUS) {
        op = "+";
    } else if (opType == OpType::MINUS) {
        op = "-";
    } else if (opType == OpType::MUL) {
        op = "*";
    } else if (opType == OpType::DIV) {
        op = "/";
    }
    m_instruction = result.m_name + " := #" + std::to_string(args1) + " " + op + " #" + std::to_string(args2);
}

Instruction::Instruction(OpType::Type opType, int args1, V args2, V result) :
    m_opType ( opType ),
    m_result ( result ),
    m_arg1 ( args1 ),
    m_arg2 ( args2 ),
    m_prev_ins ( nullptr ),
    m_next_ins ( nullptr )
{
    std::string op;
    if (opType == OpType::PLUS) {
        op = "+";
    } else if (opType == OpType::MINUS) {
        op = "-";
    } else if (opType == OpType::MUL) {
        op = "*";
    } else if (opType == OpType::DIV) {
        op = "/";
    }
    m_instruction = result.m_name + " := #" + std::to_string(args1) + " " + op + " " + args2.m_name;
}

Instruction::Instruction(OpType::Type opType, V args1, int args2, V result) :
    m_opType ( opType ),
    m_result ( result ),
    m_arg1 ( args1 ),
    m_arg2 ( args2 ),
    m_prev_ins ( nullptr ),
    m_next_ins ( nullptr )
{
    std::string op;
    if (opType == OpType::PLUS) {
        op = "+";
    } else if (opType == OpType::MINUS) {
        op = "-";
    } else if (opType == OpType::MUL) {
        op = "*";
    } else if (opType == OpType::DIV) {
        op = "/";
    }
    m_instruction = result.m_name + " := " + args1.m_name + " " + op + " " + std::to_string(args2);
}

Instruction::Instruction(OpType::Type opType, V args1, V args2, Label label) :
    m_opType ( opType ),
    m_result ( label ),
    m_arg1 ( args1 ),
    m_arg2 ( args2 ),
    m_prev_ins ( nullptr ),
    m_next_ins ( nullptr )
{
    std::string op;
    if (opType == OpType::J_EQ) {
        op = "==";
    } else if (opType == OpType::J_NE) {
        op = "!=";
    } else if (opType == OpType::J_GE) {
        op = ">=";
    } else if (opType == OpType::J_GT) {
        op = ">";
    } else if (opType == OpType::J_LE) {
        op = "<=";
    } else if (opType == OpType::J_LT) {
        op = "<";
    }
    m_instruction = "IF " + args1.m_name + " " + op + " " + args2.m_name + " GOTO " + label.m_labelName;
}

Instruction::Instruction(std::string relop, V args1, V args2, Label label) :
    m_opType ( OpType::J_RELOP ),
    m_relop ( relop ),
    m_result ( label ),
    m_arg1 ( args1 ),
    m_arg2 ( args2 ),
    m_prev_ins ( nullptr ),
    m_next_ins ( nullptr )
{
    m_instruction = "IF " + args1.m_name + " " + relop + " " + args2.m_name + " GOTO " + label.m_labelName;
}

Instruction::Instruction(OpType::Type opType, Label label) :
    m_opType ( opType ),
    m_result ( label ),
    m_prev_ins ( nullptr ),
    m_next_ins ( nullptr )
{
    m_instruction = "GOTO " + label.m_labelName;
}

Instruction::Instruction(OpType::Type opType, V result) :
    m_opType ( opType ),
    m_result ( result ),
    m_prev_ins ( nullptr ),
    m_next_ins ( nullptr )
{
    std::string op;
    if (opType == OpType::RET) {
        op = "RETURN";
    } else if (opType == OpType::PARAM) {
        op = "PARAM";
    } else if (opType == OpType::ARG) {
        op = "ARG";
    } else if (opType == OpType::READ) {
        op = "READ";
    } else if (opType == OpType::WRITE) {
        op = "WRITE";
    }
    m_instruction = op + " " + result.m_name;
}

std::string Instruction::to_string()
{
    std::string m_instruction;
    switch (m_opType) {
        case OpType::LABEL :
        {
            std::string name = std::get<std::string>(m_result);
            m_instruction = "LABEL " + name + " :";
            break;
        }
        case OpType::FUNC :
        {
            std::string name = std::get<std::string>(m_result);
            m_instruction = "FUNCTION " + name + " :";
            break;
        }
        case OpType::JUMP :
        {
            std::string name = std::get<Label>(m_result).m_labelName;
            m_instruction = "GOTO " + name;
            break;
        }
        case OpType::ASSI :
        {
            if (m_arg1.index() == 0) {
                m_instruction = std::get<V>(m_result).m_name + " := #" + std::to_string(std::get<int>(m_arg1));
            } else if (m_arg1.index() == 1) {
                m_instruction = std::get<V>(m_result).m_name + " := " + std::get<V>(m_arg1).m_name;
            }
            break;
        }
        case OpType::PLUS :
        {
            if (m_arg1.index() == 0 && m_arg2.index() == 0) {
                m_instruction = std::get<V>(m_result).m_name + " := #" + std::to_string(std::get<int>(m_arg1)) + " + #" + std::to_string(std::get<int>(m_arg2));
            } else if (m_arg1.index() == 1 && m_arg2.index() == 0) {
                m_instruction = std::get<V>(m_result).m_name + " := " + std::get<V>(m_arg1).m_name + " + #" + std::to_string(std::get<int>(m_arg2));
            } else if (m_arg1.index() == 0 && m_arg2.index() == 1) {
                m_instruction = std::get<V>(m_result).m_name + " := #" + std::to_string(std::get<int>(m_arg1)) + " + " + std::get<V>(m_arg2).m_name;
            } else {
                m_instruction = std::get<V>(m_result).m_name + " := " + std::get<V>(m_arg1).m_name + " + " + std::get<V>(m_arg2).m_name;
            }
            break;
        }
        case OpType::MINUS :
        {
            if (m_arg1.index() == 0 && m_arg2.index() == 0) {
                m_instruction = std::get<V>(m_result).m_name + " := #" + std::to_string(std::get<int>(m_arg1)) + " - #" + std::to_string(std::get<int>(m_arg2));
            } else if (m_arg1.index() == 1 && m_arg2.index() == 0) {
                m_instruction = std::get<V>(m_result).m_name + " := " + std::get<V>(m_arg1).m_name + " - #" + std::to_string(std::get<int>(m_arg2));
            } else if (m_arg1.index() == 0 && m_arg2.index() == 1) {
                m_instruction = std::get<V>(m_result).m_name + " := #" + std::to_string(std::get<int>(m_arg1)) + " - " + std::get<V>(m_arg2).m_name;
            } else {
                m_instruction = std::get<V>(m_result).m_name + " := " + std::get<V>(m_arg1).m_name + " - " + std::get<V>(m_arg2).m_name;
            }
            break;
        }
        case OpType::MUL :
        {
            if (m_arg1.index() == 0 && m_arg2.index() == 0) {
                m_instruction = std::get<V>(m_result).m_name + " := #" + std::to_string(std::get<int>(m_arg1)) + " * #" + std::to_string(std::get<int>(m_arg2));
            } else if (m_arg1.index() == 1 && m_arg2.index() == 0) {
                m_instruction = std::get<V>(m_result).m_name + " := " + std::get<V>(m_arg1).m_name + " * #" + std::to_string(std::get<int>(m_arg2));
            } else if (m_arg1.index() == 0 && m_arg2.index() == 1) {
                m_instruction = std::get<V>(m_result).m_name + " := #" + std::to_string(std::get<int>(m_arg1)) + " * " + std::get<V>(m_arg2).m_name;
            } else {
                m_instruction = std::get<V>(m_result).m_name + " := " + std::get<V>(m_arg1).m_name + " * " + std::get<V>(m_arg2).m_name;
            }
            break;
        }
        case OpType::DIV :
        {
            if (m_arg1.index() == 0 && m_arg2.index() == 0) {
                m_instruction = std::get<V>(m_result).m_name + " := #" + std::to_string(std::get<int>(m_arg1)) + " / #" + std::to_string(std::get<int>(m_arg2));
            } else if (m_arg1.index() == 1 && m_arg2.index() == 0) {
                m_instruction = std::get<V>(m_result).m_name + " := " + std::get<V>(m_arg1).m_name + " / #" + std::to_string(std::get<int>(m_arg2));
            } else if (m_arg1.index() == 0 && m_arg2.index() == 1) {
                m_instruction = std::get<V>(m_result).m_name + " := #" + std::to_string(std::get<int>(m_arg1)) + " / " + std::get<V>(m_arg2).m_name;
            } else {
                m_instruction = std::get<V>(m_result).m_name + " := " + std::get<V>(m_arg1).m_name + " / " + std::get<V>(m_arg2).m_name;
            }
            break;
        }
        case OpType::J_RELOP :
        {
            if (m_arg1.index() == 0 && m_arg2.index() == 0) {
                m_instruction = "IF #" + std::to_string(std::get<int>(m_arg1)) + " " + m_relop + " #" + std::to_string(std::get<int>(m_arg2)) + " GOTO " + std::get<Label>(m_result).m_labelName;
            } else if (m_arg1.index() == 1 && m_arg2.index() == 0) {
                m_instruction = "IF " + std::get<V>(m_arg1).m_name + " " + m_relop + " #" + std::to_string(std::get<int>(m_arg2)) + " GOTO " + std::get<Label>(m_result).m_labelName;
            } else if (m_arg1.index() == 0 && m_arg2.index() == 1) {
                m_instruction = "IF #" + std::to_string(std::get<int>(m_arg1)) + " " + m_relop + " " + std::get<V>(m_arg2).m_name + " GOTO " + std::get<Label>(m_result).m_labelName;
            } else {
                m_instruction = "IF " + std::get<V>(m_arg1).m_name + " " + m_relop + " " + std::get<V>(m_arg2).m_name + " GOTO " + std::get<Label>(m_result).m_labelName;
            }
            break;
        }
        case OpType::RET :
        {
            if (m_result.index() == 1) {
                m_instruction = "RETURN " + std::get<V>(m_result).m_name;
            } else if (m_result.index() == 3) {
                m_instruction = "RETURN #" + std::to_string(std::get<int>(m_result));
            }
            break;
        }
        case OpType::PARAM :
        {
            m_instruction = "PARAM " + std::get<V>(m_result).m_name;
            break;
        }
        case OpType::ARG :
        {
            if (m_result.index() == 1) {
                m_instruction = "ARG " + std::get<V>(m_result).m_name;
            } else if (m_result.index() == 3) {
                m_instruction = "ARG #" + std::to_string(std::get<int>(m_result));
            }
            break;
        }
        case OpType::CALL :
        {
            m_instruction = std::get<V>(m_result).m_name + " := CALL " + std::get<V>(m_arg1).m_name; 
            break;
        }
        case OpType::READ :
        {
            m_instruction = "READ " + std::get<V>(m_result).m_name;
            break;
        }
        case OpType::WRITE :
        {
            if (m_result.index() == 1) {
                m_instruction = "WRITE " + std::get<V>(m_result).m_name;
            } else if (m_result.index() == 3) {
                m_instruction = "WRITE #" + std::to_string(std::get<int>(m_result));
            }
            break;
        }
    }
    return m_instruction;
}

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

Label::Label(std::string name):
    m_labelName (name)
{
    m_count = std::stoi(name.substr(3));
}