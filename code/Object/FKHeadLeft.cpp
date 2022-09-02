#include "FKHeadLeft.h"
#include "Scene/Scene.h"
#include "Resource/Material/Material.h"
#include "FKHeadLeftAnimation.h"

#include "Engine.h"
#include "dummy.h"
#include "AttackLeft.h"
#include "AttackRight.h"
#include "AttackUp.h"
#include "AttackDown.h"
#include "PlayerMissileLeft.h"
#include "PlayerMissileRight.h"
#include "FK.h"

CFKHeadLeft::CFKHeadLeft()
{
	SetTypeID<CFKHeadLeft>();
	IsDead = false;
	m_HP = 3;
	HitTime = 0.f;

	DamageSound = CResourceManager::GetInst()->FindSound("enemydamage");
	MawnSound = CResourceManager::GetInst()->FindSound("fkheaddamage");	
}



CFKHeadLeft::~CFKHeadLeft()
{
}

void CFKHeadLeft::Start()
{
	CGameObject::Start();

}

bool CFKHeadLeft::Init()
{
	m_Sprite = CreateComponent<CSpriteComponent>("monster");
	m_Body = CreateComponent<CColliderBox2D>("Body");


	SetRootComponent(m_Sprite);

	m_Sprite->AddChild(m_Body);




	m_Body->SetCollisionProfile("Monster");

	m_Sprite->SetTransparency(true);
	//m_Sprite->SetOpacity(0.5f);

	m_Sprite->CreateAnimationInstance<CFKHeadLeftAnimation>();

	m_Sprite->SetRelativeScale(550, 480, 1.f);
	m_Sprite->SetRelativePos(500.f, 300.f, 0.f);
	m_Sprite->SetPivot(0.07f, 0.10f, 0.f);

	m_Body->SetExtent(40, 40);

	m_Body->AddCollisionCallback(Collision_State::Begin, this, &CFKHeadLeft::OnCollisionBegin);
	m_Body->AddCollisionCallback(Collision_State::End, this, &CFKHeadLeft::OnCollisionEnd);



	CFHFSM.CreateState("Idle", this, &CFKHeadLeft::IDLEStay, &CFKHeadLeft::IDLEStart, &CFKHeadLeft::IDLEEnd);
	CFHFSM.CreateState("hit", this, &CFKHeadLeft::HITStay, &CFKHeadLeft::HITStart, &CFKHeadLeft::HITEnd);
	CFHFSM.CreateState("death", this, &CFKHeadLeft::DEATHStay, &CFKHeadLeft::DEATHStart, &CFKHeadLeft::DEATHEnd);
	
	



	ChangeState("Idle");

	return true;
}

void CFKHeadLeft::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	CFHFSM.Update();
}

void CFKHeadLeft::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CFKHeadLeft* CFKHeadLeft::Clone()
{
	return new CFKHeadLeft(*this);
}

CAnimationSequence2DInstance* CFKHeadLeft::GetAnimationInstance() const
{
	return m_Sprite->GetAnimationInstance();
}

void CFKHeadLeft::ChangeAnimation(const std::string& AniName)
{
	m_Sprite->GetAnimationInstance()->ChangeAnimation(AniName);
}

void CFKHeadLeft::ChangeState(const std::string& Name)
{
	CFHFSM.ChangeState(Name);
}


void CFKHeadLeft::OnCollisionBegin(const CollisionResult& result)
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

void CFKHeadLeft::OnCollisionEnd(const CollisionResult& result)
{
}


