#pragma once
#include "UI\UIWindow.h"

class CInventoryUI :
    public CUIWindow
{
	friend class CSceneViewport;
	friend class CScene;

protected:
	CInventoryUI();
	CInventoryUI(const CInventoryUI& Window);
	virtual ~CInventoryUI();

protected:
	class CPlayer2D* m_Player;
	bool						m_Drag;
	int							m_DoubleClick;
	float						m_DoubleClickTime;
	CSharedPtr<class CUIButton> m_DragButton;

	//인벤토리 기본 이미지 
	CSharedPtr<class CUIImage>	m_InventoryBackImage;
	CSharedPtr<class CUIImage>	m_InventoryBackImage2;
	CSharedPtr<class CUIImage>	m_InventoryBackImage3;
	CSharedPtr<class CUIImage>	m_InventoryMesoImage;
	CSharedPtr<class CUIImage>	m_InventoryMaplePointImage;
	CSharedPtr<class CUIText>	m_InventoryMesoText;
	CSharedPtr<class CUIText>	m_InventoryMaplePointText;


	//장비
	CSharedPtr<class CUIButton> m_EquipButton;
	CSharedPtr<class CUIButton> m_Weapon1;
	CSharedPtr<class CUIButton> m_Weapon2;	


	//소비
	CSharedPtr<class CUIButton> m_UseButton;
	CSharedPtr<class CUIImage>	m_HpPotionImage;
	CSharedPtr<class CUIImage>	m_MpPotionImage;
	CSharedPtr<class CUINumber> m_HpPotionNumber;
	CSharedPtr<class CUINumber> m_MpPotionNumber;

	//기타
	CSharedPtr<class CUIButton> m_DisEnableButton1;

	//설치
	CSharedPtr<class CUIButton> m_DisEnableButton2;

	//캐시
	CSharedPtr<class CUIButton> m_DisEnableButton3;

	//치장
	CSharedPtr<class CUIButton> m_DisEnableButton4;

	//비활성 버튼
	CSharedPtr<class CUIButton> m_DisEnableButton5;
	CSharedPtr<class CUIButton> m_DisEnableButton6;
	CSharedPtr<class CUIButton> m_DisEnableButton7;
	CSharedPtr<class CUIButton> m_DisEnableButton8;
	CSharedPtr<class CUIButton> m_DisEnableButton9;
	CSharedPtr<class CUIButton> m_DisEnableButton10;

	//무기 장착 여부 
	bool EquipWeapon1;
	bool EquipWeapon2;

	//현재 인벤토리가 장비인지 소비인지 여부 
	CSharedPtr<class CUIButton> m_EquipInvButton;
	CSharedPtr<class CUIButton> m_UseInvButton;
	bool m_EquipInv;
	bool m_UseInv;

	//이미지 줌인 이미지 
	CSharedPtr<class CUIImage> m_Weapon1Image;
	CSharedPtr<class CUIImage> m_Weapon2Image;

public:
	void SetPlayer(class CPlayer2D* Player)
	{
		m_Player = Player;
	}

	bool GetEquipWeapon1() const
	{
		return EquipWeapon1;
	}

	void SetEquipWeapon1(bool Equip)
	{
		EquipWeapon1 = Equip;
	}

	bool GetEquipWeapon2() const
	{
		return EquipWeapon2;
	}

	void SetEquipWeapon2(bool Equip)
	{
		EquipWeapon2 = Equip;
	}


public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render();
	virtual CInventoryUI* Clone();
	virtual void Save(FILE* File);
	virtual void Load(FILE* File);


private:
	void DisEnableButtonCreate();

private:
	void Weapon1EquipButton();
	void Weapon2EquipButton();

	void UseItemEnable();
	void EquipItemEnable();
};

