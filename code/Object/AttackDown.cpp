#include "AttackDown.h"
#include "Component/SpriteComponent.h"

CAttackDown::CAttackDown()
{
	SetTypeID<CAttackDown>();
	LifeSpan = 0.1f;
}

CAttackDown::CAttackDown(const CAttackDown& obj) :
	CGameObject(obj)
{
	m_Sprite = (CSpriteComponent*)FindComponent("BulletSprite");
	m_Body = (CColliderBox2D*)FindComponent("Body");

}

CAttackDown::~CAttackDown()
{
}

void CAttackDown::SetCollisionProfile(const std::string& Name)
{
	m_Body->SetCollisionProfile(Name);
}

bool CAttackDown::Init()
{
	m_Sprite = CreateComponent<CSpriteComponent>("BulletSprite");
	m_Body = CreateComponent<CColliderBox2D>("Body");

	SetRootComponent(m_Sprite);
	SetCollisionProfile("PlayerAttack");
	m_Sprite->AddChild(m_Body);
	m_Sprite->AddTexture(0, (int)Buffer_Shader_Type::Pixel, "attackDown", TEXT("0_hollow/effect/PlayerAttackDownEffect.png"));
	m_Sprite->SetTexture(0, 0, (int)Buffer_Shader_Type::Pixel, "attackDown", TEXT("0_hollow/effect/PlayerAttackDownEffect.png"));
	m_Sprite->SetRenderState("AlphaBlend");
	m_Sprite->SetRelativeScale(170.f, 180.f, 1.f);
	m_Body->SetExtent(85.f, 90.f);

	m_Sprite->SetPivot(0.5f, 0.5f, 0.f);

	m_Body->AddCollisionCallback(Collision_State::Begin, this, &CAttackDown::OnCollisionBegin);
	m_Body->AddCollisionCallback(Collision_State::End, this, &CAttackDown::OnCollisionEnd);

	return true;
}

void CAttackDown::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);



	LifeSpan -= DeltaTime;

	if (LifeSpan <= 0.f)
	{
		Destroy();
	}

}

void CAttackDown::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CAttackDown* CAttackDown::Clone()
{
	return new CAttackDown(*this);
}

void CAttackDown::OnCollisionBegin(const CollisionResult& result)
{

}

void CAttackDown::OnCollisionEnd(const CollisionResult& result)
{
}
