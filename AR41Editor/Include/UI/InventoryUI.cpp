#include "InventoryUI.h"
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
#include "QuestUI.h"
#include "UI/UIWindow.h"

CInventoryUI::CInventoryUI()
{
	m_WindowTypeName = "InventoryUI";
}

CInventoryUI::CInventoryUI(const CInventoryUI& Window) :
	CUIWindow(Window)
{
	m_DragButton = FindWidget<CUIButton>("InventoryDragButton");
	m_InventoryBackImage = FindWidget<CUIImage>("InventoryBackImage");
	m_InventoryBackImage2 = FindWidget<CUIImage>("InventoryBackImage2");
	m_InventoryBackImage3 = FindWidget<CUIImage>("InventoryBackImage3");
	m_InventoryMesoImage = FindWidget<CUIImage>("InventoryMesoImage");
	m_InventoryMaplePointImage = FindWidget<CUIImage>("InventoryMaplePointImage");
	m_InventoryMesoText = FindWidget<CUIText>("InventoryMesoText");
	m_InventoryMaplePointText = FindWidget<CUIText>("InventoryMaplePointText");
	m_EquipButton = FindWidget<CUIButton>("InventoryEquipButton");
	m_UseButton = FindWidget<CUIButton>("InventoryUseButton");
	m_DisEnableButton1 = FindWidget<CUIButton>("InventoryDisableButton1");
	m_DisEnableButton2 = FindWidget<CUIButton>("InventoryDisableButton2");
	m_DisEnableButton3 = FindWidget<CUIButton>("InventoryDisableButton3");
	m_DisEnableButton4 = FindWidget<CUIButton>("InventoryDisableButton4");
	m_DisEnableButton5 = FindWidget<CUIButton>("InventoryDisableButton5");
	m_DisEnableButton6 = FindWidget<CUIButton>("InventoryDisableButton6");
	m_DisEnableButton7 = FindWidget<CUIButton>("InventoryDisableButton7");
	m_DisEnableButton8 = FindWidget<CUIButton>("InventoryDisableButton8");
	m_DisEnableButton9 = FindWidget<CUIButton>("InventoryDisableButton9");
	m_DisEnableButton10 = FindWidget<CUIButton>("InventoryDisableButton10");
	m_Weapon1 = FindWidget<CUIButton>("InventoryWeapon1");
	m_Weapon2 = FindWidget<CUIButton>("InventoryWeapon2");
	m_HpPotionImage = FindWidget<CUIImage>("InventoryHpPotion");
	m_MpPotionImage = FindWidget<CUIImage>("InventoryMpPotion");
	m_HpPotionNumber = FindWidget<CUINumber>("HpPotionNumber");
	m_MpPotionNumber = FindWidget<CUINumber>("MpPotionNumber");
	m_EquipInvButton = FindWidget<CUIButton>("EnableButton1");
	m_UseInvButton = FindWidget<CUIButton>("EnableButton2");
	m_Weapon1Image = FindWidget<CUIImage>("Weapon1Image");
	m_Weapon2Image = FindWidget<CUIImage>("Weapon2Image");

}

CInventoryUI::~CInventoryUI()
{
}

