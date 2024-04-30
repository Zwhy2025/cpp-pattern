#include <iostream>
#include <list>
#include <mutex>

namespace Pattern
{   
    // 前向声明
    class Observer;

    class Subject
    {
    public:
        std::list<Observer *> _listObserver;
        std::mutex _mutex_list;

    public:
        virtual void attach(Observer *o) = 0;
        virtual void detach(Observer *o) = 0;
        virtual void notify() = 0;
    };

    // 观察们构造注册观察者, 后续流程中可以统一通知观察者
    // 通知接口与具体动作解耦, 方便扩展
    class Stock : public Subject
    {
    public:
        int _nPrice = 0;
        std::mutex _mutex_p;

    public:
        int getPrice();
        void setPrice(int);
        void attach(Observer *o) override;
        void detach(Observer *o) override;
        void notify() override;
    };

    class Observer
    {
    public:
        Subject *_tSub;

    public:
        Observer(Subject *sub);
        virtual ~Observer();
        virtual void update() = 0;
    };

    Observer::Observer(Subject *sub) : _tSub(sub)
    {
        _tSub->attach(this);
    }

    Observer::~Observer()
    {
        _tSub->detach(this);
    }

    // 观测到变化后,观察者们采取的行为子类
    class Monitor : public Observer
    {
    public:
        Monitor(Subject *sub) : Observer(sub) {}
        void print(int v) const
        {
            std::cout << "Monitor: " << v << std::endl;
        }

        void update() override
        {
            print(static_cast<Stock *>(_tSub)->getPrice());
        }
    };

    class Billboard : public Observer
    {
    public:
        Billboard(Stock *stock) : Observer(stock) {}
        void display(int v) const
        {
            std::cout << "Billboard: " << v << std::endl;
        }

        void update() override
        {
            display(static_cast<Stock *>(_tSub)->getPrice());
        }
    };

    int Stock::getPrice()
    {
        std::unique_lock<std::mutex> lock(_mutex_p);
        return _nPrice;
    }

    void Stock::setPrice(int v)
    {
        std::unique_lock<std::mutex> lock(_mutex_p);
        _nPrice = v;
        std::cout << "Stock modify!" << std::endl;
        this->notify();
    }

    void Stock::attach(Observer *o)
    {
        std::unique_lock<std::mutex> lock(_mutex_list);
        std::cout << "Observer attach: " << __PRETTY_FUNCTION__<<std::endl;
        _listObserver.push_back(o);
    }

    void Stock::detach(Observer *o)
    {
        std::unique_lock<std::mutex> lock(_mutex_list);
        std::cout << "Observer detach: " << __PRETTY_FUNCTION__<<std::endl;
        _listObserver.remove(o);
    }

    void Stock::notify()
    {
        std::unique_lock<std::mutex> lock(_mutex_list);
        for (auto observer : _listObserver)
        {
            observer->update();
        }
    }

}

using namespace Pattern;
namespace  Observer{
    void run(){
        std::cout << "*********************** Observer Pattern Demo ***********************" << std::endl;
        Stock stock;
        Monitor monitor{&stock};
        Billboard billboard{&stock};
        stock.setPrice(10);
        stock.setPrice(20);
        stock.attach(&monitor);
        stock.setPrice(50);
        stock.detach(&monitor);
        stock.setPrice(100);
    }
}
