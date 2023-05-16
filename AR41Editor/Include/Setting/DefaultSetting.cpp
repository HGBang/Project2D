#include "DefaultSetting.h"
#include "Resource/Sound/Sound.h"
#include "Resource/Sound/SoundManager.h"
#include "Scene/Scene.h"
#include "Scene/Scenemanager.h"
#include "../GamePlayerSaveLoad.h"
#include "../GamePlayerPosSaveLoad.h"

#include "../Scene/EditorDefaultScene.h"
#include "../GameObject/Player2D.h"
#include "../GameObject/Bullet.h"
#include "../GameObject/TestMonster.h"
#include "../GameObject/SelectPlayer.h"
#include "../GameObject/ElderNpc.h"
#include "../GameObject/ShopNpc.h"
#include "../GameObject/Portal.h"
#include "../GameObject/Rope.h"
#include "../GameObject/Helena.h"
#include "../GameObject/HonTail.h"
#include "../GameObject/HonTailSummon.h"
#include "../GameObject/Skelegon.h"
#include "../GameObject/DarkWybern.h"
#include "../GameObject/HonTailWall.h"
#include "../GameObject/HonTailExObj.h"
#include "../GameObject/SkillEffect.h"
#include "../UI/StartSceneUI.h"
#include "Scene/Scene.h"
#include "PathManager.h"
#include "Input.h"
#include "../UI/GameStartUI.h"
#include "../UI/SelectPlayerUI.h"
#include "../UI/EquipmentUI.h"
#include "../UI/InventoryUI.h"
#include "../UI/StatusUI.h"
#include "../UI/QuestUI.h"
#include "../UI/MonsterBarUI.h"
#include "../UI/ShopUI.h"
#include "CollisionManager.h"


CDefaultSetting::CDefaultSetting()
{
}

CDefaultSetting::~CDefaultSetting()
{
    CGamePlayerSaveLoad::DestroyInst();
    CGamePlayerPosSaveLoad::DestroyInst();
}

void CDefaultSetting::Init()
{
    LoadResource();

	CreateCDO();

	SetInput();

    SetCollision();
}

void CDefaultSetting::CreateCDO()
{
	CScene::CreateObjectCDO<CPlayer2D>("Player2D");
    CScene::CreateObjectCDO<CSelectPlayer>("SelectPlayer");
	CScene::CreateObjectCDO<CTestMonster>("TestMonster");
    CScene::CreateObjectCDO<CElderNpc>("ElderNpc");
    CScene::CreateObjectCDO<CShopNpc>("ShopNpc");
    CScene::CreateObjectCDO<CPortal>("Portal");
    CScene::CreateObjectCDO<CRope>("Rope");
    CScene::CreateObjectCDO<CHelena>("Helena");
    CScene::CreateObjectCDO<CHonTail>("HonTail");
    CScene::CreateObjectCDO<CHonTailSummon>("Summon");
    CScene::CreateObjectCDO<CSkelegon>("Skelegon");
    CScene::CreateObjectCDO<CDarkWybern>("DarkWybern");
    CScene::CreateObjectCDO<CHonTailWall>("HonTailWall");
    CScene::CreateObjectCDO<CHonTailExObj>("HonTailExObj");
    CScene::CreateObjectCDO<CSkillEffect>("SkillEffect");



    CScene::CreateUIWindowCDO<CQuestUI>("QuestUI");
    CScene::CreateUIWindowCDO<CStartSceneUI>("StartSceneUI"); 
    CScene::CreateUIWindowCDO<CGameStartUI>("GameStartUI");
    CScene::CreateUIWindowCDO<CSelectPlayerUI>("SelectPlayerUI");
    CScene::CreateUIWindowCDO<CEquipmentUI>("EquipmentUI");
    CScene::CreateUIWindowCDO<CInventoryUI>("InventoryUI");
    CScene::CreateUIWindowCDO<CStatusUI>("StatusUI");
    CScene::CreateUIWindowCDO<CMonsterBarUI>("MonsterBarUI");
    CScene::CreateUIWindowCDO<CShopUI>("ShopUI");
}

void CDefaultSetting::LoadResource()
{  
    CSceneManager::GetInst()->GetScene()->GetResource()->LoadSound("BGM", "LoginBGM", true, "MapleLogin.mp3");
    //CSceneManager::GetInst()->GetScene()->GetResource()->SetVolume("BGM", 20);
    CSceneManager::GetInst()->GetScene()->GetResource()->LoadSound("BGM", "Henesis", true, "Henesis.mp3");


    const PathInfo* animPath = CPathManager::GetInst()->FindPath(ANIMATION2D_PATH);

    std::filesystem::path AnimseqDir = animPath->PathMultibyte;

    for (auto& directoryEntry : std::filesystem::directory_iterator(AnimseqDir))
    {
        if (directoryEntry.path().extension() == ".Src")
        {
            std::string name = directoryEntry.path().filename().replace_extension("").string();
            CResourceManager::GetInst()->CreateAnimationSequence2D(name, nullptr);
            CAnimationSequence2D* Animation = CResourceManager::GetInst()->FindAnimationSequence2D(name);
            Animation->Load(directoryEntry.path().string().c_str());
        }
    }
}

