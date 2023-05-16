#include "SceneWindow.h"
#include "Editor/EditorButton.h"
#include "Editor/EditorSameLine.h"
#include "Editor/EditorLabel.h"
#include "Editor/EditorImage.h"
#include "Editor/EditorText.h"
#include "Editor/EditorInput.h"
#include "Editor/EditorListBox.h"
#include "Editor/EditorComboBox.h"
#include "Editor/EditorTree.h"
#include "PathManager.h"
#include "Scene/SceneManager.h"
#include "Scene/Scene.h"
#include "../GameObject/Monster.h"
#include "../GameObject/Player2D.h"
#include "ObjectWindow.h"
#include "ComponentWindow.h"
#include "Editor/EditorGUIManager.h"

#include "Component/SpriteComponent.h"
#include "Component/CameraComponent.h"
#include "Component/TargetArm.h"
#include "../../../AR41Editor/Include/Scene/EditorDefaultScene.h"
#include "../../../Client2D/Include/Scene/MainSceneInfo.h"


CSceneWindow::CSceneWindow()
{
}

CSceneWindow::~CSceneWindow()
{
}

bool CSceneWindow::Init()
{

	CEditorButton* Button = CreateWidget<CEditorButton>("Scene 변경", 150.f, 30.f);

	Button->SetColor(29, 47, 73, 255);
	Button->SetClickCallback<CSceneWindow>(this, &CSceneWindow::SceneChange);

	CEditorSameLine* Line = CreateWidget<CEditorSameLine>("Line");

	m_SceneSaveName = CreateWidget<CEditorInput>("SceneSaveName");

	m_SceneSaveName->SetHideName("SceneSaveName");
	m_SceneSaveName->SetSize(150.f, 30.f);

	Line = CreateWidget<CEditorSameLine>("Line");

	Button = CreateWidget<CEditorButton>("Scene 저장", 150.f, 30.f);

	Button->SetColor(29, 47, 73, 255);
	Button->SetClickCallback<CSceneWindow>(this, &CSceneWindow::SceneSave);

	CEditorLabel* Label = CreateWidget<CEditorLabel>("Scene 목록");

	Label->SetColor(255, 0, 0, 255);
	Label->SetAlign(0.5f, 0.5f);
	Label->SetSizeY(30.f);

    Line = CreateWidget<CEditorSameLine>("Line");

	m_SceneList = CreateWidget<CEditorListBox>("SceneListBox");

	m_SceneList->SetHideName("SceneListBox");

	m_SceneList->SetSize(150.f, 300.f);
	m_SceneList->SetPageItemCount(6);

	m_SceneList->SetSelectCallback<CSceneWindow>(this, &CSceneWindow::SceneClickCallback);


	Line = CreateWidget<CEditorSameLine>("Line");

	m_SceneSelectName = CreateWidget<CEditorInput>("SceneName");

	m_SceneSelectName->SetHideName("SceneName");
	m_SceneSelectName->SetSize(150.f, 30.f);
	m_SceneSelectName->ReadOnly(true);


	Label = CreateWidget<CEditorLabel>("SceneInfo 리스트");

	Label->SetColor(255, 0, 0, 255);
	Label->SetAlign(0.5f, 0.5f);
	Label->SetSize(200.f,30.f);

	//m_CreateSceneName = CreateWidget<CEditorInput>("Scene Name");
	//m_CreateSceneName->SetSizeX(200.f);

	m_SceneCreateList = CreateWidget<CEditorListBox>("SceneInfo");
	m_SceneCreateList->SetHideName("SceneInfo");
	m_SceneCreateList->SetSizeX(200.f);
	m_SceneCreateList->SetPageItemCount(5);
	m_SceneCreateList->SetSelectCallback<CSceneWindow>(this, &CSceneWindow::SceneInfoListCallback);


	Line = CreateWidget<CEditorSameLine>("Line");

	m_SceneCreateButton = CreateWidget<CEditorButton>("Scene 만들기");
	m_SceneCreateButton->SetClickCallback<CSceneWindow>(this, &CSceneWindow::SceneCreateButtonCallback);
	m_SceneCreateButton->SetSize(200.f, 120.f);

	LoadSceneDirectory();
	LoadSceneInfo();

	return true;
}

void CSceneWindow::Update(float DeltaTime)
{
	CEditorWindow::Update(DeltaTime);
}

