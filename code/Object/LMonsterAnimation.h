

#pragma once

#include "Animation/AnimationSequence2DInstance.h"

class CLMonsterAnimation :
	public CAnimationSequence2DInstance
{
public:
	CLMonsterAnimation();
	CLMonsterAnimation(const CLMonsterAnimation& Anim);
	~CLMonsterAnimation();

public:
	virtual bool Init();
	virtual CLMonsterAnimation* Clone();
};


