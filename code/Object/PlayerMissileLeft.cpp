#include "PlayerMissileLeft.h"

#include "Scene/Scene.h"
#include "Resource/Material/Material.h"
#include "dummymonsterAnimation.h"

#include "Engine.h"
#include "dummy.h"
#include "PlayerMissileAnimation.h"

CPlayerMissileLeft::CPlayerMissileLeft()
{
	SetTypeID<CPlayerMissileLeft>();
	Dist = 2000.f;
}

CPlayerMissileLeft::CPlayerMissileLeft(const CPlayerMissileLeft& obj) :
	CGameObject(obj)
{
	m_Sprite = (CSpriteComponent*)FindComponent("monster");
	m_Body = (CColliderBox2D*)FindComponent("Body");

}

CPlayerMissileLeft::~CPlayerMissileLeft()
{
}

void CPlayerMissileLeft::Start()
{
	CGameObject::Start();

}

bool CPlayerMissileLeft::Init()
{
	m_Sprite = CreateComponent<CSpriteComponent>("monster");
	m_Body = CreateComponent<CColliderBox2D>("Body");


	SetRootComponent(m_Sprite);

	m_Sprite->AddChild(m_Body);




	m_Body->SetCollisionProfile("PlayerAttack");

	m_Sprite->SetTransparency(true);
	//m_Sprite->SetOpacity(0.5f);

	m_Sprite->CreateAnimationInstance<CPlayerMissileAnimation>();
	m_Sprite->GetAnimationInstance()->ChangeAnimation("PlayerMissileLeft");

	m_Sprite->SetRelativeScale(250.f, 110.f, 0.f);
	m_Sprite->SetRelativePos(500.f, 300.f, 0.f);
	m_Sprite->SetPivot(0.5f, 0.5f, 0.f);
	m_Body->SetExtent(125.f, 55.f);

	m_Body->AddCollisionMouseCallback(Collision_State::Begin, this, &CPlayerMissileLeft::OnMouseBegin);
	m_Body->AddCollisionMouseCallback(Collision_State::End, this, &CPlayerMissileLeft::OnMouseEnd);

	m_Body->AddCollisionCallback(Collision_State::Begin, this, &CPlayerMissileLeft::OnCollisionBegin);
	m_Body->AddCollisionCallback(Collision_State::End, this, &CPlayerMissileLeft::OnCollisionEnd);



	return true;
}

void CPlayerMissileLeft::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	m_Sprite->AddRelativePos(Vector3(-2000.f, 0.f, 0.f) * DeltaTime);

	Dist -= 1000*DeltaTime;

	if (Dist <= 0.f)
	{
		Destroy();
	}
}

void CPlayerMissileLeft::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CPlayerMissileLeft* CPlayerMissileLeft::Clone()
{
	return new CPlayerMissileLeft(*this);
}

CAnimationSequence2DInstance* CPlayerMissileLeft::GetAnimationInstance() const
{
	return m_Sprite->GetAnimationInstance();
}

void CPlayerMissileLeft::OnMouseBegin(const CollisionResult& result)
{
	CEngine::GetInst()->SetMouseState(Mouse_State::State1);
}

void CPlayerMissileLeft::OnMouseEnd(const CollisionResult& result)
{
	CEngine::GetInst()->SetMouseState(Mouse_State::Normal);
}

void CPlayerMissileLeft::OnCollisionBegin(const CollisionResult& result)
{
	
}

void CPlayerMissileLeft::OnCollisionEnd(const CollisionResult& result)
{
}