void CSceneWindow::SceneChange()
{
	CScene* Scene = CSceneManager::GetInst()->GetScene();

	if (Scene->GetName() == m_SelectSceneItem && m_SelectSceneItem.empty())
		return;

	CSceneManager::GetInst()->CreateNextScene(true);

	CScene* NextScene = CSceneManager::GetInst()->GetNextScene();

	const PathInfo* Info = CPathManager::GetInst()->FindPath(ROOT_PATH);

	char FullPath[MAX_PATH] = {};

	if (Info)
		strcpy_s(FullPath, Info->PathMultibyte);

	strcat_s(FullPath, "Scene/");
	strcat_s(FullPath, m_SelectSceneItem.c_str());
	strcat_s(FullPath, ".scn");

	NextScene->Load(FullPath);

	 //완료된 오브젝트 목록을 불러온다 .

	CObjectWindow* ObjectWindow = CEditorGUIManager::GetInst()->FindEditorWindow<CObjectWindow>("ObjectWindow");

	std::vector<HierarchyObjectName> vecName;

	NextScene->GetAllGameObjectHierarchyName(vecName);

	size_t Size = vecName.size();

	for (size_t i = 0; i < Size; ++i)
	{
		ObjectWindow->AddItem(vecName[i].Obj, vecName[i].Name);
	}

}

void CSceneWindow::SceneSave()
{
    std::string Name = m_SceneSaveName->GetText();

	if (Name.empty())
		return;

	const PathInfo* Info = CPathManager::GetInst()->FindPath(ROOT_PATH);

	char FullPath[MAX_PATH] = {};

	if (Info)
		strcpy_s(FullPath, Info->PathMultibyte);

	strcat_s(FullPath, "Scene/");
	strcat_s(FullPath, Name.c_str());
	strcat_s(FullPath, ".scn");

	CScene* Scene = CSceneManager::GetInst()->GetScene();

	Scene->SetName(Name);

	Scene->Save(FullPath);

	if(!m_SceneList->CheckItem(Name))
		m_SceneList->AddItem(Name);
}

void CSceneWindow::SceneClickCallback(int Index, const std::string& Item)
{
	m_SelectSceneItem = Item;

	m_SceneSelectName->SetText(Item.c_str());
}

void CSceneWindow::LoadSceneDirectory()
{
	const PathInfo* Info = CPathManager::GetInst()->FindPath(ROOT_PATH);

	char	Path[MAX_PATH] = {};

	strcpy_s(Path, Info->PathMultibyte);
	//strcat_s(Path, "Scene/");


	int	Length = (int)strlen(Path);

	// Root Path에서 Bin\을 지워준다.
	for (int i = Length - 5; i >= 0; --i)
	{
		if (Path[i] == '/' || Path[i] == '\\')
		{
			memset(&Path[i + 1], 0, sizeof(TCHAR) * (Length - i - 1));
			break;
		}
	}

	char	Directory[MAX_PATH] = {};

	strcpy_s(Directory, Path);

	// Editor의 GameObject폴더에 있는 파일을 읽어온다.
	strcat_s(Directory, "Include/Scene/");


	for (const auto& file : std::filesystem::directory_iterator(Directory))
	{
		char	Name[64] = {};
		char	FullPath[MAX_PATH] = {};
		char	Ext[_MAX_EXT] = {};

		strcpy_s(FullPath, file.path().generic_string().c_str());

		_splitpath_s(FullPath, nullptr, 0, nullptr, 0, Name, 64, Ext, _MAX_EXT);


		if (strcmp(Ext, ".cpp") == 0)
			continue;

		m_SceneCreateList->AddItem(Name);
	}

	const PathInfo* ClientInfo = CPathManager::GetInst()->FindPath(ROOT_PATH);

	char	ClientPath[MAX_PATH] = {};

	strcpy_s(ClientPath, ClientInfo->PathMultibyte);
	//strcat_s(Path, "Scene/");


	int	ClientLength = (int)strlen(ClientPath);

	// Root Path에서 Bin\을 지워준다.
	for (int i = ClientLength - 12; i >= 0; --i)
	{
		if (ClientPath[i] == '/' || ClientPath[i] == '\\')
		{
			memset(&ClientPath[i + 1], 0, sizeof(TCHAR) * (ClientLength - i - 1));
			break;
		}
	}

	char	ClientDirectory[MAX_PATH] = {};

	strcpy_s(ClientDirectory, ClientPath);

	// Editor의 GameObject폴더에 있는 파일을 읽어온다.
	strcat_s(ClientDirectory, "Client2D/Include/Scene/");


	for (const auto& file : std::filesystem::directory_iterator(ClientDirectory))
	{
		int i = 1;
		char	Name[64] = {};
		char	FullPath[MAX_PATH] = {};
		char	Ext[_MAX_EXT] = {};

		strcpy_s(FullPath, file.path().generic_string().c_str());

		_splitpath_s(FullPath, nullptr, 0, nullptr, 0, Name, 64, Ext, _MAX_EXT);


		if (strcmp(Ext, ".cpp") == 0)
			continue;

		if (Name == m_SceneCreateList->GetItem(i))
			continue;

		m_SceneCreateList->AddItem(Name);

		++i;
	}

}

