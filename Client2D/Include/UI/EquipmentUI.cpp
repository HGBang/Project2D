#include "EquipmentUI.h"
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
#include "InventoryUI.h"


CEquipmentUI::CEquipmentUI()
{
	m_WindowTypeName = "EquipmentUI";
}

CEquipmentUI::CEquipmentUI(const CEquipmentUI& Window) :
	CUIWindow(Window)
{
	m_DragButton = FindWidget<CUIButton>("DragButton");
	m_EquipBackImage1 = FindWidget<CUIImage>("EquipBackImage1");
	m_EquipBackImage2 = FindWidget<CUIImage>("EquipBackImage2");
	m_EquipBackImage3 = FindWidget<CUIImage>("EquipBackImage3");
	m_EquipBackLineImage = FindWidget<CUIImage>("EquipBackLineImage");
	m_EquipBackEquipButtonImage = FindWidget<CUIImage>("EquipBackEquipButtonImage");
	m_EquipBackCashButtonImage = FindWidget<CUIImage>("EquipBackCashButtonImage");
	m_EquipBackPetButtonImage = FindWidget<CUIImage>("EquipBackPetButtonImage");
	m_EquipBackADButtonImage = FindWidget<CUIImage>("EquipBackADButtonImage");
	m_EquipBackCheckBoxImage = FindWidget<CUIImage>("EquipBackCheckBoxImage");
	m_EquipCapButtonImage = FindWidget<CUIImage>("EquipCapButtonImage");
	m_EquipClothButtonImage = FindWidget<CUIImage>("EquipClothButtonImage");
	m_EquipPantsButtonImage = FindWidget<CUIImage>("EquipPantsButtonImage");
	m_EquipShoesButtonImage = FindWidget<CUIImage>("EquipShoesButtonImage");
	m_EquipWeaponButtonImage = FindWidget<CUIImage>("EquipWeaponButtonImage");
	m_EquipClothImage = FindWidget<CUIButton>("EquipClothImage");
	m_EquipCapImage = FindWidget<CUIButton>("EquipCapImage");
	m_EquipWeapon1Button = FindWidget<CUIButton>("EquipWeapon1Button");
	m_EquipWeapon2Button = FindWidget<CUIButton>("EquipWeapon2Button");
	m_EquipWeapon1Image = FindWidget<CUIImage>("EquipmentWeapon1Image");
	m_EquipWeapon2Image = FindWidget<CUIImage>("EquipmentWeapon2Image");
	m_EquipCapInfoImage = FindWidget<CUIImage>("CapInfoImage");
	m_EquipClothInfoImage = FindWidget<CUIImage>("ClothInfoImage");
}

CEquipmentUI::~CEquipmentUI()
{
}

void CEquipmentUI::Start()
{
	CUIWindow::Start();
	m_EquipWeapon1Button->SetCallback(EButtonEventState::Click, this, &CEquipmentUI::Weapon1EquipOffButton);
	m_EquipWeapon2Button->SetCallback(EButtonEventState::Click, this, &CEquipmentUI::Weapon2EquipOffButton);
	
}

