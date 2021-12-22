#pragma once

template < typename T >
class Singleton
{
	static T* gSingleton;
	Singleton(const Singleton& r) = delete;
	Singleton& operator =(const Singleton& r) = delete;
public:
	static inline T* ref() {
		if (!gSingleton)
		{
			gSingleton = new T;
		}
		return gSingleton;
	}
};

template < typename T >
T* Singleton<T>::gSingleton = 0;

template < typename T >
class Singletons : protected Singleton<T> {
public:
	static T* ref() { return Singleton<T>::ref(); }
};