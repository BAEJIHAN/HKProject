#include "FKHeadRightAnimation.h"

CFKHeadRightAnimation::CFKHeadRightAnimation()
{
	SetTypeID<CFKHeadRightAnimation>();
}

CFKHeadRightAnimation::CFKHeadRightAnimation(const CFKHeadRightAnimation& Anim) :
	CAnimationSequence2DInstance(Anim)
{
}

CFKHeadRightAnimation::~CFKHeadRightAnimation()
{
}

bool CFKHeadRightAnimation::Init()
{
	if (!CAnimationSequence2DInstance::Init())
		return false;

	AddAnimation("FKHeadHitRIght", "FKHeadHitRIght");
	AddAnimation("FKHeadIdleRight", "FKHeadIdleRight");
	AddAnimation("FKHeadDeathRight", "FKHeadDeathRight");

	SetLoop("FKHeadDeathRight", false);

	SetPlayTime("FKHeadDeathRight", 2);

	SetPlayTime("FKHeadHitRIght", 0.2f);

	return true;
}

CFKHeadRightAnimation* CFKHeadRightAnimation::Clone()
{
	return new CFKHeadRightAnimation(*this);
}
