#include "HP.h"
#include "Engine.h"
#include "Scene/SceneManager.h"

CHP::CHP()
{
    time = 0;
    flag = 0;
    for (int i = 0; i < 5; i++)
    {
        PieceDie[i] = false;
    }
    
}

CHP::CHP(const CHP& window) :
    CWidgetWindow(window)
{
  
    m_HP = FindWidget<CImage>("PHP");
}

CHP::~CHP()
{
}

void CHP::Start()
{
}

bool CHP::Init()
{
    if (!CWidgetWindow::Init())
        return false;

    SetSize(1280.f, 720.f);

 
    m_HP = CreateWidget<CImage>("PHP");

   

    m_HP->SetTexture("PHP", TEXT("0_hollow/ui/HP.png"));
    m_HP->SetSize(226, 143);
    m_HP->SetPos(30, 550);
    
 /*   Piece = CreateWidget<CImage>("PHP");

    Piece->SetSize(76, 128);
    Piece->SetPos(150, 580);
 
 

    Piece->SetTexture("pieceIdle", TEXT("0_hollow/ui/hppieceIdle.png"));
    for (int j = 0; j < 6; j++)
    {
        Piece->AddFrameData(Vector2(64 + 128 * j, 36), Vector2(76, 128));
    }
*/
    for (int i = 0; i < 5; i++)
    {
        Piece[i] = CreateWidget<CImage>("PHP1");

        Piece[i]->SetSize(76, 128);

        Piece[i]->SetPos(Vector2(150.f + i * 65.f, 550.f));

        Piece[i]->SetTexture("pieceIdle", TEXT("0_hollow/ui/hppieceIdle.png"));
        for (int j = 0; j < 6; j++)
        {
            Piece[i]->AddFrameData(Vector2(64.f + 128.f * j, 36.f), Vector2(76.f, 128.f));
        }
    }

    Text = CreateWidget<CText>("text");

    Text->SetText(TEXT(""));
    Text->SetPos(900, 80.f);
    Text->SetSize(300.f, 40.f);
    Text->SetFontSize(50.f);
    Text->SetZOrder(1);
    Text->SetColor(1.f, 1.f, 1.f);
    //m_Button1Text->SetOpacity(0.5f);
    Text->SetAlignH(TEXT_ALIGN_H::Center);
    Text->SetShadowEnable(true);
    Text->SetShadowOffset(2.f, 2.f);

    Text->SetOpacity(1.0f);

    //Text->SetText(TEXT(""));
   
   


   

    //Piece->SetTexture("piecedie", TEXT("0_hollow/ui/hppiecedie.png"));
    //Piece->SetTexture("pieceIdle", TEXT("0_hollow/ui/hppieceIdle.png"));

   // Piece->Enable(false);
    return true;
}

void CHP::Update(float DeltaTime)
{
   
    CWidgetWindow::Update(DeltaTime);
   
}

void CHP::PostUpdate(float DeltaTime)
{
    CWidgetWindow::PostUpdate(DeltaTime);

   /* time += DeltaTime;
    if (time >= 2 && flag == 0)
    {
        flag++;
        Piece[4]->SetTexture("piecedie", TEXT("0_hollow/ui/hppiecedie.png"));
        for (int i = 0; i < 5; i++)
        {
            Piece[4]->AddFrameData(Vector2(40 + 128 * i, 71), Vector2(76, 128));
        }
        Piece[4]->SetLoop(false);
    }*/
}

void CHP::Render()
{
    CWidgetWindow::Render();
}

CHP* CHP::Clone()
{
    return new CHP(*this);
}

void CHP::SetDie(int index)
{ 
    Piece[index]->SetTexture("piecedie", TEXT("0_hollow/ui/hppiecedie.png"));
    for (int i = 0; i < 5; i++)
    {
        Piece[index]->AddFrameData(Vector2(40.f+ 128.f * i, 71.f), Vector2(76.f, 128.f));
    }
    Piece[index]->SetLoop(false);
}

void CHP::SetText(const TCHAR* t)
{
    Text->SetText(t);
}

void CHP::SetTextOpacity(float f)
{
    Text->SetOpacity(f);
}


