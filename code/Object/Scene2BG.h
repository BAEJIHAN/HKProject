#pragma once

#include "GameObject/GameObject.h"
#include "Component/SpriteComponent.h"


class CScene2BG :
    public CGameObject
{
    friend class CScene;

protected:
    CScene2BG();
    CScene2BG(const CScene2BG& obj);
    virtual ~CScene2BG();

private:
    CSharedPtr<CSpriteComponent>    m_Sprite;

public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual CScene2BG* Clone();





public:


};


