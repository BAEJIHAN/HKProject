#include "FMonsterAnimation.h"



CFMonsterAnimation::CFMonsterAnimation()
{
	SetTypeID<CFMonsterAnimation>();
}

CFMonsterAnimation::CFMonsterAnimation(const CFMonsterAnimation& Anim) :
	CAnimationSequence2DInstance(Anim)
{
}

CFMonsterAnimation::~CFMonsterAnimation()
{
}

bool CFMonsterAnimation::Init()
{
	if (!CAnimationSequence2DInstance::Init())
		return false;


	AddAnimation("FMonAttackLeft", "FMonAttackLeft");
	AddAnimation("FMonAttackRight", "FMonAttackRight");
	AddAnimation("FMonAttackStartLeft", "FMonAttackStartLeft");
	AddAnimation("FMonAttackStartRight", "FMonAttackStartRight");
	AddAnimation("FMonIdleLeft", "FMonIdleLeft");
	AddAnimation("FMonIdleRight", "FMonIdleRight");
	AddAnimation("FMonDeathLeft", "FMonDeathLeft");
	AddAnimation("FMonDeathRight", "FMonDeathRight");

	SetLoop("FMonDeathLeft", false);
	SetLoop("FMonDeathRight", false);

	SetPlayTime("FMonDeathLeft", 0.3f);
	SetPlayTime("FMonDeathRight", 0.3f);

	SetPlayTime("FMonAttackStartLeft", 0.5f);
	SetPlayTime("FMonAttackStartRight", 0.5f);
	


	return true;
}

CFMonsterAnimation* CFMonsterAnimation::Clone()
{
	return new CFMonsterAnimation(*this);
}
