#include "SelectPlayer.h"
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
#include "../UI/StartSceneUI.h"
#include "../UI/SelectPlayerUI.h"

CSelectPlayer::CSelectPlayer()
{
	SetTypeID<CSelectPlayer>();
	m_ObjectTypeName = "SelectPlayer";
}

CSelectPlayer::CSelectPlayer(const CSelectPlayer& Obj) : 
	CGameObject(Obj)
{
	m_Sprite = (CSpriteComponent*)FindComponent("sprite");
	m_Body = (CColliderBox2D*)FindComponent("Body");
	m_Effect = (CSpriteComponent*)FindComponent("spriteChild");
}

CSelectPlayer::~CSelectPlayer()
{
}

void CSelectPlayer::Start()
{
	CGameObject::Start();



	m_EffectAnimation = m_Effect->SetAnimation<CAnimation2D>("SelectPlayerEffect");
	m_EffectAnimation->AddAnimation("SelectPlayerEffect", "SelectPlayerEffect");

	m_EffectAnimation->SetLoop("SelectPlayerEffect", true);
	m_EffectAnimation->SetPlayTime("SelectPlayerEffect", 2.0f);

	m_Animation = m_Sprite->SetAnimation<CAnimation2D>("PlayerNormalStand");
	m_Animation->AddAnimation("PlayerNormalStand", "PlayerNormalStand");
	m_Animation->AddAnimation("PlayerNormalWalk", "PlayerNormalWalk");

	m_Animation->SetLoop("PlayerNormalStand", true);
	m_Animation->SetPlayTime("PlayerNormalStand", 4.0f);

	m_Animation->SetLoop("PlayerNormalWalk", true);
	m_Animation->SetPlayTime("PlayerNormalWalk", 0.7f);

	m_Animation->SetCurrentAnimation("PlayerNormalStand");
}

bool CSelectPlayer::Init()
{
	CGameObject::Init();

	m_Body = CreateComponent<CColliderBox2D>("Body");
	m_Sprite = CreateComponent<CSpriteComponent>("sprite");
	m_Effect = CreateComponent<CSpriteComponent>("spriteChild");

	SetRootComponent(m_Body);

	m_Body->AddChild(m_Sprite);

	m_Body->SetCollisionProfile("Player");
	m_Body->SetWorldPosition(500.f, 500.f);
	m_Body->SetBoxSize(Vector2(100.f, 100.f));
	
	m_Sprite->SetPivot(0.5f, 0.5f);
	m_Sprite->SetInheritRotZ(true);
	//m_Sprite->SetWorldScale(100.f, 100.f);

	m_Sprite->AddChild(m_Effect);

	m_Effect->SetRelativePositionY(37.f);
	m_Effect->SetPivot(0.5f, 0.5f);
	
	CMaterial* Material = m_Effect->GetMaterial(0);
	Material->SetOpacity(0.f);





	return true;
}

void CSelectPlayer::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	if (m_Animation)
	{
		float ImageWidth, ImageHeight;
		int Count = m_Animation->GetCurrentFrame(m_Animation->GetCurrentAnimName());
		ImageWidth = (float)(m_Animation->GetCurrentAnimationSequence(m_Animation->GetCurrentAnimName())->GetTexture()->GetWidth(Count));
		ImageHeight = (float)(m_Animation->GetCurrentAnimationSequence(m_Animation->GetCurrentAnimName())->GetTexture()->GetHeight(Count));

		m_Sprite->SetRelativeScale(ImageWidth, ImageHeight);
		m_Sprite->SetPivot(0.5f, 0.5f);
	}

	if (m_EffectAnimation)
	{
		float ImageWidth, ImageHeight;
		int Count = m_EffectAnimation->GetCurrentFrame(m_EffectAnimation->GetCurrentAnimName());
		ImageWidth = (float)(m_EffectAnimation->GetCurrentAnimationSequence(m_EffectAnimation->GetCurrentAnimName())->GetTexture()->GetWidth(Count));
		ImageHeight = (float)(m_EffectAnimation->GetCurrentAnimationSequence(m_EffectAnimation->GetCurrentAnimName())->GetTexture()->GetHeight(Count));

		m_Effect->SetRelativeScale(ImageWidth, ImageHeight);
		m_Effect->SetPivot(0.5f, 0.5f);
	}

	CSelectPlayerUI* UIWindow = CSceneManager::GetInst()->GetScene()->GetViewport()->FindUIWindow<CSelectPlayerUI>("SelectPlayerUI");

	if (UIWindow)
	{
		if(UIWindow->GetSelectPlayer())
		{
			CMaterial* Material = m_Effect->GetMaterial(0);

			Material->SetOpacity(0.7f);

			m_Animation->ChangeAnimation("PlayerNormalWalk");
		}
	}

}

void CSelectPlayer::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CSelectPlayer* CSelectPlayer::Clone() const
{
	return new CSelectPlayer(*this);
}

void CSelectPlayer::Save(FILE* File)
{
	CGameObject::Save(File);
}

void CSelectPlayer::Load(FILE* File)
{
	CGameObject::Load(File);
}


