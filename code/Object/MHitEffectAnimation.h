#pragma once

#include "Animation/AnimationSequence2DInstance.h"

class CMHitEffectAnimation :
	public CAnimationSequence2DInstance
{
public:
	CMHitEffectAnimation();
	CMHitEffectAnimation(const CMHitEffectAnimation& Anim);
	~CMHitEffectAnimation();

public:
	virtual bool Init();
	virtual CMHitEffectAnimation* Clone();
};


