#pragma once
#include "singleton.h"
class TimeManager :
	public singleton<TimeManager>
{
private:	
public:
	TimeManager();
	virtual ~TimeManager();
};

#define TIME TimeManager::GetInst()

