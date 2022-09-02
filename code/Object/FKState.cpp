#include "FK.h"
#include "FKAnimation.h"
#include "Input.h"
#include "Engine.h"
#include "FKAttack.h"
#include "../Object/FKHeadLeft.h"
#include "../Object/FKHeadRight.h"
#include "../Object/RockDown.h"
#include "../Object/dummy.h"
#include "StoneParticle.h"
#include "OrangeParticle.h"
#include "Resource/Sound/Sound.h"
#include "Scene/Scene.h"


void CFK::IDLEStart()
{
	if (DIR::LEFT == Dir)
	{
		ChangeAnimation("FKIdleLeft");
		m_Sprite->SetPivot(0.3f, 0.34f, 0.f);
		
	}
	else if(DIR::RIGHT == Dir)
	{
		ChangeAnimation("FKIdleRight");
		m_Sprite->SetPivot(0.45f, 0.34f, 0.f);
	}		
}	

void CFK::IDLEStay()
{
}

void CFK::IDLEEnd()
{
}

void CFK::PREATTACKStart()
{
	AttackTime = 0;

	if (4 == ActNum)
	{
		ChangeAnimation("FKAttackPreLeft");
		m_Sprite->SetPivot(0.21f, 0.34f, 0.f);
	}
	else if(2==ActNum)
	{
		if (DIR::LEFT == Dir)
		{
			ChangeAnimation("FKAttackPreLeft");
			m_Sprite->SetPivot(0.21f, 0.34f, 0.f);

		}
		else if (DIR::RIGHT == Dir)
		{
			ChangeAnimation("FKAttackPreRight");
			m_Sprite->SetPivot(0.5f, 0.34f, 0.f);

		}
		AttackDir = Dir;
	}

	




}

void CFK::PREATTACKStay()
{
	float DeltaTime = CEngine::GetInst()->GetDeltaTime();

	AttackTime += DeltaTime;

	if (AttackTime >= 1.5)
	{
		if (2 == ActNum)
		{
			ChangeState("groundattack");
		}
		else if (4 == ActNum)
		{
			ChangeState("rage");
		}
		
	}
	
}

void CFK::PREATTACKEnd()
{	
	AttackTime = 0;
}

void CFK::GROUNDATTACKStart()
{
	int t = rand() % 5;
	AttackSound[t]->Play();
	AttackTime = 0;
	AttackFlag = 0;
	if (DIR::LEFT == AttackDir)
	{
		ChangeAnimation("FKAttackLeft");
		m_Sprite->SetPivot(0.45f, 0.34f, 0.f);

	}
	else if (DIR::RIGHT == AttackDir)
	{
		ChangeAnimation("FKAttackRight");
		m_Sprite->SetPivot(0.38f, 0.34f, 0.f);
	}

	

	

}

void CFK::GROUNDATTACKStay()
{
	float DeltaTime = CEngine::GetInst()->GetDeltaTime();

	AttackTime += DeltaTime;

	if (0.1f <= AttackTime && 0== AttackFlag)
	{
		AttackFlag = 1;		
	}

	if (1 == AttackFlag)
	{
		AttackFlag = 2;
		if (DIR::LEFT == AttackDir)
		{
			
			CFKAttack* BMonAttack = m_Scene->CreateGameObject<CFKAttack>("BMAttack");
			BMonAttack->SetParent(this);
			BMonAttack->SetWorldPos(m_Muzzle->GetWorldPos() + Vector3(-200.f, 0.f, 0.f));
			BMonAttack->SetWorldRotation(GetWorldRot());
			GroundAttackSound->Play();
		}
		if (DIR::RIGHT == AttackDir)
		{
		
			CFKAttack* BMonAttack = m_Scene->CreateGameObject<CFKAttack>("BMAttack");
			BMonAttack->SetParent(this);
			BMonAttack->SetWorldPos(m_Muzzle->GetWorldPos() + Vector3(200.f, 0.f, 0.f));
			BMonAttack->SetWorldRotation(GetWorldRot());
			GroundAttackSound->Play();
		}

	}
	
	if (0.4f <= AttackTime)
	{
		ChangeState("Idle");
	}
}

