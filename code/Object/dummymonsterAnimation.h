
#pragma once

#include "Animation/AnimationSequence2DInstance.h"

class CdummymonsterAnimation :
	public CAnimationSequence2DInstance
{
public:
	CdummymonsterAnimation();
	CdummymonsterAnimation(const CdummymonsterAnimation& Anim);
	~CdummymonsterAnimation();

public:
	virtual bool Init();
	virtual CdummymonsterAnimation* Clone();
};


