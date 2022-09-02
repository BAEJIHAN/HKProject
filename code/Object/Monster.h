#pragma once
#include "GameObject/GameObject.h"
#include "Component/ColliderBox2D.h"

class CMonster :
    public CGameObject
{
protected:
    CSharedPtr<CColliderBox2D>       m_Body;
    CSharedPtr<CColliderBox2D>       m_IBody;

    class Cdummy* pdummy;

    bool IsDead;
    bool IsAttacking;
    bool IsOnColPlayer;
public:
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

    bool GetIsOnColPlayer()
    {
        return IsOnColPlayer;
    }
};

