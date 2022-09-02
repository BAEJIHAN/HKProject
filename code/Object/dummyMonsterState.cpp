#include "dummymonster.h"
#include "dummymonsterAnimation.h"
#include "MHitEffectAnimation.h"
#include "Input.h"
#include "Engine.h"
#include "dummy.h"
#include "Resource/Sound/Sound.h"
void Cdummymonster::IDLEStart()
{
	IsAttacking = false;
	IdleTime = 0;
	m_Sprite->SetPivot(0.3f, 0.46f, 0.f);
	m_Body->SetExtent(60, 90);
	if (DIR::LEFT == Dir)
	{
		ChangeAnimation("HMonIdleLeft");
	}
	if (DIR::RIGHT == Dir)
	{
		ChangeAnimation("HMonIdleRight");
	}
	
}

void Cdummymonster::IDLEStay()
{
	float DeltaTime = CEngine::GetInst()->GetDeltaTime();
	IdleTime += DeltaTime;

	

	if (2.f <= IdleTime)
	{
		int a = rand() % 2;
		if(0==a)
		{
			Dir = DIR::LEFT;
		}
		else
		{
			Dir = DIR::RIGHT;
		}
		IdleTime = 0;
		ChangeState("move");
	}
}

void Cdummymonster::MOVEStart()
{
	IsWalking = true;
	MoveTime = 0;
	m_Sprite->SetPivot(0.3f, 0.46f, 0.f);
	m_Body->SetExtent(60, 90);
	if (DIR::LEFT == Dir)
	{
		ChangeAnimation("HMonWalkLeft");
	}
	if (DIR::RIGHT == Dir)
	{
		ChangeAnimation("HMonWalkRight");
	}
}

void Cdummymonster::MOVEStay()
{
	float DeltaTime = CEngine::GetInst()->GetDeltaTime();
	
	MoveTime += DeltaTime;

	if (DIR::RIGHT == Dir)
	{
		
		m_Sprite->AddRelativePos(Vector3(+200.f, 0.f, 0.f) * DeltaTime);
	}
	if (DIR::LEFT == Dir)
	{
		
		m_Sprite->AddRelativePos(Vector3(-200.f, 0.f, 0.f) * DeltaTime);
	}

	if (5.f <= MoveTime)
	{
		IdleTime = 0;
		ChangeState("Idle");
	}
}

void Cdummymonster::MOVEEnd()
{
	IsWalking = false;
}

void Cdummymonster::ATTACKONStart()
{
	AttackSound->Play();
	IsAttacking = true;
	PreAttackTime = 0;

	m_Sprite->SetPivot(0.3f, 0.36f, 0.f);
	m_Body->SetExtent(80, 50);
	m_Sprite->AddRelativePos(Vector3(0.f, -20.f, 0.f));
	if (DIR::LEFT == PlayerDir)
	{
		Dir = DIR::LEFT;
		ChangeAnimation("HMonAttackStartLeft");
	}
	if (DIR::RIGHT == PlayerDir)
	{
		Dir = DIR::RIGHT;
		ChangeAnimation("HMonAttackStartRight");
	}
}

void Cdummymonster::ATTACKONStay()
{
	float DeltaTime = CEngine::GetInst()->GetDeltaTime();

	PreAttackTime += DeltaTime;
	if (0.5f <= PreAttackTime)
	{
		PreAttackTime = 0;
		ChangeState("attack");
	}
}

void Cdummymonster::ATTACKStart()
{
	AttackTime = 0;
	m_Sprite->SetPivot(0.3f, 0.36f, 0.f);
	m_Body->SetExtent(80, 50);
	if (DIR::LEFT == Dir)
	{
		ChangeAnimation("HMonAttackLeft");
	}
	if (DIR::RIGHT == Dir)
	{
		ChangeAnimation("HMonAttackRight");
	}
}

