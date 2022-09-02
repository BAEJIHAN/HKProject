
#pragma once

#include "Animation/AnimationSequence2DInstance.h"

class CPlayerMissileAnimation :
	public CAnimationSequence2DInstance
{
public:
	CPlayerMissileAnimation();
	CPlayerMissileAnimation(const CPlayerMissileAnimation& Anim);
	~CPlayerMissileAnimation();

public:
	virtual bool Init();
	virtual CPlayerMissileAnimation* Clone();
};


