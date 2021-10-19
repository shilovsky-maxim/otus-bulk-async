#pragma once

#include "block_processor.h"

class FilePrinter final : public IBlockProcessor
{
public:
    FilePrinter() = default;
    virtual ~FilePrinter() override = default;

    void process(const IBlockPtr block) override;
};
