#include "StartSceneUI.h"
#include "UI/UIButton.h"
#include "UI/UIText.h"
#include "UI/UIProgressBar.h"
#include "UI/UINumber.h"
#include "UI/UIImage.h"
#include "UI/UIDamageNumber.h"
#include "../Scene/LoadingSceneInfo.h"
#include "Scene/SceneManager.h"
#include "Scene/Scene.h"
#include "Engine.h"
#include "../GameObject/Player2D.h"
#include "Resource/Texture/Texture.h"
#include "Scene/CameraManager.h"
#include "Component/CameraComponent.h"
#include "UI/UIShopText.h"
#include "../GameObject/HonTail.h"

CStartSceneUI::CStartSceneUI() :
    DamageNumberID(0)
{
    m_WindowTypeName = "StartSceneUI";
}

CStartSceneUI::CStartSceneUI(const CStartSceneUI& Window) :
    CUIWindow(Window)
{
    m_ExpProgressBar = FindWidget<CUIProgressBar>("ExpProgressBar");
    m_HpProgressBar = FindWidget<CUIProgressBar>("HpProgressBar");
    m_MpProgressBar = FindWidget<CUIProgressBar>("MpProgressBar");
    m_StatusImage = FindWidget<CUIImage>("UIStatus");
    m_StatusBackImage = FindWidget<CUIImage>("UIStatusBack");
    m_LevelImage = FindWidget<CUIImage>("UILevel");
    m_LevelNumber = FindWidget<CUINumber>("LevelNumber");
    m_ExpNumber = FindWidget<CUINumber>("ExpNumber");
    m_ExpValueNumber = FindWidget<CUINumber>("ExpValueNumber");
    m_HpNumber = FindWidget<CUINumber>("HpNumber");
    m_MaxHpNumber = FindWidget<CUINumber>("MaxHpNumber");
    m_MpNumber = FindWidget<CUINumber>("MpNumber");
    m_MaxMpNumber = FindWidget<CUINumber>("MaxMpNumber");
    m_LevelUpImage = FindWidget<CUIImage>("LevelUpImage");
    m_LevelText = FindWidget<CUIText>("LevelText");
    m_LevelUpText = FindWidget<CUIText>("LevelUpText");
    m_QuickSlotBackImage = FindWidget<CUIImage>("QuickSlotBack");
    m_QuickSlotImage = FindWidget<CUIImage>("QuickSlotImage");
    m_QuickSlotLeftImage = FindWidget<CUIImage>("QuickSlotLeft"); 
    m_AttackKeyImage = FindWidget<CUIImage>("AttackKeyImage");
    m_CtrlKeyImage = FindWidget<CUIImage>("CtrlKeyImage");
    m_JumpKeyImage = FindWidget<CUIImage>("JumpKeyImage");
    m_AltKeyImage = FindWidget<CUIImage>("AltKeyImage");
    m_RedPotionKeyImage = FindWidget<CUIImage>("RedPotionKeyImage");
    m_DelKeyImage = FindWidget<CUIImage>("DelKeyImage");
    m_BluePotionKeyImage = FindWidget<CUIImage>("BluePotionKeyImage");
    m_EndKeyImage = FindWidget<CUIImage>("EndKeyImage");
    m_RedPotionKeyNumber = FindWidget<CUINumber>("RedPotionNumber");
    m_BluePotionKeyNumber = FindWidget<CUINumber>("BluePotionNumber");
    m_BaseSkillKeyImage = FindWidget<CUIImage>("BaseSkillImage");
    m_ShiftKeyImage = FindWidget<CUIImage>("ShiftKeyImage");
    m_HighSkillKeyImage = FindWidget<CUIImage>("HighSkillImage");
    m_SpaceKeyImage = FindWidget<CUIImage>("SpaceKeyImage");
    m_ExpText = FindWidget<CUIText>("ExpText");
    m_AddExpNumber = FindWidget<CUINumber>("ExpAddNumber");
    m_PdnKeyImage = FindWidget<CUIImage>("PdnKeyImage");
    m_FlashJumpKeyImage = FindWidget<CUIImage>("FlashJumpImage");
}

CStartSceneUI::~CStartSceneUI()
{
}

