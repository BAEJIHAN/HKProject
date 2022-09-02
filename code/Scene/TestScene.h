#pragma once

#include "Scene/SceneMode.h"
#include "../Widget/HP.h"


class CTestScene :
    public CSceneMode
{
public:
    CTestScene();
    ~CTestScene();

private:
  //  CSharedPtr<CMainWidget> m_MainWidget;
   // CSharedPtr<CHP> HPWidget;
   

public:
    virtual bool Init();

private:

   // void CreatePlayerAnimation(const std::string& Name, const TCHAR* FileName, int FrameCount);

    void CreateMaterial();
    void CreateAnimationSequence();
    void CreateParticle();
    CSharedPtr<class CSound> m_Sound;

   
public:
  /*  CSharedPtr<CHP> GetHPWidget()
    {       
        return HPWidget;       
    }*/


};

