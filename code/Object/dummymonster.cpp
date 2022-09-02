#include "dummymonster.h"
#include "Scene/Scene.h"
#include "Resource/Material/Material.h"
#include "dummymonsterAnimation.h"

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
Cdummymonster::Cdummymonster()
{
	SetTypeID<Cdummymonster>();
		
	IdleTime = 0.f;
	MoveTime = 0.f;
	PreAttackTime = 0.f;
	AttackTime = 0.f;
	GetAttackTime = 0.f;
	DeathTime = 0.f;
	AttackRate = 10.f;

	IsDead = false;
	IsAttacking = false;
	IsWalking = false;
	IsChasing = false;
	IsGetAttack = false;
	IsOnColPlayer = false;


	HitRate = 0.f;
	hitflag = 0;


	dist = 1000;

	Dir = DIR::LEFT;
	PlayerDir = DIR::LEFT;
	PrePlayerDir = DIR::LEFT;

	DamageSound = CResourceManager::GetInst()->FindSound("enemydamage");
	AttackSound = CResourceManager::GetInst()->FindSound("monattack");

	MYPos = 0.f;
	m_HP = 3;
	pdummy = nullptr;
}




Cdummymonster::~Cdummymonster()
{
}

void Cdummymonster::Start()
{
	CGameObject::Start();
	pdummy = (Cdummy*)CSceneManager::GetInst()->GetScene()->GetPlayerObject();
}

bool Cdummymonster::Init()
{
	m_Sprite = CreateComponent<CSpriteComponent>("monster");
	m_Body = CreateComponent<CColliderBox2D>("Body");
	m_IBody = CreateComponent<CColliderBox2D>("IBody");

	SetRootComponent(m_Sprite);

	m_Sprite->AddChild(m_Body);
	m_Sprite->AddChild(m_IBody);

	

	m_Body->SetCollisionProfile("Monster");
	m_IBody->SetCollisionProfile("MonsterIdentify");

	m_Sprite->SetTransparency(true);
	//m_Sprite->SetOpacity(0.5f);

	m_Sprite->CreateAnimationInstance<CdummymonsterAnimation>();

	m_Sprite->SetRelativeScale(190.f, 200.f, 1.f);
	m_Sprite->SetRelativePos(500.f, 300.f, 0.f);
	m_Sprite->SetPivot(0.5f, 0.5f, 0.f);

	HitEffect = CreateComponent<CSpriteComponent>("hiteffect");
	m_Sprite->AddChild(HitEffect);
	HitEffect->CreateAnimationInstance<CMHitEffectAnimation>();

	HitEffect->SetRelativeScale(240, 160, 1);
	HitEffect->SetPivot(0.5f, 0.7f, 0.f);
	HitEffect->SetRenderState("AlphaBlend");
	HitEffect->GetAnimationInstance()->ChangeAnimation("hitblank");

	m_Body->SetExtent(60, 90);	

	m_Body->AddCollisionCallback(Collision_State::Begin, this, &Cdummymonster::OnCollisionBegin);
	m_Body->AddCollisionCallback(Collision_State::End, this, &Cdummymonster::OnCollisionEnd);



	m_IBody->SetExtent(400, 100);
	m_IBody->AddCollisionCallback(Collision_State::Begin, this, &Cdummymonster::IOnCollisionBegin);
	m_IBody->AddCollisionCallback(Collision_State::End, this, &Cdummymonster::IOnCollisionEnd);

	HMFSM.CreateState("Idle", this, &Cdummymonster::IDLEStay, &Cdummymonster::IDLEStart);
	

	HMFSM.CreateState("move", this, &Cdummymonster::MOVEStay, &Cdummymonster::MOVEStart, &Cdummymonster::MOVEEnd);
	
	HMFSM.CreateState("attackon", this, &Cdummymonster::ATTACKONStay, &Cdummymonster::ATTACKONStart);
	HMFSM.CreateState("attack", this, &Cdummymonster::ATTACKStay, &Cdummymonster::ATTACKStart, &Cdummymonster::ATTACKEnd);
	HMFSM.CreateState("death", this, &Cdummymonster::DEATHStay, &Cdummymonster::DEATHStart);
	HMFSM.CreateState("getattack", this, &Cdummymonster::GETATTACKStay, &Cdummymonster::GETATTACKStart, &Cdummymonster::GETATTACKEnd);

	HMFSM.ChangeState("Idle");

	return true;
}

void Cdummymonster::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	HMFSM.Update();

	if (false == IsAttacking)
	{
		AttackRate += DeltaTime;
	}

	CheckPlayerPos();

	if (dist <= 400 && IsChasing && false==IsAttacking && AttackRate >=0.5 && false==IsDead)
	{
		AttackRate=0;
		ChangeState("attackon");
	}
	
	if (true == IsGetAttack)
	{
		KnockBack();
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

void Cdummymonster::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

Cdummymonster* Cdummymonster::Clone()
{
	return new Cdummymonster(*this);
}

CAnimationSequence2DInstance* Cdummymonster::GetAnimationInstance() const
{
	return m_Sprite->GetAnimationInstance();
}

void Cdummymonster::ChangeAnimation(const std::string& AniName)
{
	m_Sprite->GetAnimationInstance()->ChangeAnimation(AniName);
}

void Cdummymonster::ChangeState(const std::string& Name)
{
	HMFSM.ChangeState(Name);
}



void Cdummymonster::CheckPlayerPos()
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

void Cdummymonster::KnockBack()
{
	float DeltaTime = CEngine::GetInst()->GetDeltaTime();
	GetAttackTime += DeltaTime;
	if (GetAttackTime <= 0.1)
	{
		if (GetColCenterPos().x < pdummy->GetColCenterPos().x)//오른쪽에서 때릴 때
		{
			m_Sprite->AddRelativePos(Vector3(-1000, 0.f, 0.f) * DeltaTime);
		}
		else if (GetColCenterPos().x >= pdummy->GetColCenterPos().x)//왼쪽에서 때릴 때
		{
			m_Sprite->AddRelativePos(Vector3(+1000, 0.f, 0.f) * DeltaTime);
		}

	}
	if (GetAttackTime >= 0.1)
	{
		IsGetAttack = false;
		GetAttackTime = 0;
	}
}

void Cdummymonster::SetMonPos(float x, float y, float z)
{
	MYPos = y;
	SetRelativePos(x, y, z);
}

void Cdummymonster::HitUpdate(float DeltaTime)
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
	}
}



void Cdummymonster::OnCollisionBegin(const CollisionResult& result)
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

void Cdummymonster::OnCollisionEnd(const CollisionResult& result)
{
	
	if ("Player" == result.Dest->GetCollisionProfile()->Name)
	{
		IsOnColPlayer = false;
	}
}

void Cdummymonster::IOnCollisionBegin(const CollisionResult& result)
{	
	if (true == IsDead)
		return;
	if ("PlayerIdentify"==result.Dest->GetCollisionProfile()->Name)
	{
		IsChasing = true;
	}
}

void Cdummymonster::IOnCollisionEnd(const CollisionResult& result)
{
	
	if (true == IsDead)
		return;
	if ("PlayerIdentify" == result.Dest->GetCollisionProfile()->Name)
	{
		IsChasing = false;
	}
}