void CInventoryUI::Start()
{
	CUIWindow::Start();

	m_DragButton = CreateWidget<CUIButton>("InventoryDragButton");
	m_DragButton->SetSize(100.f, 20.f);
	m_DragButton->SetPos(750.f, 555.f);
	m_DragButton->SetOpacity(0.f);

	m_InventoryBackImage = CreateWidget<CUIImage>("InventoryBackImage");
	m_InventoryBackImage->SetSize(197.f, 380.f);
	m_InventoryBackImage->SetPos(700.f, 200.f);
	m_InventoryBackImage->SetTexture("InventoryBackImage", TEXT("ItemWindow/ItemWindowBack.png"));

	m_InventoryBackImage2 = CreateWidget<CUIImage>("InventoryBackImage2");
	m_InventoryBackImage2->SetSize(187.f, 351.f);
	m_InventoryBackImage2->SetPos(705.f, 205.f);
	m_InventoryBackImage2->SetTexture("InventoryBackImage2", TEXT("ItemWindow/ItemWindowBack2.png"));

	m_InventoryBackImage3 = CreateWidget<CUIImage>("InventoryBackImage3");
	m_InventoryBackImage3->SetSize(183.f, 296.f);
	m_InventoryBackImage3->SetPos(707.f, 239.f);
	m_InventoryBackImage3->SetTexture("InventoryBackImage3", TEXT("ItemWindow/ItemWindowBack3.png"));

	m_InventoryMesoImage = CreateWidget<CUIImage>("InventoryMesoImage");
	m_InventoryMesoImage->SetSize(40.f, 16.f);
	m_InventoryMesoImage->SetPos(707.f, 257.f);
	m_InventoryMesoImage->SetTexture("InventoryMesoImage", TEXT("ItemWindow/MesoIcon.png"));

	m_InventoryMaplePointImage = CreateWidget<CUIImage>("InventoryMaplePointImage");
	m_InventoryMaplePointImage->SetSize(82.f, 16.f);
	m_InventoryMaplePointImage->SetPos(707.f, 239.f);
	m_InventoryMaplePointImage->SetTexture("InventoryMaplePointImage", TEXT("ItemWindow/MaplePointIcon.png"));

	m_InventoryMesoText = CreateWidget<CUIText>("InventoryMesoText");
	m_InventoryMesoText->SetFont("Default");
	m_InventoryMesoText->SetColor(Vector4(0.f, 0.f, 0.f, 1.f));
	m_InventoryMesoText->SetTextNumber(100000);
	m_InventoryMesoText->SetFontSize(12.f);
	m_InventoryMesoText->SetPos(760.f, 244.f);
	m_InventoryMesoText->SetSize(100.f, 30.f);

	m_InventoryMaplePointText = CreateWidget<CUIText>("InventoryMaplePointText");
	m_InventoryMaplePointText->SetFont("Default");
	m_InventoryMaplePointText->SetColor(Vector4(0.f, 0.f, 0.f, 1.f));
	m_InventoryMaplePointText->SetTextNumber(0);
	m_InventoryMaplePointText->SetFontSize(12.f);
	m_InventoryMaplePointText->SetPos(865.f, 226.f);
	m_InventoryMaplePointText->SetSize(100.f, 30.f);

	m_EquipButton = CreateWidget<CUIButton>("InventoryEquipButton");
	m_EquipButton->SetSize(29.f, 19.f);
	m_EquipButton->SetPos(708.f, 535.f);
	m_EquipButton->SetTexture(EButtonState::Click, "InventoryEquipButton", TEXT("ItemWindow/EquipButton_Normal.png"));
	m_EquipButton->SetTexture(EButtonState::Normal, "InventoryEquipButton", TEXT("ItemWindow/EquipButton_Normal.png"));
	m_EquipButton->SetTexture(EButtonState::Hovered, "InventoryEquipButton", TEXT("ItemWindow/EquipButton_Normal.png"));
	m_EquipButton->SetTexture(EButtonState::Disable, "InventoryEquipButton_Disable", TEXT("ItemWindow/EquipButton_Disable.png"));

	m_UseButton = CreateWidget<CUIButton>("InventoryUseButton");
	m_UseButton->SetSize(29.f, 19.f);
	m_UseButton->SetPos(738.5f, 535.f);
	m_UseButton->SetTexture(EButtonState::Click, "InventoryUseButton", TEXT("ItemWindow/UseButton_Normal.png"));
	m_UseButton->SetTexture(EButtonState::Normal, "InventoryUseButton", TEXT("ItemWindow/UseButton_Normal.png"));
	m_UseButton->SetTexture(EButtonState::Hovered, "InventoryUseButton", TEXT("ItemWindow/UseButton_Normal.png"));
	m_UseButton->SetTexture(EButtonState::Disable, "InventoryUseButton_Disable", TEXT("ItemWindow/UseButton_Disable.png"));
	m_UseButton->ButtonEnable(false);

	DisEnableButtonCreate();

	m_Weapon1 = CreateWidget<CUIButton>("InventoryWeapon1");
	m_Weapon1->SetSize(35.f, 35.f);
	m_Weapon1->SetPos(712.f, 490.f);
	m_Weapon1->SetTexture(EButtonState::Normal, "InventoryWeapon1", TEXT("Weapon1/WeaponInv.png"));
	m_Weapon1->SetTexture(EButtonState::Click, "InventoryWeapon1", TEXT("Weapon1/WeaponInv.png"));
	m_Weapon1->SetTexture(EButtonState::Hovered, "InventoryWeapon1", TEXT("Weapon1/WeaponInv.png"));
	m_Weapon1->SetTexture(EButtonState::Disable, "InventoryWeapon1", TEXT("Weapon1/WeaponInv.png"));
	m_Weapon1->SetCallback(EButtonEventState::Click, this, &CInventoryUI::Weapon1EquipButton);
	m_Weapon1->SetEnable(false);

	m_Weapon2 = CreateWidget<CUIButton>("InventoryWeapon2");
	m_Weapon2->SetSize(37.f, 36.f);
	m_Weapon2->SetPos(751.f, 490.f);
	m_Weapon2->SetTexture(EButtonState::Normal, "InventoryWeapon2", TEXT("Weapon2/WeaponInv.png"));
	m_Weapon2->SetTexture(EButtonState::Click, "InventoryWeapon2", TEXT("Weapon2/WeaponInv.png"));
	m_Weapon2->SetTexture(EButtonState::Hovered, "InventoryWeapon2", TEXT("Weapon2/WeaponInv.png"));
	m_Weapon2->SetTexture(EButtonState::Disable, "InventoryWeapon2", TEXT("Weapon2/WeaponInv.png"));
	m_Weapon2->SetCallback(EButtonEventState::Click, this, &CInventoryUI::Weapon2EquipButton);
	m_Weapon2->SetEnable(false);


	m_HpPotionImage = CreateWidget<CUIImage>("InventoryHpPotion");
	m_HpPotionImage->SetSize(27.f, 30.f);
	m_HpPotionImage->SetPos(715.f, 493.f);
	m_HpPotionImage->SetTexture("HpPotion", TEXT("Potion/RedPotionInv.png"));

	m_MpPotionImage = CreateWidget<CUIImage>("InventoryMpPotion");
	m_MpPotionImage->SetSize(27.f, 30.f);
	m_MpPotionImage->SetPos(756.f, 493.f);
	m_MpPotionImage->SetTexture("MpPotion", TEXT("Potion/BluePotionInv.png"));


	std::vector<const TCHAR*>	vecFileNames;

	for (int i = 0; i < 10; ++i)
	{
		TCHAR* FileName = new TCHAR[MAX_PATH];

		memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);

		wsprintf(FileName, TEXT("Item_Number/Item_Number%d.png"), i);

		vecFileNames.push_back(FileName);
	}

	m_HpPotionNumber = CreateWidget<CUINumber>("HpPotionNumber");
	m_HpPotionNumber->SetPos(715.f, 495.f);
	m_HpPotionNumber->SetSize(8.f, 11.f);
	m_HpPotionNumber->SetNumber(1);
	m_HpPotionNumber->SetTexture("HpPotionNumber", vecFileNames);

	m_MpPotionNumber = CreateWidget<CUINumber>("MpPotionNumber");
	m_MpPotionNumber->SetPos(755.f, 495.f);
	m_MpPotionNumber->SetSize(8.f, 11.f);
	m_MpPotionNumber->SetNumber(1);
	m_MpPotionNumber->SetTexture("MpPotionNumber", vecFileNames);

	for (int i = 0; i < 10; ++i)
	{
		m_HpPotionNumber->AddFrameData(Vector2(0.f, 0.f), Vector2(8.f, 11.f));
		m_MpPotionNumber->AddFrameData(Vector2(0.f, 0.f), Vector2(8.f, 11.f));
	}

	size_t Size = vecFileNames.size();

	for (size_t i = 0; i < Size; ++i)
	{
		SAFE_DELETE(vecFileNames[i]);
	}

	m_EquipInvButton = CreateWidget<CUIButton>("EnableButton1");
	m_EquipInvButton->SetSize(25.f, 15.f);
	m_EquipInvButton->SetPos(710.f, 535.f);
	m_EquipInvButton->SetOpacity(0.f);
	m_EquipInvButton->SetCallback(EButtonEventState::Click, this, &CInventoryUI::EquipItemEnable);


	m_UseInvButton = CreateWidget<CUIButton>("EnableButton2");
	m_UseInvButton->SetSize(25.f, 15.f);
	m_UseInvButton->SetPos(740.f, 535.f);
	m_UseInvButton->SetOpacity(0.f);
	m_UseInvButton->SetCallback(EButtonEventState::Click, this, &CInventoryUI::UseItemEnable);

	m_EquipInv = true;
	m_UseInv = false;

	m_Weapon1Image = CreateWidget<CUIImage>("Weapon1Image");
	m_Weapon1Image->SetSize(260.f, 324.f);
	m_Weapon1Image->SetPos(300.f, 300.f);
	m_Weapon1Image->SetTexture("Weapon1Image", TEXT("Weapon1Image.png"));
	m_Weapon1Image->SetOpacity(0.f);

	m_Weapon2Image = CreateWidget<CUIImage>("Weapon2Image");
	m_Weapon2Image->SetSize(259.f, 312.f);
	m_Weapon2Image->SetPos(300.f, 300.f);
	m_Weapon2Image->SetTexture("Weapon2Image", TEXT("Weapon2Image.png"));
	m_Weapon2Image->SetOpacity(0.f);
}

