#pragma once
#include "GameObject/GameObject.h"


class CDashRight :
    public CGameObject
{

    friend class Cdummy;
    friend class CScene;

protected:
    CDashRight();
    CDashRight(const CDashRight& obj);
    virtual ~CDashRight();

private:
    CSharedPtr<class CSpriteComponent>    m_Sprite;


    float LifeSpan;

public:


public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual CDashRight* Clone();



public:

};

