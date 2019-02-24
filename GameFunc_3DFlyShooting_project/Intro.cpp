#include "DXUT.h"
#include "Intro.h"

#include "ObjectManager.h"
#include "ImageManager.h"
#include "SoundManager.h"

#include "IntroAnimation.h"

Intro::Intro()
{
}


Intro::~Intro()
{
}

void Intro::Init()
{
	SOUND.Play("IntroSound", 1);
	OBJECT.AddObject<IntroAnimation>();
}

void Intro::Release()
{
	SOUND.Stop("IntroSound");
	OBJECT.Reset();
	IMAGE.Reset();
}

void Intro::LoadingResource()
{
	SOUND.AddSound("IntroSound", "./rs/Sound/IntroSound.wav", 1);
	//SOUND.Play()
	IMAGE.LoadTextures("Intro%d", "./rs/Sprite/Intro/(%d).png", 1, 61, false);
	bLoadingComplete = true;
}
