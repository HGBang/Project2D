#include "SelectPlayerUI.h"
#include "UI/UIImage.h"
#include "UI/UIButton.h"
#include "UI/UINumber.h"
#include "UI/UIText.h"
#include "Scene/Scene.h"
#include "Scene/SceneManager.h"
#include "Resource/ResourceManager.h"
#include "Resource/Sound/Sound.h"
#include "../Scene/LoadingSceneInfo.h"
#include "../Setting/DefaultSetting.h"
#include "../Setting/EngineShareSetting.h"

CSelectPlayerUI::CSelectPlayerUI()
{
	m_WindowTypeName = "SelectPlayerUI";
}

CSelectPlayerUI::CSelectPlayerUI(const CSelectPlayerUI& Window) :
	CUIWindow(Window)
{
	m_PlayerCheckImage = FindWidget<CUIImage>("PlayerCheckImage");
	m_PlayerLevelImage = FindWidget<CUIImage>("PlayerLevelImage");
	m_PlayerLevel = FindWidget<CUINumber>("PlayerLevelNumber");
	m_PlayerName = FindWidget<CUIText>("PlayerName");
	m_PlayerClassName = FindWidget<CUIText>("PlayerClassName");

	m_PlayerStr = FindWidget<CUINumber>("PlayerStrNumber");
	m_PlayerDex = FindWidget<CUINumber>("PlayerDexNumber");
	m_PlayerInt = FindWidget<CUINumber>("PlayerIntNumber");
	m_PlayerLuk = FindWidget<CUINumber>("PlayerLukNumber");

	m_GameStartButton = FindWidget<CUIButton>("GameStartButton");
	m_PlayerCreateButton = FindWidget<CUIButton>("PlayerCreateButton");
	m_PlayerDeleteButton = FindWidget<CUIButton>("PlayerDeleteButton");
	m_PrevButton = FindWidget<CUIButton>("PrevButton");
	m_WhiteButton = FindWidget<CUIButton>("WhiteButton");
}

CSelectPlayerUI::~CSelectPlayerUI()
{
}

void CSelectPlayerUI::Start()
{
	CUIWindow::Start();	

	CSceneManager::GetInst()->GetScene()->GetResource()->LoadSound("Effect", "CharSelect", false, "CharSelect.mp3");


	m_WhiteButton->SetCallback<CSelectPlayerUI>(EButtonEventState::Click, this, &CSelectPlayerUI::WhiteButtonClick);

	m_GameStartButton->SetCallback<CSelectPlayerUI>(EButtonEventState::Click, this, &CSelectPlayerUI::GameStartButton);
}