void CStartSceneUI::Start()
{
    CUIWindow::Start();    
    DamageNumberID = 0;
}
bool CStartSceneUI::Init()
{
    CUIWindow::Init();   

    // 경험치바
    m_ExpProgressBar = CreateWidget<CUIProgressBar>("ExpProgressBar");
    m_ExpProgressBar->SetBarDir(EProgressBarDir::RightToLeft);
    m_ExpProgressBar->SetPos(0.f, 0.f);
    m_ExpProgressBar->SetSize(1280.f, 10.f);

    m_ExpProgressBar->SetTexture(EProgressBarTextureType::Back, "ExpBarBack", TEXT("ExpBarBack.png"));
    m_ExpProgressBar->SetTexture(EProgressBarTextureType::Bar, "ExpBar", TEXT("ExpBar.png"));

    m_ExpProgressBar->SetProgressBarMin(0.f);
    m_ExpProgressBar->SetProgressBarMax(100.f);
    m_ExpProgressBar->SetValue(40.f);

    m_ExpText = CreateWidget<CUIText>("ExpText");
    m_ExpText->SetPos(1050.f, 35.f);
    m_ExpText->SetSize(200.f, 100.f);
    m_ExpText->SetText(TEXT("경험치가 올랐습니다. + "));
    m_ExpText->SetFontSize(15.f);
    m_ExpText->SetColor(255, 255, 0);
    m_ExpText->SetEnable(false);

  
    m_AddExpNumber = CreateWidget<CUINumber>("ExpAddNumber");

    std::vector<const TCHAR*>	ExpvecFileNames;

    for (int i = 0; i < 10; ++i)
    {
        TCHAR* FileName = new TCHAR[MAX_PATH];

        memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);

        wsprintf(FileName, TEXT("AddExpNumber/AddExpNumber%d.png"), i);

        ExpvecFileNames.push_back(FileName);
    }

    m_AddExpNumber->SetTexture("ExpAddNumber", ExpvecFileNames);

    m_AddExpNumber->SetPos(1200.f, 118.f);
    m_AddExpNumber->SetSize(13.f, 17.f);
    m_AddExpNumber->SetNumber(99);
    m_AddExpNumber->SetEnable(false);

    for (int i = 0; i < 10; ++i)
    {
        m_AddExpNumber->AddFrameData(Vector2(0.f, 0.f), Vector2(13.f, 17.f));
    }

    size_t ExpSize = ExpvecFileNames.size();

    for (size_t i = 0; i < ExpSize; ++i)
    {
        SAFE_DELETE(ExpvecFileNames[i]);
    }



    //스테이터스 이미지 

    m_StatusBackImage = CreateWidget<CUIImage>("UIStatusBack");
    m_StatusBackImage->SetTexture("StatusBack", TEXT("StatusBack.png"));
    m_StatusBackImage->SetPos(460.f, 20.f);
    m_StatusBackImage->SetSize(198.f, 37.f);

    m_StatusImage = CreateWidget<CUIImage>("UIStatus");
    m_StatusImage->SetTexture("Status", TEXT("Status.png"));
    m_StatusImage->SetPos(460.f, 10.f);
    m_StatusImage->SetSize(204.f, 70.f);

    //레벨 이미지 

    m_LevelImage = CreateWidget<CUIImage>("UILevel");
    m_LevelImage->SetTexture("Level", TEXT("MapleLevel.png"));
    m_LevelImage->SetPos(490.f, 63.f);
    m_LevelImage->SetSize(15.f, 10.f);

    //체력바

    m_HpProgressBar = CreateWidget<CUIProgressBar>("HpProgressBar");
    m_HpProgressBar->SetBarDir(EProgressBarDir::RightToLeft);
    m_HpProgressBar->SetPos(486.f, 40.f);
    m_HpProgressBar->SetSize(171.f, 10.f);

    m_HpProgressBar->SetImageTint(EProgressBarTextureType::Back, 255, 255, 255, 50);
    m_HpProgressBar->SetTexture(EProgressBarTextureType::Bar, "HpBarBack", TEXT("MapleHpBar.png"));

    m_HpProgressBar->SetProgressBarMin(0.f);
    m_HpProgressBar->SetProgressBarMax(100.f);
    m_HpProgressBar->SetValue(80.f);


    //마나바

    m_MpProgressBar = CreateWidget<CUIProgressBar>("MpProgressBar");
    m_MpProgressBar->SetBarDir(EProgressBarDir::RightToLeft);
    m_MpProgressBar->SetPos(486.f, 25.f);
    m_MpProgressBar->SetSize(171.f, 10.f);

    m_MpProgressBar->SetImageTint(EProgressBarTextureType::Back, 255, 255, 255, 50);
    m_MpProgressBar->SetTexture(EProgressBarTextureType::Bar, "MpBarBack", TEXT("MapleMpBar.png"));

    m_MpProgressBar->SetProgressBarMin(0.f);
    m_MpProgressBar->SetProgressBarMax(100.f);
    m_MpProgressBar->SetValue(100.f);

    /////////////////////////////////////////////////////////레벨 넘버 

    m_LevelNumber = CreateWidget<CUINumber>("LevelNumber");

    std::vector<const TCHAR*>	vecFileNames;

    for (int i = 0; i < 10; ++i)
    {
        TCHAR* FileName = new TCHAR[MAX_PATH];

        memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);

        wsprintf(FileName, TEXT("Level_Number/Level_Number%d.png"), i);

        vecFileNames.push_back(FileName);
    }

    m_LevelNumber->SetTexture("LevelNumber", vecFileNames);

    m_LevelNumber->SetPos(510.f, 63.f);
    m_LevelNumber->SetSize(7.f, 10.f);
    m_LevelNumber->SetNumber(99);

    for (int i = 0; i < 10; ++i)
    {
        m_LevelNumber->AddFrameData(Vector2(0.f, 0.f), Vector2(7.f, 10.f));
    }

    size_t Size = vecFileNames.size();

    for (size_t i = 0; i < Size; ++i)
    {
        SAFE_DELETE(vecFileNames[i]);
    }

    /////////////////////////////////////////////// 체력 , MP , 경험치 넘버 

    vecFileNames.clear();

    for (int i = 0; i < 10; ++i)
    {
        TCHAR* FileName = new TCHAR[MAX_PATH];

        memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);

        wsprintf(FileName, TEXT("HPMPNumber/HPMPNumber%d.png"), i);

        vecFileNames.push_back(FileName);
    }

    m_ExpNumber = CreateWidget<CUINumber>("ExpNumber");
    m_ExpNumber->SetPos(536.f, 1.3f);
    m_ExpNumber->SetSize(7.f, 9.f);
    m_ExpNumber->SetNumber(111);
    m_ExpNumber->SetTexture("HPMpNumber", vecFileNames);

    m_ExpValueNumber = CreateWidget<CUINumber>("ExpValueNumber");
    m_ExpValueNumber->SetPos(596.f, 1.3f);
    m_ExpValueNumber->SetSize(7.f, 9.f);
    m_ExpValueNumber->SetNumber(111);
    m_ExpValueNumber->SetTexture("HPMpNumber", vecFileNames);

    CUIImage* Image = CreateWidget<CUIImage>("ExpLeft");
    Image->SetPos(583.f, 0.7f);
    Image->SetSize(7.f, 9.f);
    Image->SetTexture("ExpLeft", TEXT("ExpBarLeft.png"));

    Image = CreateWidget<CUIImage>("ExpRight");
    Image->SetPos(630.f, 0.7f);
    Image->SetSize(7.f, 9.f);
    Image->SetTexture("ExpRight", TEXT("ExpBarRight.png"));

    Image = CreateWidget<CUIImage>("ExpPer");
    Image->SetPos(615.f, 1.3f);
    Image->SetSize(9.f, 9.f);
    Image->SetTexture("ExpPer", TEXT("ExpBarPer.png"));

    m_HpNumber = CreateWidget<CUINumber>("HpNumber");
    m_HpNumber->SetPos(530.f, 41.f);
    m_HpNumber->SetSize(7.f, 9.f);
    m_HpNumber->SetNumber(100);
    m_HpNumber->SetTexture("HPMpNumber", vecFileNames);

    Image = CreateWidget<CUIImage>("HpWall");
    Image->SetPos(565.f, 40.f);
    Image->SetSize(6.f, 10.f);
    Image->SetTexture("HpWall", TEXT("HpMpWall.png"));

    m_MaxHpNumber = CreateWidget<CUINumber>("MaxHpNumber");
    m_MaxHpNumber->SetPos(575.f, 41.f);
    m_MaxHpNumber->SetSize(7.f, 9.f);
    m_MaxHpNumber->SetNumber(200);
    m_MaxHpNumber->SetTexture("HPMpNumber", vecFileNames);

    m_MpNumber = CreateWidget<CUINumber>("MpNumber");
    m_MpNumber->SetPos(530.f, 25.f);
    m_MpNumber->SetSize(7.f, 9.f);
    m_MpNumber->SetNumber(100);
    m_MpNumber->SetTexture("HPMpNumber", vecFileNames);

    Image = CreateWidget<CUIImage>("MpWall");
    Image->SetPos(565.f, 25.f);
    Image->SetSize(6.f, 10.f);
    Image->SetTexture("MpWall", TEXT("HpMpWall.png"));

    m_MaxMpNumber = CreateWidget<CUINumber>("MaxMpNumber");
    m_MaxMpNumber->SetPos(575.f, 25.f);
    m_MaxMpNumber->SetSize(7.f, 9.f);
    m_MaxMpNumber->SetNumber(200);
    m_MaxMpNumber->SetTexture("HPMpNumber", vecFileNames);

    for (int i = 0; i < 10; ++i)
    {
        m_ExpNumber->AddFrameData(Vector2(0.f, 0.f), Vector2(7.f, 9.f));
        m_ExpValueNumber->AddFrameData(Vector2(0.f, 0.f), Vector2(7.f, 9.f));
        m_HpNumber->AddFrameData(Vector2(0.f, 0.f), Vector2(7.f, 9.f));
        m_MaxHpNumber->AddFrameData(Vector2(0.f, 0.f), Vector2(7.f, 9.f));
        m_MpNumber->AddFrameData(Vector2(0.f, 0.f), Vector2(7.f, 9.f));
        m_MaxMpNumber->AddFrameData(Vector2(0.f, 0.f), Vector2(7.f, 9.f));
    }

    Size = vecFileNames.size();

    for (size_t i = 0; i < Size; ++i)
    {
        SAFE_DELETE(vecFileNames[i]);
    }

    /////////////////////////////////////////UI 버튼 

    CUIButton* Button1 = CreateWidget<CUIButton>("Button1");

    Button1->SetSize(34.f, 37.f);
    Button1->SetPos(670.f, 10.f);
    Button1->SetTexture(EButtonState::Normal, "UIButton1", TEXT("UIButton.png"));
    Button1->SetTexture(EButtonState::Hovered, "UIButton1", TEXT("UIButtonHovered.png"));
    Button1->SetTexture(EButtonState::Click, "UIButton1", TEXT("UIButton.png"));

    Button1 = CreateWidget<CUIButton>("Button2");

    Button1->SetSize(34.f, 37.f);
    Button1->SetPos(707.f, 10.f);
    Button1->SetTexture(EButtonState::Normal, "UIButton2", TEXT("UIButton2.png"));
    Button1->SetTexture(EButtonState::Hovered, "UIButton2", TEXT("UIButton2Hov.png"));
    Button1->SetTexture(EButtonState::Click, "UIButton2", TEXT("UIButton2.png"));

    Button1 = CreateWidget<CUIButton>("Button3");

    Button1->SetSize(34.f, 37.f);
    Button1->SetPos(744.f, 10.f);
    Button1->SetTexture(EButtonState::Normal, "UIButton3", TEXT("UIButton3.png"));
    Button1->SetTexture(EButtonState::Hovered, "UIButton3", TEXT("UIButton3Hov.png"));
    Button1->SetTexture(EButtonState::Click, "UIButton3", TEXT("UIButton3.png"));

    Button1 = CreateWidget<CUIButton>("Button4");

    Button1->SetSize(34.f, 37.f);
    Button1->SetPos(781.f, 10.f);
    Button1->SetTexture(EButtonState::Normal, "UIButton4", TEXT("UIButton4.png"));
    Button1->SetTexture(EButtonState::Hovered, "UIButton4", TEXT("UIButton4Hov.png"));
    Button1->SetTexture(EButtonState::Click, "UIButton4", TEXT("UIButton4.png"));

    Button1 = CreateWidget<CUIButton>("Button5");

    Button1->SetSize(34.f, 37.f);
    Button1->SetPos(818.f, 10.f);
    Button1->SetTexture(EButtonState::Normal, "UIButton5", TEXT("UIButton5.png"));
    Button1->SetTexture(EButtonState::Hovered, "UIButton5", TEXT("UIButton5Hov.png"));
    Button1->SetTexture(EButtonState::Click, "UIButton5", TEXT("UIButton5.png"));

    Button1 = CreateWidget<CUIButton>("Button6");

    Button1->SetSize(34.f, 37.f);
    Button1->SetPos(855.f, 10.f);
    Button1->SetTexture(EButtonState::Normal, "UIButton6", TEXT("UIButton6.png"));
    Button1->SetTexture(EButtonState::Hovered, "UIButton6", TEXT("UIButton6Hov.png"));
    Button1->SetTexture(EButtonState::Click, "UIButton6", TEXT("UIButton6.png"));


    //// 퀵슬롯
    m_QuickSlotBackImage = CreateWidget<CUIImage>("QuickSlotBack");
    m_QuickSlotBackImage->SetPos(910.f, 15.f);
    m_QuickSlotBackImage->SetSize(349.f, 67.f);
    m_QuickSlotBackImage->SetTexture("QuickBack", TEXT("KeyBack.png"));

    m_QuickSlotImage = CreateWidget<CUIImage>("QuickSlotImage");
    m_QuickSlotImage->SetPos(910.f, 15.f);
    m_QuickSlotImage->SetSize(351.f, 73.f);
    m_QuickSlotImage->SetTexture("QuickImage", TEXT("KeyCover.png"));

    m_QuickSlotLeftImage = CreateWidget<CUIImage>("QuickSlotLeft");
    m_QuickSlotLeftImage->SetPos(900.f, 15.f);
    m_QuickSlotLeftImage->SetSize(13.f, 71.f);
    m_QuickSlotLeftImage->SetTexture("QuickLeft", TEXT("KeyTitle.png"));




    vecFileNames.clear();

    for (int i = 0; i < 21; ++i)
    {
        TCHAR* FileName = new TCHAR[MAX_PATH];

        memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);

        wsprintf(FileName, TEXT("LevelUpEffect/LevelUpEffect%d.png"), i);

        vecFileNames.push_back(FileName);
    }

    m_LevelUpImage = CreateWidget<CUIImage>("LevelUpImage");
    m_LevelUpImage->SetTexture("LevelUpImage", vecFileNames);
    m_LevelUpImage->SetPlayScale(200.f);

    CTexture* Texture = m_LevelUpImage->GetTexture();

    for (int i = 0; i < 21; ++i)
    {
        float Width = (float)(Texture->GetWidth(i));
        float Height = (float)(Texture->GetHeight(i));

        m_LevelUpImage->AddFrameData(Vector2(0.f, 0.f), Vector2(Width, Height));

    }

    Size = vecFileNames.size();

    for (size_t i = 0; i < Size; ++i)
    {
        SAFE_DELETE(vecFileNames[i]);
    }


    m_LevelUpText = CreateWidget<CUIText>("LevelUpText");

    m_LevelText = CreateWidget<CUIText>("LevelText");



    vecFileNames.clear();   

    InitKey();

    DamageNumberID = 0;

    return true;
}

