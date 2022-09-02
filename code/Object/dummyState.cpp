#include "dummy.h"
#include "dummyAnimation.h"
#include "Input.h"
#include "Engine.h"
#include "../Object/AttackLeft.h"
#include "../Object/AttackRight.h"
#include "../Object/AttackUp.h"
#include "../Object/AttackDown.h"
#include "../Object/PlayerMissileLeft.h"
#include "../Object/PlayerMissileRight.h"
#include "../Object/DashLeft.h"
#include "../Object/DashRight.h"
#include "Resource/Sound/Sound.h"

void Cdummy::IDLEStart()
{
	m_Sprite->SetPivot(0.19f, 0.36f, 0.f);
	if (DIR::LEFT==Dir)
	{
		ChangeAnimation("PlayerIdleLeft");
	}
	if (DIR::RIGHT == Dir)
	{
		ChangeAnimation("PlayerIdleRight");
	}
	
}

void Cdummy::IDLEStay()
{
	
	if (
		true == CInput::GetInst()->IsPush("Right")||
		true == CInput::GetInst()->IsPush("Left")
		)
	{
		PlayerFSM.ChangeState("movestart");
	}
	
}

void Cdummy::MOVEStart()
{
	//RunSound->Play();
	if (DIR::LEFT == Dir)
	{
		m_Sprite->SetPivot(0.19f, 0.36f, 0.f);
		ChangeAnimation("PlayerWalkLeft");
	}
	if (DIR::RIGHT == Dir)
	{
		m_Sprite->SetPivot(0.24f, 0.36f, 0.f);
		ChangeAnimation("PlayerWalkRight");
	}
	
}

void Cdummy::MOVEStay()
{
	float DeltaTime = CEngine::GetInst()->GetDeltaTime();
	
	
	if (DIR::RIGHT == Dir)
	{
		if(!IsTouchedRightWall)
			m_Sprite->AddRelativePos(Vector3(+300.f, 0.f, 0.f)* DeltaTime);
	}
	if (DIR::LEFT == Dir)
	{
		if (!IsTouchedLeftWall)
			m_Sprite->AddRelativePos(Vector3(-300.f, 0.f, 0.f)* DeltaTime);
	}

	if (
		false == CInput::GetInst()->IsPush("Right") &&
		false == CInput::GetInst()->IsPush("Left")
		)
	{
		PlayerFSM.ChangeState("movestop");
	}


	if (IsDirChanged)
	{
		if (CInput::GetInst()->IsPush("Left"))
		{

			
			PlayerFSM.ChangeState("turn");
		}

		if (DIR::RIGHT == Dir && true == CInput::GetInst()->IsPush("Right"))
		{
		
			PlayerFSM.ChangeState("turn");
		}
	}
	
	
}

void Cdummy::MOVEEnd()
{
	
	PRunTime = 0;
	//RunSound->Stop();
}

void Cdummy::MOVEStartStart()
{
	
	MoveStartTime = 0;
	if (DIR::LEFT == Dir)
	{
		ChangeAnimation("PlayerWalkStartLeft");
	}
	if (DIR::RIGHT == Dir)
	{
		m_Sprite->SetPivot(0.24f, 0.36f, 0.f);
		ChangeAnimation("PlayerWalkStartRight");
	}
}

void Cdummy::MOVEStartStay()
{
	float DeltaTime = CEngine::GetInst()->GetDeltaTime();
	MoveStartTime += DeltaTime;
	PRunTime += DeltaTime;

	if (DIR::RIGHT == Dir)
	{
		if (!IsTouchedRightWall)
			m_Sprite->AddRelativePos(Vector3(+300.f, 0.f, 0.f) * DeltaTime);
	}
	if (DIR::LEFT == Dir)
	{
		if (!IsTouchedLeftWall)
			m_Sprite->AddRelativePos(Vector3(-300.f, 0.f, 0.f) * DeltaTime);
	}

	if (
		false == CInput::GetInst()->IsPush("Right") &&
		false == CInput::GetInst()->IsPush("Left")
		)
	{
		PlayerFSM.ChangeState("Idle");
	}

	if (0.3f <= MoveStartTime)
	{
		
		MoveStartTime = 0;
		
		PlayerFSM.ChangeState("move");
	}
		
}

