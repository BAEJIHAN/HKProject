
#pragma once

#include "Animation/AnimationSequence2DInstance.h"

class CGetAttackAnimation :
	public CAnimationSequence2DInstance
{
public:
	CGetAttackAnimation();
	CGetAttackAnimation(const CGetAttackAnimation& Anim);
	~CGetAttackAnimation();

public:
	virtual bool Init();
	virtual CGetAttackAnimation* Clone();
};


