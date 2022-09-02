
#pragma once

#include "Monster.h"
#include "Component/SpriteComponent.h"


#include "../FSM.h"

class Cdummymonster :
    public CMonster
{
    friend class CScene;
    friend class CFloor;
    friend class CCol;
    
protected:
    Cdummymonster();   
    virtual ~Cdummymonster();

private:
    CSharedPtr<CSpriteComponent>    m_Sprite;
   
    CSharedPtr<CSpriteComponent>    HitEffect;
    FSM<Cdummymonster> HMFSM;
    int                 m_HP;
    DIR Dir;
    DIR PlayerDir;
    DIR PrePlayerDir;
    float IdleTime;
    float MoveTime;
    float PreAttackTime;
    float AttackTime;
    float GetAttackTime;
    float DeathTime;
    float AttackRate;

    int dist;

    int hitflag;
    float HitRate;

    bool IsGetAttack;

   
    bool IsWalking;
    bool IsChasing;

    CSharedPtr<class CSound> DamageSound;
    CSharedPtr<class CSound> AttackSound;

  

    float MYPos;

public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual Cdummymonster* Clone();
    class CAnimationSequence2DInstance* GetAnimationInstance()  const;
    void ChangeAnimation(const std::string& AniName);
    void ChangeState(const std::string& Name); 
    void CheckPlayerPos();
    void KnockBack();
    void SetMonPos(float x,float y,float z);
    void HitUpdate(float DeltaTime);

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

    void GETATTACKStart();
    void GETATTACKStay();
    void GETATTACKEnd();

    void DEATHStart();
    void DEATHStay();
};

