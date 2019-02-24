#include "DXUT.h"
#include "Stage01.h"

//Manager
#include "ObjectManager.h"
#include "ImageManager.h"
#include "GameManager.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "SoundManager.h"

//GameObject
#include "PlayerAirplane.h"
#include "MonsterAirPlane.h"
#include "SkyBox.h"
#include "MonsterDirector.h"
#include "MonsterCreater.h"
#include "MeteorAdmin.h"
#include "GameVictroy.h"
#include "GameOver.h"
#include "StageMission.h"
#include "MiddleBossA.h"

Stage01::Stage01()
{
}


Stage01::~Stage01()
{
}

void Stage01::Init()
{
	INPUT.SwitchClipMouse();
	INPUT.SwitchShowMouse();

	GAMEMANAGER.Reset();

	GAMEMANAGER.iNowState = 1;
	GAMEMANAGER.iLastState = 1;

	OBJECT.AddObject<SkyBox>();
	
	GAMEMANAGER.SetMission(20);
	
	PlayerAirplane* player = OBJECT.AddObject<PlayerAirplane>();
	MonsterCreater* monster = OBJECT.AddObject<MonsterCreater>();
	MeteorAdmin* meteor = OBJECT.AddObject <MeteorAdmin>();
	
	player->SetCreater(monster);
	meteor->SetPlayer(player);
	meteor->CreateMeteor();

	SOUND.AllStop();
	SOUND.Play("IngameSound", 1);

}

void Stage01::Release()
{
	SOUND.Stop("IngameSound");

	OBJECT.Reset();
	IMAGE.Reset();
}

void Stage01::LoadingResource()
{
	SOUND.AddSound("Explosion", "./rs/Sound/Explosion.wav");
	SOUND.SetVol("Explosion", 90);

	SOUND.AddSound("IngameSound", "./rs/Sound/IngameSound.wav");
	SOUND.SetVol("IngameSound", 90);

	SOUND.AddSound("PlayerFire", "./rs/Sound/PlayerFire.wav");
	SOUND.SetVol("PlayerFire", 85);

	SOUND.AddSound("GameOver", "./rs/Sound/GameOver.wav");

	SOUND.AddSound("MissileFire", "./rs/Sound/MissileFire.wav");

	SOUND.AddSound("LockOnedWarning", "./rs/Sound/Warning.wav");
	SOUND.SetVol("LockOnedWarning", 85);
	/****OBJ****/
	
	//Player
	IMAGE.LoadObjFile("PlayerAirPlane", "./rs/obj/Player/PlayerAirPlane.obj", true);
	
	//PlayerDirctor
	IMAGE.LoadObjFile("PlayerDirector", "./rs/obj/PlayerDirector/PlayerDirector.obj", true);

	//Stage 
	IMAGE.LoadObjFile("SkyBox_Sphere", "./rs/obj/SkyBox_Sphere/Stage.obj", true);

	//Bullet
	IMAGE.LoadObjFile("BasicBullet", "./rs/obj/Bullet/Bullet.obj", true);
	IMAGE.LoadObjFile("Missile", "./rs/obj/Missile/C.obj", true);

	//Monster
	IMAGE.LoadObjFile("MonsterA", "./rs/obj/MonsterA/MonsterA.obj", true);
	IMAGE.LoadObjFile("MonsterA2", "./rs/obj/MonsterA2/MonsterA2.obj", true);
	IMAGE.LoadObjFile("MonsterB", "./rs/obj/MonsterB/MonsterB.obj", true);
	IMAGE.LoadObjFile("MonsterB2", "./rs/obj/MonsterB2/MonsterB2.obj", true);

	IMAGE.LoadObjFile("BossA", "./rs/obj/BossA/B.obj", true);
	IMAGE.LoadObjFile("BossB", "./rs/obj/BossB/C.obj", true);

	IMAGE.LoadObjFile("MiddleBossA", "./rs/obj/MiddleBossA/A_.obj", true);
	IMAGE.LoadObjFile("MiddleBossB", "./rs/obj/MiddleBossB/A.obj", true);

	//Meteor
	IMAGE.LoadObjFile("Meteor", "./rs/obj/Meteor/Meteor.obj", true);
	/****png****/
	
	//EffectA
	IMAGE.LoadTextures("EffectA%d", "./rs/Sprite/Effect_A/(%d).png", 1, 14, true);

	//UI
	IMAGE.LoadTexture("Aim", "./rs/Sprite/UI/Aim.png", true);
	IMAGE.LoadTexture("LockOnEnemyCircle", "./rs/Sprite/UI/LockOnCircle.png", true);
	IMAGE.LoadTexture("NoneLockOnEnemyCircle", "./rs/Sprite/UI/NoneLockOnCircle.png", true);
	IMAGE.LoadTexture("LockOned", "./rs/Sprite/UI/LockOned.png", true);
	IMAGE.LoadTexture("LifeBar", "./rs/Sprite/UI/LifeBar.png", true);
	IMAGE.LoadTexture("LifeGauge", "./rs/Sprite/UI/LifeGauge.png", true);

	IMAGE.LoadTextures("SpeedEffect%d", "./rs/Sprite/Speed/%d.png", 1, 3, true);
	IMAGE.LoadTexture("PlayerHitEffect", "./rs/Sprite/UI/PlayerHitEffect.png", true);

	IMAGE.LoadTexture("GameVictory", "./rs/Sprite/UI/GameVictory.png", true);
	IMAGE.LoadTexture("GameOver", "./rs/Sprite/UI/GameOver.png", true);

	IMAGE.LoadTexture("Replay", "./rs/Sprite/UI/Replay.png", true);
	IMAGE.LoadTexture("NextStage", "./rs/Sprite/UI/NextStage.png", true);
	IMAGE.LoadTexture("MainScreen", "./rs/Sprite/UI/MainScreen.png", true);
	IMAGE.LoadTexture("StageMission", "./rs/Sprite/UI/StageMission.png", true);

	IMAGE.LoadTexture("MiddleBossAAppear", "./rs/Sprite/UI/1Stage_MidBoss.png", true);
	IMAGE.LoadTexture("BossAAppear", "./rs/Sprite/UI/1Stage_Boss.png", true);

	IMAGE.LoadTexture("MiddleBossBAppear", "./rs/Sprite/UI/2Stage_MidBoss.png", true);
	IMAGE.LoadTexture("BossBAppear", "./rs/Sprite/UI/2Stage_FinalBoss.png", true);

	IMAGE.LoadTexture("MachineGunUI", "./rs/Sprite/UI/MachingGunUI.png", true);
	IMAGE.LoadTexture("MissileUI", "./rs/Sprite/UI/MissileUI.png", true);

	IMAGE.LoadTexture("BossHpBar", "./rs/Sprite/UI/BossHpBar.png", true);
	IMAGE.LoadTexture("BossHpGauge", "./rs/Sprite/UI/BossHpGauge.png", true);

	IMAGE.LoadTextures("LoseEnding%d", "./rs/Sprite/Ending_Lose/(%d).png", 1, 51, true);
	IMAGE.LoadTextures("WinEnding%d", "./rs/Sprite/Ending_Win/(%d).png", 1, 51, true);

	bLoadingComplete = true;
}
