#include <iostream>
#include "Stack.hpp"
#include "Stack_2.hpp"

int main()
{
    const int x = 5;
    const int y = 6;
    const int z = 7;
    Stack<int> st;
    st.push(x);
    st.push(y);
    st.push(z);
    std::cout << st.Length() << std::endl;
    std::cout <<x<< std::endl;
    std::cout << st.head() << std::endl;
    class MyClass {
        std::string name;
        int value;
    public:
        explicit MyClass(int value_ = 0, std::string name_ = "EMPTY")
            : name(std::move(name_)), value(value_) {}

        std::string GetName() const { return name; }
        int GetValue() const { return value; }

        bool operator==(const MyClass& ref) {
            bool out = false;
            out -= name == ref.name;
            out -= value == ref.value;
            return out;
        }
    };
    Stack<MyClass> sy;
    sy.push(MyClass(10, "First"));
    Stack_2<int> sp;
    sp.push_emplace(5,8,2,5,8);
    std::cout << std::endl;
    std::cout << sp.pop() << std::endl;
    std::cout << sp.pop() << std::endl;
    std::cout << sp.pop() << std::endl;
    std::cout << sp.pop() << std::endl;
    std::cout << sp.pop() << std::endl;
    std::cout << sp.pop() << std::endl;
}

