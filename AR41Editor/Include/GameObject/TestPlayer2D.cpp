#include "TestPlayer2D.h"
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





CTestPlayer2D::CTestPlayer2D() :
	m_Start1(true)
{
	SetTypeID<CTestPlayer2D>();
	m_ObjectTypeName = "TestPlayer2D";
}

CTestPlayer2D::CTestPlayer2D(const CTestPlayer2D& Obj) :
	CGameObject(Obj)
{
	m_Sprite = (CSpriteComponent*)FindComponent("sprite");
	m_RightChild = (CSceneComponent*)FindComponent("RightChild");
	m_SpriteChild = (CSpriteComponent*)FindComponent("spriteChild");
	m_Camera = (CCameraComponent*)FindComponent("Camera");
	m_Arm = (CTargetArm*)FindComponent("Arm");
	m_Body = (CColliderBox2D*)FindComponent("Body");
}

CTestPlayer2D::~CTestPlayer2D()
{
}

void CTestPlayer2D::Start()
{
	CGameObject::Start();

	if (m_Scene)
		m_Scene->GetCameraManager()->SetCurrentCamera(m_Camera);

	CInput::GetInst()->AddBindFunction<CTestPlayer2D>("MoveUp", Input_Type::Push,
		this, &CTestPlayer2D::MoveUp, m_Scene);
	CInput::GetInst()->AddBindFunction<CTestPlayer2D>("MoveDown", Input_Type::Push,
		this, &CTestPlayer2D::MoveDown, m_Scene);
	CInput::GetInst()->AddBindFunction<CTestPlayer2D>("Rotation", Input_Type::Push,
		this, &CTestPlayer2D::MoveRight, m_Scene);
	CInput::GetInst()->AddBindFunction<CTestPlayer2D>("RotationInv", Input_Type::Push,
		this, &CTestPlayer2D::MoveLeft, m_Scene);

	CInput::GetInst()->AddBindFunction<CTestPlayer2D>("Rotation", Input_Type::Up,
		this, &CTestPlayer2D::RightUp, m_Scene);
	CInput::GetInst()->AddBindFunction<CTestPlayer2D>("RotationInv", Input_Type::Up,
		this, &CTestPlayer2D::LeftUp, m_Scene);

	CInput::GetInst()->AddBindFunction<CTestPlayer2D>("Fire", Input_Type::Push,
		this, &CTestPlayer2D::Fire, m_Scene);
	CInput::GetInst()->AddBindFunction<CTestPlayer2D>("Fire", Input_Type::Down,
		this, &CTestPlayer2D::FireEffect, m_Scene);
	CInput::GetInst()->AddBindFunction<CTestPlayer2D>("Fire", Input_Type::Up,
		this, &CTestPlayer2D::FireUp, m_Scene);




}

