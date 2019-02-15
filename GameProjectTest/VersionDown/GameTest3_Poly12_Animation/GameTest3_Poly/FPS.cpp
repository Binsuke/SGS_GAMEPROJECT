#include "FPS.h"

FPS::FPS() :time(0), frame(0),fFlg(false),deltaFlg(false)
{
	//sprintf_s(str, strlen(str), "FPS=");
	time = timeGetTime();
}


void FPS::Run()
{
	frame++;
	if (timeGetTime() - time > 1000)
	{
		time = timeGetTime();
		Delta = frame;
		frame = 0;
		deltaFlg = true;
	}
}

static DWORD prevTime;
void FPS::PrintFps(HWND hWnd)
{
	if (!fFlg) {
		sprintf_s(str,"%s","FPS=");
		SetWindowTextA(hWnd, str);
		fFlg = true;
		prevTime = timeGetTime();
	}
	
	/*if (timeGetTime() - time > 1000)
	{
		sprintf_s(str, "fps=%d", frame);
		SetWindowTextA(hWnd, str);
	}*/

	/*if (timeGetTime() - prevTime < 60000) {
		sprintf_s(str, "fps=%d", timeGetTime() - prevTime);
		SetWindowTextA(hWnd, str);
	}*/

}

float FPS::GetDeltaTime()
{
	if (deltaFlg) {
		float tmp = 1.0f / Delta;

		return tmp;
	}
	
	return 0;
}


