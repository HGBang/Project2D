#include "ShopNpc.h"
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
#include "Scene/SceneManager.h"
#include "../UI/ShopUI.h"

CShopNpc::CShopNpc()
{
    SetTypeID<CShopNpc>();
    m_ObjectTypeName = "ShopNpc";
}

CShopNpc::CShopNpc(const CShopNpc& Obj) : 
	CGameObject(Obj)
{
	m_Body = (CColliderBox2D*)FindComponent("Body");
	m_MainSprite = (CSpriteComponent*)FindComponent("sprite");
}

CShopNpc::~CShopNpc()
{
}

void CShopNpc::Start()
{
	CGameObject::Start();

    if (m_Scene)
        m_ShopUI = m_Scene->GetViewport()->FindUIWindow<CShopUI>("ShopUI");

    else
        CSceneManager::GetInst()->GetScene()->GetViewport()->FindUIWindow<CShopUI>("ShopUI");

    m_ShopUI->SetEnable(false);
    m_MainSprite->SetReverseX(true);

    m_Body->SetCollisionMouseCallback(ECollision_Result::Click, this, &CShopNpc::ShopMouseClick);

    m_Animation = m_MainSprite->SetAnimation<CAnimation2D>("MapleShopNpc");
    m_Animation->AddAnimation("MapleShopNpc", "MapleShopNpc");
    m_Animation->SetLoop("MapleShopNpc", true);
    m_Animation->SetPlayTime("MapleShopNpc", 0.7f);
 
}

bool CShopNpc::Init()
{
	m_Body = CreateComponent<CColliderBox2D>("Body");
	m_MainSprite = CreateComponent<CSpriteComponent>("sprite");

	SetRootComponent(m_Body);

	m_Body->AddChild(m_MainSprite);

    m_Body->SetCollisionProfile("Player");
    m_Body->SetWorldPosition(483.f, 196.f);
    m_Body->SetPivot(0.5f, 0.5f);
    m_Body->SetBoxSize(Vector2(50.f, 50.f));



    m_MainSprite->SetPivot(0.5f, 0.5f);
    m_MainSprite->SetInheritRotZ(true);
    m_MainSprite->SetReverseX(true);



	return true;
}

void CShopNpc::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

    if (m_Animation)
    {
        float ImageWidth, ImageHeight;
        int Count = m_Animation->GetCurrentFrame(m_Animation->GetCurrentAnimName());
        ImageWidth = (float)(m_Animation->GetCurrentAnimationSequence(m_Animation->GetCurrentAnimName())->GetTexture()->GetWidth(Count));
        ImageHeight = (float)(m_Animation->GetCurrentAnimationSequence(m_Animation->GetCurrentAnimName())->GetTexture()->GetHeight(Count));

        m_MainSprite->SetRelativeScale(ImageWidth, ImageHeight);
        m_MainSprite->SetPivot(0.5f, 0.5f);
    }

}

void CShopNpc::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CShopNpc* CShopNpc::Clone() const
{
	return new CShopNpc(*this);
}

void CShopNpc::ShopMouseClick(const CollisionResult& result)
{
    if (!m_ShopUI->GetEnable())
        m_ShopUI->SetEnable(true);
}
