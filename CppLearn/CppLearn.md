# C/CPP 学习

## inline 内联
c/c++ 中，为了解决一些频繁调用的小函数大量消耗栈空间（栈内存）的问题，特别的引入了 inline 修饰符，表示为内联函数。

inline 避免了避免了频繁调用函数对栈内存重复开辟所带来的消耗。

栈空间就是指放置程序的局部数据（也就是函数内数据）的内存空间。

inline使用限制：inline 只适合函数体内代码简单的函数使用，不能包含复杂的结构控制语句例如 while、switch，并且不能内联函数本身不能是直接递归函数

不宜使用内联的情况：
（1）如果函数体内的代码比较长，使用内联将导致内存消耗代价较高。 
（2）如果函数体内出现循环，那么执行函数体内代码的时间要比函数调用的开销大。

## 尾置返回类型
用于函数返回类型的自动推导，一般用于返回类型比较复杂，或者需要通过模板参数（亦或其它表达式）来推导返回类型的情况，通常会结合 decltype 一起使用，本质上算是一种语法糖，在函数定义的参数列表右侧添加 ->ReturnType 来代表函数返回类型，将通常放置函数返回类型的地方使用 auto 代替。
语法格式是：
```cpp
auto FuncName(ArgsList) -> ReturnType { }
```
auto 只是占位符，表示返回类型将会“放在后面”;“-> 返回类型” 是真正的返回类型;参数已经在前面定义好，因此返回类型可以引用参数名来推导

例如
```cpp
auto Func(int i) ->int(*)[10]; //func 接受一个int类型的实参，返回一个指针，该指针指向含有10个整数的数组
```

好处：返回类型的初衷是为了让返回值类型可以依赖于参数类型，例如
```cpp
template <typename T,typename U>
auto Func(T t,U u)->decltype( t + u );
```
另外还可以使代码更简洁，例如声明一个函数，指向无参数，无返回值的函数的指针
```cpp
void (*func())()
{

}

auto func() -> void(*)()
{

}
```

## decltype
decltype与auto关键字一样，用于进行编译时类型推导,decltype的类型推导并不是像auto一样是从变量声明的初始化表达式获得变量的类型，而是总是以一个普通表达式作为参数，返回该表达式的类型,而且decltype并不会对表达式进行求值。
decltype最大的用途，泛型结合auto，追踪返回值类型。

```cpp
template <typename _Tx, typename _Ty>
auto multiply(_Tx x, _Ty y)->decltype(x * y)
{
    std::cout << "Type of result: " << typeid(decltype(x * y)).name() << std::endl;
    return x*y;
}

```
## 泛型
### lambda
匿名函数
形式：
```cpp
[capture](params) mutable noexcept -> return_type {
    // 函数体
}
```

```cpp
int factor = 2;
auto multiply = [factor](int x) { return x * factor; };
std::cout << multiply(5);  // 输出 10
```

## 动态内存

### 动态内存和智能指针
首先回顾一下静态内存和栈内存。用静态内存管理的特征是，生命周期贯穿程序运行始终，static对象在使用之前分配，程序结束后销毁。
```cpp
#include <iostream>
//.data 程序在编译和链接之后划分出的一个内存段（Section）
int globalVar = 10;           // 静态区（.data） 定义在函数之外的变量
static int staticVar = 20;    // 静态区（.data） static 变量
const char* str = "hello";    // 字符串字面量 -> 常量区（.rodata）

void func() {
    static int localStatic = 30;  // 静态区（只初始化一次）， 局部static对象
}
```

栈内存管理在函数之内的非静态对象，在定义的程序块运行的情况下才存在。

栈内存和静态内存的共同特点是由编译器自动创建和销毁。

动态内存是通过new和delete这对运算符进行管理的，但是如果忘记delete就会造成内存泄漏，如：
```cpp
void foo() {
    MyClass* ptr = new MyClass();
    // ... 使用 ptr
    delete ptr;  // 如果忘记delete则内存泄漏
}
```