void CStartSceneUI::Update(float DeltaTime)
{
    CUIWindow::Update(DeltaTime);

    //플레이어 정보 업데이트
    UpdatePlayerInfo();
   
    //혼테일 업데이트
    if (m_HonTailProgressBar)
        UpdateHonTailInfo();    

    if (m_LevelUpFunc)
    {
        LevelUpEffect();
        m_LevelUpFunc = false;
    }

   int FrameCount =  m_LevelUpImage->GetFrame();

   if (FrameCount == 20)
   {
       m_LevelUpImage->SetEnable(false);
       m_LevelText->SetEnable(false);
       m_LevelUpText->SetEnable(false);
   }

   if (!m_MiniMapStart)
   {
       MiniMapStart();
       m_MiniMapStart = true;
   }

   if (m_Scene)
   {
       if (m_Scene->GetName() == "Henesis")
       {
           Vector2 PlayerPos = m_Player->GetWorldPos();

           float MiniMapPlayerPosX = PlayerPos.x / 15.8f + 18.f;
           float MiniMapPlayerPosY = PlayerPos.y / 20.f + 568.f;

           m_MinimapPlayerIcon->SetPos(MiniMapPlayerPosX, MiniMapPlayerPosY);
       }

       if (m_Scene->GetName() == "HonTailFront")
       {
           Vector2 PlayerPos = m_Player->GetWorldPos();

           float MiniMapPlayerPosX = PlayerPos.x / 14.14f + 20.f;
           float MiniMapPlayerPosY = PlayerPos.y / 15.8f + 586.f;

           m_MinimapPlayerIcon->SetPos(MiniMapPlayerPosX, MiniMapPlayerPosY);
       }

       if (m_Scene->GetName() == "HonTail")
       {
           Vector2 PlayerPos = m_Player->GetWorldPos();

           float MiniMapPlayerPosX = PlayerPos.x / 14.91f + 25.f;
           float MiniMapPlayerPosY = PlayerPos.y / 16.3f + 590.f;

           m_MinimapPlayerIcon->SetPos(MiniMapPlayerPosX, MiniMapPlayerPosY);
       }

       if (m_Scene->GetName() == "Basic")
       {
           Vector2 PlayerPos = m_Player->GetWorldPos();

           float MiniMapPlayerPosX = PlayerPos.x / 14.5f + 25.f;
           float MiniMapPlayerPosY = PlayerPos.y / 13.49f + 550.f;

           m_MinimapPlayerIcon->SetPos(MiniMapPlayerPosX, MiniMapPlayerPosY);
       }

   }
   
}

