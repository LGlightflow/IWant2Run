### 多态是什么,实现方式?
多态是同一个行为具有多个不同表现形式或形态的能力。(例如不同动物的eat函数表现不同)

优点:解耦,可替换,可扩充,接口,灵活

多态存在必要条件:继承,重写,父类引用指向子类对象

虚函数存在是为了多态(纯虚函数?virtual void funtion1()=0)


### 虚函数与多态，虚函数表？
https://zhuanlan.zhihu.com/p/691465234

### 堆与栈的区别？

### new/delete 和malloc/free 有什么区别？

### 智能指针,Unique_Ptr,Shared_Ptr,Weak_Ptr区别

### RALL

### inline 内联：
>https://learn.microsoft.com/zh-cn/cpp/cpp/inline-functions-cpp?view=msvc-170
>https://zhuanlan.zhihu.com/p/50812510

关键字 inline 建议编译器使用函数定义中的代码替换对该函数的每次调用，即
```cpp
inline int Add(int a, int b)
{
   return a + b;
}
int main()
{
   int num1 = 1;
   int num2 = 2;
   int myNum = Add(num1, num2);
}
//内联后：
int main()
{
   int num1 = 1;
   int num2 = 2;
   int myNum = num1 + num2;
}
```
理论上，使用内联函数可以加速程序运行，因为它们消除了与函数调用关联的开销。 调用函数需要将返回地址推送到堆栈、将参数推送到堆栈、跳转到函数体，然后在函数完成时执行返回指令。 通过内联函数可以消除此过程。

**内联代码替换操作由编译器自行决定。** 例如，如果某个函数的地址已被占用或编译器判定函数过大，则编译器不会内联该函数。

```cpp
// account.h
class Account
{
public:
// 构造函数内联，因为是在类内定义
    Account(double initial_balance)
    {
        balance = initial_balance;
    }

    double GetBalance() const;
    double Deposit(double amount);
    double Withdraw(double amount);

private:
    double balance;
};

inline double Account::GetBalance() const
{
    return balance;
}

inline double Account::Deposit(double amount)
{
    balance += amount;
    return balance;
}

inline double Account::Withdraw(double amount)
{
    balance -= amount;
    return balance;
}
```
Account 构造函数是内联函数，因为它是在类声明的正文中定义的。
给定的内联成员函数在每个编译单元中必须以相同的方式进行声明。 内联函数必须只有一个定义。

__forceinline 关键字会重写成本收益分析，改为依赖于程序员的判断。 使用 __forceinline 时应小心谨慎。 不加选择地使用 __forceinline 可能会形成较大代码但是仅获得边际性能提升，或是在某些情况下，甚至会损失性能（例如，由于较大可执行文件的分页会增加）。

inline 关键字告知编译器，内联展开是首选操作。 但编译器可以忽略它。 可能会出现这种行为的两种情况是：

* 递归函数。
* 在翻译单元中的其他位置通过指针引用的函数。（inline 允许一个函数在多个翻译单元各有一个定义（One Definition Rule 的特殊例外）
但一旦该函数被取地址（或引用、传指针等）→ 编译器必须放置它的实体（不能只展开 inline））(翻译单元 = 一个 .cpp 文件 + 它通过所有 #include 展开的内容 + 预处理后的最终代码。)

```cpp
inline void Foo() {}
//在翻译单元中的其他位置通过指针引用的函数
void (*fp)() = &Foo;   // 这里通过取地址引用了 Foo
```


### 值传递？引用传递？ 指针传递？

### 引用值做返回值

### 深拷贝 浅拷贝 拷贝构造 拷贝复制