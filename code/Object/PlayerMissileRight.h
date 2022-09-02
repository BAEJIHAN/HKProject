#pragma once

#include "GameObject/GameObject.h"
#include "Component/SpriteComponent.h"

#include "Component/ColliderBox2D.h"
#include "Component/WidgetComponent.h"

class CPlayerMissileRight :
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

protected:
    CPlayerMissileRight();
    CPlayerMissileRight(const CPlayerMissileRight& obj);
    virtual ~CPlayerMissileRight();

private:
    CSharedPtr<CSpriteComponent>    m_Sprite;
    CSharedPtr<CColliderBox2D>       m_Body;

    float Dist;

public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual CPlayerMissileRight* Clone();
    class CAnimationSequence2DInstance* GetAnimationInstance()  const;

    Vector2 GetColCenterPos()
    {
        return m_Body->GetInfo().Center;
    }

    float GetColTopYPos()
    {
        return m_Body->GetInfo().Max.y;
    }

    float GetColBottomYPos()
    {
        return m_Body->GetInfo().Min.y;
    }

    float GetColLeftXPos()
    {
        return m_Body->GetInfo().Min.x;
    }

    float GetColRightXPos()
    {
        return m_Body->GetInfo().Max.x;
    }

    void SetColExtent(Vector2 vec)
    {
        m_Body->SetExtent(vec.x, vec.y);
    }
public:
    void OnMouseBegin(const CollisionResult& result);
    void OnMouseEnd(const CollisionResult& result);

public:
    void OnCollisionBegin(const CollisionResult& result);
    void OnCollisionEnd(const CollisionResult& result);


};

