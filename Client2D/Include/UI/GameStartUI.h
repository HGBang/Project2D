#pragma once
#include "UI\UIWindow.h"
class CGameStartUI :
    public CUIWindow
{
	friend class CSceneViewport;
	friend class CScene;

protected:
	CGameStartUI();
	CGameStartUI(const CGameStartUI& Window);
	virtual ~CGameStartUI();

protected:
	CSharedPtr<class CUIButton> m_Button;
	CSharedPtr<class CUIImage> m_BackImage;
	CSharedPtr<class CUIImage> m_StartBackImage;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render();
	virtual CGameStartUI* Clone();
	virtual void Save(FILE* File);
	virtual void Load(FILE* File);

public:
	void GameStartButton();
};

