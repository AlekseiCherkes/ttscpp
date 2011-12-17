#ifndef ACOUSTIC_PROCESSOR_HPP
#define ACOUSTIC_PROCESSOR_HPP

//--------------------------------------------------------------------------------------------------

#include "processor/processor.hpp"

//--------------------------------------------------------------------------------------------------

namespace tts { namespace engine {

//--------------------------------------------------------------------------------------------------

/// Base class for all processors.
class AcousticProcessor : Processor
{
public:
    virtual void run(TokenList& tl);
private:	
};

//--------------------------------------------------------------------------------------------------
}} // namespace

#endif // ACOUSTIC_PROCESSOR_HPP