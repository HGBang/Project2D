#pragma once
#include "UI\UIWindow.h"


class CMonsterBarUI :
    public CUIWindow
{
	friend class CSceneViewport;
	friend class CScene;

protected:
	CMonsterBarUI();
	CMonsterBarUI(const CMonsterBarUI& Window);
	virtual ~CMonsterBarUI();	

protected:
	unsigned int ProgressBarID;
	unsigned int MonsterNameID;
	class CUIProgressBar* m_ProgressBar;
	class CUIText* m_MonsterNameText;
	Vector2		m_WorldPos;

public:
	CUIProgressBar* GetProGressBar(int MaxHp, const Vector2& MonsterPos);
	CUIText* GetMonsterNameTag(const TCHAR* MonsterName, const Vector2& MonsterPos);


public:
	void SetBarPos(const Vector2& MonsterPos);

	
public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render();
	virtual CMonsterBarUI* Clone();
	virtual void Save(FILE* File);
	virtual void Load(FILE* File);
};

