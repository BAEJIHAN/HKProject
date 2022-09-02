#include "FKHeadLeft.h"
#include "FKHeadLeftAnimation.h"
#include "Input.h"
#include "Engine.h"
#include "../Object/BMonAttack.h"
#include "Resource/Sound/Sound.h"

void CFKHeadLeft::IDLEStart()
{
	ChangeAnimation("FKHeadIdleLeft");
}

void CFKHeadLeft::IDLEStay()
{
}

void CFKHeadLeft::IDLEEnd()
{
}

void CFKHeadLeft::HITStart()
{
	HitTime = 0;

	
	ChangeAnimation("FKHeadHitLeft");
	
	
}

void CFKHeadLeft::HITStay()
{
	float DeltaTime = CEngine::GetInst()->GetDeltaTime();
	HitTime += DeltaTime;

	if (HitTime >= 0.2)
	{
		HitTime = 0;
		ChangeState("Idle");
	}
}

void CFKHeadLeft::HITEnd()
{
	HitTime = 0;
}

void CFKHeadLeft::DEATHStart()
{
	HitTime = 0;
	IsDead = true;
	ChangeAnimation("FKHeadDeathLeft");
	m_Sprite->SetRelativeScale(450, 380, 1.f);
}

void CFKHeadLeft::DEATHStay()
{
	float DeltaTime = CEngine::GetInst()->GetDeltaTime();
	HitTime += DeltaTime;

	if (HitTime <= 1)
	{
		m_Sprite->AddRelativePos(Vector3(-150.f, 150.f, 0.f) * DeltaTime);
	}
	else if (HitTime <= 2)
	{
		m_Sprite->AddRelativePos(Vector3(-150.f, -150.f, 0.f) * DeltaTime);
	}
}

void CFKHeadLeft::DEATHEnd()
{
}
