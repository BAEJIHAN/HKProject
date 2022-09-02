
#pragma once

#include "Scene/SceneMode.h"


class CTitleScene :
    public CSceneMode
{
public:
    CTitleScene();
    ~CTitleScene();

private:
  

public:
    virtual bool Init();

private:
    void CreateMaterial();
    void CreateAnimationSequence();
    void CreateParticle();

public:
    
};

