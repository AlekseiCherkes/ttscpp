#ifndef ENGINE_HPP
#define ENGINE_HPP

//--------------------------------------------------------------------------------------------------

#include "foundation/memory.hpp"
#include "foundation/log.hpp"

//--------------------------------------------------------------------------------------------------

namespace tts { namespace engine {

//--------------------------------------------------------------------------------------------------

class Processor;

//--------------------------------------------------------------------------------------------------

class Configurator
{
public:
    struct ProcessorInfo
    {
    };

    struct ResourceInfo
    {
    };

    virtual size_t processorCount() const = 0;
    virtual const ProcessorInfo* getProcessor(size_t index) const = 0;

    virtual size_t resourceCount() const = 0;
    virtual const ResourceInfo* getRecource(size_t index) const = 0;
};

//--------------------------------------------------------------------------------------------------

/// Holder of all TTS subsystems.
class Engine
{
public:
	static Engine& instance();

	void init();
	void release();

    void config(const Configurator* configurator);

private:
    //-- Создание синглтона не вызывает выделение динамической памяти.
    //-- Первые аллокации осуществляются в методе init(),
    //-- Полное освобождение в release().
	Engine();
	~Engine();

	HeapAllocator m_allocator;

    ProxyAllocator m_mainAllocator; ///< allocates memory for all engine subsystems
                                    ///< the rest of allocators use this one for all allocation

    ProxyAllocator m_logAllocator;  ///< allocates memory for log subsystem
};

//--------------------------------------------------------------------------------------------------
}} // tts::engine

#endif // ENGINE_HPP