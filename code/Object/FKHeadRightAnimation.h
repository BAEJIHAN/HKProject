
#pragma once

#include "Animation/AnimationSequence2DInstance.h"

class CFKHeadRightAnimation :
	public CAnimationSequence2DInstance
{
public:
	CFKHeadRightAnimation();
	CFKHeadRightAnimation(const CFKHeadRightAnimation& Anim);
	~CFKHeadRightAnimation();

public:
	virtual bool Init();
	virtual CFKHeadRightAnimation* Clone();
};



