

#pragma once

#include "Scene/SceneMode.h"


class CScene4 :
    public CSceneMode
{
public:
    CScene4();
    ~CScene4();

private:


public:
    virtual bool Init();

private:
    void CreateMaterial();
    void CreateAnimationSequence();
    void CreateParticle();

public:

};