void CFK::GROUNDATTACKEnd()
{
	AttackFlag = 0;
	AttackTime = 0;
	IsAttacking = false;
}

void CFK::RAGEStart()
{
	AttackTime = 0;
	RageRate = 0;
	ChangeAnimation("FKRage");
	m_Sprite->SetPivot(0.45f, 0.34f, 0.f);
	AttackFlag = 0;
	SwingSoundRate = 0;
	AttackSoundRate = 0;
	RockDownRate = 0;
}

void CFK::RAGEStay()
{
	float DeltaTime = CEngine::GetInst()->GetDeltaTime();
	RageRate += DeltaTime;
	SwingSoundRate += DeltaTime;
	AttackSoundRate += DeltaTime;
	AttackTime += DeltaTime;
	RockDownRate += DeltaTime;

	if (SwingSoundRate >= 0.5)
	{
		SwingSoundRate = 0;
		RageSound->Play();
	}

	if (AttackSoundRate >= 0.6)
	{
		AttackSoundRate = 0;

		int t = rand() % 5;
		AttackSound[t]->Play();
	}


	if (0.1f <= RageRate && 0 == AttackFlag)
	{
		AttackFlag = 1;
	}

	if (1 == AttackFlag)
	{
		AttackFlag = 2;
		/*CStoneParticle* stone = m_Scene->CreateGameObject<CStoneParticle>("stone");
		stone->SetRelativePos(GetWorldPos() + Vector3(-200.f * RageDir, 0.f, 0.f));*/

		CFKAttack* BMonAttack = m_Scene->CreateGameObject<CFKAttack>("BMAttack");
		BMonAttack->SetParent(this);
		BMonAttack->SetWorldPos(m_Muzzle->GetWorldPos() + Vector3(-200.f * RageDir, 0.f, 0.f));
		BMonAttack->SetWorldRotation(GetWorldRot());
		GroundAttackSound->Play();

		
	}

	if (RageRate >= 0.5)
	{
		AttackFlag = 0;
		RageRate = 0;
		RageDir *= -1;		

	}

	if (RockDownRate >= 0.4)
	{
		RockDownRate = 0;
		float xpos = (float)300 + (float)(rand() % 2200);
		CRockDown* rock = m_Scene->CreateGameObject<CRockDown>("rock");
		rock->SetRelativePos(xpos, 2000, 0);
	}

	if (6.f <= AttackTime)
	{
		ChangeState("Idle");
	}

	

}

void CFK::RAGEEnd()
{
	RockDownRate = 0;
	RageDir = 1;
	AttackFlag = 0;
	AttackTime = 0;
	RageRate = 0;
	IsAttacking = false;
}


void CFK::PREJUMPStart()
{
	int t = rand() % 5;
	AttackSound[t]->Play();
	IsAttacking = true;
	AttackTime = 0;
	if (DIR::LEFT == Dir)
	{
		ChangeAnimation("FKPreJumpLeft");
		m_Sprite->SetPivot(0.38f, 0.34f, 0.f);
		
	}
	else if (DIR::RIGHT == Dir)
	{
		ChangeAnimation("FKPreJumpRight");
		m_Sprite->SetPivot(0.4f, 0.34f, 0.f);
	}

	JumpDir = Dir;




}

void CFK::PREJUMPStay()
{
	float DeltaTime = CEngine::GetInst()->GetDeltaTime();

	AttackTime += DeltaTime;

	if (AttackTime >= 0.5)
	{
		if (0 == ActNum || 1 == ActNum)//앞점프 혹은 뒷점프
		{
			ChangeState("jump");
		}
		
		else if (3 == ActNum)//점프 공격
		{
			ChangeState("jumpattack");
		}
		
	}
}

void CFK::PREJUMPEnd()
{
	
	AttackTime = 0;
}

