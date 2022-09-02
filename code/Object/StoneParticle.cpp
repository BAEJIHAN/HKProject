#include "StoneParticle.h"
#include "Component/ParticleComponent.h"

CStoneParticle::CStoneParticle()
{
	SetTypeID<CStoneParticle>();
}

CStoneParticle::CStoneParticle(const CStoneParticle& obj) :
	CGameObject(obj)
{
	m_Particle = (CParticleComponent*)FindComponent("Stone");
}

CStoneParticle::~CStoneParticle()
{
}

bool CStoneParticle::Init()
{
	m_Particle = CreateComponent<CParticleComponent>("Stone");

	SetRootComponent(m_Particle);

	m_Particle->SetParticle("Stone");



	SetLifeSpan(1.4f);

	return true;
}

CStoneParticle* CStoneParticle::Clone()
{
	return new CStoneParticle(*this);
}
