#pragma once

#include "static_block.h"
#include "dynamic_block.h"

class IBlockFactory
{
public:
    IBlockFactory() = default;
    virtual ~IBlockFactory() = default;

    virtual IBlockPtr makeStaticBlock() const = 0;
    virtual IBlockPtr makeDynamicBlock() const = 0;
};
using IBlockFactoryPtr = std::shared_ptr<IBlockFactory>;
