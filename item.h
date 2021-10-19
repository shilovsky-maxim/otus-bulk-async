#pragma once

#include <memory>
#include <ostream>

/*
 * Interface class for items that could be stored in blocks, including other blocks.
 */
class IItem
{
public:
    IItem() = default;
    virtual ~IItem() = default;

    virtual void printContent(std::ostream& out) const = 0;
};
using IItemPtr = std::shared_ptr<IItem>;
