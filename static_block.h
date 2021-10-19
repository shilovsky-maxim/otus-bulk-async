#pragma once

#include "base_block.h"
#include <vector>

class StaticBlock final : public BaseBlock
{
public:
    StaticBlock(size_t capacity);
    virtual ~StaticBlock() override = default;

    bool isFull() const override;
private:
    size_t m_capacity{0};
};
