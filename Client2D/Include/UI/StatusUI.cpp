#include "StatusUI.h"
#include "StatusUI.h"
#include "UI/UIImage.h"
#include "UI/UIButton.h"
#include "UI/UINumber.h"
#include "UI/UIText.h"
#include "Scene/Scene.h"
#include "Scene/SceneManager.h"
#include "Resource/ResourceManager.h"
#include "Resource/Sound/Sound.h"
#include "../GameObject/Player2D.h"
#include "Engine.h"
#include "Input.h"


CStatusUI::CStatusUI()
{
	m_WindowTypeName = "StatusUI";
}

CStatusUI::CStatusUI(const CStatusUI& Window) :
	CUIWindow(Window)
{

	m_DragButton = FindWidget<CUIButton>("DragButton");
	m_StatBackImage = FindWidget<CUIImage>("StatBackImage");
	m_StatMainImage = FindWidget<CUIImage>("StatMainImage");
	m_ApImage = FindWidget<CUIImage>("StatApImage");
	m_PlayerName = FindWidget<CUIText>("StatPlayerName");
	m_ClassName = FindWidget<CUIText>("StatClassName");
	m_DamageNumber = FindWidget<CUIText>("StatDamageNumber");
	m_HpNumber = FindWidget<CUIText>("StatHpNumber");
	m_MaxHpNumber = FindWidget<CUIText>("StatMaxHpNumber");
	m_MpNumber = FindWidget<CUIText>("StatMpNumber");
	m_MaxMpNumber = FindWidget<CUIText>("StatMaxMpNumber");
	m_ApNumber = FindWidget<CUIText>("StatApNumber");
	m_StrNumber = FindWidget<CUIText>("StatStrNumber");
	m_DexNumber = FindWidget<CUIText>("StatDexNumber");
	m_IntNumber = FindWidget<CUIText>("StatIntNumber");
	m_LukNumber = FindWidget<CUIText>("StatLukNumber");
	m_StrUpButton = FindWidget<CUIButton>("StatStrUpButton");
	m_DexUpButton = FindWidget<CUIButton>("StatDexUpButton");
	m_IntUpButton = FindWidget<CUIButton>("StatIntUpButton");
	m_LukUpButton = FindWidget<CUIButton>("StatLukUpButton");
	m_Slush = FindWidget<CUIText>("Slush");
	m_Slush = FindWidget<CUIText>("Slush2");

}

CStatusUI::~CStatusUI()
{
}

void CStatusUI::Start()
{
	CUIWindow::Start();
	m_StrUpButton->SetCallback<CStatusUI>(EButtonEventState::Click, this, &CStatusUI::StrUpButtonClick);
	m_DexUpButton->SetCallback<CStatusUI>(EButtonEventState::Click, this, &CStatusUI::DexUpButtonClick);
	m_IntUpButton->SetCallback<CStatusUI>(EButtonEventState::Click, this, &CStatusUI::IntUpButtonClick);
	m_LukUpButton->SetCallback<CStatusUI>(EButtonEventState::Click, this, &CStatusUI::LukUpButtonClick);
}

