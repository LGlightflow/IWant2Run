#include <iostream>
#include <string>
using namespace std;

int main() {
    int a = 10;
    int b = 20;
    string name = "C++";

    // 1. 值捕获所有变量（复制）
    auto lambda1 = [=]() {
        cout << "[=] 值捕获: a + b = " << (a + b) << endl;
    };

    // 2. 引用捕获所有变量
    auto lambda2 = [&]() {
        cout << "[&] 引用捕获: 修改 a 和 b" << endl;
        a += 1;
        b += 2;
        cout << "a="<<a<<",b="<<b<<endl;
    };

    // 3. 捕获特定变量（值）
    auto lambda3 = [a]() {
        cout << "[a] 值捕获 a = " << a << endl;
    };

    // 4. 捕获特定变量（引用）
    auto lambda4 = [&b]() {
        b *= 2;
        cout << "[&b] 引用捕获 b = " << b << endl;
    };

    // 5. 混合捕获：默认值捕获 + 指定引用捕获
    auto lambda5 = [=, &b]() {
        cout << "[=, &b] b = " << b << ", a = " << a << endl;
        // a 是只读，b 是可修改
    };

    // 6. [this] 捕获类内成员变量（演示见后面）
    // 省略

    // 7. 初始化捕获（C++14+）
    auto lambda6 = [msg = std::move(name)]() {
        cout << "[msg = move(name)] 捕获 name = " << msg << endl;
    };

    // 执行
    lambda1();  // a=10, b=20
    lambda2();  // 修改 a, b
    lambda3();  // a=10 (复制的旧值)
    lambda4();  // b 被翻倍
    lambda5();  // a=11（但值捕获，所以显示旧值）, b=44
    lambda6();  // 捕获移动后的字符串

    cout << "main: a = " << a << ", b = " << b << ", name = " << name << endl;//name 为空，被移动了
}