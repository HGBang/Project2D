#pragma once

#include "UI\UIWindow.h"

class CQuestUI :
    public CUIWindow
{
	friend class CSceneViewport;
	friend class CScene;

protected:
	CQuestUI();
	CQuestUI(const CQuestUI& Window);
	virtual ~CQuestUI();


protected:
	class CPlayer2D* m_Player; 
	TCHAR m_QuestText[1024];
	int m_TextCount;
	int m_TextIndex;
	float m_TextTime;
	

	class CUIImage* m_QuestChatBoxImage;
	class CUIImage* m_QuestNpcImage;
	class CUIButton* m_QuestOkButton;
	class CUIButton* m_QuestCancelButton;
	class CUIText* m_QuestIngListText;
	class CUIButton* m_QuestExitButton;
	class CUIImage* m_QuestItemImage;
	class CUIImage* m_QuestItemImage1;
	class CUIImage* m_QuestWeaponImage;

	class CUIImage* m_QuestAlarmImage;
	class CUIButton* m_QuestAlarmButton;
	class CUIText* m_QuestAlarmText;
	class CUIText* m_QuestTitleText;
	class CUIText* m_QuestComplateText;
	class CUIButton* m_QuestComplateButton;

	bool	m_FrontQuest;
	bool	m_ClassChangeQuest;
	bool	m_BossQuest;

	bool	m_QuestIng;

	bool	m_FrontQuestComplete;
	bool	m_ClassChangeQuestComplete;
	bool	m_BossQuestComplete;


	bool	m_NoQuest;
	bool	m_WeaponImageOn;

	bool	m_HelenaFirstQuest;
	bool	m_HelenaSecondQuest;
	bool	m_HelenaNoQuest;

	bool	m_Skill1ImageOn;
	bool	m_Skill2ImageOn;


private:
	void FirstQuestText();
	void ClassChanageText();
	void BossQuestText();

	void FirstQuestIngText();
	void ClassChanageIngText();
	void BossQuestIngText();

	void FirstQuestCompleteText();
	void ClassChanageCompleteText();
	void BossQuestCompleteText();

	void HelenaFirstQuestText();
	void HelenaNoQuestText();
	void HelenaSecondQuestText();

public:
	void SetPlayer(CPlayer2D* Player)
	{
		m_Player = Player;
	}

public:
	bool GetFrontQuest() const
	{
		return m_FrontQuest;
	}

	bool GetFrontQuestComplete() const
	{
		return m_FrontQuestComplete;
	}

	bool GetClassChangeQuest() const
	{
		return m_ClassChangeQuest;
	}

	bool GetBossQuest() const
	{
		return m_BossQuest;
	}

	bool GetQuestIng() const
	{
		return m_QuestIng;
	}

	bool GetNoQuest() const
	{
		return m_NoQuest;
	}

	bool GetHelenaFirstQuest() const
	{
		return m_HelenaFirstQuest;
	}

	bool GetHelenaNoQuest() const
	{
		return m_HelenaNoQuest;
	}

	bool GetHelenaSecondQuest() const
	{
		return m_HelenaSecondQuest;
	}


	void SetFrontQuestFalse()
	{
		m_FrontQuest = false;
	}

	bool GetHelenaNoQuest()
	{
		return m_HelenaNoQuest;
	}

	bool GetHelenaSecondQuest()
	{
		return m_HelenaSecondQuest;
	}

	void SetHelenaNoQuest(bool Helena)
	{
		m_HelenaNoQuest = Helena;
	}

	void SetHelenaSecondQuest(bool Helena)
	{
		m_HelenaSecondQuest = Helena;
	}


public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render();
	virtual CQuestUI* Clone();
	virtual void Save(FILE* File);
	virtual void Load(FILE* File);


public:
	void SetQuestIng();
	void SetFrontQuest();
	void SetFrontQuestComplete();
	void SetHelenaFirstQuest();
	void SetHelenaNoQuest();
	void SetHelenaSecondQuest();




private:
	void QuestOkButtonClick();
	void QuestCancelButtonClick();
	void QuestExitButtonClick();
	void QuestCompleteClick();

	void ClearUI();



private:
	unsigned int		m_TimerID;
};

