#include "FMonster.h"
#include "Scene/Scene.h"
#include "Resource/Material/Material.h"
#include "FMonsterAnimation.h"
#include "MHitEffectAnimation.h"

#include "Engine.h"
#include "dummy.h"
#include "AttackLeft.h"
#include "AttackRight.h"
#include "AttackUp.h"
#include "AttackDown.h"
#include "PlayerMissileLeft.h"
#include "PlayerMissileRight.h"
#include "Input.h"
#include "Scene/SceneManager.h"

CFMonster::CFMonster()
{
	SetTypeID<CFMonster>();
	Dir = DIR::LEFT;
	PlayerDir = DIR::LEFT;
	PrePlayerDir = DIR::LEFT;
	ActTime = 0.f;
	GetAttackTime = 0.f;
	IsAttacking = false;
	MoveOnOff = false;
	IsDead = false;
	IsGetAttack = false;
	ChaseSoundRate = 0.f;
	HitRate = 0.f;
	hitflag = 0;

	FindRate = 10.f;
	fflag = 0;

	StartleSound = CResourceManager::GetInst()->FindSound("buzzerstartle");
	ChaseSound = CResourceManager::GetInst()->FindSound("buzzerfly");
	DamageSound = CResourceManager::GetInst()->FindSound("enemydamage");
	
}



CFMonster::~CFMonster()
{
}

void CFMonster::Start()
{
	CGameObject::Start();
	pdummy = (Cdummy*)CSceneManager::GetInst()->GetScene()->GetPlayerObject();
}

bool CFMonster::Init()
{
	m_Sprite = CreateComponent<CSpriteComponent>("monster");
	m_Body = CreateComponent<CColliderBox2D>("Body");
	m_IBody = CreateComponent<CColliderBox2D>("IBody");

	SetRootComponent(m_Sprite);

	

	m_Sprite->AddChild(m_Body);
	m_Sprite->AddChild(m_IBody);



	m_Body->SetCollisionProfile("Monster");
	m_IBody->SetCollisionProfile("MonsterIdentify");

	m_Sprite->SetTransparency(true);
	//m_Sprite->SetOpacity(0.5f);

	m_Sprite->CreateAnimationInstance<CFMonsterAnimation>();

	m_Sprite->SetRelativeScale(140.f, 140.f, 1.f);
	m_Sprite->SetRelativePos(500.f, 300.f, 0.f);
	m_Sprite->SetPivot(0.5f, 0.5f, 0.f);

	HitEffect = CreateComponent<CSpriteComponent>("hiteffect");
	m_Sprite->AddChild(HitEffect);
	HitEffect->CreateAnimationInstance<CMHitEffectAnimation>();

	HitEffect->SetRelativeScale(240, 160, 1);
	HitEffect->SetPivot(0.5f, 0.7f, 0.f);
	HitEffect->SetRenderState("AlphaBlend");
	HitEffect->GetAnimationInstance()->ChangeAnimation("hitblank");


	m_Body->SetExtent(50, 50);



	m_Body->AddCollisionCallback(Collision_State::Begin, this, &CFMonster::OnCollisionBegin);
	m_Body->AddCollisionCallback(Collision_State::End, this, &CFMonster::OnCollisionEnd);

	m_HP = 2;

	m_IBody->SetExtent(400, 400);
	m_IBody->AddCollisionCallback(Collision_State::Begin, this, &CFMonster::IOnCollisionBegin);
	m_IBody->AddCollisionCallback(Collision_State::End, this, &CFMonster::IOnCollisionEnd);

	FFSM.CreateState("Idle", this, &CFMonster::IDLEStay, &CFMonster::IDLEStart, &CFMonster::IDLEEnd);
	FFSM.CreateState("preattack", this, &CFMonster::PREATTACKStay, &CFMonster::PREATTACKStart, &CFMonster::PREATTACKEnd);
	FFSM.CreateState("attack", this, &CFMonster::ATTACKStay, &CFMonster::ATTACKStart, &CFMonster::ATTACKEnd);
	FFSM.CreateState("death", this, &CFMonster::DEATHStay, &CFMonster::DEATHStart, &CFMonster::DEATHEnd);

	FFSM.ChangeState("Idle");
	
	
	return true;
}

