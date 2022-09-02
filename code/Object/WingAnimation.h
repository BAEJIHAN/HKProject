#pragma once

#include "Animation/AnimationSequence2DInstance.h"

class CWingAnimation :
	public CAnimationSequence2DInstance
{
public:
	CWingAnimation();
	CWingAnimation(const CWingAnimation& Anim);
	~CWingAnimation();

public:
	virtual bool Init();
	virtual CWingAnimation* Clone();
};


