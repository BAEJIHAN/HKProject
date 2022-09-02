
#include "dummy.h"
#include "Scene/Scene.h"
#include "Input.h"
#include "Scene/SceneManager.h"
#include "Resource/Material/Material.h"
#include "DashAnimation.h"

#include "../Widget/HP.h"
#include "dummyAnimation.h"
#include "Engine.h"
#include "Device.h"
#include "WingAnimation.h"
#include "SkillEffectAnimation.h"
#include "GetAttackAnimation.h"
#include "../Scene/TestScene.h"
#include "Monster.h"
Cdummy::Cdummy()
{
	SetTypeID<Cdummy>();

	Dir = DIR::RIGHT;
	PreDir = DIR::RIGHT;
	DashDir = DASHDIR::LEFT;
	HangDir = HANGINGDIR::LEFT;

	IsDirChanged = false;
	IsOnAttack = false;
	IsOnDash = false;
	IsDashed = false;

	IsTouchedLeftWall = false;
	IsTouchedRightWall = false;
	IsTouchedTopWall = false;

	IsOnWallJump = false;
	IsDoubleJumped=false;
	IsOnJump =false;
	IsHitFromLeft = false;
	IsHanging = false;

	
	IsBeingAttack = false;
	IsInvincible = false;
	IsGetAttackPossible = true;
	IsOnEvent = false;

	IsCanAttack = true;
	DebugOn = false;

	GetAttackRate = 0;

	Phase = PHASE::GROUND;
	Map = CurMap::None;
	AfterDownAttackTime = 0;
	MoveStartTime = 0;
	MoveStopTime = 0;
	TurnTime = 0;
	JumpTime = 0;
	LandTime = 0;
	AttackTime = 0;
	DashTime = 0;
	DoubleJumpTime = 0;
	RestoreTime = 0;;
	GetAttackTime = 0;;

	JumpHeight = 450;
	JumpCurrentHeight = 0;

	DoubleJumpHeight = 450;
	DoubleJumpCurrentHeight=0;

	WallTouchedCount = 0;
	MonColCount = 0;

	AttackRate = 0;

	PRunTime = 0;
	HaningTime = 0;
	TextOpacity = 1.f;

	DamageSound = CResourceManager::GetInst()->FindSound("playerdamage");
	DashSound = CResourceManager::GetInst()->FindSound("playerdash");
	FallingSound = CResourceManager::GetInst()->FindSound("playerfalling");
	SkillSound = CResourceManager::GetInst()->FindSound("playerskill");
	JumpSound = CResourceManager::GetInst()->FindSound("playerjump");
	LandSound = CResourceManager::GetInst()->FindSound("playerland");
	HangSound = CResourceManager::GetInst()->FindSound("playermantisclaw");
	ParrySound = CResourceManager::GetInst()->FindSound("playerparry");
	//RunSound = CResourceManager::GetInst()->FindSound("playerrun");
	WallJumpSound = CResourceManager::GetInst()->FindSound("playerwalljump");
	WallSlideSound = CResourceManager::GetInst()->FindSound("playerslide");
	DoubleJumpSound = CResourceManager::GetInst()->FindSound("playerwings");
	AttackSound[0] = CResourceManager::GetInst()->FindSound("playersword1");
	AttackSound[1] = CResourceManager::GetInst()->FindSound("playersword2");
	AttackSound[2] = CResourceManager::GetInst()->FindSound("playersword3");
	AttackSound[3] = CResourceManager::GetInst()->FindSound("playersword4");
	AttackSound[4] = CResourceManager::GetInst()->FindSound("playersword5");

	PlayerHP = 5;
	
	
}

Cdummy::Cdummy(const Cdummy& obj) :
	CGameObject(obj)
{
	m_Sprite = (CSpriteComponent*)FindComponent("PlayerSprite");

	//m_ChildRoot = (CSceneComponent*)FindComponent("PlayerChildRoot");

	m_Body = (CColliderBox2D*)FindComponent("Body");
	m_Camera = (CCameraComponent*)FindComponent("Camera");

	m_Muzzle = CreateComponent<CSceneComponent>("MuzzleLeft");



}

