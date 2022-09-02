#include "TestScene.h"


#include "Scene/Scene.h"
#include "Scene/Viewport.h"

#include "Scene/SceneResource.h"
#include "Resource/Particle/Particle.h"



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

#include "../Object/OrangeParticle.h"
#include "../Object/StoneParticle.h"
#include "../Object/DeathBubbleParticle.h"
#include "PathManager.h"

CTestScene::CTestScene()
{
	SetTypeID<CTestScene>();
}

CTestScene::~CTestScene()
{
}

bool CTestScene::Init()
{
	//HPWidget = m_Scene->GetViewport()->CreateWidgetWindow<CHP>("HPWiget");
	
	CreateMaterial();

	CreateAnimationSequence();

	CreateParticle();

	srand((unsigned int)time(NULL));

	Cdummy* dummy;
	dummy = m_Scene->CreateGameObject<Cdummy>("Player");
	dummy->SetCurMapSize(Vector2(4000, 2000) );
	dummy->SetRelativePos(200, 260 , 0);


	SetPlayerObject(dummy);
	
	
	CFloor* floor;

	floor = m_Scene->CreateGameObject<CFloor>("floor");
	floor->SetRelativePos(0.f, 100.f, 0.1f);
	floor->SetRelativeScale(6000, 200, 0);
	floor->SetColExtent(Vector2(3000, 100));
	floor->MSetColExtent(Vector2(1, 1));

	/*CFloor* floor2;
	floor2 = m_Scene->CreateGameObject<CFloor>("floor2");
	floor2->SetRelativePos(100, 250, 0);
	floor2->SetRelativeScale(100, 100, 0);
	floor2->SetColExtent(Vector2(50, 50));
	floor2->MSetColExtent(Vector2(50, 50));*/

	/*
	CFloor* floor3;
	floor3 = m_Scene->CreateGameObject<CFloor>("floor3");
	floor3->SetRelativePos(-100, 450, 0);
	floor3->SetRelativeScale(100, 100, 0);
	floor3->SetColExtent(Vector2(50, 50));
	floor3->MSetColExtent(Vector2(50, 50));
	*/

	CFloor* floor4;
	floor4 = m_Scene->CreateGameObject<CFloor>("floor4");
	floor4->SetRelativePos(-400, 450, 0);
	floor4->SetRelativeScale(100, 500, 0);
	floor4->SetColExtent(Vector2(50, 250));
	floor4->MSetColExtent(Vector2(50, 250));

	/*Cdummymonster* dummymonster1;
	dummymonster1 = m_Scene->CreateGameObject<Cdummymonster>("dummymonster1");	
	dummymonster1->SetRelativePos(500, 300, 1);*/

	//CLMonster* dummymonster1;
	//dummymonster1 = m_Scene->CreateGameObject<CLMonster>("dummymonster1");
	//dummymonster1->SetRelativePos(500, 300, 1);



	/*CBMonster* dummymonster1;
	dummymonster1 = m_Scene->CreateGameObject<CBMonster>("dummymonster1");
	dummymonster1->SetRelativePos(500, 320, 1);*/

	//CFK* dummymonster1;
	//dummymonster1 = m_Scene->CreateGameObject<CFK>("dummymonster1");
	//dummymonster1->SetRelativePos(450, 350, 1);
	
	//CFKHeadLeft* dummymonster1;
	//dummymonster1 = m_Scene->CreateGameObject<CFKHeadLeft>("dummymonster1");
	//dummymonster1->SetRelativePos(450, 350, 1);
	

	/*CRockDown* dummymonster1;
	dummymonster1 = m_Scene->CreateGameObject<CRockDown>("dummymonster1");
	dummymonster1->SetRelativePos(450, 1000, 1);*/

	//CFMonster* dummymonster1;
	//dummymonster1 = m_Scene->CreateGameObject<CFMonster>("dummymonster1");
	//dummymonster1->SetRelativePos(450, 400, 1);

	CBMonster* dummymon1;
	dummymon1 = m_Scene->CreateGameObject<CBMonster>("dummymon1");
	dummymon1->SetRelativePos(1000, 300, 0);



	/*CLMonster* dummymonster1;
	dummymonster1 = m_Scene->CreateGameObject<CLMonster>("dummymonster1");
	dummymonster1->SetRelativePos(500, 300, 1); */
	
	//Cdummymonster* dummymonster1;
	//dummymonster1 = m_Scene->CreateGameObject<Cdummymonster>("dummymonster1");
	//dummymonster1->SetMonPos(800, 300, 1);

	/*CLMonster* dummymonster1;
	dummymonster1 = m_Scene->CreateGameObject<CLMonster>("dummymonster1");
	dummymonster1->SetMonPos(800, 300, 1);*/
	//
	//m_Sound->Play();

	/*CBubbleParticle* BubbleParticle = m_Scene->CreateGameObject<CBubbleParticle>("BubbleParticle");

	BubbleParticle = m_Scene->CreateGameObject<CBubbleParticle>("BubbleParticle");

	BubbleParticle->SetRelativePos(200.f, 300.f, 0.f);*/

	//COrangeParticle* Orange = m_Scene->CreateGameObject<COrangeParticle>("Orange");	

	//Orange->SetRelativePos(200.f, 300.f, 0.f);

	/*CDeathBubbleParticle* dbubble = m_Scene->CreateGameObject<CDeathBubbleParticle>("dbubble");

	dbubble->SetRelativePos(200.f, 300.f, 0.f);*/

	//CStoneParticle* stone = m_Scene->CreateGameObject<CStoneParticle>("stone");

	//stone->SetRelativePos(200.f, 300.f, 0.f);



	return true;
}



