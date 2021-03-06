// ROX.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"


#include "Factory.h"


#include <iostream>

class InheritClass:public IBase
{
public:

    InheritClass()
    {
        std::cout << "build 1\n";
    }
    ~InheritClass()
    {
        std::cout << "destory 1\n";
    }

    void Func1()
    {
        std::cout << "funcs\n";
    }

    void Foo()
    {
        std::cout << "fucking work\n";
    }

private:

};

class InheritBClass :public IBase
{
public:
    InheritBClass()
    {
        std::cout << "bulid2\n";

    }
    ~InheritBClass()
    {
        std::cout << "destory2\n";
    }
    void Foo()
    {
        std::cout << "func2\n";
    }
};

class InheritBase2 :public IBase2
{
public:
    InheritBase2()
    {
        std::cout << "build 3\n";
    }

    InheritBase2(int a)
    {
        std::cout << "build 3 a:" << a << "\n";
    }

    InheritBase2(const std::string& b)
    {
        std::cout << "build 3 b:" << b << "\n";
    }
    ~InheritBase2()
    {
        std::cout << "destory 3\n";
    }
    void Foo2()
    {
        std::cout << "base2:: foo2\n";
    }

};

InheritBase2* Gene()
{
    std::cout << "Gene!\n";
    return new InheritBase2();
}

void TestFactory()
{
    Factory<IBase> baseFactory;

    Factory<IBase>::Register_t<InheritClass> reg("build");
    Factory<IBase>::Register_t<InheritBClass> reg2("build2");

    auto pa = baseFactory.produce_share("build");
    pa->Foo();

    std::cout << "typed id " << typeid(InheritBClass).hash_code()<<"\n";


    auto pb = baseFactory.produce_unique("build2");

    std::cout << "typed id2 " << typeid(*pb).hash_code()<<"\n";


    Factory<IBase2> base2Factory;
    
    Factory<IBase2>::Register_t<InheritBase2> reg3("build3");
    auto pc = base2Factory.produce("build3");
    
    int a = 1;
    std::string b = "23333";

    Factory<IBase2>::Register_t<InheritBase2> reg4("build4", b);
    auto pc2 = base2Factory.produce_share("build4");

    auto func = [] {return new IBase2(); };
    base2Factory.Register("test",std::bind(&Gene));

    auto pd = base2Factory.produce("test");
}


int main()
{
    TestFactory();

    system("pause");

    return 0;
}

