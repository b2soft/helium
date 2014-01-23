#pragma once

#include "Head.h"


enum STATE
{
	MENU, PLAY, GAMEOVER, PAUSE
};

class CFsm
{
public:
	CFsm();
	~CFsm();
	STATE GetState();
	void SetState(STATE state);

private:
	STATE m_eState;

};