#include "DashAnimation.h"





CDashAnimation::CDashAnimation()
{
	SetTypeID<CDashAnimation>();
}

CDashAnimation::CDashAnimation(const CDashAnimation& Anim) :
	CAnimationSequence2DInstance(Anim)
{
}

CDashAnimation::~CDashAnimation()
{
}

bool CDashAnimation::Init()
{
	if (!CAnimationSequence2DInstance::Init())
		return false;

	AddAnimation("DashLeftEffect", "DashLeftEffect");
	AddAnimation("DashRightEffect", "DashRightEffect");
	AddAnimation("DashBlank", "DashBlank");
	
	SetPlayTime("DashLeftEffect", 0.15f);
	SetLoop("DashLeftEffect", false);

	SetPlayTime("DashRightEffect", 0.15f);
	SetLoop("DashRightEffect", false);

	return true;
}

CDashAnimation* CDashAnimation::Clone()
{
	return new CDashAnimation(*this);
}
