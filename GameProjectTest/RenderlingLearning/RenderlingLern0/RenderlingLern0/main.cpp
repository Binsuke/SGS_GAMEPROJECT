// include
#if defined(DEBUG) || defined(_DEBUG)
#incldue <crtpbg.h>
#endif//defined(DEBUG) || defined(_DEBUG)


#include "DemoApp.h"
#include "DemoNode.h"

// main entry point


int main(int argc, char** argv) {
#if defined (DEBUG) || defined(_DEBUG)
	//debug mode only  memory check activetion
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif //defined(DEBUG) || defined(_DEBUG)

	int ret = 0;
	{
	}


}