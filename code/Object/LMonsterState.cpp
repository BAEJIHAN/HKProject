
#include "LMonster.h"
#include "LMonsterAnimation.h"
#include "Input.h"
#include "Engine.h"
#include "dummy.h"
#include "Resource/Sound/Sound.h"
void CLMonster::IDLEStart()
{
	IdleTime = 0;
	m_Sprite->SetPivot(0.23f, 0.53f, 0.f);
	m_Body->SetExtent(40, 90);

	if (DIR::LEFT == Dir)
	{
		ChangeAnimation("LMonIdleLeft");
	}
	if (DIR::RIGHT == Dir)
	{
		ChangeAnimation("LMonldleRight");
	}
}

void CLMonster::IDLEStay()
{
	float DeltaTime = CEngine::GetInst()->GetDeltaTime();
	IdleTime += DeltaTime;


	if (2.f <= IdleTime)
	{
		int a = rand() % 2;
		if (0 == a)
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

void CLMonster::MOVEStart()
{
	IsWalking = true;
	MoveTime = 0;

	m_Body->SetExtent(45, 90);


	if (DIR::LEFT == Dir)
	{
		m_Sprite->SetPivot(0.3f, 0.53f, 0.f);
		ChangeAnimation("LMonWalkLeft");
	}
	if (DIR::RIGHT == Dir)
	{
		m_Sprite->SetPivot(0.23f, 0.53f, 0.f);
		ChangeAnimation("LMonWalkRight");
	}
}

void CLMonster::MOVEStay()
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
		MoveTime = 0;
		ChangeState("Idle");
	}
}

void CLMonster::MOVEEnd()
{
	IsWalking = false;
}

void CLMonster::ATTACKONStart()
{
}

void CLMonster::ATTACKONStay()
{
}

void CLMonster::ATTACKStart()
{
	AttackSound->Play();
	IsAttacking = true;
	AttackTime = 0;
	m_Sprite->SetPivot(0.3f, 0.53f, 0.f);
	m_Body->SetExtent(45, 90);
	if (DIR::LEFT == PlayerDir)
	{
		
		Dir = DIR::LEFT;
		ChangeAnimation("LMonAttackLeft");
	}
	if (DIR::RIGHT == PlayerDir)
	{
		
		Dir = DIR::RIGHT;
		ChangeAnimation("LMonAttackRight");
	}

}

void CLMonster::ATTACKStay()
{
	float DeltaTime = CEngine::GetInst()->GetDeltaTime();
	
	AttackTime += DeltaTime;
	

	if (DIR::RIGHT == Dir)
	{
		if (AttackTime <= 0.5f)
		{
			m_Sprite->AddRelativePos(Vector3(+200.f, 600.f, 0.f) * DeltaTime);
		}
		else
		{
			m_Sprite->AddRelativePos(Vector3(+200.f, -600.f, 0.f) * DeltaTime);
		}
		
	}
	if (DIR::LEFT == Dir)
	{
		if (AttackTime <= 0.5f)
		{
			m_Sprite->AddRelativePos(Vector3(-200.f, 600.f, 0.f) * DeltaTime);
		}
		else
		{
			m_Sprite->AddRelativePos(Vector3(-200.f, -600.f, 0.f) * DeltaTime);
		}
	}

	if (1.0f <= AttackTime)
	{
		ChangeState("Idle");
	}
}

void CLMonster::ATTACKEnd()
{
	
	IsAttacking = false;
	AttackTime = 0;
}

void CLMonster::DEATHStart()
{
	IsDead = true;
	//m_Sprite->AddRelativeRotationX(10);
	if (DIR::LEFT == Dir)
	{
		ChangeAnimation("LMonDeathLeft");
	}
	if (DIR::RIGHT == Dir)
	{
		ChangeAnimation("LMonDeathRight");
	}

	if (IsOnColPlayer)
	{
		pdummy->SubMonColCount();
	}
}

void CLMonster::DEATHStay()
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
		if (GetColCenterPos().y >= MYPos)
			m_Sprite->AddRelativePos(Vector3(0.f, -300.f, 0.f) * DeltaTime);
	}
	
}