void Cdummy::MOVEStopStart()
{			  
	MoveStopTime = 0;
	if (DIR::LEFT == Dir)
	{
		ChangeAnimation("PlayerStopLeft");
	}
	if (DIR::RIGHT == Dir)
	{
		ChangeAnimation("PlayerStopRight");
	}
}			  
			  
void Cdummy::MOVEStopStay()
{			 
	float DeltaTime = CEngine::GetInst()->GetDeltaTime();
	MoveStopTime += DeltaTime;
	if (0.2f <= MoveStopTime)
	{
		PlayerFSM.ChangeState("Idle");
	}

	if (
		true == CInput::GetInst()->IsPush("Right") ||
		true == CInput::GetInst()->IsPush("Left")
		)
	{
		MoveStopTime = 0;
		PlayerFSM.ChangeState("movestart");
	}
		
}			 


void Cdummy::TURNStart()
{
	
	TurnTime = 0;
	if (DIR::LEFT == Dir)
	{
		ChangeAnimation("PlayerTurnLeft");
	}
	if (DIR::RIGHT == Dir)
	{
		ChangeAnimation("PlayerTurnRight");
	}



}
void Cdummy::TURNStay()
{
	float DeltaTime = CEngine::GetInst()->GetDeltaTime();
	TurnTime += DeltaTime;

	if (
		false == CInput::GetInst()->IsPush("Right") &&
		false == CInput::GetInst()->IsPush("Left")
		)
	{
		PlayerFSM.ChangeState("Idle");
	}

	if (DIR::RIGHT == Dir)
	{
		if (!IsTouchedRightWall)
			m_Sprite->AddRelativePos(Vector3(+300.f, 0.f, 0.f) * DeltaTime);
	}
	if (DIR::LEFT == Dir)
	{
		if (!IsTouchedLeftWall)
			m_Sprite->AddRelativePos(Vector3(-300.f, 0.f, 0.f) * DeltaTime);
	}


	if (0.2f <= TurnTime)
	{
		
		TurnTime = 0;
		PlayerFSM.ChangeState("move");
	}
}

void Cdummy::JUMPStart()
{
	JumpSound->Play();
	IsOnJump = true;

	if (PHASE::GROUND == Phase)
	{
		JumpCurrentHeight = 0;
		
		Phase = PHASE::RISING;
		if (DIR::LEFT == Dir)
		{
			ChangeAnimation("PlayerJumpUpLeft");
		}
		if (DIR::RIGHT == Dir)
		{
			ChangeAnimation("PlayerJumpUpRight");
		}

	}
	
	

	
}

void Cdummy::JUMPStay()
{
	float DeltaTime = CEngine::GetInst()->GetDeltaTime();
	

	if (JumpCurrentHeight < JumpHeight && true == CInput::GetInst()->IsPush("Z"))
	{
		if (!IsTouchedTopWall)
			m_Sprite->AddRelativePos(Vector3(0.f, 750.f, 0.f) * DeltaTime);
		JumpCurrentHeight += 750.f * DeltaTime;
	}
	else
	{
		PlayerFSM.ChangeState("jumpdown");
	}
	
	

	if (true == CInput::GetInst()->IsPush("Right"))
	{
		if (!IsTouchedRightWall)
			m_Sprite->AddRelativePos(Vector3(+300.f, 0.f, 0.f) * DeltaTime);
	}
	if (true == CInput::GetInst()->IsPush("Left"))
	{
		if (!IsTouchedLeftWall)
			m_Sprite->AddRelativePos(Vector3(-300.f, 0.f, 0.f) * DeltaTime);
	}
	

	

}

void Cdummy::JUMPEnd()
{
	IsOnJump = false;
}