void CStartSceneUI::PostUpdate(float DeltaTime)
{
    CUIWindow::PostUpdate(DeltaTime);

    if (m_ExpOn)
    {
        m_ExpTime += DeltaTime;

        if (m_ExpTime > 1.f)
        {
            m_ExpOn = false;
            m_ExpTime = 0.f;
            m_ExpText->SetEnable(false);
            m_AddExpNumber->SetEnable(false);
        }
    }

}

void CStartSceneUI::Render()
{
    CUIWindow::Render();
}

CStartSceneUI* CStartSceneUI::Clone()
{
    return new CStartSceneUI(*this);
}

void CStartSceneUI::Save(FILE* File)
{
    CUIWindow::Save(File);    
}

void CStartSceneUI::Load(FILE* File)
{
    CUIWindow::Load(File);

    m_ExpProgressBar = FindWidget<CUIProgressBar>("ExpProgressBar");
    m_HpProgressBar = FindWidget<CUIProgressBar>("HpProgressBar");
    m_MpProgressBar = FindWidget<CUIProgressBar>("MpProgressBar");
    m_StatusImage = FindWidget<CUIImage>("UIStatus");
    m_StatusBackImage = FindWidget<CUIImage>("UIStatusBack");
    m_LevelImage = FindWidget<CUIImage>("UILevel");
    m_LevelNumber = FindWidget<CUINumber>("LevelNumber");
    m_ExpNumber = FindWidget<CUINumber>("ExpNumber");
    m_ExpValueNumber = FindWidget<CUINumber>("ExpValueNumber");
    m_HpNumber = FindWidget<CUINumber>("HpNumber");
    m_MaxHpNumber = FindWidget<CUINumber>("MaxHpNumber");
    m_MpNumber = FindWidget<CUINumber>("MpNumber");
    m_MaxMpNumber = FindWidget<CUINumber>("MaxMpNumber");
    m_LevelUpImage = FindWidget<CUIImage>("LevelUpImage");
    m_LevelText = FindWidget<CUIText>("LevelText");
    m_LevelUpText = FindWidget<CUIText>("LevelUpText");    
    m_QuickSlotBackImage = FindWidget<CUIImage>("QuickSlotBack");
    m_QuickSlotImage = FindWidget<CUIImage>("QuickSlotImage");
    m_QuickSlotLeftImage = FindWidget<CUIImage>("QuickSlotLeft");
    m_AttackKeyImage = FindWidget<CUIImage>("AttackKeyImage");
    m_CtrlKeyImage = FindWidget<CUIImage>("CtrlKeyImage");
    m_JumpKeyImage = FindWidget<CUIImage>("JumpKeyImage");
    m_AltKeyImage = FindWidget<CUIImage>("AltKeyImage");
    m_RedPotionKeyImage = FindWidget<CUIImage>("RedPotionKeyImage");
    m_DelKeyImage = FindWidget<CUIImage>("DelKeyImage");
    m_BluePotionKeyImage = FindWidget<CUIImage>("BluePotionKeyImage");
    m_EndKeyImage = FindWidget<CUIImage>("EndKeyImage");
    m_RedPotionKeyNumber = FindWidget<CUINumber>("RedPotionNumber");
    m_BluePotionKeyNumber = FindWidget<CUINumber>("BluePotionNumber");
    m_BaseSkillKeyImage = FindWidget<CUIImage>("BaseSkillImage");
    m_ShiftKeyImage = FindWidget<CUIImage>("ShiftKeyImage");
    m_HighSkillKeyImage = FindWidget<CUIImage>("HighSkillImage");
    m_SpaceKeyImage = FindWidget<CUIImage>("SpaceKeyImage");
    m_ExpText = FindWidget<CUIText>("ExpText");
    m_AddExpNumber = FindWidget<CUINumber>("ExpAddNumber");
    m_PdnKeyImage = FindWidget<CUIImage>("PdnKeyImage");
    m_FlashJumpKeyImage = FindWidget<CUIImage>("FlashJumpImage");

    DamageNumberID = 0;

}

