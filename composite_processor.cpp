#include "composite_processor.h"

void CompositeProcessor::addProcessor(IBlockProcessorPtr processor)
{
    m_processors.emplace_back(std::move(processor));
}

void CompositeProcessor::process(IBlockPtr block)
{
    for (const auto& processor : m_processors)
    {
        if (processor)
            processor->process(block);
    }
}
