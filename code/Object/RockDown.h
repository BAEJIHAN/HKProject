#pragma once

#include "GameObject/GameObject.h"
#include "Component/ColliderBox2D.h"
#include "Component/SpriteComponent.h"
#include "../FSM.h"
class CRockDown :
    public CGameObject
{
    friend class CScene;
    friend class CFK;


protected:
    CRockDown();
    CRockDown(const CRockDown& obj);
    virtual ~CRockDown();

private:
    CSharedPtr< CSpriteComponent>    m_Sprite;
    CSharedPtr<CColliderBox2D>       m_Body;
    FSM<CRockDown> RFSM;
    CSharedPtr<class CSound> DamageSound;

    int fflag;
    float RotSpeed;

    bool IsHitFromLeft;
    bool IsHitFromRight;
public:
    void SetCollisionProfile(const std::string& Name);

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual CRockDown* Clone();
    void ChangeState(const std::string& Name);


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
public:
    void OnCollisionBegin(const CollisionResult& result);
    void OnCollisionEnd(const CollisionResult& result);

    void DOWNStart();
    void DOWNStay();
    void DOWNEnd();

    void LEFTStart();
    void LEFTStay();
    void LEFTEnd();

    void RIGHTStart();
    void RIGHTStay();
    void RIGHTEnd();
};


