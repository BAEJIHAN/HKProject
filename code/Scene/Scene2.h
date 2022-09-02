#pragma once

#include "Scene/SceneMode.h"


class CScene2 :
    public CSceneMode
{
public:
    CScene2();
    ~CScene2();

private:


public:
    virtual bool Init();

private:
    void CreateMaterial();
    void CreateAnimationSequence();
    void CreateParticle();

public:

};


