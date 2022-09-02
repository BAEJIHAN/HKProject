
#pragma once

#include "GameObject/GameObject.h"
#include "Component/SpriteComponent.h"


class CScene0BG :
    public CGameObject
{
    friend class CScene;

protected:
    CScene0BG();
    CScene0BG(const CScene0BG& obj);
    virtual ~CScene0BG();

private:
    CSharedPtr<CSpriteComponent>    m_Sprite;

public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual CScene0BG* Clone();





public:


};


