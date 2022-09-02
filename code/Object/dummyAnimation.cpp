#include "dummyAnimation.h"
#include "dummy.h"


CdummyAnimation::CdummyAnimation()
{
	SetTypeID<CdummyAnimation>();
}

CdummyAnimation::CdummyAnimation(const CdummyAnimation& Anim) :
	CAnimationSequence2DInstance(Anim)
{
}

CdummyAnimation::~CdummyAnimation()
{
}

bool CdummyAnimation::Init()
{
	if (!CAnimationSequence2DInstance::Init())
		return false;

/*
AddAnimation("PlayerAttackLeft","PlayerAttackLeft")PlayerAttackLeft
AddAnimation("PlayerDashLeft","PlayerDashLeft")PlayerDashLeft 
AddAnimation("PlayerDeadlyLeft","PlayerDeadlyLeft")PlayerDeadlyLeft 
AddAnimation("PlayerDoubleJumpLeft","PlayerDoubleJumpLeft")PlayerDoubleJumpLeft 
AddAnimation("PlayerDownAttackLeft","PlayerDownAttackLeft")PlayerDownAttackLeft 
AddAnimation("PlayerGetAttackLeft","PlayerGetAttackLeft")PlayerGetAttackLeft 
AddAnimation("PlayerHangingLeft","PlayerHangingLeft")PlayerHangingLeft 
AddAnimation("PlayerIdleLeft","PlayerIdleLeft")PlayerIdleLeft 
AddAnimation("PlayerJumpDownLeft","PlayerJumpDownLeft")PlayerJumpDownLeft 
AddAnimation("PlayerJumpUpLeft","PlayerJumpUpLeft")PlayerJumpUpLeft 
AddAnimation("PlayerLandLeft","PlayerLandLeft")PlayerLandLeft 
AddAnimation("PlayerRestoreLeft","PlayerRestoreLeft")PlayerRestoreLeft 
AddAnimation("PlayerStopLeft","PlayerStopLeft")PlayerStopLeft 
AddAnimation("PlayerTurnLeft","PlayerTurnLeft")PlayerTurnLeft 
AddAnimation("PlayerUpAttackLeft","PlayerUpAttackLeft")PlayerUpAttackLeft 
AddAnimation("PlayerWalkLeft","PlayerWalkLeft")PlayerWalkLeft 
AddAnimation("PlayerWallJumpLeft","PlayerWallJumpLeft")PlayerWallJumpLeft 
AddAnimation("PlayerWalkStartLeft","PlayerWalkStartLeft")PlayerWalkStartLeft 
AddAnimation("PlayerSkillLeft","PlayerSkillLeft")PlayerSkillLeft 
AddAnimation("PlayerAttackRight","PlayerAttackRight")PlayerAttackRight 
AddAnimation("PlayerDashRight","PlayerDashRight")PlayerDashRight 
AddAnimation("PlayerDeadlyRight","PlayerDeadlyRight")PlayerDeadlyRight 
AddAnimation("PlayerDoubleJumpRight","PlayerDoubleJumpRight")PlayerDoubleJumpRight 
AddAnimation("PlayerDownAttackRight","PlayerDownAttackRight")PlayerDownAttackRight 
AddAnimation("PlayerGetAttackRight","PlayerGetAttackRight")PlayerGetAttackRight 
AddAnimation("PlayerHangingRight","PlayerHangingRight")PlayerHangingRight 
AddAnimation("PlayerIdleRight","PlayerIdleRight")PlayerIdleRight 
AddAnimation("PlayerJumpDownRight","PlayerJumpDownRight")PlayerJumpDownRight 
AddAnimation("PlayerJumpUpRight","PlayerJumpUpRight")PlayerJumpUpRight 
AddAnimation("PlayerLandRight","PlayerLandRight")PlayerLandRight 
AddAnimation("PlayerRestoreRight","PlayerRestoreRight")PlayerRestoreRight 
AddAnimation("PlayerStopRight ","PlayerStopRight ")PlayerStopRight 
AddAnimation("PlayerTurnRight","PlayerTurnRight")PlayerTurnRight 
AddAnimation("PlayerUpAttackRight ","PlayerUpAttackRight ")PlayerUpAttackRight 
AddAnimation("PlayerWalkRight","PlayerWalkRight")PlayerWalkRight 
AddAnimation("PlayerWallJumpRight ","PlayerWallJumpRight ")PlayerWallJumpRight 
AddAnimation("PlayerWalkStartRight","PlayerWalkStartRight")PlayerWalkStartRight 
AddAnimation("PlayerSkillRight","PlayerSkillRight")PlayerSkillRight 
AddAnimation("PlayerDeath","PlayerDeath")PlayerDeath 
*/

	
	
	AddAnimation("PlayerAttackLeft", "PlayerAttackLeft");
	AddAnimation("PlayerDashLeft", "PlayerDashLeft");
	AddAnimation("PlayerDeadlyLeft", "PlayerDeadlyLeft");
	AddAnimation("PlayerDoubleJumpLeft", "PlayerDoubleJumpLeft");
	AddAnimation("PlayerDownAttackLeft", "PlayerDownAttackLeft");
	AddAnimation("PlayerGetAttackLeft", "PlayerGetAttackLeft");
	AddAnimation("PlayerHangingLeft", "PlayerHangingLeft");
	AddAnimation("PlayerIdleLeft", "PlayerIdleLeft");
	AddAnimation("PlayerJumpDownLeft", "PlayerJumpDownLeft");
	AddAnimation("PlayerJumpUpLeft", "PlayerJumpUpLeft");
	AddAnimation("PlayerLandLeft", "PlayerLandLeft");
	AddAnimation("PlayerRestoreLeft", "PlayerRestoreLeft");
	AddAnimation("PlayerStopLeft", "PlayerStopLeft");
	AddAnimation("PlayerTurnLeft", "PlayerTurnLeft");
	AddAnimation("PlayerUpAttackLeft", "PlayerUpAttackLeft");
	AddAnimation("PlayerWalkLeft", "PlayerWalkLeft");
	AddAnimation("PlayerWallJumpLeft", "PlayerWallJumpLeft");
	AddAnimation("PlayerWalkStartLeft", "PlayerWalkStartLeft");
	AddAnimation("PlayerSkillLeft", "PlayerSkillLeft");
	AddAnimation("PlayerAttackRight", "PlayerAttackRight");
	AddAnimation("PlayerDashRight", "PlayerDashRight");
	AddAnimation("PlayerDeadlyRight", "PlayerDeadlyRight");
	AddAnimation("PlayerDoubleJumpRight", "PlayerDoubleJumpRight");
	AddAnimation("PlayerDownAttackRight", "PlayerDownAttackRight");
	AddAnimation("PlayerGetAttackRight", "PlayerGetAttackRight");
	AddAnimation("PlayerHangingRight", "PlayerHangingRight");
	AddAnimation("PlayerIdleRight", "PlayerIdleRight");
	AddAnimation("PlayerJumpDownRight", "PlayerJumpDownRight");
	AddAnimation("PlayerJumpUpRight", "PlayerJumpUpRight");
	AddAnimation("PlayerLandRight", "PlayerLandRight");
	AddAnimation("PlayerRestoreRight", "PlayerRestoreRight");
	AddAnimation("PlayerStopRight", "PlayerStopRight");
	AddAnimation("PlayerTurnRight", "PlayerTurnRight");
	AddAnimation("PlayerUpAttackRight", "PlayerUpAttackRight");
	AddAnimation("PlayerWalkRight", "PlayerWalkRight");
	AddAnimation("PlayerWallJumpRight", "PlayerWallJumpRight");
	AddAnimation("PlayerWalkStartRight", "PlayerWalkStartRight");
	AddAnimation("PlayerSkillRight", "PlayerSkillRight");
	AddAnimation("PlayerDeath", "PlayerDeath");

	
	SetPlayTime("PlayerDeath", 2.f);
	SetPlayTime("PlayerWalkStartRight", 0.3f);
	SetPlayTime("PlayerWalkStartLeft", 0.3f);
	SetPlayTime("PlayerStopLeft", 0.2f);
	SetPlayTime("PlayerStopRight", 0.2f);
	SetPlayTime("PlayerTurnLeft", 0.2f);
	SetPlayTime("PlayerTurnRight", 0.2f);

	SetPlayTime("PlayerLandLeft", 0.2f);
	SetPlayTime("PlayerLandRight", 0.2f);
	SetPlayTime("PlayerAttackLeft", 0.2f);
	SetPlayTime("PlayerAttackRight", 0.2f);
	SetPlayTime("PlayerUpAttackLeft", 0.2f);
	SetPlayTime("PlayerUpAttackRight", 0.2f);
	SetPlayTime("PlayerDownAttackLeft", 0.2f);
	SetPlayTime("PlayerDownAttackRight", 0.2f);
	SetPlayTime("PlayerSkillLeft", 0.3f);
	SetPlayTime("PlayerSkillRight", 0.3f);

	SetPlayTime("PlayerDoubleJumpLeft", 0.6f);
	SetPlayTime("PlayerDoubleJumpRight", 0.6f);

	SetPlayTime("PlayerAttackLeft", 0.3f);
	SetPlayTime("PlayerAttackRight", 0.3f);

	SetPlayTime("PlayerGetAttackLeft", 0.2f);
	SetPlayTime("PlayerGetAttackRight", 0.2f);

	SetPlayTime("PlayerRestoreLeft", 2.f);
	SetPlayTime("PlayerRestoreRight", 2.f);

	SetLoop("PlayerDashLeft", false);
	SetLoop("PlayerDashRight", false);
	//SetLoop("PlayerJumpUpLeft", false);


	
	
	return true;
}

CdummyAnimation* CdummyAnimation::Clone()
{
	return new CdummyAnimation(*this);
}