void CStartSceneUI::SetHonTail(CHonTail* HonTail)
{
    m_HonTail = HonTail;

    m_HonTailProgressBar = CreateWidget<CUIProgressBar>("HonTailProgressBar");
    m_HonTailProgressBar->SetBarDir(EProgressBarDir::RightToLeft);
    m_HonTailProgressBar->SetPos(260.f, 660.f);
    m_HonTailProgressBar->SetSize(1000.f, 40.f);

    m_HonTailProgressBar->SetTexture(EProgressBarTextureType::Back, "HonTailBarBack", TEXT("HonTailHpBar.png"));
    m_HonTailProgressBar->SetTexture(EProgressBarTextureType::Bar, "HonTailBar", TEXT("HonTailHpBarBack.png"));    

    CUIImage* HonTailIcon = CreateWidget<CUIImage>("HonTailIcon");
    HonTailIcon->SetPos(217.f, 670.f);
    HonTailIcon->SetSize(35.f, 35.f);
    HonTailIcon->SetTexture("HonTailIcon", TEXT("HonTailIcon.png"));


}

void CStartSceneUI::SceneChange()
{
    CSceneManager::GetInst()->CreateNextScene(true);

    CSceneManager::GetInst()->CreateSceneInfo<CLoadingSceneInfo>(false);
}

void CStartSceneUI::LevelUpEffect()
{
    m_LevelUpImage->SetEnable(true);
    m_LevelText->SetEnable(true);
    m_LevelUpText->SetEnable(true);

    m_LevelUpImage->SetFrame(0);

    CTexture* Texture = m_LevelUpImage->GetTexture();
    int FrameCount = m_LevelUpImage->GetFrame();

    float Width = (float)Texture->GetWidth(FrameCount);
    float Height = (float)Texture->GetHeight(FrameCount);
    m_LevelUpImage->SetSize(Width, Height);
    m_LevelUpImage->SetPos(500.f, 500.f);

   
    m_LevelUpText->SetPos(620.f, 500.f);
    m_LevelUpText->SetSize(100.f, 100.f);
    
    int LevelNumber = m_Player->GetLevel(); 
   
    if (LevelNumber < 10)
    {
        char LevelChar = (char)(LevelNumber + 48);
        char charBuff[256] = { "레벨" };
        charBuff[4] = LevelChar;
        TCHAR LevelText[256] = {};
        MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, (LPCCH)charBuff, (int)strlen(charBuff), LevelText, 256);

        m_LevelUpText->SetText(LevelText);
        m_LevelUpText->SetFontSize(30.f);
    }

    if (LevelNumber >= 10)
    {
        char Level1 = (char)49;
        char LevelChar = (char)(LevelNumber  + 38);
        char charBuff[256] = { "레벨" };
        charBuff[4] = Level1;
        charBuff[5] = LevelChar;
        TCHAR LevelText[256] = {};
        MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, (LPCCH)charBuff, (int)strlen(charBuff), LevelText, 256);

        m_LevelUpText->SetText(LevelText);
        m_LevelUpText->SetFontSize(30.f);
    }

    if (LevelNumber >= 20)
    {
        char Level1 = (char)50;
        char LevelChar = (char)(LevelNumber + 28);
        char charBuff[256] = { "레벨" };
        charBuff[4] = Level1;
        charBuff[5] = LevelChar;
        TCHAR LevelText[256] = {};
        MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, (LPCCH)charBuff, (int)strlen(charBuff), LevelText, 256);

        m_LevelUpText->SetText(LevelText);
        m_LevelUpText->SetFontSize(30.f);
    }

 
    m_LevelText->SetPos(600.f, 450.f);
    m_LevelText->SetSize(200.f, 100.f);
    m_LevelText->SetText(TEXT("레벨이 올랐습니다!"));
    m_LevelText->SetFontSize(15.f);
    m_LevelText->SetColor(255, 205, 85);


    
}

