

#pragma once

#include "Animation/AnimationSequence2DInstance.h"

class CFMonsterAnimation :
	public CAnimationSequence2DInstance
{
public:
	CFMonsterAnimation();
	CFMonsterAnimation(const CFMonsterAnimation& Anim);
	~CFMonsterAnimation();

public:
	virtual bool Init();
	virtual CFMonsterAnimation* Clone();
};


