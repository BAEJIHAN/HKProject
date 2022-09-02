#include "Scene0.h"
#include "Scene/Scene.h"
#include "Scene/Viewport.h"
#include "Scene/SceneResource.h"

#include "../Object/FMonster.h"
#include "../Object/LMonster.h"
#include "../Object/BMonster.h"
#include "../Object/FK.h"
#include "../Object/FKHeadLeft.h"

#include "../Object/dummymonster.h"
#include "../Object/dummy.h"
#include "../Object/Floor.h"
#include "../Object/PlayerMissileLeft.h"
#include "../Object/PlayerMissileRight.h"
#include "../Object/RockDown.h"
#include "../Object/Col.h"



#include "../Object/Scene0BG.h"
#include "../Object/Scene0Col.h"
#include "../Scene/Scene1.h"



CScene0::CScene0()
{
	SetTypeID<CScene0>();
}

CScene0::~CScene0()
{
}

bool CScene0::Init()
{
	CreateMaterial();

	CreateAnimationSequence();

	CreateParticle();

	CScene0BG* BG;
	BG = m_Scene->CreateGameObject<CScene0BG>("BG");
	BG->SetRelativePos(866, 550, 0);



	Cdummy* dummy;
	dummy = m_Scene->CreateGameObject<Cdummy>("Player");
	dummy->SetRelativePos(300, 250, 0);
	dummy->SetCurMapSize(Vector2(1731, 1100));
	dummy->SetCurMap(CurMap::Map0);

	SetPlayerObject(dummy);

	CCol* col1;
	col1 = m_Scene->CreateGameObject<CCol>("col1");
	col1->SetRelativePos(33, 640, 1);
	col1->SetColExtent(Vector2(33.f, 450.f));

	CCol* col2;
	col2 = m_Scene->CreateGameObject<CCol>("col2");
	col2->SetRelativePos(865, 95, 1);
	col2->SetColExtent(Vector2(1731, 95));

	CScene0Col* changecol;
	changecol = m_Scene->CreateGameObject<CScene0Col>("changecol");
	changecol->SetRelativePos(1700, 300, 1);
	
	return true;
}



void CScene0::CreateMaterial()
{

}

void CScene0::CreateAnimationSequence()
{


}



void CScene0::CreateParticle()
{

}
