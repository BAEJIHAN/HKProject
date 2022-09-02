#pragma once

#include "Animation/AnimationSequence2DInstance.h"

class CFKAnimation :
	public CAnimationSequence2DInstance
{
public:
	CFKAnimation();
	CFKAnimation(const CFKAnimation& Anim);
	~CFKAnimation();

public:
	virtual bool Init();
	virtual CFKAnimation* Clone();
};


