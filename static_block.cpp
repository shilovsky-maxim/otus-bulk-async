#include "static_block.h"

StaticBlock::StaticBlock(size_t capacity)
: m_capacity(capacity)
{
}

bool StaticBlock::isFull() const
{
    return m_capacity <= m_items.size();
}
