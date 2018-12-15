// include
#if defined(DEBUG) || defined(_DEBUG)
#include <crtdbg.h>
#endif//defined(DEBUG) || defined(_DEBUG)


#include "DemoApp.h"
#include "DemoNode.h"

// main entry point


#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"d3dcompiler.lib")
int main(int argc, char** argv) {
#if defined (DEBUG) || defined(_DEBUG)
	//debug mode only  memory check activetion
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif //defined(DEBUG) || defined(_DEBUG)

	int ret = 0;
	{
		DemoApp::Config config;
		config.title = (LPSTR)"SimpleDemo";
		config.multiSampleCount = 4;
		config.multiSampleQuality = 0;

		DemoApp app(config);
		DemoNode node;

		// setting Node
		app.SetNode(&node);

		//run application

		ret = app.Run();
	}

	return ret;
}