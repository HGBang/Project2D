
#include "Scene.h"
#include "../GameObject/GameObject.h"
#include "../Input.h"
#include "../Component/SpriteComponent.h"
#include "../Component/CameraComponent.h"
#include "../Component/TargetArm.h"
#include "../Component/SceneComponent.h"
#include "../Component/ColliderBox2D.h"
#include "../Component/TileMapComponent.h"
#include "../Component/NavigationAgent.h"
#include "../Component/MovementComponent.h"
#include "../Animation/Animation2D.h"
#include "../UI/UIButton.h"
#include "../UI/UIImage.h"
#include "../UI/UIWindow.h"
#include "../UI/UIProgressBar.h"
#include "../UI/UIText.h"
#include "../UI/UINumber.h"
#include "../PathManager.h"
#include "../GameObject/GameObject.h"



std::unordered_map<std::string, CSceneInfo*> CScene::m_mapSceneInfoCDO;

CScene::CScene() :
	m_Change(false),
	m_Start(false),
	m_PortalCount(0)
{
	m_Name = "Scene";

	m_SceneInfo = new CSceneInfo;

	m_SceneInfo->m_Owner = this;

	m_SceneInfo->Init();

	m_Resource = new CSceneResource;

	m_Resource->m_Owner = this;

	m_Resource->Init();

	m_CameraManager = new CCameraManager;

	m_CameraManager->m_Owner = this;

	m_CameraManager->Init();

	m_CollisionManager = new CSceneCollision;

	m_CollisionManager->m_Owner = this;

	m_CollisionManager->Init();

	m_Viewport = new CSceneViewport;

	m_Viewport->m_Owner = this;

	m_Viewport->Init();

	m_NavManager = new CNavigationManager;

	m_NavManager->m_Owner = this;

	m_NavManager->Init();
}

CScene::~CScene()
{
	CInput::GetInst()->ClearCallback(this);

	SAFE_DELETE(m_NavManager);
	SAFE_DELETE(m_Viewport);
	SAFE_DELETE(m_CollisionManager);
	SAFE_DELETE(m_CameraManager);
	SAFE_DELETE(m_Resource);
	SAFE_DELETE(m_SceneInfo);
}

void CScene::CreateCDO()
{
	// ==================== SceneInfo ====================
	CSceneInfo* Info = new CSceneInfo;

	Info->Init();

	CScene::AddSceneInfoCDO("SceneInfo", Info);


	// ==================== GameObject ====================
	CGameObject* ObjCDO = new CGameObject;

	ObjCDO->Init();

	CGameObject::AddObjectCDO("GameObject", ObjCDO);


	// ==================== Component ====================
	CComponent* ComCDO = new CSceneComponent;

	ComCDO->Init();

	CComponent::AddComponentCDO("SceneComponent", ComCDO);

	ComCDO = new CSpriteComponent;

	ComCDO->Init();

	CComponent::AddComponentCDO("SpriteComponent", ComCDO);

	ComCDO = new CCameraComponent;

	ComCDO->Init();

	CComponent::AddComponentCDO("CameraComponent", ComCDO);

	ComCDO = new CTargetArm;

	ComCDO->Init();

	CComponent::AddComponentCDO("TargetArm", ComCDO);

	ComCDO = new CColliderBox2D;

	ComCDO->Init();

	CComponent::AddComponentCDO("Box2D", ComCDO);

	ComCDO = new CTileMapComponent;

	ComCDO->Init();

	CComponent::AddComponentCDO("TileMapComponent", ComCDO);

	ComCDO = new CNavigationAgent;

	ComCDO->Init();

	CComponent::AddComponentCDO("NavigationAgent", ComCDO);

	ComCDO = new CMovementComponent;

	ComCDO->Init();

	CComponent::AddComponentCDO("MovementComponent", ComCDO);


	// ==================== Animation ====================
	CAnimation2D* AnimCDO = new CAnimation2D;

	AnimCDO->Init();

	CAnimation2D::AddAnimationCDO("Animation2D", AnimCDO);


	// ==================== UI ====================
	CUIWindow* UIWindowCDO = new CUIWindow;

	UIWindowCDO->Init();

	CUIWindow::AddUIWindowCDO("UIWindow", UIWindowCDO);

	CUIWidget* UIWidgetCDO = new CUIButton;

	UIWidgetCDO->Init();

	CUIWidget::AddUIWidgetCDO("UIButton", UIWidgetCDO);

	UIWidgetCDO = new CUIImage;

	UIWidgetCDO->Init();

	CUIWidget::AddUIWidgetCDO("UIImage", UIWidgetCDO);

	UIWidgetCDO = new CUIProgressBar;

	UIWidgetCDO->Init();

	CUIWidget::AddUIWidgetCDO("UIProgressBar", UIWidgetCDO);

	UIWidgetCDO = new CUINumber;

	UIWidgetCDO->Init();

	CUIWidget::AddUIWidgetCDO("UINumber", UIWidgetCDO);

	UIWidgetCDO = new CUIText;

	UIWidgetCDO->Init();

	CUIWidget::AddUIWidgetCDO("UIText", UIWidgetCDO);

}

