#include "GamePlayerSaveLoad.h"
#include "PathManager.h"
#include "GameObject/Player2D.h"
#include "GameObject/GameObject.h"
#include "Scene/Scene.h"
#include "Scene/SceneManager.h"
#include "UI/EquipmentUI.h"
#include "UI/InventoryUI.h"
#include "UI/QuestUI.h"

DEFINITION_SINGLE(CGamePlayerSaveLoad)

CGamePlayerSaveLoad::CGamePlayerSaveLoad()
{

}

CGamePlayerSaveLoad::~CGamePlayerSaveLoad()
{
	
}

void CGamePlayerSaveLoad::Save()
{
	m_Player = (CPlayer2D*)CSceneManager::GetInst()->GetScene()->FindObject("Player2D");

	m_ItemUI = CSceneManager::GetInst()->GetScene()->GetViewport()->FindUIWindow<CInventoryUI>("InventoryUI");

	m_EquipUI = CSceneManager::GetInst()->GetScene()->GetViewport()->FindUIWindow<CEquipmentUI>("CEquipmentUI");

	m_QuestUI = CSceneManager::GetInst()->GetScene()->GetViewport()->FindUIWindow<CQuestUI>("QuestUI");


	m_HpPotion = m_Player->GetHpPotionNumber();
	m_MpPotion = m_Player->GetMpPotionNumber();
	m_HelenaQuest = m_Player->GetHelenaFirstQuestOn();
	m_FrontQuest = m_Player->GetFrontQuestOn();
	m_Weapon = m_Player->GetWeapon();
	m_Weapon1 = m_Player->GetWeapon1();
	m_Weapon2 = m_Player->GetWeapon2();
	m_PlayerSkill1Lock = m_Player->GetSkill1Lock();
	m_PlayerSkill2Lock = m_Player->GetSkill2Lock();

	m_Weapon1Equip = m_ItemUI->GetEquipWeapon1();
	m_Weapon2Equip = m_ItemUI->GetEquipWeapon2();

	m_PlayerLevel = m_Player->GetLevel();
	m_PlayerExp = m_Player->GetExp();
	m_PlayerMaxExp = m_Player->GetMaxExp();
	m_PlayerStr = m_Player->GetStr();
	m_PlayerDex = m_Player->GetDex();
	m_PlayerInt = m_Player->GetInt();
	m_PlayerLuk = m_Player->GetLuk();
	m_PlayerHp = m_Player->GetHp();
	m_PlayerMaxHp = m_Player->GetMaxHp();
	m_PlayerMp = m_Player->GetMp();
	m_PlayerMaxMp = m_Player->GetMaxMp();

	HelenaNoQuest = m_QuestUI->GetHelenaNoQuest();
	HelenaSecondQuest = m_QuestUI->GetHelenaSecondQuest();

}

void CGamePlayerSaveLoad::Load()
{

	m_Player = (CPlayer2D*)CSceneManager::GetInst()->GetScene()->FindObject("Player2D");

	m_ItemUI = CSceneManager::GetInst()->GetScene()->GetViewport()->FindUIWindow<CInventoryUI>("InventoryUI");

	m_EquipUI = CSceneManager::GetInst()->GetScene()->GetViewport()->FindUIWindow<CEquipmentUI>("CEquipmentUI");

	m_QuestUI = CSceneManager::GetInst()->GetScene()->GetViewport()->FindUIWindow<CQuestUI>("QuestUI");

	m_Player->SetHpPotionNumber(m_HpPotion);
	m_Player->SetMpPotionNumber(m_MpPotion);	
	m_Player->SetHelenaFirstQuestOn(m_HelenaQuest);

	m_Player->SetFrontQuestOn(m_FrontQuest);
		
	m_Player->SetWeapon(m_Weapon);	
	m_Player->SetWeapon(m_Weapon1);
	m_Player->SetWeapon(m_Weapon2);
		
	m_Player->SetSkill1Lock(m_PlayerSkill1Lock);
	m_Player->SetSkill2Lock(m_PlayerSkill2Lock);

	m_ItemUI->SetEquipWeapon1(m_Weapon1Equip);
	m_ItemUI->SetEquipWeapon2(m_Weapon2Equip);

	m_Player->SetLevel(m_PlayerLevel);
	m_Player->SetExp(m_PlayerExp);
	m_Player->SetMaxExp(m_PlayerMaxExp);
	m_Player->SetStr(m_PlayerStr);
	m_Player->SetInt(m_PlayerInt);
	m_Player->SetLuk(m_PlayerLuk);
	m_Player->SetDex(m_PlayerDex);

	m_Player->SetHp(m_PlayerHp);
	m_Player->SetMaxHp(m_PlayerMaxHp);
	m_Player->SetMp(m_PlayerMp);
	m_Player->SetMaxMp(m_PlayerMaxMp);

	m_QuestUI->SetFrontQuestFalse();

	m_QuestUI->SetHelenaNoQuest(HelenaSecondQuest);
	m_QuestUI->SetHelenaSecondQuest(HelenaSecondQuest);

}
