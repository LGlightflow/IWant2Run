#include <iostream>
#include <string>
using namespace std;

int main() {
    int a = 10;
    int b = 20;
    string name = "C++";

    // 1. ֵ�������б��������ƣ�
    auto lambda1 = [=]() {
        cout << "[=] ֵ����: a + b = " << (a + b) << endl;
    };

    // 2. ���ò������б���
    auto lambda2 = [&]() {
        cout << "[&] ���ò���: �޸� a �� b" << endl;
        a += 1;
        b += 2;
        cout << "a="<<a<<",b="<<b<<endl;
    };

    // 3. �����ض�������ֵ��
    auto lambda3 = [a]() {
        cout << "[a] ֵ���� a = " << a << endl;
    };

    // 4. �����ض����������ã�
    auto lambda4 = [&b]() {
        b *= 2;
        cout << "[&b] ���ò��� b = " << b << endl;
    };

    // 5. ��ϲ���Ĭ��ֵ���� + ָ�����ò���
    auto lambda5 = [=, &b]() {
        cout << "[=, &b] b = " << b << ", a = " << a << endl;
        // a ��ֻ����b �ǿ��޸�
    };

    // 6. [this] �������ڳ�Ա��������ʾ�����棩
    // ʡ��

    // 7. ��ʼ������C++14+��
    auto lambda6 = [msg = std::move(name)]() {
        cout << "[msg = move(name)] ���� name = " << msg << endl;
    };

    // ִ��
    lambda1();  // a=10, b=20
    lambda2();  // �޸� a, b
    lambda3();  // a=10 (���Ƶľ�ֵ)
    lambda4();  // b ������
    lambda5();  // a=11����ֵ����������ʾ��ֵ��, b=44
    lambda6();  // �����ƶ�����ַ���

    cout << "main: a = " << a << ", b = " << b << ", name = " << name << endl;//name Ϊ�գ����ƶ���
}