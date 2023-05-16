#include "ShopUI.h"
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
#include "UI/UIShopText.h"

CShopUI::CShopUI()
{
	m_WindowTypeName = "ShopUI";
}

CShopUI::CShopUI(const CShopUI& Window) :
	CUIWindow(Window)
{
	m_ShopBackImage1 = FindWidget<CUIImage>("ShopBackImage1");
	m_ShopBackImage2 = FindWidget<CUIImage>("ShopBackImage2");
	m_ShopBackImage3 = FindWidget<CUIImage>("ShopBackImage3");
	m_ShopRedButton = FindWidget<CUIButton>("ShopRedButton");
	m_ShopBlueButton = FindWidget<CUIButton>("ShopBlueButton");
	m_ShopRedPotionSelect = FindWidget<CUIImage>("ShopRedPotionSelect");
	m_ShopBluePotionSelect = FindWidget<CUIImage>("ShopBluePotionSelect");
	m_RedPotionImage = FindWidget<CUIImage>("ShopRedPotionImage");
	m_BluePotionImage = FindWidget<CUIImage>("ShopBluePotionImage");
	m_RedPotionText = FindWidget<CUIText>("RedPotionText");
	m_BluePotionText = FindWidget<CUIText>("BluePotionText");
	m_ShopNpcImage = FindWidget<CUIImage>("ShopTopNpcImage");
	m_ShopPlayerImage = FindWidget<CUIImage>("ShopPlayerImage");
	m_ShopCategoryImage = FindWidget<CUIImage>("ShopCategoryImage");
	m_PlayerCategoryImage = FindWidget<CUIImage>("PlayerCategoryImage");
	m_RedPotionNumber = FindWidget<CUINumber>("ShopHpPotionNumber");
	m_BluePotionNumber = FindWidget<CUINumber>("ShopMpPotionNumber");
	m_BuyButton = FindWidget<CUIButton>("ShopBuyButton");
	m_CloseButton = FindWidget<CUIButton>("ShopCloseButton");
	m_BuyBackImage = FindWidget<CUIImage>("ShopBuyBackImage");
	m_BuyText = FindWidget<CUIText>("ShopBuyText");
	m_RealBuyButton = FindWidget<CUIButton>("ShopRealBuyButton");
	m_RealCloseButton = FindWidget<CUIButton>("ShopRealCancelButton");
	m_ShopText = FindWidget<CUIShopText>("ShopText");

}

CShopUI::~CShopUI()
{
}

void CShopUI::Start()
{
	CUIWindow::Start();

	CSceneManager::GetInst()->GetScene()->GetResource()->LoadSound("Effect", "BuyShopItem", false, "BuyShopItem.mp3");

	m_ShopBlueButton->SetCallback(EButtonEventState::Click, this, &CShopUI::BluePotionClick);
	m_ShopRedButton->SetCallback(EButtonEventState::Click, this, &CShopUI::RedPotionClick);
	m_BuyButton->SetCallback(EButtonEventState::Click, this, &CShopUI::BuyButtonClick);
	m_CloseButton->SetCallback(EButtonEventState::Click, this, &CShopUI::CloseButtonClick);

	m_RealBuyButton->SetCallback(EButtonEventState::Click, this, &CShopUI::RealBuyButtonClick);
	m_RealCloseButton->SetCallback(EButtonEventState::Click, this, &CShopUI::RealCloseButtonClick);

	SetEnable(false);
}

