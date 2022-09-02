#include "BMonAttackAnimation.h"

CBMonAttackAnimation::CBMonAttackAnimation()
{
	SetTypeID<CBMonAttackAnimation>();
}

CBMonAttackAnimation::CBMonAttackAnimation(const CBMonAttackAnimation& Anim) :
	CAnimationSequence2DInstance(Anim)
{
}

CBMonAttackAnimation::~CBMonAttackAnimation()
{
}

bool CBMonAttackAnimation::Init()
{
	if (!CAnimationSequence2DInstance::Init())
		return false;

	AddAnimation("GroundHitEffect", "GroundHitEffect");
	SetPlayTime("GroundHitEffect", 0.1f);



	return true;
}

CBMonAttackAnimation* CBMonAttackAnimation::Clone()
{
	return new CBMonAttackAnimation(*this);
}
