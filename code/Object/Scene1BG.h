#pragma once

#include "GameObject/GameObject.h"
#include "Component/SpriteComponent.h"


class CScene1BG :
    public CGameObject
{
    friend class CScene;

protected:
    CScene1BG();
    CScene1BG(const CScene1BG& obj);
    virtual ~CScene1BG();

private:
    CSharedPtr<CSpriteComponent>    m_Sprite;

public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual CScene1BG* Clone();





public:


};


