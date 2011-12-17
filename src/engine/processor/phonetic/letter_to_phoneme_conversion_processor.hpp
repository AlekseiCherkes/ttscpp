#ifndef LETTER_TO_PHONEME_CONVERSION_PROCESSOR_HPP
#define LETTER_TO_PHONEME_CONVERSION_PROCESSOR_HPP

#include "processor/processor.hpp"

//--------------------------------------------------------------------------------------------------

namespace tts { namespace engine {

//--------------------------------------------------------------------------------------------------

class TokenList;

//--------------------------------------------------------------------------------------------------

/// Base class for all processors.
class LettertoPhonemeConversionProcessor
{
public:
    /// Execute the processor.
    virtual void run(TokenList& tl);
};

//--------------------------------------------------------------------------------------------------
}} // namespace

#endif // LETTER_TO_PHONEME_CONVERSION_PROCESSOR_HPP