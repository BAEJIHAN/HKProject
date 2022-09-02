#include "DashLeft.h"
#include "Component/SpriteComponent.h"
#include "DashAnimation.h"
CDashLeft::CDashLeft()
{
	SetTypeID<CDashLeft>();
	LifeSpan = 0.3f;
}

CDashLeft::CDashLeft(const CDashLeft& obj) :
	CGameObject(obj)
{
	m_Sprite = (CSpriteComponent*)FindComponent("dashleft");

}

CDashLeft::~CDashLeft()
{
}



bool CDashLeft::Init()
{
	m_Sprite = CreateComponent<CSpriteComponent>("dashleft");


	SetRootComponent(m_Sprite);

	m_Sprite->CreateAnimationInstance<CDashAnimation>();
	m_Sprite->SetRelativeScale(250, 250, 1.f);
	m_Sprite->SetRenderState("AlphaBlend");
	m_Sprite->SetPivot(0.5f, 0.5f, 0.f);
	m_Sprite->SetLayerName("BackEffect");
	

	return true;
}

void CDashLeft::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);



	LifeSpan -= DeltaTime;

	if (LifeSpan <= 0.f)
	{
		Destroy();
	}

}

void CDashLeft::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CDashLeft* CDashLeft::Clone()
{
	return new CDashLeft(*this);
}