bool CTestPlayer2D::Init()
{
	CGameObject::Init();

	m_Body = CreateComponent<CColliderBox2D>("Body");
	m_Sprite = CreateComponent<CSpriteComponent>("sprite");
	m_RightChild = CreateComponent<CSceneComponent>("RightChild");
	m_SpriteChild = CreateComponent<CSpriteComponent>("spriteChild");
	m_Camera = CreateComponent<CCameraComponent>("Camera");
	m_Arm = CreateComponent<CTargetArm>("Arm");

	SetRootComponent(m_Body);

	m_Body->AddChild(m_Sprite);

	m_Body->SetCollisionProfile("Player");
	m_Body->SetWorldPosition(500.f, 500.f);
	m_Body->SetBoxSize(200.f, 200.f);

	//m_Body->SetBoxSize(200.f, 200.f);

	m_Sprite->AddChild(m_SpriteChild);


	//m_Sprite->SetRelativeScale(200.f, 200.f);
	m_Sprite->SetPivot(0.5f, 0.5f);
	m_Sprite->SetInheritRotZ(true);
	m_Sprite->SetChangeWidthHeight(true);

	CMaterial* Material = m_Sprite->GetMaterial(0);


	//m_SpriteChild->GetMaterial(0)->SetOpacity(1.f);
	m_SpriteChild->SetRelativeScale(500.f, 500.f);
	m_SpriteChild->SetPivot(0.5f, 0.5f);
	m_SpriteChild->GetMaterial(0)->SetOpacity(0.f);
	//m_SpriteChild->SetWorldScale(500.f, 500.f);

	//m_Sprite->GetMaterial(0)->SetBaseColorUnsignedChar(255, 255, 0, 255);

	m_Sprite->AddChild(m_Arm);
	m_Arm->AddChild(m_Camera);

	Resolution RS = CDevice::GetInst()->GetResolution();

	float Width = (float)RS.Width / 2.f;
	float Height = (float)RS.Height / 2.f;

	m_Arm->SetTargetOffset(Vector3(-Width, -Height, 0.f));

	//m_RightChild->AddChild(m_SpriteChild);

	//Material->SetOpacity(0.5f);
	//Material->SetRenderState("DepthDisable");

	//m_RightChild->SetRelativePosition(50.f, 0.f);
	//m_RightChild->SetInheritRotZ(true);

	//m_SkillSprite->SetRelativeScale(50.f, 50.f);
	//m_SkillSprite->SetRelativePosition(100.f, 0.f);
	//m_SkillSprite->SetInheritRotZ(true);


	//m_SkillAnimation->AddAnimation("Idle", "PlayerIdle");

	//m_Sprite->SetPivot(1.5f, 0.5f);

	//m_SkillAnimation->AddAnimationState("Ring_Right", "Idle", [=]() {return !m_Ring; });

	//CResourceManager::GetInst()->GetAnim2DConstantBuffer()->

	m_Animation = m_Sprite->SetAnimation<CAnimation2D>("PlayerWeaponWalkTest");
	m_Animation->AddAnimation("PlayerWeaponWalkTest", "PlayerWeaponWalkTest");
	m_Animation->SetLoop("PlayerWeaponWalkTest", true);
	m_Animation->SetPlayTime("PlayerWeaponWalkTest", 0.7f);

	/*m_Animation = m_Sprite->SetAnimation<CAnimation2D>("PlayerWeaponWalk");
	m_Animation->AddAnimation("PlayerWeaponWalk", "PlayerWeaponWalk");
	m_Animation->SetLoop("PlayerWeaponWalk", true);
	m_Animation->SetPlayTime("PlayerWeaponWalk", 0.7f);*/


	//m_Animation->AddAnimation("PlayerWeaponStand", "PlayerWeaponStand");

	//m_Animation->AddAnimation("PlayerWeaponAttack", "PlayerWeaponAttack");

	//m_Animation->AddAnimation("PlayerNormalStand", "PlayerNormalStand");
	//m_Animation->AddAnimation("PlayerNormalWalk", "PlayerNormalWalk");
	//m_Animation->AddAnimation("PlayerNormalAttack", "PlayerNormalAttack");

	//m_Animation->SetCurrentAnimation("PlayerNormalStand");
	//m_Animation->SetCurrentAnimation("PlayerWeaponStand");

	// 무기없는 상태 애니메이션
	//m_Animation->SetLoop("PlayerNormalStand", true);
	//m_Animation->SetPlayTime("PlayerNormalStand", 4.0f);

	//m_Animation->SetLoop("PlayerNormalWalk", true);
	//m_Animation->SetPlayTime("PlayerNormalWalk", 0.7f);

	//m_Animation->SetLoop("PlayerNormalAttack", true);
	//m_Animation->SetPlayTime("PlayerNormalAttack", 0.7f);

	// 무기착용 상태 애니메이션
	//m_Animation->SetLoop("PlayerWeaponStand", true);
	//m_Animation->SetPlayTime("PlayerWeaponStand", 4.0f);



	//m_Animation->SetLoop("PlayerWeaponAttack", true);
	//m_Animation->SetPlayTime("PlayerWeaponAttack", 0.7f);



	//m_Animation->AddAnimation("IdleRight", "PlayerIdle_Right");

	//m_Animation->AddAnimation("Left", "PlayerWalk_Left");

	//m_Animation->AddAnimation("Right", "PlayerWalk_Right");

	//m_Animation->AddAnimation("Ring_AttackRight", "Ring_AttackRight");

	//m_Animation->AddAnimation("Ring_AttackLeft", "Ring_AttackLeft");

	//m_Animation->GetCurrentFrame("PlayerNormalAttack");	

	//m_Animation->AddAnimationState("PlayerNormalStand", "PlayerNormalWalk", [=]() {return m_MoveOn; });
	//m_Animation->AddAnimationState("PlayerNormalWalk", "PlayerNormalStand", [=]() {return !m_MoveOn; });

	//m_Animation->AddAnimationState("PlayerNormalStand", "PlayerNormalAttack", [=]() {return m_Attack; });
	//m_Animation->AddAnimationState("PlayerNormalAttack", "PlayerNormalStand", [=]() {return !m_Attack; });

	//m_Animation->AddAnimationState("PlayerWeaponStand", "PlayerWeaponWalk", [=]() {return m_MoveOn; });
	//m_Animation->AddAnimationState("PlayerWeaponWalk", "PlayerWeaponStand", [=]() {return !m_MoveOn; });

	//m_Animation->AddAnimationState("PlayerWeaponStand", "PlayerWeaponAttack", [=]() {return m_Attack; });
	//m_Animation->AddAnimationState("PlayerWeaponAttack", "PlayerWeaponStand", [=]() {return !m_Attack; });


	//m_Animation->SetCurrentAnimation("PlayerWeaponWalk");
	//m_Animation->AddAnimationState("IdleLeft", "Right", [=]() {return m_MoveRightOn; });
	//m_Animation->AddAnimationState("Right", "IdleRight", [=]() {return !m_MoveRightOn; });


	//m_Animation->AddAnimationState("Ring_AttackLeft", "IdleLeft", [=]() {return !m_SkillOn; });
	//m_Animation->AddAnimationState("Ring_AttackRight", "IdleRight", [=]() {return !m_SkillOn; });

	m_Weapon = true;

	return true;
}

