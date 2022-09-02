#include "GetAttackAnimation.h"


CGetAttackAnimation::CGetAttackAnimation()
{
	SetTypeID<CGetAttackAnimation>();
}

CGetAttackAnimation::CGetAttackAnimation(const CGetAttackAnimation& Anim) :
	CAnimationSequence2DInstance(Anim)
{
}

CGetAttackAnimation::~CGetAttackAnimation()
{
}

bool CGetAttackAnimation::Init()
{
	if (!CAnimationSequence2DInstance::Init())
		return false;
	AddAnimation("GetAttackLeftEffect", "GetAttackLeftEffect");
	AddAnimation("GetAttackRightEffect", "GetAttackRightEffect");
	AddAnimation("GetAttackBlank", "GetAttackBlank");


	return true;
}

CGetAttackAnimation* CGetAttackAnimation::Clone()
{
	return new CGetAttackAnimation(*this);
}
