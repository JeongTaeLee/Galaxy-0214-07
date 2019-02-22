#pragma once
#include "GameResult.h"
class GameVictroy :
	public GameResult
{
public:
	GameVictroy();
	virtual ~GameVictroy();

	virtual void Init()	override;
};