Cdummy::~Cdummy()
{
}

bool Cdummy::Init()
{
	HPWidget = m_Scene->GetViewport()->CreateWidgetWindow<CHP>("HPWiget");
	m_Sprite = CreateComponent<CSpriteComponent>("PlayerSprite");

	

	m_Body = CreateComponent<CColliderBox2D>("Body");
	m_IBody = CreateComponent<CColliderBox2D>("IBody");
	m_FBody = CreateComponent<CColliderBox2D>("FBody");

	m_Camera = CreateComponent<CCameraComponent>("Camera");
	

	
	m_Muzzle = CreateComponent<CSceneComponent>("MuzzleLeft");
	
	SetRootComponent(m_Sprite);
	
	m_Camera->OnCenter();


	m_Sprite->AddChild(m_Body);
	m_Sprite->AddChild(m_IBody);
	m_Sprite->AddChild(m_FBody);
	m_Sprite->AddChild(m_Camera);
	m_Sprite->AddChild(m_Muzzle);
	


	

	

	m_Sprite->SetTransparency(true);
	//m_Sprite->SetOpacity(0.5f);

	m_Sprite->CreateAnimationInstance<CdummyAnimation>();

	
	
	m_Sprite->SetRelativeScale(160.f, 180.f, 1.f);
	m_Sprite->SetRelativePos(100.f, 50.f, 0.f);
	m_Sprite->SetPivot(0.19f, 0.36f, 0.f);
	
	WingLeft = CreateComponent<CSpriteComponent>("wingleft");
	m_Sprite->AddChild(WingLeft);
	WingLeft->CreateAnimationInstance<CWingAnimation>();

	WingLeft->SetRelativeScale(360, 260, 1);
	WingLeft->SetPivot(0.5f, 0.5f, 0.f);
	WingLeft->SetLayerName("BackEffect");
	WingLeft->GetAnimationInstance()->ChangeAnimation("WingNone");

	WingRight = CreateComponent<CSpriteComponent>("wingright");
	m_Sprite->AddChild(WingRight);
	WingRight->CreateAnimationInstance<CWingAnimation>();

	GetAttackEffect = CreateComponent<CSpriteComponent>("getattack");
	
	GetAttackEffect->SetRelativeScale(277, 188, 1.f);
	GetAttackEffect->SetRenderState("AlphaBlend");
	GetAttackEffect->SetPivot(0.5f, 0.5f, 0.f);
	GetAttackEffect->CreateAnimationInstance<CGetAttackAnimation>();
	GetAttackEffect->GetAnimationInstance()->ChangeAnimation("GetAttackBlank");
	
	DashleftEffect = CreateComponent<CSpriteComponent>("getattack");
	DashleftEffect->SetRelativeScale(277, 188, 1.f);
	DashleftEffect->SetRenderState("AlphaBlend");
	DashleftEffect->SetPivot(0.1f, 0.6f, 0.f);
	DashleftEffect->SetLayerName("BackEffect");
	DashleftEffect->CreateAnimationInstance<CDashAnimation>();
	DashleftEffect->GetAnimationInstance()->ChangeAnimation("DashBlank");
	m_Sprite->AddChild(DashleftEffect);

	DashrightEffect = CreateComponent<CSpriteComponent>("getattack");
	DashrightEffect->SetRelativeScale(277, 188, 1.f);
	DashrightEffect->SetRenderState("AlphaBlend");
	DashrightEffect->SetPivot(0.9f, 0.6f, 0.f);
	DashrightEffect->SetLayerName("BackEffect");
	DashrightEffect->CreateAnimationInstance<CDashAnimation>();
	DashrightEffect->GetAnimationInstance()->ChangeAnimation("DashBlank");
	m_Sprite->AddChild(DashrightEffect);

	


	m_Sprite->AddChild(GetAttackEffect);

	WingRight->SetRelativeScale(360, 260, 1);
	WingRight->SetPivot(0.5, 0.5, 0);
	WingRight->SetLayerName("BackEffect");
	WingRight->GetAnimationInstance()->ChangeAnimation("WingNone");

	SkillLeftEffect = CreateComponent<CSpriteComponent>("skillleft");
	SkillLeftEffect->CreateAnimationInstance<CSkillEffectAnimation>();

	SkillLeftEffect->SetRelativeScale(300.f, 280.f, 1.f);
	SkillLeftEffect->SetPivot(0.6f, 0.5f, 0.f);
	
	SkillLeftEffect->GetAnimationInstance()->ChangeAnimation("SkillNone");
	
	SkillRightEffect = CreateComponent<CSpriteComponent>("skillright");
	SkillRightEffect->CreateAnimationInstance<CSkillEffectAnimation>();

	SkillRightEffect->SetRelativeScale(300.f, 280.f, 1.f);
	SkillRightEffect->SetPivot(0.4f, 0.5f, 0.f);
	
	SkillRightEffect->GetAnimationInstance()->ChangeAnimation("SkillNone");
	m_Sprite->AddChild(SkillLeftEffect);
	m_Sprite->AddChild(SkillRightEffect);
	SkillLeftEffect->SetRenderState("AlphaBlend");
	SkillRightEffect->SetRenderState("AlphaBlend");
	WingLeft->SetRenderState("AlphaBlend");
	WingRight->SetRenderState("AlphaBlend");

	m_Body->SetCollisionProfile("Player");
	m_Body->SetExtent(27, 60);
	m_Body->AddCollisionCallback(Collision_State::Begin, this, &Cdummy::OnCollisionBegin);
	m_Body->AddCollisionCallback(Collision_State::End, this, &Cdummy::OnCollisionEnd);

	m_IBody->SetCollisionProfile("PlayerIdentify");
	m_IBody->SetExtent(27, 60);
	m_IBody->AddCollisionCallback(Collision_State::Begin, this, &Cdummy::IOnCollisionBegin);
	m_IBody->AddCollisionCallback(Collision_State::End, this, &Cdummy::IOnCollisionEnd);

	m_FBody->SetCollisionProfile("PlayerFloor");
	m_FBody->SetExtent(27, 60);
	m_FBody->AddCollisionCallback(Collision_State::Begin, this, &Cdummy::IOnCollisionBegin);
	m_FBody->AddCollisionCallback(Collision_State::End, this, &Cdummy::IOnCollisionEnd);
	

	



	PlayerFSM.CreateState("Idle", this, &Cdummy::IDLEStay, &Cdummy::IDLEStart);
	PlayerFSM.CreateState("move", this, &Cdummy::MOVEStay, &Cdummy::MOVEStart, &Cdummy::MOVEEnd);
	PlayerFSM.CreateState("movestart", this, &Cdummy::MOVEStartStay, &Cdummy::MOVEStartStart);
	PlayerFSM.CreateState("movestop", this, &Cdummy::MOVEStopStay, &Cdummy::MOVEStopStart);
	PlayerFSM.CreateState("turn", this, &Cdummy::TURNStay, &Cdummy::TURNStart);
	PlayerFSM.CreateState("jumpup", this, &Cdummy::JUMPStay, &Cdummy::JUMPStart, &Cdummy::JUMPEnd);
	PlayerFSM.CreateState("jumpdown", this, &Cdummy::JUMPDownStay, &Cdummy::JUMPDownStart);
	PlayerFSM.CreateState("land", this, &Cdummy::LANDStay, &Cdummy::LANDStart);
	PlayerFSM.CreateState("attack", this, &Cdummy::ATTACKStay, &Cdummy::ATTACKStart, &Cdummy::ATTACKEnd);
	PlayerFSM.CreateState("attackup", this, &Cdummy::ATTACKUPStay, &Cdummy::ATTACKUPStart, &Cdummy::ATTACKUPEnd);
	PlayerFSM.CreateState("attackdown", this, &Cdummy::ATTACKDOWNStay, &Cdummy::ATTACKDOWNStart, &Cdummy::ATTACKDOWNEnd);
	PlayerFSM.CreateState("skill", this, &Cdummy::SKILLStay, &Cdummy::SKILLStart, &Cdummy::SKILLEnd);
	PlayerFSM.CreateState("dash", this, &Cdummy::DASHStay, &Cdummy::DASHStart, &Cdummy::DASHEnd);
	PlayerFSM.CreateState("doublejump", this, &Cdummy::DOUBLEJUMPStay, &Cdummy::DOUBLEJUMPStart, &Cdummy::DOUBLEJUMPEnd);
	PlayerFSM.CreateState("getattack", this, &Cdummy::GETATTACKStay, &Cdummy::GETATTACKStart, &Cdummy::GETATTACKEnd);
	PlayerFSM.CreateState("restore", this, &Cdummy::RESTOREStay, &Cdummy::RESTOREStart);
	PlayerFSM.CreateState("afterdownattack", this, &Cdummy::AFTERDOWNATTACKStay, &Cdummy::AFTERDOWNATTACKStart);
	PlayerFSM.CreateState("hanging", this, &Cdummy::HANGINGStay, &Cdummy::HANGINGStart, &Cdummy::HANGINGEnd);
	PlayerFSM.CreateState("jumpfromwall", this, &Cdummy::JUMPFROMWALLStay, &Cdummy::JUMPFROMWALLStart, &Cdummy::JUMPFROMWALLEnd);
	
	PlayerFSM.ChangeState("Idle");
	return true;
}

