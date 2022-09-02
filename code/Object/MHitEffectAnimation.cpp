#include "MHitEffectAnimation.h"

CMHitEffectAnimation::CMHitEffectAnimation()
{
	SetTypeID<CMHitEffectAnimation>();
}

CMHitEffectAnimation::CMHitEffectAnimation(const CMHitEffectAnimation& Anim) :
	CAnimationSequence2DInstance(Anim)
{
}

CMHitEffectAnimation::~CMHitEffectAnimation()
{
}

bool CMHitEffectAnimation::Init()
{
	if (!CAnimationSequence2DInstance::Init())
		return false;

	AddAnimation("hit1", "hit1");
	AddAnimation("hit2", "hit2");
	AddAnimation("hit3", "hit3");
	AddAnimation("hit4", "hit4");
	AddAnimation("hit5", "hit5");
	AddAnimation("hit6", "hit6");
	AddAnimation("hitblank", "hitblank");






	return true;
}

CMHitEffectAnimation* CMHitEffectAnimation::Clone()
{
	return new CMHitEffectAnimation(*this);
}