void Cdummy::JUMPDownStart()
{
	
	Phase = PHASE::FALLING;
	if (DIR::LEFT == Dir)
	{
		m_Sprite->SetPivot(0.19f, 0.36f, 0.f);
		ChangeAnimation("PlayerJumpDownLeft");
	}
	if (DIR::RIGHT == Dir)
	{
		m_Sprite->SetPivot(0.33f, 0.36f, 0.f);
		ChangeAnimation("PlayerJumpDownRight");
	}

}

void Cdummy::JUMPDownStay()
{
	
	float DeltaTime = CEngine::GetInst()->GetDeltaTime();
	

	
	m_Sprite->AddRelativePos(Vector3(0.f, -750.f, 0.f) * DeltaTime);
	
	

	if (true == CInput::GetInst()->IsPush("Right"))
	{
		if (!IsTouchedRightWall)
			m_Sprite->AddRelativePos(Vector3(+300.f, 0.f, 0.f) * DeltaTime);
	}
	if (true == CInput::GetInst()->IsPush("Left"))
	{
		if (!IsTouchedLeftWall)
			m_Sprite->AddRelativePos(Vector3(-300.f, 0.f, 0.f) * DeltaTime);
	}

}

void Cdummy::DOUBLEJUMPStart()
{
	DoubleJumpSound->Play();
	IsDoubleJumped = true;
	DoubleJumpCurrentHeight = 0;

	Phase = PHASE::RISING;
	if (DIR::LEFT == Dir)
	{
		WingLeft->GetAnimationInstance()->ChangeAnimation("WingLeft");
		m_Sprite->SetPivot(0.19f, 0.36f, 0.f);
		ChangeAnimation("PlayerDoubleJumpLeft");
	}
	if (DIR::RIGHT == Dir)
	{
		WingRight->GetAnimationInstance()->ChangeAnimation("WingRight");
		m_Sprite->SetPivot(0.8f, 0.36f, 0.f);
		ChangeAnimation("PlayerDoubleJumpRight");
	}
}

void Cdummy::DOUBLEJUMPStay()
{
	float DeltaTime = CEngine::GetInst()->GetDeltaTime();


	if (DoubleJumpCurrentHeight < DoubleJumpHeight)
	{
		if (!IsTouchedTopWall)
			m_Sprite->AddRelativePos(Vector3(0.f, 750.f, 0.f) * DeltaTime);
		DoubleJumpCurrentHeight += 750.f * DeltaTime;
	}
	else
	{
		PlayerFSM.ChangeState("jumpdown");
	}



	if (true == CInput::GetInst()->IsPush("Right"))
	{
		if (!IsTouchedRightWall)
			m_Sprite->AddRelativePos(Vector3(+300.f, 0.f, 0.f) * DeltaTime);
	}
	if (true == CInput::GetInst()->IsPush("Left"))
	{
		if (!IsTouchedLeftWall)
			m_Sprite->AddRelativePos(Vector3(-300.f, 0.f, 0.f) * DeltaTime);
	}
}

void Cdummy::DOUBLEJUMPEnd()
{
	WingLeft->GetAnimationInstance()->ChangeAnimation("WingNone");
	WingRight->GetAnimationInstance()->ChangeAnimation("WingNone");
}

void Cdummy::HANGINGStart()
{
	HangSound->Play();
	if (false == WallSlideSound->IsPlay())
	{
		WallSlideSound->Play();
	}
	HaningTime = 0;
	
	IsHanging = true;
	if (HANGINGDIR::LEFT == HangDir)
	{
		m_Sprite->SetPivot(0.24f, 0.36f, 0.f);
		ChangeAnimation("PlayerHangingLeft");
	}
	if (HANGINGDIR::RIGHT == HangDir)
	{	
		
		m_Sprite->SetPivot(0.24f, 0.36f, 0.f);
		ChangeAnimation("PlayerHangingRight");
	}
}

