#include "SkillEffect.h"
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
#include "HonTailHitEffect.h"
#include "Player2D.h"
#include "Scene/Scene.h"
#include "Scene/SceneManager.h"

CSkillEffect::CSkillEffect()
{
    SetTypeID<CSkillEffect>();

    m_ObjectTypeName = "SkillEffect";
}

CSkillEffect::CSkillEffect(const CSkillEffect& Obj) : 
    CGameObject(Obj)
{
}

CSkillEffect::~CSkillEffect()
{
}

void CSkillEffect::Start()
{
    CGameObject::Start();

    CSceneManager::GetInst()->GetScene()->GetResource()->LoadSound("Effect", "FlashJump", false, "FlashJump.mp3");

    m_Animation = m_MainSprite->SetAnimation<CAnimation2D>("SkillEffect");
    m_Animation->AddAnimation("FlashJumpEffect", "FlashJumpEffect");
    m_Animation->SetCurrentStartFunction<CSkillEffect>("FlashJumpEffect", this, &CSkillEffect::SkillEffectStartFunc);
    m_Animation->SetCurrentEndFunction<CSkillEffect>("FlashJumpEffect", this, &CSkillEffect::SkillEffectEndFunc);

    m_Animation->SetPlayTime("FlashJumpEffect", 0.7f);

}

bool CSkillEffect::Init()
{
    CGameObject::Init();

    m_MainSprite = CreateComponent<CSpriteComponent>("SkillEffect");

    SetRootComponent(m_MainSprite);

    m_MainSprite->SetPivot(0.5f, 0.5f);

    return true;
}

void CSkillEffect::Destory()
{
    CGameObject::Destroy();
}

void CSkillEffect::Update(float DeltaTime)
{
    CGameObject::Update(DeltaTime);
    
    if (m_Animation)
    {
        float ImageWidth, ImageHeight;
        int Count = m_Animation->GetCurrentFrame(m_Animation->GetCurrentAnimName());
        ImageWidth = (float)(m_Animation->GetCurrentAnimationSequence(m_Animation->GetCurrentAnimName())->GetTexture()->GetWidth(Count));
        ImageHeight = (float)(m_Animation->GetCurrentAnimationSequence(m_Animation->GetCurrentAnimName())->GetTexture()->GetHeight(Count));

        m_MainSprite->SetRelativeScale(ImageWidth, ImageHeight);
    }
}

void CSkillEffect::PostUpdate(float DeltaTime)
{
    CGameObject::PostUpdate(DeltaTime);
}

CSkillEffect* CSkillEffect::Clone() const
{
    return new CSkillEffect(*this);
}

void CSkillEffect::SetAnimation(const std::string& Name ,float PlayTime , bool Loop)
{
    m_Animation->SetPlayTime(Name, PlayTime);
    m_Animation->SetLoop(Name, Loop);
    m_Animation->ChangeAnimation(Name);
}

void CSkillEffect::SetReverseX(bool Reverse)
{    
    m_MainSprite->SetReverseX(Reverse);
}

void CSkillEffect::SkillEffectStartFunc()
{
    m_Scene->GetResource()->SoundPlay("FlashJump");
}

void CSkillEffect::SkillEffectEndFunc()
{
    Destory();
}