void CFK::JUMPStart()
{
	int t = rand() % 5;
	AttackSound[t]->Play();
	JumpSound->Play();
	AttackTime = 0;

	

	JumpDist=(float)(rand() % 4 +1);

	if (DIR::LEFT == JumpDir)
	{
		ChangeAnimation("FKOnJumpLeft");
		m_Sprite->SetPivot(0.25f, 0.34f, 0.f);

	}
	else if (DIR::RIGHT == JumpDir)
	{
		ChangeAnimation("FKOnJumpRight");
		m_Sprite->SetPivot(0.5f, 0.34f, 0.f);
	}





}

void CFK::JUMPStay()
{
	float DeltaTime = CEngine::GetInst()->GetDeltaTime();

	AttackTime += DeltaTime;

	if (0 == ActNum)//앞점프
	{
		if (AttackTime <= 1.0)
		{
			m_Sprite->AddRelativePos(Vector3(0, 600.f, 0.f) * DeltaTime);
			if (false == GetIsTouchedFromRight())
			{
				m_Sprite->AddRelativePos(Vector3(+100.f * (float)JumpDist, 0.f, 0.f) * DeltaTime);
			}
			
		}
		else if (AttackTime <= 2.0)
		{
			
			m_Sprite->AddRelativePos(Vector3(0, -600.f, 0.f) * DeltaTime);
			if (false == GetIsTouchedFromRight())
			{
				m_Sprite->AddRelativePos(Vector3(+100.f * (float)JumpDist, 0.f, 0.f) * DeltaTime);
			}
		}
		else if (AttackTime > 2.0)
		{
			ChangeState("land");
		}

		
	}
	else if (1 == ActNum)//뒷점프
	{
		if (AttackTime <= 1.0)
		{			
			m_Sprite->AddRelativePos(Vector3(0, 600.f, 0.f) * DeltaTime);
			if (false == GetIsTouchedFromLeft())
			{
				m_Sprite->AddRelativePos(Vector3(-100.f * (float)JumpDist, 0.f, 0.f) * DeltaTime);
			}
		}
		else if (AttackTime <= 2.0)
		{
			m_Sprite->AddRelativePos(Vector3(0, -600.f, 0.f) * DeltaTime);
			if (false == GetIsTouchedFromLeft())
			{
				m_Sprite->AddRelativePos(Vector3(-100.f * (float)JumpDist, 0.f, 0.f) * DeltaTime);
			}			
		}
		else if (AttackTime > 2.0)
		{
			ChangeState("land");
		}
	}
	

	
}

void CFK::JUMPEnd()
{
	AttackTime = 0;
	JumpDist = 0;
}


void CFK::LandStart()
{
	LandSound->Play();
	AttackTime = 0;
	if (DIR::LEFT == JumpDir)
	{
		ChangeAnimation("FKLandLeft");
		m_Sprite->SetPivot(0.37f, 0.34f, 0.f);

	}
	else if (DIR::RIGHT == JumpDir)
	{
		ChangeAnimation("FKLandRight");
		m_Sprite->SetPivot(0.4f, 0.34f, 0.f);
	}
}

void CFK::LandStay()
{
	float DeltaTime = CEngine::GetInst()->GetDeltaTime();

	AttackTime += DeltaTime;

	if (AttackTime >= 0.5)
	{
		ChangeState("Idle");
	}
}

void CFK::LandEnd()
{
	AttackTime = 0;
	IsAttacking = false;
}


void CFK::JUMPATTACKStart()//점프공격 내려올 때
{
	AttackTime = 0;

	

	JumpDist = (float)(rand() % 4 + 1);

	if (DIR::LEFT == Dir)
	{
		ChangeAnimation("FKOnJumpAttackLeft");
		m_Sprite->SetPivot(0.2f, 0.34f, 0.f);

	}
	else if (DIR::RIGHT == Dir)
	{
		ChangeAnimation("FKOnJumpAttackRight");
		m_Sprite->SetPivot(0.55f, 0.34f, 0.f);
	}
	JumpDir = Dir;
}