void Cdummy::HANGINGStay()
{
	float DeltaTime = CEngine::GetInst()->GetDeltaTime();
	HaningTime += DeltaTime;

	m_Sprite->AddRelativePos(Vector3(0.f, -300.f, 0.f) * DeltaTime);
	
	if (HaningTime >= 2.0)
	{
		HangSound->Play();
	}


}

void Cdummy::HANGINGEnd()
{
	WallSlideSound->Stop();
	HaningTime = 0;
	IsHanging = false;
}

void Cdummy::JUMPFROMWALLStart()
{
	WallJumpSound->Play();
	JumpCurrentHeight = 0;
	IsDoubleJumped = false;
	IsOnWallJump = true;
	Phase = PHASE::RISING;
	if (HANGINGDIR::LEFT == HangDir)
	{
		
		ChangeAnimation("PlayerWallJumpLeft");
	}
	if (HANGINGDIR::RIGHT == HangDir)
	{
		
		ChangeAnimation("PlayerWallJumpRight");
	}
}

void Cdummy::JUMPFROMWALLStay()
{
	float DeltaTime = CEngine::GetInst()->GetDeltaTime();

	if (HANGINGDIR::LEFT == HangDir)
	{
		if (!IsTouchedRightWall)
			m_Sprite->AddRelativePos(Vector3(+300.f, 0.f, 0.f) * DeltaTime);
		
	}

	if (HANGINGDIR::RIGHT == HangDir)
	{
		if (!IsTouchedLeftWall)
			m_Sprite->AddRelativePos(Vector3(-300.f, 0.f, 0.f) * DeltaTime);
		
	}
	

	if (JumpCurrentHeight < JumpHeight)
	{
		if (!IsTouchedTopWall)
			m_Sprite->AddRelativePos(Vector3(0.f, 750.f, 0.f) * DeltaTime);
		JumpCurrentHeight += 750.f * DeltaTime;
	}
	else
	{
		PlayerFSM.ChangeState("jumpdown");
	}




}

void Cdummy::JUMPFROMWALLEnd()
{
	IsOnWallJump = false;
}

void Cdummy::LANDStart()
{
	LandSound->Play();
	
	Phase = PHASE::GROUND;
	LandTime = 0;
	IsDashed = false;
	IsDoubleJumped = false;
	if (DIR::LEFT == Dir)
	{
		m_Sprite->SetPivot(0.19f, 0.36f, 0.f);
		ChangeAnimation("PlayerLandLeft");
	}
	if (DIR::RIGHT == Dir)
	{
		m_Sprite->SetPivot(0.24f, 0.36f, 0.f);
		ChangeAnimation("PlayerLandRight");
	}
	
}

void Cdummy::LANDStay()
{
	
	float DeltaTime = CEngine::GetInst()->GetDeltaTime();
	PRunTime += DeltaTime;
	LandTime += DeltaTime;
	if (LandTime > 0.2)
	{
		
		PlayerFSM.ChangeState("Idle");
	}

	if (true == CInput::GetInst()->IsPush("Right"))
	{
		if (!IsTouchedRightWall)
			m_Sprite->AddRelativePos(Vector3(+300.f, 0.f, 0.f) * DeltaTime);
	}
	if (true == CInput::GetInst()->IsPush("Left"))
	{
		if (!IsTouchedLeftWall)
			m_Sprite->AddRelativePos(Vector3(-300.f, 0.f, 0.f) * DeltaTime);
	}
}

void Cdummy::DASHStart()
{
	DashSound->Play();
	IsOnDash = true;
	
	IsDashed = true;
	if (DIR::LEFT == Dir)
	{
		m_Sprite->SetPivot(0.19f, 0.36f, 0.f);
		DashDir = DASHDIR::LEFT;
		ChangeAnimation("PlayerDashLeft");
		DashleftEffect->GetAnimationInstance()->ChangeAnimation("DashLeftEffect");
	
	}
	if (DIR::RIGHT == Dir)
	{
		DashDir = DASHDIR::RIGHT;
		m_Sprite->SetPivot(0.85f, 0.36f, 0.f);
		ChangeAnimation("PlayerDashRight");
		DashrightEffect->GetAnimationInstance()->ChangeAnimation("DashRightEffect");
	
	}
	
}

