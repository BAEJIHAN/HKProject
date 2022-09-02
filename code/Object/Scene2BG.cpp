#include "Scene2BG.h"
#include "Scene/Scene.h"
#include "Resource/Material/Material.h"


CScene2BG::CScene2BG()
{
	SetTypeID<CScene2BG>();
}

CScene2BG::CScene2BG(const CScene2BG& obj) :
	CGameObject(obj)
{
	m_Sprite = (CSpriteComponent*)FindComponent("FloorSprite");


}

CScene2BG::~CScene2BG()
{
}

void CScene2BG::Start()
{
	CGameObject::Start();
}

bool CScene2BG::Init()
{
	m_Sprite = CreateComponent<CSpriteComponent>("scene2");

	SetRootComponent(m_Sprite);


	m_Sprite->AddTexture(0, (int)Buffer_Shader_Type::Pixel, "scene2", TEXT("0_hollow/background/Scene2BG.png"));
	m_Sprite->SetTexture(0, 0, (int)Buffer_Shader_Type::Pixel, "scene2", TEXT("0_hollow/background/Scene2BG.png"));
	m_Sprite->SetRelativeScale(2554, 4172, 1.f);
	m_Sprite->SetLayerName("Back");
	m_Sprite->SetPivot(0.5f, 0.5f, 0.f);




	return true;
}

void CScene2BG::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CScene2BG::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CScene2BG* CScene2BG::Clone()
{
	return new CScene2BG(*this);
}
