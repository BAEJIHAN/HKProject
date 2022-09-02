#pragma once

#include "GameObject/GameObject.h"
#include "Component/SpriteComponent.h"


class CScene3BG :
    public CGameObject
{
    friend class CScene;

protected:
    CScene3BG();
    CScene3BG(const CScene3BG& obj);
    virtual ~CScene3BG();

private:
    CSharedPtr<CSpriteComponent>    m_Sprite;

public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual CScene3BG* Clone();





public:


};


