
#pragma once

#include "GameObject/GameObject.h"

class CDeathBubbleParticle :
    public CGameObject
{
    friend class CScene;

protected:
    CDeathBubbleParticle();
    CDeathBubbleParticle(const CDeathBubbleParticle& obj);
    virtual ~CDeathBubbleParticle();

private:
    CSharedPtr<class CParticleComponent>    m_Particle;

public:
    virtual bool Init();
    virtual CDeathBubbleParticle* Clone();
};

