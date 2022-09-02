
#include "FKHeadLeftAnimation.h"

CFKHeadLeftAnimation::CFKHeadLeftAnimation()
{
	SetTypeID<CFKHeadLeftAnimation>();
}

CFKHeadLeftAnimation::CFKHeadLeftAnimation(const CFKHeadLeftAnimation& Anim) :
	CAnimationSequence2DInstance(Anim)
{
}

CFKHeadLeftAnimation::~CFKHeadLeftAnimation()
{
}

bool CFKHeadLeftAnimation::Init()
{
	if (!CAnimationSequence2DInstance::Init())
		return false;

	AddAnimation("FKHeadHitLeft", "FKHeadHitLeft");
	AddAnimation("FKHeadIdleLeft", "FKHeadIdleLeft");
	AddAnimation("FKHeadDeathLeft", "FKHeadDeathLeft");

	SetLoop("FKHeadDeathLeft", false);

	SetPlayTime("FKHeadDeathLeft", 2);
	SetPlayTime("FKHeadHitLeft", 0.2f);


	return true;
}

CFKHeadLeftAnimation* CFKHeadLeftAnimation::Clone()
{
	return new CFKHeadLeftAnimation(*this);
}
