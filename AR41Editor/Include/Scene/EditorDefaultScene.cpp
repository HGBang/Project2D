
#include "EditorDefaultScene.h"
#include "Scene/Scene.h"
#include "Scene/SceneViewport.h"
#include "../UI/StartSceneUI.h"
#include "../UI/SelectPlayerUI.h"
#include "../UI/EquipmentUI.h"
#include "../UI/InventoryUI.h"
#include "../UI/StatusUI.h"
#include "UI/UINumber.h"
#include "UI/UIWindow.h"
#include "../UI/MonsterBarUI.h"
#include "../UI/ShopUI.h"
#include "../UI/QuestUI.h"
#include "../GameObject/Skelegon.h"
#include "Scene/SceneManager.h"


CEditorDefaultScene::CEditorDefaultScene()
{
	m_ClassTypeName = "EditorDefaultScene";
}

CEditorDefaultScene::~CEditorDefaultScene()
{
}

bool CEditorDefaultScene::Init()
{

	m_Owner->GetViewport()->CreateUIWindow<CQuestUI>("QuestUI");

    m_Owner->GetViewport()->CreateUIWindow<CShopUI>("ShopUI");

	//m_Owner->GetViewport()->CreateUIWindow<CShopUI>("QuestUI");
	// 
	m_Owner->GetViewport()->CreateUIWindow<CMonsterBarUI>("MonsterBarUI");

	//m_Owner->GetViewport()->CreateUIWindow<CSelectPlayerUI>("SelectPlayerUI");

	//m_Owner->GetViewport()->CreateUIWindow<CInventoryUI>("InventoryUI");

	//CResourceManager::GetInst()->SoundPlay("Henesis");
		
	//m_Owner->GetSceneInfo();



	//RespawnSkelegon(Vector2(200.f,200.f));
	//RespawnSkelegon(Vector2(300.f, 200.f));
	//RespawnSkelegon(Vector2(400.f, 200.f));

	return true;
}

void CEditorDefaultScene::RespawnSkelegon(const Vector2& MonsterPos)
{
	CScene* Scene = CSceneManager::GetInst()->GetScene();

	CSkelegon* Skelegon = Scene->CreateObject<CSkelegon>("Skelegon");
	Skelegon->SetWorldPosition(MonsterPos);
	Skelegon->SetScene(Scene);
}
