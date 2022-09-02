#pragma once

#include "Animation/AnimationSequence2DInstance.h"

class CSkillEffectAnimation :
	public CAnimationSequence2DInstance
{
public:
	CSkillEffectAnimation();
	CSkillEffectAnimation(const CSkillEffectAnimation& Anim);
	~CSkillEffectAnimation();

public:
	virtual bool Init();
	virtual CSkillEffectAnimation* Clone();
};


