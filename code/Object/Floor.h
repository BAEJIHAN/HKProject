
#pragma once

#include "GameObject/GameObject.h"
#include "Component/SpriteComponent.h"
#include "Component/PaperBurnComponent.h"
#include "Component/ColliderCircle.h"
#include "Component/WidgetComponent.h"
#include "Component/ColliderBox2D.h"

class CFloor :
    public CGameObject
{
    friend class CScene;

protected:
    CFloor();
    CFloor(const CFloor& obj);
    virtual ~CFloor();

private:
    CSharedPtr<CSpriteComponent>    m_Sprite;
    CSharedPtr<CColliderBox2D>       m_Body;
    CSharedPtr<CColliderBox2D>       m_MonBody;
   

  

public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual CFloor* Clone();

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


    //몬스터용 충돌체
    Vector2 MGetColCenterPos()
    {
        return m_MonBody->GetInfo().Center;
    }

    float MGetColTopYPos()
    {
        return m_MonBody->GetInfo().Max.y;
    }

    float MGetColBottomYPos()
    {
        return m_MonBody->GetInfo().Min.y;
    }

    float MGetColLeftXPos()
    {
        return m_MonBody->GetInfo().Min.x;
    }

    float MGetColRightXPos()
    {
        return m_MonBody->GetInfo().Max.x;
    }

    void MSetColExtent(Vector2 vec)
    {
        m_MonBody->SetExtent(vec.x, vec.y);
    }


public:
    void OnCollisionBegin(const CollisionResult& result);
    void OnCollisionEnd(const CollisionResult& result);

    void MOnCollisionBegin(const CollisionResult& result);
    void MOnCollisionEnd(const CollisionResult& result);

};


