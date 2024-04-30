#include <iostream>
#include <memory>
#include <string>
namespace Pattern
{

    class Beverage
    {
    public:
        virtual ~Beverage() {}
        virtual std::string getDescription() const = 0;
        virtual double cost() const = 0;
    };

    // 具体组件
    class Coffee : public Beverage
    {
    public:
        std::string getDescription() const override
        {
            return "Coffee";
        }

        double cost() const override
        {
            return 1.0;
        }
    };

    // 装饰器基类
    class CondimentDecorator : public Beverage
    {
    protected:
        std::unique_ptr<Beverage> beverage;

    public:
        CondimentDecorator(std::unique_ptr<Beverage> b) : beverage(std::move(b)) {}

        std::string getDescription() const override
        {
            return beverage->getDescription();
        }

        double cost() const override
        {
            return beverage->cost();
        }
    };

    // 具体装饰器A
    class Milk : public CondimentDecorator
    {
    public:
        Milk(std::unique_ptr<Beverage> b) : CondimentDecorator(std::move(b)) {}

        std::string getDescription() const override
        {
            return CondimentDecorator::getDescription() + ", Milk";
        }

        double cost() const override
        {
            return CondimentDecorator::cost() + 0.5;
        }
    };

    // 具体装饰器B
    class Sugar : public CondimentDecorator
    {
    public:
        Sugar(std::unique_ptr<Beverage> b) : CondimentDecorator(std::move(b)) {}

        std::string getDescription() const override
        {
            return CondimentDecorator::getDescription() + ", Sugar";
        }

        double cost() const override
        {
            return CondimentDecorator::cost() + 0.2;
        }
    };

}

using namespace Pattern;
namespace Decorator
{
    void run()
    {

        std::cout << "*********************** Decorator Pattern Demo ***********************" << std::endl;
        // 创建一个具体coffee对象
        std::unique_ptr<Beverage> coffee = std::make_unique<Coffee>();
        std::cout << coffee->getDescription() << " costs " << coffee->cost() << " dollars." << std::endl;

        // 创建装饰器并装饰Milk组件
        coffee = std::make_unique<Milk>(std::move(coffee));
        std::cout << coffee->getDescription() << " costs " << coffee->cost() << " dollars." << std::endl;

        // 使用装饰后的Sugar组件
        coffee = std::make_unique<Sugar>(std::move(coffee));
        std::cout << coffee->getDescription() << " costs " << coffee->cost() << " dollars." << std::endl;
    }
}