bool CStatusUI::Init()
{
	CUIWindow::Init();

	m_DragButton = CreateWidget<CUIButton>("DragButton");
	m_DragButton->SetSize(100.f, 30.f);
	m_DragButton->SetPos(250.f, 600.f);
	m_DragButton->SetOpacity(0.f);


	m_StatBackImage = CreateWidget<CUIImage>("StatBackImage");
	m_StatBackImage->SetSize(212.f, 336.f);
	m_StatBackImage->SetPos(200.f, 300.f);
	m_StatBackImage->SetTexture("StatBackImage", TEXT("StatWindow/StatWindowBack.png"));

	m_StatMainImage = CreateWidget<CUIImage>("StatMainImage");
	m_StatMainImage->SetSize(202.f, 307.f);
	m_StatMainImage->SetPos(205.f, 310.f);
	m_StatMainImage->SetTexture("StatMainImage", TEXT("StatWindow/StatWindowMain.png"));

	m_ApImage = CreateWidget<CUIImage>("ApImage");
	m_ApImage->SetSize(198.f, 46.f);
	m_ApImage->SetPos(205.f, 420.f);
	m_ApImage->SetTexture("ApImage", TEXT("StatWindow/StatWindowAp.png"));

	m_PlayerName = CreateWidget<CUIText>("StatPlayerName");
	m_PlayerName->SetPos(280.f, 577.f);
	m_PlayerName->SetSize(100.f, 30.f);
	m_PlayerName->SetText(TEXT("플레이어"));
	m_PlayerName->SetFontSize(9.f);
	m_PlayerName->SetColor(Vector4(0.f, 0.f, 0.f, 1.f));

	m_ClassName = CreateWidget<CUIText>("StatClassName");
	m_ClassName->SetPos(280.f, 560.f);
	m_ClassName->SetSize(100.f, 30.f);
	m_ClassName->SetText(TEXT("메르세데스"));
	m_ClassName->SetFontSize(9.f);
	m_ClassName->SetColor(Vector4(0.f, 0.f, 0.f, 1.f));

	//스텟 어빌리티 숫자 

	m_DamageNumber = CreateWidget<CUIText>("StatDamageNumber");
	m_DamageNumber->SetFont("Default");
	m_DamageNumber->SetColor(0, 0, 0);
	m_DamageNumber->SetSize(100.f, 30.f);
	m_DamageNumber->SetFontSize(9.f);
	m_DamageNumber->SetText(TEXT("10"));
	m_DamageNumber->SetPos(280.f, 507.f);


	m_HpNumber = CreateWidget<CUIText>("StatHpNumber");
	m_HpNumber->SetFont("Default");
	m_HpNumber->SetColor(0, 0, 0);
	m_HpNumber->SetSize(100.f, 30.f);
	m_HpNumber->SetFontSize(9.f);
	m_HpNumber->SetText(TEXT("1000"));
	m_HpNumber->SetPos(280.f, 470.f);

	m_Slush = CreateWidget<CUIText>("Slush");
	m_Slush->SetFont("Default");
	m_Slush->SetColor(0, 0, 0);
	m_Slush->SetSize(10.f, 30.f);
	m_Slush->SetFontSize(8.f);
	m_Slush->SetText(TEXT("/"));
	m_Slush->SetPos(305.f, 470.f);

	m_MaxHpNumber = CreateWidget<CUIText>("StatMaxHpNumber");
	m_MaxHpNumber->SetFont("Default");
	m_MaxHpNumber->SetColor(0, 0, 0);
	m_MaxHpNumber->SetSize(100.f, 30.f);
	m_MaxHpNumber->SetFontSize(9.f);
	m_MaxHpNumber->SetText(TEXT("2000"));
	m_MaxHpNumber->SetPos(312.f, 470.f);

	m_MpNumber = CreateWidget<CUIText>("StatMpNumber");
	m_MpNumber->SetFont("Default");
	m_MpNumber->SetColor(0, 0, 0);
	m_MpNumber->SetSize(100.f, 30.f);
	m_MpNumber->SetFontSize(9.f);
	m_MpNumber->SetText(TEXT("1000"));
	m_MpNumber->SetPos(280.f, 452.f);

	m_Slush2 = CreateWidget<CUIText>("Slush2");
	m_Slush2->SetFont("Default");
	m_Slush2->SetColor(0, 0, 0);
	m_Slush2->SetSize(10.f, 30.f);
	m_Slush2->SetFontSize(8.f);
	m_Slush2->SetText(TEXT("/"));
	m_Slush2->SetPos(305.f, 452.f);

	m_MaxMpNumber = CreateWidget<CUIText>("StatMaxMpNumber");
	m_MaxMpNumber->SetFont("Default");
	m_MaxMpNumber->SetColor(0, 0, 0);
	m_MaxMpNumber->SetSize(100.f, 30.f);
	m_MaxMpNumber->SetFontSize(9.f);
	m_MaxMpNumber->SetText(TEXT("2000"));
	m_MaxMpNumber->SetPos(312.f, 452.f);

	m_ApNumber = CreateWidget<CUIText>("StatApNumber");
	m_ApNumber->SetFont("Default");
	m_ApNumber->SetColor(0, 0, 0);
	m_ApNumber->SetSize(100.f, 30.f);
	m_ApNumber->SetFontSize(9.f);
	m_ApNumber->SetText(TEXT("0"));
	m_ApNumber->SetPos(280.f, 412.f);

	m_StrNumber = CreateWidget<CUIText>("StatStrNumber");
	m_StrNumber->SetFont("Default");
	m_StrNumber->SetColor(0, 0, 0);
	m_StrNumber->SetSize(100.f, 30.f);
	m_StrNumber->SetFontSize(9.f);
	m_StrNumber->SetText(TEXT("5"));
	m_StrNumber->SetPos(280.f, 383.f);

	m_DexNumber = CreateWidget<CUIText>("StatDexNumber");
	m_DexNumber->SetFont("Default");
	m_DexNumber->SetColor(0, 0, 0);
	m_DexNumber->SetSize(100.f, 30.f);
	m_DexNumber->SetFontSize(9.f);
	m_DexNumber->SetText(TEXT("10"));
	m_DexNumber->SetPos(280.f, 366.f);

	m_IntNumber = CreateWidget<CUIText>("StatIntNumber");
	m_IntNumber->SetFont("Default");
	m_IntNumber->SetColor(0, 0, 0);
	m_IntNumber->SetSize(100.f, 30.f);
	m_IntNumber->SetFontSize(9.f);
	m_IntNumber->SetText(TEXT("5"));
	m_IntNumber->SetPos(280.f, 347.f);

	m_LukNumber = CreateWidget<CUIText>("StatLukNumber");
	m_LukNumber->SetFont("Default");
	m_LukNumber->SetColor(0, 0, 0);
	m_LukNumber->SetSize(100.f, 30.f);
	m_LukNumber->SetFontSize(9.f);
	m_LukNumber->SetText(TEXT("5"));
	m_LukNumber->SetPos(280.f, 330.f);

	m_StrUpButton = CreateWidget<CUIButton>("StatStrUpButton");
	m_StrUpButton->SetPos(387.f, 400.5f);
	m_StrUpButton->SetSize(12.f, 12.f);
	m_StrUpButton->SetTexture(EButtonState::Normal, "StatUpButton_Normal", TEXT("StatWindow/StatButton_Normal.png"));
	m_StrUpButton->SetTexture(EButtonState::Hovered, "StatUpButton_Normal", TEXT("StatWindow/StatButton_Hov.png"));
	m_StrUpButton->SetTexture(EButtonState::Click, "StatUpButton_Normal", TEXT("StatWindow/StatButton_Click.png"));
	m_StrUpButton->SetTexture(EButtonState::Disable, "StatUpButton_Normal", TEXT("StatWindow/StatButton_Enable.png"));
	m_StrUpButton->SetCallback<CStatusUI>(EButtonEventState::Click, this, &CStatusUI::StrUpButtonClick);
	m_StrUpButton->ButtonEnable(false);

	m_DexUpButton = CreateWidget<CUIButton>("StatDexUpButton");
	m_DexUpButton->SetPos(387.f, 383.f);
	m_DexUpButton->SetSize(12.f, 12.f);
	m_DexUpButton->SetTexture(EButtonState::Normal, "StatUpButton_Normal", TEXT("StatWindow/StatButton_Normal.png"));
	m_DexUpButton->SetTexture(EButtonState::Hovered, "StatUpButton_Normal", TEXT("StatWindow/StatButton_Hov.png"));
	m_DexUpButton->SetTexture(EButtonState::Click, "StatUpButton_Normal", TEXT("StatWindow/StatButton_Click.png"));
	m_DexUpButton->SetTexture(EButtonState::Disable, "StatUpButton_Normal", TEXT("StatWindow/StatButton_Enable.png"));
	m_DexUpButton->SetCallback<CStatusUI>(EButtonEventState::Click, this, &CStatusUI::DexUpButtonClick);
	m_DexUpButton->ButtonEnable(false);

	m_IntUpButton = CreateWidget<CUIButton>("StatIntUpButton");
	m_IntUpButton->SetPos(387.f, 364.5f);
	m_IntUpButton->SetSize(12.f, 12.f);
	m_IntUpButton->SetTexture(EButtonState::Normal, "StatUpButton_Normal", TEXT("StatWindow/StatButton_Normal.png"));
	m_IntUpButton->SetTexture(EButtonState::Hovered, "StatUpButton_Normal", TEXT("StatWindow/StatButton_Hov.png"));
	m_IntUpButton->SetTexture(EButtonState::Click, "StatUpButton_Normal", TEXT("StatWindow/StatButton_Click.png"));
	m_IntUpButton->SetTexture(EButtonState::Disable, "StatUpButton_Normal", TEXT("StatWindow/StatButton_Enable.png"));
	m_IntUpButton->SetCallback<CStatusUI>(EButtonEventState::Click, this, &CStatusUI::IntUpButtonClick);
	m_IntUpButton->ButtonEnable(false);

	m_LukUpButton = CreateWidget<CUIButton>("StatLukUpButton");
	m_LukUpButton->SetPos(387.f, 346.5f);
	m_LukUpButton->SetSize(12.f, 12.f);
	m_LukUpButton->SetTexture(EButtonState::Normal, "StatUpButton_Normal", TEXT("StatWindow/StatButton_Normal.png"));
	m_LukUpButton->SetTexture(EButtonState::Hovered, "StatUpButton_Normal", TEXT("StatWindow/StatButton_Hov.png"));
	m_LukUpButton->SetTexture(EButtonState::Click, "StatUpButton_Normal", TEXT("StatWindow/StatButton_Click.png"));
	m_LukUpButton->SetTexture(EButtonState::Disable, "StatUpButton_Normal", TEXT("StatWindow/StatButton_Enable.png"));
	m_LukUpButton->SetCallback<CStatusUI>(EButtonEventState::Click, this, &CStatusUI::LukUpButtonClick);
	m_LukUpButton->ButtonEnable(false);


	return true;
}

