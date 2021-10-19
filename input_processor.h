#pragma once

#include <iostream>
#include "block_factory.h"
#include "block_processor.h"
#include "input_provider.h"

class IState;
using IStatePtr = std::unique_ptr<IState>;

class IStateFactory;
using IStateFactoryPtr = std::unique_ptr<IStateFactory>;

class InputProcessor final
{
public:
    InputProcessor(IBlockFactoryPtr blockFactory, IBlockProcessorPtr processor);
    ~InputProcessor();

    void processInput(IInputProviderPtr in);

private:
    IStatePtr m_state;
    IStateFactoryPtr m_stateFactory;
};
using InputProcessorPtr = std::shared_ptr<InputProcessor>;
