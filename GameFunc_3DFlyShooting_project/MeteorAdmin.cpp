#include "DXUT.h"
#include "MeteorAdmin.h"

//Manager
#include "ObjectManager.h"

//Component

//GameObject
#include "Meteor.h"
#include "PlayerAirplane.h"

#include "Func.h"

MeteorAdmin::MeteorAdmin()
	:lpPlayer(nullptr)
{
}


MeteorAdmin::~MeteorAdmin()
{
}

void MeteorAdmin::Init()
{
}

void MeteorAdmin::Update()
{
}

void MeteorAdmin::SetPlayer(PlayerAirplane* _lpPlayer)
{
	lpPlayer = _lpPlayer;
}

void MeteorAdmin::CreateMeteor()
{
	for (int i = 0; i < 1000; ++i)
	{
		Meteor* lpMeteor = OBJECT.AddObject<Meteor>();
		lpMeteor->SetMeteor((MeteorType)GetRandomNumber((int)MeteorType::E_METEOR_01, (int)MeteorType::E_METEOR_03));
		lpMeteor->SetPlayer(lpPlayer);

		float fRange = 20000;

		Vector3 vStartPos(Vector3(0.f, 0.f, 0.f) + Vector3(-fRange, -fRange, -fRange));
		Vector3 vEndPos(Vector3(0.f, 0.f, 0.f) + Vector3(fRange, fRange, fRange));

		Vector3 vCreatePos = Vector3(0.f, 0.f, 0.f);
		bool	reLocate = false;

		while (true)
		{
			vCreatePos = GetRandomNumber(vStartPos, vEndPos);
			reLocate = false;

			if (500.f > GetLengthVector3(lpPlayer->transform->worldPos, vCreatePos))
			{
				reLocate = true;
				continue;
			}

			for (auto Iter : vMeteor)
			{
				if (Iter == lpMeteor)
					continue;

				if (500.f > GetLengthVector3(Iter->transform->worldPos, vCreatePos))
				{
					reLocate = true;
					break;
				}
			}

			if (!reLocate)
			{
				lpMeteor->transform->pos = vCreatePos;
				vMeteor.push_back(lpMeteor);
				break;
			}
		}
	}
}
