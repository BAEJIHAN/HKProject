#include "Scene4BG.h"
#include "Scene/Scene.h"
#include "Resource/Material/Material.h"


CScene4BG::CScene4BG()
{
	SetTypeID<CScene4BG>();
}

CScene4BG::CScene4BG(const CScene4BG& obj) :
	CGameObject(obj)
{
	m_Sprite = (CSpriteComponent*)FindComponent("FloorSprite");


}

CScene4BG::~CScene4BG()
{
}

void CScene4BG::Start()
{
	CGameObject::Start();
}

bool CScene4BG::Init()
{
	m_Sprite = CreateComponent<CSpriteComponent>("scene4");

	SetRootComponent(m_Sprite);


	m_Sprite->AddTexture(0, (int)Buffer_Shader_Type::Pixel, "scene4", TEXT("0_hollow/background/Scene4BG.png"));
	m_Sprite->SetTexture(0, 0, (int)Buffer_Shader_Type::Pixel, "scene4", TEXT("0_hollow/background/Scene4BG.png"));
	m_Sprite->SetRelativeScale(3246, 1100, 1.f);
	m_Sprite->SetLayerName("Back");
	m_Sprite->SetPivot(0.5f, 0.5f, 0.f);




	return true;
}

void CScene4BG::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CScene4BG::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CScene4BG* CScene4BG::Clone()
{
	return new CScene4BG(*this);
}