bool CInventoryUI::Init()
{
	CUIWindow::Init();	

	return true;
}

void CInventoryUI::Update(float DeltaTime)
{
	CUIWindow::Update(DeltaTime);

	Vector2 WorldPos = CInput::GetInst()->GetMousePos();
	Vector2 MouseWolrldPos = CInput::GetInst()->GetMouseWorldPos();

	if (m_DragButton->GetButtonState() == EButtonState::Normal || m_DragButton->GetButtonState() == EButtonState::Hovered)
	{
		m_Drag = false;
	}

	if (m_DragButton->GetButtonState() == EButtonState::Click)
	{
		m_Drag = true;
	}

	if (m_Drag)
		m_Pos = Vector2(WorldPos.x - 800.f, WorldPos.y - 570.f);


	if (!m_UseInv && m_EquipInv)
	{
		m_HpPotionImage->SetEnable(false);
		m_MpPotionImage->SetEnable(false);
		m_HpPotionNumber->SetEnable(false);
		m_MpPotionNumber->SetEnable(false);
		m_EquipButton->ButtonEnable(true);
	}

	if (!m_EquipInv && m_UseInv)
	{
		m_Weapon1->SetEnable(false);
		m_Weapon2->SetEnable(false);
		m_UseButton->ButtonEnable(true);
	}

	if (!EquipWeapon1 && !m_UseInv)
		m_Weapon1->SetEnable(true);

	/*if (m_Player->GetWeapon1())
	{
		m_Weapon1->SetEnable(false);	
	}

	if (m_Player->GetWeapon2())
	{
		m_Weapon2->SetEnable(false);	
	}*/

	if (!EquipWeapon2 && !m_UseInv && m_Player->GetSkill2Lock())
		m_Weapon2->SetEnable(true);

	m_DoubleClickTime += DeltaTime;

	if (m_DoubleClickTime > 0.7f)
	{
		m_DoubleClickTime = 0.f;
		m_DoubleClick = 0;
	}

	if (m_UseButton->GetEnable())
	{
		int HpPotionNumber = m_Player->GetHpPotionNumber();
		int MpPotionNumber = m_Player->GetMpPotionNumber();

		m_HpPotionNumber->SetNumber(HpPotionNumber);
		m_MpPotionNumber->SetNumber(MpPotionNumber);
	}

	if (m_Weapon1->GetButtonState() == EButtonState::Hovered)
	{
		m_Weapon1Image->SetOpacity(1.f);
		m_Weapon1Image->SetPos(Vector2(m_Pos.x * 0.1f + 600.f, m_Pos.y * 0.1f + 195.f));
	}	

	if (m_Weapon1->GetButtonState() == EButtonState::Normal || !m_Weapon1->GetEnable())
	{
		m_Weapon1Image->SetOpacity(0.f);
	}

	if (m_Weapon2->GetButtonState() == EButtonState::Hovered)
	{
		m_Weapon2Image->SetOpacity(1.f);
		m_Weapon2Image->SetPos(Vector2(m_Pos.x * 0.1f + 630.f, m_Pos.y * 0.1f + 195.f));
	}

	if (m_Weapon2->GetButtonState() == EButtonState::Normal || !m_Weapon2->GetEnable())
	{
		m_Weapon2Image->SetOpacity(0.f);
	}
}

