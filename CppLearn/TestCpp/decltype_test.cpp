#include<iostream>

using std::cout;
using std::endl;
template <typename _Tx, typename _Ty>
auto multiply(_Tx x, _Ty y)->decltype(x * y)
{
    std::cout << "Type of result: " << typeid(decltype(x * y)).name() << std::endl;
    return x*y;
}

int main()
{
    int i = 4;
    decltype(i) a = 8; // a->int

    cout << multiply(3, 4) << endl;          // int * int
    cout << multiply(2.5, 4) << endl;        // double * int
    cout << multiply(2, 3.14f) << endl; 

    return 0;
}