void Cdummy::DASHStay()
{
	
	float DeltaTime = CEngine::GetInst()->GetDeltaTime();
	DashTime += DeltaTime;
	if (DASHDIR::LEFT == DashDir)
	{
		if (!IsTouchedLeftWall)
		{
			m_Sprite->AddRelativePos(Vector3(-900.f, 0.f, 0.f) * DeltaTime);
			
		}
			
		
	}
	if (DASHDIR::RIGHT == DashDir)
	{
		
		if (!IsTouchedRightWall)
		{
			m_Sprite->AddRelativePos(Vector3(+900.f, 0.f, 0.f) * DeltaTime);
			
		}
			

	}

	if (DashTime > 0.3f)
	{
		DashTime = 0;
	
		if (PHASE::RISING == Phase || PHASE::FALLING == Phase)
		{			
			
			PlayerFSM.ChangeState("jumpdown");
		}
		else if(PHASE::GROUND == Phase)
		{
			
			IsDashed = false;
			PlayerFSM.ChangeState("Idle");
		}

		
	}

}

void Cdummy::DASHEnd()
{
	if (DASHDIR::LEFT == DashDir)
	{
		
		DashleftEffect->GetAnimationInstance()->ChangeAnimation("DashBlank");
	


	}
	if (DASHDIR::RIGHT == DashDir)
	{

		DashrightEffect->GetAnimationInstance()->ChangeAnimation("DashBlank");

	}

	IsOnDash = false;
}

void Cdummy::GETATTACKStart()
{
	

	DamageSound->Play();
	IsBeingAttack = true;
	IsGetAttackPossible = false;
	m_Sprite->SetPivot(0.19f, 0.36f, 0.f);
	
	GetAttackTime = 0;
	if (IsHitFromLeft)
	{
		GetAttackEffect->GetAnimationInstance()->ChangeAnimation("GetAttackLeftEffect");
		ChangeAnimation("PlayerGetAttackRight");
	}
	else
	{
		GetAttackEffect->GetAnimationInstance()->ChangeAnimation("GetAttackRightEffect");
		ChangeAnimation("PlayerGetAttackLeft");
		
	}
	
}

void Cdummy::GETATTACKStay()
{
	float DeltaTime = CEngine::GetInst()->GetDeltaTime();
	GetAttackTime += DeltaTime;
	
	if (GetAttackTime > 0.1)
	{
		GetAttackEffect->GetAnimationInstance()->ChangeAnimation("GetAttackBlank");
	}

	if (GetAttackTime > 0.2)
	{
		PlayerFSM.ChangeState("jumpdown");
	}

	if (IsHitFromLeft)
	{
		if (!IsTouchedRightWall)
			m_Sprite->AddRelativePos(Vector3(900.f, 0.f, 0.f) * DeltaTime); 
		if (!IsTouchedTopWall)
			m_Sprite->AddRelativePos(Vector3(0.f, 300.f, 0.f) * DeltaTime);
	}
	else
	{
		if (!IsTouchedLeftWall)
			m_Sprite->AddRelativePos(Vector3(-900.f, 0.f, 0.f) * DeltaTime);
		if (!IsTouchedTopWall)
			m_Sprite->AddRelativePos(Vector3(0.f, 300.f, 0.f) * DeltaTime); 

	}


}

void Cdummy::GETATTACKEnd()
{
	GetAttackEffect->GetAnimationInstance()->ChangeAnimation("GetAttackBlank");
	IsBeingAttack = false;
}



void Cdummy::RESTOREStart()
{

	RestoreTime = 0;
	
	if (DIR::LEFT == Dir)
	{
		m_Sprite->SetPivot(0.19f, 0.36f, 0.f);
		ChangeAnimation("PlayerRestoreLeft");
	}
	if (DIR::RIGHT == Dir)
	{
		m_Sprite->SetPivot(0.77f, 0.36f, 0.f);
		ChangeAnimation("PlayerRestoreRight");
	}
}

