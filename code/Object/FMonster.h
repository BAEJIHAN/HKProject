

#pragma once

#include "Monster.h"
#include "Component/SpriteComponent.h"


#include "../FSM.h"
class CFMonster :
    public CMonster
{
    friend class CScene;

protected:
    CFMonster();

    virtual ~CFMonster();

private:
    CSharedPtr<CSpriteComponent>    m_Sprite;
    CSharedPtr<CSpriteComponent>    HitEffect;

    FSM<CFMonster> FFSM;

    DIR Dir;
    DIR PlayerDir;
    DIR PrePlayerDir;

    float ActTime;
    float FindRate;
    float ChaseSoundRate;
    float GetAttackTime;

    bool IsGetAttack;
    int                 m_HP;

    int hitflag;
    float HitRate;

    CSharedPtr<class CSound> StartleSound;
    CSharedPtr<class CSound> ChaseSound;
    CSharedPtr<class CSound> DamageSound;

    

    Vector2     DirVec;
    bool         MoveOnOff;  
    Vector2 TargetPos;
    int fflag;

public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual CFMonster* Clone();
    class CAnimationSequence2DInstance* GetAnimationInstance()  const;

    void ChangeAnimation(const std::string& AniName);
    void ChangeState(const std::string& Name);
    void ChangeDir();
    void HitUpdate(float DeltaTime);
    void KnockBack();
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

    void FindPlayer(Vector2 v);
    void FMonMove();
  

public:
    void OnMouseBegin(const CollisionResult& result);
    void OnMouseEnd(const CollisionResult& result);

public:
    void OnCollisionBegin(const CollisionResult& result);
    void OnCollisionEnd(const CollisionResult& result);

    void IOnCollisionBegin(const CollisionResult& result);
    void IOnCollisionEnd(const CollisionResult& result);

private:
 

    void IDLEStart();
    void IDLEStay();
    void IDLEEnd();

    void PREATTACKStart();
    void PREATTACKStay();
    void PREATTACKEnd();

    void ATTACKStart();
    void ATTACKStay();
    void ATTACKEnd();

    void DEATHStart();
    void DEATHStay();
    void DEATHEnd();


    //AddAnimation("FMonAttackLeft", "FMonAttackLeft");
    //AddAnimation("FMonAttackRight", "FMonAttackRight");
    //AddAnimation("FMonAttackStartLeft", "FMonAttackStartLeft");
    //AddAnimation("FMonAttackStartRight", "FMonAttackStartRight");
    //AddAnimation("FMonIdleLeft", "FMonIdleLeft");
    //AddAnimation("FMonIdleRight", "FMonIdleRight");
    //AddAnimation("FMonDeathLeft", "FMonDeathLeft");
    //AddAnimation("FMonDeathRight", "FMonDeathRight");
};

