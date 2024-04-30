#include <memory>
#include <iostream>
#include <mutex>

namespace Pattern
{
    class LazySingleton
    {
    public:
        // 获取单例实例的静态方法
        static std::shared_ptr<LazySingleton> getInstance()
        {
            static std::shared_ptr<LazySingleton> _instance = std::shared_ptr<LazySingleton>(new LazySingleton());
            return _instance;
        }

        // 示例方法
        void doSomething()
        {
            std::cout << "LazySingleton..." << std::endl;
        }

    private:
        // 将构造函数设为私有，防止外部创建实例
        LazySingleton() {}
        // 防止复制构造
        LazySingleton(const LazySingleton &) = delete;
        // 防止赋值操作
        LazySingleton &operator=(const LazySingleton &) = delete;
    };

    class HungrySingleton
    {
    public:
        // 获取单例实例的静态方法
        static std::shared_ptr<HungrySingleton> getInstance()
        {
            //  双重检查锁保证线程安全
            if (instance == nullptr)
            {
                // 这个锁必须是静态的，因为静态方法只能访问静态成员变量
                std::unique_lock<std::mutex> lock(mutex);
                if (instance == nullptr)
                {
                    // 不能使用make_shared，因为make_shared会调用拷贝构造函数，而LazySingleton的拷贝构造函数是私有的
                    instance = std::shared_ptr<HungrySingleton>(new HungrySingleton());
                }
            }
            return instance;
        }

        // 示例方法
        void doSomething()
        {
            std::cout << "HungrySingleton..." << std::endl;
        }

    private:
        // 将构造函数设为私有，防止外部创建实例
        HungrySingleton() {}

        // 防止复制构造
        HungrySingleton(const HungrySingleton &) = delete;
        // 防止赋值操作
        HungrySingleton &operator=(const HungrySingleton &) = delete;

        static std::shared_ptr<HungrySingleton> instance;
        // 使用互斥锁来保护实例的创建
        static std::mutex mutex;
    };
    std::shared_ptr<HungrySingleton> HungrySingleton::instance = nullptr;
    std::mutex HungrySingleton::mutex;

}
using namespace Pattern;

namespace Singleton
{
    void run()
    {
        std::cout << "*********************** Singleton Pattern Demo ***********************" << std::endl;
        using namespace Pattern;
        HungrySingleton::getInstance()->doSomething();
        LazySingleton::getInstance()->doSomething();
    }
}