void Cdummy::Start()
{
	CGameObject::Start();

	if (CurMap::Map4 == Map)
	{
		HPWidget->SetText(TEXT("°ÅÁþµÈ ±â»ç"));
		IsOnEvent = true;
	}
}

void Cdummy::Update(float DeltaTime)
{

	CGameObject::Update(DeltaTime);

	CheckCamera();

	if (IsOnEvent)
		return;

	if (CurMap::Map4 == Map)
	{
		
		if(TextOpacity>=0.f)
			TextOpacity -= DeltaTime/5;

		HPWidget->SetTextOpacity(TextOpacity);

		if (TextOpacity <= 0)
		{
			HPWidget->SetText(TEXT(""));
		}
	}

	KeyCheck();

	PlayerFSM.Update();

	if (false == IsGetAttackPossible)
	{
		GetAttackRate += DeltaTime;

		if (GetAttackRate <= 0.25)
		{
			m_Sprite->SetOpacity(0.5);
		}
		else if(GetAttackRate > 0.25 && GetAttackRate <= 0.5)
		{
			m_Sprite->SetOpacity(1);
		}
		else if (GetAttackRate > 0.5 && GetAttackRate <= 0.75)
		{
			m_Sprite->SetOpacity(0.5);
		}
		else if (GetAttackRate > 0.75 && GetAttackRate <= 1)
		{
			m_Sprite->SetOpacity(1);
		}
		else if (GetAttackRate >1 && GetAttackRate <= 1.25)
		{
			m_Sprite->SetOpacity(0.5);
		}
		
	}
	if (MonColCount > 0 && true == IsGetAttackPossible && false == IsInvincible)
	{
		if (PlayerHP > 0)
		{
			PlayerHP--;
			HPWidget->SetDie(PlayerHP);
		}
		
		
		
		ChangeState("getattack");
	}
	if (GetAttackRate >= 1.5)
	{
		GetAttackRate = 0;
		IsGetAttackPossible = true;
		m_Sprite->SetOpacity(1);

	}

	if (false == IsCanAttack)
	{
		AttackRate += DeltaTime;
	}
	
	if (AttackRate >= 0.4)
	{
		AttackRate = 0;
		IsCanAttack = true;
	}
	

	









	if (DebugOn)
	{
		HWND hwnd = CEngine::GetInst()->GetWindowHandle();
		HDC dc = GetDC(hwnd);

		std::string fps = std::to_string(CEngine::GetInst()->GetFPS());


		std::string a = "WallTouchedCount : ";
		std::string b = std::to_string(WallTouchedCount);
		std::string c = a + b;

		std::string d = std::to_string(GetColCenterPos().x);
		std::string e = std::to_string(GetColCenterPos().y);
		std::string f = "XPos : " + d + " YPos : " + e;
		std::string g = std::to_string(MonColCount);
		std::string h = "MonCol : " + g;

		TCHAR szUniCode1[256] = { 0, };
		TCHAR szUniCode2[256] = { 0, };
		TCHAR szUniCode3[256] = { 0, };
		TCHAR szUniCode4[256] = { 0, };

		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, fps.c_str(), (int)strlen(fps.c_str()), szUniCode1, 256);
		TextOut(dc, 0, 0, szUniCode1, lstrlen(szUniCode1));
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, c.c_str(), (int)strlen(c.c_str()), szUniCode2, 256);
		TextOut(dc, 0, 20, szUniCode2, lstrlen(szUniCode2));
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, f.c_str(), (int)strlen(f.c_str()), szUniCode3, 256);
		TextOut(dc, 0, 40, szUniCode3, lstrlen(szUniCode3));
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, h.c_str(), (int)strlen(h.c_str()), szUniCode4, 256);
		TextOut(dc, 0, 60, szUniCode4, lstrlen(szUniCode4));
		ReleaseDC(hwnd, dc);
	}

	
}

