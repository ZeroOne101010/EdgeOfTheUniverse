#define GLEW_STATIC
#include <Windows.h>
#include "Application.h"
#include "ByteHelper.h"
#include "ChunkThread.h"
//#include <thread>
//
//class A
//{
//public:
//	int* value;
//	A();
//
//	void updateA();
//};
//
//A::A()
//{
//	value = new int[10];
//	for (int x = 0; x < 10; x++)
//	{
//		value[x] = x;
//	}
//}
//
//void A::updateA()
//{
//	if (value != nullptr)
//	{
//		int number = 0;
//		for (int x = 0; x < 10; x++)
//		{
//			number += value[x];
//		}
//		std::cout << number << std::endl;
//	}
//}
//
//A a;
//
//std::mutex m;
//
//void threadUpdate()
//{
//	std::this_thread::sleep_for(std::chrono::seconds(2));
//	m.lock();
//	delete a.value;
//	a.value = nullptr;
//	std::this_thread::sleep_for(std::chrono::seconds(2));
//	m.unlock();
//}

int main()
{
	//std::thread t1(threadUpdate);

	//while (true)
	//{
	//	m.lock();
	//	a.updateA();
	//	m.unlock();
	//}

	Application* application = new Application();
	application->GameLoop();
	delete application;
	return 0;
}
