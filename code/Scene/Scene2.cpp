#include "Scene2.h"
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

#include "../Object/Scene2BG.h"
#include "../Object/Scene2Col.h"
#include "../Scene/Scene3.h"

#include "PathManager.h"

CScene2::CScene2()
{
	SetTypeID<CScene2>();
}

CScene2::~CScene2()
{
}

bool CScene2::Init()
{
	CreateMaterial();

	CreateAnimationSequence();

	CreateParticle();


	CScene2BG* BG;
	BG = m_Scene->CreateGameObject<CScene2BG>("BG");
	BG->SetRelativePos(1277, 2086, 0);



	Cdummy* dummy;
	dummy = m_Scene->CreateGameObject<Cdummy>("Player");
	dummy->SetRelativePos(1277, 463, 0);
	dummy->SetCurMapSize(Vector2(2554, 4172));
	dummy->SetCurMap(CurMap::Map2);

	SetPlayerObject(dummy);

	CFMonster* FMon1;
	FMon1 = m_Scene->CreateGameObject<CFMonster>("FMon1");
	FMon1->SetRelativePos(1657, 1343, 0);

	CFMonster* FMon2;
	FMon2 = m_Scene->CreateGameObject<CFMonster>("FMon2");
	FMon2->SetRelativePos(521, 1111, 0);

	CFMonster* FMon3;
	FMon3 = m_Scene->CreateGameObject<CFMonster>("FMon3");
	FMon3->SetRelativePos(1633, 2191, 0);

	CFMonster* FMon4;
	FMon4 = m_Scene->CreateGameObject<CFMonster>("FMon4");
	FMon4->SetRelativePos(1673, 3343, 0);

	CFMonster* FMon5;
	FMon5 = m_Scene->CreateGameObject<CFMonster>("FMon5");
	FMon5->SetRelativePos(873, 3203, 0);

	

	//CCol* col1;
	//col1 = m_Scene->CreateGameObject<CCol>("col1");
	//col1->SetRelativePos(1263, 127, 1);
	//col1->SetColExtent(Vector2(628, 75));



	CCol* col1;
	col1 = m_Scene->CreateGameObject<CCol>("col1");
	col1->SetRelativePos(1263, 327, 1);
	col1->SetColExtent(Vector2(628, 75));

	CCol* col2;
	col2 = m_Scene->CreateGameObject<CCol>("col2");
	col2->SetRelativePos(537, 463, 1);
	col2->SetColExtent(Vector2(80, 58));

	CCol* col3;
	col3 = m_Scene->CreateGameObject<CCol>("col3");
	col3->SetRelativePos(335, 663, 1);
	col3->SetColExtent(Vector2(123, 127));

	CCol* col4;
	col4 = m_Scene->CreateGameObject<CCol>("col4");
	col4->SetRelativePos(182, 1248, 1);
	col4->SetColExtent(Vector2(43, 565));

	CCol* col5;
	col5 = m_Scene->CreateGameObject<CCol>("col5");
	col5->SetRelativePos(2007, 561, 1);
	col5->SetColExtent(Vector2(115, 148));

	CCol* col6;
	col6 = m_Scene->CreateGameObject<CCol>("col6");
	col6->SetRelativePos(2209, 1139, 1);
	col6->SetColExtent(Vector2(79, 430));

	CCol* col7;
	col7 = m_Scene->CreateGameObject<CCol>("col7");
	col7->SetRelativePos(990, 911, 1);
	col7->SetColExtent(Vector2(140, 75));

	CCol* col8;
	col8 = m_Scene->CreateGameObject<CCol>("col8");
	col8->SetRelativePos(1271, 977, 1);
	col8->SetColExtent(Vector2(148, 134));

	CCol* col9;
	col9 = m_Scene->CreateGameObject<CCol>("col9");
	col9->SetRelativePos(795, 2187, 1);
	col9->SetColExtent(Vector2(600, 476));

	CCol* col10;
	col10 = m_Scene->CreateGameObject<CCol>("col10");
	col10->SetRelativePos(2000, 1997, 1);
	col10->SetColExtent(Vector2(135, 445));

	CCol* col11;
	col11 = m_Scene->CreateGameObject<CCol>("col11");
	col11->SetRelativePos(2255, 3019, 1);
	col11->SetColExtent(Vector2(293, 554));

	CCol* col12;
	col12 = m_Scene->CreateGameObject<CCol>("col12");
	col12->SetRelativePos(423, 2839, 1);
	col12->SetColExtent(Vector2(55, 165));

	CCol* col13;
	col13 = m_Scene->CreateGameObject<CCol>("col13");
	col13->SetRelativePos(281, 3425, 1);
	col13->SetColExtent(Vector2(81, 416));

	CCol* col14;
	col14 = m_Scene->CreateGameObject<CCol>("col14");
	col14->SetRelativePos(1465, 3891, 1);
	col14->SetColExtent(Vector2(1088, 72));

	CScene2Col* scene2col;
	scene2col = m_Scene->CreateGameObject<CScene2Col>("scene2col");
	scene2col->SetRelativePos(2475, 3650, 1);
	


	return true;
}



void CScene2::CreateMaterial()
{

}

void CScene2::CreateAnimationSequence()
{


}



void CScene2::CreateParticle()
{

}
