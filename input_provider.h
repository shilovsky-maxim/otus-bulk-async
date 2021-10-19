#pragma once

#include <string>
#include <memory>

class IInputProvider
{
public:
    IInputProvider() = default;
    virtual ~IInputProvider() = default;

    virtual bool getLine(std::string& line) = 0;
};
using IInputProviderPtr = std::shared_ptr<IInputProvider>;
