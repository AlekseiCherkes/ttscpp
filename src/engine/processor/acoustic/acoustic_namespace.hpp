#ifndef NAMESPACE_HPP
#define NAMESPACE_HPP

#include "foundation/singleton.hpp"
#include "processor/root_namespace.hpp"
#include "processor/processor_namespace.hpp"

namespace tts { namespace engine {

/// Class that represents processor namespace in the processor register
class AcousticNamespace :  public ProcessorNamespace, public Singleton<AcousticNamespace>
{
public:
	AcousticNamespace() : 
	  ProcessorNamespace("acoustic",  RootNamespace::instance())
	{
	}

	virtual ~AcousticNamespace()
	{
	}
};

}} // namespace

#endif // NAMESPACE_HPP