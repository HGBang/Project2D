#include "HonTailHitEffect.h"
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
#include "../UI/StartSceneUI.h"
#include <time.h>
#include "Player2D.h"
#include "Engine.h"

HonTailHitEffect::HonTailHitEffect()
{
	SetTypeID<HonTailHitEffect>();

	m_ObjectTypeName = "HonTailHitEffect";
}

HonTailHitEffect::HonTailHitEffect(const HonTailHitEffect& Obj) :
	CGameObject(Obj)
{
}

HonTailHitEffect::~HonTailHitEffect()
{
}


void HonTailHitEffect::Start()
{
	CGameObject::Start();
}

bool HonTailHitEffect::Init()
{
	CGameObject::Init();

	m_HonTailHitEffectSprite = CreateComponent<CSpriteComponent>("Sprite");
	m_HonTailHitCollider = CreateComponent<CColliderBox2D>("HitEffect");

	SetRootComponent(m_HonTailHitEffectSprite);

	m_HonTailHitEffectSprite->AddChild(m_HonTailHitCollider);

	m_HonTailHitCollider->SetCollisionProfile("Die");

	m_HonTailHitCollider->SetRelativePosition(0.f, 10.f);

	m_HonTailHitEffectSprite->SetPivot(0.5f, 0.5f);
	m_HonTailHitEffectSprite->Set2DZOffset(-200.f);

	m_HitEffectAnimation = m_HonTailHitEffectSprite->SetAnimation<CAnimation2D>("HonTail_HitEffect");
	m_HitEffectAnimation->AddAnimation("HonTailLeftHand_Hit", "HonTailLeftHand_Hit");
	m_HitEffectAnimation->AddAnimation("HonTailMainHead_Hit", "HonTailMainHead_Hit");
	m_HitEffectAnimation->AddAnimation("HonTailLeftHead_Hit", "HonTailLeftHead_Hit");
	m_HitEffectAnimation->AddAnimation("HonTailRightHead_Hit", "HonTailRightHead_Hit");
	m_HitEffectAnimation->AddAnimation("HonTailLeg_Hit", "HonTailLeg_Hit");
	m_HitEffectAnimation->AddAnimation("HonTailTail_Hit", "HonTailTail_Hit");
	m_HitEffectAnimation->AddAnimation("HonTailWing_Hit", "HonTailWing_Hit");
	m_HitEffectAnimation->AddAnimation("HonTailMainHeadSkill_Hit", "HonTailMainHeadSkill_Hit");
	m_HitEffectAnimation->AddAnimation("HonTailLeftHeadSkill_Hit", "HonTailLeftHeadSkill_Hit");
	m_HitEffectAnimation->AddAnimation("HonTailRightHeadSkill_Hit", "HonTailRightHeadSkill_Hit");
	m_HitEffectAnimation->AddAnimation("SkelegonHitEffect", "SkelegonHitEffect");
	m_HitEffectAnimation->AddAnimation("DarkWybernHitEffect", "DarkWybernHitEffect");
	m_HitEffectAnimation->AddAnimation("HonTailMainHead_ExSkillHit", "HonTailMainHead_ExSkillHit");
	

	m_HitEffectAnimation->SetCurrentEndFunction<HonTailHitEffect>("HonTailLeftHand_Hit", this, &HonTailHitEffect::EffectEndFuc);
	m_HitEffectAnimation->SetCurrentEndFunction<HonTailHitEffect>("HonTailMainHead_Hit", this, &HonTailHitEffect::EffectEndFuc);
	m_HitEffectAnimation->SetCurrentEndFunction<HonTailHitEffect>("HonTailLeftHead_Hit", this, &HonTailHitEffect::EffectEndFuc);
	m_HitEffectAnimation->SetCurrentEndFunction<HonTailHitEffect>("HonTailRightHead_Hit", this, &HonTailHitEffect::EffectEndFuc);
	m_HitEffectAnimation->SetCurrentEndFunction<HonTailHitEffect>("HonTailLeg_Hit", this, &HonTailHitEffect::EffectEndFuc);
	m_HitEffectAnimation->SetCurrentEndFunction<HonTailHitEffect>("HonTailTail_Hit", this, &HonTailHitEffect::EffectEndFuc);
	m_HitEffectAnimation->SetCurrentEndFunction<HonTailHitEffect>("HonTailWing_Hit", this, &HonTailHitEffect::EffectEndFuc);
	m_HitEffectAnimation->SetCurrentEndFunction<HonTailHitEffect>("HonTailMainHeadSkill_Hit", this, &HonTailHitEffect::EffectEndFuc);
	m_HitEffectAnimation->SetCurrentEndFunction<HonTailHitEffect>("HonTailLeftHeadSkill_Hit", this, &HonTailHitEffect::EffectEndFuc);
	m_HitEffectAnimation->SetCurrentEndFunction<HonTailHitEffect>("HonTailRightHeadSkill_Hit", this, &HonTailHitEffect::EffectEndFuc);
	m_HitEffectAnimation->SetCurrentEndFunction<HonTailHitEffect>("SkelegonHitEffect", this, &HonTailHitEffect::EffectEndFuc);
	m_HitEffectAnimation->SetCurrentEndFunction<HonTailHitEffect>("DarkWybernHitEffect", this, &HonTailHitEffect::EffectEndFuc);
	m_HitEffectAnimation->SetCurrentEndFunction<HonTailHitEffect>("HonTailMainHead_ExSkillHit", this, &HonTailHitEffect::EffectEndFuc);


	CAnimation2DData* Animation2DDate = m_HitEffectAnimation->FindAnimation("HonTailLeftHand_Hit");
	Animation2DDate->AddNotify("HonTailLeftHand_Hit", 13 , this, &HonTailHitEffect::EffectNotify);
	//Animation2DDate->AddNotify("HonTailRightHead_Hit", 3, this, &HonTailHitEffect::EffectNotify);

	m_HitEffectAnimation->SetLoop("HonTailLeftHand_Hit", false);
	m_HitEffectAnimation->SetPlayTime("HonTailLeftHand_Hit", 2.5f);
	m_HitEffectAnimation->SetPlayTime("HonTailRightHead_Hit", 0.7f);
	m_HitEffectAnimation->SetPlayTime("HonTailLeg_Hit", 0.7f);
	m_HitEffectAnimation->SetPlayTime("HonTailMainHead_Hit", 0.7f);
	m_HitEffectAnimation->SetPlayTime("HonTailLeftHead_Hit", 0.7f);
	m_HitEffectAnimation->SetPlayTime("HonTailRightHead_Hit", 0.7f);
	m_HitEffectAnimation->SetPlayTime("HonTailTail_Hit", 0.7f);
	m_HitEffectAnimation->SetPlayTime("HonTailWing_Hit", 0.7f);
	m_HitEffectAnimation->SetPlayTime("HonTailMainHeadSkill_Hit", 0.7f);
	m_HitEffectAnimation->SetPlayTime("SkelegonHitEffect", 0.7f);
	m_HitEffectAnimation->SetPlayTime("DarkWybernHitEffect", 0.7f);
	m_HitEffectAnimation->SetPlayTime("HonTailMainHead_ExSkillHit", 0.7f);

	m_Player = (CPlayer2D*)m_Scene->FindObject("Player2D");


	return true;
}