void Cdummy::RESTOREStay()
{
	float DeltaTime = CEngine::GetInst()->GetDeltaTime();
	RestoreTime += DeltaTime;
	if (RestoreTime >= 2)
	{
		PlayerFSM.ChangeState("Idle");
		return;
	}
	if (false == CInput::GetInst()->IsPush("A"))
	{
		PlayerFSM.ChangeState("Idle");
	}
}

void Cdummy::ATTACKStart()
{
	
	IsOnAttack = true;
	AttackTime = 0;
	if (DIR::LEFT == Dir)
	{
		CAttackLeft* AttackLeft = m_Scene->CreateGameObject<CAttackLeft>("Bullet");
		AttackLeft->SetParent(this);
		AttackLeft->SetWorldPos(m_Muzzle->GetWorldPos() + Vector3(-100.f, 0.f, 0.f));
		AttackLeft->SetWorldRotation(GetWorldRot());
		
		m_Sprite->SetPivot(0.22f, 0.36f, 0.f);
		ChangeAnimation("PlayerAttackLeft");
	}
	if (DIR::RIGHT == Dir)
	{
		CAttackRight* AttackRight = m_Scene->CreateGameObject<CAttackRight>("Bullet");
		AttackRight->SetParent(this);
		AttackRight->SetWorldPos(m_Muzzle->GetWorldPos() + Vector3(100.f, 0.f, 0.f));
		AttackRight->SetWorldRotation(GetWorldRot());
		
		m_Sprite->SetPivot(0.55f, 0.36f, 0.f);
		ChangeAnimation("PlayerAttackRight");
	}
}

void Cdummy::ATTACKStay()
{
	float DeltaTime = CEngine::GetInst()->GetDeltaTime();
	AttackTime += DeltaTime;
	if (AttackTime >= 0.2)
	{
		IsOnAttack = false;
		if ((true == CInput::GetInst()->IsPush("Right") || true == CInput::GetInst()->IsPush("Left")) && Phase == PHASE::GROUND)
		{
			PlayerFSM.ChangeState("move");
		}
		else if(!(true == CInput::GetInst()->IsPush("Right") || true == CInput::GetInst()->IsPush("Left")) && Phase == PHASE::GROUND)
		{
			PlayerFSM.ChangeState("Idle");
		}
		else if(Phase == PHASE::FALLING || Phase == PHASE::RISING)
		{
			PlayerFSM.ChangeState("jumpdown");
		}
		
		
		
	
	}
	if (Phase == PHASE::FALLING || Phase == PHASE::RISING)
	{
		m_Sprite->AddRelativePos(Vector3(0.f, -750.f, 0.f) * DeltaTime);
	}

	if (true == CInput::GetInst()->IsPush("Right"))
	{
		if (!IsTouchedRightWall)
			m_Sprite->AddRelativePos(Vector3(+300.f, 0.f, 0.f) * DeltaTime);
	}
	if (true == CInput::GetInst()->IsPush("Left"))
	{
		if (!IsTouchedLeftWall)
			m_Sprite->AddRelativePos(Vector3(-300.f, 0.f, 0.f) * DeltaTime);
	}
}

void Cdummy::ATTACKEnd()
{
	IsOnAttack = false;
}

void Cdummy::ATTACKUPStart()
{

	CAttackUp* AttackUp = m_Scene->CreateGameObject<CAttackUp>("Bullet");
	AttackUp->SetParent(this);
	AttackUp->SetWorldPos(m_Muzzle->GetWorldPos() + Vector3(0.f, 100.f, 0.f));
	AttackUp->SetWorldRotation(GetWorldRot());

	AttackTime = 0;
	IsOnAttack = true;
	if (DIR::LEFT == Dir)
	{
		m_Sprite->SetPivot(0.21f, 0.36f, 0.f);
		ChangeAnimation("PlayerUpAttackLeft");
	}
	if (DIR::RIGHT == Dir)
	{
		m_Sprite->SetPivot(0.45f, 0.36f, 0.f);
		ChangeAnimation("PlayerUpAttackRight");
	}
}

