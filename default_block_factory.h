#pragma once

#include "block_factory.h"

class DefaultBlockFactory final: public IBlockFactory
{
public:
    DefaultBlockFactory(size_t capacity);
    virtual ~DefaultBlockFactory() override = default;

    IBlockPtr makeStaticBlock() const override;
    IBlockPtr makeDynamicBlock() const override;

private:
    size_t m_capacity{0};
};
