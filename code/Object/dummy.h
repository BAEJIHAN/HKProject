
#pragma once

#include "GameObject/GameObject.h"
#include "Component/SpriteComponent.h"
#include "Component/ColliderBox2D.h"
#include "Component/CameraComponent.h"


#include "../FSM.h"
#include "../Widget/HP.h"



enum class DASHDIR
{
    LEFT,
    RIGHT,
};

enum class HANGINGDIR
{
    LEFT,
    RIGHT,
};


class Cdummy :
    public CGameObject
{
    friend class CFloor;
    friend class CScene;
    friend class CdummyAnimation;
    friend class Cdummymonster;
    friend class CLMonster;
    friend class CFMonster;
    friend class CBMonster;
    friend class CBMonAttack;
    friend class CFK;
    friend class CFKHeadLeft;
    friend class CFKHeadRight;
    friend class CRockDown;
    friend class CCol;
    friend class CScene0Col;
    friend class CScene1Col;
    friend class CScene2Col;
    friend class CScene3Col;
    friend class CFKAttack;
protected:
    Cdummy();
    Cdummy(const Cdummy& obj);
    virtual ~Cdummy();

private:
    FSM<Cdummy> PlayerFSM;
    CSharedPtr<CHP> HPWidget;
    CSharedPtr<CSpriteComponent>    m_Sprite;   
    CSharedPtr<CColliderBox2D>       m_Body;
    CSharedPtr<CColliderBox2D>       m_IBody;
    CSharedPtr<CColliderBox2D>       m_FBody;

    CSharedPtr<CCameraComponent>     m_Camera;
  
    CSharedPtr<CSceneComponent>     m_Muzzle;
  
    Vector2 CurMapSize;

    CSharedPtr<CSpriteComponent>    DashleftEffect;
    CSharedPtr<CSpriteComponent>    DashrightEffect;

    CSharedPtr<CSpriteComponent>    WingLeft;
    CSharedPtr<CSpriteComponent>    WingRight;

    CSharedPtr<CSpriteComponent>    SkillLeftEffect;
    CSharedPtr<CSpriteComponent>    SkillRightEffect;

    CSharedPtr<CSpriteComponent>    GetAttackEffect;
    int WallTouchedCount;
    int MonColCount;

 

    bool DebugOn;

    bool IsOnAttack;

    bool IsDoubleJumped;
    bool IsOnJump;

    bool IsDirChanged;
  
    bool IsDashed;
    bool IsOnDash;

    bool IsHitFromLeft;

    bool IsTouchedLeftWall;
    bool IsTouchedRightWall;
    bool IsTouchedTopWall;

    bool IsHanging;

    bool IsOnWallJump;

    bool IsInvincible;

    bool IsBeingAttack;

    bool IsOnEvent;
 

    bool IsGetAttackPossible;
    float       GetAttackRate;


    bool IsCanAttack;
    float AttackRate;

    float HaningTime;
    float PRunTime;

    float TextOpacity;

    PHASE Phase;

    CurMap Map;
    DASHDIR DashDir;
    DIR Dir;
    DIR PreDir;
    HANGINGDIR HangDir;


    CSharedPtr<class CSound> DamageSound;
    CSharedPtr<class CSound> DashSound;
    CSharedPtr<class CSound> FallingSound;
    CSharedPtr<class CSound> SkillSound;
    CSharedPtr<class CSound> JumpSound;
    CSharedPtr<class CSound> LandSound;
    CSharedPtr<class CSound> HangSound;
    CSharedPtr<class CSound> ParrySound;
    //CSharedPtr<class CSound> RunSound;
    CSharedPtr<class CSound> WallJumpSound;
    CSharedPtr<class CSound> WallSlideSound;
    CSharedPtr<class CSound> DoubleJumpSound;
    CSharedPtr<class CSound> AttackSound[5];
   
    int PlayerHP;

 



public:
    virtual bool Init();
    virtual void Start();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual Cdummy* Clone();
    
    class CAnimationSequence2DInstance* GetAnimationInstance()  const;

    bool GetOnDash()
    {
        return IsOnDash;
    }

    //충돌체 반환
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
    //충돌체 반환


    PHASE GetPhase()
    {
        return Phase;
    }

    void SetPhase(PHASE phase)
    {
        Phase = phase;
    }

    //메달리는 방향 설정
    HANGINGDIR GetHangDir()
    {
        return HangDir;
    }

    void SetHangDir(HANGINGDIR dir)
    {
        HangDir = dir;
    }
    //메달리는 방향 설정

    //몹 한테 맞은 방향
    bool GetIsHitFromLeft()
    {
        return IsHitFromLeft;
    }

    void SetIsHitFromLeft(bool dir)
    {
        IsHitFromLeft = dir;
    }
    //몹 한테 맞은 방향

    //벽 터치 판정
    bool GetIsTouchedLeftWall()
    {
        return IsTouchedLeftWall;
    }

    void SetIsTouchedLeftWall(bool is)
    {
        IsTouchedLeftWall = is;
    }

    bool GetIsTouchedRightWall()
    {
        return IsTouchedRightWall;
    }

    void SetIsTouchedRightWall(bool is)
    {
        IsTouchedRightWall = is;
    }

    bool GetIsTouchedTopWall()
    {
        return IsTouchedTopWall;
    }

    void SetIsTouchedTopWall(bool is)
    {
        IsTouchedTopWall = is;
    }
    //벽 터치 판정

    //점프 중인가 아닌가
    bool GetIsJumpl()
    {
        return IsOnJump;
    }

    void SetIsJump(bool is)
    {
        IsOnJump = is;
    }
    //점프 중인가 아닌가

    //벽 점프
    bool GetIsOnWallJumpl()
    {
        return IsOnWallJump;
    }

    void SetIsOnWallJump(bool is)
    {
        IsOnWallJump = is;
    }
    //벽 점프



    //벽 닿은 횟수
    void AddWallTouchedCount()
    {
        WallTouchedCount++;
    }

    void SubWallTouchedCount()
    {
        WallTouchedCount--;
    }

    int GetWallTouchedCount()
    {
        return WallTouchedCount;
    }
    //벽 닿은 횟수
    
    //무적
    bool GetIsInvincible()
    {
        return IsInvincible;
    }

    void SetIsInvincible(bool is)
    {
        IsInvincible = is;
    }

    //피격가능
    bool GetIsGetAttackPossible()
    {
        return IsGetAttackPossible;
    }

    void SetIsGetAttackPossible(bool is)
    {
        IsGetAttackPossible = is;
    }

    //몬스터 피격 횟수
    void AddMonColCount()
    {
        MonColCount++;
    }

    void SubMonColCount()
    {
        MonColCount--;
    }

    int GetMonColCount()
    {
        return MonColCount;
    }

    Vector2 GetCurMapSize()
    {
        return CurMapSize;
    }

    void SetCurMapSize(Vector2 size);
  
    void SetCurMap(CurMap a)
    {
        Map = a;
    }

    //피격중인가
    bool GetIsBeingAttack()
    {
        return IsBeingAttack;
    }


    //이벤트
    void SetIsOnEvent(bool _b)
    {
        IsOnEvent = _b;
    }

    void CheckCamera();
    void ChangeAnimation(const std::string& AniName);

    void KeyCheck();
    void ChangeState(const std::string& Name);
private:
 



    void IDLEStart();
    void IDLEStay();
    
    
    
    void MOVEStartStart();
    void MOVEStartStay();


    void MOVEStopStart();
    void MOVEStopStay();
 

    void TURNStart();
    void TURNStay();
 

    void MOVEStart();
    void MOVEStay();
    void MOVEEnd();
    
    void JUMPStart();
    void JUMPStay();
    void JUMPEnd();

    void JUMPDownStart();
    void JUMPDownStay();

    void DOUBLEJUMPStart();
    void DOUBLEJUMPStay();
    void DOUBLEJUMPEnd();

    void HANGINGStart();
    void HANGINGStay();
    void HANGINGEnd();

    void JUMPFROMWALLStart();
    void JUMPFROMWALLStay();
    void JUMPFROMWALLEnd();

    void LANDStart();
    void LANDStay();

    void DASHStart();
    void DASHStay();
    void DASHEnd();

    void GETATTACKStart();
    void GETATTACKStay();
    void GETATTACKEnd();
 

    void RESTOREStart();
    void RESTOREStay();

    void ATTACKStart();
    void ATTACKStay();
    void ATTACKEnd();

    void ATTACKUPStart();
    void ATTACKUPStay();
    void ATTACKUPEnd();

    void ATTACKDOWNStart();
    void ATTACKDOWNStay();
    void ATTACKDOWNEnd();

    void AFTERDOWNATTACKStart();
    void AFTERDOWNATTACKStay();

    void SKILLStart();
    void SKILLStay();
    void SKILLEnd();

    


private:
    float MoveStartTime;
    float MoveStopTime;
    float TurnTime;
    float JumpTime;
    float LandTime;
    float AttackTime;
    float DashTime;
    float JumpHeight;
    float JumpCurrentHeight;
    float DoubleJumpTime;

    float AfterDownAttackTime;

    float RestoreTime;
    float GetAttackTime;

    float DoubleJumpHeight;
    float DoubleJumpCurrentHeight;

private:
    void OnCollisionBegin(const CollisionResult& result);
    void OnCollisionEnd(const CollisionResult& result);

    void IOnCollisionBegin(const CollisionResult& result);
    void IOnCollisionEnd(const CollisionResult& result);
};

