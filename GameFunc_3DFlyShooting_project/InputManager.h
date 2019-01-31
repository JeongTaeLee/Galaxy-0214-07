#pragma once
#include "singleton.h"

class InputManager
	:public singleton<InputManager>
{
private:
	bool bNowKey[256];
	bool bOldKey[256];

public:
	InputManager();
	~InputManager();

	void Update();

	bool GetUpKey(int i) { return (!bNowKey[i] && bOldKey[i]); }
	bool GetDownKey(int i) { return (bNowKey[i] && !bOldKey[i]); }
	bool GetPressKey(int i) { return (bNowKey[i] && bOldKey[i]); }
};

#define INPUT InputManager::GetInst()

#define KEYUP(i) INPUT.GetUpKey(i)
#define KEYDOWN(i) INPUT.GetDownKey(i)
#define KEYPRESS(i) INPUT.GetPressKey(i)

