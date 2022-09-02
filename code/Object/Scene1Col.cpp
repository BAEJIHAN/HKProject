#include "Scene1Col.h"
#include "Scene/Scene.h"
#include "Resource/Material/Material.h"
#include "Engine.h"
#include "Input.h"
#include "Scene/SceneManager.h"
#include "../Scene/Scene2.h"
#include "dummy.h"

CScene1Col::CScene1Col()
{
	SetTypeID<CScene1Col>();
}

CScene1Col::CScene1Col(const CScene1Col& obj) :
	CGameObject(obj)
{
	m_Sprite = (CSpriteComponent*)FindComponent("FloorSprite");
	m_Body = (CColliderBox2D*)FindComponent("Body");
	

}

CScene1Col::~CScene1Col()
{
}

void CScene1Col::Start()
{
	CGameObject::Start();


}

bool CScene1Col::Init()
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

	m_Body->AddCollisionCallback(Collision_State::Begin, this, &CScene1Col::OnCollisionBegin);
	m_Body->AddCollisionCallback(Collision_State::End, this, &CScene1Col::OnCollisionEnd);



	return true;
}

void CScene1Col::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

}

void CScene1Col::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CScene1Col* CScene1Col::Clone()
{
	return new CScene1Col(*this);
}

void CScene1Col::OnCollisionBegin(const CollisionResult& result)
{
	Cdummy tdummy;


	
	CSceneManager::GetInst()->CreateNextScene();
	CSceneManager::GetInst()->CreateSceneMode<CScene2>(false);
	
}

void CScene1Col::OnCollisionEnd(const CollisionResult& result)
{
}





