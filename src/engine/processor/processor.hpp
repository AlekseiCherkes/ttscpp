#ifndef PROCESSOR_HPP
#define PROCESSOR_HPP

//--------------------------------------------------------------------------------------------------

namespace tts { namespace engine {

//--------------------------------------------------------------------------------------------------

class TokenList;

//--------------------------------------------------------------------------------------------------

/// Base class for all processors.
class Processor
{
public:
    Processor()
    {
    }

    virtual ~Processor()
    {
    }

    /// Execute the processor.
    virtual void run(TokenList& tl) = 0;
};

//--------------------------------------------------------------------------------------------------
}} // namespace

#endif // PROCESSOR_HPP