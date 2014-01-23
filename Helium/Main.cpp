#include "Head.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR lpCmdLine, int nShowCmd)
{
	
	srand(1);
	
 // DEBUG
	_CheckLeaks;
	CSystem::Initialize(hInstance);

	//of.close();
	
	return 0;
}