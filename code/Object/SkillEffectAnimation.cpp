#include "SkillEffectAnimation.h"



CSkillEffectAnimation::CSkillEffectAnimation()
{
	SetTypeID<CSkillEffectAnimation>();
}

CSkillEffectAnimation::CSkillEffectAnimation(const CSkillEffectAnimation& Anim) :
	CAnimationSequence2DInstance(Anim)
{
}

CSkillEffectAnimation::~CSkillEffectAnimation()
{
}

bool CSkillEffectAnimation::Init()
{
	if (!CAnimationSequence2DInstance::Init())
		return false;

	AddAnimation("SkillLeftEffect", "SkillLeftEffect");
	AddAnimation("SkillRightEffect", "SkillRightEffect");
	AddAnimation("SkillNone", "SkillNone");

	SetPlayTime("SkillLeftEffect", 0.3f);
	SetPlayTime("SkillRightEffect", 0.3f);

	return true;
}

CSkillEffectAnimation* CSkillEffectAnimation::Clone()
{
	return new CSkillEffectAnimation(*this);
}