bool CSelectPlayerUI::Init()
{
	CUIWindow::Init();


	m_SelectPlayer = false;

	m_PlayerCheckImage = CreateWidget<CUIImage>("PlayerCheckImage");
	m_PlayerCheckImage->SetPos(1000.f, 160.f);
	m_PlayerCheckImage->SetSize(194.f, 271.f);
	m_PlayerCheckImage->SetTexture("PlayerCheckImage", TEXT("PlayerSelect.png"));

	m_PlayerLevelImage = CreateWidget<CUIImage>("PlayerLevelImage");
	m_PlayerLevelImage->SetPos(1070.f, 385.f);
	m_PlayerLevelImage->SetSize(23.f, 18.f);
	m_PlayerLevelImage->SetTexture("PlayerLevelImage", TEXT("PlayerSelectLv.png"));

	m_PlayerLevel = CreateWidget<CUINumber>("PlayerLevelNumber");
	m_PlayerLevel->SetPos(1100.f, 385.f);
	m_PlayerLevel->SetSize(11.f, 19.f);
	//m_PlayerLevel->SetNumber(1);

	std::vector<const TCHAR*>	vecFileNames;

	for (int i = 0; i < 10; ++i)
	{
		TCHAR* FileName = new TCHAR[MAX_PATH];

		memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);

		wsprintf(FileName, TEXT("SelectSceneLvNumber/SelectSceneLvNumber%d.png"), i);

		vecFileNames.push_back(FileName);
	}

	m_PlayerLevel->SetTexture("PlayerLevelNumber", vecFileNames);

	for (int i = 0; i < 10; ++i)
	{
		m_PlayerLevel->AddFrameData(Vector2(0.f, 0.f), Vector2(11.f, 19.f));
	}

	size_t Size = vecFileNames.size();

	for (size_t i = 0; i < Size; ++i)
	{
		SAFE_DELETE(vecFileNames[i]);
	}

	m_PlayerClassName = CreateWidget<CUIText>("PlayerClassName");
	m_PlayerClassName->SetPos(1080.f, 238.f);
	m_PlayerClassName->SetSize(100.f, 100.f);
	m_PlayerClassName->SetText(TEXT(""));
	m_PlayerClassName->SetFontSize(10.f);

	m_PlayerName = CreateWidget<CUIText>("PlayerName");
	m_PlayerName->SetPos(1060.f, 268.f);
	m_PlayerName->SetSize(100.f, 100.f);
	m_PlayerName->SetText(TEXT(""));
	m_PlayerName->SetFontSize(15.f);


	vecFileNames.clear();

	for (int i = 0; i < 10; ++i)
	{
		TCHAR* FileName = new TCHAR[MAX_PATH];

		memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);

		wsprintf(FileName, TEXT("HPMPNumber/HPMPNumber%d.png"), i);

		vecFileNames.push_back(FileName);
	}

	m_PlayerStr = CreateWidget<CUINumber>("PlayerStrNumber");
	m_PlayerStr->SetPos(1067.f, 303.f);
	m_PlayerStr->SetSize(7.f, 9.f);
	m_PlayerStr->SetTexture("PlayerStrNumber", vecFileNames);
	//m_PlayerStr->SetNumber(10);

	m_PlayerDex = CreateWidget<CUINumber>("PlayerDexNumber");
	m_PlayerDex->SetPos(1067.f, 279.f);
	m_PlayerDex->SetSize(7.f, 9.f);
	m_PlayerDex->SetTexture("PlayerDexNumber", vecFileNames);
	//m_PlayerDex->SetNumber(10);

	m_PlayerInt = CreateWidget<CUINumber>("PlayerIntNumber");
	m_PlayerInt->SetPos(1137.f, 303.f);
	m_PlayerInt->SetSize(7.f, 9.f);
	m_PlayerInt->SetTexture("PlayerIntNumber", vecFileNames);
	//m_PlayerInt->SetNumber(10);

	m_PlayerLuk = CreateWidget<CUINumber>("PlayerLukNumber");
	m_PlayerLuk->SetPos(1137.f, 279.f);
	m_PlayerLuk->SetSize(7.f, 9.f);
	m_PlayerLuk->SetTexture("PlayerLukNumber", vecFileNames);
	//m_PlayerLuk->SetNumber(10);

	for (int i = 0; i < 10; ++i)
	{
		m_PlayerStr->AddFrameData(Vector2(0.f, 0.f), Vector2(7.f, 9.f));
		m_PlayerDex->AddFrameData(Vector2(0.f, 0.f), Vector2(7.f, 9.f));
		m_PlayerInt->AddFrameData(Vector2(0.f, 0.f), Vector2(7.f, 9.f));
		m_PlayerLuk->AddFrameData(Vector2(0.f, 0.f), Vector2(7.f, 9.f));
	}

	Size = vecFileNames.size();

	for (size_t i = 0; i < Size; ++i)
	{
		SAFE_DELETE(vecFileNames[i]);
	}

	m_GameStartButton = CreateWidget<CUIButton>("GameStartButton");
	m_GameStartButton->SetSize(140.f, 52.f);
	m_GameStartButton->SetPos(1026.f, 188.f);
	m_GameStartButton->SetTexture(EButtonState::Normal, "GameStartButton", TEXT("PlayerSelectButton_Normal.png"));
	m_GameStartButton->SetTexture(EButtonState::Hovered, "GameStartButton", TEXT("PlayerSelectButton_Hov.png"));
	m_GameStartButton->SetTexture(EButtonState::Click, "GameStartButton", TEXT("PlayerSelectButton_Click.png"));
	m_GameStartButton->SetTexture(EButtonState::Disable, "GameStartButton", TEXT("PlayerSelectButton_Enable.png"));
	m_GameStartButton->ButtonEnable(false);


	m_PlayerCreateButton = CreateWidget<CUIButton>("PlayerCreateButton");
	m_PlayerCreateButton->SetSize(132.f, 47.f);
	m_PlayerCreateButton->SetPos(440.f, 30.f);
	m_PlayerCreateButton->SetTexture(EButtonState::Normal, "PlayerCreateButton", TEXT("CreatePlayerButton_Normal.png"));
	m_PlayerCreateButton->SetTexture(EButtonState::Hovered, "PlayerCreateButton", TEXT("CreatePlayerButton_Hov.png"));
	m_PlayerCreateButton->SetTexture(EButtonState::Click, "PlayerCreateButton", TEXT("CreatePlayerButton_Click.png"));


	m_PlayerDeleteButton = CreateWidget<CUIButton>("PlayerDeleteButton");
	m_PlayerDeleteButton->SetSize(132.f, 47.f);
	m_PlayerDeleteButton->SetPos(600.f, 30.f);
	m_PlayerDeleteButton->SetTexture(EButtonState::Normal, "PlayerDeleteButton", TEXT("DeletePlayerButton_Normal.png"));
	m_PlayerDeleteButton->SetTexture(EButtonState::Hovered, "PlayerDeleteButton", TEXT("DeletePlayerButton_Hov.png"));
	m_PlayerDeleteButton->SetTexture(EButtonState::Click, "PlayerDeleteButton", TEXT("DeletePlayerButton_Click.png"));


	m_PrevButton = CreateWidget<CUIButton>("PrevButton");
	m_PrevButton->SetSize(81.f, 34.f);
	m_PrevButton->SetPos(0.f, 30.f);
	m_PrevButton->SetTexture(EButtonState::Normal, "PrevButton", TEXT("PrevButton_Normal.png"));
	m_PrevButton->SetTexture(EButtonState::Hovered, "PrevButton", TEXT("PrevButton_Hov.png"));
	m_PrevButton->SetTexture(EButtonState::Click, "PrevButton", TEXT("PrevButton_Click.png"));

	m_WhiteButton = CreateWidget<CUIButton>("WhiteButton");
	m_WhiteButton->SetSize(100.f, 120.f);
	m_WhiteButton->SetPos(550.f, 150.f);
	m_WhiteButton->SetTexture(EButtonState::Normal, "WhiteButton", TEXT("PrevButton_Normal.png"));
	m_WhiteButton->SetTexture(EButtonState::Hovered, "WhiteButton", TEXT("PrevButton_Hov.png"));
	m_WhiteButton->SetTexture(EButtonState::Click, "WhiteButton", TEXT("PrevButton_Click.png"));
	m_WhiteButton->SetOpacity(0.f);
	m_WhiteButton->SetCallback<CSelectPlayerUI>(EButtonEventState::Click, this, &CSelectPlayerUI::WhiteButtonClick);

	return true;
}

