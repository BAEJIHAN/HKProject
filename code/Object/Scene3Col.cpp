#include "Scene3Col.h"
#include "Scene/Scene.h"
#include "Resource/Material/Material.h"
#include "Engine.h"
#include "Input.h"
#include "Scene/SceneManager.h"
#include "../Scene/Scene4.h"
#include "dummy.h"

CScene3Col::CScene3Col()
{
	SetTypeID<CScene3Col>();
}

CScene3Col::CScene3Col(const CScene3Col& obj) :
	CGameObject(obj)
{
	m_Sprite = (CSpriteComponent*)FindComponent("FloorSprite");
	m_Body = (CColliderBox2D*)FindComponent("Body");


}

CScene3Col::~CScene3Col()
{
}

void CScene3Col::Start()
{
	CGameObject::Start();


}

bool CScene3Col::Init()
{
	m_Sprite = CreateComponent<CSpriteComponent>("FloorSprite");
	m_Body = CreateComponent<CColliderBox2D>("Body");



	SetRootComponent(m_Sprite);

	m_Sprite->AddChild(m_Body);




	m_Body->SetCollisionProfile("Floor");


	m_Sprite->SetTransparency(true);


	m_Sprite->AddTexture(0, (int)Buffer_Shader_Type::Pixel, "blank", TEXT("0_hollow/effect/Blank.png"));
	m_Sprite->SetTexture(0, 0, (int)Buffer_Shader_Type::Pixel, "blank", TEXT("0_hollow/effect/Blank.png"));
	m_Sprite->SetRelativeScale(1, 1, 1.f);

	m_Sprite->SetPivot(0.5f, 0.5f, 0.f);

	m_Body->SetExtent(60, 80);

	m_Body->AddCollisionCallback(Collision_State::Begin, this, &CScene3Col::OnCollisionBegin);
	m_Body->AddCollisionCallback(Collision_State::End, this, &CScene3Col::OnCollisionEnd);



	return true;
}

void CScene3Col::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

}

void CScene3Col::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CScene3Col* CScene3Col::Clone()
{
	return new CScene3Col(*this);
}

void CScene3Col::OnCollisionBegin(const CollisionResult& result)
{
	Cdummy tdummy;



	CSceneManager::GetInst()->CreateNextScene();
	CSceneManager::GetInst()->CreateSceneMode<CScene4>(false);
}

void CScene3Col::OnCollisionEnd(const CollisionResult& result)
{
}