void Cdummy::ATTACKUPStay()
{
	float DeltaTime = CEngine::GetInst()->GetDeltaTime();
	AttackTime += DeltaTime;
	if (AttackTime >= 0.2)
	{
		IsOnAttack = false;
		if ((true == CInput::GetInst()->IsPush("Right") || true == CInput::GetInst()->IsPush("Left")) && Phase == PHASE::GROUND)
		{
			PlayerFSM.ChangeState("move");
		}
		else if (!(true == CInput::GetInst()->IsPush("Right") || true == CInput::GetInst()->IsPush("Left")) && Phase == PHASE::GROUND)
		{
			PlayerFSM.ChangeState("Idle");
		}
		else if (Phase == PHASE::FALLING || Phase == PHASE::RISING)
		{
			PlayerFSM.ChangeState("jumpdown");
		}




	}
	if (Phase == PHASE::FALLING || Phase == PHASE::RISING)
	{
		m_Sprite->AddRelativePos(Vector3(0.f, -750.f, 0.f) * DeltaTime);
	}

	if (true == CInput::GetInst()->IsPush("Right"))
	{
		if (!IsTouchedRightWall)
			m_Sprite->AddRelativePos(Vector3(+300.f, 0.f, 0.f) * DeltaTime);
	}
	if (true == CInput::GetInst()->IsPush("Left"))
	{
		if (!IsTouchedLeftWall)
			m_Sprite->AddRelativePos(Vector3(-300.f, 0.f, 0.f) * DeltaTime);
	}

}

void Cdummy::ATTACKUPEnd()
{
	IsOnAttack = false;
}

void Cdummy::ATTACKDOWNStart()
{
	IsOnAttack = true;
	AttackTime = 0;

	CAttackDown* AttackDown = m_Scene->CreateGameObject<CAttackDown>("Bullet");
	AttackDown->SetParent(this);
	AttackDown->SetWorldPos(m_Muzzle->GetWorldPos() + Vector3(0.f, -130.f, 0.f));
	AttackDown->SetWorldRotation(GetWorldRot());

	if (DIR::LEFT == Dir)
	{
		m_Sprite->SetPivot(0.25f, 0.36f, 0.f);
		ChangeAnimation("PlayerDownAttackLeft");
	}
	if (DIR::RIGHT == Dir)
	{
		m_Sprite->SetPivot(0.55f, 0.36f, 0.f);
		ChangeAnimation("PlayerDownAttackRight");
	}
}

void Cdummy::ATTACKDOWNStay()
{
	float DeltaTime = CEngine::GetInst()->GetDeltaTime();
	AttackTime += DeltaTime;
	if (AttackTime >= 0.2)
	{
		IsOnAttack = false;
		if ((true == CInput::GetInst()->IsPush("Right") || true == CInput::GetInst()->IsPush("Left")) && Phase == PHASE::GROUND)
		{
			PlayerFSM.ChangeState("move");
		}
		else if (!(true == CInput::GetInst()->IsPush("Right") || true == CInput::GetInst()->IsPush("Left")) && Phase == PHASE::GROUND)
		{
			PlayerFSM.ChangeState("Idle");
		}
		else if (Phase == PHASE::FALLING || Phase == PHASE::RISING)
		{
			PlayerFSM.ChangeState("jumpdown");
		}




	}
	if (Phase == PHASE::FALLING || Phase == PHASE::RISING)
	{
		m_Sprite->AddRelativePos(Vector3(0.f, -750.f, 0.f) * DeltaTime);
	}

	if (true == CInput::GetInst()->IsPush("Right"))
	{
		if (!IsTouchedRightWall)
			m_Sprite->AddRelativePos(Vector3(+300.f, 0.f, 0.f) * DeltaTime);
	}
	if (true == CInput::GetInst()->IsPush("Left"))
	{
		if (!IsTouchedLeftWall)
			m_Sprite->AddRelativePos(Vector3(-300.f, 0.f, 0.f) * DeltaTime);
	}
}