void CTestScene::CreateMaterial()
{
	CResourceManager::GetInst()->LoadSound("UI", false, "beginbutton", "hollow/begin_button.wav");
	CResourceManager::GetInst()->LoadSound("UI", false, "bossbattle", "hollow/Boss Battle 1.wav");
	CResourceManager::GetInst()->LoadSound("UI", false, "bossexplode", "hollow/boss_explode.wav");
	CResourceManager::GetInst()->LoadSound("UI", false, "bossstun", "hollow/boss_stun.wav");
	CResourceManager::GetInst()->LoadSound("UI", false, "buzzerfly", "hollow/buzzer_fly.wav");
	CResourceManager::GetInst()->LoadSound("UI", false, "buzzerstartle", "hollow/buzzer_startle_02.wav");
	CResourceManager::GetInst()->LoadSound("UI", false, "cavebm1", "hollow/cave_atmos_misc.wav");
	CResourceManager::GetInst()->LoadSound("UI", false, "cavebm2", "hollow/cave_atmos_misc_3.wav");
	CResourceManager::GetInst()->LoadSound("UI", false, "caverockhit1", "hollow/cave_in_rock_hit.wav");
	CResourceManager::GetInst()->LoadSound("UI", false, "caverockhit2", "hollow/cave_in_rock_hit_2.wav");
	CResourceManager::GetInst()->LoadSound("UI", false, "enemydamage", "hollow/enemy_damage.wav");
	CResourceManager::GetInst()->LoadSound("UI", false, "enemydeath", "hollow/enemy_death_sword.wav");

	CResourceManager::GetInst()->LoadSound("UI", false, "fkattack1", "hollow/False_Knight_Attack_New_01.wav");
	CResourceManager::GetInst()->LoadSound("UI", false, "fkattack2", "hollow/False_Knight_Attack_New_02.wav");
	CResourceManager::GetInst()->LoadSound("UI", false, "fkattack3", "hollow/False_Knight_Attack_New_03.wav");
	CResourceManager::GetInst()->LoadSound("UI", false, "fkattack4", "hollow/False_Knight_Attack_New_04.wav");
	CResourceManager::GetInst()->LoadSound("UI", false, "fkattack5", "hollow/False_Knight_Attack_New_05.wav");
	CResourceManager::GetInst()->LoadSound("UI", false, "fkceilbreak", "hollow/false_knight_ceiling_break.wav");
	CResourceManager::GetInst()->LoadSound("UI", false, "fkdamagearmour", "hollow/false_knight_damage_armour.wav");
	CResourceManager::GetInst()->LoadSound("UI", false, "fkdamagearmourfinal", "hollow/false_knight_damage_armour_final.wav");
	CResourceManager::GetInst()->LoadSound("UI", false, "fkheaddamage", "hollow/false_knight_head_damage_2.wav");
	CResourceManager::GetInst()->LoadSound("UI", false, "fkjump", "hollow/false_knight_jump.wav");
	CResourceManager::GetInst()->LoadSound("UI", false, "fkland", "hollow/false_knight_land.wav");
	CResourceManager::GetInst()->LoadSound("UI", false, "fklandfirst", "hollow/false_knight_land_1st_time.wav");
	CResourceManager::GetInst()->LoadSound("UI", false, "fkroll", "hollow/false_knight_roll.wav");
	CResourceManager::GetInst()->LoadSound("UI", false, "fkstrikeground", "hollow/false_knight_strike_ground.wav");
	CResourceManager::GetInst()->LoadSound("UI", false, "fkswing", "hollow/false_knight_swing.wav");
	CResourceManager::GetInst()->LoadSound("UI", false, "fkhit1", "hollow/Fknight_hit_01.wav");
	CResourceManager::GetInst()->LoadSound("UI", false, "fkhit2", "hollow/Fknight_hit_02.wav");
	CResourceManager::GetInst()->LoadSound("UI", false, "fkhit3", "hollow/Fknight_hit_03.wav");
	CResourceManager::GetInst()->LoadSound("UI", false, "fkhit4", "hollow/Fknight_hit_05.wav");
	CResourceManager::GetInst()->LoadSound("UI", false, "fkhit5", "hollow/Fknight_hit_06.wav");
	CResourceManager::GetInst()->LoadSound("UI", false, "flyflying", "hollow/fly_flying.wav");
	CResourceManager::GetInst()->LoadSound("UI", false, "heartbeat", "hollow/heartbeat_B_01.wav");
	CResourceManager::GetInst()->LoadSound("UI", false, "heartbeat", "hollow/heartbeat_B_02.wav");
	CResourceManager::GetInst()->LoadSound("UI", false, "heartbeat", "hollow/heartbeat_B_03.wav");
	CResourceManager::GetInst()->LoadSound("UI", false, "playerdamage", "hollow/hero_damage.wav");
	CResourceManager::GetInst()->LoadSound("UI", false, "playerdash", "hollow/hero_dash.wav");
	CResourceManager::GetInst()->LoadSound("UI", false, "playerdeath1", "hollow/hero_death_extra_details.wav");
	CResourceManager::GetInst()->LoadSound("UI", false, "playerdeath2", "hollow/hero_death_v2.wav");
	CResourceManager::GetInst()->LoadSound("UI", false, "playerfalling", "hollow/hero_falling.wav");
	CResourceManager::GetInst()->LoadSound("UI", false, "playerskill", "hollow/hero_fireball.wav");
	CResourceManager::GetInst()->LoadSound("UI", false, "playerjump", "hollow/hero_jump.wav");
	CResourceManager::GetInst()->LoadSound("UI", false, "playerland", "hollow/hero_land_hard.wav");
	CResourceManager::GetInst()->LoadSound("UI", false, "playermantisclaw", "hollow/hero_mantis_claw.wav");
	CResourceManager::GetInst()->LoadSound("UI", false, "playerparry", "hollow/hero_parry.wav");
	CResourceManager::GetInst()->LoadSound("UI", true, "playerrun", "hollow/hero_run_footsteps_stone.wav");
	CResourceManager::GetInst()->LoadSound("UI", false, "playerdashshade", "hollow/hero_shade_dash_1.wav");
	CResourceManager::GetInst()->LoadSound("UI", false, "playerdashair", "hollow/hero_super_dash_air_brake.wav");	
	CResourceManager::GetInst()->LoadSound("UI", false, "playerwalljump", "hollow/hero_wall_jump.wav");
	CResourceManager::GetInst()->LoadSound("UI", false, "playerslide", "hollow/hero_wall_slide.wav");
	CResourceManager::GetInst()->LoadSound("UI", false, "playerwings", "hollow/hero_wings.wav");
	CResourceManager::GetInst()->LoadSound("UI", false, "playersword1", "hollow/sword_1.wav");
	CResourceManager::GetInst()->LoadSound("UI", false, "playersword2", "hollow/sword_2.wav");
	CResourceManager::GetInst()->LoadSound("UI", false, "playersword3", "hollow/sword_3.wav");
	CResourceManager::GetInst()->LoadSound("UI", false, "playersword4", "hollow/sword_4.wav");
	CResourceManager::GetInst()->LoadSound("UI", false, "playersword5", "hollow/sword_5.wav");

	CResourceManager::GetInst()->LoadSound("UI", false, "bmonrun", "hollow/ruin_fat_sentry_run_loop.wav");
	CResourceManager::GetInst()->LoadSound("UI", false, "bmonattack", "hollow/Ruins_Sentry_Fat_attack_02.wav");
	CResourceManager::GetInst()->LoadSound("UI", false, "monattack", "hollow/Ruins_Sentry_attack_02.wav");
	

	CResourceManager::GetInst()->LoadSound("UI", false, "playerswordreject", "hollow/sword_hit_reject.wav");

	m_Sound = CResourceManager::GetInst()->FindSound("playerwalk");


	//CResourceManager::GetInst()->CreateMaterial<CMaterial>("Orange");
	//CMaterial* Material = m_Scene->GetResource()->FindMaterial("Orange");

	//Material->AddTexture(0, (int)Buffer_Shader_Type::Pixel, "Orange", TEXT("Particle/Orange.png"));

	//Material->SetShader("ParticleRenderShader");
	//Material->SetRenderState("AlphaBlend");

	CResourceManager::GetInst()->CreateMaterial<CMaterial>("Orange");
	CMaterial* Material = m_Scene->GetResource()->FindMaterial("Orange");
	Material->AddTexture(0, (int)Buffer_Shader_Type::Pixel, "Orange", TEXT("Particle/Orange.png"));
	Material->SetShader("ParticleRenderShader");
	Material->SetRenderState("AlphaBlend");

	CResourceManager::GetInst()->CreateMaterial<CMaterial>("Stone");
	CMaterial* Material1 = m_Scene->GetResource()->FindMaterial("Stone");
	Material1->AddTexture(0, (int)Buffer_Shader_Type::Pixel, "Stone", TEXT("Particle/stone.png"));
	Material1->SetShader("ParticleRenderShader");
	Material1->SetRenderState("AlphaBlend");

	CResourceManager::GetInst()->CreateMaterial<CMaterial>("Deathbubble");
	CMaterial* Material2 = m_Scene->GetResource()->FindMaterial("Deathbubble");
	Material2->AddTexture(0, (int)Buffer_Shader_Type::Pixel, "Deathbubble", TEXT("Particle/Deathbubble.png"));
	Material2->SetShader("ParticleRenderShader");
	Material2->SetRenderState("AlphaBlend");


}