void CInventoryUI::PostUpdate(float DeltaTime)
{
	CUIWindow::PostUpdate(DeltaTime);
}

void CInventoryUI::Render()
{
	CUIWindow::Render();
}

CInventoryUI* CInventoryUI::Clone()
{
	return new CInventoryUI(*this);
}

void CInventoryUI::Save(FILE* File)
{
	CUIWindow::Save(File);

	fwrite(&EquipWeapon1, sizeof(bool), 1, File);
	fwrite(&EquipWeapon2, sizeof(bool), 1, File);

}

void CInventoryUI::Load(FILE* File)
{
	CUIWindow::Load(File);

	m_DragButton = FindWidget<CUIButton>("InventoryDragButton");
	m_InventoryBackImage = FindWidget<CUIImage>("InventoryBackImage");
	m_InventoryBackImage2 = FindWidget<CUIImage>("InventoryBackImage2");
	m_InventoryBackImage3 = FindWidget<CUIImage>("InventoryBackImage3");
	m_InventoryMesoImage = FindWidget<CUIImage>("InventoryMesoImage");
	m_InventoryMaplePointImage = FindWidget<CUIImage>("InventoryMaplePointImage");
	m_InventoryMesoText = FindWidget<CUIText>("InventoryMesoText");
	m_InventoryMaplePointText = FindWidget<CUIText>("InventoryMaplePointText");
	m_EquipButton = FindWidget<CUIButton>("InventoryEquipButton");
	m_UseButton = FindWidget<CUIButton>("InventoryUseButton");
	m_DisEnableButton1 = FindWidget<CUIButton>("InventoryDisableButton1");
	m_DisEnableButton2 = FindWidget<CUIButton>("InventoryDisableButton2");
	m_DisEnableButton3 = FindWidget<CUIButton>("InventoryDisableButton3");
	m_DisEnableButton4 = FindWidget<CUIButton>("InventoryDisableButton4");
	m_DisEnableButton5 = FindWidget<CUIButton>("InventoryDisableButton5");
	m_DisEnableButton6 = FindWidget<CUIButton>("InventoryDisableButton6");
	m_DisEnableButton7 = FindWidget<CUIButton>("InventoryDisableButton7");
	m_DisEnableButton8 = FindWidget<CUIButton>("InventoryDisableButton8");
	m_DisEnableButton9 = FindWidget<CUIButton>("InventoryDisableButton9");
	m_DisEnableButton10 = FindWidget<CUIButton>("InventoryDisableButton10");
	m_Weapon1 = FindWidget<CUIButton>("InventoryWeapon1");
	m_Weapon2 = FindWidget<CUIButton>("InventoryWeapon2");

	m_HpPotionImage = FindWidget<CUIImage>("InventoryHpPotion");
	m_MpPotionImage = FindWidget<CUIImage>("InventoryMpPotion");
	m_HpPotionNumber = FindWidget<CUINumber>("HpPotionNumber");
	m_MpPotionNumber = FindWidget<CUINumber>("MpPotionNumber");
	m_EquipInvButton = FindWidget<CUIButton>("EnableButton1");
	m_UseInvButton = FindWidget<CUIButton>("EnableButton2");
	m_Weapon1Image = FindWidget<CUIImage>("Weapon1Image");
	m_Weapon2Image = FindWidget<CUIImage>("Weapon2Image");

	fread(&EquipWeapon1, sizeof(bool), 1, File);
	fread(&EquipWeapon2, sizeof(bool), 1, File);

}

