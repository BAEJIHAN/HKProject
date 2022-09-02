

#pragma once

#include "Animation/AnimationSequence2DInstance.h"

class CBMonsterAnimation :
	public CAnimationSequence2DInstance
{
public:
	CBMonsterAnimation();
	CBMonsterAnimation(const CBMonsterAnimation& Anim);
	~CBMonsterAnimation();

public:
	virtual bool Init();
	virtual CBMonsterAnimation* Clone();
};


