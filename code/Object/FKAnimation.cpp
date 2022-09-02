#include "FKAnimation.h"





CFKAnimation::CFKAnimation()
{
	SetTypeID<CFKAnimation>();
}

CFKAnimation::CFKAnimation(const CFKAnimation& Anim) :
	CAnimationSequence2DInstance(Anim)
{
}

CFKAnimation::~CFKAnimation()
{
}

bool CFKAnimation::Init()
{
	if (!CAnimationSequence2DInstance::Init())
		return false;

	/*

	FKAttackLeft 
		FKAttackPreLeft 
		FKAttackPreRight 
		FKAttackRight 
		FKGroggyLeft 
		FKGroggyRight 
		FKHitGroundLeft 
		FKHitGroundRight 
		FKIdleLeft 
		FKIdleRight 
		FKOnJumpLeft 
		FKOnJumpRight 
		FKPreJumpLeft 
		FKPreJumpRight 
		FKOnJumpAttackLeft 
		FKOnJumpAttackRight 
		FKRage 
		FKRollLeft 
		FKRollRight 
		FKStandLeft 
		FKStandRight 
		*/


	AddAnimation("FKAttackLeft", "FKAttackLeft");
	AddAnimation("FKAttackPreLeft", "FKAttackPreLeft");
	AddAnimation("FKAttackPreRight", "FKAttackPreRight");
	AddAnimation("FKAttackRight", "FKAttackRight");
	AddAnimation("FKGroggyLeft", "FKGroggyLeft");
	AddAnimation("FKGroggyRight", "FKGroggyRight");
	AddAnimation("FKHitGroundLeft", "FKHitGroundLeft");
	AddAnimation("FKHitGroundRight", "FKHitGroundRight");
	AddAnimation("FKIdleLeft", "FKIdleLeft");
	AddAnimation("FKIdleRight", "FKIdleRight");
	AddAnimation("FKOnJumpLeft", "FKOnJumpLeft");
	AddAnimation("FKOnJumpRight", "FKOnJumpRight");
	AddAnimation("FKPreJumpLeft", "FKPreJumpLeft");
	AddAnimation("FKPreJumpRight", "FKPreJumpRight");
	AddAnimation("FKOnJumpAttackLeft", "FKOnJumpAttackLeft");
	AddAnimation("FKOnJumpAttackRight", "FKOnJumpAttackRight");
	AddAnimation("FKRage", "FKRage");
	AddAnimation("FKRollLeft", "FKRollLeft");
	AddAnimation("FKRollRight", "FKRollRight");
	AddAnimation("FKStandLeft", "FKStandLeft");
	AddAnimation("FKStandRight", "FKStandRight");
	AddAnimation("FKLandLeft", "FKLandLeft");
	AddAnimation("FKLandRight", "FKLandRight");

	SetPlayTime("FKStandLeft", 0.7f);
	SetPlayTime("FKStandRight", 0.7f);

	SetPlayTime("FKRollLeft", 1.4f);
	SetPlayTime("FKRollRight", 1.4f);

	SetPlayTime("FKAttackPreLeft", 0.5f);
	SetPlayTime("FKAttackPreLeft", 0.5f);

	SetPlayTime("FKHitGroundLeft", 0.4f);
	SetPlayTime("FKHitGroundRight", 0.4f);

	SetPlayTime("FKPreJumpLeft", 0.5f);
	SetPlayTime("FKPreJumpRight", 0.5f);

	SetPlayTime("FKHitGroundLeft", 0.5f);
	SetPlayTime("FKHitGroundRight", 0.5f);

	SetPlayTime("FKIdleLeft", 1.0f);
	SetPlayTime("FKIdleRight", 1.0f);

	SetLoop("FKGroggyLeft", false);
	SetLoop("FKGroggyRight", false);

	return true;
}

CFKAnimation* CFKAnimation::Clone()
{
	return new CFKAnimation(*this);
}