void CInventoryUI::DisEnableButtonCreate()
{
	m_DisEnableButton1 = CreateWidget<CUIButton>("InventoryDisableButton1");
	m_DisEnableButton1->SetSize(29.f, 19.f);
	m_DisEnableButton1->SetPos(768.5f, 535.f);
	m_DisEnableButton1->SetTexture(EButtonState::Click, "InventoryDisableButton1", TEXT("ItemWindow/DisableButton1.png"));
	m_DisEnableButton1->SetTexture(EButtonState::Normal, "InventoryDisableButton1", TEXT("ItemWindow/DisableButton1.png"));
	m_DisEnableButton1->SetTexture(EButtonState::Hovered, "InventoryDisableButton1", TEXT("ItemWindow/DisableButton1.png"));
	m_DisEnableButton1->SetTexture(EButtonState::Disable, "InventoryDisableButton1", TEXT("ItemWindow/DisableButton1.png"));
	m_DisEnableButton1->ButtonEnable(false);

	m_DisEnableButton2 = CreateWidget<CUIButton>("InventoryDisableButton2");
	m_DisEnableButton2->SetSize(29.f, 19.f);
	m_DisEnableButton2->SetPos(798.5f, 535.f);
	m_DisEnableButton2->SetTexture(EButtonState::Click, "InventoryDisableButton2", TEXT("ItemWindow/DisableButton2.png"));
	m_DisEnableButton2->SetTexture(EButtonState::Normal, "InventoryDisableButton2", TEXT("ItemWindow/DisableButton2.png"));
	m_DisEnableButton2->SetTexture(EButtonState::Hovered, "InventoryDisableButton2", TEXT("ItemWindow/DisableButton2.png"));
	m_DisEnableButton2->SetTexture(EButtonState::Disable, "InventoryDisableButton2", TEXT("ItemWindow/DisableButton2.png"));
	m_DisEnableButton2->ButtonEnable(false);

	m_DisEnableButton3 = CreateWidget<CUIButton>("InventoryDisableButton3");
	m_DisEnableButton3->SetSize(29.f, 19.f);
	m_DisEnableButton3->SetPos(828.5f, 535.f);
	m_DisEnableButton3->SetTexture(EButtonState::Click, "InventoryDisableButton3", TEXT("ItemWindow/DisableButton3.png"));
	m_DisEnableButton3->SetTexture(EButtonState::Normal, "InventoryDisableButton3", TEXT("ItemWindow/DisableButton3.png"));
	m_DisEnableButton3->SetTexture(EButtonState::Hovered, "InventoryDisableButton3", TEXT("ItemWindow/DisableButton3.png"));
	m_DisEnableButton3->SetTexture(EButtonState::Disable, "InventoryDisableButton3", TEXT("ItemWindow/DisableButton3.png"));
	m_DisEnableButton3->ButtonEnable(false);

	m_DisEnableButton4 = CreateWidget<CUIButton>("InventoryDisableButton4");
	m_DisEnableButton4->SetSize(29.f, 19.f);
	m_DisEnableButton4->SetPos(858.5f, 535.f);
	m_DisEnableButton4->SetTexture(EButtonState::Click, "InventoryDisableButton4", TEXT("ItemWindow/DisableButton4.png"));
	m_DisEnableButton4->SetTexture(EButtonState::Normal, "InventoryDisableButton4", TEXT("ItemWindow/DisableButton4.png"));
	m_DisEnableButton4->SetTexture(EButtonState::Hovered, "InventoryDisableButton4", TEXT("ItemWindow/DisableButton4.png"));
	m_DisEnableButton4->SetTexture(EButtonState::Disable, "InventoryDisableButton4", TEXT("ItemWindow/DisableButton4.png"));
	m_DisEnableButton4->ButtonEnable(false);

	m_DisEnableButton5 = CreateWidget<CUIButton>("InventoryDisableButton5");
	m_DisEnableButton5->SetImageTint(EButtonState::Disable, 255, 255, 255, 255);
	m_DisEnableButton5->SetSize(28.f, 28.f);
	m_DisEnableButton5->SetPos(708.f, 208.f);
	m_DisEnableButton5->SetTexture(EButtonState::Click, "InventoryDisableButton5", TEXT("ItemWindow/ItemWindowButton1.png"));
	m_DisEnableButton5->SetTexture(EButtonState::Normal, "InventoryDisableButton5", TEXT("ItemWindow/ItemWindowButton1.png"));
	m_DisEnableButton5->SetTexture(EButtonState::Hovered, "InventoryDisableButton5", TEXT("ItemWindow/ItemWindowButton1.png"));
	m_DisEnableButton5->SetTexture(EButtonState::Disable, "InventoryDisableButton5", TEXT("ItemWindow/ItemWindowButton1.png"));
	m_DisEnableButton5->ButtonEnable(false);


	m_DisEnableButton6 = CreateWidget<CUIButton>("InventoryDisableButton6");
	m_DisEnableButton6->SetImageTint(EButtonState::Disable, 255, 255, 255, 255);
	m_DisEnableButton6->SetSize(29.f, 28.f);
	m_DisEnableButton6->SetPos(738.f, 208.f);
	m_DisEnableButton6->SetTexture(EButtonState::Click, "InventoryDisableButton6", TEXT("ItemWindow/ItemWindowButton2.png"));
	m_DisEnableButton6->SetTexture(EButtonState::Normal, "InventoryDisableButton6", TEXT("ItemWindow/ItemWindowButton2.png"));
	m_DisEnableButton6->SetTexture(EButtonState::Hovered, "InventoryDisableButton6", TEXT("ItemWindow/ItemWindowButton2.png"));
	m_DisEnableButton6->SetTexture(EButtonState::Disable, "InventoryDisableButton6", TEXT("ItemWindow/ItemWindowButton2.png"));
	m_DisEnableButton6->ButtonEnable(false);

	m_DisEnableButton7 = CreateWidget<CUIButton>("InventoryDisableButton7");
	m_DisEnableButton7->SetImageTint(EButtonState::Disable, 255, 255, 255, 255);
	m_DisEnableButton7->SetSize(28.f, 28.f);
	m_DisEnableButton7->SetPos(769.f, 208.f);
	m_DisEnableButton7->SetTexture(EButtonState::Click, "InventoryDisableButton7", TEXT("ItemWindow/ItemWindowButton3.png"));
	m_DisEnableButton7->SetTexture(EButtonState::Normal, "InventoryDisableButton7", TEXT("ItemWindow/ItemWindowButton3.png"));
	m_DisEnableButton7->SetTexture(EButtonState::Hovered, "InventoryDisableButton7", TEXT("ItemWindow/ItemWindowButton3.png"));
	m_DisEnableButton7->SetTexture(EButtonState::Disable, "InventoryDisableButton7", TEXT("ItemWindow/ItemWindowButton3.png"));
	m_DisEnableButton7->ButtonEnable(false);

	m_DisEnableButton8 = CreateWidget<CUIButton>("InventoryDisableButton8");
	m_DisEnableButton8->SetImageTint(EButtonState::Disable, 255, 255, 255, 255);
	m_DisEnableButton8->SetSize(28.f, 28.f);
	m_DisEnableButton8->SetPos(799.f, 208.f);
	m_DisEnableButton8->SetTexture(EButtonState::Click, "InventoryDisableButton8", TEXT("ItemWindow/ItemWindowButton4.png"));
	m_DisEnableButton8->SetTexture(EButtonState::Normal, "InventoryDisableButton8", TEXT("ItemWindow/ItemWindowButton4.png"));
	m_DisEnableButton8->SetTexture(EButtonState::Hovered, "InventoryDisableButton8", TEXT("ItemWindow/ItemWindowButton4.png"));
	m_DisEnableButton8->SetTexture(EButtonState::Disable, "InventoryDisableButton8", TEXT("ItemWindow/ItemWindowButton4.png"));
	m_DisEnableButton8->ButtonEnable(false);

	m_DisEnableButton9 = CreateWidget<CUIButton>("InventoryDisableButton9");
	m_DisEnableButton9->SetImageTint(EButtonState::Disable, 255, 255, 255, 255);
	m_DisEnableButton9->SetSize(29.f, 28.f);
	m_DisEnableButton9->SetPos(829.f, 208.f);
	m_DisEnableButton9->SetTexture(EButtonState::Click, "InventoryDisableButton9", TEXT("ItemWindow/ItemWindowButton5.png"));
	m_DisEnableButton9->SetTexture(EButtonState::Normal, "InventoryDisableButton9", TEXT("ItemWindow/ItemWindowButton5.png"));
	m_DisEnableButton9->SetTexture(EButtonState::Hovered, "InventoryDisableButton9", TEXT("ItemWindow/ItemWindowButton5.png"));
	m_DisEnableButton9->SetTexture(EButtonState::Disable, "InventoryDisableButton9", TEXT("ItemWindow/ItemWindowButton5.png"));
	m_DisEnableButton9->ButtonEnable(false);

	m_DisEnableButton10 = CreateWidget<CUIButton>("InventoryDisableButton10");
	m_DisEnableButton10->SetImageTint(EButtonState::Disable, 255, 255, 255, 255);
	m_DisEnableButton10->SetSize(28.f, 28.f);
	m_DisEnableButton10->SetPos(859.f, 208.f);
	m_DisEnableButton10->SetTexture(EButtonState::Click, "InventoryDisableButton10", TEXT("ItemWindow/ItemWindowButton6.png"));
	m_DisEnableButton10->SetTexture(EButtonState::Normal, "InventoryDisableButton10", TEXT("ItemWindow/ItemWindowButton6.png"));
	m_DisEnableButton10->SetTexture(EButtonState::Hovered, "InventoryDisableButton10", TEXT("ItemWindow/ItemWindowButton6.png"));
	m_DisEnableButton10->SetTexture(EButtonState::Disable, "InventoryDisableButton10", TEXT("ItemWindow/ItemWindowButton6.png"));
	m_DisEnableButton10->ButtonEnable(false);
}

