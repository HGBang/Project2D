#include "HonTailWall.h"
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
#include "../GameObject/HonTail.h"

CHonTailWall::CHonTailWall()
{
	SetTypeID<CHonTailWall>();
	m_ObjectTypeName = "HonTailWall";
}

CHonTailWall::CHonTailWall(const CHonTailWall& Obj) :
	CGameObject(Obj)
{
	m_MainSprite = (CSpriteComponent*)FindComponent("HonTailWallSprite");
}

CHonTailWall::~CHonTailWall()
{
}

void CHonTailWall::Start()
{
	CGameObject::Start();
}

bool CHonTailWall::Init()
{
	CGameObject::Init();

	m_MainSprite = CreateComponent<CSpriteComponent>("HonTailWallSprite");

	SetRootComponent(m_MainSprite);

	m_MainSprite->SetTexture("HonTailWall", TEXT("HonTailWall.png"));
	m_MainSprite->SetWorldScale(800.f, 354.f);
	m_MainSprite->SetPivot(0.5f, 0.5f);

	m_MainSprite->SetWorldPosition(655.f, 100.f);

	return true;
}

void CHonTailWall::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
	m_MainSprite->Set2DZOffset(1.f);
}

void CHonTailWall::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CHonTailWall* CHonTailWall::Clone() const
{
	return new CHonTailWall(*this);
}