void HonTailHitEffect::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	float ImageWidth, ImageHeight;
	int Count = m_HitEffectAnimation->GetCurrentFrame(m_HitEffectAnimation->GetCurrentAnimName());
	ImageWidth = (float)(m_HitEffectAnimation->GetCurrentAnimationSequence(m_HitEffectAnimation->GetCurrentAnimName())->GetTexture()->GetWidth(Count));
	ImageHeight = (float)(m_HitEffectAnimation->GetCurrentAnimationSequence(m_HitEffectAnimation->GetCurrentAnimName())->GetTexture()->GetHeight(Count));

	m_HonTailHitEffectSprite->SetRelativeScale(ImageWidth, ImageHeight);
}

void HonTailHitEffect::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);

	m_RandomDamage = CEngine::GetInst()->GetNumber();

	if (m_HitEffectAnimation)
	{

		if (m_HitEffectAnimation->GetCurrentAnimName() == "HonTailLeftHand_Hit")
		{
			m_Damage = m_RandomDamage + 200;
		}

		if (m_HitEffectAnimation->GetCurrentAnimName() == "HonTailLeftHand_Hit")
		{
			m_Damage = m_RandomDamage + 200;
		}

		if (m_HitEffectAnimation->GetCurrentAnimName() == "HonTailLeftHead_Hit")
		{
			m_Damage = m_RandomDamage + 300;
		}

		if (m_HitEffectAnimation->GetCurrentAnimName() == "HonTailRightHead_Hit")
		{
			m_Damage = m_RandomDamage + 300;
		}

		if (m_HitEffectAnimation->GetCurrentAnimName() == "HonTailMainHead_Hit")
		{
			m_Damage = m_RandomDamage + 350;
		}

		if (m_HitEffectAnimation->GetCurrentAnimName() == "HonTailLeg_Hit")
		{
			m_Damage = m_RandomDamage + 100;
		}

		if (m_HitEffectAnimation->GetCurrentAnimName() == "HonTailWing_Hit")
		{
			m_Damage = m_RandomDamage + 250;
		}

		if (m_HitEffectAnimation->GetCurrentAnimName() == "HonTailTail_Hit")
		{
			m_Damage = m_RandomDamage + 350;
		}

		if (m_HitEffectAnimation->GetCurrentAnimName() == "HonTailLeftHeadSkill_Hit")
		{
			m_Damage = m_RandomDamage + 350;
		}

		if (m_HitEffectAnimation->GetCurrentAnimName() == "HonTailRightHeadSkill_Hit")
		{
			m_Damage = m_RandomDamage + 350;
		}

		if (m_HitEffectAnimation->GetCurrentAnimName() == "HonTailMainHeadSkill_Hit")
		{
			
			m_Damage = m_Player->GetHp() - 1;
			m_MpDamage = m_Player->GetMp() - 1;

		}

		if (m_HitEffectAnimation->GetCurrentAnimName() == "SkelegonHitEffect")
		{
			m_Damage = m_RandomDamage + 50;
		}

		if (m_HitEffectAnimation->GetCurrentAnimName() == "DarkWybernHitEffect")
		{
			m_Damage = m_RandomDamage + 20;
		}

		if (m_HitEffectAnimation->GetCurrentAnimName() == "HonTailMainHead_ExSkillHit")
		{
			m_Damage = m_RandomDamage + 500;
		}



			/*
    m_HitEffectAnimation->AddAnimation("HonTailLeftHand_Hit", "HonTailLeftHand_Hit");
	m_HitEffectAnimation->AddAnimation("HonTailMainHead_Hit", "HonTailMainHead_Hit");
	m_HitEffectAnimation->AddAnimation("HonTailLeftHead_Hit", "HonTailLeftHead_Hit");
	m_HitEffectAnimation->AddAnimation("HonTailRightHead_Hit", "HonTailRightHead_Hit");
	m_HitEffectAnimation->AddAnimation("HonTailLeg_Hit", "HonTailLeg_Hit");
	m_HitEffectAnimation->AddAnimation("HonTailTail_Hit", "HonTailTail_Hit");
	m_HitEffectAnimation->AddAnimation("HonTailWing_Hit", "HonTailWing_Hit");
			
			*/





	}

}

HonTailHitEffect* HonTailHitEffect::Clone() const
{
	return new HonTailHitEffect(*this);
}

void HonTailHitEffect::SetAnimation(const std::string& Name)
{
	m_HitEffectAnimation->ChangeAnimation(Name);
}

void HonTailHitEffect::SetCollisionProfile(const std::string& Name)
{
	m_HonTailHitCollider->SetCollisionProfile(Name);
}

const std::string HonTailHitEffect::GetCurrentAnimName()
{
	return m_HitEffectAnimation->GetCurrentAnimName();
}

void HonTailHitEffect::Destory()
{
	Destroy();
}

void HonTailHitEffect::EffectEndFuc()
{	
	Destory();
}

void HonTailHitEffect::EffectNotify()
{
	m_HonTailHitCollider->SetCollisionProfile("JungSY");
}

