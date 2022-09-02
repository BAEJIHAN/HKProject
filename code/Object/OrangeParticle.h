#pragma once

#include "GameObject/GameObject.h"

class COrangeParticle :
    public CGameObject
{
    friend class CScene;

protected:
    COrangeParticle();
    COrangeParticle(const COrangeParticle& obj);
    virtual ~COrangeParticle();

private:
    CSharedPtr<class CParticleComponent>    m_Particle;

public:
    virtual bool Init();
    virtual COrangeParticle* Clone();
};

