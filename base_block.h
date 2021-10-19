#pragma once

#include "block.h"
#include <vector>

class BaseBlock : public IBlock
{
public:
    BaseBlock() = default;
    virtual ~BaseBlock() override = default;

    bool addItem(IItemPtr item) override;
    void printContent(std::ostream& out) const override;
    std::vector<IItemPtr> getItems() const override;
protected:
    std::vector<IItemPtr> m_items;
};