void CFK::JUMPATTACKStay()
{

	float DeltaTime = CEngine::GetInst()->GetDeltaTime();

	AttackTime += DeltaTime;

	if (DIR::LEFT == JumpDir)
	{
		if (AttackTime <= 1.0)
		{
			m_Sprite->AddRelativePos(Vector3(0, 600.f, 0.f) * DeltaTime);
			if (false == GetIsTouchedFromLeft())
			{
				m_Sprite->AddRelativePos(Vector3(-100.f * (float)JumpDist, 0.f, 0.f) * DeltaTime);
			}
			
		}
		else if (AttackTime <= 2.0)
		{
			m_Sprite->AddRelativePos(Vector3(0, -600.f, 0.f) * DeltaTime);
			if (false == GetIsTouchedFromLeft())
			{
				m_Sprite->AddRelativePos(Vector3(-100.f * (float)JumpDist, 0.f, 0.f) * DeltaTime);
			}
			
		}
		else if (AttackTime > 2.0)
		{
			ChangeState("hitground");
		}

	}
	else if (DIR::RIGHT == JumpDir)
	{
		if (AttackTime <= 1.0)
		{
			m_Sprite->AddRelativePos(Vector3(0, 600.f, 0.f) * DeltaTime);
			if (false == GetIsTouchedFromRight())
			{
				m_Sprite->AddRelativePos(Vector3(+100.f * (float)JumpDist, 0.f, 0.f) * DeltaTime);
			}
			
		}
		else if (AttackTime <= 2.0)
		{
			m_Sprite->AddRelativePos(Vector3(0, -600.f, 0.f) * DeltaTime);
			if (false == GetIsTouchedFromRight())
			{
				m_Sprite->AddRelativePos(Vector3(+100.f * (float)JumpDist, 0.f, 0.f) * DeltaTime);
			}			
		}
		else if (AttackTime > 2.0)
		{
			ChangeState("hitground");
		}
	}
}

void CFK::JUMPATTACKEnd()
{
	AttackTime = 0;
}


void CFK::HITGROUNDStart()
{
	int t = rand() % 5;
	AttackSound[t]->Play();
	AttackTime = 0;
	AttackFlag = 0;
	if (DIR::LEFT == JumpDir)
	{
		ChangeAnimation("FKHitGroundLeft");
		m_Sprite->SetPivot(0.4f, 0.34f, 0.f);

	}
	else if (DIR::RIGHT == JumpDir)
	{
		ChangeAnimation("FKHitGroundRight");
		m_Sprite->SetPivot(0.35f, 0.34f, 0.f);
	}
}

void CFK::HITGROUNDStay()
{
	float DeltaTime = CEngine::GetInst()->GetDeltaTime();

	AttackTime += DeltaTime;

	if (0.1f <= AttackTime && 0==AttackFlag)
	{
		AttackFlag = 1;
		
	}

	if (1 == AttackFlag)
	{
		AttackFlag = 2;
		if(DIR::LEFT == JumpDir)
		{
		/*	CStoneParticle* stone = m_Scene->CreateGameObject<CStoneParticle>("stone");
			stone->SetRelativePos(GetWorldPos() + Vector3(-200.f, 0.f, 0.f));*/
			CFKAttack* BMonAttack = m_Scene->CreateGameObject<CFKAttack>("BMAttack");
			BMonAttack->SetParent(this);
			BMonAttack->SetWorldPos(m_Muzzle->GetWorldPos() + Vector3(-200.f, 0.f, 0.f));
			BMonAttack->SetWorldRotation(GetWorldRot());
			GroundAttackSound->Play();
		}
		if (DIR::RIGHT == JumpDir)
		{
			/*CStoneParticle* stone = m_Scene->CreateGameObject<CStoneParticle>("stone");
			stone->SetRelativePos(GetWorldPos() + Vector3(200.f, 0.f, 0.f));*/
			CFKAttack* BMonAttack = m_Scene->CreateGameObject<CFKAttack>("BMAttack");
			BMonAttack->SetParent(this);
			BMonAttack->SetWorldPos(m_Muzzle->GetWorldPos() + Vector3(200.f, 0.f, 0.f));
			BMonAttack->SetWorldRotation(GetWorldRot());
			GroundAttackSound->Play();

		}
	}

	if (0.5f <= AttackTime)
	{
		ChangeState("Idle");
	}
}