void CFMonster::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
	if (0 == fflag)
	{
		fflag++;
		return;
	}


	
	
	

	
	
	FFSM.Update();

	if (IsDead)
		return;
	if (IsAttacking)
	{
		if (FindRate >= 0.3)
		{
			FindPlayer(pdummy->GetColCenterPos());
			FindRate = 0;
		}
		FindRate += DeltaTime;
	}
	FMonMove();
	
	float pxpos = pdummy->GetColCenterPos().x;
	float xpos = this->GetColCenterPos().x;





	if (pdummy->GetColCenterPos().x < this->GetColCenterPos().x)
	{
		PlayerDir = DIR::LEFT;

	}
	else
	{
		PlayerDir = DIR::RIGHT;
	}


	if (PlayerDir != PrePlayerDir)
	{
		ChangeDir();

	}

	if (PlayerDir == DIR::LEFT)
	{
		PrePlayerDir = DIR::LEFT;
	}
	else if (PlayerDir == DIR::RIGHT)
	{
		PrePlayerDir = DIR::RIGHT;
	}

	if (true == IsGetAttack)
	{
		KnockBack();
	}

	HitUpdate(DeltaTime);
}

void CFMonster::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CFMonster* CFMonster::Clone()
{
	return new CFMonster(*this);
}

CAnimationSequence2DInstance* CFMonster::GetAnimationInstance() const
{
	return m_Sprite->GetAnimationInstance();
}

void CFMonster::ChangeAnimation(const std::string& AniName)
{
	m_Sprite->GetAnimationInstance()->ChangeAnimation(AniName);
}

void CFMonster::ChangeState(const std::string& Name)
{
	FFSM.ChangeState(Name);
}

void CFMonster::ChangeDir()
{
	
		
	if (DIR::LEFT == Dir)
	{
		Dir = DIR::RIGHT;

	}
	else if (DIR::RIGHT == Dir)
	{
		Dir = DIR::LEFT;

	}
	if (true == IsAttacking)
	{
		ChangeState("attack");
	}
	
	
}

void CFMonster::HitUpdate(float DeltaTime)
{
	if (false == IsGetAttack)
	{
		HitRate = 0;
		return;
	}

	HitRate += DeltaTime;

	if (0 == hitflag)
	{
		hitflag++;
		int i = rand() % 6;
		if (0 == i)
		{
			HitEffect->GetAnimationInstance()->ChangeAnimation("hit1");
		}
		else if (1 == i)
		{
			HitEffect->GetAnimationInstance()->ChangeAnimation("hit2");
		}
		else if (2 == i)
		{
			HitEffect->GetAnimationInstance()->ChangeAnimation("hit3");
		}
		else if (3 == i)
		{
			HitEffect->GetAnimationInstance()->ChangeAnimation("hit4");
		}
		else if (4 == i)
		{
			HitEffect->GetAnimationInstance()->ChangeAnimation("hit5");
		}
		else if (5 == i)
		{
			HitEffect->GetAnimationInstance()->ChangeAnimation("hit6");
		}

	}

	if (HitRate > 0.09)
	{
		IsGetAttack = false;
		HitRate = 2;
		hitflag = 0;
		HitEffect->GetAnimationInstance()->ChangeAnimation("hitblank");
	}
}

void CFMonster::KnockBack()
{
	float DeltaTime = CEngine::GetInst()->GetDeltaTime();
	GetAttackTime += DeltaTime;
	if (GetAttackTime <= 0.1)
	{
		if (GetColCenterPos().x < pdummy->GetColCenterPos().x)//오른쪽에서 때릴 때
		{
			m_Sprite->AddRelativePos(Vector3(-1000, 0.f, 0.f) * DeltaTime);
		}
		else if (GetColCenterPos().x >= pdummy->GetColCenterPos().x)//왼쪽에서 때릴 때
		{
			m_Sprite->AddRelativePos(Vector3(+1000, 0.f, 0.f) * DeltaTime);
		}	

	}
	if (GetAttackTime >= 0.1)
	{
		IsGetAttack = false;
		GetAttackTime = 0;
	}
}







