#include "BMonster.h"
#include "BMonsterAnimation.h"
#include "Input.h"
#include "Engine.h"
#include "../Object/BMonAttack.h"
#include "StoneParticle.h"
#include "dummy.h"
#include "Resource/Sound/Sound.h"
#include "Scene/Scene.h"
void CBMonster::IDLEStart()
{
	IdleTime = 0;
	m_Sprite->SetPivot(0.4f, 0.35f, 0.f);
	m_Body->SetExtent(160, 100.f);
	if (DIR::LEFT == Dir)
	{
		ChangeAnimation("BMonIdleLeft");
	}
	if (DIR::RIGHT == Dir)
	{
		ChangeAnimation("BMonIdleRight");
	}
}

void CBMonster::IDLEStay()
{
	float DeltaTime = CEngine::GetInst()->GetDeltaTime();

}

void CBMonster::MOVEStart()
{
	IsWalking = true;
	MoveTime = 0;
	m_Sprite->SetPivot(0.4f, 0.35f, 0.f);
	m_Body->SetExtent(160, 100.f);
	if (DIR::LEFT == Dir)
	{
		ChangeAnimation("BMonWalkLeft");
	}
	if (DIR::RIGHT == Dir)
	{
		ChangeAnimation("BMonWalkRight");
	}
}
void CBMonster::MOVEStay()
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

}
void CBMonster::MOVEEnd()
{
	IsWalking = false;
}



void CBMonster::ATTACKStart()
{
	AttackSound->Play();
	AttackFlag = 0;
	AttackTime = 0;
	IsAttacking = true;
	m_Body->SetExtent(160, 100.f);
	if (DIR::LEFT == Dir)
	{
		m_Sprite->SetPivot(0.6f, 0.4f, 0.f);
		ChangeAnimation("BMonAttackLeft");
	}
	if (DIR::RIGHT == Dir)
	{
		m_Sprite->SetPivot(0.4f, 0.4f, 0.f);
		ChangeAnimation("BMonAttackRight");
	}
}

void CBMonster::ATTACKStay()
{
	float DeltaTime = CEngine::GetInst()->GetDeltaTime();

	AttackTime += DeltaTime;



	if (0.4f <= AttackTime && 0 == AttackFlag)
	{
		AttackFlag = 1;
		
	}

	if (1 == AttackFlag)
	{
		GroundSound->Play();
		AttackFlag = 2;
		if (DIR::LEFT == Dir)
		{
			/*CStoneParticle* stone = m_Scene->CreateGameObject<CStoneParticle>("stone");
			stone->SetRelativePos(GetWorldPos() + Vector3(-180.f, 0.f, 0.f));*/

			CBMonAttack* BMonAttack = m_Scene->CreateGameObject<CBMonAttack>("BMAttack");
			BMonAttack->SetParent(this);
			BMonAttack->SetWorldPos(m_Muzzle->GetWorldPos() + Vector3(-180.f, 0.f, 0.f));
			BMonAttack->SetWorldRotation(GetWorldRot());
		}
		if (DIR::RIGHT == Dir)
		{
			/*CStoneParticle* stone = m_Scene->CreateGameObject<CStoneParticle>("stone");
			stone->SetRelativePos(GetWorldPos() + Vector3(180.f, 0.f, 0.f));*/

			CBMonAttack* BMonAttack = m_Scene->CreateGameObject<CBMonAttack>("BMAttack");
			BMonAttack->SetParent(this);
			BMonAttack->SetWorldPos(m_Muzzle->GetWorldPos() + Vector3(180.f, 0.f, 0.f));
			BMonAttack->SetWorldRotation(GetWorldRot());


		}
	}
	



	


	if (0.7f <= AttackTime)
	{
		
		if (true == IsChasing)
		{
			ChangeState("move");
		}
		else
		{
			ChangeState("Idle");
		}
		

	}
	
	
}

void CBMonster::ATTACKEnd()
{
	AttackFlag = 0;
	IsAttacking = false;
	AttackTime = 0;
}

void CBMonster::STOMPStart()
{

	AttackTime = 0;
	m_Sprite->SetPivot(0.4f, 0.35f, 0.f);
	m_Body->SetExtent(160, 65.f);
	if (DIR::LEFT == Dir)
	{
		ChangeAnimation("BMonStompLeft");
	}
	if (DIR::RIGHT == Dir)
	{
		ChangeAnimation("BMonStompRight");
	}
}

void CBMonster::STOMPStay()
{
}

void CBMonster::DEATHStart()
{
	DeathTime = 0;
	IsDead = true;
	m_Sprite->SetPivot(0.4f, 0.35f, 0.f);
	//m_Body->SetExtent(160, 100.f);
	if (DIR::LEFT == Dir)
	{
		ChangeAnimation("BMonDeathLeft");
	}
	if (DIR::RIGHT == Dir)
	{
		ChangeAnimation("BMonDeathRight");
	}

	if (IsOnColPlayer)
	{
		pdummy->SubMonColCount();
	}
}

void CBMonster::DEATHStay()
{
	float DeltaTime = CEngine::GetInst()->GetDeltaTime();
	DeathTime += DeltaTime;
	if (DeathTime <= 0.15)
	{
		if (GetColCenterPos().x < pdummy->GetColCenterPos().x)//오른쪽에서 때릴 때
		{
			m_Sprite->AddRelativePos(Vector3(-250.f, 0.f, 0.f) * DeltaTime);
		}
		else if (GetColCenterPos().x >= pdummy->GetColCenterPos().x)//왼쪽에서 때릴 때
		{
			m_Sprite->AddRelativePos(Vector3(+250.f, 0.f, 0.f) * DeltaTime);
		}

		m_Sprite->AddRelativePos(Vector3(0.f, 200.f, 0.f) * DeltaTime);

	}
	else if(DeathTime <= 0.3)
	{
		
		if (GetColCenterPos().x < pdummy->GetColCenterPos().x)//오른쪽에서 때릴 때
		{
			m_Sprite->AddRelativePos(Vector3(-250.f, 0.f, 0.f) * DeltaTime);
		}
		else if (GetColCenterPos().x >= pdummy->GetColCenterPos().x)//왼쪽에서 때릴 때
		{
			m_Sprite->AddRelativePos(Vector3(+250.f, 0.f, 0.f) * DeltaTime);
		}

		m_Sprite->AddRelativePos(Vector3(0.f, -200.f, 0.f) * DeltaTime);
	}
	else if (DeathTime >= 0.3)
	{

	}
}
