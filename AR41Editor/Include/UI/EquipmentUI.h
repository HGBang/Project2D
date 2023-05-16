#pragma once
#include "UI\UIWindow.h"

class CEquipmentUI :
    public CUIWindow
{
	friend class CSceneViewport;
	friend class CScene;

protected:
	CEquipmentUI();
	CEquipmentUI(const CEquipmentUI& Window);
	virtual ~CEquipmentUI();

protected:
	class CPlayer2D* m_Player;
	class CInventoryUI* m_ItemUI;



	bool m_Drag;
	int m_DoubleClick;
	float m_DoubleClickTime;
	CSharedPtr<class CUIButton> m_DragButton;

	CSharedPtr<class CUIImage> m_EquipBackImage1;
	CSharedPtr<class CUIImage> m_EquipBackImage2;
	CSharedPtr<class CUIImage> m_EquipBackImage3;
	CSharedPtr<class CUIImage> m_EquipBackLineImage;
	CSharedPtr<class CUIImage> m_EquipBackCheckBoxImage;
	CSharedPtr<class CUIImage> m_EquipBackEquipButtonImage;
	CSharedPtr<class CUIImage> m_EquipBackCashButtonImage;
	CSharedPtr<class CUIImage> m_EquipBackPetButtonImage;
	CSharedPtr<class CUIImage> m_EquipBackADButtonImage;

	CSharedPtr<class CUIImage> m_EquipCapButtonImage;
	CSharedPtr<class CUIImage> m_EquipClothButtonImage;
	CSharedPtr<class CUIImage> m_EquipPantsButtonImage;
	CSharedPtr<class CUIImage> m_EquipShoesButtonImage;
	CSharedPtr<class CUIImage> m_EquipWeaponButtonImage;

	CSharedPtr<class CUIButton> m_EquipClothImage;
	CSharedPtr<class CUIButton> m_EquipCapImage;
	CSharedPtr<class CUIButton> m_EquipWeapon1Button;
	CSharedPtr<class CUIButton> m_EquipWeapon2Button;
	//
	CSharedPtr<class CUIImage> m_EquipWeapon1Image;
	CSharedPtr<class CUIImage> m_EquipWeapon2Image;

	CSharedPtr<class CUIImage> m_EquipCapInfoImage;
	CSharedPtr<class CUIImage> m_EquipClothInfoImage;




public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render();
	virtual CEquipmentUI* Clone();
	virtual void Save(FILE* File);
	virtual void Load(FILE* File);	

private:
	void Weapon1EquipOffButton();
	void Weapon2EquipOffButton();

public:
	void SetPlayer(class CPlayer2D* Player)
	{
		m_Player = Player;
	}


};

