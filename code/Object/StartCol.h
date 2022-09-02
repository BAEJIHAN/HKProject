

#pragma once

#include "GameObject/GameObject.h"
#include "Component/SpriteComponent.h"
#include "Component/ColliderBox2D.h"

class CStartCol :
    public CGameObject
{
    friend class CScene;

protected:
    CStartCol();
    CStartCol(const CStartCol& obj);
    virtual ~CStartCol();

private:
    CSharedPtr<CSpriteComponent>    m_Sprite;
    CSharedPtr<CColliderBox2D>       m_Body;
    CSharedPtr<class CSound> titlebg;

    bool IsOnMouse;

public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual CStartCol* Clone();

    


public:
    void OnMouseBegin(const CollisionResult& result);
    void OnMouseEnd(const CollisionResult& result);


};


