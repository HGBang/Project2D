#pragma once
#include "UI\UIWindow.h"
class CSelectPlayerUI :
    public CUIWindow
{
	friend class CSceneViewport;
	friend class CScene;

protected:
	CSelectPlayerUI();
	CSelectPlayerUI(const CSelectPlayerUI& Window);
	virtual ~CSelectPlayerUI();

protected:
	bool	m_SelectPlayer;
	bool	m_ButtonOn;

	CSharedPtr<class CUIButton> m_GameStartButton;
	CSharedPtr<class CUIButton> m_PlayerCreateButton;
	CSharedPtr<class CUIButton> m_PlayerDeleteButton;
	CSharedPtr<class CUIButton> m_PrevButton;
	CSharedPtr<class CUIButton> m_WhiteButton;

	CSharedPtr<class CUIImage>	m_PlayerCheckImage;
	CSharedPtr<class CUIImage>	m_PlayerLevelImage;
	CSharedPtr<class CUIText>	m_PlayerName;
	CSharedPtr<class CUIText>	m_PlayerClassName;

	CSharedPtr<class CUINumber> m_PlayerLevel;
	CSharedPtr<class CUINumber>	m_PlayerStr;
	CSharedPtr<class CUINumber>	m_PlayerInt;
	CSharedPtr<class CUINumber>	m_PlayerDex;
	CSharedPtr<class CUINumber>	m_PlayerLuk;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render();
	virtual CSelectPlayerUI* Clone();
	virtual void Save(FILE* File);
	virtual void Load(FILE* File);

public:
	void SetSelectPlayer(bool Select)
	{
		m_SelectPlayer = Select;
	}

	bool GetSelectPlayer() const
	{
		return m_SelectPlayer;
	}

public:
	void GameStartButton();
	void WhiteButtonClick();
};