bool CShopUI::Init()
{

	m_ShopBackImage1 = CreateWidget<CUIImage>("ShopBackImage1");
	m_ShopBackImage1->SetSize(465.f, 328.f);
	m_ShopBackImage1->SetPos(450.f, 250.f);
	m_ShopBackImage1->SetTexture("ShopBackImage1", TEXT("MapleShop/MapleShopBack.png"));

	m_ShopBackImage2 = CreateWidget<CUIImage>("ShopBackImage2");
	m_ShopBackImage2->SetSize(453.f, 317.f);
	m_ShopBackImage2->SetPos(455.f, 257.f);
	m_ShopBackImage2->SetTexture("ShopBackImage2", TEXT("MapleShop/MapleShopMain.png"));

	m_ShopBackImage3 = CreateWidget<CUIImage>("ShopBackImage3");
	m_ShopBackImage3->SetSize(451.f, 254.f);
	m_ShopBackImage3->SetPos(456.f, 262.f);
	m_ShopBackImage3->SetTexture("ShopBackImage3", TEXT("MapleShop/MapleShopMain2.png"));

	m_ShopRedButton = CreateWidget<CUIButton>("ShopRedButton");
	m_ShopRedButton->SetSize(160.f, 30.f);
	m_ShopRedButton->SetPos(500.f, 432.f);
	m_ShopRedButton->SetOpacity(0.f);

	m_ShopBlueButton = CreateWidget<CUIButton>("ShopBlueButton");
	m_ShopBlueButton->SetSize(160.f, 30.f);
	m_ShopBlueButton->SetPos(500.f, 390.f);	
	m_ShopBlueButton->SetOpacity(0.f);

	
	m_ShopRedPotionSelect = CreateWidget<CUIImage>("ShopRedPotionSelect");
	m_ShopRedPotionSelect->SetSize(165.f, 35.f);
	m_ShopRedPotionSelect->SetPos(496.f, 430.f);
	m_ShopRedPotionSelect->SetTexture("RedPotionSelect", TEXT("MapleShop/MapleShopSelect.png"));
	m_ShopRedPotionSelect->SetEnable(false);

	m_ShopBluePotionSelect = CreateWidget<CUIImage>("ShopBluePotionSelect");
	m_ShopBluePotionSelect->SetSize(165.f, 35.f);
	m_ShopBluePotionSelect->SetPos(496.f, 388.f);
	m_ShopBluePotionSelect->SetTexture("BluePotionSelect", TEXT("MapleShop/MapleShopSelect.png"));
	m_ShopBluePotionSelect->SetEnable(false);

	m_RedPotionImage = CreateWidget<CUIImage>("ShopRedPotionImage");
	m_RedPotionImage->SetSize(27.f, 27.f);
	m_RedPotionImage->SetPos(462.f, 432.f);
	m_RedPotionImage->SetTexture("ShopRedPotionImage", TEXT("MapleShop/RedPotion.png"));

	m_BluePotionImage = CreateWidget<CUIImage>("ShopBluePotionImage");
	m_BluePotionImage->SetSize(27.f, 27.f);
	m_BluePotionImage->SetPos(462.f, 390.f);
	m_BluePotionImage->SetTexture("ShopBluePotionImage", TEXT("MapleShop/BluePotion.png"));

	m_RedPotionText = CreateWidget<CUIText>("RedPotionText");
	m_RedPotionText->SetFont("Default");
	m_RedPotionText->SetFontSize(10.f);
	m_RedPotionText->SetPos(500.f, 435.f);
	m_RedPotionText->SetSize(100.f, 30.f);
	m_RedPotionText->SetColor(0, 0, 0);
	m_RedPotionText->SetText(TEXT("빨간 포션"));

	m_BluePotionText = CreateWidget<CUIText>("BluePotionText");
	m_BluePotionText->SetFont("Default");
	m_BluePotionText->SetFontSize(10.f);
	m_BluePotionText->SetPos(500.f, 393.f);
	m_BluePotionText->SetSize(100.f, 30.f);
	m_BluePotionText->SetColor(0, 0, 0);
	m_BluePotionText->SetText(TEXT("파란 포션"));

	CUIImage* MesoImage = CreateWidget<CUIImage>("MesoImage");
	MesoImage->SetSize(12.f, 12.f);
	MesoImage->SetPos(500.f, 433.f);
	MesoImage->SetTexture("MesoImage", TEXT("MapleShop/ShopMesoImage.png"));

	MesoImage = CreateWidget<CUIImage>("MesoImage1");
	MesoImage->SetSize(12.f, 12.f);
	MesoImage->SetPos(500.f, 393.f);
	MesoImage->SetTexture("MesoImage1", TEXT("MapleShop/ShopMesoImage.png"));

	CUIText* MesoText = CreateWidget<CUIText>("MesoText");
	MesoText->SetFont("Default");
	MesoText->SetFontSize(10.f);
	MesoText->SetPos(520.f, 417.f);
	MesoText->SetSize(100.f, 30.f);
	MesoText->SetColor(0, 0, 0);
	MesoText->SetText(TEXT("0 메소"));

	MesoText = CreateWidget<CUIText>("MesoText1");
	MesoText->SetFont("Default");
	MesoText->SetFontSize(10.f);
	MesoText->SetPos(520.f, 377.f);
	MesoText->SetSize(100.f, 30.f);
	MesoText->SetColor(0, 0, 0);
	MesoText->SetText(TEXT("0 메소"));

	m_ShopNpcImage = CreateWidget<CUIImage>("ShopTopNpcImage");
	m_ShopNpcImage->SetSize(60.f,72.f);
	m_ShopNpcImage->SetPos(480.f, 500.f);
	m_ShopNpcImage->SetTexture("ShopTopNpcImage", TEXT("MapleShop/MapleShopNpc1.png"));

	m_ShopPlayerImage = CreateWidget<CUIImage>("ShopPlayerImage");
	m_ShopPlayerImage->SetSize(61.f, 71.f);
	m_ShopPlayerImage->SetPos(710.f, 500.f);
	m_ShopPlayerImage->SetTexture("ShopPlayerImage", TEXT("MapleShop/PlayerNormalStand0.png"));

	m_ShopCategoryImage = CreateWidget<CUIImage>("ShopCategoryImage");
	m_ShopCategoryImage->SetSize(42.f, 19.f);
	m_ShopCategoryImage->SetPos(457.f, 470.f);
	m_ShopCategoryImage->SetTexture("ShopCategoryImage", TEXT("MapleShop/MapleShopEvery.png"));

	m_PlayerCategoryImage = CreateWidget<CUIImage>("PlayerCategoryImage");
	m_PlayerCategoryImage->SetSize(42.f, 19.f);
	m_PlayerCategoryImage->SetPos(690.f, 470.f);
	m_PlayerCategoryImage->SetTexture("PlayerCategoryImage", TEXT("MapleShop/MapleShopUse.png"));

	class CUIImage* PlayerRedPotion = CreateWidget<CUIImage>("PlayerShopRedPotionImage");
	PlayerRedPotion->SetSize(27.f, 30.f);
	PlayerRedPotion->SetPos(693.f, 433.f);
	PlayerRedPotion->SetTexture("PlayerShopRedPotionImage", TEXT("MapleShop/RedPotion.png"));

	PlayerRedPotion = CreateWidget<CUIImage>("PlayerShopBluePotionImage");
	PlayerRedPotion->SetSize(27.f, 30.f);
	PlayerRedPotion->SetPos(693.f, 390.f);
	PlayerRedPotion->SetTexture("PlayerShopBluePotionImage", TEXT("MapleShop/BluePotion.png"));


	std::vector<const TCHAR*>	vecFileNames;

	for (int i = 0; i < 10; ++i)
	{
		TCHAR* FileName = new TCHAR[MAX_PATH];

		memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);

		wsprintf(FileName, TEXT("Item_Number/Item_Number%d.png"), i);

		vecFileNames.push_back(FileName);
	}

	m_RedPotionNumber = CreateWidget<CUINumber>("ShopHpPotionNumber");
	m_RedPotionNumber->SetPos(693.f, 433.f);
	m_RedPotionNumber->SetSize(8.f, 11.f);
	m_RedPotionNumber->SetNumber(0);
	m_RedPotionNumber->SetTexture("ShopHpPotionNumber", vecFileNames);

	m_BluePotionNumber = CreateWidget<CUINumber>("ShopMpPotionNumber");
	m_BluePotionNumber->SetPos(693.f, 390.f);
	m_BluePotionNumber->SetSize(8.f, 11.f);
	m_BluePotionNumber->SetNumber(0);
	m_BluePotionNumber->SetTexture("ShopMpPotionNumber", vecFileNames);

	for (int i = 0; i < 10; ++i)
	{
		m_RedPotionNumber->AddFrameData(Vector2(0.f, 0.f), Vector2(8.f, 11.f));
		m_BluePotionNumber->AddFrameData(Vector2(0.f, 0.f), Vector2(8.f, 11.f));
	}

	size_t Size = vecFileNames.size();

	for (size_t i = 0; i < Size; ++i)
	{
		SAFE_DELETE(vecFileNames[i]);
	}


	class CUIText* PlayerMesoText = CreateWidget<CUIText>("PlayerMesoText");
	PlayerMesoText->SetPos(850.f, 488.f);
	PlayerMesoText->SetFont("Default");
	PlayerMesoText->SetFontSize(12.f);
	PlayerMesoText->SetSize(100.f, 30.f);
	PlayerMesoText->SetColor(0, 0, 0);
	PlayerMesoText->SetText(TEXT("100000"));


	m_BuyButton = CreateWidget<CUIButton>("ShopBuyButton");
	m_BuyButton->SetSize(64.f, 16.f);
	m_BuyButton->SetPos(610.f, 500.f);
	m_BuyButton->SetTexture(EButtonState::Normal, "ShopBuyButton_Normal", TEXT("MapleShop/ShopBuyButton_Normal.png"));
	m_BuyButton->SetTexture(EButtonState::Click, "ShopBuyButton_Click", TEXT("MapleShop/ShopBuyButton_Click.png"));
	m_BuyButton->SetTexture(EButtonState::Hovered, "ShopBuyButton_Hov", TEXT("MapleShop/ShopBuyButton_Hov.png"));

	m_CloseButton = CreateWidget<CUIButton>("ShopCloseButton");
	m_CloseButton->SetSize(64.f, 16.f);
	m_CloseButton->SetPos(610.f, 520.f);
	m_CloseButton->SetTexture(EButtonState::Normal, "ShopCloseButton_Normal", TEXT("MapleShop/ShopExitButton_Normal.png"));
	m_CloseButton->SetTexture(EButtonState::Click, "ShopCloseButton_Click", TEXT("MapleShop/ShopExitButton_Click.png"));
	m_CloseButton->SetTexture(EButtonState::Hovered, "ShopCloseButton_Hov", TEXT("MapleShop/ShopExitButton_Hov.png"));


	m_BuyBackImage = CreateWidget<CUIImage>("ShopBuyBackImage");
	m_BuyBackImage->SetSize(281.f, 154.f);
	m_BuyBackImage->SetPos(560.f, 350.f);
	m_BuyBackImage->SetTexture("ShopBuyBackImage", TEXT("ItemShopBuy/ItemBuyBack1.png"));
	m_BuyBackImage->SetEnable(false);

	
	m_BuyText = CreateWidget<CUIText>("ShopBuyText");
	m_BuyText->SetFont("Default");
	m_BuyText->SetPos(580.f, 440.f);
	m_BuyText->SetColor(255, 255, 255);
	m_BuyText->SetFontSize(11.f);
	m_BuyText->SetSize(200.f, 30.f);
	m_BuyText->SetText(TEXT("몇 개를 구매하시겠습니까 ?"));
	m_BuyText->SetEnable(false);

	m_RealBuyButton = CreateWidget<CUIButton>("ShopRealBuyButton");
	m_RealBuyButton->SetSize(40.f, 16.f);
	m_RealBuyButton->SetPos(700.f, 395.f);
	m_RealBuyButton->SetTexture(EButtonState::Normal, "ShopRealBuyButton_Normal", TEXT("ItemShopBuy/BuyButton_Normal.png"));
	m_RealBuyButton->SetTexture(EButtonState::Hovered, "ShopRealBuyButton_Hov", TEXT("ItemShopBuy/BuyButton_Hov.png"));
	m_RealBuyButton->SetTexture(EButtonState::Click, "ShopRealBuyButton_Click", TEXT("ItemShopBuy/BuyButton_Click.png"));
	m_RealBuyButton->SetEnable(false);

	m_RealCloseButton = CreateWidget<CUIButton>("ShopRealCancelButton");
	m_RealCloseButton->SetSize(40.f, 16.f);
	m_RealCloseButton->SetPos(750.f, 395.f);
	m_RealCloseButton->SetTexture(EButtonState::Normal, "ShopRealCancelButton_Normal", TEXT("ItemShopBuy/CancelButton_Normal.png"));
	m_RealCloseButton->SetTexture(EButtonState::Hovered, "ShopRealCancelButton_Hov", TEXT("ItemShopBuy/CancelButton_Hov.png"));
	m_RealCloseButton->SetTexture(EButtonState::Click, "ShopRealCancelButton_Click", TEXT("ItemShopBuy/CancelButton_Click.png"));
	m_RealCloseButton->SetEnable(false);

	m_ShopText = CreateWidget<CUIShopText>("ShopText");
	m_ShopText->SetSize(200.f, 30.f);
	m_ShopText->SetFont("Default");
	m_ShopText->SetFontSize(12.f);
	m_ShopText->SetPos(600.f, 403.f);
	m_ShopText->SetText(TEXT(""));
	m_ShopText->SetColor(0, 0, 0);
	m_ShopText->SetEnable(false);

	

	return true;
}

