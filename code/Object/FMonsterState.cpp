#include "FMonster.h"
#include "FMonsterAnimation.h"
#include "Input.h"
#include "Engine.h"
#include "Resource/Sound/Sound.h"
#include "dummy.h"
void CFMonster::IDLEStart()
{
	
	
	if (DIR::LEFT == Dir)
	{
		ChangeAnimation("FMonIdleLeft");
		m_Sprite->SetPivot(0.35f, 0.4f, 0.f);
	}
	if (DIR::RIGHT == Dir)
	{
		ChangeAnimation("FMonIdleRight");
		m_Sprite->SetPivot(0.45f, 0.4f, 0.f);
	}
	
	

}

void CFMonster::IDLEStay()
{
}

void CFMonster::IDLEEnd()
{
}

void CFMonster::PREATTACKStart()
{
	StartleSound->Play();
	

	ActTime = 0;

	if (DIR::LEFT == Dir)
	{
		ChangeAnimation("FMonAttackStartLeft");
		m_Sprite->SetPivot(0.35f, 0.4f, 0.f);
	}
	if (DIR::RIGHT == Dir)
	{
		ChangeAnimation("FMonAttackStartRight");
		m_Sprite->SetPivot(0.6f, 0.4f, 0.f);
	}

	
}

void CFMonster::PREATTACKStay()
{
	float DeltaTime = CEngine::GetInst()->GetDeltaTime();
	ActTime += DeltaTime;

	if (ActTime >= 0.5)
	{
		IsAttacking = true;
		ChangeState("attack");
	}
}

void CFMonster::PREATTACKEnd()
{
	ActTime = 0;
}

void CFMonster::ATTACKStart()
{
	ChaseSound->Play();
	ChaseSoundRate = 2;
	if (DIR::LEFT == Dir)
	{
		ChangeAnimation("FMonAttackLeft");
		m_Sprite->SetPivot(0.35f, 0.4f, 0.f);
	}
	if (DIR::RIGHT == Dir)
	{
		ChangeAnimation("FMonAttackRight");
		m_Sprite->SetPivot(0.45f, 0.4f, 0.f);
	}
}

void CFMonster::ATTACKStay()
{
	float DeltaTime = CEngine::GetInst()->GetDeltaTime();
	ActTime += DeltaTime;
	ChaseSoundRate += DeltaTime;

	if (ChaseSoundRate >= 2)
	{
		if(ChaseSound->IsPlay())
			ChaseSound->Stop();

		ChaseSound->Play();
		
		
		ChaseSoundRate = 0;
	}
	
}

void CFMonster::ATTACKEnd()
{
	
}

void CFMonster::DEATHStart()
{
	ChaseSound->Stop();
	ActTime = 0;
	IsAttacking = false;
	IsDead = true;
	if (DIR::LEFT == Dir)
	{
		ChangeAnimation("FMonDeathLeft");
		m_Sprite->SetPivot(0.35f, 0.4f, 0.f);
	}
	if (DIR::RIGHT == Dir)
	{
		ChangeAnimation("FMonDeathRight");
		m_Sprite->SetPivot(0.3f, 0.4f, 0.f);
	}

	if (IsOnColPlayer)
	{
		pdummy->SubMonColCount();
	}
}

void CFMonster::DEATHStay()
{
	float DeltaTime = CEngine::GetInst()->GetDeltaTime();
	ActTime += DeltaTime;

	
	if (DIR::LEFT == Dir)
	{
		m_Sprite->AddRelativePos(Vector3(50.f, -800.f, 0.f) * DeltaTime);
	}
	if (DIR::RIGHT == Dir)
	{
		m_Sprite->AddRelativePos(Vector3(-50.f, -800.f, 0.f) * DeltaTime);
	}
	
	if (ActTime >= 3.0)
	{
		Destroy();
	}

}

void CFMonster::DEATHEnd()
{
}

