#include "ElderNpc.h"
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


CElderNpc::CElderNpc()
{
    SetTypeID<CElderNpc>();
    m_ObjectTypeName = "ElderNpc";
}

CElderNpc::CElderNpc(const CElderNpc& Obj) :
    CGameObject(Obj)
{
    m_Body = (CColliderBox2D*)FindComponent("Body");
    m_MainSprite = (CSpriteComponent*)FindComponent("sprite");
    m_QuestSprite = (CSpriteComponent*)FindComponent("QuestSprite");
}

CElderNpc::~CElderNpc()
{
}

void CElderNpc::Start()
{
    CGameObject::Start();

    if (m_Scene)
        m_QuestUI = m_Scene->GetViewport()->FindUIWindow<CQuestUI>("QuestUI");

    else
        m_QuestUI = CSceneManager::GetInst()->GetScene()->GetViewport()->FindUIWindow<CQuestUI>("QuestUI");

    m_QuestAnimation = m_QuestSprite->SetAnimation<CAnimation2D>("QuestIcon");
    m_QuestAnimation->AddAnimation("QuestIcon", "QuestIcon");
    m_QuestAnimation->AddAnimation("QuestIng", "QuestIng");
    m_QuestAnimation->AddAnimation("QuestComplete", "QuestComplete");

    m_QuestAnimation->SetLoop("QuestIcon", true);
    m_QuestAnimation->SetLoop("QuestIng", true);
    m_QuestAnimation->SetLoop("QuestComplete", true);



    m_Body->SetCollisionMouseCallback(ECollision_Result::Click, this, &CElderNpc::QuestMouseClickCallback);
}

bool CElderNpc::Init()
{
    CGameObject::Init();

    m_Body = CreateComponent<CColliderBox2D>("Body");
    m_MainSprite = CreateComponent<CSpriteComponent>("sprite");
    m_QuestSprite = CreateComponent<CSpriteComponent>("QuestSprite");


    SetRootComponent(m_Body);

    m_Body->AddChild(m_MainSprite);

    m_Body->SetCollisionProfile("Player");
    m_Body->SetWorldPosition(1147.f, 348.f);
    m_Body->SetPivot(0.f, 1.f);
    m_Body->SetBoxSize(Vector2(20.f, 150.f));
    m_Body->SetCollisionMouseCallback(ECollision_Result::Click, this, &CElderNpc::QuestMouseClickCallback);    
    

    m_MainSprite->SetPivot(0.5f, 0.5f);
    m_MainSprite->SetInheritRotZ(true);

    m_MainSprite->AddChild(m_QuestSprite);

    m_Animation = m_MainSprite->SetAnimation<CAnimation2D>("Elder");
    m_Animation->AddAnimation("Elder", "Elder");
    m_Animation->SetLoop("Elder", true);
    m_Animation->SetPlayTime("Elder", 0.7f);

    if (m_Scene)
        m_QuestUI = m_Scene->GetViewport()->FindUIWindow<CQuestUI>("QuestUI");

    else
        m_QuestUI = CSceneManager::GetInst()->GetScene()->GetViewport()->FindUIWindow<CQuestUI>("QuestUI");




    //CMaterial* QuestMaterial = m_QuestSprite->GetMaterial(0);
    //QuestMaterial->SetOpacity(0.f);

    return true;
}

void CElderNpc::Update(float DeltaTime)
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

    if (m_Scene->GetName() != "Henesis")
    {

        if (m_QuestAnimation)
        {
            float ImageWidth, ImageHeight;
            int Count = m_QuestAnimation->GetCurrentFrame(m_QuestAnimation->GetCurrentAnimName());
            ImageWidth = (float)(m_QuestAnimation->GetCurrentAnimationSequence(m_QuestAnimation->GetCurrentAnimName())->GetTexture()->GetWidth(Count));
            ImageHeight = (float)(m_QuestAnimation->GetCurrentAnimationSequence(m_QuestAnimation->GetCurrentAnimName())->GetTexture()->GetHeight(Count));

            m_QuestSprite->SetRelativeScale(ImageWidth, ImageHeight);
            m_QuestSprite->SetPivot(0.5f, 0.5f);

        }

        m_QuestSprite->SetWorldPosition(m_Body->GetWorldPos().x, m_Body->GetWorldPos().y + 60.f);

        if (m_QuestUI->GetFrontQuest() || m_QuestUI->GetClassChangeQuest() || m_QuestUI->GetBossQuest())
        {
            m_QuestAnimation->ChangeAnimation("QuestIcon");
        }

        if (m_QuestUI->GetQuestIng())
        {
            m_QuestAnimation->ChangeAnimation("QuestIng");
        }

        if (m_QuestUI->GetFrontQuestComplete() && !m_QuestUI->GetNoQuest())
        {
            m_QuestAnimation->ChangeAnimation("QuestComplete");
        }

        if (m_QuestUI->GetNoQuest())
        {
            CMaterial* Material = m_QuestSprite->GetMaterial(0);
            Material->SetOpacity(0.f);
        }

    }

}

void CElderNpc::PostUpdate(float DeltaTime)
{
    CGameObject::PostUpdate(DeltaTime);
}

CElderNpc* CElderNpc::Clone() const
{
    return new CElderNpc(*this);
}

void CElderNpc::Save(FILE* File)
{
    CGameObject::Save(File);
}

void CElderNpc::Load(FILE* File)
{
    CGameObject::Load(File);

}

void CElderNpc::QuestMouseClickCallback(const CollisionResult& result)
{
    if (m_QuestUI->GetFrontQuest())
        m_QuestUI->SetFrontQuest();

    if (m_QuestUI->GetQuestIng())
        m_QuestUI->SetQuestIng();

    if (m_QuestUI->GetFrontQuestComplete())
        m_QuestUI->SetFrontQuestComplete();
}


