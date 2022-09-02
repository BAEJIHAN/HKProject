#include "AttackUp.h"
#include "Component/SpriteComponent.h"

CAttackUp::CAttackUp()
{
	SetTypeID<CAttackUp>();
	LifeSpan = 0.1f;
}

CAttackUp::CAttackUp(const CAttackUp& obj) :
	CGameObject(obj)
{
	m_Sprite = (CSpriteComponent*)FindComponent("BulletSprite");
	m_Body = (CColliderBox2D*)FindComponent("Body");

}

CAttackUp::~CAttackUp()
{
}

void CAttackUp::SetCollisionProfile(const std::string& Name)
{
	m_Body->SetCollisionProfile(Name);
}

bool CAttackUp::Init()
{
	m_Sprite = CreateComponent<CSpriteComponent>("BulletSprite");
	m_Body = CreateComponent<CColliderBox2D>("Body");

	SetRootComponent(m_Sprite);
	SetCollisionProfile("PlayerAttack");
	m_Sprite->AddChild(m_Body);
	m_Sprite->AddTexture(0, (int)Buffer_Shader_Type::Pixel, "attackUp", TEXT("0_hollow/effect/PlayerAttackUpEffect.png"));
	m_Sprite->SetTexture(0, 0, (int)Buffer_Shader_Type::Pixel, "attackUp", TEXT("0_hollow/effect/PlayerAttackUpEffect.png"));
	m_Sprite->SetRenderState("AlphaBlend");
	m_Sprite->SetRelativeScale(170.f, 180.f, 1.f);
	m_Body->SetExtent(85.f, 90.f);

	m_Sprite->SetPivot(0.5f, 0.5f, 0.f);

	m_Body->AddCollisionCallback(Collision_State::Begin, this, &CAttackUp::OnCollisionBegin);
	m_Body->AddCollisionCallback(Collision_State::End, this, &CAttackUp::OnCollisionEnd);

	return true;
}

void CAttackUp::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);



	LifeSpan -= DeltaTime;

	if (LifeSpan <= 0.f)
	{
		Destroy();
	}

}

void CAttackUp::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CAttackUp* CAttackUp::Clone()
{
	return new CAttackUp(*this);
}

void CAttackUp::OnCollisionBegin(const CollisionResult& result)
{

}

void CAttackUp::OnCollisionEnd(const CollisionResult& result)
{
}
