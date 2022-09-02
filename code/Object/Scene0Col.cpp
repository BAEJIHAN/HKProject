#include "Scene0Col.h"
#include "Scene/Scene.h"
#include "Resource/Material/Material.h"
#include "Engine.h"
#include "Input.h"
#include "Scene/SceneManager.h"
#include "../Scene/Scene1.h"
#include "dummy.h"

CScene0Col::CScene0Col()
{
	SetTypeID<CScene0Col>();
}

CScene0Col::CScene0Col(const CScene0Col& obj) :
	CGameObject(obj)
{
	m_Sprite = (CSpriteComponent*)FindComponent("FloorSprite");
	m_Body = (CColliderBox2D*)FindComponent("Body");


}

CScene0Col::~CScene0Col()
{
}

void CScene0Col::Start()
{
	CGameObject::Start();


}

bool CScene0Col::Init()
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

	m_Body->AddCollisionCallback(Collision_State::Begin, this, &CScene0Col::OnCollisionBegin);
	m_Body->AddCollisionCallback(Collision_State::End, this, &CScene0Col::OnCollisionEnd);



	return true;
}

void CScene0Col::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

}

void CScene0Col::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CScene0Col* CScene0Col::Clone()
{
	return new CScene0Col(*this);
}

void CScene0Col::OnCollisionBegin(const CollisionResult& result)
{
	Cdummy tdummy;



	CSceneManager::GetInst()->CreateNextScene();
	CSceneManager::GetInst()->CreateSceneMode<CScene1>(false);

}

void CScene0Col::OnCollisionEnd(const CollisionResult& result)
{
}





