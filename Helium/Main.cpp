#include "Head.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR lpCmdLine, int nShowCmd)
{
	
 // DEBUG
	_CheckLeaks;
	CSystem::Initialize(hInstance);

	
	return 0;
}