void Cdummy::ATTACKDOWNEnd()
{
	IsOnAttack = false;
}

void Cdummy::AFTERDOWNATTACKStart()
{
	AfterDownAttackTime = 0;
}

void Cdummy::AFTERDOWNATTACKStay()
{
	float DeltaTime = CEngine::GetInst()->GetDeltaTime();
	AfterDownAttackTime += DeltaTime;
	if (AfterDownAttackTime >= 0.2)
	{
		AfterDownAttackTime = 0;
		PlayerFSM.ChangeState("jumpdown");
	}
	m_Sprite->AddRelativePos(Vector3(0.f, 800.f, 0.f) * DeltaTime);

	if (true == CInput::GetInst()->IsPush("Right"))
	{
		if (!IsTouchedRightWall)
			m_Sprite->AddRelativePos(Vector3(+300.f, 0.f, 0.f) * DeltaTime);
	}
	if (true == CInput::GetInst()->IsPush("Left"))
	{
		if (!IsTouchedLeftWall)
			m_Sprite->AddRelativePos(Vector3(-300.f, 0.f, 0.f) * DeltaTime);
	}
}

void Cdummy::SKILLStart()
{
	SkillSound->Play();




	IsOnAttack = true;
	AttackTime = 0;
	if (DIR::LEFT == Dir)
	{
		SkillLeftEffect->GetAnimationInstance()->ChangeAnimation("SkillLeftEffect");
		CPlayerMissileLeft* MissileLeft = m_Scene->CreateGameObject<CPlayerMissileLeft>("Bullet");
		MissileLeft->SetParent(this);
		MissileLeft->SetWorldPos(m_Muzzle->GetWorldPos() + Vector3(-100.f, 0.f, 0.f));
		MissileLeft->SetWorldRotation(GetWorldRot());
		m_Sprite->SetPivot(0.25f, 0.36f, 0.f);
		ChangeAnimation("PlayerSkillLeft");
	}
	if (DIR::RIGHT == Dir)
	{
		SkillRightEffect->GetAnimationInstance()->ChangeAnimation("SkillRightEffect");
		CPlayerMissileRight* MissileRight = m_Scene->CreateGameObject<CPlayerMissileRight>("Bullet");
		MissileRight->SetParent(this);
		MissileRight->SetWorldPos(m_Muzzle->GetWorldPos() + Vector3(100.f, 0.f, 0.f));
		MissileRight->SetWorldRotation(GetWorldRot());
		m_Sprite->SetPivot(0.35f, 0.36f, 0.f);
		ChangeAnimation("PlayerSkillRight");
	}
}

void Cdummy::SKILLStay()
{
	float DeltaTime = CEngine::GetInst()->GetDeltaTime();
	AttackTime += DeltaTime;
	if (AttackTime >= 0.3)
	{
		IsOnAttack = false;
		if ((true == CInput::GetInst()->IsPush("Right") || true == CInput::GetInst()->IsPush("Left")) && Phase == PHASE::GROUND)
		{
			PlayerFSM.ChangeState("move");
		}
		else if (!(true == CInput::GetInst()->IsPush("Right") || true == CInput::GetInst()->IsPush("Left")) && Phase == PHASE::GROUND)
		{
			PlayerFSM.ChangeState("Idle");
		}
		else if (Phase == PHASE::FALLING || Phase == PHASE::RISING)
		{
			PlayerFSM.ChangeState("jumpdown");
		}
	}
}

void Cdummy::SKILLEnd()
{
	SkillLeftEffect->GetAnimationInstance()->ChangeAnimation("SkillNone");
	SkillRightEffect->GetAnimationInstance()->ChangeAnimation("SkillNone");
	IsOnAttack = false;
}



