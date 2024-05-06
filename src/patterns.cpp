#include "behavioral/observer.cpp"
#include "creational/singleton.cpp"
#include "structural/decorator.cpp"
#include "structural/adapter.cpp"

int main() {
    // 调用各个设计模式的run函数
    Observer::run();
    Singleton::run();
    Decorator::run();
    Adapter::run();

    return 0;
}
