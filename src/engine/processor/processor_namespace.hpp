#ifndef PROCESSOR_REGISTER_HPP
#define PROCESSOR_REGISTER_HPP

namespace tts { namespace engine {

/// Class that represents processor namespace in the processor register
class ProcessorNamespace
{
public:
	ProcessorNamespace(const char* name, ProcessorNamespace* parent) 
	: m_name(name)
	, m_parent(parent)
	{
		if(parent) parent->registerNamespace(this, name);

		for(size_t i = 0; i < 16; ++i)
		{
			m_processorRecords[i].name = 0;
		}

		for(size_t i = 0; i < 16; ++i)
		{
			m_namespaceRecords[i].name = 0;
			m_namespaceRecords[i].ns = 0;
		}
	}

	virtual ~ProcessorNamespace()
	{
	}

	const char* name() { return m_name; }

	bool registerProcessor(const char* name)
	{
		for(size_t i = 0; i < 16; ++i)
		{
			if(m_processorRecords[i].name == 0)
			{
				m_processorRecords[i].name = name;
				break;
			}
		}
		return true;
	}

	void registerNamespace(ProcessorNamespace* ns, const char* name)
	{
		for(size_t i = 0; i < 16; ++i)
		{
			if(m_namespaceRecords[i].name == 0)
			{
				m_namespaceRecords[i].name = name;
				m_namespaceRecords[i].ns = ns;
				break;
			}
		}
	}

private:

	//typedef (Processor* ProcessorFactory)();

	struct ProcessorRecord
	{
		const char* name;
		//ProcessorFactory factory;
	};

	struct NamespaceRecord
	{
		const char* name;
		ProcessorNamespace* ns;
	};

	static const int processorCount = 16;
	static const int namespaceCount = 16;

	ProcessorRecord           m_processorRecords[processorCount];
	NamespaceRecord           m_namespaceRecords[namespaceCount];
	const char*               m_name;
	const ProcessorNamespace* m_parent;
};

}} // namespace

#endif // PROCESSOR_REGISTER_HPP