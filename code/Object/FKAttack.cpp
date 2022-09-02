#include "FKAttack.h"
#include "Component/SpriteComponent.h"
#include "dummy.h"
#include "BMonAttackAnimation.h"
CFKAttack::CFKAttack()
{
	SetTypeID<CFKAttack>();
	LifeSpan = 0.1f;
}

CFKAttack::CFKAttack(const CFKAttack& obj) :
	CGameObject(obj)
{
	m_Sprite = (CSpriteComponent*)FindComponent("BulletSprite");
	m_Body = (CColliderBox2D*)FindComponent("Body");

}

CFKAttack::~CFKAttack()
{
}

void CFKAttack::SetCollisionProfile(const std::string& Name)
{
	m_Body->SetCollisionProfile(Name);
}

bool CFKAttack::Init()
{
	m_Sprite = CreateComponent<CSpriteComponent>("Sprite");
	m_Body = CreateComponent<CColliderBox2D>("Body");

	SetRootComponent(m_Sprite);
	SetCollisionProfile("MonsterAttack");
	m_Sprite->AddChild(m_Body);
	m_Sprite->CreateAnimationInstance<CBMonAttackAnimation>();

	m_Sprite->SetRelativeScale(380, 80.f, 1.f);

	m_Body->SetExtent(120.f, 120.f);

	m_Sprite->SetPivot(0.5f, 1.85f, 0.f);

	m_Body->AddCollisionCallback(Collision_State::Begin, this, &CFKAttack::OnCollisionBegin);
	m_Body->AddCollisionCallback(Collision_State::End, this, &CFKAttack::OnCollisionEnd);

	return true;
}

void CFKAttack::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);



	LifeSpan -= DeltaTime;

	if (LifeSpan <= 0.f)
	{
		Destroy();
	}

}

void CFKAttack::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CFKAttack* CFKAttack::Clone()
{
	return new CFKAttack(*this);
}

void CFKAttack::OnCollisionBegin(const CollisionResult& result)
{
	Cdummy tdummy;


	if (result.Dest->GetGameObject()->GetTypeID() == tdummy.GetTypeID())
	{
		Cdummy* dummy = (Cdummy*)result.Dest->GetGameObject();

		dummy->AddMonColCount();

		if (true == dummy->GetIsGetAttackPossible() && false == dummy->GetIsInvincible() && dummy->GetMonColCount() > 0)
		{
			if (dummy->GetColCenterPos().x <= this->GetColCenterPos().x)
			{

				dummy->SetIsHitFromLeft(false);
			}
			else if (this->GetColCenterPos().x < dummy->GetColCenterPos().x)
			{
				dummy->SetIsHitFromLeft(true);
			}

		}

	}

}

void CFKAttack::OnCollisionEnd(const CollisionResult& result)
{
	Cdummy tdummy;
	if (result.Dest->GetGameObject()->GetTypeID() == tdummy.GetTypeID())
	{

		Cdummy* dummy = (Cdummy*)result.Dest->GetGameObject();
		dummy->SubMonColCount();
	}
}
