#include "Scene3BG.h"
#include "Scene/Scene.h"
#include "Resource/Material/Material.h"


CScene3BG::CScene3BG()
{
	SetTypeID<CScene3BG>();
}

CScene3BG::CScene3BG(const CScene3BG& obj) :
	CGameObject(obj)
{
	m_Sprite = (CSpriteComponent*)FindComponent("FloorSprite");


}

CScene3BG::~CScene3BG()
{
}

void CScene3BG::Start()
{
	CGameObject::Start();
}

bool CScene3BG::Init()
{
	m_Sprite = CreateComponent<CSpriteComponent>("scene3");

	SetRootComponent(m_Sprite);


	m_Sprite->AddTexture(0, (int)Buffer_Shader_Type::Pixel, "scene3", TEXT("0_hollow/background/Scene3BG.png"));
	m_Sprite->SetTexture(0, 0, (int)Buffer_Shader_Type::Pixel, "scene3", TEXT("0_hollow/background/Scene3BG.png"));
	m_Sprite->SetRelativeScale(3622, 1968, 1.f);
	m_Sprite->SetLayerName("Back");
	m_Sprite->SetPivot(0.5f, 0.5f, 0.f);




	return true;
}

void CScene3BG::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CScene3BG::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CScene3BG* CScene3BG::Clone()
{
	return new CScene3BG(*this);
}
