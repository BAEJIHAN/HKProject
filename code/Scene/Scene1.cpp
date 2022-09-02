#include "Scene1.h"
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

#include "PathManager.h"

#include "../Object/Scene1BG.h"
#include "../Object/Scene1Col.h"
#include "../Scene/Scene2.h"



CScene1::CScene1()
{
	SetTypeID<CScene1>();
}

CScene1::~CScene1()
{
}

bool CScene1::Init()
{
	CreateMaterial();

	CreateAnimationSequence();

	CreateParticle();

	CScene1BG* BG;
	BG = m_Scene->CreateGameObject<CScene1BG>("BG");
	BG->SetRelativePos(2472, 750, 0);


	 
	Cdummy* dummy;
	dummy = m_Scene->CreateGameObject<Cdummy>("Player");	
	dummy->SetRelativePos(300, 198, 0);
	dummy->SetCurMapSize(Vector2(4944, 1500));
	dummy->SetCurMap(CurMap::Map1);

	SetPlayerObject(dummy);

	Cdummymonster* dummymon1;
	dummymon1 = m_Scene->CreateGameObject<Cdummymonster>("dummymon1");
	dummymon1->SetMonPos(1000, 228, 0);

	Cdummymonster* dummymon2;
	dummymon2 = m_Scene->CreateGameObject<Cdummymonster>("dummymon2");
	dummymon2->SetMonPos(2500, 228, 0);

	Cdummymonster* dummymon3;
	dummymon3 = m_Scene->CreateGameObject<Cdummymonster>("dummymon3");
	dummymon3->SetMonPos(3500, 228, 0);

	CLMonster* lmon1;
	lmon1 = m_Scene->CreateGameObject<CLMonster>("lmon1");
	lmon1->SetMonPos(2000, 228, 0);

	CLMonster* lmon2;
	lmon2 = m_Scene->CreateGameObject<CLMonster>("lmon1");
	lmon2->SetMonPos(3400, 228, 0);

	

	CCol* col1;
	col1 = m_Scene->CreateGameObject<CCol>("col1");
	col1->SetRelativePos(2798 , 37, 1);
	col1->SetColExtent(Vector2(2798, 100.f));

	CCol* col2;
	col2 = m_Scene->CreateGameObject<CCol>("col2");
	col2->SetRelativePos(247, 830, 1);
	col2->SetColExtent(Vector2(235, 106));

	CCol* col3;
	col3 = m_Scene->CreateGameObject<CCol>("col3");
	col3->SetRelativePos(633, 1180, 1);
	col3->SetColExtent(Vector2(135, 265));


	CCol* col4;
	col4 = m_Scene->CreateGameObject<CCol>("col4");
	col4->SetRelativePos(3920, 1090, 1);
	col4->SetColExtent(Vector2(1685, 375));


	//CCol* col5;
	//col5 = m_Scene->CreateGameObject<CCol>("col5");
	//col5->SetRelativePos(5285, 1580, 1);
	//col5->SetColExtent(Vector2(320, 155));

	
	CScene1Col* changecol;
	changecol = m_Scene->CreateGameObject<CScene1Col>("changecol");
	changecol->SetRelativePos(4825, 267, 1);
	

	return true;
}



void CScene1::CreateMaterial()
{

}

void CScene1::CreateAnimationSequence()
{
	

}



void CScene1::CreateParticle()
{
	
}
