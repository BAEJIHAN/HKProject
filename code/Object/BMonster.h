#pragma once

#include "Monster.h"
#include "Component/SpriteComponent.h"
#include "../FSM.h"

class CBMonster :
    public CMonster
{
    friend class CScene;

protected:
    CBMonster();  
    virtual ~CBMonster();

private:
    CSharedPtr<CSpriteComponent>    m_Sprite; 
    CSharedPtr<CSpriteComponent>    HitEffect;
    CSharedPtr<CSceneComponent>     m_Muzzle;

    FSM<CBMonster> BMFSM;
 
    class Cdummy* pdummy;

    DIR Dir;
    DIR PlayerDir;
    DIR PrePlayerDir;

    float IdleTime;
    float MoveTime;
    float PreAttackTime;
    float AttackTime;
    float AttackRate;
    

    float ChangeDirTime;
    float DeathTime;

    int hitflag;
    float HitRate;

    int dist;

    bool IsGetAttack;
    bool ChangeDirOn;
    bool IsChasing;
    bool IsWalking;

    int fflag;
    int AttackFlag;

    int m_HP;

    CSharedPtr<class CSound> DamageSound;
    CSharedPtr<class CSound> AttackSound;
    CSharedPtr<class CSound> RunSound;
    CSharedPtr<class CSound> GroundSound;
   
public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual CBMonster* Clone();
    class CAnimationSequence2DInstance* GetAnimationInstance()  const;
    void ChangeAnimation(const std::string& AniName);
    void ChangeState(const std::string& Name);
    void ChangeDir();
    void CheckPlayerPos();
    void Chase();
    void HitUpdate(float DeltaTime);

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

    bool GetIsAttacking()
    {
        return IsAttacking;
    }

    bool GetIsDead()
    {
        return IsDead;
    }

public:
    void OnCollisionBegin(const CollisionResult& result);
    void OnCollisionEnd(const CollisionResult& result);

public:
    void IOnCollisionBegin(const CollisionResult& result);
    void IOnCollisionEnd(const CollisionResult& result);

private:
    void IDLEStart();
    void IDLEStay();

    void MOVEStart();
    void MOVEStay();
    void MOVEEnd();

    void STOMPStart();
    void STOMPStay();

    void ATTACKStart();
    void ATTACKStay();
    void ATTACKEnd();

    void DEATHStart();
    void DEATHStay();
};

