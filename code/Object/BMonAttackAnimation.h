#pragma once

#include "Animation/AnimationSequence2DInstance.h"

class CBMonAttackAnimation :
	public CAnimationSequence2DInstance
{
public:
	CBMonAttackAnimation();
	CBMonAttackAnimation(const CBMonAttackAnimation& Anim);
	~CBMonAttackAnimation();

public:
	virtual bool Init();
	virtual CBMonAttackAnimation* Clone();
};



