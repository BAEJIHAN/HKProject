#pragma once

#include "Scene/SceneMode.h"


class CScene0 :
    public CSceneMode
{
public:
    CScene0();
    ~CScene0();

private:


public:
    virtual bool Init();

private:
    void CreateMaterial();
    void CreateAnimationSequence();
    void CreateParticle();

public:

};


