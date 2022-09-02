#include "WingAnimation.h"

CWingAnimation::CWingAnimation()
{
	SetTypeID<CWingAnimation>();
}

CWingAnimation::CWingAnimation(const CWingAnimation& Anim) :
	CAnimationSequence2DInstance(Anim)
{
}

CWingAnimation::~CWingAnimation()
{
}

bool CWingAnimation::Init()
{
	if (!CAnimationSequence2DInstance::Init())
		return false;
	
	AddAnimation("WingLeft", "WingLeft");
	AddAnimation("WingRight", "WingRight");
	AddAnimation("WingNone", "WingNone");
	
	SetPlayTime("WingLeft", 0.65f);
	SetPlayTime("WingRight", 0.65f);


	return true;
}

CWingAnimation* CWingAnimation::Clone()
{
	return new CWingAnimation(*this);
}