### 智能指针
C++ 引入了智能指针。智能指针利用 RAII（Resource Acquisition Is Initialization，资源获取即初始化）机制，将内存的管理和对象的生命周期绑定在一起。当智能指针对象创建时，它获取资源（即分配内存）；当智能指针对象销毁时，它自动释放所指向的内存，无需手动调用delete。

智能指针类型
#### unique_ptr
保证同一时间内只有一个智能指针可以指向该对象，为了确保资源独占性，unique_ptr不允许拷贝和赋值

```cpp
#include <iostream>
#include <memory>

int main() {
    std::unique_ptr<int> u1(new int(10));
    // std::unique_ptr<int> u2 = u1;  // 编译错误，不允许拷贝
    std::unique_ptr<int> u3 = std::move(u1);  //std::move 将u1的所有权转给u3后，u1为空指针，u3有资源的所有权
    if (!u1) {
        std::cout << "u1 is nullptr" << std::endl;
    }
    std::cout << *u3 << std::endl; 
    return 0;
}
```

#### shared_ptr

shared_ptr实现了共享式拥有概念，允许多个智能指针指向相同对象，通过引用计数机制来管理对象的生命周期 。当一个shared_ptr指向对象时，引用计数加 1；当shared_ptr离开作用域或被重新赋值时，引用计数减 1，当引用计数为 0 时，对象会被自动释放。
```cpp
#include <iostream>
#include <memory>

int main() {
    std::shared_ptr<int> s1(new int(10));
    std::shared_ptr<int> s2 = s1; 
    std::cout << "s1 use_count: " << s1.use_count() << std::endl; // s1,s2 共享1个对象，引用计数为2，
    std::cout << "s2 use_count: " << s2.use_count() << std::endl; 
    s1.reset(); 
    std::cout << "s2 use_count: " << s2.use_count() << std::endl; //s1调用reset后，只有s2指向对象
    return 0;
}
```
shared_ptr在多线程环境中使用时，需要注意线程安全问题，因为引用计数的修改不是原子操作，可能会导致数据竞争 。（使用std::atomic来实现原子操作，或者使用互斥锁来保护引用计数的修改 ）


#### weak_ptr
weak_ptr是一种不控制对象生命周期的智能指针，它指向一个由shared_ptr管理的对象，主要用于协助shared_ptr解决循环引用问题 。weak_ptr不会增加对象的引用计数，它的构造和析构不会影响对象的生命周期 。

```cpp
#include <iostream>
#include <memory>

class B;
class A {
public:
    std::shared_ptr<B> pb_;
    ~A() {
        std::cout << "A delete" << std::endl;
    }
};

class B {
public:
    std::shared_ptr<A> pa_;
    ~B() {
        std::cout << "B delete" << std::endl;
    }
};

void fun() {
    std::shared_ptr<A> pa(new A());
    std::shared_ptr<B> pb(new B());
    pa->pb_ = pb;
    pb->pa_ = pa;
    std::cout << "pa use_count: " << pa.use_count() << std::endl; 
    std::cout << "pb use_count: " << pb.use_count() << std::endl; 
}

int main() {
    fun();
    return 0;
}
```

```cpp
#include <iostream>
#include <memory>

int main() {
    std::shared_ptr<int> s1(new int(10));
    std::weak_ptr<int> w1 = s1; 
    if (std::shared_ptr<int> s2 = w1.lock()) {  //lock函数提升weak_ptr为shared_ptr
        std::cout << *s2 << std::endl; 
    } else {
        std::cout << "object has been deleted" << std::endl;
    }
    s1.reset(); 
    if (std::shared_ptr<int> s3 = w1.lock()) { 
        std::cout << *s3 << std::endl; 
    } else {
        std::cout << "object has been deleted" << std::endl; // 释放后返回空的shared_ptr
    }
    return 0;
}
```