void Cdummymonster::ATTACKStay()
{
	
	float DeltaTime = CEngine::GetInst()->GetDeltaTime();
	AttackTime += DeltaTime;
	if (DIR::RIGHT == Dir)
	{

		m_Sprite->AddRelativePos(Vector3(+400.f, 0.f, 0.f) * DeltaTime);
	}
	if (DIR::LEFT == Dir)
	{

		m_Sprite->AddRelativePos(Vector3(-400.f, 0.f, 0.f) * DeltaTime);
	}
	if (2.0f <= AttackTime)
	{
		AttackTime = 0;		
		ChangeState("Idle");
	}
}

void Cdummymonster::ATTACKEnd()
{
	m_Sprite->AddRelativePos(Vector3(0.f, 20.f, 0.f));
	IsAttacking = false;
}

void Cdummymonster::GETATTACKStart()
{
	m_Sprite->AddRelativePos(Vector3(0.f, -20.f, 0.f));
	GetAttackTime = 0;
	DamageSound->Play();
	m_HP--;

	if (0 == m_HP)
		ChangeState("death");
}

void Cdummymonster::GETATTACKStay()
{
	float DeltaTime = CEngine::GetInst()->GetDeltaTime();
	GetAttackTime += DeltaTime;
	if (GetAttackTime <= 0.1f)
	{
		if (GetColCenterPos().x < pdummy->GetColCenterPos().x)//오른쪽에서 때릴 때
		{
			m_Sprite->AddRelativePos(Vector3(-1000.f, 0.f, 0.f) * DeltaTime);
		}
		else if (GetColCenterPos().x >= pdummy->GetColCenterPos().x)//왼쪽에서 때릴 때
		{
			m_Sprite->AddRelativePos(Vector3(+1000.f, 0.f, 0.f) * DeltaTime);
		}

	}

	if (GetAttackTime >= 0.1)
	{
	
		GetAttackTime = 0;
		if (IsAttacking)
		{
			ChangeState("attack");
		}
		else
		{
			ChangeState("Idle");
		}
	}
}

void Cdummymonster::GETATTACKEnd()
{
}

void Cdummymonster::DEATHStart()
{
	DeathTime = 0;
	IsDead = true;

	if (IsOnColPlayer)
	{
		pdummy->SubMonColCount();
	}
	
	m_Sprite->AddRelativePos(Vector3(0.f, -20.f, 0.f));
	if (DIR::LEFT == Dir)
	{
		ChangeAnimation("HMonDeathLeft");
	}
	if (DIR::RIGHT == Dir)
	{
		ChangeAnimation("HMonDeathRight");
	}
}

void Cdummymonster::DEATHStay()
{
	float DeltaTime = CEngine::GetInst()->GetDeltaTime();
	DeathTime += DeltaTime;
	if (DeathTime <= 0.15)
	{
		if (GetColCenterPos().x < pdummy->GetColCenterPos().x)//오른쪽에서 때릴 때
		{
			m_Sprite->AddRelativePos(Vector3(-300.f, 0.f, 0.f) * DeltaTime);
		}
		else if (GetColCenterPos().x >= pdummy->GetColCenterPos().x)//왼쪽에서 때릴 때
		{
			m_Sprite->AddRelativePos(Vector3(+300.f, 0.f, 0.f) * DeltaTime);
		}

		m_Sprite->AddRelativePos(Vector3(0.f, 300.f, 0.f) * DeltaTime);

	}
	else
	{
		if (DeathTime <= 0.3)
		{
			if (GetColCenterPos().x < pdummy->GetColCenterPos().x)//오른쪽에서 때릴 때
			{
				m_Sprite->AddRelativePos(Vector3(-300.f, 0.f, 0.f) * DeltaTime);
			}
			else if (GetColCenterPos().x >= pdummy->GetColCenterPos().x)//왼쪽에서 때릴 때
			{
				m_Sprite->AddRelativePos(Vector3(+300.f, 0.f, 0.f) * DeltaTime);
			}
		}
		if(GetColTopYPos()>=MYPos)
			m_Sprite->AddRelativePos(Vector3(0.f, -300.f, 0.f) * DeltaTime);
	}
}
