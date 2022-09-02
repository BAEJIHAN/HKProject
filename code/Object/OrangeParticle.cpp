#include "OrangeParticle.h"
#include "Component/ParticleComponent.h"

COrangeParticle::COrangeParticle()
{
	SetTypeID<COrangeParticle>();
}

COrangeParticle::COrangeParticle(const COrangeParticle& obj) :
	CGameObject(obj)
{
	m_Particle = (CParticleComponent*)FindComponent("Orange");
}

COrangeParticle::~COrangeParticle()
{
}

bool COrangeParticle::Init()
{
	m_Particle = CreateComponent<CParticleComponent>("Orange");

	SetRootComponent(m_Particle);
	
	m_Particle->SetParticle("Orange");
	

	
	SetLifeSpan(0.8f);
	
	return true;
}

COrangeParticle* COrangeParticle::Clone()
{
	return new COrangeParticle(*this);
}