void CFMonster::FindPlayer(Vector2 v)
{
	Vector2 a_CacVec = v - GetColCenterPos();
	if (a_CacVec.Length() < 4.0f)
	{
		return;
	}

	MoveOnOff = true;

	DirVec = v - GetColCenterPos();
	DirVec.Normalize();       
	TargetPos = v;      
}

void CFMonster::FMonMove()
{
	float DeltaTime = CEngine::GetInst()->GetDeltaTime();

	if (MoveOnOff == true)
	{
		static double a_CacStep;
		static Vector2 a_CacEndVec;

		// 가야할 방향에 시간 값을 곱해서 조금씩 이동하게 한다
		a_CacStep = DeltaTime * 250; //이번에 한걸음 길이 (보폭)

		a_CacEndVec = TargetPos - GetColCenterPos();
		if (a_CacEndVec.Length() <= (float)a_CacStep)  //목표점까지의 거리보다 보폭이 크거나 같으면 도착으로 본다.
		{
			MoveOnOff = false;
			
		}
		else
		{
			Vector2 temp = DirVec * (float)a_CacStep;
			m_Sprite->AddRelativePos(temp.x,temp.y, 0);
		}
	}
	
}



void CFMonster::OnMouseBegin(const CollisionResult& result)
{
	CEngine::GetInst()->SetMouseState(Mouse_State::State1);
}

void CFMonster::OnMouseEnd(const CollisionResult& result)
{
	CEngine::GetInst()->SetMouseState(Mouse_State::Normal);
}

void CFMonster::OnCollisionBegin(const CollisionResult& result)
{
	CAttackDown tAttackDown;
	CAttackRight tAttackRight;
	CAttackLeft tAttackLeft;
	CAttackUp tAttackUp;
	CPlayerMissileRight tMisiileRight;
	CPlayerMissileLeft tMisiileLeft;

	if ("Player" == result.Dest->GetCollisionProfile()->Name)
	{
		IsOnColPlayer = true;
	}

	if (result.Dest->GetGameObject()->GetTypeID() == tAttackDown.GetTypeID() ||
		result.Dest->GetGameObject()->GetTypeID() == tAttackUp.GetTypeID() ||
		result.Dest->GetGameObject()->GetTypeID() == tAttackRight.GetTypeID() ||
		result.Dest->GetGameObject()->GetTypeID() == tAttackLeft.GetTypeID() ||
		result.Dest->GetGameObject()->GetTypeID() == tMisiileRight.GetTypeID() ||
		result.Dest->GetGameObject()->GetTypeID() == tMisiileLeft.GetTypeID())
	{
		if (true == IsDead)
			return;

		

		if (result.Dest->GetGameObject()->GetTypeID() == tAttackDown.GetTypeID())
		{

			pdummy->ChangeState("afterdownattack");
		}

		IsGetAttack = true;
		DamageSound->Play();
		m_HP--;
		if (0 == m_HP)
		{
			ChangeState("death");
		}


	}

}

void CFMonster::OnCollisionEnd(const CollisionResult& result)
{
	if ("Player" == result.Dest->GetCollisionProfile()->Name)
	{
		IsOnColPlayer = false;
	}
}

void CFMonster::IOnCollisionBegin(const CollisionResult& result)
{

	if (true == IsDead)
		return;
	if ("PlayerIdentify" == result.Dest->GetCollisionProfile()->Name)
	{
		if (false == IsAttacking)
		{
			ChangeState("preattack");
		}
		
	}
}

void CFMonster::IOnCollisionEnd(const CollisionResult& result)
{
}