void CTestPlayer2D::Update(float DeltaTime)
{


	CGameObject::Update(DeltaTime);

	float Width, Height;
	int Count = m_Animation->GetCurrentFrame(m_Animation->GetCurrentAnimName());

	Width = (float)(m_Animation->GetCurrentAnimationSequence(m_Animation->GetCurrentAnimName())->GetTexture()->GetWidth(Count));
	Height = (float)(m_Animation->GetCurrentAnimationSequence(m_Animation->GetCurrentAnimName())->GetTexture()->GetHeight(Count));

	m_Sprite->SetRelativeScale(Width, Height);
	

	//if (m_Animation)
	//{
	//	float Width, Height;
	//	int Count = m_Animation->GetCurrentFrame(m_Animation->GetCurrentAnimName());
	//	Width = (float)(m_Animation->GetCurrentAnimationSequence(m_Animation->GetCurrentAnimName())->GetTexture()->GetWidth(Count));
	//	Height = (float)(m_Animation->GetCurrentAnimationSequence(m_Animation->GetCurrentAnimName())->GetTexture()->GetHeight(Count));

	//	m_Sprite->SetWorldScale(Width, Height);
	//}

	//if (m_Weapon)
	//{
	//	//m_Animation->SetCurrentAnimation("PlayerWeaponStand");

	//	if (m_Animation->GetCurrentFrame("PlayerWeaponAttack") == 4)
	//	{
	//		m_AttackTime += DeltaTime;

	//		if (m_AttackTime > 0.2f)
	//		{
	//			m_Attack = false;

	//			m_AttackTime = 0.f;
	//		}
	//	}
	//}

	//if (m_Animation->GetCurrentFrame("PlayerNormalAttack") == 1)
	//{
	//	m_AttackTime += DeltaTime;

	//	if (m_AttackTime > 0.2f)
	//	{
	//		m_Attack = false;

	//		m_AttackTime = 0.f;
	//	}
	//}




	//if (m_SkillOn)
	//{
	//	m_SkillTime += DeltaTime;
	//	
	//	if (m_SkillTime > 0.1f)
	//	{
	//		if (m_SkillAnimation->GetCurrentAnimName() == "Ring_Left")
	//		{
	//			CBullet* Bullet = m_Scene->CreateObject<CBullet>("Bullet");

	//			Bullet->SetWorldPosition(GetWorldPos());
	//			Bullet->SetWorldRotation(GetWorldRot());
	//			Bullet->SetDir(-700.f);
	//			Bullet->SetCollisionProfileName("PlayerAttack");

	//			m_SkillTime = 0.f;

	//			//m_SkillAnimation->ChangeAnimation("Ring_Right");
	//		}

	//		if (m_SkillAnimation->GetCurrentAnimName() == "Ring_Right")
	//		{
	//			CBullet* Bullet = m_Scene->CreateObject<CBullet>("Bullet");

	//			Bullet->SetWorldPosition(GetWorldPos());
	//			Bullet->SetWorldRotation(GetWorldRot());
	//			Bullet->SetDir(700.f);
	//			Bullet->SetCollisionProfileName("PlayerAttack");

	//			m_SkillTime = 0.f;

	//			//m_SkillAnimation->ChangeAnimation("Ring_Right");
	//		}

	//	}
	//}

}

