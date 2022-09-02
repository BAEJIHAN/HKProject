#include "Scene4.h"
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

#include "../Object/Scene4BG.h"



#include "PathManager.h"

CScene4::CScene4()
{
	SetTypeID<CScene4>();
}

CScene4::~CScene4()
{
}

bool CScene4::Init()
{
	CreateMaterial();

	CreateAnimationSequence();

	CreateParticle();



	CScene4BG* BG;
	BG = m_Scene->CreateGameObject<CScene4BG>("BG");
	BG->SetRelativePos(1623, 550, 0);



	Cdummy* dummy;
	dummy = m_Scene->CreateGameObject<Cdummy>("Player");	
	dummy->SetRelativePos(1200, 174, 0);
	dummy->SetCurMapSize(Vector2(3247, 1100));
	dummy->SetCurMap(CurMap::Map4);

	SetPlayerObject(dummy);

	
	CFK* fk;
	fk = m_Scene->CreateGameObject<CFK>("fk");
	fk->SetRelativePos(1623, 1200, 0);
	
	//fk->SetRelativePos(1623, 1500, 0);




	CCol* col1;
	col1 = m_Scene->CreateGameObject<CCol>("col1");
	col1->SetRelativePos(1623, 38, 1);
	col1->SetColExtent(Vector2(1623, 75));

	CCol* col2;
	col2 = m_Scene->CreateGameObject<CCol>("col2");
	col2->SetRelativePos(173, 600, 1);
	col2->SetColExtent(Vector2(88, 495));
	

	CCol* col3;
	col3 = m_Scene->CreateGameObject<CCol>("col3");
	col3->SetRelativePos(2929, 707, 1);
	col3->SetColExtent(Vector2(325, 385));
	

	CCol* col4;
	col4 = m_Scene->CreateGameObject<CCol>("col4");
	col4->SetRelativePos(1623, 1025, 1);
	col4->SetColExtent(Vector2(1623, 75));

	return true;
}



void CScene4::CreateMaterial()
{

}

void CScene4::CreateAnimationSequence()
{


}



void CScene4::CreateParticle()
{

}
