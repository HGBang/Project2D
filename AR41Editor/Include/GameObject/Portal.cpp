#include "Portal.h"
#include "Component/SpriteComponent.h"
#include "Input.h"
#include "Device.h"
#include "Component/TargetArm.h"
#include "Component/ColliderBox2D.h"
#include "Component/ColliderSphere2D.h"
#include "Component/ColliderOBB2D.h"
#include "Scene/CameraManager.h"
#include "Component/CameraComponent.h"
#include "Scene/Scene.h"
#include "Resource/Material/Material.h"
#include "Animation/Animation2D.h"
#include "Bullet.h"
#include "Resource/Sound/Sound.h"
#include "Scene/SceneManager.h"
#include "Scene/Scene.h"
#include "Resource/Sound/SoundManager.h"
#include "Component/MovementComponent.h"
#include "Component/NavigationAgent.h"
#include "Component/UIComponent.h"
#include "../Setting/DefaultSetting.h"
#include "Engine.h"
#include "../Setting/EngineShareSetting.h"
#include "../UI/QuestUI.h"
#include "Resource/Material/Material.h"
#include "UI/UIButton.h"
#include "UI/UIWindow.h"
#include "PathManager.h"
#include "../GamePlayerSaveLoad.h"
#include "../GamePlayerPosSaveLoad.h"
#include "TimerManager.h"

CPortal::CPortal()
{
	SetTypeID<CPortal>();
	m_ObjectTypeName = "Portal";
}

CPortal::CPortal(const CPortal& Obj) : 
	CGameObject(Obj)
{
	m_Body = (CColliderBox2D*)FindComponent("Body");
	m_MainSprite = (CSpriteComponent*)FindComponent("sprite");
}

CPortal::~CPortal()
{
}

void CPortal::Start()
{
	CGameObject::Start();

	m_Body->SetCollisionCallback(ECollision_Result::Collision, this, &CPortal::PortalMove);
	m_Body->SetCollisionCallback(ECollision_Result::Release, this, &CPortal::PortalMoveOff);

	m_Animation = m_MainSprite->SetAnimation<CAnimation2D>("Potal");
	m_Animation->AddAnimation("Potal", "Potal");
	m_Animation->SetLoop("Potal", true);
	m_Animation->SetPlayTime("Potal", 0.7f);


}

bool CPortal::Init()
{
	CGameObject::Init();

	m_Body = CreateComponent<CColliderBox2D>("Body");
	m_MainSprite = CreateComponent<CSpriteComponent>("sprite");

	SetRootComponent(m_Body);

	m_Body->AddChild(m_MainSprite);

	m_Body->SetCollisionProfile("Portal");
	m_Body->SetWorldPosition(915.f, 150.f);
	m_Body->SetPivot(0.5f, 0.5f);
	m_Body->SetBoxSize(Vector2(130.f, 50.f));

	//m_MainSprite->SetPivot(0.5f, 0.5f);
	m_MainSprite->SetInheritRotZ(true);




	return true;
}



void CPortal::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	m_PortalName;

	if (m_Animation)
	{
		float ImageWidth, ImageHeight;
		int Count = m_Animation->GetCurrentFrame(m_Animation->GetCurrentAnimName());
		ImageWidth = (float)(m_Animation->GetCurrentAnimationSequence(m_Animation->GetCurrentAnimName())->GetTexture()->GetWidth(Count));
		ImageHeight = (float)(m_Animation->GetCurrentAnimationSequence(m_Animation->GetCurrentAnimName())->GetTexture()->GetHeight(Count));

		m_MainSprite->SetRelativeScale(ImageWidth, ImageHeight);		
	}


}

