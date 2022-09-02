#include "FK.h"
#include "Scene/Scene.h"
#include "Resource/Material/Material.h"
#include "FKAnimation.h"

#include "Engine.h"
#include "dummy.h"
#include "AttackLeft.h"
#include "AttackRight.h"
#include "AttackUp.h"
#include "AttackDown.h"
#include "PlayerMissileLeft.h"
#include "PlayerMissileRight.h"
#include "Scene/SceneManager.h"
#include "RockDown.h"
#include "MHitEffectAnimation.h"

CFK::CFK()
{
	SetTypeID<CFK>();
	LeftHead = nullptr;
	RightHead = nullptr;

	IdleTime = 0.f;
	MoveTime = 0.f;
	PreAttackTime = 0.f;
	AttackTime = 0.f;
	AttackRate = 0.f;
	ChangeDirTime = 0.f;
	RageRate = 0.f;
	PreIdleTime = 0.f;

	JumpDist = 0.f;
	AppearDist = 0.f;

	RageDir = 1;
	ActNum = 10;
	
	HeadFlag = 0;
	AttackFlag = 0;

	SwingSoundRate = 0.f;
	AttackSoundRate = 0.f;
	RockDownRate = 0.f;
	HitRate = 0.f;
	hitflag = 0;

	IsDead = false;
	IsAttacking = false;	
	ChangeDirOn = false;
	IsGetAttack = false;

	IsTouchedFromLeft = false;
	IsTouchedFromRight = false;
	IsAppearing = false;

	Dir = DIR::LEFT;
	PlayerDir = DIR::LEFT;
	PrePlayerDir = DIR::LEFT;
	JumpDir = DIR::LEFT;
	AttackDir= DIR::LEFT;
	RollDir = DIR::LEFT;

	pdummy = nullptr;
	MYPos = 260.f;
	fflag = 0;

	AttackSound[0] = CResourceManager::GetInst()->FindSound("fkattack1");
	AttackSound[1] = CResourceManager::GetInst()->FindSound("fkattack2");
	AttackSound[2] = CResourceManager::GetInst()->FindSound("fkattack3");
	AttackSound[3] = CResourceManager::GetInst()->FindSound("fkattack4");
	AttackSound[4] = CResourceManager::GetInst()->FindSound("fkattack5");


	DamageSound = CResourceManager::GetInst()->FindSound("enemydamage");
	DamageArmour = CResourceManager::GetInst()->FindSound("fkdamagearmour");
	JumpSound = CResourceManager::GetInst()->FindSound("fkjump");
	LandSound = CResourceManager::GetInst()->FindSound("fkland");
	RollSound = CResourceManager::GetInst()->FindSound("fkroll");
	GroundAttackSound = CResourceManager::GetInst()->FindSound("fkstrikeground");
	RageSound = CResourceManager::GetInst()->FindSound("fkswing");
	EndSound = CResourceManager::GetInst()->FindSound("bossexplode");
	GroggySound = CResourceManager::GetInst()->FindSound("bossstun");
	BG = CResourceManager::GetInst()->FindSound("bossbackgroundmusic");
	FullHP = 10;
	m_HP = FullHP;
	RHP = 10;	

}


CFK::~CFK()
{
}

void CFK::Start()
{
	CGameObject::Start();
	pdummy = (Cdummy*)CSceneManager::GetInst()->GetScene()->GetPlayerObject();
	
}

