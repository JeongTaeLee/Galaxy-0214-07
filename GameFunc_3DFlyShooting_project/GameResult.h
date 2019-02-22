#pragma once
#include "GameObject.h"

class UIRenderer;
class Text;

class GameResult :
	public GameObject
{
protected:
	UIRenderer* lpRenderer;

	Text* lpScore;
	Text* lpKillMonster;
public:
	GameResult();
	virtual ~GameResult();

	virtual void Init()	override;
};

