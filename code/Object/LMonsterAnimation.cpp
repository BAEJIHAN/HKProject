#include "LMonsterAnimation.h"


CLMonsterAnimation::CLMonsterAnimation()
{
	SetTypeID<CLMonsterAnimation>();
}

CLMonsterAnimation::CLMonsterAnimation(const CLMonsterAnimation& Anim) :
	CAnimationSequence2DInstance(Anim)
{
}

CLMonsterAnimation::~CLMonsterAnimation()
{
}

bool CLMonsterAnimation::Init()
{
	if (!CAnimationSequence2DInstance::Init())
		return false;

	AddAnimation("LMonAttackLeft", "LMonAttackLeft");
	AddAnimation("LMonAttackRight", "LMonAttackRight");
	AddAnimation("LMonDeathLeft", "LMonDeathLeft");
	AddAnimation("LMonDeathRight", "LMonDeathRight");
	AddAnimation("LMonIdleLeft", "LMonIdleLeft");	
	AddAnimation("LMonldleRight", "LMonldleRight");
	AddAnimation("LMonWalkLeft", "LMonWalkLeft");
	AddAnimation("LMonWalkRight", "LMonWalkRight");
	
	SetLoop("LMonDeathLeft", false);
	SetLoop("LMonDeathRight", false);


	return true;
}

CLMonsterAnimation* CLMonsterAnimation::Clone()
{
	return new CLMonsterAnimation(*this);
}
