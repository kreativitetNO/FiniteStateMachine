#include <iostream>

#include "MyFunctionalClass.h"

class SomeRealization : public ISomeInterface
{
    public:
    void someInterfaceMethod() override
    {
        std::cout << "Calling ISomeInterface::someInterfaceMethod()" << std::endl;
    }
};

int main()
{
    SomeRealization myService;

    MyFunctionalClass mfc {myService};

    mfc.startStateMachine();

    mfc.stateMethod();
    mfc.stateSwappingMethod();
    mfc.stateMethod();
    mfc.stateSwappingMethod();
    mfc.stateMethod();
    mfc.stateSwappingMethod();
    mfc.stateMethod();
    mfc.stateSwappingMethod();
    mfc.stateMethod();
    mfc.stateSwappingMethod();
    mfc.stateMethod();
}