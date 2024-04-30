#include "behavioral/observer.cpp"
#include "creational/singleton.cpp"
int main() {
    // 调用各个设计模式的run函数
    Observer::run();
    Singleton::run();

    return 0;
}
