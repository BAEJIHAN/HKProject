#include "BMonster.h"
#include "Scene/Scene.h"
#include "Resource/Material/Material.h"
#include "BMonsterAnimation.h"

#include "Engine.h"
#include "dummy.h"
#include "AttackLeft.h"
#include "AttackRight.h"
#include "AttackUp.h"
#include "AttackDown.h"
#include "PlayerMissileLeft.h"
#include "PlayerMissileRight.h"
#include "Scene/SceneManager.h"
#include "MHitEffectAnimation.h"

CBMonster::CBMonster()
{
	SetTypeID<CBMonster>();

	IdleTime = 0.f;
	MoveTime = 0.f;
	PreAttackTime = 0.f;
	AttackTime = 0.f;
	AttackRate = 0.f;
	ChangeDirTime = 0.f;
	DeathTime = 0.f;
	HitRate = 0.f;
	hitflag = 0;

	IsGetAttack = false;
	IsChasing = false;
	IsDead = false;
	IsAttacking = false;
	IsWalking = false;
	ChangeDirOn = false;

	Dir = DIR::LEFT;
	PlayerDir = DIR::LEFT;
	PrePlayerDir = DIR::LEFT;

	dist = 1000;

	pdummy = nullptr;
	AttackFlag = 0;
	fflag = 0;

	DamageSound = CResourceManager::GetInst()->FindSound("enemydamage");
	AttackSound = CResourceManager::GetInst()->FindSound("bmonattack"); 
	RunSound = CResourceManager::GetInst()->FindSound("bmonrun");
	GroundSound = CResourceManager::GetInst()->FindSound("fkstrikeground");

}




CBMonster::~CBMonster()
{
}

void CBMonster::Start()
{
	CGameObject::Start();
	pdummy = (Cdummy*)CSceneManager::GetInst()->GetScene()->GetPlayerObject();
}

bool CBMonster::Init()
{
	m_Sprite = CreateComponent<CSpriteComponent>("monster");
	m_Body = CreateComponent<CColliderBox2D>("Body");
	m_IBody = CreateComponent<CColliderBox2D>("IBody");
	m_Muzzle = CreateComponent<CSceneComponent>("Muzzle");

	SetRootComponent(m_Sprite);

	m_Sprite->AddChild(m_Body);
	m_Sprite->AddChild(m_IBody);
	m_Sprite->AddChild(m_Muzzle);

	


	m_Body->SetCollisionProfile("Monster");
	m_IBody->SetCollisionProfile("MonsterIdentify");

	m_Sprite->SetTransparency(true);
	//m_Sprite->SetOpacity(0.5f);

	m_Sprite->CreateAnimationInstance<CBMonsterAnimation>();

	m_Sprite->SetRelativeScale(400.f, 340.f, 1.f);	
	m_Sprite->SetPivot(0.5f, 0.5f, 0.f);

	HitEffect = CreateComponent<CSpriteComponent>("hiteffect");
	m_Sprite->AddChild(HitEffect);
	HitEffect->CreateAnimationInstance<CMHitEffectAnimation>();

	HitEffect->SetRelativeScale(240.f, 160.f, 1.f);
	HitEffect->SetPivot(0.5f, 0.7f, 0.f);
	HitEffect->SetRenderState("AlphaBlend");
	HitEffect->GetAnimationInstance()->ChangeAnimation("hitblank");

	m_Body->SetExtent(160.f, 100.f);	

	m_Body->AddCollisionCallback(Collision_State::Begin, this, &CBMonster::OnCollisionBegin);
	m_Body->AddCollisionCallback(Collision_State::End, this, &CBMonster::OnCollisionEnd);

	m_HP = 10;

	m_IBody->SetExtent(600, 100);
	m_IBody->AddCollisionCallback(Collision_State::Begin, this, &CBMonster::IOnCollisionBegin);
	m_IBody->AddCollisionCallback(Collision_State::End, this, &CBMonster::IOnCollisionEnd);

	BMFSM.CreateState("Idle", this, &CBMonster::IDLEStay, &CBMonster::IDLEStart);
	
	

	BMFSM.CreateState("move", this, &CBMonster::MOVEStay, &CBMonster::MOVEStart, &CBMonster::MOVEEnd);
	BMFSM.CreateState("stomp", this, &CBMonster::STOMPStay, &CBMonster::STOMPStart);
	BMFSM.CreateState("attack", this, &CBMonster::ATTACKStay, &CBMonster::ATTACKStart, &CBMonster::ATTACKEnd);
	BMFSM.CreateState("death", this, &CBMonster::DEATHStay, &CBMonster::DEATHStart);

	BMFSM.ChangeState("Idle");
	return true;
}