bool CFK::Init()
{
	m_Sprite = CreateComponent<CSpriteComponent>("monster");
	m_Body = CreateComponent<CColliderBox2D>("Body");
	
	m_Muzzle = CreateComponent<CSceneComponent>("Muzzle");

	SetRootComponent(m_Sprite);

	m_Sprite->AddChild(m_Body);
	
	m_Sprite->AddChild(m_Muzzle);

	


	m_Body->SetCollisionProfile("Monster");


	m_Sprite->SetTransparency(true);
	//m_Sprite->SetOpacity(0.5f);

	m_Sprite->CreateAnimationInstance<CFKAnimation>();

	m_Sprite->SetRelativeScale(550, 480, 1.f);
	m_Sprite->SetPivot(0.35f, 0.45f, 0.f);
	HitEffect = CreateComponent<CSpriteComponent>("hiteffect");
	m_Sprite->AddChild(HitEffect);
	HitEffect->CreateAnimationInstance<CMHitEffectAnimation>();

	HitEffect->SetRelativeScale(360, 240, 1);
	HitEffect->SetPivot(0.5f, 0.9f, 0.f);
	HitEffect->SetRenderState("AlphaBlend");
	HitEffect->GetAnimationInstance()->ChangeAnimation("hitblank");

	m_Body->SetExtent(130, 140);

	m_Body->AddCollisionCallback(Collision_State::Begin, this, &CFK::OnCollisionBegin);
	m_Body->AddCollisionCallback(Collision_State::End, this, &CFK::OnCollisionEnd);
	
	CFFSM.CreateState("Idle", this, &CFK::IDLEStay, &CFK::IDLEStart, &CFK::IDLEEnd);
	CFFSM.CreateState("preattack", this, &CFK::PREATTACKStay, &CFK::PREATTACKStart, &CFK::PREATTACKEnd);
	CFFSM.CreateState("hitground", this, &CFK::HITGROUNDStay, &CFK::HITGROUNDStart, &CFK::HITGROUNDEnd);
	CFFSM.CreateState("rage", this, &CFK::RAGEStay, &CFK::RAGEStart, &CFK::RAGEEnd);
	CFFSM.CreateState("groundattack", this, &CFK::GROUNDATTACKStay, &CFK::GROUNDATTACKStart, &CFK::GROUNDATTACKEnd);
	CFFSM.CreateState("prejump", this, &CFK::PREJUMPStay, &CFK::PREJUMPStart, &CFK::PREJUMPEnd);
	CFFSM.CreateState("jump", this, &CFK::JUMPStay, &CFK::JUMPStart, &CFK::JUMPEnd);
	CFFSM.CreateState("land", this, &CFK::LandStay, &CFK::LandStart, &CFK::LandEnd);
	CFFSM.CreateState("jumpattack", this, &CFK::JUMPATTACKStay, &CFK::JUMPATTACKStart, &CFK::JUMPATTACKEnd);
	CFFSM.CreateState("groggy", this, &CFK::GROGGYStay, &CFK::GROGGYStart, &CFK::GROGGYEnd);
	CFFSM.CreateState("roll", this, &CFK::ROLLStay, &CFK::ROLLStart, &CFK::ROLLEnd);
	CFFSM.CreateState("stand", this, &CFK::STANDStay, &CFK::STANDStart, &CFK::STANDEnd);
	CFFSM.CreateState("Idle", this, &CFK::IDLEStay, &CFK::IDLEStart, &CFK::IDLEEnd);
	CFFSM.CreateState("death", this, &CFK::DEATHStay, &CFK::DEATHStart);
	CFFSM.CreateState("appear", this, &CFK::APPEARStay, &CFK::APPEARStart, &CFK::APPEAREnd);
	CFFSM.CreateState("appearland", this, &CFK::APPEARLANDStay, &CFK::APPEARLANDStart, &CFK::APPEARLANDEnd);
	



	ChangeState("appear");


	



	return true;
}

void CFK::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	CFFSM.Update();


	if (0 == fflag)
	{
		fflag++;
		return;
	}

	if (1 == fflag)
	{
		fflag++;
		
	}
	

	float pxpos = pdummy->GetColCenterPos().x;
	float xpos = this->GetColCenterPos().x;

	



	if (pdummy->GetColCenterPos().x < this->GetColCenterPos().x)
	{
		PlayerDir = DIR::LEFT;

	}
	else
	{
		PlayerDir = DIR::RIGHT;
	}


	if (PlayerDir != PrePlayerDir)
	{
		ChangeDir();

	}

	if (PlayerDir == DIR::LEFT)
	{
		PrePlayerDir = DIR::LEFT;
	}
	else if (PlayerDir == DIR::RIGHT)
	{
		PrePlayerDir = DIR::RIGHT;
	}

	if (false == IsAttacking && false ==IsGroggy)
	{
		AttackRate += DeltaTime;
	}

	if (AttackRate >= 2)
	{
		AttackRate = 0;
		if (false == IsAppearing)
		{
			TakeNextAction();
		}
		
	}

	if (GetColRightXPos() >= 2600)
	{
		SetIsTouchedFromRight(true);
	}
	else
	{
		SetIsTouchedFromRight(false);
	}

	if (GetColLeftXPos() <= 280)
	{
		SetIsTouchedFromLeft(true);
	}
	else
	{
		SetIsTouchedFromLeft(false);
	}

	HitUpdate(DeltaTime);

}

void CFK::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CFK* CFK::Clone()
{
	return new CFK(*this);
}

CAnimationSequence2DInstance* CFK::GetAnimationInstance() const
{
	return m_Sprite->GetAnimationInstance();
}

void CFK::ChangeDir()
{
	if (DIR::LEFT == Dir)
	{
		Dir = DIR::RIGHT;

	}
	else if (DIR::RIGHT == Dir)
	{
		Dir = DIR::LEFT;

	}
	if (false == IsAttacking && false== IsGroggy)
	{
		ChangeState("Idle");
	}
	
	
}