bool CEquipmentUI::Init()
{
	CUIWindow::Init();

	

	m_DragButton = CreateWidget<CUIButton>("DragButton");
	m_DragButton->SetSize(100.f, 25.f);
	m_DragButton->SetPos(560.f, 630.f);
	m_DragButton->SetOpacity(0.f);


	m_EquipBackImage1 = CreateWidget<CUIImage>("EquipBackImage1");
	m_EquipBackImage1->SetSize(232.f, 354.f);
	m_EquipBackImage1->SetPos(500.f, 300.f);
	m_EquipBackImage1->SetTexture("EquipBackImage1", TEXT("EquipWindow/EquipWindowBack1.png"));

	m_EquipBackImage2 = CreateWidget<CUIImage>("EquipBackImage2");
	m_EquipBackImage2->SetSize(214.f, 256.f);
	m_EquipBackImage2->SetPos(509.f, 353.f);
	m_EquipBackImage2->SetTexture("EquipBackImage2", TEXT("EquipWindow/EquipWindowBack2.png"));

	m_EquipBackImage3 = CreateWidget<CUIImage>("EquipBackImage3");
	m_EquipBackImage3->SetSize(127.f, 209.f);
	m_EquipBackImage3->SetPos(555.f, 373.f);
	m_EquipBackImage3->SetTexture("EquipBackImage3", TEXT("EquipWindow/EquipWindowChBack.png"));

	m_EquipBackLineImage = CreateWidget<CUIImage>("EquipBackLineImage");
	m_EquipBackLineImage->SetSize(218.f, 4.f);
	m_EquipBackLineImage->SetPos(507.f, 608.f);
	m_EquipBackLineImage->SetTexture("EquipBackLineImage", TEXT("EquipWindow/EquipWindowLine.png"));

	m_EquipBackEquipButtonImage = CreateWidget<CUIImage>("EquipBackEquipButtonImage");
	m_EquipBackEquipButtonImage->SetSize(42.f, 22.f);
	m_EquipBackEquipButtonImage->SetPos(507.f, 612.f);
	m_EquipBackEquipButtonImage->SetTexture("EquipBackEquipButtonImage", TEXT("EquipWindow/EquipWindowEquipButton.png"));

	m_EquipBackCashButtonImage = CreateWidget<CUIImage>("EquipBackCashButtonImage");
	m_EquipBackCashButtonImage->SetSize(42.f, 20.f);
	m_EquipBackCashButtonImage->SetPos(550.f, 612.f);
	m_EquipBackCashButtonImage->SetTexture("EquipBackCashButtonImage", TEXT("EquipWindow/EquipWindowCashButton.png"));

	m_EquipBackPetButtonImage = CreateWidget<CUIImage>("EquipBackPetButtonImage");
	m_EquipBackPetButtonImage->SetSize(42.f, 20.f);
	m_EquipBackPetButtonImage->SetPos(593.f, 612.f);
	m_EquipBackPetButtonImage->SetTexture("EquipBackPetButtonImage", TEXT("EquipWindow/EquipWindowPetButton.png"));

	m_EquipBackADButtonImage = CreateWidget<CUIImage>("EquipBackADButtonImage");
	m_EquipBackADButtonImage->SetSize(42.f, 20.f);
	m_EquipBackADButtonImage->SetPos(636.f, 612.f);
	m_EquipBackADButtonImage->SetTexture("EquipBackADButtonImage", TEXT("EquipWindow/EquipWindowADButton.png"));

	m_EquipBackCheckBoxImage = CreateWidget<CUIImage>("EquipBackCheckBoxImage");
	m_EquipBackCheckBoxImage->SetSize(212.f, 18.f);
	m_EquipBackCheckBoxImage->SetPos(510.f, 310.f);
	m_EquipBackCheckBoxImage->SetTexture("EquipBackCheckBoxImage", TEXT("EquipWindow/EquipWindowTitle.png"));

	m_EquipCapButtonImage = CreateWidget<CUIImage>("EquipCapButtonImage");
	m_EquipCapButtonImage->SetSize(40.f, 39.f);
	m_EquipCapButtonImage->SetPos(600.f, 475.f);
	m_EquipCapButtonImage->SetTexture("EquipCapButtonImage", TEXT("EquipWindow/EquipCapButton.png"));

	m_EquipClothButtonImage = CreateWidget<CUIImage>("EquipClothButtonImage");
	m_EquipClothButtonImage->SetSize(40.f, 39.f);
	m_EquipClothButtonImage->SetPos(600.f, 430.f);
	m_EquipClothButtonImage->SetTexture("EquipClothButtonImage", TEXT("EquipWindow/EquipClothButton.png"));

	m_EquipPantsButtonImage = CreateWidget<CUIImage>("EquipPantsButtonImage");
	m_EquipPantsButtonImage->SetSize(40.f, 39.f);
	m_EquipPantsButtonImage->SetPos(600.f, 390.f);
	m_EquipPantsButtonImage->SetTexture("EquipPantsButtonImage", TEXT("EquipWindow/EquipPantsButton.png"));

	m_EquipShoesButtonImage = CreateWidget<CUIImage>("EquipShoesButtonImage");
	m_EquipShoesButtonImage->SetSize(40.f, 39.f);
	m_EquipShoesButtonImage->SetPos(640.f, 390.f);
	m_EquipShoesButtonImage->SetTexture("EquipShoesButtonImage", TEXT("EquipWindow/EquipShoesButton.png"));

	m_EquipWeaponButtonImage = CreateWidget<CUIImage>("EquipWeaponButtonImage");
	m_EquipWeaponButtonImage->SetSize(40.f, 39.f);
	m_EquipWeaponButtonImage->SetPos(560.f, 430.f);
	m_EquipWeaponButtonImage->SetTexture("EquipWeaponButtonImage", TEXT("EquipWindow/EquipWeaponButton.png"));

	m_EquipClothImage = CreateWidget<CUIButton>("EquipClothImage");
	m_EquipClothImage->SetSize(30.f, 28.f);
	m_EquipClothImage->SetPos(605.f, 435.f);
	m_EquipClothImage->SetTexture(EButtonState::Normal, "EquipClothImage", TEXT("EquipWindow/ClothImage.png"));
	m_EquipClothImage->SetTexture(EButtonState::Click, "EquipClothImage", TEXT("EquipWindow/ClothImage.png"));
	m_EquipClothImage->SetTexture(EButtonState::Hovered, "EquipClothImage", TEXT("EquipWindow/ClothImage.png"));

	m_EquipCapImage = CreateWidget<CUIButton>("EquipCapImage");
	m_EquipCapImage->SetSize(34.f, 28.f);
	m_EquipCapImage->SetPos(605.f, 480.f);
	m_EquipCapImage->SetTexture(EButtonState::Normal, "EquipCapImage", TEXT("EquipWindow/CapImage.png"));
	m_EquipCapImage->SetTexture(EButtonState::Click, "EquipCapImage", TEXT("EquipWindow/CapImage.png"));
	m_EquipCapImage->SetTexture(EButtonState::Hovered, "EquipCapImage", TEXT("EquipWindow/CapImage.png"));

	m_EquipWeapon1Button = CreateWidget<CUIButton>("EquipWeapon1Button");
	m_EquipWeapon1Button->SetSize(35.f, 35.f);
	m_EquipWeapon1Button->SetPos(565.f, 435.f);
	m_EquipWeapon1Button->SetTexture(EButtonState::Normal, "EquipWeapon1", TEXT("EquipWindow/Weapon1Inv.png"));
	m_EquipWeapon1Button->SetTexture(EButtonState::Click, "EquipWeapon1", TEXT("EquipWindow/Weapon1Inv.png"));
	m_EquipWeapon1Button->SetTexture(EButtonState::Hovered, "EquipWeapon1", TEXT("EquipWindow/Weapon1Inv.png"));
	m_EquipWeapon1Button->SetTexture(EButtonState::Disable, "EquipWeapon1", TEXT("EquipWindow/Weapon1Inv.png"));
	m_EquipWeapon1Button->SetCallback(EButtonEventState::Click, this, &CEquipmentUI::Weapon1EquipOffButton);
	m_EquipWeapon1Button->SetOpacity(0.f);
	m_EquipWeapon1Button->SetEnable(false);

	m_EquipWeapon2Button = CreateWidget<CUIButton>("EquipWeapon2Button");
	m_EquipWeapon2Button->SetSize(37.f, 36.f);
	m_EquipWeapon2Button->SetPos(562.f, 434.f);
	m_EquipWeapon2Button->SetTexture(EButtonState::Normal, "EquipWeapon2", TEXT("EquipWindow/Weapon2Inv.png"));
	m_EquipWeapon2Button->SetTexture(EButtonState::Click, "EquipWeapon2", TEXT("EquipWindow/Weapon2Inv.png"));
	m_EquipWeapon2Button->SetTexture(EButtonState::Hovered, "EquipWeapon2", TEXT("EquipWindow/Weapon2Inv.png"));
	m_EquipWeapon2Button->SetTexture(EButtonState::Disable, "EquipWeapon2", TEXT("EquipWindow/Weapon2Inv.png"));
	m_EquipWeapon2Button->SetCallback(EButtonEventState::Click, this, &CEquipmentUI::Weapon2EquipOffButton);
	m_EquipWeapon2Button->SetOpacity(0.f);
	m_EquipWeapon2Button->SetEnable(false);


	if (m_Scene)
		m_ItemUI = m_Scene->GetViewport()->FindUIWindow<CInventoryUI>("InventoryUI");

	else
		m_ItemUI = CSceneManager::GetInst()->GetScene()->GetViewport()->FindUIWindow<CInventoryUI>("InventoryUI");

	m_EquipWeapon1Image = CreateWidget<CUIImage>("EquipmentWeapon1Image");
	m_EquipWeapon1Image->SetSize(260.f, 324.f);
	m_EquipWeapon1Image->SetPos(300.f, 300.f);
	m_EquipWeapon1Image->SetTexture("Weapon1Image", TEXT("Weapon1Image.png"));
	m_EquipWeapon1Image->SetOpacity(0.f);

	m_EquipWeapon2Image = CreateWidget<CUIImage>("EquipmentWeapon2Image");
	m_EquipWeapon2Image->SetSize(259.f, 312.f);
	m_EquipWeapon2Image->SetPos(300.f, 300.f);
	m_EquipWeapon2Image->SetTexture("Weapon2Image", TEXT("Weapon2Image.png"));
	m_EquipWeapon2Image->SetOpacity(0.f);

	m_EquipCapInfoImage = CreateWidget<CUIImage>("CapInfoImage");
	m_EquipCapInfoImage->SetSize(261.f, 294.f);
	m_EquipCapInfoImage->SetPos(300.f, 300.f);
	m_EquipCapInfoImage->SetTexture("CapInfoImage", TEXT("EquipCapInfo.png"));
	m_EquipCapInfoImage->SetOpacity(0.f);

	m_EquipClothInfoImage = CreateWidget<CUIImage>("ClothInfoImage");
	m_EquipClothInfoImage->SetSize(261.f, 294.f);
	m_EquipClothInfoImage->SetPos(300.f, 300.f);
	m_EquipClothInfoImage->SetTexture("ClothInfoImage", TEXT("EquipClothInfo.png"));
	m_EquipClothInfoImage->SetOpacity(0.f);


	return true;
}

