#ifndef ISOMEINTERFACE_H
#define ISOMEINTERFACE_H

class ISomeInterface
{
    public:
    ISomeInterface() = default;
    ISomeInterface(ISomeInterface const&&) = delete;
    ISomeInterface& operator=(ISomeInterface const&&) = delete;
    ISomeInterface(ISomeInterface&&) = delete;
    ISomeInterface& operator=(ISomeInterface&&) = delete;
    virtual ~ISomeInterface() = default;

    virtual void someInterfaceMethod() = 0;
};

#endif