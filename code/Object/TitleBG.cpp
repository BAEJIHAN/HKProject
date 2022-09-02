#include "TitleBG.h"
#include "Scene/Scene.h"
#include "Resource/Material/Material.h"


CTitleBG::CTitleBG()
{
	SetTypeID<CTitleBG>();
}

CTitleBG::CTitleBG(const CTitleBG& obj) :
	CGameObject(obj)
{
	m_Sprite = (CSpriteComponent*)FindComponent("FloorSprite");
	

}

CTitleBG::~CTitleBG()
{
}

void CTitleBG::Start()
{
	CGameObject::Start();
}

bool CTitleBG::Init()
{
	m_Sprite = CreateComponent<CSpriteComponent>("title");
	
	SetRootComponent(m_Sprite);
	

	m_Sprite->AddTexture(0, (int)Buffer_Shader_Type::Pixel, "title", TEXT("0_hollow/background/title.png"));
	m_Sprite->SetTexture(0, 0, (int)Buffer_Shader_Type::Pixel, "title", TEXT("0_hollow/background/title.png"));
	m_Sprite->SetRelativeScale(1280, 720, 1.f);

	m_Sprite->SetPivot(0.5f, 0.5f, 0.f);

	


	return true;
}

void CTitleBG::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CTitleBG::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CTitleBG* CTitleBG::Clone()
{
	return new CTitleBG(*this);
}