void CEquipmentUI::Update(float DeltaTime)
{
	CUIWindow::Update(DeltaTime);	

	// 인벤토리 드래그 처리 

	Vector2 WorldPos = CInput::GetInst()->GetMousePos();

	if (m_DragButton)
	{
		if (m_DragButton->GetButtonState() == EButtonState::Normal || m_DragButton->GetButtonState() == EButtonState::Hovered)
		{
			m_Drag = false;
		}

		if (m_DragButton->GetButtonState() == EButtonState::Click)
		{
			m_Drag = true;
		}
	}

	if(m_Drag)
	m_Pos = Vector2(WorldPos.x -615.f, WorldPos.y - 645.f);

	if (m_ItemUI->GetEquipWeapon1())
	{
		m_EquipWeapon1Button->SetEnable(true);
		m_EquipWeapon1Button->SetOpacity(1.f);		
	}

	if (m_ItemUI->GetEquipWeapon2())
	{
		m_EquipWeapon2Button->SetEnable(true);
		m_EquipWeapon2Button->SetOpacity(1.f);		
	}

	m_DoubleClickTime += DeltaTime;

	if (m_DoubleClickTime > 0.7f)
	{
		m_DoubleClick = 0;
		m_DoubleClickTime = 0.f;
	}


	if (m_EquipWeapon1Button->GetButtonState() == EButtonState::Hovered && m_EquipWeapon1Button->GetEnable())
	{
		m_EquipWeapon1Image->SetOpacity(1.f);
		m_EquipWeapon1Image->SetPos(Vector2(m_Pos.x * 0.1f + 550.f, m_Pos.y * 0.1f + 120.f));
	}

	if (m_EquipWeapon1Button->GetButtonState() == EButtonState::Normal || !m_EquipWeapon1Button->GetEnable())
	{
		m_EquipWeapon1Image->SetOpacity(0.f);
	}

	if (m_EquipWeapon2Button->GetButtonState() == EButtonState::Hovered && m_EquipWeapon2Button->GetEnable())
	{
		m_EquipWeapon2Image->SetOpacity(1.f);
		m_EquipWeapon2Image->SetPos(Vector2(m_Pos.x * 0.1f + 550.f, m_Pos.y * 0.1f + 120.f));
	}

	if (m_EquipWeapon2Button->GetButtonState() == EButtonState::Normal ||  !m_EquipWeapon2Button->GetEnable())
	{
		m_EquipWeapon2Image->SetOpacity(0.f);
	}

	if (m_EquipCapImage->GetButtonState() == EButtonState::Hovered)
	{
		m_EquipCapInfoImage->SetOpacity(1.f);
		m_EquipCapInfoImage->SetPos(Vector2(m_Pos.x * 0.1f + 550.f, m_Pos.y * 0.1f + 200.f));
	}

	if (m_EquipCapImage->GetButtonState() == EButtonState::Normal)
	{
		m_EquipCapInfoImage->SetOpacity(0.f);
	}

	if (m_EquipClothImage->GetButtonState() == EButtonState::Hovered)
	{
		m_EquipClothInfoImage->SetOpacity(1.f);
		m_EquipClothInfoImage->SetPos(Vector2(m_Pos.x * 0.1f + 550.f, m_Pos.y * 0.1f + 160.f));
	}

	if (m_EquipClothImage->GetButtonState() == EButtonState::Normal)
	{
		m_EquipClothInfoImage->SetOpacity(0.f);
	}


}

