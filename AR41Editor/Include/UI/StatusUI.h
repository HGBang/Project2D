#pragma once
#include "UI\UIWindow.h"
class CStatusUI :
    public CUIWindow
{
	friend class CSceneViewport;
	friend class CScene;

protected:
	CStatusUI();
	CStatusUI(const CStatusUI& Window);
	virtual ~CStatusUI();

protected:
	class CPlayer2D* m_Player;
	CSharedPtr<class CUIButton> m_DragButton;

	//½ºÅÝÃ¢ 
	CSharedPtr<class CUIImage> m_StatBackImage;
	CSharedPtr<class CUIImage> m_StatMainImage;
	CSharedPtr<class CUIImage> m_ApImage;
	CSharedPtr<class CUIText>  m_PlayerName;
	CSharedPtr<class CUIText>  m_ClassName;

	CSharedPtr<class CUIText> m_DamageNumber;
	CSharedPtr<class CUIText> m_HpNumber;
	CSharedPtr<class CUIText> m_MaxHpNumber;
	CSharedPtr<class CUIText> m_MpNumber;
	CSharedPtr<class CUIText> m_MaxMpNumber;
	CSharedPtr<class CUIText> m_ApNumber;
	CSharedPtr<class CUIText> m_StrNumber;
	CSharedPtr<class CUIText> m_DexNumber;
	CSharedPtr<class CUIText> m_IntNumber;
	CSharedPtr<class CUIText> m_LukNumber;

	CSharedPtr<class CUIButton> m_StrUpButton;
	CSharedPtr<class CUIButton> m_DexUpButton;
	CSharedPtr<class CUIButton> m_IntUpButton;
	CSharedPtr<class CUIButton> m_LukUpButton;

	CSharedPtr<class CUIText> m_Slush;
	CSharedPtr<class CUIText> m_Slush2;


	bool m_Drag;
	bool m_ButtonUpdate;
	bool m_ButtonDisable;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render();
	virtual CStatusUI* Clone();
	virtual void Save(FILE* File);
	virtual void Load(FILE* File);

public:
	void SetUpdateApButton(bool Update)
	{
		m_ButtonUpdate = Update;
	}

private:
	void UpdatePlayerInfo();
	void UpdateApButtonInfo();
	void UpdateButtonDisable();

private:
	void StrUpButtonClick();
	void DexUpButtonClick();
	void IntUpButtonClick();
	void LukUpButtonClick();
};

