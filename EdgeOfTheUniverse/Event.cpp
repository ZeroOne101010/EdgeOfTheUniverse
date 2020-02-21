#include "Event.h"
template<class T>
Event<T>::Event()
{

}

template<class T>
Event<T>::~Event()
{
	for (int i = 0; i < delegates.size(); i++)
		delete delegates[i];
	delegates.clear();
}

template<class T>
void Event<T>::operator+=(T method)
{
	delegates.push_back(method);
}

template<class T>
void Event<T>::operator()()
{
	for (int i = 0; i < delegates.size(); i++)
	{
		delegates[i]();
	}
}


