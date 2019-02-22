#pragma once
#include "GameResult.h"
class GameOver :
	public GameResult
{
public:
	GameOver();
	virtual ~GameOver();

	virtual void Init()	override;
};