void Cdummy::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

Cdummy* Cdummy::Clone()
{
	return new Cdummy(*this);
}

CAnimationSequence2DInstance* Cdummy::GetAnimationInstance() const
{
	return m_Sprite->GetAnimationInstance();
}

void Cdummy::SetCurMapSize(Vector2 size)
{
	CurMapSize = size;
	CEngine::GetInst()->SetCurMapSize((int)size.x, (int)size.y);
}

void Cdummy::CheckCamera()
{
	Resolution RS = CDevice::GetInst()->GetResolution();
	Vector2 MapSize = GetCurMapSize();

	/*
	¿ÞÂÊ¸¸ ´ê¾ÒÀ» ‹š
	¿ÞÂÊ°ú ¾Æ·¡°¡ ´ê¾ÒÀ» ¶§
	
	¾Æ·¡¸¸ ´ê¾ÒÀ» ¶§

	¿À¸¥ÂÊ¸¸ ´ê¾ÒÀ» ‹š
	¿À¸¥ÂÊ°ú ¾Æ·¡°¡ ´ê¾ÒÀ» ‹š
	
	¿ÞÂÊ°ú À§°¡ ´ê¾ÒÀ» ¶§

	À§¸¸ ´ê¾ÒÀ» ¶§
	
	¿À¸¥ÂÊ°ú À§°¡ ´ê¾ÒÀ» ¶§
	*/
	if (RS.Width / 2 >= GetColCenterPos().x)//¿ÞÂÊ¸¸ ´ê¾ÒÀ» ‹š
	{
		CEngine::GetInst()->SetIsTouchedLeft(true);
		
	}
	else
	{
		CEngine::GetInst()->SetIsTouchedLeft(false);
	}

	if (MapSize.x - (float)(RS.Width / 2) <= GetColCenterPos().x)//¿À¸¥ÂÊ¸¸ ´ê¾ÒÀ» ‹š
	{
		
		CEngine::GetInst()->SetIsTouchedRight(true);
	}
	else
	{
		CEngine::GetInst()->SetIsTouchedRight(false);
	}


	if (RS.Height / 2 >= GetColCenterPos().y)//¹Ù´Ú¸¸ ´ê¾ÒÀ» ¶§
	{
		CEngine::GetInst()->SetIsTouchedBottom(true);
	}
	else
	{
		CEngine::GetInst()->SetIsTouchedBottom(false);
	}

	if (MapSize.y - RS.Height / 2 <= GetColCenterPos().y)//À§°¡ ´ê¾ÒÀ» ¶§
	{
		CEngine::GetInst()->SetIsTouchedTop(true);
	}
	else
	{
		CEngine::GetInst()->SetIsTouchedTop(false);
	}


	
}

