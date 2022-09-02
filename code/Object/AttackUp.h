
#pragma once

#include "GameObject/GameObject.h"
#include "Component/ColliderBox2D.h"

class CAttackUp :
    public CGameObject
{
    friend class CScene;
    friend class Cdummymonster;
    friend class CLMonster;
    friend class CFMonster;
    friend class CBMonster;
    friend class CFK;
    friend class CFKHeadLeft;
    friend class CFKHeadRight;
    friend class CRockDown;

protected:
    CAttackUp();
    CAttackUp(const CAttackUp& obj);
    virtual ~CAttackUp();

private:
    CSharedPtr<class CSpriteComponent>    m_Sprite;
    CSharedPtr<CColliderBox2D>       m_Body;

    float LifeSpan;

public:
    void SetCollisionProfile(const std::string& Name);

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual CAttackUp* Clone();

    Vector2 GetCenter()
    {
        return m_Body->GetInfo().Center;
    }
public:
    void OnCollisionBegin(const CollisionResult& result);
    void OnCollisionEnd(const CollisionResult& result);
};