void CScene::Start()
{
	m_Start = true;	

	auto	iter = m_ObjList.begin();
	auto	iterEnd = m_ObjList.end();

	for (; iter != iterEnd; ++iter)
	{
		(*iter)->Start();
	}

	m_CameraManager->Start();

	m_Viewport->Start();

	if (m_Name == "Henesis")
	{
		CResourceManager::GetInst()->SoundStop("FrontScene");
		CResourceManager::GetInst()->SoundStop("Basic");
		CResourceManager::GetInst()->LoadSound("BGM", "Henesis", true, "Henesis.mp3");
		CResourceManager::GetInst()->SetVolume(20);
		CResourceManager::GetInst()->SoundPlay("Henesis");
	}

	if (m_Name == "GameStart")
	{
		CResourceManager::GetInst()->LoadSound("BGM", "LoginBGM", true, "MapleLogin.mp3");
		CResourceManager::GetInst()->SetVolume(20);
		CResourceManager::GetInst()->SoundPlay("LoginBGM");
	}

	if (m_Name == "PlayerSelect")
	{
		CResourceManager::GetInst()->LoadSound("BGM", "LoginBGM", true, "MapleLogin.mp3");
		CResourceManager::GetInst()->SetVolume(20);
		CResourceManager::GetInst()->SoundPlay("LoginBGM");
	}

	if (m_Name == "FrontScene")
	{
		CResourceManager::GetInst()->SoundStop("LoginBGM");
		CResourceManager::GetInst()->LoadSound("BGM", "FrontScene", true, "HenesisGround.mp3");
		CResourceManager::GetInst()->SetVolume(20);
		CResourceManager::GetInst()->SoundPlay("FrontScene");
	}

	if (m_Name == "HenesisShop")
	{
		CResourceManager::GetInst()->SoundStop("Henesis");
		CResourceManager::GetInst()->LoadSound("BGM", "Henesis", true, "Henesis.mp3");
		CResourceManager::GetInst()->SetVolume(20);
		CResourceManager::GetInst()->SoundPlay("Henesis");
	}

	if (m_Name == "HenesisClass")
	{
		CResourceManager::GetInst()->SoundStop("Henesis");
		CResourceManager::GetInst()->LoadSound("BGM", "Henesis", true, "Henesis.mp3");
		CResourceManager::GetInst()->SetVolume(20);
		CResourceManager::GetInst()->SoundPlay("Henesis");
	}

	if (m_Name == "HonTailFront")
	{
		CResourceManager::GetInst()->SoundStop("Henesis");
		CResourceManager::GetInst()->LoadSound("BGM", "HonTailFront", true, "HonTailFront.mp3");
		CResourceManager::GetInst()->SetVolume(20);
		CResourceManager::GetInst()->SoundPlay("HonTailFront");
	}

	if (m_Name == "HonTail")
	{
		CResourceManager::GetInst()->SoundStop("HonTailFront");
		CResourceManager::GetInst()->LoadSound("BGM", "HonTailFront", true, "HonTailFront.mp3");
		CResourceManager::GetInst()->SetVolume(20);
		CResourceManager::GetInst()->SoundPlay("HonTailFront");
	}

	if (m_Name == "Basic")
	{
		CResourceManager::GetInst()->SoundStop("Henesis");
		CResourceManager::GetInst()->LoadSound("BGM", "Basic", true, "Basic.mp3");
		CResourceManager::GetInst()->SetVolume(20);
		CResourceManager::GetInst()->SoundPlay("Basic");
	}


}