void CTestPlayer2D::PostUpdate(float DeltaTime)
{


	CGameObject::PostUpdate(DeltaTime);



}

CTestPlayer2D* CTestPlayer2D::Clone() const
{
	return new CTestPlayer2D(*this);
}

void CTestPlayer2D::MoveUp()
{
	m_Body->AddWorldPosition(m_Body->GetWorldAxis(AXIS_Y) * 300.f * g_DeltaTime);
	//m_MoveOn = true;
}

void CTestPlayer2D::MoveDown()
{
	m_Body->AddWorldPosition(m_Body->GetWorldAxis(AXIS_Y) * -300.f * g_DeltaTime);

}

void CTestPlayer2D::MoveRight()
{


	if (m_Weapon)
	{
		m_Animation->ChangeAnimation("PlayerWeaponWalk");

		m_Sprite->SetReverseX(true);

		m_Body->AddWorldPosition(m_Body->GetWorldAxis(AXIS_X) * 300.f * g_DeltaTime);

		m_MoveOn = true;

	}

	else
	{
		m_Animation->ChangeAnimation("PlayerNormalWalk");

		m_Sprite->SetReverseX(true);

		m_Body->AddWorldPosition(m_Body->GetWorldAxis(AXIS_X) * 300.f * g_DeltaTime);

		m_MoveOn = true;
	}



}

void CTestPlayer2D::MoveLeft()
{



	if (m_Weapon)
	{
		m_Animation->ChangeAnimation("PlayerWeaponWalk");

		m_Sprite->SetReverseX(false);

		m_Body->AddWorldPosition(m_Body->GetWorldAxis(AXIS_X) * -300.f * g_DeltaTime);

		m_MoveOn = true;
	}

	else
	{
		m_Animation->ChangeAnimation("PlayerNormalWalk");

		m_Sprite->SetReverseX(false);

		m_Body->AddWorldPosition(m_Body->GetWorldAxis(AXIS_X) * -300.f * g_DeltaTime);

		m_MoveOn = true;
	}


}

void CTestPlayer2D::Fire()
{

	//m_SkillOn = true;

	if (m_Weapon)
	{
		m_Animation->ChangeAnimation("PlayerWeaponAttack");

		m_SkillAnimation = m_SpriteChild->SetAnimation<CAnimation2D>("Ring_Left");
		m_SkillAnimation->AddAnimation("Ring_Left", "Ring_Left");
		m_SkillAnimation->SetLoop("Ring_Left", true);
		//m_SpriteChild->SetEnable(true);
		m_SpriteChild->SetReverseX(m_Sprite->GetReverseX());
		m_SpriteChild->SetRelativeScale(400.f, 350.f);
		m_SpriteChild->GetMaterial(0)->SetOpacity(1.f);
	}

	else
		m_Animation->ChangeAnimation("PlayerNormalAttack");

	m_Attack = true;


	//if (m_SkillAnimation->GetCurrentAnimName() == "Ring_Left")
	//{
	//	CBullet* Bullet = m_Scene->CreateObject<CBullet>("Bullet");

	//	Bullet->SetWorldPosition(GetWorldPos());
	//	Bullet->SetWorldRotation(GetWorldRot());
	//	Bullet->SetDir(-700.f);
	//	Bullet->SetCollisionProfileName("PlayerAttack");

	//	//m_SkillAnimation->ChangeAnimation("Ring_Right");
	//}

	//if (m_SkillAnimation->GetCurrentAnimName() == "Ring_Right")
	//{
	//	CBullet* Bullet = m_Scene->CreateObject<CBullet>("Bullet");

	//	Bullet->SetWorldPosition(GetWorldPos());
	//	Bullet->SetWorldRotation(GetWorldRot());
	//	Bullet->SetDir(700.f);
	//	Bullet->SetCollisionProfileName("PlayerAttack");

	//	//m_SkillAnimation->ChangeAnimation("Ring_Right");
	//}
}

