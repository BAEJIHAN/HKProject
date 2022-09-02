#pragma once

#include "Scene/SceneMode.h"


class CScene3 :
    public CSceneMode
{
public:
    CScene3();
    ~CScene3();

private:


public:
    virtual bool Init();

private:
    void CreateMaterial();
    void CreateAnimationSequence();
    void CreateParticle();

public:

};


