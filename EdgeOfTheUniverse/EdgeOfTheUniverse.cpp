#define GLEW_STATIC
#include <Windows.h>
#include "Application.h"
#include "ByteHelper.h"
#include "ChunkThread.h"

int main()
{
	Application* application = new Application();
	application->GameLoop();
	delete application;
	return 0;
}