void CStartSceneUI::SetDamageNumber(Vector2 Pos, int Damage)
{

    ++DamageNumberID;

    std::string Number = std::to_string(DamageNumberID);

    DamageID = Number;

    std::vector<const TCHAR*>	vecFileNames;

    for (int i = 0; i < 10; ++i)
    {
        TCHAR* FileName = new TCHAR[MAX_PATH];

        memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);

        wsprintf(FileName, TEXT("Damage_Number/Damage_Number%d.png"), i);

        vecFileNames.push_back(FileName);
    }

    CUIDamageNumber* DamageNumber = CreateWidget<CUIDamageNumber>(DamageID);
 
    DamageNumber->SetTexture("DamageNumber", vecFileNames);
    DamageNumber->SetSize(37.f, 38.f);

    for (int i = 0; i < 10; ++i)
    {
        DamageNumber->AddFrameData(Vector2(0.f, 0.f), Vector2(37.f, 38.f));
    }

    size_t Size = vecFileNames.size();

    for (size_t i = 0; i < Size; ++i)
    {
        SAFE_DELETE(vecFileNames[i]);
    }  

    DamageNumber->SetUIPos(Vector2(Pos.x -50.f, Pos.y - 50.f));
    DamageNumber->SetNumber(Damage);

}

void CStartSceneUI::SetMonsterDamageNumber(Vector2 Pos, int Damage, int MpDamage)
{
    ++DamageNumberID;

    std::string Number = std::to_string(DamageNumberID);

    DamageID = Number;

    std::vector<const TCHAR*>	vecFileNames;

    for (int i = 0; i < 10; ++i)
    {
        TCHAR* FileName = new TCHAR[MAX_PATH];

        memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);

        wsprintf(FileName, TEXT("PlayerHitDamageNumber/PlayerHitDamageNumber%d.png"), i);

        vecFileNames.push_back(FileName);
    }

    CUIDamageNumber* DamageNumber = CreateWidget<CUIDamageNumber>(DamageID);

    DamageNumber->SetTexture("PlayerHitDamageNumber", vecFileNames);
    DamageNumber->SetSize(31.f, 33.f);

    for (int i = 0; i < 10; ++i)
    {
        DamageNumber->AddFrameData(Vector2(0.f, 0.f), Vector2(37.f, 38.f));
    }

    size_t Size = vecFileNames.size();

    for (size_t i = 0; i < Size; ++i)
    {
        SAFE_DELETE(vecFileNames[i]);
    }

    DamageNumber->SetUIPos(Vector2(Pos.x - 50.f, Pos.y - 50.f));
    DamageNumber->SetNumber(Damage);
}

void CStartSceneUI::SetCriticalDamageNumber(Vector2 Pos, int Damage)
{
    ++DamageNumberID;

    std::string Number = std::to_string(DamageNumberID);

    DamageID = Number;

    std::vector<const TCHAR*>	vecFileNames;

    for (int i = 0; i < 10; ++i)
    {
        TCHAR* FileName = new TCHAR[MAX_PATH];

        memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);

        wsprintf(FileName, TEXT("CriticalDamageNumber/CriticalDamageNumber%d.png"), i);

        vecFileNames.push_back(FileName);
    }

    CUIDamageNumber* DamageNumber = CreateWidget<CUIDamageNumber>(DamageID);

    DamageNumber->SetTexture("CriticalDamageNumber", vecFileNames);
    DamageNumber->SetSize(37.f, 38.f);

    for (int i = 0; i < 10; ++i)
    {
        DamageNumber->AddFrameData(Vector2(0.f, 0.f), Vector2(37.f, 38.f));
    }

    size_t Size = vecFileNames.size();

    for (size_t i = 0; i < Size; ++i)
    {
        SAFE_DELETE(vecFileNames[i]);
    }

    DamageNumber->SetUIPos(Vector2(Pos.x - 50.f, Pos.y - 50.f));
    DamageNumber->SetNumber(Damage);
}

void CStartSceneUI::UpdatePlayerInfo()
{
    m_Player = (CPlayer2D*)m_Scene->FindObject("Player2D");

    int Level = m_Player->GetLevel();
    int MaxHp = m_Player->GetMaxHp();
    int Hp = m_Player->GetHp();
    int MaxMp = m_Player->GetMaxMp();
    int Mp = m_Player->GetMp();
    int MaxExp = m_Player->GetMaxExp();
    int Exp = m_Player->GetExp();

    // Level Update
    m_LevelNumber->SetNumber(Level);

    // Exp Update
    m_ExpProgressBar->SetProgressBarMin(0.f);
    m_ExpProgressBar->SetProgressBarMax((float)MaxExp);
    m_ExpProgressBar->SetValue((float)Exp);
    m_ExpValueNumber->SetNumber((int)m_ExpProgressBar->GetPercent());
    m_ExpNumber->SetNumber(Exp);

    // Hp Update
    m_HpProgressBar->SetProgressBarMin(0.f);
    m_HpProgressBar->SetProgressBarMax((float)MaxHp);
    m_HpProgressBar->SetValue((float)Hp);
    m_HpNumber->SetNumber(Hp);
    m_MaxHpNumber->SetNumber(MaxHp);

    //Mp Update
    m_MpProgressBar->SetProgressBarMin(0.f);
    m_MpProgressBar->SetProgressBarMax((float)MaxMp);
    m_MpProgressBar->SetValue((float)Mp);
    m_MpNumber->SetNumber(Mp);
    m_MaxMpNumber->SetNumber(MaxMp);

    // 물약 갯수 업데이트 
    m_RedPotionKeyNumber->SetNumber(m_Player->GetHpPotionNumber());
    m_BluePotionKeyNumber->SetNumber(m_Player->GetMpPotionNumber());

    if (m_Player->GetSkill1Lock())
    {
        m_BaseSkillKeyImage->SetEnable(true);
        m_ShiftKeyImage->SetEnable(true);
        m_PdnKeyImage->SetEnable(true);
        m_FlashJumpKeyImage->SetEnable(true);
    }

    if (m_Player->GetSkill2Lock())
    {
        m_HighSkillKeyImage->SetEnable(true);
        m_SpaceKeyImage->SetEnable(true);
    }

}

