#include <iostream>
#include <memory>

namespace pattern
{

    // 新目标接口
    class NewTarget
    {
    public:
        virtual void newRequest() = 0;
    };

    // 旧被适配的类
    class OldAdaptee
    {
    public:
        void oldRequest()
        {
            std::cout << "OldAdaptee's oldRequest" << std::endl;
        }
    };

    // 适配器类
    class Adapter : public NewTarget
    {
    private:
        std::unique_ptr<OldAdaptee> oldAdaptee;

    public:
        Adapter() : oldAdaptee(std::make_unique<OldAdaptee>()) {}

        void newRequest() override
        {
            oldAdaptee->oldRequest();
        }
    };

} // namespace pa

using namespace pattern;
namespace Adapter
{

    void run()
    {
        std::cout << "*********************** Adapter Pattern Demo ***********************" << std::endl;
        std::unique_ptr<NewTarget> target = std::make_unique<pattern::Adapter>();

        target->newRequest(); // 输出：OldAdaptee's oldRequest
    }
}