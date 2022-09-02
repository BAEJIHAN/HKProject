#include "FKHeadRight.h"
#include "Scene/Scene.h"
#include "Resource/Material/Material.h"
#include "FKHeadRightAnimation.h"

#include "Engine.h"
#include "dummy.h"
#include "AttackLeft.h"
#include "AttackRight.h"
#include "AttackUp.h"
#include "AttackDown.h"
#include "PlayerMissileLeft.h"
#include "PlayerMissileRight.h"
#include "FK.h"

CFKHeadRight::CFKHeadRight()
{
	SetTypeID<CFKHeadRight>();
	IsDead = false;
	m_HP = 3;
	HitTime=0.f;
	DamageSound = CResourceManager::GetInst()->FindSound("enemydamage");
	MawnSound = CResourceManager::GetInst()->FindSound("fkheaddamage");
}



CFKHeadRight::~CFKHeadRight()
{
}

void CFKHeadRight::Start()
{
	CGameObject::Start();

}

bool CFKHeadRight::Init()
{
	m_Sprite = CreateComponent<CSpriteComponent>("monster");
	m_Body = CreateComponent<CColliderBox2D>("Body");


	SetRootComponent(m_Sprite);

	m_Sprite->AddChild(m_Body);




	m_Body->SetCollisionProfile("Monster");

	m_Sprite->SetTransparency(true);
	//m_Sprite->SetOpacity(0.5f);

	m_Sprite->CreateAnimationInstance<CFKHeadRightAnimation>();

	m_Sprite->SetRelativeScale(550, 480, 1.f);
	m_Sprite->SetRelativePos(500.f, 300.f, 0.f);
	m_Sprite->SetPivot(0.07f, 0.10f, 0.f);

	m_Body->SetExtent(40, 40);

	m_Body->AddCollisionCallback(Collision_State::Begin, this, &CFKHeadRight::OnCollisionBegin);
	m_Body->AddCollisionCallback(Collision_State::End, this, &CFKHeadRight::OnCollisionEnd);

	

	CFHFSM.CreateState("Idle", this, &CFKHeadRight::IDLEStay, &CFKHeadRight::IDLEStart, &CFKHeadRight::IDLEEnd);
	CFHFSM.CreateState("hit", this, &CFKHeadRight::HITStay, &CFKHeadRight::HITStart, &CFKHeadRight::HITEnd);
	CFHFSM.CreateState("death", this, &CFKHeadRight::DEATHStay, &CFKHeadRight::DEATHStart, &CFKHeadRight::DEATHEnd);




	ChangeState("Idle");

	return true;
}

void CFKHeadRight::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	CFHFSM.Update();
}

void CFKHeadRight::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}



CAnimationSequence2DInstance* CFKHeadRight::GetAnimationInstance() const
{
	return m_Sprite->GetAnimationInstance();
}

void CFKHeadRight::ChangeAnimation(const std::string& AniName)
{
	m_Sprite->GetAnimationInstance()->ChangeAnimation(AniName);
}

void CFKHeadRight::ChangeState(const std::string& Name)
{
	CFHFSM.ChangeState(Name);
}


void CFKHeadRight::OnCollisionBegin(const CollisionResult& result)
{
	Cdummy tdummy;
	CAttackDown tAttackDown;
	CAttackRight tAttackRight;
	CAttackLeft tAttackLeft;
	CAttackUp tAttackUp;
	CPlayerMissileRight tMisiileRight;
	CPlayerMissileLeft tMisiileLeft;
	CFK tFK;

	if (result.Dest->GetGameObject()->GetTypeID() == tAttackDown.GetTypeID() ||
		result.Dest->GetGameObject()->GetTypeID() == tAttackUp.GetTypeID() ||
		result.Dest->GetGameObject()->GetTypeID() == tAttackRight.GetTypeID() ||
		result.Dest->GetGameObject()->GetTypeID() == tAttackLeft.GetTypeID() ||
		result.Dest->GetGameObject()->GetTypeID() == tMisiileRight.GetTypeID() ||
		result.Dest->GetGameObject()->GetTypeID() == tMisiileLeft.GetTypeID())
	{
		if (result.Dest->GetGameObject()->GetTypeID() == tAttackDown.GetTypeID())
		{
			Cdummy* dummy = (Cdummy*)result.Dest->GetGameObject()->GetParent();
			dummy->ChangeState("afterdownattack");
		}
		CFK* fk = (CFK*)GetParent();

		if (false == IsDead)
		{
			DamageSound->Play();
			MawnSound->Play();
			ChangeState("hit");
			fk->SubRHP();
			if (0 == fk->GetRHP())
			{
				fk->ChangeState("death");
				ChangeState("death");
			}
		}

	}

}

void CFKHeadRight::OnCollisionEnd(const CollisionResult& result)
{
}
