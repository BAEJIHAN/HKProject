#pragma once

#include "GameObject/GameObject.h"
#include "Component/SpriteComponent.h"


class CTitleBG :
    public CGameObject
{
    friend class CScene;

protected:
    CTitleBG();
    CTitleBG(const CTitleBG& obj);
    virtual ~CTitleBG();

private:
    CSharedPtr<CSpriteComponent>    m_Sprite;

public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual CTitleBG* Clone();

  


    
public:
   

};


