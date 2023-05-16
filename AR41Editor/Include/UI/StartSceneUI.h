#pragma once

#include "UI/UIWindow.h"

class CStartSceneUI :
    public CUIWindow
{
	friend class CSceneViewport;
	friend class CScene;
	friend class CPlayer2D;

private:
	class CPlayer2D* m_Player;
	class CHonTail* m_HonTail;

protected:
	CStartSceneUI();
	CStartSceneUI(const CStartSceneUI& Window);
	virtual ~CStartSceneUI();

protected:	
	CSharedPtr<class CUIText> m_LevelUpText;
	CSharedPtr<class CUIText> m_LevelText;

	CSharedPtr<class CUINumber> m_LevelNumber;
	CSharedPtr<class CUINumber> m_ExpNumber;
	CSharedPtr<class CUINumber> m_ExpValueNumber;

	CSharedPtr<class CUINumber> m_HpNumber;
	CSharedPtr<class CUINumber> m_MaxHpNumber;
	CSharedPtr<class CUINumber> m_MpNumber;
	CSharedPtr<class CUINumber> m_MaxMpNumber;

	CSharedPtr<class CUIImage> m_StatusImage;
	CSharedPtr<class CUIImage> m_StatusBackImage;
	CSharedPtr<class CUIImage> m_LevelImage;
	CSharedPtr<class CUIImage> m_LevelUpImage;

	CSharedPtr<class CUIProgressBar> m_ExpProgressBar;
	CSharedPtr<class CUIProgressBar> m_HpProgressBar;
	CSharedPtr<class CUIProgressBar> m_MpProgressBar;

	class CUIProgressBar* m_HonTailProgressBar;

	CSharedPtr<class CUIImage> m_QuickSlotBackImage;
	CSharedPtr<class CUIImage> m_QuickSlotImage;
	CSharedPtr<class CUIImage> m_QuickSlotLeftImage;

	CSharedPtr<class CUINumber> m_DamageNumber;

	//Key 
	class CUIImage* m_AttackKeyImage;
	class CUIImage* m_CtrlKeyImage;
	class CUIImage* m_JumpKeyImage;
	class CUIImage* m_AltKeyImage;
	class CUIImage* m_RedPotionKeyImage;
	class CUIImage* m_DelKeyImage;
	class CUINumber* m_RedPotionKeyNumber;
	class CUIImage* m_BluePotionKeyImage;
	class CUIImage* m_EndKeyImage;
	class CUINumber* m_BluePotionKeyNumber;

	class CUIImage* m_BaseSkillKeyImage;
	class CUIImage* m_ShiftKeyImage;
	class CUIImage* m_HighSkillKeyImage;
	class CUIImage* m_SpaceKeyImage;
	class CUIImage* m_PdnKeyImage;
	class CUIImage* m_FlashJumpKeyImage;
	

	class CUIText* m_ExpText;
	class CUINumber* m_AddExpNumber;
	class CUIImage* m_MinimapPlayerIcon;

	float m_ExpTime;
	bool m_ExpOn;

	bool m_LevelUpFunc;

	float DamageEnableTime;
	std::string DamageID;
	int DamageNumberID;

	bool m_MiniMapStart;

	
public:
	void SetLevelUpFunc(bool Func)
	{
		m_LevelUpFunc = Func;
	}

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render();
	virtual CStartSceneUI* Clone();
	virtual void Save(FILE* File);
	virtual void Load(FILE* File);


public:
	void SetHonTail(CHonTail* HonTail);

public:
	void SceneChange();
	void LevelUpEffect();
	void SetDamageNumber(Vector2 Pos, int Damage);
	void SetCriticalDamageNumber(Vector2 Pos, int Damage);
	void SetMonsterDamageNumber(Vector2 Pos, int Damage, int MpDamage = 0);
	void SetExp(int Exp);
	void MiniMapStart();

private:
	void UpdatePlayerInfo();
	void UpdateHonTailInfo();
	void InitKey();
	TCHAR* StringtoTCHAR(const std::string& Name);

};

