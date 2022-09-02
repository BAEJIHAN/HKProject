#include "DeathBubbleParticle.h"
#include "Component/ParticleComponent.h"

CDeathBubbleParticle::CDeathBubbleParticle()
{
	SetTypeID<CDeathBubbleParticle>();
}

CDeathBubbleParticle::CDeathBubbleParticle(const CDeathBubbleParticle& obj) :
	CGameObject(obj)
{
	m_Particle = (CParticleComponent*)FindComponent("Deathbubble");
}

CDeathBubbleParticle::~CDeathBubbleParticle()
{
}

bool CDeathBubbleParticle::Init()
{
	m_Particle = CreateComponent<CParticleComponent>("Deathbubble");

	SetRootComponent(m_Particle);

	m_Particle->SetParticle("Deathbubble");



	SetLifeSpan(3);

	return true;
}

CDeathBubbleParticle* CDeathBubbleParticle::Clone()
{
	return new CDeathBubbleParticle(*this);
}
