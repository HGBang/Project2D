#include "EditorTestScene.h"
#include "../UI/TestSceneUI.h"
#include "Scene/Scene.h"
#include "Scene/SceneViewport.h"
#include "../UI/GameStartUI.h"

CEditorTestScene::CEditorTestScene()
{
	m_ClassTypeName = "EditorTestScene";
}

CEditorTestScene::~CEditorTestScene()
{
}

bool CEditorTestScene::Init()
{
	m_Owner->GetViewport()->CreateUIWindow<CGameStartUI>("GameStartUI");

	return true;
}