void CStatusUI::Update(float DeltaTime)
{
	CUIWindow::Update(DeltaTime);

	// 인벤토리 드래그 처리 

	Vector2 WorldPos = CInput::GetInst()->GetMousePos();

	if (m_DragButton->GetButtonState() == EButtonState::Normal || m_DragButton->GetButtonState() == EButtonState::Hovered)
	{
		m_Drag = false;
	}

	if (m_DragButton->GetButtonState() == EButtonState::Click)
	{
		m_Drag = true;
	}

	if (m_Drag)
		m_Pos = Vector2(WorldPos.x - 300.f, WorldPos.y - 625.f);


	// 플레이어 정보 업데이트 
	UpdatePlayerInfo();

	// AP 버튼 업데이트 
	if (m_ButtonUpdate)
		UpdateApButtonInfo();

	if (m_ButtonDisable)
		UpdateButtonDisable();
}

void CStatusUI::PostUpdate(float DeltaTime)
{
	CUIWindow::PostUpdate(DeltaTime);
}

void CStatusUI::Render()
{
	CUIWindow::Render();
}

CStatusUI* CStatusUI::Clone()
{
	return new CStatusUI(*this);
}

void CStatusUI::Save(FILE* File)
{
	CUIWindow::Save(File);
}

void CStatusUI::Load(FILE* File)
{
	CUIWindow::Load(File);

	m_DragButton = FindWidget<CUIButton>("DragButton");
	m_StatBackImage = FindWidget<CUIImage>("StatBackImage");
	m_StatMainImage = FindWidget<CUIImage>("StatMainImage");
	m_ApImage = FindWidget<CUIImage>("StatApImage");
	m_PlayerName = FindWidget<CUIText>("StatPlayerName");
	m_ClassName = FindWidget<CUIText>("StatClassName");
	m_DamageNumber = FindWidget<CUIText>("StatDamageNumber");
	m_HpNumber = FindWidget<CUIText>("StatHpNumber");
	m_MaxHpNumber = FindWidget<CUIText>("StatMaxHpNumber");
	m_MpNumber = FindWidget<CUIText>("StatMpNumber");
	m_MaxMpNumber = FindWidget<CUIText>("StatMaxMpNumber");
	m_ApNumber = FindWidget<CUIText>("StatApNumber");
	m_StrNumber = FindWidget<CUIText>("StatStrNumber");
	m_DexNumber = FindWidget<CUIText>("StatDexNumber");
	m_IntNumber = FindWidget<CUIText>("StatIntNumber");
	m_LukNumber = FindWidget<CUIText>("StatLukNumber");
	m_StrUpButton = FindWidget<CUIButton>("StatStrUpButton");
	m_DexUpButton = FindWidget<CUIButton>("StatDexUpButton");
	m_IntUpButton = FindWidget<CUIButton>("StatIntUpButton");
	m_LukUpButton = FindWidget<CUIButton>("StatLukUpButton");
	m_Slush = FindWidget<CUIText>("Slush");
	m_Slush = FindWidget<CUIText>("Slush2");

}