void CFK::HITGROUNDEnd()
{
	AttackFlag = 0;
	AttackTime = 0;
	IsAttacking = false;
}


void CFK::ROLLStart()
{
	GroggySound->Play();
	RollSound->Play();
	IsAttacking = false;
	IsGroggy = true;
	AttackTime = 0;
	if (DIR::LEFT == PlayerDir)
	{
		RollDir = DIR::RIGHT;

	}
	else if (DIR::RIGHT == PlayerDir)
	{
		RollDir = DIR::LEFT;
	}
	

	if (DIR::LEFT == RollDir)
	{
		ChangeAnimation("FKRollLeft");
		m_Sprite->SetPivot(0.2f, 0.34f, 0.f);

	}
	else if (DIR::RIGHT == RollDir)
	{
		ChangeAnimation("FKRollRight");
		m_Sprite->SetPivot(0.25f, 0.34f, 0.f);
	}
}

void CFK::ROLLStay()
{
	float DeltaTime = CEngine::GetInst()->GetDeltaTime();

	AttackTime += DeltaTime;

	if (DIR::LEFT == RollDir)
	{
		if (AttackTime <= 0.7)
		{

			m_Sprite->AddRelativePos(Vector3(0, 250.f, 0.f) * DeltaTime);
			if (false == GetIsTouchedFromLeft())
			{
				m_Sprite->AddRelativePos(Vector3(-150.f, 0.f, 0.f) * DeltaTime);
			}
		}
		if(AttackTime>=0.7)
		{
			if (MYPos <= GetColCenterPos().y)
			{
				m_Sprite->AddRelativePos(Vector3(0, -250.f, 0.f) * DeltaTime);
			}
			else
			{
				ChangeState("groggy");
			}
			
		
			if (false == GetIsTouchedFromLeft())
			{
				m_Sprite->AddRelativePos(Vector3(-150.f, 0.f, 0.f) * DeltaTime);
			}

		}
		
	

	}
	if (DIR::RIGHT == RollDir)
	{
		if (AttackTime <= 0.7)
		{
			m_Sprite->AddRelativePos(Vector3(0, 250.f, 0.f) * DeltaTime);
			if (false == GetIsTouchedFromRight())
			{
				m_Sprite->AddRelativePos(Vector3(150.f, 0.f, 0.f) * DeltaTime);
			}
			
		}
		if (AttackTime >= 0.7)
		{
			if (MYPos <= GetColCenterPos().y)
			{
				m_Sprite->AddRelativePos(Vector3(0, -250.f, 0.f) * DeltaTime);
			}
			else
			{
				ChangeState("groggy");
			}


			if (false == GetIsTouchedFromLeft())
			{
				m_Sprite->AddRelativePos(Vector3(150.f, 0.f, 0.f) * DeltaTime);
			}

		}
		

	}
}

void CFK::ROLLEnd()
{
	AttackTime = 0;
}


void CFK::GROGGYStart()
{
	
	AttackTime = 0;
	HeadFlag = 0;
	if (DIR::LEFT == Dir)
	{
		ChangeAnimation("FKGroggyLeft");
		m_Sprite->SetPivot(0.24f, 0.34f, 0.f);

	}
	else if (DIR::RIGHT == Dir)
	{
		ChangeAnimation("FKGroggyRight");
		m_Sprite->SetPivot(0.25f, 0.34f, 0.f);
	}
}

