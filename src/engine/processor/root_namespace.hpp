#ifndef ROOT_NAMESPACE_HPP
#define ROOT_NAMESPACE_HPP

#include "processor/processor_namespace.hpp"
#include "foundation/singleton.hpp"

namespace tts { namespace engine {

/// Root of the processor namespaces tree
class RootNamespace :  public ProcessorNamespace, public Singleton<RootNamespace>
{
public:
	RootNamespace()
	: ProcessorNamespace("", 0)
	{
	}

	virtual ~RootNamespace()
	{
	}
};

}} // namespace

#endif // ROOT_NAMESPACE_HPP