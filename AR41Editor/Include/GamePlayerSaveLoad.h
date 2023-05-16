#pragma once
#include "EngineInfo.h"

class CGamePlayerSaveLoad
{	
protected:
	class CPlayer2D* m_Player;
	class CInventoryUI* m_ItemUI;
	class CEquipmentUI* m_EquipUI;
	class CQuestUI* m_QuestUI;

	int m_HpPotion;
	int m_MpPotion;
	bool m_HelenaQuest;
	bool m_FrontQuest;
	bool m_Weapon;
	bool m_Weapon1;
	bool m_Weapon2;
	bool m_PlayerSkill1Lock;
	bool m_PlayerSkill2Lock;
	bool m_Weapon1Equip;
	bool m_Weapon2Equip;

	int m_PlayerLevel;
	int m_PlayerExp;
	int m_PlayerMaxExp;
	int m_PlayerStr;
	int m_PlayerDex;
	int m_PlayerInt;
	int m_PlayerLuk;
	int m_PlayerMaxHp;
	int m_PlayerHp;
	int m_PlayerMaxMp;
	int m_PlayerMp;

	bool HelenaNoQuest;
	bool HelenaSecondQuest;


public:
	void Save();
	void Load();

	DECLARE_SINGLE(CGamePlayerSaveLoad)
};

