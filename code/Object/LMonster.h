
#pragma once


#include "Component/SpriteComponent.h"
#include "Monster.h"
#include "../FSM.h"

class CLMonster :
    public CMonster
{
    friend class CScene;

protected:
    CLMonster();
    virtual ~CLMonster();

private:
    CSharedPtr<CSpriteComponent>    m_Sprite;  
    CSharedPtr<CSpriteComponent>    HitEffect;
    FSM<CLMonster> LMFSM;

   
    int                 m_HP;
    DIR Dir;
    DIR PlayerDir;
    DIR PrePlayerDir;

    float IdleTime;
    float MoveTime;
    float PreAttackTime;
    float AttackTime;

    float DeathTime;
    float GetAttackTime;
    float ChangeDirDist;
  
    float OrangeTime;
       
    bool IsWalking;
    bool IsChasing;

    int hitflag;
    float HitRate;
    float AttackRate;

    int dist;

    bool IsGetAttack;
    CSharedPtr<class CSound> DamageSound;
    CSharedPtr<class CSound> AttackSound;

    float MYPos;

public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual CLMonster* Clone();
    class CAnimationSequence2DInstance* GetAnimationInstance()  const;
    void ChangeAnimation(const std::string& AniName);
    void ChangeState(const std::string& Name);
    void CheckPlayerPos();
    void KnockBack();
    void HitUpdate(float DeltaTime);


    void SetMonPos(float x, float y, float z);

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
   
public:
    void OnCollisionBegin(const CollisionResult& result);
    void OnCollisionEnd(const CollisionResult& result);

    void IOnCollisionBegin(const CollisionResult& result);
    void IOnCollisionEnd(const CollisionResult& result);

private: 

    void IDLEStart();
    void IDLEStay();

    void MOVEStart();
    void MOVEStay();
    void MOVEEnd();

    void ATTACKONStart();
    void ATTACKONStay();

    void ATTACKStart();
    void ATTACKStay();
    void ATTACKEnd();

    void DEATHStart();
    void DEATHStay();
};

