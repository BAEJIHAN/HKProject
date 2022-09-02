#include "PlayerMissileAnimation.h"


CPlayerMissileAnimation::CPlayerMissileAnimation()
{
	SetTypeID<CPlayerMissileAnimation>();
}

CPlayerMissileAnimation::CPlayerMissileAnimation(const CPlayerMissileAnimation& Anim) :
	CAnimationSequence2DInstance(Anim)
{
}

CPlayerMissileAnimation::~CPlayerMissileAnimation()
{
}

bool CPlayerMissileAnimation::Init()
{
	if (!CAnimationSequence2DInstance::Init())
		return false;

	AddAnimation("PlayerMissileLeft", "PlayerMissileLeft");
	AddAnimation("PlayerMissileRight", "PlayerMissileRight");

	SetPlayTime("PlayerMissileLeft", 0.2f);
	SetPlayTime("PlayerMissileRight", 0.2f);

	SetLoop("PlayerMissileLeft", false);
	SetLoop("PlayerMissileRight", false);

	return true;
}

CPlayerMissileAnimation* CPlayerMissileAnimation::Clone()
{
	return new CPlayerMissileAnimation(*this);
}
