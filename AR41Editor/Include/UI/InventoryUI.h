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

	//�κ��丮 �⺻ �̹��� 
	CSharedPtr<class CUIImage>	m_InventoryBackImage;
	CSharedPtr<class CUIImage>	m_InventoryBackImage2;
	CSharedPtr<class CUIImage>	m_InventoryBackImage3;
	CSharedPtr<class CUIImage>	m_InventoryMesoImage;
	CSharedPtr<class CUIImage>	m_InventoryMaplePointImage;
	CSharedPtr<class CUIText>	m_InventoryMesoText;
	CSharedPtr<class CUIText>	m_InventoryMaplePointText;


	//���
	CSharedPtr<class CUIButton> m_EquipButton;
	CSharedPtr<class CUIButton> m_Weapon1;
	CSharedPtr<class CUIButton> m_Weapon2;	


	//�Һ�
	CSharedPtr<class CUIButton> m_UseButton;
	CSharedPtr<class CUIImage>	m_HpPotionImage;
	CSharedPtr<class CUIImage>	m_MpPotionImage;
	CSharedPtr<class CUINumber> m_HpPotionNumber;
	CSharedPtr<class CUINumber> m_MpPotionNumber;

	//��Ÿ
	CSharedPtr<class CUIButton> m_DisEnableButton1;

	//��ġ
	CSharedPtr<class CUIButton> m_DisEnableButton2;

	//ĳ��
	CSharedPtr<class CUIButton> m_DisEnableButton3;

	//ġ��
	CSharedPtr<class CUIButton> m_DisEnableButton4;

	//��Ȱ�� ��ư
	CSharedPtr<class CUIButton> m_DisEnableButton5;
	CSharedPtr<class CUIButton> m_DisEnableButton6;
	CSharedPtr<class CUIButton> m_DisEnableButton7;
	CSharedPtr<class CUIButton> m_DisEnableButton8;
	CSharedPtr<class CUIButton> m_DisEnableButton9;
	CSharedPtr<class CUIButton> m_DisEnableButton10;

	//���� ���� ���� 
	bool EquipWeapon1;
	bool EquipWeapon2;

	//���� �κ��丮�� ������� �Һ����� ���� 
	CSharedPtr<class CUIButton> m_EquipInvButton;
	CSharedPtr<class CUIButton> m_UseInvButton;
	bool m_EquipInv;
	bool m_UseInv;

	//�̹��� ���� �̹��� 
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

