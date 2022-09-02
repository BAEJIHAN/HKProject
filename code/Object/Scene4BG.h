#pragma once

#include "GameObject/GameObject.h"
#include "Component/SpriteComponent.h"


class CScene4BG :
    public CGameObject
{
    friend class CScene;

protected:
    CScene4BG();
    CScene4BG(const CScene4BG& obj);
    virtual ~CScene4BG();

private:
    CSharedPtr<CSpriteComponent>    m_Sprite;

public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual CScene4BG* Clone();





public:


};


