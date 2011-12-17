#ifndef SINGLETON_HPP
#define SINGLETON_HPP

/// Singleton implementation
template<class T>
class Singleton
{
public:
	static T* instance()
	{
		static T s_instance;
		return &s_instance;
	}
};

#endif // SINGLETON_HPP