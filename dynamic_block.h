#pragma once

#include "base_block.h"

class DynamicBlock final : public BaseBlock
{
public:
    DynamicBlock() = default;
    virtual ~DynamicBlock() override = default;

    bool isFull() const override;
};