void Cdummy::ChangeState(const std::string &Name)
{
	PlayerFSM.ChangeState(Name);
}



void Cdummy::ChangeAnimation(const std::string& AniName)
{
	m_Sprite->GetAnimationInstance()->ChangeAnimation(AniName);
}

void Cdummy::KeyCheck()
{	
	if (CInput::GetInst()->IsDown("U"))
	{
		if (true == DebugOn)
		{
			DebugOn=false;

		}
		else if (false == DebugOn)
		{
			DebugOn = true;
		}
	}

	if (CInput::GetInst()->IsDown("I"))
	{
		if (true == CEngine::IsRenderCol)
		{
			CEngine::IsRenderCol = false;

		}
		else if (false == CEngine::IsRenderCol)
		{
			CEngine::IsRenderCol=true;
		}
	}


	if (CInput::GetInst()->IsDown("T"))
	{
		if (true == IsInvincible)
		{
			SetIsInvincible(false);
		}
		else if (false == IsInvincible)
		{
			SetIsInvincible(true);
		}
	}

	if (IsBeingAttack)
	{
		return;
	}


	if (CInput::GetInst()->IsDown("C")&& !IsDashed)
	{
		PlayerFSM.ChangeState("dash");		
	}




	if (CInput::GetInst()->IsPush("Right"))
	{
		Dir = DIR::RIGHT;
	}
	if (CInput::GetInst()->IsPush("Left"))
	{
		Dir = DIR::LEFT;
	}

	if (PreDir != Dir)
		IsDirChanged = true;
	else
		IsDirChanged = false;

	PreDir = Dir;

	if (CInput::GetInst()->IsPush("Z") && CInput::GetInst()->IsPush("X"))
	{
		return;
	}



	if (CInput::GetInst()->IsDown("Z")&& !IsOnDash)
	{
		
		if (IsHanging)
		{
			PlayerFSM.ChangeState("jumpfromwall");
		}
		else if (PHASE::FALLING == Phase && !IsDoubleJumped)
		{
			PlayerFSM.ChangeState("doublejump");
		}
		else if (PHASE::GROUND == Phase)
		{
			PlayerFSM.ChangeState("jumpup");
		}		
		
		
	}

	if (CInput::GetInst()->IsDown("X") && false==IsOnAttack)
	{
		if (!IsOnDash && true==IsCanAttack)
		{
			IsCanAttack = false;

			int t = rand() % 5;
			AttackSound[t]->Play();

			if (CInput::GetInst()->IsPush("Up"))
			{
				PlayerFSM.ChangeState("attackup");
			}				
			else if (CInput::GetInst()->IsPush("Down"))
			{
				if(PHASE::GROUND!=Phase)
					PlayerFSM.ChangeState("attackdown");
			}
			else
			{
				PlayerFSM.ChangeState("attack");
			}			
				
		}
			
	}

	if (CInput::GetInst()->IsDown("A") &&  Phase== PHASE::GROUND)
	{
		if (!IsOnDash)
		{
			PlayerFSM.ChangeState("restore");
		}

	}

	if (CInput::GetInst()->IsDown("S"))
	{
		if (!IsOnDash && true == IsCanAttack)
		{
			IsCanAttack = false;
			PlayerFSM.ChangeState("skill");
		}

	}
	
}

