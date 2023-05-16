#pragma once
#include "UI\UIWindow.h"
class CShopUI :
    public CUIWindow
{
	friend class CSceneViewport;
	friend class CScene;

protected:
	CShopUI();
	CShopUI(const CShopUI& Window);
	virtual ~CShopUI();

protected:
	class CUIImage* m_ShopBackImage1;
	class CUIImage* m_ShopBackImage2;
	class CUIImage* m_ShopBackImage3;

	class CUIImage* m_ShopRedPotionSelect;
	class CUIImage* m_ShopBluePotionSelect;

	class CUIButton* m_ShopRedButton;
	class CUIButton* m_ShopBlueButton;

	class CUIImage* m_RedPotionImage;
	class CUIImage* m_BluePotionImage;

	class CUIText* m_RedPotionText;
	class CUIText* m_BluePotionText;

	class CUIImage* m_ShopCategoryImage;
	class CUIImage* m_PlayerCategoryImage;

	class CUIImage* m_ShopNpcImage;
	class CUIImage* m_ShopPlayerImage;

	class CUINumber* m_RedPotionNumber;
	class CUINumber* m_BluePotionNumber;

	class CUIButton* m_BuyButton;
	class CUIButton* m_CloseButton;

	class CUIImage* m_BuyBackImage;
	class CUIText* m_BuyText;
	class CUIButton* m_RealBuyButton;
	class CUIButton* m_RealCloseButton;
	class CUIShopText* m_ShopText;


	bool m_SelectRedPotion;
	bool m_SelectBluePotion;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render();
	virtual CShopUI* Clone();
	virtual void Save(FILE* File);
	virtual void Load(FILE* File);

private:
	void RedPotionClick();
	void BluePotionClick();
	void BuyButtonClick();
	void CloseButtonClick();
	void RealBuyButtonClick();
	void RealCloseButtonClick();
};

