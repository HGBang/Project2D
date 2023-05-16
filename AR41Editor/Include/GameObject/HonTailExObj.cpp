#include "HonTailExObj.h"
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

CHonTailExObj::CHonTailExObj()
{
	SetTypeID<CHonTailExObj>();
	m_ObjectTypeName = "HonTailExObj";
}

CHonTailExObj::CHonTailExObj(const CHonTailExObj& Obj) :
	CGameObject(Obj)
{
}

CHonTailExObj::~CHonTailExObj()
{
}

void CHonTailExObj::Start()
{
	CGameObject::Start();

	

	m_Animation = m_MainSprite->SetAnimation<CAnimation2D>("HonTailExObj");
	m_Animation->AddAnimation("HonTailMainHead_ExSkill", "HonTailMainHead_ExSkill");

	m_Animation->SetLoop("HonTailMainHead_ExSkill", false);

	m_Notify = m_Animation->FindAnimation("HonTailMainHead_ExSkill");
	m_Notify->AddNotify("HonTailMainHead_ExSkill", 8, this, &CHonTailExObj::ExNotify);


	m_Animation->SetCurrentEndFunction("HonTailMainHead_ExSkill", this, &CHonTailExObj::AnimationEndFunc);

	m_HitBox->SetCollisionCallback(ECollision_Result::Collision, this, &CHonTailExObj::CollisionOn);
	m_HitBox->SetCollisionCallback(ECollision_Result::Release, this, &CHonTailExObj::CollisionOff);

}

bool CHonTailExObj::Init()
{
	CGameObject::Init();

	m_HitBox = CreateComponent<CColliderBox2D>("HonTailObjBody");
	m_MainSprite = CreateComponent<CSpriteComponent>("HonTailObjSprite");

	SetRootComponent(m_HitBox);
	m_HitBox->AddChild(m_MainSprite);

	m_HitBox->SetCollisionProfile("Monster");

	m_HitBox->SetBoxSize(150.f, 600.f);
	m_MainSprite->SetPivot(0.5f, 0.5f);
	m_MainSprite->Set2DZOffset(5.f);


	return true;
}

void CHonTailExObj::Destory()
{
	CGameObject::Destroy();
}

void CHonTailExObj::Update(float DeltaTime)
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

void CHonTailExObj::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CHonTailExObj* CHonTailExObj::Clone() const
{
	return new CHonTailExObj(*this);
}

void CHonTailExObj::ExNotify()
{
	if (m_CollisionOn)
	{	
		CPlayer2D* Player = (CPlayer2D*)m_Scene->FindObject("Player2D");
		Vector2 PlayerPos = Player->GetWorldPos();
		HonTailHitEffect* HitEffect = m_Scene->CreateObject<HonTailHitEffect>("HonTailHitEffect");
		HitEffect->SetAnimation("HonTailMainHead_ExSkillHit");
		HitEffect->SetCollisionProfile("JungSY");
		HitEffect->SetWorldPosition(PlayerPos);	
	}
}

void CHonTailExObj::CollisionOn(const CollisionResult& result)
{
	m_CollisionOn = true;
}

void CHonTailExObj::CollisionOff(const CollisionResult& result)
{
	m_CollisionOn = false;
}

void CHonTailExObj::AnimationEndFunc()
{
	Destory();
}
