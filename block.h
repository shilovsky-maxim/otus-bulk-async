#pragma once

#include "item.h"
#include <vector>

class IBlock : public IItem
{
public:
    IBlock() = default;
    virtual ~IBlock() override = default;

    virtual bool addItem(IItemPtr item) = 0;
    virtual bool isFull() const = 0;
    virtual std::vector<IItemPtr> getItems() const = 0;
};
using IBlockPtr = std::shared_ptr<IBlock>;
