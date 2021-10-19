#pragma once

#include <iostream>
#include "block.h"

class IBlockProcessor
{
public:
    IBlockProcessor() = default;
    virtual ~IBlockProcessor() = default;

    virtual void process(IBlockPtr block) = 0;
};
using IBlockProcessorPtr = std::shared_ptr<IBlockProcessor>;