bool CScene::Init()
{

	return true;
}

void CScene::FirstUpdate(float DeltaTime)
{

	if (m_SceneInfo)
		m_SceneInfo->Update(DeltaTime);

	auto	iter = m_ObjList.begin();
	auto	iterEnd = m_ObjList.end();

	for (; iter != iterEnd;)
	{
		if (!(*iter)->GetActive())
		{
			iter = m_ObjList.erase(iter);
			iterEnd = m_ObjList.end();
			continue;
		}

		else if (!(*iter)->GetEnable())
		{
			++iter;
			continue;
		}

		(*iter)->FirstUpdate(DeltaTime);
		++iter;
	}

}

void CScene::Update(float DeltaTime)
{
	auto	iter = m_ObjList.begin();
	auto	iterEnd = m_ObjList.end();

	for (; iter != iterEnd;)
	{
		if (!(*iter)->GetActive())
		{
			iter = m_ObjList.erase(iter);
			iterEnd = m_ObjList.end();
			continue;
		}

		else if (!(*iter)->GetEnable())
		{
			++iter;
			continue;
		}

		(*iter)->Update(DeltaTime);
		++iter;
	}

	m_CameraManager->Update(DeltaTime);

	m_Viewport->Update(DeltaTime);
}

void CScene::PostUpdate(float DeltaTime)
{
	if (m_SceneInfo)
		m_SceneInfo->PostUpdate(DeltaTime);

	auto	iter = m_ObjList.begin();
	auto	iterEnd = m_ObjList.end();

	for (; iter != iterEnd;)
	{
		if (!(*iter)->GetActive())
		{
			iter = m_ObjList.erase(iter);
			iterEnd = m_ObjList.end();
			continue;
		}

		else if (!(*iter)->GetEnable())
		{
			++iter;
			continue;
		}

		(*iter)->PostUpdate(DeltaTime);
		++iter;
	}

	m_CameraManager->PostUpdate(DeltaTime);

	m_Viewport->PostUpdate(DeltaTime);
}

void CScene::Collision(float DeltaTime)
{
	m_CollisionManager->Update(DeltaTime);
}

void CScene::Save(const char* FullPath)
{
	FILE* File = nullptr;

	fopen_s(&File, FullPath, "wb");

	if (!File)
		return;

	// 이름 저장
	int	Length = (int)m_Name.length();

	fwrite(&Length, 4, 1, File);
	fwrite(m_Name.c_str(), 1, Length, File);

	// SceneInfo 저장
	m_SceneInfo->Save(File);
	m_CameraManager->Save(File);
	m_CollisionManager->Save(File);
	m_Viewport->Save(File);

	int	ObjCount = (int)m_ObjList.size();

	fwrite(&ObjCount, 4, 1, File);

	auto	iter = m_ObjList.begin();
	auto	iterEnd = m_ObjList.end();

	for (; iter != iterEnd; ++iter)
	{
		std::string	ClassTypeName = (*iter)->GetObjectTypeName();

		Length = (int)ClassTypeName.length();

		fwrite(&Length, 4, 1, File);
		fwrite(ClassTypeName.c_str(), 1, Length, File);

		(*iter)->Save(File);
	}

	

	fclose(File);
}