void CStatusUI::UpdatePlayerInfo()
{
	m_Player = (CPlayer2D*)m_Scene->FindObject("Player2D");

	int MaxHp = m_Player->GetMaxHp();
	int Hp = m_Player->GetHp();
	int MaxMp = m_Player->GetMaxMp();
	int Mp = m_Player->GetMp();
	int Damage = m_Player->GetDamage();
	int Ap = m_Player->GetAp();
	int Str = m_Player->GetStr();
	int Dex = m_Player->GetDex();
	int Int = m_Player->GetInt();
	int Luk = m_Player->GetLuk();

	m_DamageNumber->SetTextNumber(Damage);
	m_HpNumber->SetTextNumber(Hp);
	m_MaxHpNumber->SetTextNumber(MaxHp);
	m_MpNumber->SetTextNumber(Mp);
	m_MaxMpNumber->SetTextNumber(MaxMp);
	m_ApNumber->SetTextNumber(Ap);
	m_StrNumber->SetTextNumber(Str);
	m_DexNumber->SetTextNumber(Dex);
	m_IntNumber->SetTextNumber(Int);
	m_LukNumber->SetTextNumber(Luk);

}

void CStatusUI::UpdateApButtonInfo()
{
	int ApCount = m_Player->GetAp();

	if (ApCount > 0)
	{
		m_StrUpButton->ButtonEnable(true);
		m_DexUpButton->ButtonEnable(true);
		m_IntUpButton->ButtonEnable(true);
		m_LukUpButton->ButtonEnable(true);
	}

	m_ButtonUpdate = false;
}

