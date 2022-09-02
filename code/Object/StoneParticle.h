#pragma once

#include "GameObject/GameObject.h"

class CStoneParticle :
    public CGameObject
{
    friend class CScene;

protected:
    CStoneParticle();
    CStoneParticle(const CStoneParticle& obj);
    virtual ~CStoneParticle();

private:
    CSharedPtr<class CParticleComponent>    m_Particle;

public:
    virtual bool Init();
    virtual CStoneParticle* Clone();
};

