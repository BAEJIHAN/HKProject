#include "Col.h"
#include "Scene/Scene.h"
#include "Resource/Material/Material.h"

#include "Engine.h"
#include "dummy.h"
#include "dummymonster.h"
#include "FK.h"

CCol::CCol()
{
	SetTypeID<CCol>();
}

CCol::CCol(const CCol& obj) :
	CGameObject(obj)
{
	m_Sprite = (CSpriteComponent*)FindComponent("FloorSprite");
	m_Body = (CColliderBox2D*)FindComponent("Body");

}

CCol::~CCol()
{
}

void CCol::Start()
{
	CGameObject::Start();


}

bool CCol::Init()
{
	m_Sprite = CreateComponent<CSpriteComponent>("FloorSprite");
	m_Body = CreateComponent<CColliderBox2D>("Body");
	m_MonBody = CreateComponent<CColliderBox2D>("MBody");


	SetRootComponent(m_Sprite);

	m_Sprite->AddChild(m_Body);
	m_Sprite->AddChild(m_MonBody);



	m_Body->SetCollisionProfile("Floor");
	m_MonBody->SetCollisionProfile("MFloor");

	m_Sprite->SetTransparency(true);
	//m_Sprite->SetOpacity(0.5f);
	//m_ChildLeftSprite->SetTexture(0, 0, (int)Buffer_Shader_Type::Pixel, "Teemo", TEXT("Teemo.jpg"));
	//m_Sprite->CreateAnimationInstance<CMonsterAnimation>();

	m_Sprite->AddTexture(0, (int)Buffer_Shader_Type::Pixel, "blank", TEXT("0_hollow/effect/Blank.png"));
	m_Sprite->SetTexture(0, 0, (int)Buffer_Shader_Type::Pixel, "blank", TEXT("0_hollow/effect/Blank.png"));
	m_Sprite->SetRelativeScale(2000.f, 200.f, 1.f);

	m_Sprite->SetPivot(0.5f, 0.5f, 0.f);

	m_Body->SetExtent(1, 1);
	m_MonBody->SetExtent(1, 1);


	m_Body->AddCollisionCallback(Collision_State::Begin, this, &CCol::OnCollisionBegin);
	m_Body->AddCollisionCallback(Collision_State::End, this, &CCol::OnCollisionEnd);

	m_MonBody->AddCollisionCallback(Collision_State::Begin, this, &CCol::MOnCollisionBegin);
	m_MonBody->AddCollisionCallback(Collision_State::End, this, &CCol::MOnCollisionEnd);


	return true;
}

void CCol::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CCol::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CCol* CCol::Clone()
{
	return new CCol(*this);
}



void CCol::OnCollisionBegin(const CollisionResult& result)
{
	Cdummy tdummy;



	if (result.Dest->GetGameObject()->GetTypeID() == tdummy.GetTypeID())
	{
		Cdummy* dummy = (Cdummy*)result.Dest->GetGameObject();
		dummy->AddWallTouchedCount();
		if (dummy->GetColBottomYPos() + 3 > this->GetColTopYPos())
		{
			dummy->ChangeState("land");
		}
		else if (dummy->GetColTopYPos() - 1 < this->GetColBottomYPos())
		{
			dummy->ChangeState("jumpdown");
			dummy->SetIsTouchedTopWall(true);
		}
		else if (dummy->GetColRightXPos() - 1 < this->GetColLeftXPos())
		{
			dummy->SetIsTouchedRightWall(true);
			if (PHASE::RISING == dummy->GetPhase() || PHASE::FALLING == dummy->GetPhase())
			{
				dummy->SetHangDir(HANGINGDIR::RIGHT);
				dummy->ChangeState("hanging");
			}


		}
		else if (this->GetColRightXPos() < dummy->GetColLeftXPos() + 1)
		{
			dummy->SetIsTouchedLeftWall(true);
			if (PHASE::RISING == dummy->GetPhase() || PHASE::FALLING == dummy->GetPhase())
			{
				dummy->SetHangDir(HANGINGDIR::LEFT);
				dummy->ChangeState("hanging");
			}

		}
	}
	else
	{

	}
}

void CCol::OnCollisionEnd(const CollisionResult& result)
{
	Cdummy tdummy;
	Cdummymonster tdummymonster;
	/*int a = 0;
	int b = 0;
	int c = 0;
	int d = 0;*/

	if (result.Dest->GetGameObject()->GetTypeID() == tdummy.GetTypeID())
	{
		Cdummy* dummy = (Cdummy*)result.Dest->GetGameObject();
		dummy->SubWallTouchedCount();

		dummy->SetIsTouchedTopWall(false);

		if ((dummy->GetColLeftXPos() < this->GetColLeftXPos() ||
			dummy->GetColRightXPos() > this->GetColRightXPos()) && !(dummy->GetOnDash())) //밖으로 떨어질 때 대쉬 중 아님
		{
			/*a = dummy->GetColRightXPos();
			b = this->GetColLeftXPos();
			c = this->GetColRightXPos();
			d = dummy->GetColLeftXPos();*/

			if (dummy->GetColRightXPos() - 3 < (this->GetColLeftXPos()))
			{
				dummy->SetIsTouchedRightWall(false);
			}

			if (this->GetColRightXPos() < (dummy->GetColLeftXPos() + 3))
			{
				dummy->SetIsTouchedLeftWall(false);
			}

			if (0 == dummy->GetWallTouchedCount() && (PHASE::RISING != dummy->GetPhase() || PHASE::FALLING != dummy->GetPhase()))
			{
				if (!dummy->GetIsOnWallJumpl() && !dummy->GetIsJumpl())
					dummy->ChangeState("jumpdown");
			}

		}
		else if ((dummy->GetColLeftXPos() < this->GetColLeftXPos() ||
			dummy->GetColRightXPos() > this->GetColRightXPos()) && (dummy->GetOnDash())) //밖으로 떨어질 때 대쉬 중
		{
			if (dummy->GetColRightXPos() - 3 < (this->GetColLeftXPos()))
			{
				dummy->SetIsTouchedRightWall(false);
			}

			if (this->GetColRightXPos() < (dummy->GetColLeftXPos() + 3))
			{
				dummy->SetIsTouchedLeftWall(false);
			}
			if (0 == dummy->GetWallTouchedCount())
			{

				dummy->SetPhase(PHASE::FALLING);
			}
		}
		else if (dummy->GetColBottomYPos() > this->GetColTopYPos())
		{

		}



	}



}

void CCol::MOnCollisionBegin(const CollisionResult& result)
{
	


}

void CCol::MOnCollisionEnd(const CollisionResult& result)
{
	
}


