#include <iostream>
#include <memory>

class B;
class A {
public:
    //std::shared_ptr<B> pb_;
    std::weak_ptr<B> pb_; //weak_ptr 才能在func推出时执行析构
    ~A() {
        std::cout << "A delete" << std::endl;
    }
};

class B {
public:
    //std::shared_ptr<A> pa_;
    std::weak_ptr<A> pa_;
    ~B() {
        std::cout << "B delete" << std::endl;
    }
};

void fun() {
    std::shared_ptr<A> pa(new A()); // A先入栈
    std::shared_ptr<B> pb(new B());
    pa->pb_ = pb; // 循环引用
    pb->pa_ = pa; // 循环引用,pa和pb的引用计数永远不会为 0,对象无法被释放
    
    std::cout << "pa use_count: " << pa.use_count() << std::endl; 
    std::cout << "pb use_count: " << pb.use_count() << std::endl; 
    
}


int main() {
    // std::unique_ptr<int> u1(new int(10));
    // // std::unique_ptr<int> u2 = u1;  // 编译错误，不允许拷贝
    // std::unique_ptr<int> u3 = std::move(u1);  //std::move 将u1的所有权转给u3后，u1为空指针，u3有资源的所有权
    // if (!u1) {
    //     std::cout << "u1 is nullptr" << std::endl;
    // }
    // std::cout << *u3 << std::endl; 
    

    // std::shared_ptr<int> s1(new int(10));
    // std::shared_ptr<int> s2 = s1; 
    // std::cout << "s1 use_count: " << s1.use_count() << std::endl; // s1,s2 共享1个对象，引用计数为2，
    // std::cout << "s2 use_count: " << s2.use_count() << std::endl; 
    // s1.reset(); 
    // std::cout << "s2 use_count: " << s2.use_count() << std::endl; //s1调用reset后，只有s2指向对象
    
    // fun();

    std::shared_ptr<int> s1(new int(10));
    std::weak_ptr<int> w1 = s1; 
    if (std::shared_ptr<int> s2 = w1.lock()) { 
        std::cout << *s2 << std::endl; 
    } else {
        std::cout << "object has been deleted" << std::endl;
    }
    s1.reset(); 
    if (std::shared_ptr<int> s3 = w1.lock()) { 
        std::cout << *s3 << std::endl; 
    } else {
        std::cout << "object has been deleted" << std::endl;
    }
    return 0;
}