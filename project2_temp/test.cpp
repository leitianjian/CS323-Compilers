class A
{
public:
    A() {}
};

int etest(const A *&p1, const A *&p2){
    
}

int main(){
    const A* a1 = new A();
    const A* a2 = new A();
    etest((a1), a2);
}