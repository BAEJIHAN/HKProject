#include "AttackRight.h"
#include "Component/SpriteComponent.h"

CAttackRight::CAttackRight()
{
	SetTypeID<CAttackRight>();
	LifeSpan = 0.1f;
}

CAttackRight::CAttackRight(const CAttackRight& obj) :
	CGameObject(obj)
{
	m_Sprite = (CSpriteComponent*)FindComponent("BulletSprite");
	m_Body = (CColliderBox2D*)FindComponent("Body");

}

CAttackRight::~CAttackRight()
{
}

void CAttackRight::SetCollisionProfile(const std::string& Name)
{
	m_Body->SetCollisionProfile(Name);
}

bool CAttackRight::Init()
{
	m_Sprite = CreateComponent<CSpriteComponent>("BulletSprite");
	m_Body = CreateComponent<CColliderBox2D>("Body");

	SetRootComponent(m_Sprite);
	SetCollisionProfile("PlayerAttack");
	m_Sprite->AddChild(m_Body);
	m_Sprite->AddTexture(0, (int)Buffer_Shader_Type::Pixel, "attackRight", TEXT("0_hollow/effect/PlayerAttackRightEffect.png"));
	m_Sprite->SetTexture(0, 0, (int)Buffer_Shader_Type::Pixel, "attackRight", TEXT("0_hollow/effect/PlayerAttackRightEffect.png"));
	m_Sprite->SetRenderState("AlphaBlend");

	m_Sprite->SetRelativeScale(170.f, 180.f, 1.f);
	m_Body->SetExtent(85.f, 90.f);

	m_Sprite->SetPivot(0.5f, 0.5f, 0.f);

	m_Body->AddCollisionCallback(Collision_State::Begin, this, &CAttackRight::OnCollisionBegin);
	m_Body->AddCollisionCallback(Collision_State::End, this, &CAttackRight::OnCollisionEnd);

	return true;
}

void CAttackRight::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);



	LifeSpan -= DeltaTime;

	if (LifeSpan <= 0.f)
	{
		Destroy();
	}

}

void CAttackRight::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CAttackRight* CAttackRight::Clone()
{
	return new CAttackRight(*this);
}

void CAttackRight::OnCollisionBegin(const CollisionResult& result)
{

}

void CAttackRight::OnCollisionEnd(const CollisionResult& result)
{
}