void CStartSceneUI::InitKey()
{

    m_AttackKeyImage = CreateWidget<CUIImage>("AttackKeyImage");
    m_AttackKeyImage->SetPos(910.f, 18.f);
    m_AttackKeyImage->SetSize(32.f, 32.f);
    m_AttackKeyImage->SetTexture("AttackKeyImage", TEXT("KeyIcon/AttackKey.png"));

    m_CtrlKeyImage = CreateWidget<CUIImage>("CtrlKeyImage");
    m_CtrlKeyImage->SetPos(915.f, 35.f);
    m_CtrlKeyImage->SetSize(23.f, 9.f);
    m_CtrlKeyImage->SetTexture("CtrlKeyImage", TEXT("KeyIcon/CtrlKeyIcon.png"));

    m_JumpKeyImage = CreateWidget<CUIImage>("JumpKeyImage");
    m_JumpKeyImage->SetPos(948.f, 18.f);
    m_JumpKeyImage->SetSize(32.f, 32.f);
    m_JumpKeyImage->SetTexture("JumpKeyImage", TEXT("KeyIcon/JumpKey.png"));

    m_AltKeyImage = CreateWidget<CUIImage>("AltKeyImage");
    m_AltKeyImage->SetPos(955.f, 35.f);
    m_AltKeyImage->SetSize(18.f, 9.f);
    m_AltKeyImage->SetTexture("AltKeyImage", TEXT("KeyIcon/AltKeyIcon.png"));

    m_RedPotionKeyImage = CreateWidget<CUIImage>("RedPotionKeyImage");
    m_RedPotionKeyImage->SetSize(27.f, 27.f);
    m_RedPotionKeyImage->SetPos(984.f, 21.f);
    m_RedPotionKeyImage->SetTexture("RedPotionKeyImage", TEXT("KeyIcon/RedPotionKey.png"));

    m_DelKeyImage = CreateWidget<CUIImage>("DelKeyImage");
    m_DelKeyImage->SetSize(19.f, 9.f);
    m_DelKeyImage->SetPos(984.f, 40.f);
    m_DelKeyImage->SetTexture("DelKeyImage", TEXT("KeyIcon/DelKeyIcon.png"));

    m_BluePotionKeyImage = CreateWidget<CUIImage>("BluePotionKeyImage");
    m_BluePotionKeyImage->SetSize(27.f, 27.f);
    m_BluePotionKeyImage->SetPos(1018.f, 21.f);
    m_BluePotionKeyImage->SetTexture("BluePotionKeyImage", TEXT("KeyIcon/BluePotionKey.png"));

    m_EndKeyImage = CreateWidget<CUIImage>("EndKeyImage");
    m_EndKeyImage->SetSize(19.f, 9.f);
    m_EndKeyImage->SetPos(1018.f, 40.f);
    m_EndKeyImage->SetTexture("EndKeyImage", TEXT("KeyIcon/EndKeyIcon.png"));


    std::vector<const TCHAR*>	vecFileNames;

    for (int i = 0; i < 10; ++i)
    {
        TCHAR* FileName = new TCHAR[MAX_PATH];

        memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);

        wsprintf(FileName, TEXT("Item_Number/Item_Number%d.png"), i);

        vecFileNames.push_back(FileName);
    }

    m_RedPotionKeyNumber = CreateWidget<CUINumber>("RedPotionNumber");
    m_RedPotionKeyNumber->SetTexture("RedPotionKeyNumber", vecFileNames);
    m_RedPotionKeyNumber->SetPos(984.f, 21.f);
    m_RedPotionKeyNumber->SetSize(8.f, 11.f);
    m_RedPotionKeyNumber->SetNumber(100);

    m_BluePotionKeyNumber = CreateWidget<CUINumber>("BluePotionNumber");
    m_BluePotionKeyNumber->SetTexture("BluePotionKeyNumber", vecFileNames);
    m_BluePotionKeyNumber->SetPos(1018.f, 21.f);
    m_BluePotionKeyNumber->SetSize(8.f, 11.f);
    m_BluePotionKeyNumber->SetNumber(100);

    for (int i = 0; i < 10; ++i)
    {
        m_RedPotionKeyNumber->AddFrameData(Vector2(0.f, 0.f), Vector2(8.f, 11.f));
        m_BluePotionKeyNumber->AddFrameData(Vector2(0.f, 0.f), Vector2(8.f, 11.f));
    }

    size_t Size = vecFileNames.size();

    for (size_t i = 0; i < Size; ++i)
    {
        SAFE_DELETE(vecFileNames[i]);
    }


    m_BaseSkillKeyImage = CreateWidget<CUIImage>("BaseSkillImage");
    m_BaseSkillKeyImage->SetPos(912.f, 53.f);
    m_BaseSkillKeyImage->SetSize(32.f, 32.f);
    m_BaseSkillKeyImage->SetTexture("BaseSkillImage", TEXT("KeyIcon/SpeedDualShotIcon.png"));
    m_BaseSkillKeyImage->SetEnable(false);

    m_ShiftKeyImage = CreateWidget<CUIImage>("ShiftKeyImage");
    m_ShiftKeyImage->SetPos(915.f, 75.f);
    m_ShiftKeyImage->SetSize(28.f, 9.f);
    m_ShiftKeyImage->SetTexture("ShiftKeyImage", TEXT("KeyIcon/ShiftKeyIcon.png"));
    m_ShiftKeyImage->SetEnable(false);

    m_HighSkillKeyImage = CreateWidget<CUIImage>("HighSkillImage");
    m_HighSkillKeyImage->SetPos(946.f, 53.f);
    m_HighSkillKeyImage->SetSize(32.f, 32.f);
    m_HighSkillKeyImage->SetTexture("HighSkillImage", TEXT("KeyIcon/RingIcon.png"));
    m_HighSkillKeyImage->SetEnable(false);

    m_SpaceKeyImage = CreateWidget<CUIImage>("SpaceKeyImage");
    m_SpaceKeyImage->SetPos(948.f, 75.f);
    m_SpaceKeyImage->SetSize(28.f, 9.f);
    m_SpaceKeyImage->SetTexture("SpaceKeyImage", TEXT("KeyIcon/SpaceKeyIcon.png"));
    m_SpaceKeyImage->SetEnable(false);

    m_FlashJumpKeyImage = CreateWidget<CUIImage>("FlashJumpImage");
    m_FlashJumpKeyImage->SetPos(1052.f, 18.f);
    m_FlashJumpKeyImage->SetSize(32.f, 32.f);
    m_FlashJumpKeyImage->SetTexture("FlashJumpImage", TEXT("KeyIcon/FlashJumpIcon.png"));
    m_FlashJumpKeyImage->SetEnable(false);

    m_PdnKeyImage = CreateWidget<CUIImage>("PdnKeyImage");
    m_PdnKeyImage->SetPos(1055.f, 40.f);
    m_PdnKeyImage->SetSize(22.f, 9.f);
    m_PdnKeyImage->SetTexture("PdnKeyImage", TEXT("KeyIcon/PdnKeyIcon.png"));
    m_PdnKeyImage->SetEnable(false);



}