void CScene::Load(const char* FullPath)
{
	FILE* File = nullptr;

	fopen_s(&File, FullPath, "rb");

	if (!File)
		return;

	// 이름 저장
	int	Length = 0;
	char	Name[256] = {};

	fread(&Length, 4, 1, File);
	fread(Name, 1, Length, File);

	m_Name = Name;

	// SceneInfo 저장
	Length = 0;
	char	SceneInfoName[256] = {};

	fread(&Length, 4, 1, File);
	fread(SceneInfoName, 1, Length, File);

	SAFE_DELETE(m_SceneInfo);

	CSceneInfo* CDO = FindSceneInfoCDO(SceneInfoName);

	if (!CDO)
		CDO = FindSceneInfoCDO("SceneInfo");

	m_SceneInfo = CDO->Clone();

	m_SceneInfo->m_Owner = this;

	m_SceneInfo->Load(File);

	m_CameraManager->m_Owner = this;
	m_CameraManager->Load(File);

	m_CollisionManager->m_Owner = this;
	m_CollisionManager->Load(File);

	m_Viewport->Load(File);

	int	ObjCount = 0;

	fread(&ObjCount, 4, 1, File);

	for (int i = 0; i < ObjCount; ++i)
	{
		Length = 0;

		char	ObjClassTypeName[256] = {};

		fread(&Length, 4, 1, File);
		fread(ObjClassTypeName, 1, Length, File);	

		CGameObject* ObjCDO = CGameObject::FindCDO(ObjClassTypeName);

		CGameObject* NewObj = ObjCDO->Clone();

		NewObj->SetScene(this);

		NewObj->Load(File);		

		if (NewObj->GetName() == "GameObject")
		{
			m_TileMap = nullptr;

			m_TileMap = (CTileMapComponent*)NewObj->FindComponent("TileMapComponent");
			if(m_TileMap)
				m_TileMap->SetScene(this);
		}		

		m_ObjList.push_back(NewObj);
	}	

	m_SceneInfo->LoadComplete();	

	fclose(File);
}

void CScene::Save(const char* FileName, const std::string& PathName)
{
	const PathInfo* Path = CPathManager::GetInst()->FindPath(PathName);

	char FullPath[MAX_PATH] = {};

	if (Path)
		strcpy_s(FullPath, Path->PathMultibyte);

	strcat_s(FullPath, FileName);

	Save(FullPath);
}

void CScene::Load(const char* FileName, const std::string& PathName)
{
	const PathInfo* Path = CPathManager::GetInst()->FindPath(PathName);

	char FullPath[MAX_PATH] = {};

	if (Path)
		strcpy_s(FullPath, Path->PathMultibyte);

	strcat_s(FullPath, FileName);

	Load(FullPath);
}

void CScene::GetAllGameObjectHierarchyName(std::vector<HierarchyObjectName>& vecName)
{
	auto    iter = m_ObjList.begin();
	auto    iterEnd = m_ObjList.end();

	for (; iter != iterEnd; ++iter)
	{
		HierarchyObjectName	Names;

		//CGameObject* Parent = (*iter)->GetParent();

		Names.Name = (*iter)->GetName();
		Names.ClassName = (*iter)->GetObjectTypeName();
		Names.Obj = *iter;
		//Names.Parent = Parent;

		/*if (Parent)
		{
			Names.ParentName = Parent->GetName();
			Names.ParentClassName = Parent->GetComponentTypeName();
		}*/

		vecName.push_back(Names);
	}
}

void CScene::SetTileMap(CTileMapComponent* TileMap)
{
	m_TileMap = TileMap;
}



CGameObject* CScene::FindObject(const std::string& Name)
{
	auto	iter = m_ObjList.begin();
	auto	iterEnd = m_ObjList.end();

	for (; iter != iterEnd; ++iter)
	{
		if ((*iter)->GetName() == Name)
			return *iter;
	}

	return nullptr;
}
