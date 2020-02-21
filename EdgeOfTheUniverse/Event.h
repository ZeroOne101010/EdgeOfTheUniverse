#pragma once
#include <vector>
template<class T>
class Event
{
public:
	Event();
	~Event();
	void operator+=(T method);
	void operator()();
private:
	std::vector<T> delegates;
};
