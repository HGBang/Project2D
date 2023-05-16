#include "Rope.h"
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


CRope::CRope()
{
	SetTypeID<CRope>();
	m_ObjectTypeName = "Rope";
}

CRope::CRope(const CRope& Obj) : 
	CGameObject(Obj)
{
	m_Body = (CColliderBox2D*)FindComponent("Body");
}

CRope::~CRope()
{
}

void CRope::Start()
{
	CGameObject::Start();

	m_Body->SetBoxSize(Vector2(11.f, 161.f));

	//m_Body->SetBoxSize(11.f, 277.f);

}

bool CRope::Init()
{

	m_Body = CreateComponent<CColliderBox2D>("Body");

	SetRootComponent(m_Body);
	m_Body->SetCollisionProfile("Rope");

	m_Body->SetWorldPosition(2950.f, 520.f);
	m_Body->SetPivot(0.5f, 0.5f);


	return true;
}

void CRope::Save(FILE* File)
{
	CGameObject::Save(File);
}

void CRope::Load(FILE* File)
{
	CGameObject::Load(File);
}

void CRope::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CRope::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);

	if (m_Scene)
	{
		if (m_Scene->GetName() == "Basic")
			m_Body->SetBoxSize(11.f, 277.f);
	}
}

CRope* CRope::Clone() const
{
	return new CRope(*this);
}