void CSceneWindow::SceneInfoListCallback(int Index, const std::string& Item)
{
	if (Item == "EditorDefaultScene")
	{
		m_SelectSceneInfoItem = "CEditorDefaultScene";
	}

	if (Item == "MainSceneInfo")
	{
		m_SelectSceneInfoItem = "CMainSceneInfo";
	}

	if (Item == "EditorTestScene")
	{
		m_SelectSceneInfoItem = "CEditorTestScene";
	}

	//m_SelectSceneInfoItem = Item;	
}

void CSceneWindow::SceneCreateButtonCallback()
{	
	
	if (m_SelectSceneInfoItem == "CEditorDefaultScene")
	{
		//std::string Name = m_CreateSceneName->GetText();
		CScene* Scene = CSceneManager::GetInst()->GetNextScene();	
		CSceneManager::GetInst()->CreateNextScene(true);
		CSceneManager::GetInst()->ChangeNextScene();
	    CSceneManager::GetInst()->CreateSceneInfo<CEditorDefaultScene>(Scene);
	
	
		//CScene* Scene = CSceneManager::GetInst()->GetScene(); // A 

		//CScene* NextScene = CSceneManager::GetInst()->GetNextScene(); // A

		//if (NextScene)
		//{
		//	NextScene = Scene;
		//	CSceneManager::GetInst()->CreateNextScene(true);
		//}		

		//if(Scene)

		//const PathInfo* Info = CPathManager::GetInst()->FindPath(ROOT_PATH);

		//char FullPath[MAX_PATH] = {};		

		//if (Info)
		//	strcpy_s(FullPath, Info->PathMultibyte);

		//strcat_s(FullPath, "Scene/");
		//strcat_s(FullPath, Name.c_str());
		//strcat_s(FullPath, ".scn");
		
		//CScene* NextScene = CSceneManager::GetInst()->GetNextScene();

	    //NextScene = Scene;

		//Scene->SetName(Name);

		//Scene->Save(FullPath);


		//if (!m_SceneList->CheckItem(Name))
			//m_SceneList->AddItem(Name);

	

	}

	if (m_SelectSceneInfoItem == "CEditorTestScene")
	{
		//std::string Name = m_CreateSceneName->GetText();
		CScene* Scene = CSceneManager::GetInst()->GetNextScene();
		CSceneManager::GetInst()->CreateNextScene(true);
		CSceneManager::GetInst()->ChangeNextScene();
	

		/*const PathInfo* Info = CPathManager::GetInst()->FindPath(ROOT_PATH);

		char FullPath[MAX_PATH] = {};

		if (Info)
			strcpy_s(FullPath, Info->PathMultibyte);

		strcat_s(FullPath, "Scene/");
		strcat_s(FullPath, Name.c_str());
		strcat_s(FullPath, ".scn");

		CScene* Scene = CSceneManager::GetInst()->GetScene();

		Scene->SetName(Name);

		Scene->Save(FullPath);

		if (!m_SceneList->CheckItem(Name))
			m_SceneList->AddItem(Name);*/

		//CSceneManager::GetInst()->ChangeNextScene();
		//CSceneManager::GetInst()->CreateNextScene();
		//CScene* Scene = CSceneManager::

	}

}

void CSceneWindow::LoadSceneInfo()
{
	const PathInfo* Info = CPathManager::GetInst()->FindPath(ROOT_PATH);

	char	Path[MAX_PATH] = {};

	strcpy_s(Path, Info->PathMultibyte);
	strcat_s(Path, "Scene/");


	for (const auto& file : std::filesystem::directory_iterator(Path))
	{
		char	Name[64] = {};
		char	FullPath[MAX_PATH] = {};
		char	Ext[_MAX_EXT] = {};

		strcpy_s(FullPath, file.path().generic_string().c_str());

		_splitpath_s(FullPath, nullptr, 0, nullptr, 0, Name, 64, Ext, _MAX_EXT);

		m_SceneList->AddItem(Name);
	}
}
