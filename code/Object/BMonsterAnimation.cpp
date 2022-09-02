#include "BMonsterAnimation.h"




CBMonsterAnimation::CBMonsterAnimation()
{
	SetTypeID<CBMonsterAnimation>();
}

CBMonsterAnimation::CBMonsterAnimation(const CBMonsterAnimation& Anim) :
	CAnimationSequence2DInstance(Anim)
{
}

CBMonsterAnimation::~CBMonsterAnimation()
{
}

bool CBMonsterAnimation::Init()
{
	if (!CAnimationSequence2DInstance::Init())
		return false;

	AddAnimation("BMonAttackLeft", "BMonAttackLeft");
	AddAnimation("BMonAttackRight", "BMonAttackRight");
	AddAnimation("BMonDeathLeft", "BMonDeathLeft");
	AddAnimation("BMonDeathRight", "BMonDeathRight");
	AddAnimation("BMonIdleLeft", "BMonIdleLeft");
	AddAnimation("BMonIdleRight", "BMonIdleRight");
	AddAnimation("BMonStompLeft", "BMonStompLeft");
	AddAnimation("BMonStompRight", "BMonStompRight");
	AddAnimation("BMonWalkLeft", "BMonWalkLeft");
	AddAnimation("BMonWalkRight", "BMonWalkRight");

	SetPlayTime("BMonAttackLeft", 0.7f);
	SetPlayTime("BMonAttackLeft", 0.7f);

	SetLoop("BMonDeathLeft", false);
	SetLoop("BMonDeathRight", false);



	return true;
}

CBMonsterAnimation* CBMonsterAnimation::Clone()
{
	return new CBMonsterAnimation(*this);
}
