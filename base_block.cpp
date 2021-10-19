#include "base_block.h"

bool BaseBlock::addItem(IItemPtr item)
{
    if (isFull())
        return false;
    m_items.emplace_back(std::move(item));
    return true;
}

void BaseBlock::printContent(std::ostream& out) const
{
    bool isFirst = true;
    for (const auto& item : m_items)
    {
        if (!item)
            continue;
        if (!isFirst)
            out << ", ";
        item->printContent(out);
        isFirst = false;
    }
}

std::vector<IItemPtr> BaseBlock::getItems() const
{
    return m_items;
}
