
#pragma once

#include "Animation/AnimationSequence2DInstance.h"

class CdummyAnimation :
	public CAnimationSequence2DInstance
{
public:
	CdummyAnimation();
	CdummyAnimation(const CdummyAnimation& Anim);
	~CdummyAnimation();

public:
	virtual bool Init();
	virtual CdummyAnimation* Clone();
};

