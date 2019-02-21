#pragma once
#include "Component.h"
class Animater :
	public Component
{
private:
	std::map<std::string, std::vector<Mesh*> *> mAnimation;

	std::string sNowAni;
	std::vector<Mesh*>* vNowAni;

	int fFrameCount;

	float fFrameDelay;
	float fFrameAccrue;
public:
	Animater();
	virtual ~Animater();

	virtual void Update()	override;

public:
	void Add(const std::string& name, std::string& keys, const std::string& paths, int mn, int mx);
	void Chanage(const std::string& name);
public:
	void SetFarmeDelay(float _fFrameDelay) { fFrameDelay = _fFrameDelay; }
};

