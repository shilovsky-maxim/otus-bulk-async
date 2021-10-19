#include "default_block_factory.h"

DefaultBlockFactory::DefaultBlockFactory(size_t capacity)
: m_capacity(capacity)
{
}

IBlockPtr DefaultBlockFactory::makeStaticBlock() const
{
    return std::make_unique<StaticBlock>(m_capacity);
}

IBlockPtr DefaultBlockFactory::makeDynamicBlock() const
{
    return std::make_unique<DynamicBlock>();
}
