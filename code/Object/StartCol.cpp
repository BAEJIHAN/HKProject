#include "StartCol.h"
#include "Scene/Scene.h"
#include "Resource/Material/Material.h"
#include "Engine.h"
#include "Input.h"
#include "Scene/SceneManager.h"
#include "../Scene/Scene0.h"
#include "../Scene/Scene1.h"
#include "../Scene/Scene2.h"
#include "../Scene/Scene3.h"
#include "../Scene/Scene4.h"

CStartCol::CStartCol()
{
	SetTypeID<CStartCol>();
}

CStartCol::CStartCol(const CStartCol& obj) :
	CGameObject(obj)
{
	m_Sprite = (CSpriteComponent*)FindComponent("FloorSprite");
	m_Body = (CColliderBox2D*)FindComponent("Body");
	IsOnMouse = false;

}

CStartCol::~CStartCol()
{
}

void CStartCol::Start()
{
	CGameObject::Start();


}

bool CStartCol::Init()
{
	m_Sprite = CreateComponent<CSpriteComponent>("FloorSprite");
	m_Body = CreateComponent<CColliderBox2D>("Body");
	titlebg = CResourceManager::GetInst()->FindSound("titlebg");


	SetRootComponent(m_Sprite);

	m_Sprite->AddChild(m_Body);
	



	m_Body->SetCollisionProfile("Floor");
	

	m_Sprite->SetTransparency(true);
	

	m_Sprite->AddTexture(0, (int)Buffer_Shader_Type::Pixel, "blank", TEXT("0_hollow/effect/Blank.png"));
	m_Sprite->SetTexture(0, 0, (int)Buffer_Shader_Type::Pixel, "blank", TEXT("0_hollow/effect/Blank.png"));
	m_Sprite->SetRelativeScale(1, 1, 1.f);

	m_Sprite->SetPivot(0.5f, 0.5f, 0.f);

	m_Body->SetExtent(300, 100);



	m_Body->AddCollisionMouseCallback(Collision_State::Begin, this, &CStartCol::OnMouseBegin);
	m_Body->AddCollisionMouseCallback(Collision_State::End, this, &CStartCol::OnMouseEnd);

	titlebg->Play();
	

	return true;
}

void CStartCol::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
	if (CInput::GetInst()->IsDown("MLButton")&& IsOnMouse)
	{
		titlebg->Stop();
		CSceneManager::GetInst()->CreateNextScene();
		CSceneManager::GetInst()->CreateSceneMode<CScene0>(false);

		/*CSceneManager::GetInst()->CreateNextScene();
		CSceneManager::GetInst()->CreateSceneMode<CScene2>(false);*/

		//CSceneManager::GetInst()->CreateNextScene();
		//CSceneManager::GetInst()->CreateSceneMode<CScene3>(false);

		//CSceneManager::GetInst()->CreateNextScene();
		//CSceneManager::GetInst()->CreateSceneMode<CScene4>(false);

		
	}
}

void CStartCol::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CStartCol* CStartCol::Clone()
{
	return new CStartCol(*this);
}

void CStartCol::OnMouseBegin(const CollisionResult& result)
{
	IsOnMouse = true;

}

void CStartCol::OnMouseEnd(const CollisionResult& result)
{
	IsOnMouse = false;
}