void CFK::HitUpdate(float DeltaTime)
{
	if (false == IsGetAttack)
	{
		HitRate = 0;
		return;
	}

	HitRate += DeltaTime;

	if (0 == hitflag)
	{
		hitflag++;
		int i = rand() % 6;
		if (0 == i)
		{
			HitEffect->GetAnimationInstance()->ChangeAnimation("hit1");
		}
		else if (1 == i)
		{
			HitEffect->GetAnimationInstance()->ChangeAnimation("hit2");
		}
		else if (2 == i)
		{
			HitEffect->GetAnimationInstance()->ChangeAnimation("hit3");
		}
		else if (3 == i)
		{
			HitEffect->GetAnimationInstance()->ChangeAnimation("hit4");
		}
		else if (4 == i)
		{
			HitEffect->GetAnimationInstance()->ChangeAnimation("hit5");
		}
		else if (5 == i)
		{
			HitEffect->GetAnimationInstance()->ChangeAnimation("hit6");
		}

	}

	if (HitRate > 0.09)
	{
		IsGetAttack = false;
		HitRate = 2;
		hitflag = 0;
		HitEffect->GetAnimationInstance()->ChangeAnimation("hitblank");
	}
}

void CFK::TakeNextAction()
{
	IsAttacking = true;
	

	

	ActNum = rand() % 5;
	
	
	switch (ActNum)
	{

	case 0://¾ÕÁ¡ÇÁ
	{
		ChangeState("prejump");
		break;
	}
	case 1://µÞÁ¡ÇÁ
	{
		ChangeState("prejump");
		break;
	}
	case 2://¶¥°ø°Ý
	{
		ChangeState("preattack");
		break;
	}
	case 3://Á¡ÇÁ°ø°Ý
	{
		ChangeState("prejump");
		break;
	}
	case 4://±¤ºÐ
	{
		ChangeState("preattack");
		break;
	}
	default:
	{
		break;
	}

	}

	
	
}

void CFK::SetMonPos(float x, float y, float z)
{
	MYPos = y;
	SetRelativePos(x, y, z);
}

void CFK::ChangeAnimation(const std::string& AniName)
{
	m_Sprite->GetAnimationInstance()->ChangeAnimation(AniName);
}

void CFK::ChangeState(const std::string& Name)
{
	CFFSM.ChangeState(Name);
}


void CFK::OnCollisionBegin(const CollisionResult& result)
{
	if ("Player" == result.Dest->GetCollisionProfile()->Name)
	{
		IsOnColPlayer = true;
	}


	if (IsDead)
	{
		return;
	}


	Cdummy tdummy;
	CAttackDown tAttackDown;
	CAttackRight tAttackRight;
	CAttackLeft tAttackLeft;
	CAttackUp tAttackUp;
	CPlayerMissileRight tMisiileRight;
	CPlayerMissileLeft tMisiileLeft;
	CRockDown tRockDown;

	
	if (result.Dest->GetGameObject()->GetTypeID() == tAttackDown.GetTypeID() ||
		result.Dest->GetGameObject()->GetTypeID() == tAttackUp.GetTypeID() ||
		result.Dest->GetGameObject()->GetTypeID() == tAttackRight.GetTypeID() ||
		result.Dest->GetGameObject()->GetTypeID() == tAttackLeft.GetTypeID() ||
		result.Dest->GetGameObject()->GetTypeID() == tMisiileRight.GetTypeID() ||
		result.Dest->GetGameObject()->GetTypeID() == tMisiileLeft.GetTypeID() ||
		result.Dest->GetGameObject()->GetTypeID() == tRockDown.GetTypeID())
	{
		if (result.Dest->GetGameObject()->GetTypeID() == tAttackDown.GetTypeID())
		{
			Cdummy* dummy = (Cdummy*)result.Dest->GetGameObject()->GetParent();
			dummy->ChangeState("afterdownattack");
		}

		if(!IsGroggy)
			DamageArmour->Play();
		m_HP--;
		IsGetAttack = true;
		if (result.Dest->GetGameObject()->GetTypeID() == tRockDown.GetTypeID())
		{
			CRockDown* rock = (CRockDown*)result.Dest->GetGameObject()->GetParent();
			if(rock)
				rock->Destroy();
		}

		if (0 == m_HP)
		{
			ChangeState("roll");
		}


	}

}

void CFK::OnCollisionEnd(const CollisionResult& result)
{
	if ("Player" == result.Dest->GetCollisionProfile()->Name)
	{
		IsOnColPlayer = false;
	}
}
