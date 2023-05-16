#include "Helena.h"
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

CHelena::CHelena()
{
    SetTypeID<CHelena>();
    m_ObjectTypeName = "Helena";
}

CHelena::CHelena(const CHelena& Obj) : 
    CGameObject(Obj)
{
    m_Body = (CColliderBox2D*)FindComponent("Body");
    m_MainSprite = (CSpriteComponent*)FindComponent("sprite");
    m_NameSprite = (CSpriteComponent*)FindComponent("spriteChild");
}

CHelena::~CHelena()
{
}

void CHelena::Start()
{
	CGameObject::Start();

    if (m_Scene)
        m_QuestUI = m_Scene->GetViewport()->FindUIWindow<CQuestUI>("QuestUI");

    else
        m_QuestUI = CSceneManager::GetInst()->GetScene()->GetViewport()->FindUIWindow<CQuestUI>("QuestUI");


    m_Animation = m_MainSprite->SetAnimation<CAnimation2D>("Helena");
    m_Animation->AddAnimation("Helena", "Helena");
    m_Animation->SetLoop("Helena", true);
    m_Animation->SetPlayTime("Helena", 0.7f); 


    m_NameSprite->SetTexture("HelenaName", TEXT("HelenaNameCard.png"));

    m_Body->SetCollisionMouseCallback(ECollision_Result::Click, this, &CHelena::QuestMouseClickCallback);
}

bool CHelena::Init()
{
    m_Body = CreateComponent<CColliderBox2D>("Body");
    m_MainSprite = CreateComponent<CSpriteComponent>("sprite");
    m_NameSprite = CreateComponent<CSpriteComponent>("spriteChild");


    SetRootComponent(m_Body);

    m_Body->AddChild(m_MainSprite);

    m_Body->SetCollisionProfile("Player");
    m_Body->SetWorldPosition(1147.f, 348.f);
    m_Body->SetPivot(0.f, 1.f);
    m_Body->SetBoxSize(Vector2(20.f, 150.f));

    m_MainSprite->SetPivot(0.5f, 0.5f);
    m_MainSprite->SetInheritRotZ(true);

    m_MainSprite->AddChild(m_NameSprite);

    m_NameSprite->SetRelativePosition(-22.f, -50.f);
    m_NameSprite->SetRelativeScale(1.f, 1.f);


	return true;
}

void CHelena::Update(float DeltaTime)
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

        m_NameSprite->SetRelativeScale(40.f, 15.f);
    } 
}

void CHelena::PostUpdate(float DeltaTime)
{
    CGameObject::PostUpdate(DeltaTime);
}

CHelena* CHelena::Clone() const
{
	return new CHelena(*this);
}

void CHelena::Save(FILE* File)
{
    CGameObject::Save(File);
}

void CHelena::Load(FILE* File)
{
    CGameObject::Load(File);
}

void CHelena::QuestMouseClickCallback(const CollisionResult& result)
{
    if (m_QuestUI->GetHelenaFirstQuest())
        m_QuestUI->SetHelenaFirstQuest();

    if (m_QuestUI->GetHelenaNoQuest())
        m_QuestUI->SetHelenaNoQuest();

    if (m_QuestUI->GetHelenaSecondQuest())
        m_QuestUI->SetHelenaSecondQuest();

}
