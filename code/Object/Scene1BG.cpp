#include "Scene1BG.h"
#include "Scene/Scene.h"
#include "Resource/Material/Material.h"


CScene1BG::CScene1BG()
{
	SetTypeID<CScene1BG>();
}

CScene1BG::CScene1BG(const CScene1BG& obj) :
	CGameObject(obj)
{
	m_Sprite = (CSpriteComponent*)FindComponent("FloorSprite");


}

CScene1BG::~CScene1BG()
{
}

void CScene1BG::Start()
{
	CGameObject::Start();
}

bool CScene1BG::Init()
{
	m_Sprite = CreateComponent<CSpriteComponent>("bg1");

	SetRootComponent(m_Sprite);


	m_Sprite->AddTexture(0, (int)Buffer_Shader_Type::Pixel, "bg1", TEXT("0_hollow/background/Scene1BG.png"));
	m_Sprite->SetTexture(0, 0, (int)Buffer_Shader_Type::Pixel, "bg1", TEXT("0_hollow/background/Scene1BG.png"));
	m_Sprite->SetRelativeScale(4944, 1500, 1.f);
	m_Sprite->SetLayerName("Back");
	m_Sprite->SetPivot(0.5f, 0.5f, 0.f);




	return true;
}

void CScene1BG::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CScene1BG::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CScene1BG* CScene1BG::Clone()
{
	return new CScene1BG(*this);
}