void CShopUI::Update(float DeltaTime)
{
	CUIWindow::Update(DeltaTime);
}

void CShopUI::PostUpdate(float DeltaTime)
{
	CUIWindow::PostUpdate(DeltaTime);
}

void CShopUI::Render()
{
	CUIWindow::Render();
}

CShopUI* CShopUI::Clone()
{
	return new CShopUI(*this);
}

void CShopUI::Save(FILE* File)
{
	CUIWindow::Save(File);
}

void CShopUI::Load(FILE* File)
{
	CUIWindow::Load(File);

	m_ShopBackImage1 = FindWidget<CUIImage>("ShopBackImage1");
	m_ShopBackImage2 = FindWidget<CUIImage>("ShopBackImage2");
	m_ShopBackImage3 = FindWidget<CUIImage>("ShopBackImage3");
	m_ShopRedButton = FindWidget<CUIButton>("ShopRedButton");
	m_ShopBlueButton = FindWidget<CUIButton>("ShopBlueButton");
	m_ShopRedPotionSelect = FindWidget<CUIImage>("ShopRedPotionSelect");
	m_ShopBluePotionSelect = FindWidget<CUIImage>("ShopBluePotionSelect");
	m_RedPotionImage = FindWidget<CUIImage>("ShopRedPotionImage");
	m_BluePotionImage = FindWidget<CUIImage>("ShopBluePotionImage");
	m_RedPotionText = FindWidget<CUIText>("RedPotionText");
	m_BluePotionText = FindWidget<CUIText>("BluePotionText");
	m_ShopNpcImage = FindWidget<CUIImage>("ShopTopNpcImage");
	m_ShopPlayerImage = FindWidget<CUIImage>("ShopPlayerImage");
	m_ShopCategoryImage = FindWidget<CUIImage>("ShopCategoryImage");
	m_PlayerCategoryImage = FindWidget<CUIImage>("PlayerCategoryImage");
	m_RedPotionNumber = FindWidget<CUINumber>("ShopHpPotionNumber");
	m_BluePotionNumber = FindWidget<CUINumber>("ShopMpPotionNumber");
	m_BuyButton = FindWidget<CUIButton>("ShopBuyButton");
	m_CloseButton = FindWidget<CUIButton>("ShopCloseButton");
	m_BuyBackImage = FindWidget<CUIImage>("ShopBuyBackImage");
	m_BuyText = FindWidget<CUIText>("ShopBuyText");
	m_RealBuyButton = FindWidget<CUIButton>("ShopRealBuyButton");
	m_RealCloseButton = FindWidget<CUIButton>("ShopRealCancelButton");
	m_ShopText = FindWidget<CUIShopText>("ShopText");

	CUIImage* MesoImage = CreateWidget<CUIImage>("MesoImage");
	MesoImage->SetSize(12.f, 12.f);
	MesoImage->SetPos(500.f, 433.f);
	MesoImage->SetTexture("MesoImage", TEXT("MapleShop/ShopMesoImage.png"));

	MesoImage = CreateWidget<CUIImage>("MesoImage1");
	MesoImage->SetSize(12.f, 12.f);
	MesoImage->SetPos(500.f, 393.f);
	MesoImage->SetTexture("MesoImage1", TEXT("MapleShop/ShopMesoImage.png"));

	CUIText* MesoText = CreateWidget<CUIText>("MesoText");
	MesoText->SetFont("Default");
	MesoText->SetFontSize(10.f);
	MesoText->SetPos(520.f, 417.f);
	MesoText->SetSize(100.f, 30.f);
	MesoText->SetColor(0, 0, 0);
	MesoText->SetText(TEXT("0 메소"));

	MesoText = CreateWidget<CUIText>("MesoText1");
	MesoText->SetFont("Default");
	MesoText->SetFontSize(10.f);
	MesoText->SetPos(520.f, 377.f);
	MesoText->SetSize(100.f, 30.f);
	MesoText->SetColor(0, 0, 0);
	MesoText->SetText(TEXT("0 메소"));

	class CUIImage* PlayerRedPotion = CreateWidget<CUIImage>("PlayerShopRedPotionImage");
	PlayerRedPotion->SetSize(27.f, 30.f);
	PlayerRedPotion->SetPos(693.f, 433.f);
	PlayerRedPotion->SetTexture("PlayerShopRedPotionImage", TEXT("MapleShop/RedPotion.png"));

	PlayerRedPotion = CreateWidget<CUIImage>("PlayerShopBluePotionImage");
	PlayerRedPotion->SetSize(27.f, 30.f);
	PlayerRedPotion->SetPos(693.f, 390.f);
	PlayerRedPotion->SetTexture("PlayerShopBluePotionImage", TEXT("MapleShop/BluePotion.png"));

	class CUIText* PlayerMesoText = CreateWidget<CUIText>("PlayerMesoText");
	PlayerMesoText->SetPos(850.f, 488.f);
	PlayerMesoText->SetFont("Default");
	PlayerMesoText->SetFontSize(12.f);
	PlayerMesoText->SetSize(100.f, 30.f);
	PlayerMesoText->SetColor(0, 0, 0);
	PlayerMesoText->SetText(TEXT("100000"));

}

