#include "Scene3.h"
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

#include "../Object/Scene3BG.h"
#include "../Object/Scene3Col.h"
#include "../Scene/Scene4.h"

#include "PathManager.h"

CScene3::CScene3()
{
	SetTypeID<CScene3>();
}

CScene3::~CScene3()
{
}

bool CScene3::Init()
{
	CreateMaterial();

	CreateAnimationSequence();

	CreateParticle();


	CScene3BG* BG;
	BG = m_Scene->CreateGameObject<CScene3BG>("BG");
	BG->SetRelativePos(1811, 984, 0);



	Cdummy* dummy;
	dummy = m_Scene->CreateGameObject<Cdummy>("Player");	
	dummy->SetRelativePos(300, 402, 0);
	dummy->SetCurMapSize(Vector2(3622, 1968));
	dummy->SetCurMap(CurMap::Map3);

	SetPlayerObject(dummy);


	CBMonster* bmon;
	bmon = m_Scene->CreateGameObject<CBMonster>("bmon");
	bmon->SetRelativePos(2500, 452, 0);




	CCol* col1;
	col1 = m_Scene->CreateGameObject<CCol>("col1");
	col1->SetRelativePos(1811, 266, 1);
	col1->SetColExtent(Vector2(1811, 75));

	CCol* col2;
	col2 = m_Scene->CreateGameObject<CCol>("col2");
	col2->SetRelativePos(1649, 1723, 1);
	col2->SetColExtent(Vector2(275, 245));

	CCol* col3;
	col3 = m_Scene->CreateGameObject<CCol>("col3");
	col3->SetRelativePos(2777, 1337, 1);
	col3->SetColExtent(Vector2(845, 165));




	CScene3Col* scene3col;
	scene3col = m_Scene->CreateGameObject<CScene3Col>("scene3col");
	scene3col->SetRelativePos(3515, 420, 1);



	return true;
}



void CScene3::CreateMaterial()
{

}

void CScene3::CreateAnimationSequence()
{


}



void CScene3::CreateParticle()
{

}