void CStartSceneUI::UpdateHonTailInfo()
{

    int HonTailMaxHp =  m_HonTail->GetHonTailMaxHp();
    int HonTailHp = m_HonTail->GetHonTailHp();

    m_HonTailProgressBar->SetProgressBarMin(0.f);
    m_HonTailProgressBar->SetProgressBarMax((float)HonTailMaxHp);
    m_HonTailProgressBar->SetValue((float)HonTailHp);

    if (HonTailHp <= 0)
    {
        m_HonTailProgressBar->SetEnable(false);
        CUIImage* HonTailIcon = FindWidget<CUIImage>("HonTailIcon");
        HonTailIcon->SetEnable(false);
    }

}

TCHAR* CStartSceneUI::StringtoTCHAR(const std::string& Name)
{
    size_t origsize = 0, convertedChars = 0;
    origsize = strlen(Name.c_str()) + 1;
    wchar_t* t = new wchar_t[origsize];
    mbstowcs_s(&convertedChars, t, origsize, Name.c_str(), _TRUNCATE);

    return (TCHAR*)t;
}

void CStartSceneUI::SetExp(int Exp)
{
    
    m_ExpText->SetEnable(true);
    m_AddExpNumber->SetEnable(true);
    m_AddExpNumber->SetNumber(Exp);
    m_Player->AddExp(Exp);
    m_ExpOn = true;
}

void CStartSceneUI::MiniMapStart()
{

    if (m_Scene->GetName() == "HonTail")
    {
        CUIImage* MiniMap = CreateWidget<CUIImage>("HonTailMiniMap");
        MiniMap->SetPos(15.f, 580.f);
        MiniMap->SetSize(135.f, 130.f);
        MiniMap->SetTexture("HonTailMiniMap", TEXT("HonTailMiniMap.png"));

        m_MinimapPlayerIcon = CreateWidget<CUIImage>("PlayerMiniMap");
        m_MinimapPlayerIcon->SetSize(12.f, 12.f);
        m_MinimapPlayerIcon->SetTexture("PlayerMiniMap", TEXT("MapPlayerIcon.png"));
    }

    if (m_Scene->GetName() == "Henesis")
    {
        CUIImage* MiniMap = CreateWidget<CUIImage>("HenesisMiniMap");
        MiniMap->SetPos(15.f, 560.f);
        MiniMap->SetSize(381.f, 148.f);
        MiniMap->SetTexture("HenesisMiniMap", TEXT("HenesisMiniMap.png"));

        m_MinimapPlayerIcon = CreateWidget<CUIImage>("PlayerMiniMap");
        m_MinimapPlayerIcon->SetSize(12.f, 12.f);
        m_MinimapPlayerIcon->SetTexture("PlayerMiniMap", TEXT("MapPlayerIcon.png"));

    }

    if (m_Scene->GetName() == "HonTailFront")
    {
        CUIImage* MiniMap = CreateWidget<CUIImage>("HonTailFrontMiniMap");
        MiniMap->SetPos(15.f, 580.f);
        MiniMap->SetSize(168.f, 120.f);
        MiniMap->SetTexture("HonTailFrontMinimap", TEXT("HonTailFrontMinimap.png"));

        m_MinimapPlayerIcon = CreateWidget<CUIImage>("PlayerMiniMap");
        m_MinimapPlayerIcon->SetSize(12.f, 12.f);
        m_MinimapPlayerIcon->SetTexture("PlayerMiniMap", TEXT("MapPlayerIcon.png"));
    }

    if (m_Scene->GetName() == "Basic")
    {
        CUIImage* MiniMap = CreateWidget<CUIImage>("BasicMiniMap");
        MiniMap->SetPos(15.f, 540.f);
        MiniMap->SetSize(141.f, 170.f);
        MiniMap->SetTexture("BasicMiniMap", TEXT("BasicMiniMap.png"));

        m_MinimapPlayerIcon = CreateWidget<CUIImage>("PlayerMiniMap");
        m_MinimapPlayerIcon->SetSize(12.f, 12.f);
        m_MinimapPlayerIcon->SetTexture("PlayerMiniMap", TEXT("MapPlayerIcon.png"));
    }

    if (m_Scene->GetName() == "HenesisClass")
    {
        CUIImage* MiniMap = CreateWidget<CUIImage>("HenesisClassMiniMap");
        MiniMap->SetPos(15.f, 620.f);
        MiniMap->SetSize(127.f, 92.f);
        MiniMap->SetTexture("HenesisClassMiniMap", TEXT("HenesisClassMiniMap.png"));
    }

}


