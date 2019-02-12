#include "DXUT.h"
#include "InputManager.h"


InputManager::InputManager()
	:vOldMousePos(0.f,0.f), vNowMousePos(0.f,0.f), 
	vMouseGap(0.f, 0.f), bMouseClip(false)
{
	memset(bNowKey, false, sizeof(bool) * 256);
	memset(bOldKey, false, sizeof(bool) * 256);
}


InputManager::~InputManager()
{
}

void InputManager::Update()
{
	memcpy(bOldKey, bNowKey, sizeof(bool) * 256);
	memset(bNowKey, false, sizeof(bool) * 256);

	for (int i = 0; i < 256; ++i)
	{
		if (GetAsyncKeyState(i))
			bNowKey[i] = true;
	}

	vOldMousePos = vNowMousePos;

	POINT pt = { 0 };
	GetCursorPos(&pt);
	ScreenToClient(g_hwnd, &pt);
	
	vNowMousePos = Vector2(pt.x, pt.y);
	//DEBUG_LOG(vNowMousePos.x << " " << vNowMousePos.y);
		
	MouseGapProcess();
}

void InputManager::MouseGapProcess()
{
	if (bMouseClip)
	{
		vMouseGap = vNowMousePos - Vector2(WINSIZEX / 2, WINSIZEY / 2);

		POINT pt = { WINSIZEX / 2, WINSIZEY / 2 };
		ClientToScreen(g_hwnd, &pt);

		SetCursorPos(pt.x, pt.y);
	}
	else
		vMouseGap = vNowMousePos - vOldMousePos;
}

void InputManager::SetMouseClip(bool _bMouseClip)
{
	if (_bMouseClip)
	{
		bMouseClip = _bMouseClip;

		POINT pt = { WINSIZEX / 2, WINSIZEY / 2 };
		ClientToScreen(g_hwnd, &pt);

		SetCursorPos(pt.x, pt.y);

		vNowMousePos = Vector2(WINSIZEX / 2, WINSIZEY / 2);
		vOldMousePos = Vector2(WINSIZEX / 2, WINSIZEY / 2);
		vMouseGap = Vector2(0.f, 0.f);
	}
	else
		bMouseClip = _bMouseClip;
}