void CPortal::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);

	m_PortalName;

	if (m_PortalName == "HenesisToShop")
	{
		if (m_PortalMove && GetAsyncKeyState(VK_UP) & 0x8000)
		{			
			CGamePlayerSaveLoad::GetInst()->Save();
			CGamePlayerPosSaveLoad::GetInst()->Save();

			m_Scene->GetResource()->SoundStop("Henesis");

			CScene* Scene = CSceneManager::GetInst()->GetScene();

			CSceneManager::GetInst()->CreateNextScene(true);

			CScene* NextScene = CSceneManager::GetInst()->GetNextScene();

			NextScene->Load("HenesisShop.scn", SCENE_PATH);
		}
	}

	if (m_PortalName == "ShopToHenesis")
	{
		if (m_PortalMove && GetAsyncKeyState(VK_UP) & 0x8000)
		{
			CGamePlayerSaveLoad::GetInst()->Save();

			m_Scene->GetResource()->SoundStop("Henesis");

			CScene* Scene = CSceneManager::GetInst()->GetScene();

			CSceneManager::GetInst()->CreateNextScene(true);

			CScene* NextScene = CSceneManager::GetInst()->GetNextScene();

			NextScene->Load("Henesis.scn", SCENE_PATH);
		}
	}

	if (m_PortalName == "HenesisToClass")
	{
		if (m_PortalMove && GetAsyncKeyState(VK_UP) & 0x8000)
		{
			CGamePlayerSaveLoad::GetInst()->Save();
			CGamePlayerPosSaveLoad::GetInst()->Save();

			m_Scene->GetResource()->SoundStop("Henesis");

			CScene* Scene = CSceneManager::GetInst()->GetScene();

			CSceneManager::GetInst()->CreateNextScene(true);

			CScene* NextScene = CSceneManager::GetInst()->GetNextScene();

			NextScene->Load("HenesisClass.scn", SCENE_PATH);
		}
	}

	if (m_PortalName == "HenesisClassToHenesis")
	{
		if (m_PortalMove && GetAsyncKeyState(VK_UP) & 0x8000)
		{			
			CGamePlayerSaveLoad::GetInst()->Save();

			m_Scene->GetResource()->SoundStop("Henesis");

			CScene* Scene = CSceneManager::GetInst()->GetScene();

			CSceneManager::GetInst()->CreateNextScene(true);

			CScene* NextScene = CSceneManager::GetInst()->GetNextScene();

			NextScene->Load("Henesis.scn", SCENE_PATH);
		}
	}

	if (m_PortalName == "HenesisToHonTailFront")
	{
		if (m_PortalMove && GetAsyncKeyState(VK_UP) & 0x8000)
		{
			CGamePlayerSaveLoad::GetInst()->Save();
			CGamePlayerPosSaveLoad::GetInst()->Save();

			m_Scene->GetResource()->SoundStop("Henesis");

			CScene* Scene = CSceneManager::GetInst()->GetScene();

			CSceneManager::GetInst()->CreateNextScene(true);

			CScene* NextScene = CSceneManager::GetInst()->GetNextScene();

			NextScene->Load("HonTailFront.scn", SCENE_PATH);
		}
	}

	if (m_PortalName == "HonTailFrontToHenesis")
	{
		if (m_PortalMove && GetAsyncKeyState(VK_UP) & 0x8000)
		{
			CGamePlayerSaveLoad::GetInst()->Save();

			m_Scene->GetResource()->SoundStop("HonTailFront");

			CScene* Scene = CSceneManager::GetInst()->GetScene();

			CSceneManager::GetInst()->CreateNextScene(true);

			CScene* NextScene = CSceneManager::GetInst()->GetNextScene();

			NextScene->Load("Henesis.scn", SCENE_PATH);
		}
	}

	if (m_PortalName == "HonTailFrontToHonTail")
	{
		if (m_PortalMove && GetAsyncKeyState(VK_UP) & 0x8000)
		{
			CGamePlayerSaveLoad::GetInst()->Save();		

			m_Scene->GetResource()->SoundStop("HonTailFront");

			CScene* Scene = CSceneManager::GetInst()->GetScene();

			CSceneManager::GetInst()->CreateNextScene(true);

			CScene* NextScene = CSceneManager::GetInst()->GetNextScene();

			NextScene->Load("HonTail.scn", SCENE_PATH);
		}
	}


	if (m_PortalName == "HenesisToBasic")
	{
		if (m_PortalMove && GetAsyncKeyState(VK_UP) & 0x8000)
		{
			CGamePlayerSaveLoad::GetInst()->Save();
			CGamePlayerPosSaveLoad::GetInst()->Save();

			m_Scene->GetResource()->SoundStop("Henesis");

			CScene* Scene = CSceneManager::GetInst()->GetScene();

			CSceneManager::GetInst()->CreateNextScene(true);

			CScene* NextScene = CSceneManager::GetInst()->GetNextScene();

			NextScene->Load("Basic.scn", SCENE_PATH);
		}
	}

	if (m_PortalName == "BasicToHenesis")
	{
		if (m_PortalMove && GetAsyncKeyState(VK_UP) & 0x8000)
		{
			CTimerManager::GetInst()->DestroyInst();

			CGamePlayerSaveLoad::GetInst()->Save();

			m_Scene->GetResource()->SoundStop("Basic");

			CScene* Scene = CSceneManager::GetInst()->GetScene();

			CSceneManager::GetInst()->CreateNextScene(true);

			CScene* NextScene = CSceneManager::GetInst()->GetNextScene();

			NextScene->Load("Henesis.scn", SCENE_PATH);
		}
	}








}

CPortal* CPortal::Clone() const
{
	return new CPortal(*this);
}

void CPortal::PortalMove(const CollisionResult& result)
{
	m_PortalMove = true;
}
void CPortal::PortalMoveOff(const CollisionResult& result)
{
	m_PortalMove = false;
}
void CPortal::Save(FILE* File)
{
	CGameObject::Save(File);

	int	Length = (int)m_PortalName.length();

	fwrite(&Length, 4, 1, File);
	fwrite(m_PortalName.c_str(), 1, Length, File);
}

void CPortal::Load(FILE* File)
{
	CGameObject::Load(File);

	// 이름 저장
	int	Length = 0;
	char	Name[256] = {};

	fread(&Length, 4, 1, File);
	fread(Name, 1, Length, File);

	m_PortalName = Name;
}