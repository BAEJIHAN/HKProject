#include "AttackLeft.h"
#include "Component/SpriteComponent.h"

CAttackLeft::CAttackLeft() 
{
	SetTypeID<CAttackLeft>();
	LifeSpan = 0.1f;
}

CAttackLeft::CAttackLeft(const CAttackLeft& obj) :
	CGameObject(obj)
{
	m_Sprite = (CSpriteComponent*)FindComponent("BulletSprite");
	m_Body = (CColliderBox2D*)FindComponent("Body");
	
}

CAttackLeft::~CAttackLeft()
{
}

void CAttackLeft::SetCollisionProfile(const std::string& Name)
{
	m_Body->SetCollisionProfile(Name);
}



bool CAttackLeft::Init()
{
	m_Sprite = CreateComponent<CSpriteComponent>("BulletSprite");
	m_Body = CreateComponent<CColliderBox2D>("Body");

	SetRootComponent(m_Sprite);
	SetCollisionProfile("PlayerAttack");
	m_Sprite->AddChild(m_Body);
	m_Sprite->AddTexture(0, (int)Buffer_Shader_Type::Pixel, "attackLeft", TEXT("0_hollow/effect/PlayerAttackLeftEffect.png"));
	
	m_Sprite->SetTexture(0, 0, (int)Buffer_Shader_Type::Pixel, "attackLeft", TEXT("0_hollow/effect/PlayerAttackLeftEffect.png"));
	m_Sprite->SetRenderState("AlphaBlend");

	m_Sprite->SetRelativeScale(170.f, 180.f, 1.f);
	m_Body->SetExtent(85.f, 90.f);

	m_Sprite->SetPivot(0.5f, 0.5f, 0.f);

	m_Body->AddCollisionCallback(Collision_State::Begin, this, &CAttackLeft::OnCollisionBegin);
	m_Body->AddCollisionCallback(Collision_State::End, this, &CAttackLeft::OnCollisionEnd);

	return true;
}

void CAttackLeft::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	

	LifeSpan -= DeltaTime;

	if (LifeSpan <= 0.f)
	{
		Destroy();
	}
	
}

void CAttackLeft::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CAttackLeft* CAttackLeft::Clone()
{
	return new CAttackLeft(*this);
}

void CAttackLeft::OnCollisionBegin(const CollisionResult& result)
{
	
}

void CAttackLeft::OnCollisionEnd(const CollisionResult& result)
{
}
