#pragma once
#include "singleton.h"
class TimeManager :
	public singleton<TimeManager>
{
private:	
	bool bFastTime;
public:
	TimeManager();
	virtual ~TimeManager();

	void SetFastTime(bool _bFastTime)	{ bFastTime = _bFastTime; };
	bool GetFastTime()					{ return bFastTime; }

	float GetElapsedTime() { return bFastTime ? (DXUTGetElapsedTime() * 2) : DXUTGetElapsedTime(); }
};

#define TIME TimeManager::GetInst()
#define Et TIME.GetElapsedTime()
