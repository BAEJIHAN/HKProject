#include "dummymonsterAnimation.h"

CdummymonsterAnimation::CdummymonsterAnimation()
{
	SetTypeID<CdummymonsterAnimation>();
}

CdummymonsterAnimation::CdummymonsterAnimation(const CdummymonsterAnimation& Anim) :
	CAnimationSequence2DInstance(Anim)
{
}

CdummymonsterAnimation::~CdummymonsterAnimation()
{
}

bool CdummymonsterAnimation::Init()
{
	if (!CAnimationSequence2DInstance::Init())
		return false;
	/*
	HMonAttackLeft 
	HMonAttackRight 
	HMonAttackStartLeft 
	HMonAttackStartRight 
	HMonDeathLeft 
	HMonDeathRight 
	HMonIdleLeft 
	HMonIdleRight 
	HMonWalkLeft 
	HMonWalkRight 

		*/
	AddAnimation("HMonIdleLeft", "HMonIdleLeft");
	AddAnimation("HMonIdleRight", "HMonIdleRight");
	AddAnimation("HMonAttackLeft", "HMonAttackLeft");
	AddAnimation("HMonAttackRight", "HMonAttackRight");
	AddAnimation("HMonAttackStartLeft", "HMonAttackStartLeft");
	AddAnimation("HMonAttackStartRight", "HMonAttackStartRight");
	AddAnimation("HMonDeathLeft", "HMonDeathLeft");
	AddAnimation("HMonDeathRight", "HMonDeathRight");	
	AddAnimation("HMonWalkLeft", "HMonWalkLeft");
	AddAnimation("HMonWalkRight", "HMonWalkRight");

	SetPlayTime("HMonAttackStartLeft", 0.5);
	SetPlayTime("HMonAttackStartRight", 0.5);

	SetLoop("HMonDeathLeft", false);
	SetLoop("HMonDeathRight", false);

	return true;
}

CdummymonsterAnimation* CdummymonsterAnimation::Clone()
{
	return new CdummymonsterAnimation(*this);
}