void CEquipmentUI::PostUpdate(float DeltaTime)
{
	CUIWindow::PostUpdate(DeltaTime);
}

void CEquipmentUI::Render()
{
	CUIWindow::Render();
}

CEquipmentUI* CEquipmentUI::Clone()
{
	return new CEquipmentUI(*this);
}

void CEquipmentUI::Save(FILE* File)
{
	CUIWindow::Save(File);
}

void CEquipmentUI::Load(FILE* File)
{
	CUIWindow::Load(File);
	m_DragButton = FindWidget<CUIButton>("DragButton");
	m_EquipBackImage1 = FindWidget<CUIImage>("EquipBackImage1");
	m_EquipBackImage2 = FindWidget<CUIImage>("EquipBackImage2");
	m_EquipBackImage3 = FindWidget<CUIImage>("EquipBackImage3");
	m_EquipBackLineImage = FindWidget<CUIImage>("EquipBackLineImage");
	m_EquipBackEquipButtonImage = FindWidget<CUIImage>("EquipBackEquipButtonImage");
	m_EquipBackCashButtonImage = FindWidget<CUIImage>("EquipBackCashButtonImage");
	m_EquipBackPetButtonImage = FindWidget<CUIImage>("EquipBackPetButtonImage");
	m_EquipBackADButtonImage = FindWidget<CUIImage>("EquipBackADButtonImage");
	m_EquipBackCheckBoxImage = FindWidget<CUIImage>("EquipBackCheckBoxImage");
	m_EquipCapButtonImage = FindWidget<CUIImage>("EquipCapButtonImage");
	m_EquipClothButtonImage = FindWidget<CUIImage>("EquipClothButtonImage");
	m_EquipPantsButtonImage = FindWidget<CUIImage>("EquipPantsButtonImage");
	m_EquipShoesButtonImage = FindWidget<CUIImage>("EquipShoesButtonImage");
	m_EquipWeaponButtonImage = FindWidget<CUIImage>("EquipWeaponButtonImage");
	m_EquipClothImage = FindWidget<CUIButton>("EquipClothImage");
	m_EquipCapImage = FindWidget<CUIButton>("EquipCapImage");
	m_EquipWeapon1Button = FindWidget<CUIButton>("EquipWeapon1Button");
	m_EquipWeapon2Button = FindWidget<CUIButton>("EquipWeapon2Button");
	m_EquipWeapon1Image = FindWidget<CUIImage>("EquipmentWeapon1Image");
	m_EquipWeapon2Image = FindWidget<CUIImage>("EquipmentWeapon2Image");
	m_EquipCapInfoImage = FindWidget<CUIImage>("CapInfoImage");
	m_EquipClothInfoImage = FindWidget<CUIImage>("ClothInfoImage");


	if (m_Scene)
	{
		m_ItemUI = m_Scene->GetViewport()->FindUIWindow<CInventoryUI>("InventoryUI");
		m_Player = (CPlayer2D*)m_Scene->FindObject("Player2D");
	}

	else
	{
		m_ItemUI = CSceneManager::GetInst()->GetScene()->GetViewport()->FindUIWindow<CInventoryUI>("InventoryUI");
		m_Player = (CPlayer2D*)CSceneManager::GetInst()->GetScene()->FindObject("Player2D");
	}



}

void CEquipmentUI::Weapon1EquipOffButton()
{	

	++m_DoubleClick;

	if (m_DoubleClick > 1)
	{
		m_EquipWeapon1Button->SetEnable(false);

		m_ItemUI->SetEquipWeapon1(false);

		m_Player->SetAnimation("PlayerNormalStand");

		m_Player->SetWeapon1(false);
		
	}
}


void CEquipmentUI::Weapon2EquipOffButton()
{

	++m_DoubleClick;

	if (m_DoubleClick > 1)
	{
		m_EquipWeapon2Button->SetEnable(false);

		m_ItemUI->SetEquipWeapon2(false);

		m_Player->SetAnimation("PlayerNormalStand");

		m_Player->SetWeapon2(false);		
	}

}