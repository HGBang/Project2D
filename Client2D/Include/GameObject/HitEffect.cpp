#include "HitEffect.h"
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


CHitEffect::CHitEffect()
{
	SetTypeID<CHitEffect>();

	m_ObjectTypeName = "Effect";
}

CHitEffect::CHitEffect(const CHitEffect& Obj) :
	CGameObject(Obj)
{
}

CHitEffect::~CHitEffect()
{
}


void CHitEffect::Start()
{
	CGameObject::Start();
}

bool CHitEffect::Init()
{
	CGameObject::Init();
	m_Sprite = CreateComponent<CSpriteComponent>("Sprite");

	m_Sprite->SetPivot(0.5f, 0.5f);

	m_HitAnimation = m_Sprite->SetAnimation<CAnimation2D>("Ring_Effect");
	m_HitAnimation->AddAnimation("Ring_Effect", "Ring_Effect");
	m_HitAnimation->AddAnimation("SpeedDualShotHit", "SpeedDualShotHit");
	m_HitAnimation->AddAnimation("NormalAttackHit", "NormalAttackHit");

	//1 . ±âº» °ø°Ý ÇÇ°Ý ÀÌÆåÆ®
	m_HitAnimation->SetLoop("NormalAttackHit", false);
	m_HitAnimation->SetPlayTime("NormalAttackHit", 0.1f);

	//2 . ½ºÇÇµå µà¾ó¼¦ ÇÇ°Ý ÀÌÆåÆ®
	m_HitAnimation->SetLoop("SpeedDualShotHit", false);
	m_HitAnimation->SetPlayTime("SpeedDualShotHit", 0.1f);

	//3 . ÀÌ½´Å¸¸£ÀÇ¸µ ÇÇ°Ý ÀÌÆåÆ®
	m_HitAnimation->SetLoop("Ring_Effect", false);
	m_HitAnimation->SetPlayTime("Ring_Effect", 0.1f);


	m_HitAnimation->SetCurrentEndFunction<CHitEffect>("NormalAttackHit", this, &CHitEffect::SoundPlay);
	m_HitAnimation->SetCurrentEndFunction<CHitEffect>("SpeedDualShotHit", this, &CHitEffect::SoundPlay);
	m_HitAnimation->SetCurrentEndFunction<CHitEffect>("Ring_Effect", this, &CHitEffect::SoundPlay);


	
	return true;
}

void CHitEffect::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);


	if (m_HitAnimation)
	{
		float ImageWidth, ImageHeight;
		int Count = m_HitAnimation->GetCurrentFrame(m_HitAnimation->GetCurrentAnimName());
		ImageWidth = (float)(m_HitAnimation->GetCurrentAnimationSequence(m_HitAnimation->GetCurrentAnimName())->GetTexture()->GetWidth(Count));
		ImageHeight = (float)(m_HitAnimation->GetCurrentAnimationSequence(m_HitAnimation->GetCurrentAnimName())->GetTexture()->GetHeight(Count));

		m_Sprite->SetRelativeScale(ImageWidth, ImageHeight);
	}
}

void CHitEffect::Destory()
{
	CGameObject::Destroy();
}

void CHitEffect::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CHitEffect* CHitEffect::Clone() const
{
	return new CHitEffect(*this);
}

void CHitEffect::SetAnimation(const std::string& Name)
{
	m_HitAnimation->ChangeAnimation(Name);
}

void CHitEffect::SoundPlay()
{
	if (m_HitAnimation->GetCurrentAnimName() == "NormalAttackHit")
		m_Scene->GetResource()->SoundPlay("NormalAttack_Hit");

	if (m_HitAnimation->GetCurrentAnimName() == "SpeedDualShotHit")
		m_Scene->GetResource()->SoundPlay("SpeedDualShot_Hit");

	if (m_HitAnimation->GetCurrentAnimName() == "Ring_Effect")
		m_Scene->GetResource()->SoundPlay("Ring_Hit");

	Destroy();
}