void Cdummy::OnCollisionBegin(const CollisionResult& result)
{
	if ("Monster" == result.Dest->GetCollisionProfile()->Name)
	{
		CMonster* Mon = (CMonster*)result.Dest->GetGameObject();
		if (true == Mon->GetIsDead())
		{
			return;
		}

		AddMonColCount();
		if (true == GetIsGetAttackPossible() && false == GetIsInvincible() && GetMonColCount() > 0)
		{
			if (GetColRightXPos() - 10 < Mon->GetColLeftXPos())
			{

				SetIsHitFromLeft(false);
			}
			else if (Mon->GetColRightXPos() < GetColLeftXPos() + 10)
			{
				SetIsHitFromLeft(true);
			}
		}

		
	}
}

void Cdummy::OnCollisionEnd(const CollisionResult& result)
{


	std::string t = result.Dest->GetCollisionProfile()->Name;
	if ("Monster" == result.Dest->GetCollisionProfile()->Name)
	{
		CMonster* Mon = (CMonster*)result.Dest->GetGameObject();
		if (true == Mon->GetIsDead())
		{
			return;
		}

		SubMonColCount();
		


	}
	
}

void Cdummy::IOnCollisionBegin(const CollisionResult& result)
{
}

void Cdummy::IOnCollisionEnd(const CollisionResult& result)
{
}


