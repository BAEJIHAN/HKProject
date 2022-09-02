#include "BMonAttack.h"
#include "Component/SpriteComponent.h"
#include "dummy.h"
#include "BMonAttackAnimation.h"
CBMonAttack::CBMonAttack()
{
	SetTypeID<CBMonAttack>();
	LifeSpan = 0.1f;
}

CBMonAttack::CBMonAttack(const CBMonAttack& obj) :
	CGameObject(obj)
{
	m_Sprite = (CSpriteComponent*)FindComponent("BulletSprite");
	m_Body = (CColliderBox2D*)FindComponent("Body");

}

CBMonAttack::~CBMonAttack()
{
}

void CBMonAttack::SetCollisionProfile(const std::string& Name)
{
	m_Body->SetCollisionProfile(Name);
}

bool CBMonAttack::Init()
{
	m_Sprite = CreateComponent<CSpriteComponent>("Sprite");
	m_Body = CreateComponent<CColliderBox2D>("Body");

	SetRootComponent(m_Sprite);
	SetCollisionProfile("MonsterAttack");
	m_Sprite->AddChild(m_Body);
	m_Sprite->CreateAnimationInstance<CBMonAttackAnimation>();

	m_Sprite->SetRelativeScale(380, 80.f, 1.f);
	
	m_Body->SetExtent(120.f, 120.f);

	m_Sprite->SetPivot(0.5f, 1.35f, 0.f);

	m_Body->AddCollisionCallback(Collision_State::Begin, this, &CBMonAttack::OnCollisionBegin);
	m_Body->AddCollisionCallback(Collision_State::End, this, &CBMonAttack::OnCollisionEnd);

	return true;
}

void CBMonAttack::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);



	LifeSpan -= DeltaTime;

	if (LifeSpan <= 0.f)
	{
		Destroy();
	}

}

void CBMonAttack::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CBMonAttack* CBMonAttack::Clone()
{
	return new CBMonAttack(*this);
}

void CBMonAttack::OnCollisionBegin(const CollisionResult& result)
{
	Cdummy tdummy;
	

	if (result.Dest->GetGameObject()->GetTypeID() == tdummy.GetTypeID())
	{
		Cdummy* dummy = (Cdummy*)result.Dest->GetGameObject();

		dummy->AddMonColCount();

		if (true == dummy->GetIsGetAttackPossible() && false == dummy->GetIsInvincible() && dummy->GetMonColCount() > 0)
		{
			if (dummy->GetColCenterPos().x  <= this->GetColCenterPos().x)
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

void CBMonAttack::OnCollisionEnd(const CollisionResult& result)
{
	Cdummy tdummy;
	if (result.Dest->GetGameObject()->GetTypeID() == tdummy.GetTypeID())
	{

		Cdummy* dummy = (Cdummy*)result.Dest->GetGameObject();
		dummy->SubMonColCount();
	}
}
