#include <iostream>
#include <string>
#include <variant>

using namespace std;

class A
{
public:
    int n;
};

class B
{
public:
    A a;

    std::string str() {
        return std::string("B with a.n = ").append(to_string(a.n));
    }
};

class C
{
public:
    std::string str;
};

int main() {
    std::variant<B, C> v;
    B b;
    A a;
    a.n = 10;
    b.a = a;
    std::cout << b.str() << std::endl;

    v = b;
    a.n = 20;
    b.a = a;

    std::cout << b.str() << std::endl;
    std::cout << get<B>(v).str() << endl;

}