#include "Scene2Col.h"
#include "Scene/Scene.h"
#include "Resource/Material/Material.h"
#include "Engine.h"
#include "Input.h"
#include "Scene/SceneManager.h"
#include "../Scene/Scene3.h"
#include "dummy.h"

CScene2Col::CScene2Col()
{
	SetTypeID<CScene2Col>();
}

CScene2Col::CScene2Col(const CScene2Col& obj) :
	CGameObject(obj)
{
	m_Sprite = (CSpriteComponent*)FindComponent("FloorSprite");
	m_Body = (CColliderBox2D*)FindComponent("Body");


}

CScene2Col::~CScene2Col()
{
}

void CScene2Col::Start()
{
	CGameObject::Start();


}

bool CScene2Col::Init()
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

	m_Body->AddCollisionCallback(Collision_State::Begin, this, &CScene2Col::OnCollisionBegin);
	m_Body->AddCollisionCallback(Collision_State::End, this, &CScene2Col::OnCollisionEnd);



	return true;
}

void CScene2Col::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

}

void CScene2Col::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CScene2Col* CScene2Col::Clone()
{
	return new CScene2Col(*this);
}

void CScene2Col::OnCollisionBegin(const CollisionResult& result)
{
	Cdummy tdummy;



	CSceneManager::GetInst()->CreateNextScene();
	CSceneManager::GetInst()->CreateSceneMode<CScene3>(false);
}

void CScene2Col::OnCollisionEnd(const CollisionResult& result)
{
}





