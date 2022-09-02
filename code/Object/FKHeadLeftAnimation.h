#pragma once

#include "Animation/AnimationSequence2DInstance.h"

class CFKHeadLeftAnimation :
	public CAnimationSequence2DInstance
{
public:
	CFKHeadLeftAnimation();
	CFKHeadLeftAnimation(const CFKHeadLeftAnimation& Anim);
	~CFKHeadLeftAnimation();

public:
	virtual bool Init();
	virtual CFKHeadLeftAnimation* Clone();
};


