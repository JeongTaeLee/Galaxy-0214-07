#pragma once
#include "singleton.h"

class InputManager
	:public singleton<InputManager>
{
private:
	bool bNowKey[256];
	bool bOldKey[256];

	Vector2 vOldMousePos;
	Vector2 vNowMousePos;
	Vector2 vMouseGap;

	bool bMouseClip;
	bool bMouseShow;
public:
	InputManager();
	~InputManager();

	void Update();
	void MouseGapProcess();

	const Vector2 & GetMousePos() { return vNowMousePos; }
	const Vector2 & GetMouseGap() { return vMouseGap; }

	void SetMouseClip(bool _bMouseClip);
	void SetShowMouse(bool _bMouseShow);
	
	void SwitchShowMouse();
	void SwitchClipMouse();

	bool GetUpKey(int i) { return (!bNowKey[i] && bOldKey[i]); }
	bool GetDownKey(int i) { return (bNowKey[i] && !bOldKey[i]); }
	bool GetPressKey(int i) { return (bNowKey[i] && bOldKey[i]); }
};

#define INPUT InputManager::GetInst()

#define KEYUP(i) INPUT.GetUpKey(i)
#define KEYDOWN(i) INPUT.GetDownKey(i)
#define KEYPRESS(i) INPUT.GetPressKey(i)

