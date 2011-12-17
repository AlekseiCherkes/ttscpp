#ifndef PROCESSOR_REGISTRATOR_HPP
#define PROCESSOR_REGISTRATOR_HPP

#include "processor/processor_namespace.hpp"

namespace tts { namespace engine {

/// Utility class for processor automatic registration in the ProcessorNamespace
class ProcessorRegistrator
{
public:
	ProcessorRegistrator(ProcessorNamespace& processorNamespace, const char* processorName)
	{
		processorNamespace.registerProcessor(processorName);
		x = 10;
	}
	int x;
};

}} // namespace

#endif // PROCESSOR_REGISTRATOR_HPP