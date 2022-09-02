#pragma once
#include "GameObject/GameObject.h"


class CDashLeft :
    public CGameObject
{

    friend class Cdummy;
    friend class CScene;

protected:
    CDashLeft();
    CDashLeft(const CDashLeft& obj);
    virtual ~CDashLeft();

private:
    CSharedPtr<class CSpriteComponent>    m_Sprite;


    float LifeSpan;

public:


public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual CDashLeft* Clone();



public:

};

