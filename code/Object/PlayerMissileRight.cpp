#include "PlayerMissileRight.h"

#include "Scene/Scene.h"
#include "Resource/Material/Material.h"
#include "dummymonsterAnimation.h"
#include "Engine.h"
#include "dummy.h"
#include "PlayerMissileAnimation.h"

CPlayerMissileRight::CPlayerMissileRight()
{
	SetTypeID<CPlayerMissileRight>();
	Dist = 2000.f;
}

CPlayerMissileRight::CPlayerMissileRight(const CPlayerMissileRight& obj) :
	CGameObject(obj)
{
	m_Sprite = (CSpriteComponent*)FindComponent("monster");
	m_Body = (CColliderBox2D*)FindComponent("Body");

}

CPlayerMissileRight::~CPlayerMissileRight()
{
}

void CPlayerMissileRight::Start()
{
	CGameObject::Start();
	

}

bool CPlayerMissileRight::Init()
{
	m_Sprite = CreateComponent<CSpriteComponent>("monster");
	m_Body = CreateComponent<CColliderBox2D>("Body");


	SetRootComponent(m_Sprite);

	m_Sprite->AddChild(m_Body);




	m_Body->SetCollisionProfile("PlayerAttack");

	m_Sprite->SetTransparency(true);
	//m_Sprite->SetOpacity(0.5f);

	m_Sprite->CreateAnimationInstance<CPlayerMissileAnimation>();
	m_Sprite->GetAnimationInstance()->SetCurrentAnimation("PlayerMissileRight");

	m_Sprite->SetRelativeScale(250.f, 110.f, 0.f);
	m_Sprite->SetRelativePos(500.f, 300.f, 0.f);
	m_Sprite->SetPivot(0.5f, 0.5f, 0.f);
	m_Body->SetExtent(125.f, 55.f);

	m_Body->AddCollisionMouseCallback(Collision_State::Begin, this, &CPlayerMissileRight::OnMouseBegin);
	m_Body->AddCollisionMouseCallback(Collision_State::End, this, &CPlayerMissileRight::OnMouseEnd);

	m_Body->AddCollisionCallback(Collision_State::Begin, this, &CPlayerMissileRight::OnCollisionBegin);
	m_Body->AddCollisionCallback(Collision_State::End, this, &CPlayerMissileRight::OnCollisionEnd);



	return true;
}

void CPlayerMissileRight::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	m_Sprite->AddRelativePos(Vector3(2000.f, 0.f, 0.f) * DeltaTime);

	Dist -= 1000 * DeltaTime;

	if (Dist <= 0.f)
	{
		Destroy();
	}
}

void CPlayerMissileRight::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CPlayerMissileRight* CPlayerMissileRight::Clone()
{
	return new CPlayerMissileRight(*this);
}

CAnimationSequence2DInstance* CPlayerMissileRight::GetAnimationInstance() const
{
	return m_Sprite->GetAnimationInstance();
}

void CPlayerMissileRight::OnMouseBegin(const CollisionResult& result)
{
	CEngine::GetInst()->SetMouseState(Mouse_State::State1);
}

void CPlayerMissileRight::OnMouseEnd(const CollisionResult& result)
{
	CEngine::GetInst()->SetMouseState(Mouse_State::Normal);
}

void CPlayerMissileRight::OnCollisionBegin(const CollisionResult& result)
{

}

void CPlayerMissileRight::OnCollisionEnd(const CollisionResult& result)
{
}
