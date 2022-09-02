#include "DashRight.h"
#include "Component/SpriteComponent.h"
#include "DashAnimation.h"

CDashRight::CDashRight()
{
	SetTypeID<CDashRight>();
	LifeSpan = 0.3f;
}

CDashRight::CDashRight(const CDashRight& obj) :
	CGameObject(obj)
{
	m_Sprite = (CSpriteComponent*)FindComponent("dashright");

}

CDashRight::~CDashRight()
{
}



bool CDashRight::Init()
{
	m_Sprite = CreateComponent<CSpriteComponent>("dashright");


	SetRootComponent(m_Sprite);

	m_Sprite->CreateAnimationInstance<CDashAnimation>();
	m_Sprite->SetRelativeScale(250, 250, 1.f);
	m_Sprite->SetRenderState("AlphaBlend");
	m_Sprite->SetPivot(0.5f, 0.5f, 0.f);
	m_Sprite->SetLayerName("BackEffect");
	m_Sprite->GetAnimationInstance()->ChangeAnimation("DashRightEffect");

	return true;
}

void CDashRight::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);



	LifeSpan -= DeltaTime;

	if (LifeSpan <= 0.f)
	{
		Destroy();
	}

}

void CDashRight::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CDashRight* CDashRight::Clone()
{
	return new CDashRight(*this);
}
