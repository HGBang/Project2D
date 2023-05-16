#include "HonTailSummon.h"
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

CHonTailSummon::CHonTailSummon()
{
	SetTypeID<CHonTailSummon>();
	m_ObjectTypeName = "Summon";
}

CHonTailSummon::CHonTailSummon(const CHonTailSummon& Obj) :
	CGameObject(Obj)
{
	m_Body = (CColliderBox2D*)FindComponent("HonTailSummon");
	m_MainSprite = (CSpriteComponent*)FindComponent("HonTailSummonSprite");
}

CHonTailSummon::~CHonTailSummon()
{
}


void CHonTailSummon::Start()
{
	CGameObject::Start();

	DeadCount = 5;

	m_Body->SetCollisionCallback<CHonTailSummon>(ECollision_Result::Collision, this, &CHonTailSummon::HonTailSummonCallBack);
}

bool CHonTailSummon::Init()
{
	CGameObject::Init();

	m_Body = CreateComponent<CColliderBox2D>("HonTailSummon");
	m_MainSprite = CreateComponent<CSpriteComponent>("HonTailSummonSprite");

	SetRootComponent(m_Body);

	m_Body->AddChild(m_MainSprite);
	m_Body->SetWorldPosition(1200.f, 175.f);
	m_Body->SetCollisionProfile("Monster");

	m_MainSprite->SetTexture("HonTailSummon", TEXT("HonTailSummon.png"));
	m_MainSprite->SetWorldScale(199.f, 250.f);
	m_MainSprite->SetPivot(0.5f, 0.2f);

	return true;
}

void CHonTailSummon::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	int i = 0;
}

void CHonTailSummon::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CHonTailSummon* CHonTailSummon::Clone() const
{
	return new CHonTailSummon(*this);
}

void CHonTailSummon::HonTailSummonCallBack(const CollisionResult& result)
{
	--DeadCount;

	if (DeadCount == 0)
	{
		m_Scene->CreateObject<CHonTail>("HonTail");
		Destroy();
	}

}
