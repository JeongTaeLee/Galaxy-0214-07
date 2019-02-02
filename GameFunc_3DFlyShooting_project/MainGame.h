#pragma once

class SkyBox;

class MainGame
{
private:
public:
	MainGame();
	virtual ~MainGame();

	void Init();
	void Release();
	void Update();
	void Render();
	
	void LostDevice();
	void ResetDevice();
};