void CShopUI::RedPotionClick()
{
	
	m_SelectRedPotion = true;
	m_ShopRedPotionSelect->SetEnable(true);

	if (m_SelectBluePotion)
	{
		m_SelectBluePotion = false;
		m_ShopBluePotionSelect->SetEnable(false);
	}
	
}

void CShopUI::BluePotionClick()
{
	m_SelectBluePotion = true;
	m_ShopBluePotionSelect->SetEnable(true);

	if (m_SelectBluePotion)
	{
		m_SelectRedPotion = false;
		m_ShopRedPotionSelect->SetEnable(false);
	}
}

void CShopUI::BuyButtonClick()
{
	CEngine::GetInst()->ClearText();

	m_BuyBackImage->SetEnable(true);
	m_BuyText->SetEnable(true);
	m_RealBuyButton->SetEnable(true);
	m_RealCloseButton->SetEnable(true);
	m_ShopText->SetEnable(true);
	m_ShopText->SetTextTime(true);

	
}

void CShopUI::CloseButtonClick()
{
	SetEnable(false);
}

void CShopUI::RealBuyButtonClick()
{
	CPlayer2D* Player = nullptr;

	if (m_Scene)
		Player = (CPlayer2D*)m_Scene->FindObject("Player2D");

	else
		Player = (CPlayer2D*)CSceneManager::GetInst()->GetScene()->FindObject("Player2D");
	
	std::string Number = CEngine::GetInst()->GetUIText();

	int PotionNumber = atoi(Number.c_str());	

	if (m_SelectRedPotion)
	{
		Player->AddHpPotionNumber(PotionNumber);
	}

	if (m_SelectBluePotion)
	{
		Player->AddMpPotionNumber(PotionNumber);
	}

	m_Scene->GetResource()->SoundPlay("BuyShopItem");

	m_RedPotionNumber->SetNumber(Player->GetHpPotionNumber());
	m_BluePotionNumber->SetNumber(Player->GetMpPotionNumber());

	m_BuyBackImage->SetEnable(false);
	m_BuyText->SetEnable(false);
	m_RealBuyButton->SetEnable(false);
	m_RealCloseButton->SetEnable(false);
	m_ShopText->SetTextTime(false);
	m_ShopText->SetEnable(false);
}

void CShopUI::RealCloseButtonClick()
{
	CEngine::GetInst()->ClearText();

	m_BuyBackImage->SetEnable(false);
	m_BuyText->SetEnable(false);
	m_RealBuyButton->SetEnable(false);
	m_RealCloseButton->SetEnable(false);
	m_ShopText->SetTextTime(false);
	m_ShopText->SetEnable(false);
}