void CDefaultSetting::SetInput()
{
    CInput::GetInst()->AddBindKey("MoveRight", VK_RIGHT);
    CInput::GetInst()->AddBindKey("MoveLeft", VK_LEFT);
    CInput::GetInst()->AddBindKey("MoveUp", VK_UP);
    CInput::GetInst()->AddBindKey("MoveDown", VK_DOWN);
    CInput::GetInst()->AddBindKey("Ring", VK_SPACE);
    CInput::GetInst()->AddBindKey("Jump", 'Z');
    CInput::GetInst()->AddBindKey("NormalAttack", VK_LCONTROL);
    CInput::GetInst()->SetKeyCtrl("NormalAttack");
    CInput::GetInst()->AddBindKey("SpeedDuelShot", VK_LSHIFT);
    CInput::GetInst()->SetKeyShift("SpeedDuelShot");
    CInput::GetInst()->AddBindKey("RedPotion", VK_DELETE);
    CInput::GetInst()->AddBindKey("BluePotion", VK_END);
    CInput::GetInst()->AddBindKey("FlashJump", VK_NEXT);

    CInput::GetInst()->AddBindKey("LevelUp", 'P');
    CInput::GetInst()->AddBindKey("StatUI", 'S');
    CInput::GetInst()->AddBindKey("ItemUI", 'I');
    CInput::GetInst()->AddBindKey("EquipUI", 'E');


}