void CStatusUI::UpdateButtonDisable()
{
	m_StrUpButton->ButtonEnable(false);
	m_DexUpButton->ButtonEnable(false);
	m_IntUpButton->ButtonEnable(false);
	m_LukUpButton->ButtonEnable(false);

	m_ButtonDisable = false;
}

void CStatusUI::StrUpButtonClick()
{
	int ApCount = m_Player->GetAp();

	if (ApCount)
		m_Player->AddStr(1);

	ApCount = m_Player->GetAp();

	if (ApCount == 0)
		m_ButtonDisable = true;

}

void CStatusUI::DexUpButtonClick()
{
	int ApCount = m_Player->GetAp();

	if (ApCount)
		m_Player->AddDex(1);

	ApCount = m_Player->GetAp();

	if (ApCount == 0)
		m_ButtonDisable = true;
}

void CStatusUI::IntUpButtonClick()
{
	int ApCount = m_Player->GetAp();

	if (ApCount)
		m_Player->AddInt(1);

	ApCount = m_Player->GetAp();

	if (ApCount == 0)
		m_ButtonDisable = true;
}

void CStatusUI::LukUpButtonClick()
{
	int ApCount = m_Player->GetAp();

	if (ApCount)
		m_Player->AddLuk(1);

	ApCount = m_Player->GetAp();

	if (ApCount == 0)
		m_ButtonDisable = true;
}