void CFK::GROGGYStay()
{
	float DeltaTime = CEngine::GetInst()->GetDeltaTime();

	AttackTime += DeltaTime;
	
	if (AttackTime >= 0.8 && 0== HeadFlag)
	{
		HeadFlag = 1;
	}
	if (1== HeadFlag)
	{
		HeadFlag = 2;
		if (DIR::LEFT == Dir)
		{

			LeftHead = m_Scene->CreateGameObject<CFKHeadLeft>("head");
			LeftHead->SetParent(this);
			LeftHead->SetWorldPos(m_Muzzle->GetWorldPos() + Vector3(-88.f, -117.f, 0.f));
			LeftHead->SetWorldRotation(GetWorldRot());
			
		}
		if (DIR::RIGHT == Dir)
		{
			RightHead = m_Scene->CreateGameObject<CFKHeadRight>("head");
			RightHead->SetParent(this);
			RightHead->SetWorldPos(m_Muzzle->GetWorldPos() + Vector3(85.f, -117.f, 0.f));
			RightHead->SetWorldRotation(GetWorldRot());
			
		}
	}
	if (AttackTime >= 5)
	{
		if (DIR::LEFT == Dir)
		{
			LeftHead->Destroy();
		}
		if (DIR::RIGHT == Dir)
		{
			RightHead->Destroy();
			

		}
		ChangeState("stand");
	}

	
}

void CFK::GROGGYEnd()
{
	AttackTime = 0;
	HeadFlag = 0;
}

void CFK::STANDStart()
{
	int t = rand() % 5;
	AttackSound[t]->Play();
	AttackTime = 0;
	m_HP = FullHP;
	if (DIR::LEFT == Dir)
	{
		ChangeAnimation("FKStandLeft");
		m_Sprite->SetPivot(0.3f, 0.34f, 0.f);

	}
	else if (DIR::RIGHT == Dir)
	{
		ChangeAnimation("FKStandRight");
		m_Sprite->SetPivot(0.4f, 0.34f, 0.f);
	}
}

void CFK::STANDStay()
{
	float DeltaTime = CEngine::GetInst()->GetDeltaTime();

	AttackTime += DeltaTime;

	if (AttackTime >= 0.7f)
	{
		
		ChangeState("Idle");
	}

}

void CFK::STANDEnd()
{
	AttackTime = 0;
	IsGroggy = false;
}

void CFK::DEATHStart()
{
	BG->Stop();
	COrangeParticle* orange = m_Scene->CreateGameObject<COrangeParticle>("orange");
	orange->SetRelativePos(GetWorldPos());
	EndSound->Play();
	IsDead = true;
	IsGroggy = true;

	if (IsOnColPlayer)
	{
		pdummy->SubMonColCount();
	}

	
}

void CFK::DEATHStay()
{
}



/////////////////////////등장
void CFK::APPEARStart()
{
	
	IsAppearing = true;
	ChangeAnimation("FKOnJumpLeft");
	m_Sprite->SetPivot(0.25f, 0.34f, 0.f);
	
	AppearDist = 0;
}

void CFK::APPEARStay()
{
	float DeltaTime = CEngine::GetInst()->GetDeltaTime();
	pdummy->SetIsOnEvent(true);
	AppearDist += DeltaTime* 600.f;


	
	m_Sprite->AddRelativePos(Vector3(0.f, -1* DeltaTime * 600.f, 0.f));

	if (AppearDist >= 940.f)
	{
		ChangeState("appearland");
	}
		
}

void CFK::APPEAREnd()
{
}

void CFK::APPEARLANDStart()
{
	
	LandSound->Play();
	AttackTime = 0;	
	ChangeAnimation("FKLandLeft");
	m_Sprite->SetPivot(0.37f, 0.34f, 0.f);

	
}

void CFK::APPEARLANDStay()
{
	float DeltaTime = CEngine::GetInst()->GetDeltaTime();

	AttackTime += DeltaTime;

	if (AttackTime >= 0.5)
	{
		ChangeState("Idle");
	}
}

void CFK::APPEARLANDEnd()
{
	pdummy->SetIsOnEvent(false);
	IsAppearing = false;
	AttackTime = 0;
	BG->Play();
}