void CTestScene::CreateAnimationSequence()
{
	const PathInfo* AniPath = CPathManager::GetInst()->FindPath("Animation");
	char AniListPath[255] = {};
	strcat_s(AniListPath, AniPath->PathMultibyte);
	strcat_s(AniListPath, "PlayerAnimationList.txt");

	char tAniName[256] = {};
	int Length = 0;
	int tFrameCount = 0;

	FILE* fp = nullptr;
	fopen_s(&fp, AniListPath, "rt");

	for (int i = 0; i < 39; i++)
	{
		fscanf_s(fp, "%d", &Length);
		fread(tAniName, sizeof(char), Length + 1, fp);
		tAniName[Length] = '\0';
		fscanf_s(fp, "%d", &tFrameCount);

		char buffer[256] = "0_hollow/player/";
		const char* destbuffer = tAniName;
		strcat_s(buffer, destbuffer);
		strcat_s(buffer, ".png");
		TCHAR szUniCode[256] = { 0, };
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, buffer, (int)strlen(buffer), szUniCode, (int)256);


		CResourceManager::GetInst()->CreateAnimationSequence2D(tAniName, tAniName, szUniCode);

		for (int j = 0; j < tFrameCount; j++)
		{
			CResourceManager::GetInst()->AddAnimationSequence2DFrame(tAniName, Vector2(128.f + 256.f * j, 76.f), PlayerSize);
		}

	}

	fclose(fp);

	//뿔몬 애니메이션

	char HMAniListPath[255] = {};
	strcat_s(HMAniListPath, AniPath->PathMultibyte);
	strcat_s(HMAniListPath, "HMonAnimationList.txt");

	char HMAniName[256] = {};
	Length = 0;
	tFrameCount = 0;

	fp = nullptr;
	fopen_s(&fp, HMAniListPath, "rt");

	for (int i = 0; i < 10; i++)
	{
		fscanf_s(fp, "%d", &Length);
		fread(HMAniName, sizeof(char), Length + 1, fp);
		HMAniName[Length] = '\0';
		fscanf_s(fp, "%d", &tFrameCount);

		char buffer[256] = "0_hollow/monster/hornmonster/";
		const char* destbuffer = HMAniName;
		strcat_s(buffer, destbuffer);
		strcat_s(buffer, ".png");
		TCHAR szUniCode[256] = { 0, };
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, buffer, (int)strlen(buffer), szUniCode, (int)256);

		CResourceManager::GetInst()->CreateAnimationSequence2D(HMAniName, HMAniName, szUniCode);

		for (int j = 0; j < tFrameCount; j++)
		{
			CResourceManager::GetInst()->AddAnimationSequence2DFrame(HMAniName, Vector2(128.f + 256.f * j, 56.f), Vector2(190.f, 200.f));
		}

	}

	fclose(fp);

	//점프몬 애니메이션

	char LMAniListPath[255] = {};
	strcat_s(LMAniListPath, AniPath->PathMultibyte);
	strcat_s(LMAniListPath, "LMonAnimationList.txt");

	char LMAniName[256] = {};
	Length = 0;
	tFrameCount = 0;

	fp = nullptr;
	fopen_s(&fp, LMAniListPath, "rt");

	for (int i = 0; i < 8; i++)
	{
		fscanf_s(fp, "%d", &Length);
		fread(LMAniName, sizeof(char), Length + 1, fp);
		LMAniName[Length] = '\0';
		fscanf_s(fp, "%d", &tFrameCount);

		char buffer[256] = "0_hollow/monster/lmonster/";
		const char* destbuffer = LMAniName;
		strcat_s(buffer, destbuffer);
		strcat_s(buffer, ".png");
		TCHAR szUniCode[256] = { 0, };
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, buffer, (int)strlen(buffer), szUniCode, (int)256);

		CResourceManager::GetInst()->CreateAnimationSequence2D(LMAniName, LMAniName, szUniCode);

		for (int j = 0; j < tFrameCount; j++)
		{
			CResourceManager::GetInst()->AddAnimationSequence2DFrame(LMAniName, Vector2(128.f + 256.f * j, 56.f), Vector2(190.f, 200.f));
		}

	}

	fclose(fp);

	//파리몬 애니메이션

	char FMAniListPath[255] = {};
	strcat_s(FMAniListPath, AniPath->PathMultibyte);
	strcat_s(FMAniListPath, "FMonAnimationList.txt");

	char FMAniName[256] = {};
	Length = 0;
	tFrameCount = 0;

	fp = nullptr;
	fopen_s(&fp, FMAniListPath, "rt");

	for (int i = 0; i < 8; i++)
	{
		fscanf_s(fp, "%d", &Length);
		fread(FMAniName, sizeof(char), Length + 1, fp);
		FMAniName[Length] = '\0';
		fscanf_s(fp, "%d", &tFrameCount);

		char buffer[256] = "0_hollow/monster/fmonster/";
		const char* destbuffer = FMAniName;
		strcat_s(buffer, destbuffer);
		strcat_s(buffer, ".png");
		TCHAR szUniCode[256] = { 0, };
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, buffer, (int)strlen(buffer), szUniCode, (int)256);

		CResourceManager::GetInst()->CreateAnimationSequence2D(FMAniName, FMAniName, szUniCode);

		for (int j = 0; j < tFrameCount; j++)
		{
			CResourceManager::GetInst()->AddAnimationSequence2DFrame(FMAniName, Vector2(128.f + 256.f * j, 116.f), Vector2(140.f, 140.f));

		}

	}

	fclose(fp);

	//빅몬 애니메이션

	char BMAniListPath[255] = {};
	strcat_s(BMAniListPath, AniPath->PathMultibyte);
	strcat_s(BMAniListPath, "BMonAnimationList.txt");

	char BMAniName[256] = {};
	Length = 0;
	tFrameCount = 0;

	fp = nullptr;
	fopen_s(&fp, BMAniListPath, "rt");

	for (int i = 0; i < 10; i++)
	{
		fscanf_s(fp, "%d", &Length);
		fread(BMAniName, sizeof(char), Length + 1, fp);
		BMAniName[Length] = '\0';
		fscanf_s(fp, "%d", &tFrameCount);

		char buffer[256] = "0_hollow/monster/bmonster/";
		const char* destbuffer = BMAniName;
		strcat_s(buffer, destbuffer);
		strcat_s(buffer, ".png");
		TCHAR szUniCode[256] = { 0, };
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, buffer, (int)strlen(buffer), szUniCode, (int)256);

		CResourceManager::GetInst()->CreateAnimationSequence2D(BMAniName, BMAniName, szUniCode);

		for (int j = 0; j < tFrameCount; j++)
		{
			CResourceManager::GetInst()->AddAnimationSequence2DFrame(BMAniName, Vector2(128.f + 256.f * j, 121.f), Vector2(126.f, 135.f));
		}

	}

	fclose(fp);

	//거짓된 기사 애니메이션

	char FKAniListPath[255] = {};
	strcat_s(FKAniListPath, AniPath->PathMultibyte);
	strcat_s(FKAniListPath, "FKAnimationList.txt");

	char FKAniName[256] = {};
	Length = 0;
	tFrameCount = 0;

	fp = nullptr;
	fopen_s(&fp, FKAniListPath, "rt");

	for (int i = 0; i < 23; i++)
	{
		fscanf_s(fp, "%d", &Length);
		fread(FKAniName, sizeof(char), Length + 1, fp);
		FKAniName[Length] = '\0';
		fscanf_s(fp, "%d", &tFrameCount);

		char buffer[256] = "0_hollow/monster/fk/";
		const char* destbuffer = FKAniName;
		strcat_s(buffer, destbuffer);
		strcat_s(buffer, ".png");
		TCHAR szUniCode[256] = { 0, };
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, buffer, (int)strlen(buffer), szUniCode, (int)256);

		CResourceManager::GetInst()->CreateAnimationSequence2D(FKAniName, FKAniName, szUniCode);

		for (int j = 0; j < tFrameCount; j++)
		{
			CResourceManager::GetInst()->AddAnimationSequence2DFrame(FKAniName, Vector2(128.f + 256.f * j, 76.f), Vector2(250.f, 180.f));
		}

	}

	fclose(fp);

	//거짓된 머리 애니메이션

	char FKHeadAniListPath[255] = {};
	strcat_s(FKHeadAniListPath, AniPath->PathMultibyte);
	strcat_s(FKHeadAniListPath, "FKHeadAnimationList.txt");

	char FKHeadAniName[256] = {};
	Length = 0;
	tFrameCount = 0;

	fp = nullptr;
	fopen_s(&fp, FKHeadAniListPath, "rt");

	for (int i = 0; i < 6; i++)
	{
		fscanf_s(fp, "%d", &Length);
		fread(FKHeadAniName, sizeof(char), Length + 1, fp);
		FKHeadAniName[Length] = '\0';
		fscanf_s(fp, "%d", &tFrameCount);

		char buffer[256] = "0_hollow/monster/fkhead/";
		const char* destbuffer = FKHeadAniName;
		strcat_s(buffer, destbuffer);
		strcat_s(buffer, ".png");
		TCHAR szUniCode[256] = { 0, };
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, buffer, (int)strlen(buffer), szUniCode, 256);

		CResourceManager::GetInst()->CreateAnimationSequence2D(FKHeadAniName, FKHeadAniName, szUniCode);

		for (int j = 0; j < tFrameCount; j++)
		{
			CResourceManager::GetInst()->AddAnimationSequence2DFrame(FKHeadAniName, Vector2(128.f + 256.f * j, 76.f), Vector2(250.f, 180.f));
		}

	}

	fclose(fp);



	//미사일
	CResourceManager::GetInst()->CreateAnimationSequence2D("PlayerMissileLeft", "PlayerMissileLeft", L"0_hollow/effect/PlayerMssileLeft.png");

	for (int j = 0; j < 4; j++)
	{
		CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerMissileLeft", Vector2(128.f + 256.f * j, 152.f), Vector2(250.f, 110.f));
	}

	CResourceManager::GetInst()->CreateAnimationSequence2D("PlayerMissileRight", "PlayerMissileRight", L"0_hollow/effect/PlayerMssileRight.png");

	for (int j = 0; j < 4; j++)
	{
		CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerMissileRight", Vector2(9.f + 256.f * j, 152.f), Vector2(250.f, 110.f));
	}


	//이펙트

	//대쉬 이펙트
	CResourceManager::GetInst()->CreateAnimationSequence2D("DashLeftEffect", "DashLeftEffect", L"0_hollow/effect/DashLeftEffect.png");

	for (int j = 0; j < 2; j++)
	{
		CResourceManager::GetInst()->AddAnimationSequence2DFrame("DashLeftEffect", Vector2(256.f + 512.f * j, 106.f), Vector2(400.f, 300.f));
	}

	CResourceManager::GetInst()->CreateAnimationSequence2D("DashRightEffect", "DashRightEffect", L"0_hollow/effect/DashRightEffect.png");

	for (int j = 0; j < 2; j++)
	{
		CResourceManager::GetInst()->AddAnimationSequence2DFrame("DashRightEffect", Vector2(0.f + 512.f * j, 106.f), Vector2(400.f, 300.f));
	}

	CResourceManager::GetInst()->CreateAnimationSequence2D("DashBlank", "DashBlank", L"0_hollow/effect/DashRightEffect.png");

	for (int j = 0; j < 1; j++)
	{
		CResourceManager::GetInst()->AddAnimationSequence2DFrame("DashBlank", Vector2(1, 1), Vector2(1, 1));
	}


	//날개 이펙트
	CResourceManager::GetInst()->CreateAnimationSequence2D("WingLeft", "WingLeft", L"0_hollow/effect/WingLeft.png");

	for (int j = 0; j < 6; j++)
	{
		CResourceManager::GetInst()->AddAnimationSequence2DFrame("WingLeft", Vector2(76.f + 512.f * j, 126.f), Vector2(360.f, 260.f));
	}

	CResourceManager::GetInst()->CreateAnimationSequence2D("WingRight", "WingRight", L"0_hollow/effect/WingRight.png");

	for (int j = 0; j < 6; j++)
	{
		CResourceManager::GetInst()->AddAnimationSequence2DFrame("WingRight", Vector2(76.f + 512.f * j, 126.f), Vector2(360.f, 260.f));
	}

	CResourceManager::GetInst()->CreateAnimationSequence2D("WingNone", "WingNone", L"0_hollow/effect/WingLeft.png");

	for (int j = 0; j < 1; j++)
	{
		CResourceManager::GetInst()->AddAnimationSequence2DFrame("WingNone", Vector2(1, 1), Vector2(1, 1));
	}

	//스킬 이펙트
	CResourceManager::GetInst()->CreateAnimationSequence2D("SkillLeftEffect", "SkillLeftEffect", L"0_hollow/effect/SkillLeftEffect.png");

	for (int j = 0; j < 6; j++)
	{
		CResourceManager::GetInst()->AddAnimationSequence2DFrame("SkillLeftEffect", Vector2(106.f + 512.f * j, 116.f), Vector2(300.f, 280.f));
	}

	CResourceManager::GetInst()->CreateAnimationSequence2D("SkillRightEffect", "SkillRightEffect", L"0_hollow/effect/SkillRightEffect.png");

	for (int j = 0; j < 6; j++)
	{
		CResourceManager::GetInst()->AddAnimationSequence2DFrame("SkillRightEffect", Vector2(106.f + 512.f * j, 116.f), Vector2(300.f, 280.f));
	}

	CResourceManager::GetInst()->CreateAnimationSequence2D("SkillNone", "SkillNone", L"0_hollow/effect/SkillRightEffect.png");

	for (int j = 0; j < 1; j++)
	{
		CResourceManager::GetInst()->AddAnimationSequence2DFrame("SkillNone", Vector2(1, 1), Vector2(1, 1));
	}

	//플레이어 피격 이펙트
	CResourceManager::GetInst()->CreateAnimationSequence2D("GetAttackLeftEffect", "GetAttackLeftEffect", L"0_hollow/effect/GetAttackLeftEffect.png");

	for (int j = 0; j < 1; j++)
	{
		CResourceManager::GetInst()->AddAnimationSequence2DFrame("GetAttackLeftEffect", Vector2(0, 0), Vector2(277, 188));
	}

	CResourceManager::GetInst()->CreateAnimationSequence2D("GetAttackRightEffect", "GetAttackRightEffect", L"0_hollow/effect/GetAttackRightEffect.png");

	for (int j = 0; j < 1; j++)
	{
		CResourceManager::GetInst()->AddAnimationSequence2DFrame("GetAttackRightEffect", Vector2(0, 0), Vector2(277, 188));
	}

	CResourceManager::GetInst()->CreateAnimationSequence2D("GetAttackBlank", "GetAttackBlank", L"0_hollow/effect/Blank.png");

	for (int j = 0; j < 1; j++)
	{
		CResourceManager::GetInst()->AddAnimationSequence2DFrame("GetAttackBlank", Vector2(1, 1), Vector2(1, 1));
	}

	//몬스터 피격 이펙트
	CResourceManager::GetInst()->CreateAnimationSequence2D("hit1", "hit1", L"0_hollow/effect/hit1.png");

	for (int j = 0; j < 1; j++)
	{
		CResourceManager::GetInst()->AddAnimationSequence2DFrame("hit1", Vector2(0, 0), Vector2(408, 247));
	}

	CResourceManager::GetInst()->CreateAnimationSequence2D("hit2", "hit2", L"0_hollow/effect/hit2.png");

	for (int j = 0; j < 1; j++)
	{
		CResourceManager::GetInst()->AddAnimationSequence2DFrame("hit2", Vector2(0, 0), Vector2(356, 215));
	}

	CResourceManager::GetInst()->CreateAnimationSequence2D("hit3", "hit3", L"0_hollow/effect/hit3.png");

	for (int j = 0; j < 1; j++)
	{
		CResourceManager::GetInst()->AddAnimationSequence2DFrame("hit3", Vector2(0, 0), Vector2(215, 80));
	}

	CResourceManager::GetInst()->CreateAnimationSequence2D("hit4", "hit4", L"0_hollow/effect/hit4.png");

	for (int j = 0; j < 1; j++)
	{
		CResourceManager::GetInst()->AddAnimationSequence2DFrame("hit4", Vector2(0, 0), Vector2(213, 70));
	}

	CResourceManager::GetInst()->CreateAnimationSequence2D("hit5", "hit5", L"0_hollow/effect/hit5.png");

	for (int j = 0; j < 1; j++)
	{
		CResourceManager::GetInst()->AddAnimationSequence2DFrame("hit5", Vector2(0, 0), Vector2(357, 224));
	}

	CResourceManager::GetInst()->CreateAnimationSequence2D("hit6", "hit6", L"0_hollow/effect/hit6.png");

	for (int j = 0; j < 1; j++)
	{
		CResourceManager::GetInst()->AddAnimationSequence2DFrame("hit6", Vector2(0, 0), Vector2(402, 233));
	}

	CResourceManager::GetInst()->CreateAnimationSequence2D("hitblank", "hitblank", L"0_hollow/effect/hit6.png");

	for (int j = 0; j < 1; j++)
	{
		CResourceManager::GetInst()->AddAnimationSequence2DFrame("hitblank", Vector2(1, 1), Vector2(1, 1));
	}

	//땅공격 이펙트
	CResourceManager::GetInst()->CreateAnimationSequence2D("GroundHitEffect", "GroundHitEffect", L"0_hollow/effect/GroundHitEffect.png");

	for (int j = 0; j < 4; j++)
	{
		CResourceManager::GetInst()->AddAnimationSequence2DFrame("GroundHitEffect", Vector2(132.f + 1024.f * j, 0), Vector2(760.f, 256.f));
	}
}



