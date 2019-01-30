#pragma once
#include "singleton.h"

class InputManager
	:public singleton<InputManager>
{
public:
	InputManager();
	~InputManager();
};

