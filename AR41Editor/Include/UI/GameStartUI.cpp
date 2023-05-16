#include "GameStartUI.h"
#include "UI/UIImage.h"
#include "UI/UIButton.h"
#include "Scene/Scene.h"
#include "Scene/SceneManager.h"
#include "Resource/ResourceManager.h"
#include "Resource/Sound/Sound.h"
#include "../Scene/LoadingSceneInfo.h"


CGameStartUI::CGameStartUI()
{
	m_WindowTypeName = "GameStartUI";
}

CGameStartUI::CGameStartUI(const CGameStartUI& Window) : 
    CUIWindow(Window)
{
    m_BackImage = FindWidget<CUIImage>("GameStartBack");
    m_Button = FindWidget<CUIButton>("GameStartButton");
}

CGameStartUI::~CGameStartUI()
{
}

void CGameStartUI::Start()
{
	CUIWindow::Start();

    m_BackImage = CreateWidget<CUIImage>("GameStartBack");
    m_BackImage->SetSize(1280.f, 720.f);
    m_BackImage->SetTexture("MainImage", TEXT("MainImage.png"));

    m_Button = CreateWidget<CUIButton>("GameStartButton");

    m_Button->SetSize(350.f, 53.f);
    m_Button->SetPos(460.f, 280.f);
    m_Button->SetTint(255, 0, 0, 255);

    m_Button->SetTexture(EButtonState::Normal, "StartButton", TEXT("GameStartButton.png"));
    m_Button->SetTexture(EButtonState::Hovered, "StartButton", TEXT("GameStartButton.png"));
    m_Button->SetTexture(EButtonState::Click, "StartButton", TEXT("GameStartButton.png"));
    m_Button->SetTexture(EButtonState::Disable, "StartButton", TEXT("GameStartButton.png"));

    m_Button->SetSound(EButtonEventState::Hovered, "UI", "ButtonHovered", false, "LoginMouseHoveredButton.mp3");
    m_Button->SetSound(EButtonEventState::Click, "UI", "ButtonClick", false, "LoginMouseClickButton.mp3");

    m_Button->SetCallback<CGameStartUI>(EButtonEventState::Click, this, &CGameStartUI::GameStartButton);


    //CResourceManager::GetInst()->SoundPlay("LoginBGM");

}

bool CGameStartUI::Init()
{
    CUIWindow::Init();

     m_BackImage = CreateWidget<CUIImage>("GameStartBack");
    m_BackImage->SetSize(1280.f, 720.f);
    m_BackImage->SetTexture("MainImage", TEXT("MainImage.png"));

    m_Button = CreateWidget<CUIButton>("GameStartButton");

    m_Button->SetSize(350.f, 53.f);
    m_Button->SetPos(460.f, 280.f);
    m_Button->SetTint(255, 0, 0, 255);

    m_Button->SetTexture(EButtonState::Normal, "StartButton", TEXT("GameStartButton.png"));
    m_Button->SetTexture(EButtonState::Hovered, "StartButton", TEXT("GameStartButton.png"));
    m_Button->SetTexture(EButtonState::Click, "StartButton", TEXT("GameStartButton.png"));
    m_Button->SetTexture(EButtonState::Disable, "StartButton", TEXT("GameStartButton.png"));

    m_Button->SetSound(EButtonEventState::Hovered, "UI", "ButtonHovered", false, "LoginMouseHoveredButton.mp3");
    m_Button->SetSound(EButtonEventState::Click, "UI", "ButtonClick", false, "LoginMouseClickButton.mp3");

    m_Button->SetCallback<CGameStartUI>(EButtonEventState::Click, this, &CGameStartUI::GameStartButton);


    //CResourceManager::GetInst()->SoundPlay("LoginBGM");


	return true;
}

void CGameStartUI::Update(float DeltaTime)
{
	CUIWindow::Update(DeltaTime);
}

void CGameStartUI::PostUpdate(float DeltaTime)
{
	CUIWindow::PostUpdate(DeltaTime);
}

void CGameStartUI::Render()
{
	CUIWindow::Render();
}

CGameStartUI* CGameStartUI::Clone()
{
	return new CGameStartUI(*this);
}

void CGameStartUI::Save(FILE* File)
{
	CUIWindow::Save(File);
}

void CGameStartUI::Load(FILE* File)
{
	CUIWindow::Load(File);

    m_BackImage = FindWidget<CUIImage>("GameStartBack");
    m_Button = FindWidget<CUIButton>("GameStartButton");
}

void CGameStartUI::GameStartButton()
{
    CScene* Scene = CSceneManager::GetInst()->GetScene();

    CSceneManager::GetInst()->CreateNextScene(true);

    CScene* NextScene = CSceneManager::GetInst()->GetNextScene();
    NextScene->Load("PlayerSelect.scn", SCENE_PATH);

    //CSceneManager::GetInst()->GetScene()->Load("Test10.scn", SCENE_PATH);    
}
