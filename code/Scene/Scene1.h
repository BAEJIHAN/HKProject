#pragma once

#include "Scene/SceneMode.h"


class CScene1 :
    public CSceneMode
{
public:
    CScene1();
    ~CScene1();

private:


public:
    virtual bool Init();

private:
    void CreateMaterial();
    void CreateAnimationSequence();
    void CreateParticle();

public:

};