void CDefaultSetting::SetCollision()
{
    CCollisionManager::GetInst()->CreateChannel("Player", ECollision_Interaction::Collision);
    CCollisionManager::GetInst()->CreateChannel("PlayerAttack", ECollision_Interaction::Collision);
    CCollisionManager::GetInst()->CreateChannel("Monster", ECollision_Interaction::Collision);
    CCollisionManager::GetInst()->CreateChannel("MonsterAttack", ECollision_Interaction::Collision);
    CCollisionManager::GetInst()->CreateChannel("Portal", ECollision_Interaction::Collision);
    CCollisionManager::GetInst()->CreateChannel("Rope", ECollision_Interaction::Collision);
    CCollisionManager::GetInst()->CreateChannel("Die", ECollision_Interaction::Ignore);
    CCollisionManager::GetInst()->CreateChannel("JungSY", ECollision_Interaction::Ignore);


    CCollisionManager::GetInst()->CreateProfile("Player", "Player", true);
    CCollisionManager::GetInst()->CreateProfile("PlayerAttack", "PlayerAttack", true);
    CCollisionManager::GetInst()->CreateProfile("Monster", "Monster", true);
    CCollisionManager::GetInst()->CreateProfile("MonsterAttack", "MonsterAttack", true);
    CCollisionManager::GetInst()->CreateProfile("Portal", "Portal", true);
    CCollisionManager::GetInst()->CreateProfile("Rope", "Rope", true);
    CCollisionManager::GetInst()->CreateProfile("Die", "Die", true);
    CCollisionManager::GetInst()->CreateProfile("JungSY", "JungSY", true);


    CCollisionManager::GetInst()->SetCollisionInteraction("Portal", "PlayerAttack", ECollision_Interaction::Ignore);
    CCollisionManager::GetInst()->SetCollisionInteraction("Portal", "Monster", ECollision_Interaction::Ignore);
    CCollisionManager::GetInst()->SetCollisionInteraction("Portal", "MonsterAttack", ECollision_Interaction::Ignore);
    CCollisionManager::GetInst()->SetCollisionInteraction("Portal", "Player", ECollision_Interaction::Collision);
    CCollisionManager::GetInst()->SetCollisionInteraction("Portal", "Rope", ECollision_Interaction::Ignore);

    CCollisionManager::GetInst()->SetCollisionInteraction("Player", "PlayerAttack", ECollision_Interaction::Ignore);
    CCollisionManager::GetInst()->SetCollisionInteraction("Player", "Die", ECollision_Interaction::Collision);
    CCollisionManager::GetInst()->SetCollisionInteraction("Player", "Monster", ECollision_Interaction::Collision);
    CCollisionManager::GetInst()->SetCollisionInteraction("Player", "Player", ECollision_Interaction::Ignore);
    CCollisionManager::GetInst()->SetCollisionInteraction("Player", "Portal", ECollision_Interaction::Collision);
    CCollisionManager::GetInst()->SetCollisionInteraction("Player", "Rope", ECollision_Interaction::Collision);
    CCollisionManager::GetInst()->SetCollisionInteraction("Player", "JungSY", ECollision_Interaction::Collision);

    CCollisionManager::GetInst()->SetCollisionInteraction("PlayerAttack", "Player", ECollision_Interaction::Ignore);
    CCollisionManager::GetInst()->SetCollisionInteraction("PlayerAttack", "Die", ECollision_Interaction::Ignore);
    CCollisionManager::GetInst()->SetCollisionInteraction("PlayerAttack", "MonsterAttack", ECollision_Interaction::Ignore);
    CCollisionManager::GetInst()->SetCollisionInteraction("PlayerAttack", "PlayerAttack", ECollision_Interaction::Ignore);
    CCollisionManager::GetInst()->SetCollisionInteraction("PlayerAttack", "JungSY", ECollision_Interaction::Ignore);

    CCollisionManager::GetInst()->SetCollisionInteraction("Monster", "Player", ECollision_Interaction::Collision);
    CCollisionManager::GetInst()->SetCollisionInteraction("Monster", "MonsterAttack", ECollision_Interaction::Ignore);
    CCollisionManager::GetInst()->SetCollisionInteraction("Monster", "Monster", ECollision_Interaction::Ignore);
    CCollisionManager::GetInst()->SetCollisionInteraction("Monster", "PlayerAttack", ECollision_Interaction::Collision);
    CCollisionManager::GetInst()->SetCollisionInteraction("Monster", "Die", ECollision_Interaction::Ignore);
    CCollisionManager::GetInst()->SetCollisionInteraction("Monster", "JungSY", ECollision_Interaction::Ignore);

    CCollisionManager::GetInst()->SetCollisionInteraction("MonsterAttack", "Monster", ECollision_Interaction::Ignore);
    CCollisionManager::GetInst()->SetCollisionInteraction("MonsterAttack", "MonsterAttack", ECollision_Interaction::Ignore);
    CCollisionManager::GetInst()->SetCollisionInteraction("MonsterAttack", "PlayerAttack", ECollision_Interaction::Ignore);
    CCollisionManager::GetInst()->SetCollisionInteraction("MonsterAttack", "Die", ECollision_Interaction::Ignore);
    CCollisionManager::GetInst()->SetCollisionInteraction("MonsterAttack", "JungSY", ECollision_Interaction::Ignore);

    CCollisionManager::GetInst()->SetCollisionInteraction("Rope", "Player", ECollision_Interaction::Collision);
    CCollisionManager::GetInst()->SetCollisionInteraction("Rope", "PlayerAttack", ECollision_Interaction::Ignore);
    CCollisionManager::GetInst()->SetCollisionInteraction("Rope", "Monster", ECollision_Interaction::Ignore);
    CCollisionManager::GetInst()->SetCollisionInteraction("Rope", "MonsterAttack", ECollision_Interaction::Ignore);
    CCollisionManager::GetInst()->SetCollisionInteraction("Rope", "Portal", ECollision_Interaction::Ignore);

    CCollisionManager::GetInst()->SetCollisionInteraction("Die", "Monster", ECollision_Interaction::Ignore);
    CCollisionManager::GetInst()->SetCollisionInteraction("Die", "MonsterAttack", ECollision_Interaction::Ignore);
    CCollisionManager::GetInst()->SetCollisionInteraction("Die", "PlayerAttack", ECollision_Interaction::Ignore);
    CCollisionManager::GetInst()->SetCollisionInteraction("Die", "Die", ECollision_Interaction::Ignore);
    CCollisionManager::GetInst()->SetCollisionInteraction("Die", "Player", ECollision_Interaction::Ignore);
    CCollisionManager::GetInst()->SetCollisionInteraction("Die", "JungSY", ECollision_Interaction::Ignore);
 
    CCollisionManager::GetInst()->SetCollisionInteraction("JungSY", "JungSY", ECollision_Interaction::Ignore);
    CCollisionManager::GetInst()->SetCollisionInteraction("JungSY", "Die", ECollision_Interaction::Ignore);
    CCollisionManager::GetInst()->SetCollisionInteraction("JungSY", "MonsterAttack", ECollision_Interaction::Ignore);
    CCollisionManager::GetInst()->SetCollisionInteraction("JungSY", "Monster", ECollision_Interaction::Ignore);
    CCollisionManager::GetInst()->SetCollisionInteraction("JungSY", "PlayerAttack", ECollision_Interaction::Ignore);
    CCollisionManager::GetInst()->SetCollisionInteraction("JungSY", "Player", ECollision_Interaction::Collision);
  

}
