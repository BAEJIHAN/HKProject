#include "RockDown.h"
#include "Engine.h"

void CRockDown::DOWNStart()
{
}

void CRockDown::DOWNStay()
{
	float DeltaTime = CEngine::GetInst()->GetDeltaTime();
	m_Sprite->AddRelativeRotationZ(RotSpeed * DeltaTime);

	m_Sprite->AddRelativePos(0, -600.f * DeltaTime, 0);


}

void CRockDown::DOWNEnd()
{
}

void CRockDown::LEFTStart()
{
	
	RotSpeed = 1200.f;
	SetCollisionProfile("PlayerAttack");
}

void CRockDown::LEFTStay()
{
	float DeltaTime = CEngine::GetInst()->GetDeltaTime();
	m_Sprite->AddRelativeRotationZ(RotSpeed * DeltaTime);

	m_Sprite->AddRelativePos(-2000.f*DeltaTime, -100.f * DeltaTime, 0);
}

void CRockDown::LEFTEnd()
{
}

void CRockDown::RIGHTStart()
{
	RotSpeed = 1200.f;
	SetCollisionProfile("PlayerAttack");
}

void CRockDown::RIGHTStay()
{
	float DeltaTime = CEngine::GetInst()->GetDeltaTime();
	m_Sprite->AddRelativeRotationZ(RotSpeed * DeltaTime);

	m_Sprite->AddRelativePos(2000.f * DeltaTime, -100.f * DeltaTime, 0);
}

void CRockDown::RIGHTEnd()
{
}