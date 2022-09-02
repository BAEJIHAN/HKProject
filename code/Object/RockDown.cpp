#include "RockDown.h"
#include "Component/SpriteComponent.h"
#include "dummy.h"
#include "AttackLeft.h"
#include "AttackRight.h"
#include "AttackUp.h"
#include "AttackDown.h"
#include "Resource/Sound/Sound.h"
#include "Resource/ResourceManager.h"
CRockDown::CRockDown()
{
	SetTypeID<CRockDown>();
	DamageSound = CResourceManager::GetInst()->FindSound("enemydamage");
	RotSpeed = 300.f;
	IsHitFromLeft = false;
	IsHitFromRight = false;
	fflag = 0;
}

CRockDown::CRockDown(const CRockDown& obj) :
	CGameObject(obj)
{
	m_Sprite = (CSpriteComponent*)FindComponent("BulletSprite");
	m_Body = (CColliderBox2D*)FindComponent("Body");

}

CRockDown::~CRockDown()
{
}

void CRockDown::SetCollisionProfile(const std::string& Name)
{
	m_Body->SetCollisionProfile(Name);
}

bool CRockDown::Init()
{
	m_Sprite = CreateComponent<CSpriteComponent>("Sprite");
	m_Body = CreateComponent<CColliderBox2D>("Body");

	SetRootComponent(m_Sprite);
	SetCollisionProfile("Rock");
	m_Sprite->AddChild(m_Body);
	m_Sprite->AddTexture(0, (int)Buffer_Shader_Type::Pixel, "rock", TEXT("0_hollow/effect/Rock.png"));
	m_Sprite->SetTexture(0, 0, (int)Buffer_Shader_Type::Pixel, "rock", TEXT("0_hollow/effect/Rock.png"));
	m_Sprite->SetRelativeScale(145.f, 160.f, 1.f);
	m_Body->SetExtent(50.f, 50.f);

	m_Sprite->SetPivot(0.5f, 0.5f, 0.f);
	m_Sprite->SetRelativePos(Vector3(500, 3000, 0));
	m_Body->AddCollisionCallback(Collision_State::Begin, this, &CRockDown::OnCollisionBegin);
	m_Body->AddCollisionCallback(Collision_State::End, this, &CRockDown::OnCollisionEnd);

	RFSM.CreateState("down", this, &CRockDown::DOWNStay, &CRockDown::DOWNStart, &CRockDown::DOWNEnd);
	RFSM.CreateState("left", this, &CRockDown::LEFTStay, &CRockDown::LEFTStart, &CRockDown::LEFTEnd);
	RFSM.CreateState("right", this, &CRockDown::RIGHTStay, &CRockDown::RIGHTStart, &CRockDown::RIGHTEnd);
	ChangeState("down");

	

	return true;
}

void CRockDown::Update(float DeltaTime)
{
	if (0 == fflag)
	{
		fflag++;
		return;
	}
	CGameObject::Update(DeltaTime);
	RFSM.Update();



	if (GetColCenterPos().y<=150)
	{
		Destroy();
	}

	if (GetColRightXPos() >= 2600)
	{
		Destroy();
	}
	
	if (GetColLeftXPos() <= 280)
	{
		Destroy();
	}



	

}

void CRockDown::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CRockDown* CRockDown::Clone()
{
	return new CRockDown(*this);
}

void CRockDown::ChangeState(const std::string& Name)
{
	RFSM.ChangeState(Name);
}

void CRockDown::OnCollisionBegin(const CollisionResult& result)
{
	Cdummy tdummy;
	CAttackDown tAttackDown;
	CAttackRight tAttackRight;
	CAttackLeft tAttackLeft;
	CAttackUp tAttackUp;

	if (result.Dest->GetGameObject()->GetTypeID() == tdummy.GetTypeID())
	{
		Cdummy* dummy = (Cdummy*)result.Dest->GetGameObject();

		dummy->AddMonColCount();

		if (true == dummy->GetIsGetAttackPossible() && false == dummy->GetIsInvincible() && dummy->GetMonColCount() > 0)
		{
			if (dummy->GetColRightXPos() - 10 < this->GetColLeftXPos())
			{

				dummy->SetIsHitFromLeft(false);
			}
			else if (this->GetColRightXPos() < dummy->GetColLeftXPos() + 10)
			{
				dummy->SetIsHitFromLeft(true);
			}

		}

	}

	if (result.Dest->GetGameObject()->GetTypeID() == tAttackDown.GetTypeID() ||
		result.Dest->GetGameObject()->GetTypeID() == tAttackUp.GetTypeID()
	
		)
	{
		DamageSound->Play();
		Destroy();


	}
	
	if (result.Dest->GetGameObject()->GetTypeID() == tAttackLeft.GetTypeID())//오른쪽에서 왼쪽으로 때림
	{
		DamageSound->Play();
		ChangeState("left");
	}
	if (result.Dest->GetGameObject()->GetTypeID() == tAttackRight.GetTypeID())//왼쪽에서 오른쪽으로 때림
	{
		DamageSound->Play();
		ChangeState("right");
	}

}

void CRockDown::OnCollisionEnd(const CollisionResult& result)
{
	Cdummy tdummy;
	if (result.Dest->GetGameObject()->GetTypeID() == tdummy.GetTypeID())
	{

		Cdummy* dummy = (Cdummy*)result.Dest->GetGameObject();
		dummy->SubMonColCount();
	}
}