void CBMonster::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
	BMFSM.Update();
	if (0 == fflag)
	{
		fflag++;
		return;
	}

	if (IsDead)
	{
		return;
	}
	
	if (false == IsAttacking)
	{
		AttackRate += DeltaTime;
	}
	
	CheckPlayerPos();
	

	if (dist <= 300 && AttackRate >=0.5f && IsChasing)
	{
		AttackRate = 0;
		ChangeState("attack");
	}

	if (PlayerDir != PrePlayerDir)
	{
		ChangeDirOn = true;
	
	}

	if (ChangeDirOn)
	{
		ChangeDirTime += DeltaTime;
	}

	if (ChangeDirTime >= 0.8)
	{
		ChangeDirTime = 0;
		ChangeDirOn = false;
		ChangeDir();
	}

	if (dist >= 600)
	{
		ChangeState("Idle");
	}

	if (true == IsChasing && false == IsWalking && false==IsAttacking)
	{
		Chase();
	}


	if (PlayerDir == DIR::LEFT)
	{
		PrePlayerDir = DIR::LEFT;
	}
	else if (PlayerDir == DIR::RIGHT)
	{
		PrePlayerDir = DIR::RIGHT;
	}
	
	HitUpdate(DeltaTime);
}

void CBMonster::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CBMonster* CBMonster::Clone()
{
	return new CBMonster(*this);
}

CAnimationSequence2DInstance* CBMonster::GetAnimationInstance() const
{
	return m_Sprite->GetAnimationInstance();
}

void CBMonster::ChangeDir()
{
	if (DIR::LEFT == PlayerDir)
	{
		Dir = DIR::LEFT;

	}
	else if (DIR::RIGHT == PlayerDir)
	{
		Dir = DIR::RIGHT;

	}

	if (IsWalking)
	{
		ChangeState("move");
	}
}

void CBMonster::CheckPlayerPos()
{
	float pxpos = pdummy->GetColCenterPos().x;
	float xpos = this->GetColCenterPos().x;

	dist = abs((int)xpos - (int)pxpos);



	if (pdummy->GetColCenterPos().x < this->GetColCenterPos().x)
	{
		PlayerDir = DIR::LEFT;

	}
	else
	{
		PlayerDir = DIR::RIGHT;
	}


	
}

void CBMonster::Chase()
{
	ChangeState("move");
}

void CBMonster::HitUpdate(float DeltaTime)
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
		HitRate = 2;
		hitflag = 0;
		HitEffect->GetAnimationInstance()->ChangeAnimation("hitblank");
		IsGetAttack = false;
	}
}

void CBMonster::ChangeAnimation(const std::string& AniName)
{
	m_Sprite->GetAnimationInstance()->ChangeAnimation(AniName);
}

void CBMonster::ChangeState(const std::string& Name)
{
	BMFSM.ChangeState(Name);
}


void CBMonster::OnCollisionBegin(const CollisionResult& result)
{
	CAttackDown tAttackDown;
	CAttackRight tAttackRight;
	CAttackLeft tAttackLeft;
	CAttackUp tAttackUp;
	CPlayerMissileRight tMisiileRight;
	CPlayerMissileLeft tMisiileLeft;

	if ("Player" == result.Dest->GetCollisionProfile()->Name)
	{
		IsOnColPlayer = true;
	}

	if (result.Dest->GetGameObject()->GetTypeID() == tAttackDown.GetTypeID() ||
		result.Dest->GetGameObject()->GetTypeID() == tAttackUp.GetTypeID() ||
		result.Dest->GetGameObject()->GetTypeID() == tAttackRight.GetTypeID() ||
		result.Dest->GetGameObject()->GetTypeID() == tAttackLeft.GetTypeID() ||
		result.Dest->GetGameObject()->GetTypeID() == tMisiileRight.GetTypeID() ||
		result.Dest->GetGameObject()->GetTypeID() == tMisiileLeft.GetTypeID())
	{
		if (true == IsDead)
			return;

		
		if (result.Dest->GetGameObject()->GetTypeID() == tAttackDown.GetTypeID())
		{

			pdummy->ChangeState("afterdownattack");
		}

		IsGetAttack = true;
		DamageSound->Play();
		m_HP--;
		if (0 == m_HP)
		{
			ChangeState("death");
		}


	}

}

void CBMonster::OnCollisionEnd(const CollisionResult& result)
{
	if ("Player" == result.Dest->GetCollisionProfile()->Name)
	{
		IsOnColPlayer = false;
	}
}

void CBMonster::IOnCollisionBegin(const CollisionResult& result)
{
	if (true == IsDead)
		return;
	if ("PlayerIdentify" == result.Dest->GetCollisionProfile()->Name)
	{
		IsChasing = true;
	}
}

void CBMonster::IOnCollisionEnd(const CollisionResult& result)
{
	if (true == IsDead)
		return;
	if ("PlayerIdentify" == result.Dest->GetCollisionProfile()->Name)
	{
		IsChasing = false;
	}
}


