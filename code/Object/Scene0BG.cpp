#include "Scene0BG.h"
#include "Scene/Scene.h"
#include "Resource/Material/Material.h"

CScene0BG::CScene0BG()
{
	SetTypeID<CScene0BG>();
}

CScene0BG::CScene0BG(const CScene0BG& obj) :
	CGameObject(obj)
{
	m_Sprite = (CSpriteComponent*)FindComponent("FloorSprite");


}

CScene0BG::~CScene0BG()
{
}

void CScene0BG::Start()
{
	CGameObject::Start();
}

bool CScene0BG::Init()
{
	m_Sprite = CreateComponent<CSpriteComponent>("bg0");

	SetRootComponent(m_Sprite);


	m_Sprite->AddTexture(0, (int)Buffer_Shader_Type::Pixel, "bg0", TEXT("0_hollow/background/Scene0BG.png"));
	m_Sprite->SetTexture(0, 0, (int)Buffer_Shader_Type::Pixel, "bg0", TEXT("0_hollow/background/Scene0BG.png"));
	m_Sprite->SetRelativeScale(1731.f, 1100.f, 1.f);
	m_Sprite->SetLayerName("Back");
	m_Sprite->SetPivot(0.5f, 0.5f, 0.f);




	return true;
}

void CScene0BG::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CScene0BG::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CScene0BG* CScene0BG::Clone()
{
	return new CScene0BG(*this);
}