void CInventoryUI::Weapon1EquipButton()
{	
	++m_DoubleClick;

	if (m_DoubleClick > 1)
	{
		m_Weapon1->SetEnable(false);
		EquipWeapon1 = true;

		if (EquipWeapon2)
			EquipWeapon2 = false;

		m_Player->SetWeapon(false);
		m_Player->SetWeapon1(true);
		m_Player->SetWeapon2(false);
		m_Player->SetAnimation("PlayerWeaponStand");
	
	}
	
}

void CInventoryUI::Weapon2EquipButton()
{

	++m_DoubleClick;

	if (m_DoubleClick > 1)
	{
		m_Weapon2->SetEnable(false);
		EquipWeapon2 = true;

		if (EquipWeapon1)
			EquipWeapon1 = false;		

		m_Player->SetWeapon2(true);		
		m_Player->SetWeapon1(false);
		m_Player->SetWeapon(false);
		m_Player->SetAnimation("PlayerWeapon1Stand");
	}


}

void CInventoryUI::UseItemEnable()
{
	m_UseInv = true;

	if (m_UseInv)
	{
		m_HpPotionImage->SetEnable(true);
		m_MpPotionImage->SetEnable(true);
		m_HpPotionNumber->SetEnable(true);
		m_MpPotionNumber->SetEnable(true);
	}

	m_EquipInv = false;
	m_EquipButton->ButtonEnable(false);
	m_UseButton->ButtonEnable(true);
}

void CInventoryUI::EquipItemEnable()
{
	m_EquipInv = true;

	if (m_EquipInv)
	{
		if(!EquipWeapon1 && m_Player->GetFrontQuestOn())
		m_Weapon1->SetEnable(true);

		if(!EquipWeapon2 && m_Player->GetSkill2Lock())
		m_Weapon2->SetEnable(true);
	}

	m_UseInv = false;
	m_UseButton->ButtonEnable(false);
	m_EquipButton->ButtonEnable(true);
}
