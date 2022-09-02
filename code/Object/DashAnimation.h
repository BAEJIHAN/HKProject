#pragma once

#include "Animation/AnimationSequence2DInstance.h"

class CDashAnimation :
	public CAnimationSequence2DInstance
{
public:
	CDashAnimation();
	CDashAnimation(const CDashAnimation& Anim);
	~CDashAnimation();

public:
	virtual bool Init();
	virtual CDashAnimation* Clone();
};