void CSelectPlayerUI::Update(float DeltaTime)
{
	CUIWindow::Update(DeltaTime);

	if (m_SelectPlayer && !m_ButtonOn)
	{
		m_PlayerName->SetText(TEXT("Player"));
		m_PlayerClassName->SetText(TEXT("메르세데스"));

		m_PlayerLevel->SetNumber(1);
		m_PlayerStr->SetNumber(5);
		m_PlayerInt->SetNumber(5);
		m_PlayerLuk->SetNumber(5);
		m_PlayerDex->SetNumber(10);
		m_GameStartButton->ButtonEnable(true);
		m_ButtonOn = true;
	}

	




}

void CSelectPlayerUI::PostUpdate(float DeltaTime)
{
	CUIWindow::PostUpdate(DeltaTime);
}

void CSelectPlayerUI::Render()
{
	CUIWindow::Render();
}

CSelectPlayerUI* CSelectPlayerUI::Clone()
{
	return new CSelectPlayerUI(*this);
}

void CSelectPlayerUI::Save(FILE* File)
{
	CUIWindow::Save(File);
}

void CSelectPlayerUI::Load(FILE* File)
{
	CUIWindow::Load(File);

	m_PlayerCheckImage = FindWidget<CUIImage>("PlayerCheckImage");
	m_PlayerLevelImage = FindWidget<CUIImage>("PlayerLevelImage");
	m_PlayerLevel = FindWidget<CUINumber>("PlayerLevelNumber");
	m_PlayerName = FindWidget<CUIText>("PlayerName");
	m_PlayerClassName = FindWidget<CUIText>("PlayerClassName");

	m_PlayerStr = FindWidget<CUINumber>("PlayerStrNumber");
	m_PlayerDex = FindWidget<CUINumber>("PlayerDexNumber");
	m_PlayerInt = FindWidget<CUINumber>("PlayerIntNumber");
	m_PlayerLuk = FindWidget<CUINumber>("PlayerLukNumber");

	m_GameStartButton = FindWidget<CUIButton>("GameStartButton");
	m_PlayerCreateButton = FindWidget<CUIButton>("PlayerCreateButton");
	m_PlayerDeleteButton = FindWidget<CUIButton>("PlayerDeleteButton");
	m_PrevButton = FindWidget<CUIButton>("PrevButton");
	m_WhiteButton = FindWidget<CUIButton>("WhiteButton");

}

void CSelectPlayerUI::GameStartButton()
{
	CScene* Scene = CSceneManager::GetInst()->GetScene();

	CSceneManager::GetInst()->CreateNextScene(true);

	CScene* NextScene = CSceneManager::GetInst()->GetNextScene();

	NextScene->Load("FrontScene.scn", SCENE_PATH);

}

void CSelectPlayerUI::WhiteButtonClick()
{
	m_SelectPlayer = true;

	m_Scene->GetResource()->SoundPlay("CharSelect");
}