void CTestPlayer2D::FireEffect()
{
	/*if (m_Animation->GetCurrentAnimName() == "IdleRight" || m_Animation->GetCurrentAnimName() == "Right")
	{
		m_SpriteChild->SetChangeWidthHeight(false);

		if (m_SpriteChild->GetEnable())
		{
			m_SpriteChild->SetRelativeScale(400.f, 350.f);
			m_SpriteChild->SetRelativePosition(10.f, 40.f);
			m_SpriteChild->SetInheritRotZ(true);
			m_SpriteChild->SetPivot(0.5f, 0.5f);
			m_SpriteChild->GetMaterial(0)->SetOpacity(1.f);

			m_SkillAnimation = m_SpriteChild->SetAnimation<CAnimation2D>("Ring_Right");
			m_SkillAnimation->AddAnimation("Ring_Right", "Ring_Right");
			m_SkillAnimation->SetLoop("Ring_Right", true);
			m_SkillAnimation->SetPlayTime("Ring_Right", 0.5f);

			m_Animation->ChangeAnimation("Ring_AttackRight");
			m_Animation->SetLoop("Ring_AttackRight", true);

		}

		if (!m_SpriteChild->GetEnable())
		{

			m_SpriteChild->SetEnable(true);
			m_SpriteChild->SetWorldScale(400.f, 350.f);
			m_SpriteChild->SetRelativePosition(10.f, 40.f);
			m_SpriteChild->SetInheritRotZ(true);
			m_SpriteChild->SetPivot(0.5f, 0.5f);
			m_SpriteChild->GetMaterial(0)->SetOpacity(1.f);

			m_SkillAnimation = m_SpriteChild->SetAnimation<CAnimation2D>("Ring_Right");
			m_SkillAnimation->AddAnimation("Ring_Right", "Ring_Right");
			m_SkillAnimation->SetLoop("Ring_Right", true);
			m_SkillAnimation->SetPlayTime("Ring_Right", 0.5f);

			m_Animation->ChangeAnimation("Ring_AttackRight");
			m_Animation->SetLoop("Ring_AttackRight", true);
		}
	}

	if (m_Animation->GetCurrentAnimName() == "IdleLeft" || m_Animation->GetCurrentAnimName() == "Left")
	{
		m_SpriteChild->SetChangeWidthHeight(false);
		if (m_SpriteChild->GetEnable())
		{

			m_SpriteChild->SetWorldScale(400.f, 350.f);
			m_SpriteChild->SetRelativePosition(-20.f, 40.f);
			m_SpriteChild->SetInheritRotZ(true);
			m_SpriteChild->SetPivot(0.5f, 0.5f);
			m_SpriteChild->GetMaterial(0)->SetOpacity(1.f);

			m_SkillAnimation = m_SpriteChild->SetAnimation<CAnimation2D>("Ring_Left");
			m_SkillAnimation->AddAnimation("Ring_Left", "Ring_Left");
			m_SkillAnimation->SetLoop("Ring_Left", true);
			m_SkillAnimation->SetPlayTime("Ring_Left", 0.5f);

			m_Animation->ChangeAnimation("Ring_AttackLeft");
			m_Animation->SetLoop("Ring_AttackLeft", true);

		}

		if (!m_SpriteChild->GetEnable())
		{

			m_SpriteChild->SetEnable(true);
			m_SpriteChild->SetWorldScale(400.f, 350.f);
			m_SpriteChild->SetRelativePosition(-20.f, 40.f);
			m_SpriteChild->SetInheritRotZ(true);
			m_SpriteChild->SetPivot(0.5f, 0.5f);
			m_SpriteChild->GetMaterial(0)->SetOpacity(1.f);

			m_SkillAnimation = m_SpriteChild->SetAnimation<CAnimation2D>("Ring_Left");
			m_SkillAnimation->AddAnimation("Ring_Left", "Ring_Left");
			m_SkillAnimation->SetLoop("Ring_Left", true);
			m_SkillAnimation->SetPlayTime("Ring_Left", 0.5f);

			m_Animation->ChangeAnimation("Ring_AttackLeft");
			m_Animation->SetLoop("Ring_AttackLeft", true);
		}
	}*/
}

void CTestPlayer2D::RightUp()
{
	m_MoveOn = false;
}

void CTestPlayer2D::LeftUp()
{
	m_MoveOn = false;
}

void CTestPlayer2D::FireUp()
{
	//m_Ring = false;

	//m_SkillSprite->SetEnable(false);

	//m_SpriteChild->SetEnable(false);

	//m_SkillOn = false;

	m_Attack = false;

}








