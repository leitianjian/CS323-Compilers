#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <string>
#include <variant>
#include <iostream>

namespace Compiler
{
struct OpType {
    typedef enum {
        LABEL, FUNC, 
        ASSI, PLUS, MINUS, MUL, DIV, 
        JUMP, J_EQ, J_NE, J_LT, J_LE, J_GT, J_GE, J_RELOP,
        RET, PARAM, ARG, CALL, READ, WRITE
    } Type;
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
    friend bool operator==(const V& lhs, const V& rhs)
    {
        return lhs.m_isTemp == rhs.m_isTemp && lhs.m_count == rhs.m_count;
    }
};


class Label
{
public:
    int m_count;
    std::string m_labelName;

    Label();
    ~Label();
    Label(int count);
    Label(std::string name);
    friend bool operator==(const Label& lhs, const Label& rhs)
    {
        return lhs.m_count == rhs.m_count;
    }
};

class Instruction
{
public:
    Instruction *m_prev_ins;
    Instruction *m_next_ins;

    OpType::Type m_opType;
    std::string m_relop;
    std::variant<int, V> m_arg1;
    std::variant<int, V> m_arg2;
    std::variant<Label, V, std::string, int> m_result;

    std::string m_instruction;

    Instruction();
    ~Instruction();
    Instruction(OpType::Type opType, std::string name); // LABEL x :    FUNCTION x :
    Instruction(OpType::Type opType, std::string functName, V result); // x := CALL f
    Instruction(OpType::Type opType, V args, V result); // ASSI
    Instruction(OpType::Type opType, int args, V result); // ASSI
    Instruction(OpType::Type opType, V args1, V args2, V result);
    Instruction(OpType::Type opType, int args1, int args2, V result);
    Instruction(OpType::Type opType, int args1, V args2, V result);
    Instruction(OpType::Type opType, V args1, int args2, V result);
    Instruction(OpType::Type opType, V args1, V args2, Label label);
    Instruction(std::string relop, V args1, V args2, Label label);
    Instruction(OpType::Type opType, Label label); // GOTO label
    Instruction(OpType::Type opType, V result);
    std::string to_string();

    Instruction(const std::string &instruction);
};

template <class... Args>
struct variant_cast_proxy
{
    std::variant<Args...> v;

    template <class... ToArgs>
    operator std::variant<ToArgs...>() const
    {
        return std::visit([](auto&& arg) -> std::variant<ToArgs...> { return arg ; },
                          v);
    }
};

template <class... Args>
auto variant_cast(const std::variant<Args...>& v) -> variant_cast_proxy<Args...>
{
    return {v};
}

}
#endif