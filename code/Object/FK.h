
#pragma once

#include "GameObject/GameObject.h"
#include "Component/SpriteComponent.h"
#include "Monster.h"
#include "../FSM.h"

class CFK :
    public CMonster
{
    friend class CScene;
    friend class CFKHeadLeft;
    friend class CFKHeadRight;
    friend class CCol;

protected:
    CFK(); 
    virtual ~CFK();

private:
    CSharedPtr<CSpriteComponent>    m_Sprite;    
    CSharedPtr<CSceneComponent>     m_Muzzle;
    CSharedPtr<CSpriteComponent>    HitEffect;

    class CFKHeadLeft* LeftHead;
    class CFKHeadRight* RightHead;


    FSM<CFK> CFFSM;

    DIR Dir;
    DIR PlayerDir;
    DIR PrePlayerDir;
    DIR JumpDir;
    DIR AttackDir;
    DIR RollDir;

    int ActNum;

    float PreIdleTime;

    float IdleTime;
    float MoveTime;
    float PreAttackTime;
    float AttackTime;
    float AttackRate;
    float RageRate;
    
    float SwingSoundRate;
    float AttackSoundRate;

    float RockDownRate;

    int RageDir;
    float JumpDist;

    float AppearDist;

    float ChangeDirTime;

    bool ChangeDirOn;
     
    bool IsGroggy;
    bool IsGetAttack;

    int HeadFlag;
    int AttackFlag;


    int hitflag;
    float HitRate;

    
    int fflag;

    int FullHP;
    int m_HP;
    int RHP;

    bool IsTouchedFromLeft;
    bool IsTouchedFromRight;

    bool IsAppearing;

    CSharedPtr<class CSound> AttackSound[5];
    CSharedPtr<class CSound> DamageSound;
    CSharedPtr<class CSound> DamageArmour;
    CSharedPtr<class CSound> JumpSound;
    CSharedPtr<class CSound> LandSound;
    CSharedPtr<class CSound> RollSound;
    CSharedPtr<class CSound> GroundAttackSound;
    CSharedPtr<class CSound> RageSound;
    CSharedPtr<class CSound> EndSound;
    CSharedPtr<class CSound> GroggySound;
    CSharedPtr<class CSound> BG;
   
    float MYPos;


   



public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual CFK* Clone();
    class CAnimationSequence2DInstance* GetAnimationInstance()  const;
    void ChangeAnimation(const std::string& AniName);
    void ChangeState(const std::string& Name);
    void ChangeDir();
    void HitUpdate(float DeltaTime);

    void TakeNextAction();

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

    bool GetIsAttacking()
    {
        return IsAttacking;
    }

    bool GetIsDead()
    {
        return IsDead;
    }

    void SubRHP()
    {
        RHP--;
    }

    int GetRHP()
    {
        return RHP;
    }

   
    void SetIsTouchedFromLeft(bool is)
    {
        IsTouchedFromLeft = is;
    }
    void SetIsTouchedFromRight(bool is)
    {
        IsTouchedFromRight = is;
    }
    bool GetIsTouchedFromLeft()
    {
        return IsTouchedFromLeft;
    }

    bool GetIsTouchedFromRight()
    {
        return IsTouchedFromRight;
    }
public:
    void OnCollisionBegin(const CollisionResult& result);
    void OnCollisionEnd(const CollisionResult& result);

public:
  

private:

    void IDLEStart();
    void IDLEStay();
    void IDLEEnd();

    void PREATTACKStart();
    void PREATTACKStay();
    void PREATTACKEnd();

    void HITGROUNDStart();
    void HITGROUNDStay();
    void HITGROUNDEnd();
         
    void RAGEStart();
    void RAGEStay();
    void RAGEEnd();   

    void GROUNDATTACKStart();
    void GROUNDATTACKStay();
    void GROUNDATTACKEnd();

    void PREJUMPStart();
    void PREJUMPStay();
    void PREJUMPEnd();

    void JUMPStart();
    void JUMPStay();
    void JUMPEnd();

    void JUMPATTACKStart();
    void JUMPATTACKStay();
    void JUMPATTACKEnd();

    void LandStart();
    void LandStay();
    void LandEnd();

    void GROGGYStart();
    void GROGGYStay();
    void GROGGYEnd();

    void ROLLStart();
    void ROLLStay();
    void ROLLEnd();

    void STANDStart();
    void STANDStay();
    void STANDEnd();

    void DEATHStart();
    void DEATHStay();

    void APPEARStart();
    void APPEARStay();
    void APPEAREnd();

    void APPEARLANDStart();
    void APPEARLANDStay();
    void APPEARLANDEnd();
};

