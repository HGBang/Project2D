#include "MonsterBarUI.h"
#include "UI/UIButton.h"
#include "UI/UIText.h"
#include "UI/UIProgressBar.h"
#include "UI/UINumber.h"
#include "UI/UIImage.h"
#include "UI/UIDamageNumber.h"
#include "UI/UIWidget.h"
#include "../Scene/LoadingSceneInfo.h"
#include "Scene/SceneManager.h"
#include "Scene/Scene.h"
#include "Engine.h"
#include "../GameObject/Player2D.h"
#include "Resource/Texture/Texture.h"
#include "Scene/CameraManager.h"
#include "Component/CameraComponent.h"

CMonsterBarUI::CMonsterBarUI() : 
	ProgressBarID(0)
{
	m_WindowTypeName = "MonsterBarUI";
}

CMonsterBarUI::CMonsterBarUI(const CMonsterBarUI& Window) :
	CUIWindow(Window)
{
	
}

CMonsterBarUI::~CMonsterBarUI()
{		
}

CUIProgressBar* CMonsterBarUI::GetProGressBar(int MaxHp, const Vector2& MonsterPos)
{
	++ProgressBarID;
	std::string BarID = std::to_string(ProgressBarID);

	m_ProgressBar = CreateWidget<CUIProgressBar>(BarID);
	m_ProgressBar->SetSize(82.f, 10.f);
	m_ProgressBar->SetUIPos(MonsterPos);
	m_ProgressBar->SetTexture(EProgressBarTextureType::Back, "MonsterHpBack", TEXT("MonsterHpBar/MonsterHpBarBack.png"));
	m_ProgressBar->SetTexture(EProgressBarTextureType::Bar, "MonsterHpBar", TEXT("MonsterHpBar/MonsterHpBar.png"));
	m_ProgressBar->SetProgressBarMax((float)MaxHp);
	m_ProgressBar->SetValue(100.f);
	m_ProgressBar->SetMonster(true);
	m_ProgressBar->SetPivot(0.5f, -5.5f);
	m_ProgressBar->SetEnable(false);
	

	return m_ProgressBar;
}

CUIText* CMonsterBarUI::GetMonsterNameTag(const TCHAR* MonsterName, const Vector2& MonsterPos)
{
	++MonsterNameID;
	std::string MonsterID = "MonsterMonsterMonsterMonster" + MonsterNameID;

	m_MonsterNameText = CreateWidget<CUIText>(MonsterID);
	m_MonsterNameText->SetFont("Default");
	m_MonsterNameText->SetColor(255, 255, 0);
	m_MonsterNameText->SetSize(100.f, 30.f);
	m_MonsterNameText->SetFontSize(20.f);
	m_MonsterNameText->SetPos(MonsterPos);
	m_MonsterNameText->SetFontSize(13.f);
	m_MonsterNameText->SetText(MonsterName);
	m_MonsterNameText->SetEnable(false);

	return m_MonsterNameText;
}

void CMonsterBarUI::SetBarPos(const Vector2& MonsterPos)
{
	m_WorldPos = MonsterPos;
	m_Pos = MonsterPos;	
}

void CMonsterBarUI::Start()
{
	CUIWindow::Start();

	ProgressBarID = 0;
	MonsterNameID = 0;
}

bool CMonsterBarUI::Init()
{
	return true;
}

void CMonsterBarUI::Update(float DeltaTime)
{
	CUIWindow::Update(DeltaTime);	
}

void CMonsterBarUI::PostUpdate(float DeltaTime)
{
	CUIWindow::PostUpdate(DeltaTime);
}

void CMonsterBarUI::Render()
{
	CUIWindow::Render();
}

CMonsterBarUI* CMonsterBarUI::Clone()
{
	return new CMonsterBarUI(*this);
}

void CMonsterBarUI::Save(FILE* File)
{
	CUIWindow::Save(File);

}

void CMonsterBarUI::Load(FILE* File)
{
	CUIWindow::Load(File);
	ProgressBarID = 0;
	MonsterNameID = 0;
}
