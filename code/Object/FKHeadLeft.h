#pragma once

#include "Monster.h"
#include "Component/SpriteComponent.h"

#include "../FSM.h"

class CFKHeadLeft :
    public CMonster
{
    friend class CScene;
    friend class CFK;

protected:
    CFKHeadLeft();  
    virtual ~CFKHeadLeft();

private:
    CSharedPtr<CSpriteComponent>    m_Sprite;
   
    FSM<CFKHeadLeft> CFHFSM;
  
    bool IsDead;
    float HitTime;
    int                 m_HP;
    
    CSharedPtr<class CSound> DamageSound;
    CSharedPtr<class CSound> MawnSound;
public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual CFKHeadLeft* Clone();
    class CAnimationSequence2DInstance* GetAnimationInstance()  const;
    void ChangeAnimation(const std::string& AniName);
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

private:
    void IDLEStart();
    void IDLEStay();
    void IDLEEnd();

    void HITStart();
    void HITStay();
    void HITEnd();

    void DEATHStart();
    void DEATHStay();
    void DEATHEnd();

};

