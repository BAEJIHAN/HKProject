#include "FKHeadRight.h"
#include "FKHeadRightAnimation.h"
#include "Input.h"
#include "Engine.h"
#include "../Object/BMonAttack.h"
#include "Resource/Sound/Sound.h"

void CFKHeadRight::IDLEStart()
{

	
		ChangeAnimation("FKHeadIdleRight");
	




}

void CFKHeadRight::IDLEStay()
{
}

void CFKHeadRight::IDLEEnd()
{
}

void CFKHeadRight::HITStart()
{
	HitTime = 0;

	
	ChangeAnimation("FKHeadHitRIght");
	
}

void CFKHeadRight::HITStay()
{
	float DeltaTime = CEngine::GetInst()->GetDeltaTime();
	HitTime += DeltaTime;

	if (HitTime >= 0.2)
	{
		HitTime = 0;
		ChangeState("Idle");
	}
}

void CFKHeadRight::HITEnd()
{
	HitTime = 0;
}

void CFKHeadRight::DEATHStart()
{
	HitTime = 0;
	IsDead = true;
	ChangeAnimation("FKHeadDeathRight");
	m_Sprite->SetRelativeScale(450, 380, 1.f);
}

void CFKHeadRight::DEATHStay()
{
	float DeltaTime = CEngine::GetInst()->GetDeltaTime();
	HitTime += DeltaTime;

	if (HitTime <= 1)
	{
		m_Sprite->AddRelativePos(Vector3(150.f, 150.f, 0.f) * DeltaTime);
	}
	else if (HitTime <= 2)
	{
		m_Sprite->AddRelativePos(Vector3(150.f, -150.f, 0.f) * DeltaTime);
	}
}

void CFKHeadRight::DEATHEnd()
{

}