void CTestScene::CreateParticle()
{
	//오렌지
	m_Scene->GetResource()->CreateParticle("Orange");
	CParticle* Particle = m_Scene->GetResource()->FindParticle("Orange");

	CMaterial* Material = m_Scene->GetResource()->FindMaterial("Orange");

	Particle->SetMaterial(Material);
	Particle->SetSpawnCountMax(50);
	Particle->SetLifeTimeMin(0.f);
	Particle->SetLifeTimeMax(1.5f);
	Particle->SetScaleMin(Vector3(50.f, 50.f, 1.f));
	Particle->SetScaleMax(Vector3(100.f, 100.f, 1.f));
	Particle->SetSpeedMin(100.f);
	Particle->SetSpeedMax(300.f);
	Particle->SetMoveDir(Vector3(0.f, 1.f, 0.f));
	Particle->SetStartMin(Vector3(-30.f, -30.f, 0.f));
	Particle->SetStartMax(Vector3(30.f, 30.f, 0.f));
	Particle->SetColorMin(Vector4(238.f/255.f, 142.f / 255.f, 66.f / 255.f, 1.f));
	Particle->SetColorMax(Vector4(238.f / 255.f, 142.f / 255.f, 66.f / 255.f, 1.f));
	Particle->SetMoveAngle(Vector3(0.f, 0.f, 360.f));
	Particle->SetGravity(false);
	Particle->SetMove(true);


	//몹 죽을 때
	m_Scene->GetResource()->CreateParticle("Deathbubble");
	CParticle* Particle1 = m_Scene->GetResource()->FindParticle("Deathbubble");

	CMaterial* Material1 = m_Scene->GetResource()->FindMaterial("Deathbubble");

	Particle1->SetMaterial(Material1);
	Particle1->SetSpawnCountMax(20);
	Particle1->SetLifeTimeMin(1.0f);
	Particle1->SetLifeTimeMax(3.5f);
	Particle1->SetScaleMin(Vector3(15.f, 15, 1.f));
	Particle1->SetScaleMax(Vector3(25, 25, 1.f));
	Particle1->SetSpeedMin(10);
	Particle1->SetSpeedMax(100);
	Particle1->SetMoveDir(Vector3(0.f, 1.f, 0.f));
	Particle1->SetStartMin(Vector3(-60.f, -60.f, 0.f));
	Particle1->SetStartMax(Vector3(60.f, 60.f, 0.f));
	Particle1->SetColorMin(Vector4(195 / 255.f, 134 / 255.f, 92 / 255.f, 1.f));
	Particle1->SetColorMax(Vector4(195 / 255.f, 134 / 255.f, 92 / 255.f, 1.f));
	Particle1->SetMoveAngle(Vector3(0.f, 0.f, 90.f));
	Particle1->SetGravity(true);
	Particle1->SetMove(true);

	//돌파편
	m_Scene->GetResource()->CreateParticle("Stone");
	CParticle* Particle2 = m_Scene->GetResource()->FindParticle("Stone");

	CMaterial* Material2 = m_Scene->GetResource()->FindMaterial("Stone");

	Particle2->SetMaterial(Material2);
	Particle2->SetSpawnCountMax(30);
	Particle2->SetLifeTimeMin(1.5f);
	Particle2->SetLifeTimeMax(2.f);
	Particle2->SetScaleMin(Vector3(25, 25, 1.f));
	Particle2->SetScaleMax(Vector3(35, 35, 1.f));
	Particle2->SetSpeedMin(5);
	Particle2->SetSpeedMax(900);
	Particle2->SetMoveDir(Vector3(0.f, 1.f, 0.f));
	Particle2->SetStartMin(Vector3(-30.f, -120.f, 0.f));
	Particle2->SetStartMax(Vector3(30.f,-120.f, 0.f));
	Particle2->SetColorMin(Vector4(24 / 255.f, 36 / 255.f, 49 / 255.f, 1.f));
	Particle2->SetColorMax(Vector4(24 / 255.f, 36 / 255.f, 49 / 255.f, 1.f));
	Particle2->SetMoveAngle(Vector3(0.f, 0.f, 90.f));
	Particle2->SetGravity(true);
	Particle2->SetMove(true);

	


	/*m_Scene->GetResource()->CreateParticle("Bubble");
	CParticle* Particle = m_Scene->GetResource()->FindParticle("Bubble");

	CMaterial* Material = m_Scene->GetResource()->FindMaterial("Bubble");

	Particle->SetMaterial(Material);
	Particle->SetSpawnCountMax(1000);
	Particle->SetLifeTimeMin(3.f);
	Particle->SetLifeTimeMax(5.f);
	Particle->SetScaleMin(Vector3(20.f, 20.f, 1.f));
	Particle->SetScaleMax(Vector3(50.f, 50.f, 1.f));
	Particle->SetSpeedMin(100.f);
	Particle->SetSpeedMax(300.f);
	Particle->SetMoveDir(Vector3(0.f, 1.f, 0.f));
	Particle->SetStartMin(Vector3(-30.f, -30.f, 0.f));
	Particle->SetStartMax(Vector3(30.f, 30.f, 0.f));
	Particle->SetColorMin(Vector4(0.2f, 0.1f, 0.8f, 1.f));
	Particle->SetColorMax(Vector4(0.2f, 0.1f, 0.8f, 1.f));
	Particle->SetMoveAngle(Vector3(0.f, 0.f, 30.f));
	Particle->SetGravity(true);
	Particle->SetMove(true);*/
}
