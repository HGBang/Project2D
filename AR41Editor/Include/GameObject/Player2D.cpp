
#include "Player2D.h"
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
#include "Scene/SceneManager.h"
#include "Resource/Material/Material.h"
#include "Animation/Animation2D.h"
#include "Bullet.h"
#include "Resource/Sound/Sound.h"
#include "Scene/SceneManager.h"
#include "Scene/Scene.h"
#include "Resource/Sound/SoundManager.h"
#include "Component/MovementComponent.h"
#include "Component/NavigationAgent.h"
#include "../GamePlayerSaveLoad.h"
#include "../GamePlayerPosSaveLoad.h"
#include "HonTailHitEffect.h"
#include "SkillEffect.h"
#include <time.h>
#include "HonTailWall.h"

#include "../Setting/DefaultSetting.h"
#include "Engine.h"
#include "../Setting/EngineShareSetting.h"
#include "../UI/StartSceneUI.h"
#include "../UI/EquipmentUI.h"
#include "../UI/InventoryUI.h"
#include "../UI/StatusUI.h"
#include "../UI/QuestUI.h"
#include "TimerManager.h"

CPlayer2D::CPlayer2D() :
	m_Level(1),
	m_MaxHP(2000),
	m_HP(1800),
	m_MaxMP(1000),
	m_MP(800),
	m_MaxExp(2000),
	m_Exp(550),
	m_Damage(10),
	m_Str(5),
	m_Dex(10),
	m_Int(5),
	m_Luk(5),
	m_Ap(0),
	m_WeaponDamage(0),
	m_HpPotionNumber(0),
	m_MpPotionNumber(0)
{
	SetTypeID<CPlayer2D>();
	m_ObjectTypeName = "Player2D";
}

CPlayer2D::CPlayer2D(const CPlayer2D& Obj) :
	CGameObject(Obj)
{
	m_Sprite = (CSpriteComponent*)FindComponent("sprite");
	m_RightChild = (CSceneComponent*)FindComponent("RightChild");
	m_SpriteChild = (CSpriteComponent*)FindComponent("spriteChild");
	m_Camera = (CCameraComponent*)FindComponent("Camera");
	m_Arm = (CTargetArm*)FindComponent("Arm");
	m_Body = (CColliderBox2D*)FindComponent("Body");
	m_MoveComponent = (CMovementComponent*)FindComponent("Movement");
	m_LevelUpSprite = (CSpriteComponent*)FindComponent("SkillSprite");
	m_DeBuffSprite = (CSpriteComponent*)FindComponent("DeBuffSprite");
	m_HP = Obj.m_HP;
	m_MaxHP = Obj.m_MaxHP;
	m_MP = Obj.m_MP;
	m_MaxMP = Obj.m_MaxMP;
	m_Exp = Obj.m_Exp;
	m_MaxExp = Obj.m_MaxExp;
	m_Level = Obj.m_Level;
	m_Damage = Obj.m_Damage;
	m_WeaponDamage = Obj.m_WeaponDamage;
	m_Str = Obj.m_Str;
	m_Dex = Obj.m_Dex;
	m_Luk = Obj.m_Luk;
	m_Int = Obj.m_Int;
	m_Ap = Obj.m_Ap;
}

CPlayer2D::~CPlayer2D()
{
	
}

void CPlayer2D::SetDeBuff(bool Debuff)
{
	m_DeBuffSprite->SetEnable(Debuff);
}

void CPlayer2D::Start()
{
	CGameObject::Start();

	CSceneManager::GetInst()->GetScene()->GetResource()->LoadSound("Effect", "Ring_Ing", false, "Ring_Ing.mp3");
	CSceneManager::GetInst()->GetScene()->GetResource()->LoadSound("Effect", "Ring_Start", false, "Ring_Start.mp3");
	CSceneManager::GetInst()->GetScene()->GetResource()->LoadSound("Effect", "Ring_Hit", false, "Ring_Hit.mp3");
	CSceneManager::GetInst()->GetScene()->GetResource()->LoadSound("Effect", "LevelUp", false, "LevelUp.mp3");
	CSceneManager::GetInst()->GetScene()->GetResource()->LoadSound("Effect", "NormalAttack_Use", false, "NormalAttack_Use.mp3");
	CSceneManager::GetInst()->GetScene()->GetResource()->LoadSound("Effect", "NormalAttack_Hit", false, "NormalAttack_Hit.mp3");
	CSceneManager::GetInst()->GetScene()->GetResource()->LoadSound("Effect", "SpeedDuelShot_Use", false, "SpeedDuelShot_Use.mp3");
	CSceneManager::GetInst()->GetScene()->GetResource()->LoadSound("Effect", "SpeedDuelShot_Hit", false, "SpeedDuelShot_Hit.mp3");
	CSceneManager::GetInst()->GetScene()->GetResource()->LoadSound("Effect", "MapleJump", false, "MapleJump.mp3");
	CSceneManager::GetInst()->GetScene()->GetResource()->LoadSound("Effect", "PotionUse", false, "PotionUse.mp3");

	if (m_Scene)
	{
		m_Scene->GetCameraManager()->SetCurrentCamera(m_Camera);
		m_MainUI = m_Scene->GetViewport()->CreateUIWindow<CStartSceneUI>("StartSceneUI");
		//m_MainUI->Start();

		m_ItemUI = m_Scene->GetViewport()->CreateUIWindow<CInventoryUI>("InventoryUI");
		m_ItemUI->Start();
		m_ItemUI->SetPlayer(this);
		m_ItemUI->SetEnable(false);

		m_StatUI = m_Scene->GetViewport()->CreateUIWindow<CStatusUI>("StatusUI");
		//m_StatUI->Start();
		m_StatUI->SetEnable(false);

		m_EquipUI = m_Scene->GetViewport()->CreateUIWindow<CEquipmentUI>("EquipmentUI");
		//m_EquipUI->Start();
		m_EquipUI->SetEnable(false);
		m_EquipUI->SetPlayer(this);

		m_QuestUI = m_Scene->GetViewport()->CreateUIWindow<CQuestUI>("QuestUI");
		m_QuestUI->SetPlayer(this);

	}
	
	//UI 키 세팅
	CInput::GetInst()->AddBindFunction<CPlayer2D>("StatUI", Input_Type::Down,
		this, &CPlayer2D::StatUIOpen, m_Scene);

	CInput::GetInst()->AddBindFunction<CPlayer2D>("ItemUI", Input_Type::Down,
		this, &CPlayer2D::ItemUIOpen, m_Scene);

	CInput::GetInst()->AddBindFunction<CPlayer2D>("EquipUI", Input_Type::Down,
		this, &CPlayer2D::EquipUIOpen, m_Scene);


	//플레이어 키세팅
	CInput::GetInst()->AddBindFunction<CPlayer2D>("LevelUp", Input_Type::Up,
		this, &CPlayer2D::LevelUpKey, m_Scene);
	CInput::GetInst()->AddBindFunction<CPlayer2D>("MoveUp", Input_Type::Push,
		this, &CPlayer2D::MoveUp, m_Scene);
	CInput::GetInst()->AddBindFunction<CPlayer2D>("MoveDown", Input_Type::Push,
		this, &CPlayer2D::MoveDown, m_Scene);
	CInput::GetInst()->AddBindFunction<CPlayer2D>("MoveRight", Input_Type::Push,
		this, &CPlayer2D::MoveRight, m_Scene);
	CInput::GetInst()->AddBindFunction<CPlayer2D>("MoveLeft", Input_Type::Push,
		this, &CPlayer2D::MoveLeft, m_Scene);
	CInput::GetInst()->AddBindFunction<CPlayer2D>("FlashJump", Input_Type::Down,
		this, &CPlayer2D::FlashJump, m_Scene);

	CInput::GetInst()->AddBindFunction<CPlayer2D>("Jump", Input_Type::Down,
		this, &CPlayer2D::Jump, m_Scene);
	CInput::GetInst()->AddBindFunction<CPlayer2D>("MoveRight", Input_Type::Up,
		this, &CPlayer2D::RightUp, m_Scene);
	CInput::GetInst()->AddBindFunction<CPlayer2D>("MoveLeft", Input_Type::Up,
		this, &CPlayer2D::LeftUp, m_Scene);
	CInput::GetInst()->AddBindFunction<CPlayer2D>("MoveDown", Input_Type::Up,
		this, &CPlayer2D::DownUp, m_Scene);
	CInput::GetInst()->AddBindFunction<CPlayer2D>("MoveUp", Input_Type::Up,
		this, &CPlayer2D::MoveUpUp, m_Scene);


	CInput::GetInst()->AddBindFunction<CPlayer2D>("Ring", Input_Type::Push,
		this, &CPlayer2D::Ring, m_Scene);
	CInput::GetInst()->AddBindFunction<CPlayer2D>("Ring", Input_Type::Down,
		this, &CPlayer2D::RingEffect, m_Scene);
	CInput::GetInst()->AddBindFunction<CPlayer2D>("Ring", Input_Type::Up,
		this, &CPlayer2D::FireUp, m_Scene);

	CInput::GetInst()->AddBindFunction<CPlayer2D>("NormalAttack", Input_Type::Down,
		this, &CPlayer2D::NormalAttack, m_Scene);
	CInput::GetInst()->AddBindFunction<CPlayer2D>("NormalAttack", Input_Type::Up,
		this, &CPlayer2D::NormalAttackUp, m_Scene);

	CInput::GetInst()->AddBindFunction<CPlayer2D>("SpeedDuelShot", Input_Type::Down,
		this, &CPlayer2D::SpeedDuelShot, m_Scene);

	CInput::GetInst()->AddBindFunction<CPlayer2D>("RedPotion", Input_Type::Down,
		this, &CPlayer2D::RedPotionKeyFunc, m_Scene);
	CInput::GetInst()->AddBindFunction<CPlayer2D>("BluePotion", Input_Type::Down,
		this, &CPlayer2D::BluePotionKeyFunc, m_Scene);


	m_Animation = m_Sprite->SetAnimation<CAnimation2D>("PlayerNormalStand");

	m_Animation->AddAnimation("PlayerWeaponStand", "PlayerWeaponStand");
	m_Animation->AddAnimation("PlayerWeaponWalk", "PlayerWeaponWalk");
	m_Animation->AddAnimation("PlayerWeaponAttack", "PlayerWeaponAttack");
	m_Animation->AddAnimation("PlayerWeaponProne", "PlayerWeaponProne");
	m_Animation->AddAnimation("PlayerWeaponJump", "PlayerWeaponJump");
	m_Animation->AddAnimation("PlayerWeaponHit", "PlayerWeaponHit");

	m_Animation->AddAnimation("PlayerNormalStand", "PlayerNormalStand");
	m_Animation->AddAnimation("PlayerNormalWalk", "PlayerNormalWalk");
	m_Animation->AddAnimation("PlayerNormalAttack", "PlayerNormalAttack");
	m_Animation->AddAnimation("PlayerNormalProne", "PlayerNormalProne");
	m_Animation->AddAnimation("PlayerNormalJump", "PlayerNormalJump");
	m_Animation->AddAnimation("PlayerRope", "PlayerRope");

	m_Animation->AddAnimation("PlayerWeapon1Stand", "PlayerWeapon1Stand");
	m_Animation->AddAnimation("PlayerWeapon1Walk", "PlayerWeapon1Walk");
	m_Animation->AddAnimation("PlayerWeapon1Attack", "PlayerWeapon1Attack");
	m_Animation->AddAnimation("PlayerWeapon1Prone", "PlayerWeapon1Prone");
	m_Animation->AddAnimation("PlayerWeapon1Jump", "PlayerWeapon1Jump");
	m_Animation->AddAnimation("PlayerWeapon1Hit", "PlayerWeapon1Hit");
	
	// 로프 상태 애니메이션 
	m_Animation->SetLoop("PlayerRope", true);
	m_Animation->SetPlayTime("PlayerRope", 1.0f);

	// 무기없는 상태 애니메이션
	m_Animation->SetLoop("PlayerNormalStand", true);
	m_Animation->SetPlayTime("PlayerNormalStand", 4.0f);

	m_Animation->SetLoop("PlayerNormalWalk", true);
	m_Animation->SetPlayTime("PlayerNormalWalk", 0.7f);

	m_Animation->SetLoop("PlayerNormalAttack", false);
	m_Animation->SetPlayTime("PlayerNormalAttack", 0.7f);

	m_Animation->SetLoop("PlayerNormalProne", true);
	m_Animation->SetPlayTime("PlayerNormalProne", 0.7f);

	m_Animation->SetLoop("PlayerNormalJump", true);
	m_Animation->SetPlayTime("PlayerNormalJump", 0.7f);

	// 무기1착용 상태 애니메이션
	m_Animation->SetLoop("PlayerWeaponStand", true);
	m_Animation->SetPlayTime("PlayerWeaponStand", 4.0f);

	m_Animation->SetLoop("PlayerWeaponWalk", true);
	m_Animation->SetPlayTime("PlayerWeaponWalk", 0.7f);

	m_Animation->SetLoop("PlayerWeaponAttack", true);
	m_Animation->SetPlayTime("PlayerWeaponAttack", 0.7f);

	m_Animation->SetLoop("PlayerWeaponProne", true);
	m_Animation->SetPlayTime("PlayerWeaponProne", 0.7f);

	m_Animation->SetLoop("PlayerWeaponJump", true);
	m_Animation->SetPlayTime("PlayerWeaponJump", 0.7f);

	m_Animation->SetLoop("PlayerWeaponHit", true);
	m_Animation->SetPlayTime("PlayerWeaponHit", 0.7f);

	// 무기2착용 상태 애니메이션	
	m_Animation->SetLoop("PlayerWeapon1Stand", true);
	m_Animation->SetPlayTime("PlayerWeapon1Stand", 4.0f);

	m_Animation->SetLoop("PlayerWeapon1Walk", true);
	m_Animation->SetPlayTime("PlayerWeapon1Walk", 0.7f);

	m_Animation->SetLoop("PlayerWeapon1Attack", true);
	m_Animation->SetPlayTime("PlayerWeapon1Attack", 0.7f);

	m_Animation->SetLoop("PlayerWeapon1Prone", true);
	m_Animation->SetPlayTime("PlayerWeapon1Prone", 0.7f);

	m_Animation->SetLoop("PlayerWeapon1Jump", true);
	m_Animation->SetPlayTime("PlayerWeapon1Jump", 0.7f);

	m_Animation->SetLoop("PlayerWeapon1Hit", true);
	m_Animation->SetPlayTime("PlayerWeapon1Hit", 0.7f);

	m_Animation->AddAnimationState("PlayerNormalStand", "PlayerNormalWalk", [=]() {return !m_MoveOn; });
	m_Animation->AddAnimationState("PlayerNormalWalk", "PlayerNormalStand", [=]() {return m_MoveOn; });

	m_Animation->AddAnimationState("PlayerNormalStand", "PlayerNormalAttack", [=]() {return m_AttackOn; });
	m_Animation->AddAnimationState("PlayerNormalAttack", "PlayerNormalStand", [=]() {return !m_AttackOn; });

	m_Animation->AddAnimationState("PlayerNormalStand", "PlayerNormalProne", [=]() {return !m_MoveOn; });
	m_Animation->AddAnimationState("PlayerNormalProne", "PlayerNormalStand", [=]() {return m_MoveOn; });

	m_Animation->AddAnimationState("PlayerWeaponStand", "PlayerWeaponWalk", [=]() {return !m_MoveOn; });
	m_Animation->AddAnimationState("PlayerWeaponWalk", "PlayerWeaponStand", [=]() {return m_MoveOn; });

	m_Animation->AddAnimationState("PlayerWeaponStand", "PlayerWeaponAttack", [=]() {return m_AttackOn; });
	m_Animation->AddAnimationState("PlayerWeaponAttack", "PlayerWeaponStand", [=]() {return !m_AttackOn; });

	m_Animation->AddAnimationState("PlayerWeaponStand", "PlayerWeaponProne", [=]() {return !m_MoveOn; });
	m_Animation->AddAnimationState("PlayerWeaponProne", "PlayerWeaponStand", [=]() {return m_MoveOn; });

	m_Animation->AddAnimationState("PlayerWeapon1Stand", "PlayerWeapon1Walk", [=]() {return !m_MoveOn; });
	m_Animation->AddAnimationState("PlayerWeapon1Walk", "PlayerWeapon1Stand", [=]() {return m_MoveOn; });

	m_Animation->AddAnimationState("PlayerWeapon1Stand", "PlayerWeapon1Attack", [=]() {return m_AttackOn; });
	m_Animation->AddAnimationState("PlayerWeapon1Attack", "PlayerWeapon1Stand", [=]() {return !m_AttackOn; });

	m_Animation->AddAnimationState("PlayerWeapon1Stand", "PlayerWeapon1Prone", [=]() {return !m_MoveOn; });
	m_Animation->AddAnimationState("PlayerWeapon1Prone", "PlayerWeapon1Stand", [=]() {return m_MoveOn; });

	m_SkillAnimation = m_SpriteChild->SetAnimation<CAnimation2D>("SpeedDuelShot");
	m_SkillAnimation->AddAnimation("SpeedDuelShot", "SpeedDuelShot");
	m_SkillAnimation->AddAnimation("Ring_Left", "Ring_Left");
	m_SkillAnimation->AddAnimation("FlashJump", "FlashJump");

	m_SkillAnimation->SetLoop("Ring_Left", true);
	m_SkillAnimation->SetPlayTime("Ring_Left", 0.5f);	


	m_DeBuffAnimation = m_DeBuffSprite->SetAnimation<CAnimation2D>("Debuff");
	m_DeBuffAnimation->AddAnimation("HonTailHandSkill_Hit", "HonTailHandSkill_Hit");

	m_DeBuffAnimation->SetLoop("HonTailHandSkill_Hit", true);
	
	m_MoveComponent->SetGravity(true);
	m_MoveComponent->SetJumpVelocity(50.f);
	m_MoveComponent->SetGround(false);
	m_Body->SetBoxSize(Vector2(40.f, 10.f));

	//Resolution RS = CDevice::GetInst()->GetResolution();

	//float Width = (float)RS.Width / 2.f;
	//float Height = (float)RS.Height / 2.7f;

	//m_Arm->SetTargetOffset(Vector3(-Width, -Height, 0.f));	


	if (m_Scene->GetName() == "FrontScene")	
		m_Arm->SetCameraMinMax(0.f, 1360.f, 0.f, 827.f);

	if (m_Scene->GetName() == "HenesisShop")
		m_Arm->SetCameraMinMax(0.f, 1365.f, 0.f, 765.f);

	if (m_Scene->GetName() == "Henesis")
		m_Arm->SetCameraMinMax(0.f, 5830.f, 0.f, 1130.f);		

	if (m_Scene->GetName() == "HenesisClass")
		m_Arm->SetCameraMinMax(0.f, 1280.f, 0.f, 1000.f);	

	if (m_Scene->GetName() == "HonTail")
	{
		m_Arm->SetCameraMinMax(0.f, 1408.f, 0.f, 915.f);
		CHonTailWall* Wall = m_Scene->CreateObject<CHonTailWall>("HonTailWall");
	}

	if (m_Scene->GetName() == "HonTailFront")
		m_Arm->SetCameraMinMax(0.f, 1980.f, 0.f, 790.f);		

	if (m_Scene->GetName() == "Basic")
		m_Arm->SetCameraMinMax(0.f, 1582, 0.f, 1282);

	//m_Arm->SetCameraMinMax(0.f, 1582, 0.f, 1282);

	//m_Arm->SetCameraMinMax(0.f, 1360.f, 0.f, 827.f);

	//m_Arm->SetCameraMinMax(0.f, 5830.f, 0.f, 1130.f);

    //m_Arm->SetCameraMinMax(0.f, 1980.f, 0.f, 790.f);

	//m_Arm->SetCameraMinMax(0.f, 1408.f, 0.f, 915.f);

	//m_Arm->SetCameraMinMax(0.f, 1360.f, 0.f, 827.f);

	//m_Arm->SetCameraMinMax(0.f, 1280.f, 0.f, 720.f);

	//m_Arm->SetCameraMinMax(0.f, 1280.f, 0.f, 1000.f);

	//m_Arm->SetCameraMinMax(0.f, 1365.f, 0.f, 765.f);

	m_Body->SetCollisionCallback<CPlayer2D>(ECollision_Result::Collision, this, &CPlayer2D::CollisionPlayer);
	m_Body->SetCollisionCallback<CPlayer2D>(ECollision_Result::Release, this, &CPlayer2D::CollisionPlayerEnd);

	m_Animation->SetCurrentEndFunction<CPlayer2D>("PlayerWeaponAttack", this, &CPlayer2D::AttackEndFunc);
	m_Animation->SetCurrentEndFunction<CPlayer2D>("PlayerNormalAttack", this, &CPlayer2D::AttackEndFunc);
	m_Animation->SetCurrentEndFunction<CPlayer2D>("PlayerWeapon1Attack", this, &CPlayer2D::AttackEndFunc);
	
	m_Animation->SetCurrentStartFunction<CPlayer2D>("PlayerWeaponAttack", this, &CPlayer2D::AttackStartFunc);
	m_Animation->SetCurrentStartFunction<CPlayer2D>("PlayerWeapon1Attack", this, &CPlayer2D::AttackStartFunc);	

	if (m_Scene->GetName() == "Henesis")
	{
		CGamePlayerPosSaveLoad::GetInst()->Load();
		CGamePlayerSaveLoad::GetInst()->Load();
	}

	if (m_Scene->GetName() != "FrontScene")
		CGamePlayerSaveLoad::GetInst()->Load();

	if (m_Weapon)
		m_Animation->SetCurrentAnimation("PlayerNormalStand");

	if (m_Weapon1)
	{
		m_Animation->SetCurrentAnimation("PlayerWeaponStand");	
		m_Weapon2 = false;
	}

	if (m_Weapon2)
	{
		m_Animation->SetCurrentAnimation("PlayerWeapon1Stand");	
		m_Weapon1 = false;
	}

	
}

bool CPlayer2D::Init()
{
	CGameObject::Init();

	/* Create Components */
	m_Body					= CreateComponent<CColliderBox2D>("Body");
	m_Sprite				= CreateComponent<CSpriteComponent>("sprite");
	m_RightChild			= CreateComponent<CSceneComponent>("RightChild");
	m_SpriteChild			= CreateComponent<CSpriteComponent>("spriteChild");
	m_LevelUpSprite			= CreateComponent<CSpriteComponent>("SkillSprite");
	m_Camera				= CreateComponent<CCameraComponent>("Camera");
	m_Arm					= CreateComponent<CTargetArm>("Arm");
	m_MoveComponent			= CreateComponent<CMovementComponent>("Movement");
	m_DeBuffSprite			= CreateComponent<CSpriteComponent>("DeBuffSprite");

	/* Set up Hierachy*/
	/*
	*	Body
	*	 Sprite
	*	 TargetArm
	*	   Camera
	* 
	*/

	SetRootComponent(m_Body);									
	m_Body->AddChild(m_Sprite);
	m_Body->AddChild(m_DeBuffSprite);
	m_Body->AddChild(m_Arm);

	
	m_Arm->AddChild(m_Camera);
	m_SpriteChild->AddChild(m_LevelUpSprite);
	m_Sprite->AddChild(m_SpriteChild);

	/* Setup Component's Options~~*/
	m_DeBuffSprite->SetPivot(0.5f, 0.5f);
	m_DeBuffSprite->SetEnable(false);
	m_Body->SetCollisionProfile("Player");
	m_Body->SetWorldPosition(300.f, 500.f);

	m_Sprite->SetPivot(0.5f, 0.5f);
	m_Sprite->SetInheritRotZ(true);	
	m_Sprite->Set2DZOffset(-100.f);

	m_SpriteChild->SetPivot(0.5f, 0.5f);

	m_LevelUpSprite->SetPivot(0.5f, 0.5f);
	m_LevelUpSprite->GetMaterial(0)->SetOpacity(0.f);


	m_MoveOn = true;
	m_Moving = true;

	m_Weapon = true;
	m_Weapon1 = false;
	m_Weapon2 = false;
	m_Jump = false;


	return true;
}

void CPlayer2D::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
	m_TestTime += DeltaTime;

	if (m_HP <= 0)
		m_HP = 0;

	if (m_Weapon1)
		m_WeaponDamage = 10;

	if (m_Weapon2)
		m_WeaponDamage = 20;

	unsigned int Damage = CEngine::GetInst()->GetNumber() / 10;

	if (!m_DamageDebuff)
	{
		m_Skill1Damage = m_Damage + 10 + Damage;
		m_Skill2Damage = m_Damage + 20 + Damage;

		m_Damage = m_Dex + m_WeaponDamage + (m_Level * 5);
	}

	if (m_DamageDebuff)
	{
		m_DamageDebuffTime += DeltaTime;

		m_Damage = 1;
		m_Skill1Damage = 1;
		m_Skill2Damage = 1;

		if (m_DamageDebuffTime > 5.f)
		{
			m_DamageDebuff = false;
			m_DamageDebuffTime = 0.f;
		}
	}

	if (m_HitSkillLock)
	{
		m_HitSkillLockTime += DeltaTime;

		if (m_HitSkillLockTime > 0.7f)
		{
			m_HitSkillLockTime = 0.f;
			m_HitSkillLock = false;
		}
	}


	if (!m_ItemUI->GetEquipWeapon1() && !m_ItemUI->GetEquipWeapon2() && !m_Weapon)
	{
		m_Weapon = true;
		m_Weapon1 = false;
		m_Weapon2 = false;
		m_Animation->ChangeAnimation("PlayerNormalStand");
	}

	if (m_ItemUI->GetEquipWeapon1() && !m_Weapon1 && !m_Weapon2)
	{
		m_Weapon = false;
		m_Weapon1 = true;
		m_Weapon2 = false;		
		m_Animation->SetCurrentAnimation("PlayerWeaponStand");
	}

	if (m_ItemUI->GetEquipWeapon2() && !m_Weapon2 &&!m_Weapon1)
	{
		m_Weapon = false;
		m_Weapon1 = false;
		m_Weapon2 = true;
		m_Animation->SetCurrentAnimation("PlayerWeapon1Stand");
	}	

	if (!m_SkillOn)
	{
		m_SpriteChild->SetEnable(false);
	}

	
	if (m_FlashLeftJump)
	{
		m_FlashJumpTime += DeltaTime;

		if (m_FlashJumpTime < 3.f)
		{		
			AddWorldPositionX(-600.f * DeltaTime);			
		}				

	}

	if (m_FlashRightJump)
	{
		m_FlashJumpTime += DeltaTime;

		if (m_FlashJumpTime < 3.f)
		{				
			AddWorldPositionX(600.f * DeltaTime);
		}

	}


	if (m_LevelUp)
	{
		m_Scene->GetResource()->SoundPlay("LevelUp");

		m_LevelUpSprite->GetMaterial(0)->SetOpacity(1.f);
	

		m_LevelUpAnimation = m_LevelUpSprite->SetAnimation<CAnimation2D>("LevelUp");
		m_LevelUpAnimation->AddAnimation("LevelUp", "LevelUp");

		m_LevelUpAnimation->SetCurrentAnimation("LevelUp");

		m_LevelUpAnimation->SetLoop("LevelUp", false);
		m_LevelUpAnimation->SetPlayTime("LevelUp", 1.9f);
		m_LevelUpAnimation->SetCurrentEndFunction("LevelUp", this, &CPlayer2D::LevelUpEnd);

		++m_Level;

		AddAp(5);
		AddMaxHp(150);
		AddMaxMp(150);
		SetExp(0);
		AddMaxExp(200);	

		m_HP = m_MaxHP;
		m_MP = m_MaxMP;

		m_LevelUpOn = true;
		m_LevelUp = false;
		m_StatUI->SetUpdateApButton(true);
	}



	if (m_LevelUpOn)
	{
		m_MainUI->SetLevelUpFunc(true);
		m_LevelUpOn = false;
	}

	if (m_Exp >= m_MaxExp)
	{
		m_LevelUp = true;
	}

		if (m_Jump)
		{
			if (!m_MoveComponent->GetJump())
			{

				if (m_Weapon)
				{
					m_Animation->ChangeAnimation("PlayerNormalStand");
					m_Jump = false;
					m_FlashLeftJump = false;
					m_FlashRightJump = false;
					m_FlashJumpTime = 0.f;

					if (m_SkillOn)
						m_SkillOn = false;
				}

				if (m_Weapon1)
				{
					m_Animation->ChangeAnimation("PlayerWeaponStand");
					m_Jump = false;
					m_FlashLeftJump = false;
					m_FlashRightJump = false;
					m_FlashJumpTime = 0.f;

					if (m_SkillOn)
						m_SkillOn = false;
				}

				if (m_Weapon2)
				{
					m_Animation->ChangeAnimation("PlayerWeapon1Stand");
					m_Jump = false;
					m_FlashLeftJump = false;
					m_FlashRightJump = false;
					m_FlashJumpTime = 0.f;

					if (m_SkillOn)
						m_SkillOn = false;
				}
				
			}
		}

	CMaterial* Material = m_Sprite->GetMaterial(0);

	if (m_ImmuneDamage)
	{
		m_ImmuneDamageTime += DeltaTime;	

		Material->SetBaseColor(Vector4(0.0f, 0.0f, 0.0f, 0.0f));	

		m_ImmuneTime += DeltaTime;

		if (m_ImmuneTime > 0.01f)
		{

			Material->SetBaseColor(Vector4(1.0f, 1.0f, 1.0f, 0.0f));

			m_ImmuneTime = 0.f;
		}

		if (m_ImmuneDamageTime > 2.f)
		{
			m_ImmuneDamage = false;
			m_Hit = false;
			m_ImmuneDamageTime = 0.f;
			Material->SetBaseColor(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
		}

	}




	if (m_Hit)
	{
		m_ImmuneDamage = true;

		m_HitTime += DeltaTime;				

		if (m_RightHit)
		{
			m_MoveComponent->MoveUp(30.f);
			AddWorldPositionX(250.f * DeltaTime);

			if (m_HitTime > 0.3f)
			{	
				m_HitTime = 0.f;
				m_Hit = false;
				m_RightHit = false;					
			}

		}

		if (m_LeftHit)
		{
			m_MoveComponent->MoveUp(30.f);
			AddWorldPositionX(-150.f * DeltaTime);

			if (m_HitTime > 0.3f)
			{
				m_HitTime = 0.f;
				m_Hit = false;
				m_LeftHit = false;
				
			}
		}	
	}

		if (m_MoveComponent)
		{
			if (m_MoveComponent->GetDiving() && !m_RopeOn)
			{
				if (m_Weapon)
				{
					m_Animation->ChangeAnimation("PlayerNormalJump");
					m_Jump = true;
				}

				if (m_Weapon1)
				{
					m_Animation->ChangeAnimation("PlayerWeaponJump");
					m_Jump = true;
				}

				if (m_Weapon2)
				{
					m_Animation->ChangeAnimation("PlayerWeapon1Jump");
					m_Jump = true;
				}				
			}
		}	
		

	if (m_RingON && !m_Hit)
	{		
		m_SkillTime += DeltaTime;   

		m_RingTime += DeltaTime;

		if (m_RingTime > 0.5f)
		{
			AddSkillMp(-15);

			m_RingTime = 0.f;

			if (m_MP < 15)
			{
				m_SkillOn = false;
				m_RingON = false;
			}
		}
		
		if (m_SkillTime > 0.09f)
		{
			float PosX, PosY;

			PosX = m_Body->GetWorldPos().x;
			PosY = m_Body->GetWorldPos().y;

			if (m_Sprite->GetReverseX())
			{
				CBullet* Bullet = m_Scene->CreateObject<CBullet>("Bullet");
				Bullet->SetCollisionProfileName("PlayerAttack");
				Bullet->SetDir(900.f);
				Bullet->SetDamage(m_Skill2Damage);
				Bullet->SetWorldPosition(m_Body->GetWorldPos().x, m_Body->GetWorldPos().y + 30.f);
			}

			else
			{
				CBullet* Bullet = m_Scene->CreateObject<CBullet>("Bullet");
				Bullet->SetCollisionProfileName("PlayerAttack");
				Bullet->SetDir(-900.f);
				Bullet->SetDamage(m_Skill2Damage);
				Bullet->SetWorldPosition(m_Body->GetWorldPos().x, m_Body->GetWorldPos().y + 30.f);
			}

			m_SkillTime = 0.f;
		}
					
	}		

	if (m_Animation)
	{
		float ImageWidth, ImageHeight;
		int Count = m_Animation->GetCurrentFrame(m_Animation->GetCurrentAnimName());
		ImageWidth = (float)(m_Animation->GetCurrentAnimationSequence(m_Animation->GetCurrentAnimName())->GetTexture()->GetWidth(Count));
		ImageHeight = (float)(m_Animation->GetCurrentAnimationSequence(m_Animation->GetCurrentAnimName())->GetTexture()->GetHeight(Count));

		m_Sprite->SetRelativeScale(ImageWidth, ImageHeight);
		m_Sprite->SetPivot(0.5f, 0.1f);			

		if (m_Animation->GetCurrentAnimName() == "PlayerNormalProne" )
		{
			m_Sprite->SetPivot(0.5f, 0.1f);
		}

		if (m_Animation->GetCurrentAnimName() == "PlayerWeaponProne" || 
			m_Animation->GetCurrentAnimName() == "PlayerWeapon1Prone")
		{
			m_Sprite->SetPivot(0.5f, 0.4f);
		}

		
		if (m_Animation->GetCurrentAnimName() == "PlayerWeaponWalk" ||
			 m_Animation->GetCurrentAnimName() == "PlayerWeapon1Walk" ||
			m_Animation->GetCurrentAnimName() == "PlayerWeaponStand" ||
			m_Animation->GetCurrentAnimName() == "PlayerWeapon1Stand")
		{
			m_Sprite->SetPivot(0.5f, 0.3f);
		}
	}


	if (m_SkillAnimation)
	{
		float ImageWidth, ImageHeight;
		int Count = m_SkillAnimation->GetCurrentFrame(m_SkillAnimation->GetCurrentAnimName());
		ImageWidth = (float)(m_SkillAnimation->GetCurrentAnimationSequence(m_SkillAnimation->GetCurrentAnimName())->GetTexture()->GetWidth(Count));
		ImageHeight = (float)(m_SkillAnimation->GetCurrentAnimationSequence(m_SkillAnimation->GetCurrentAnimName())->GetTexture()->GetHeight(Count));

		m_SpriteChild->SetRelativeScale(ImageWidth, ImageHeight);
		m_SpriteChild->SetPivot(0.5f, 0.5f);


		if (m_SkillAnimation->GetCurrentAnimName() == "Ring_Left")
		{
			Vector2 Postion = GetWorldPos();

			if (m_Sprite->GetReverseX())
			{
				m_SpriteChild->SetReverseX(m_Sprite->GetReverseX());
				m_SpriteChild->SetWorldPosition(Postion.x + 20.f, Postion.y + 70.f);
			}

			else
			{
				m_SpriteChild->SetReverseX(m_Sprite->GetReverseX());
				m_SpriteChild->SetWorldPosition(Postion.x - 20.f, Postion.y + 70.f);
			}
		}

		if (m_SkillAnimation->GetCurrentAnimName() == "SpeedDuelShot")
		{

			if (m_Sprite->GetReverseX())
			{
				m_SpriteChild->SetReverseX(m_Sprite->GetReverseX());
				m_SpriteChild->SetRelativePositionY(35.f);
				m_SpriteChild->SetRelativePositionX(35.f);
			}

			else
			{
				m_SpriteChild->SetReverseX(m_Sprite->GetReverseX());
				m_SpriteChild->SetRelativePositionY(35.f);
				m_SpriteChild->SetRelativePositionX(-35.f);
			}
		}

		if (m_SkillAnimation->GetCurrentAnimName() == "FlashJump")
		{

			if (m_Sprite->GetReverseX())
			{
				m_SpriteChild->SetReverseX(m_Sprite->GetReverseX());
				m_SpriteChild->SetWorldPositionX(GetWorldPos().x -45.f);
				m_SpriteChild->SetWorldPositionY(GetWorldPos().y + 40.f);
	
			}

			else
			{
				m_SpriteChild->SetReverseX(m_Sprite->GetReverseX());
				m_SpriteChild->SetWorldPositionX(GetWorldPos().x +50.f);	
				m_SpriteChild->SetWorldPositionY(GetWorldPos().y + 40.f);
			}
		}

	}

	if (m_LevelUpAnimation)
	{
		float ImageWidth, ImageHeight;
		int Count = m_LevelUpAnimation->GetCurrentFrame(m_LevelUpAnimation->GetCurrentAnimName());
		ImageWidth = (float)(m_LevelUpAnimation->GetCurrentAnimationSequence(m_LevelUpAnimation->GetCurrentAnimName())->GetTexture()->GetWidth(Count));
		ImageHeight = (float)(m_LevelUpAnimation->GetCurrentAnimationSequence(m_LevelUpAnimation->GetCurrentAnimName())->GetTexture()->GetHeight(Count));
		m_LevelUpSprite->SetRelativeScale(ImageWidth, ImageHeight);
		m_LevelUpSprite->SetWorldPosition(GetWorldPos().x, GetWorldPos().y + 190.f);
	}

	if (m_DeBuffAnimation)
	{
		float ImageWidth, ImageHeight;
		int Count = m_DeBuffAnimation->GetCurrentFrame(m_DeBuffAnimation->GetCurrentAnimName());
		ImageWidth = (float)(m_DeBuffAnimation->GetCurrentAnimationSequence(m_DeBuffAnimation->GetCurrentAnimName())->GetTexture()->GetWidth(Count));
		ImageHeight = (float)(m_DeBuffAnimation->GetCurrentAnimationSequence(m_DeBuffAnimation->GetCurrentAnimName())->GetTexture()->GetHeight(Count));
		m_DeBuffSprite->SetRelativeScale(ImageWidth, ImageHeight);
		m_DeBuffSprite->SetRelativePosition(Vector2(0.f, 85.f));
	}


	if (m_DeBuffSprite->GetEnable())
	{
		m_DebuffSkillLock = true;
		m_DebuffTime += DeltaTime;

		m_RingON = false;
		m_SkillOn = false;

		if (m_DebuffTime > 3.f)
		{
			m_DeBuffSprite->SetEnable(false);
		
			m_DebuffTime = 0.f;
			m_DebuffSkillLock = false;
		}
	}

	
}

void CPlayer2D::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);

	if (m_FrontQuestOn)
	{
		if (m_FrontMonsterCount > 0)
		{
			m_FrontQuestComplete = true;
			m_FrontQuestOn = false;
		}
	}
}

CPlayer2D* CPlayer2D::Clone() const
{
	return new CPlayer2D(*this);
}

void CPlayer2D::MoveUp()
{	

	if (m_Rope)
	{				
		SetWorldPositionX(m_RopePosX);

		if(m_Rope)
		m_MoveComponent->MoveUp(200.f);

		m_MoveComponent->SetGravity(false);
		m_RopeOn = true;
		m_Animation->ChangeAnimation("PlayerRope");

			if (m_MoveOn)
			{
				m_MoveOn = false;
				m_AttackOn = false;		
			}
		
	}
}

void CPlayer2D::MoveDown()
{	

	if (m_MoveOn && !m_Hit)
	{
		m_MoveOn = false;
		m_AttackOn = false;

		if (m_Weapon1)
			m_Animation->ChangeAnimation("PlayerWeaponProne");

		else if (m_Weapon2)
			m_Animation->ChangeAnimation("PlayerWeapon1Prone");

		else
			m_Animation->ChangeAnimation("PlayerNormalProne");
	}


	if (m_Rope)
	{	

		SetWorldPositionX(m_RopePosX);

		if(m_Rope)
		m_MoveComponent->MoveDown(-200.f);

		m_MoveComponent->SetGravity(false);
		m_RopeOn = true;
		m_Animation->ChangeAnimation("PlayerRope");

		if (m_MoveOn)
		{
			m_MoveOn = false;
			m_AttackOn = false;
		}

	}
	
}

void CPlayer2D::MoveRight()
{	
	m_RightRopeJump = true;

		if (m_MoveOn || m_Moving && !m_RopeOn && !m_Hit)
		{
			if (!m_FlashLeftJump && !m_FlashRightJump)
			m_MoveComponent->MoveRight(300.f);

			m_MoveOn = false;
			m_AttackOn = false;

			m_Sprite->SetReverseX(true);

			if (m_Weapon1)
				m_Animation->ChangeAnimation("PlayerWeaponWalk");

			else if (m_Weapon2)
				m_Animation->ChangeAnimation("PlayerWeapon1Walk");

			else
				m_Animation->ChangeAnimation("PlayerNormalWalk");
		}	
}

void CPlayer2D::MoveLeft()
{		
	m_LeftRopeJump = true;

		if (m_MoveOn || m_Moving && !m_RopeOn && !m_Hit)
		{
			if(!m_FlashLeftJump && !m_FlashRightJump)
			m_MoveComponent->MoveRight(-300.f);

			m_MoveOn = false;
			m_AttackOn = false;

			m_Sprite->SetReverseX(false);

			if (m_Weapon1)
				m_Animation->ChangeAnimation("PlayerWeaponWalk");

			else if (m_Weapon2)
				m_Animation->ChangeAnimation("PlayerWeapon1Walk");

			else
				m_Animation->ChangeAnimation("PlayerNormalWalk");
		}	
}

void CPlayer2D::FlashJump()
{

	

	if (m_Skill1Lock && m_MP > 15)
	{

		if (m_Jump && !m_FlashLeftJump && !m_FlashRightJump)
		{
			if (m_Sprite->GetReverseX())
			{
				m_FlashRightJump = true;

				AddSkillMp(-15);

				CSkillEffect* Effect = m_Scene->CreateObject<CSkillEffect>("SkillEffect");
				Effect->SetWorldPosition(GetWorldPos().x, GetWorldPos().y + 20.f);
				Effect->SetReverseX(m_Sprite->GetReverseX());
			}

			else
			{
				m_FlashLeftJump = true;

				AddSkillMp(-15);

				CSkillEffect* Effect = m_Scene->CreateObject<CSkillEffect>("SkillEffect");
				Effect->SetWorldPosition(GetWorldPos().x, GetWorldPos().y + 20.f);
			}

			m_SkillOn = true;
			m_SpriteChild->SetEnable(true);
			m_SkillAnimation->SetCurrentAnimation("FlashJump");
		}
	}
}

void CPlayer2D::Ring()
{
	if (m_Skill2Lock)
	{
		if (m_MP >= 15)
		{

			if (!m_DebuffSkillLock && !m_HitSkillLock)
			{
				if (m_Weapon1 || m_Weapon2 && !m_Hit)
				{
				m_AttackOn = true;
				m_MoveOn = false;
				m_Moving = false;

				m_SkillOn = true;
				m_SpriteChild->SetEnable(true);

				if (m_Weapon1)
					m_Animation->ChangeAnimation("PlayerWeaponAttack");

				if (m_Weapon2)
					m_Animation->ChangeAnimation("PlayerWeapon1Attack");

				m_SkillAnimation->ChangeAnimation("Ring_Left");

				m_RingON = true;
				}
			}
		}
	}
}

void CPlayer2D::RingEffect()
{

}

void CPlayer2D::NormalAttack()
{
	if (!m_Jump && !m_Hit)
	{
		m_AttackOn = true;
		m_MoveOn = false;
		m_Moving = false;

		if (m_Weapon)
			m_Animation->ChangeAnimation("PlayerNormalAttack");

		if (m_Weapon1 && !m_AttackRage)
		{
			m_NormalAttack = true;
			m_AttackRage = true;
			m_Animation->ChangeAnimation("PlayerWeaponAttack");
			m_Scene->GetResource()->SoundPlay("NormalAttack_Use");
		}

		if (m_Weapon2 && !m_AttackRage)
		{
			m_NormalAttack = true;
			m_AttackRage = true;
			m_Animation->ChangeAnimation("PlayerWeapon1Attack");
			m_Scene->GetResource()->SoundPlay("NormalAttack_Use");
		}
	}
}

void CPlayer2D::SpeedDuelShot()
{
	
	if (!m_DebuffSkillLock)
	{
		if (m_MP >= 10 && !m_Hit)
		{
			

			if (!m_Jump)
			{
				if (m_Skill1Lock)
				{

					if (m_Weapon1 && !m_AttackRage)
					{

						m_AttackOn = true;
						m_MoveOn = false;
						m_Moving = false;

						m_SkillOn = true;
						m_SpriteChild->SetEnable(true);

						m_SpeedDuelShot = true;
						m_AttackRage = true;
						m_Animation->ChangeAnimation("PlayerWeaponAttack");
						m_SkillAnimation->SetCurrentAnimation("SpeedDuelShot");
					}

					if (m_Weapon2 && !m_AttackRage)
					{

						m_AttackOn = true;
						m_MoveOn = false;
						m_Moving = false;

						m_SkillOn = true;

						m_SpriteChild->SetEnable(true);

						m_SpeedDuelShot = true;
						m_AttackRage = true;
						m_Animation->ChangeAnimation("PlayerWeapon1Attack");
						m_SkillAnimation->SetCurrentAnimation("SpeedDuelShot");
					}
				}
			}
		}
	}
}

void CPlayer2D::RightUp()
{	
	m_RightRopeJump = false;

	if (!m_AttackOn && !m_RopeOn && !m_Hit)
	{
		m_AttackOn = true;
		m_MoveOn = true;
		m_Moving = true;
	}
}

void CPlayer2D::LeftUp()
{		
	m_LeftRopeJump = false;

	if (!m_AttackOn && !m_RopeOn && !m_Hit)
	{
		m_AttackOn = true;
		m_MoveOn = true;
		m_Moving = true;
	}
}

void CPlayer2D::DownUp()
{	
	if (!m_AttackOn && !m_RopeOn &&!m_Hit)
	{
		m_AttackOn = true;
		m_MoveOn = true;
		m_Moving = true;
	}
}

void CPlayer2D::MoveUpUp()
{
	
}

void CPlayer2D::FireUp()
{
	m_AttackOn = false;
	m_MoveOn = true;
	m_Moving = true;

	m_SkillOn = false;
	m_RingON = false;
	m_Scene->GetResource()->SoundStop("Ring_Ing");
	m_Scene->GetResource()->SoundStop("Ring_Start");
}

void CPlayer2D::NormalAttackUp()
{
	m_AttackOn = false;
	m_MoveOn = true;
	m_Moving = true;
}

void CPlayer2D::Jump()
{
	if (!m_Jump)
	{

		if (m_Weapon)
			m_Animation->ChangeAnimation("PlayerNormalJump");

		if (m_Weapon1)
			m_Animation->ChangeAnimation("PlayerWeaponJump");

		if (m_Weapon2)
			m_Animation->ChangeAnimation("PlayerWeapon1Jump");

		m_Scene->GetResource()->SoundPlay("MapleJump");

		SetWorldPositionY(GetWorldPos().y + 3.f);

		m_MoveComponent->SetJump(true);
		m_Jump = true;
	}


	if (m_RopeOn)
	{
		m_Rope = false;
		m_RopeOn = false;

		if (m_RightRopeJump)
			m_MoveComponent->MoveRight(300.f);

		if (m_LeftRopeJump)
			m_MoveComponent->MoveLeft(300.f);

		m_MoveComponent->SetFallStartY(GetWorldPos().y - 100.f);
		m_MoveComponent->SetGravity(true);		

		m_MoveComponent->SetJump(true);
		
		m_Jump = true;
		
	}

}

void CPlayer2D::LevelUpKey()
{
	m_LevelUp = true;
}

void CPlayer2D::LevelUpEnd()
{
	m_LevelUpSprite->GetMaterial(0)->SetOpacity(0.f);
	m_LevelUpOn = false;
}

void CPlayer2D::CollisionPlayer(const CollisionResult& result)
{

	if (result.Dest->GetOwner()->GetName() == "Monster")
	{
		CColliderBox2D* Box = (CColliderBox2D*)result.Dest->GetOwner()->GetRootComponent();

		if (Box->GetCollisionProfile()->Name == "Monster")
		{
			m_Hit = true;

			AddHp(-20);

			if (m_AttackRage)
				m_AttackRage = false;

		}
	}


	if (result.Dest->GetOwner()->GetName() == "DarkWybern" || result.Dest->GetOwner()->GetName() == "Skelegon")
	{	

		if (result.Dest->GetCollisionProfile()->Name == "Monster")
		{
			if (!m_ImmuneDamage)
			{
				if (result.Dest->GetWorldPos().x < GetWorldPos().x)
				{
					m_RightHit = true;
					m_Hit = true;
					m_RingON = false;
					m_SkillOn = false;
				}

				if (result.Dest->GetWorldPos().x > GetWorldPos().x)
				{
					m_LeftHit = true;
					m_Hit = true;
					m_RingON = false;
					m_SkillOn = false;
				}

				m_MainUI->SetMonsterDamageNumber(Vector2(GetWorldPos().x, GetWorldPos().y + 90.f), 117);

				HitHp(-117);

				if (m_AttackRage)
					m_AttackRage = false;

			}
		}

	}

	if (result.Dest->GetOwner()->GetName() == "HonTail")
	
	{		

		if (result.Dest->GetCollisionProfile()->Name == "JungSY")
		{
			if (!m_ImmuneDamage)
			{
				if (result.Dest->GetWorldPos().x < GetWorldPos().x)
				{
					m_RightHit = true;
					m_Hit = true;
					m_RingON = false;
					m_SkillOn = false;
				}

				if (result.Dest->GetWorldPos().x > GetWorldPos().x)
				{
					m_LeftHit = true;
					m_Hit = true;
					m_RingON = false;
					m_SkillOn = false;
				}

				m_MainUI->SetMonsterDamageNumber(Vector2(GetWorldPos().x, GetWorldPos().y + 90.f), 300);

				HitHp(-300);

				if (m_AttackRage)
					m_AttackRage = false;

			}			
		}

	}

	if (result.Dest->GetOwner()->GetName() == "HonTailHitEffect")

	{
		if (result.Dest->GetCollisionProfile()->Name == "JungSY")
		{
			HonTailHitEffect* HitEffect = (HonTailHitEffect*)result.Dest->GetOwner();

			if (!m_ImmuneDamage)
			{
				if (result.Dest->GetWorldPos().x < GetWorldPos().x)
				{
					m_RightHit = true;
					m_Hit = true;
					m_HitSkillLock = true;
					m_RingON = false;
					m_SkillOn = false;
				}

				if (result.Dest->GetWorldPos().x > GetWorldPos().x)
				{
					m_LeftHit = true;
					m_Hit = true;
					m_HitSkillLock = true;
					m_RingON = false;
					m_SkillOn = false;
				}

				else
				{
					m_LeftHit = true;
					m_Hit = true;
					m_HitSkillLock = true;
					m_RingON = false;
					m_SkillOn = false;
				}

				HonTailHitEffect* Effect = (HonTailHitEffect*)result.Dest->GetOwner();

				int Damage = Effect->GetHitDamage();
				int MpDamage = Effect->GetHitMpDamage();

				m_MainUI->SetMonsterDamageNumber(Vector2(GetWorldPos().x, GetWorldPos().y + 90.f), Damage, MpDamage);

				if (m_AttackRage)
					m_AttackRage = false;

				HitHp(-Damage);
				AddSkillMp(-MpDamage);
			}

		

			else if (HitEffect->GetCurrentAnimName() == "HonTailMainHeadSkill_Hit")
			{
				int Damage = HitEffect->GetHitDamage();
				int MpDamage = HitEffect->GetHitMpDamage();

				m_MainUI->SetMonsterDamageNumber(Vector2(GetWorldPos().x, GetWorldPos().y + 90.f), Damage, MpDamage);

				HitHp(-Damage);
				AddSkillMp(-MpDamage);
			}

		
			
		}

	}

	if (result.Dest->GetOwner()->GetName() == "Rope")
	{
		m_Rope = true;

		m_RopePosX = result.Dest->GetOwner()->GetWorldPos().x;	
	}

}

void CPlayer2D::CollisionPlayerEnd(const CollisionResult& result)
{
	if (result.Dest->GetOwner()->GetName() == "Rope")
	{
		m_Rope = false;

		if (m_RopeOn)
		{
			if (result.Dest->GetOwner()->GetWorldPos().y > GetWorldPos().y)
			{
				m_RopeOn = false;
				m_MoveComponent->SetFallStartY(GetWorldPos().y - 50.f);
				m_MoveComponent->SetGravity(true);
			
			}
			
			else
			{
					m_RopeOn = false;	
					m_MoveComponent->SetFallStartY(GetWorldPos().y - 100.f);
					m_MoveComponent->SetGravity(true);
				
			}
		}

		if (!m_AttackOn)
		{
			m_AttackOn = true;
			m_MoveOn = true;
			m_Moving = true;
		}

	}
}

void CPlayer2D::StatUIOpen()
{
	if (!m_StatUI->GetEnable())
		m_StatUI->SetEnable(true);

	else
	{
		m_StatUI->SetEnable(false);
	}
}

void CPlayer2D::ItemUIOpen()
{
	if (!m_ItemUI->GetEnable())
		m_ItemUI->SetEnable(true);

	else
	{
		m_ItemUI->SetEnable(false);
	}

}

void CPlayer2D::EquipUIOpen()
{
	if (!m_EquipUI->GetEnable())
		m_EquipUI->SetEnable(true);

	else
	{
		m_EquipUI->SetEnable(false);
	}
}

void CPlayer2D::Save(FILE* File)
{
	CGameObject::Save(File);

	fwrite(&m_HP, sizeof(int), 1, File);
	fwrite(&m_MaxHP, sizeof(int), 1, File);
	fwrite(&m_MP, sizeof(int), 1, File);
	fwrite(&m_MaxMP, sizeof(int), 1, File);
	fwrite(&m_Exp, sizeof(int), 1, File);
	fwrite(&m_MaxExp, sizeof(int), 1, File);
	fwrite(&m_Level, sizeof(int), 1, File);
	fwrite(&m_Str, sizeof(int), 1, File);
	fwrite(&m_Dex, sizeof(int), 1, File);
	fwrite(&m_Int, sizeof(int), 1, File);
	fwrite(&m_Luk, sizeof(int), 1, File);
	fwrite(&m_Ap, sizeof(int), 1, File);


	//CGamePlayerSaveLoad::GetInst()->Save();

}

void CPlayer2D::Load(FILE* File)
{
	CGameObject::Load(File);

	fread(&m_HP, sizeof(int), 1, File);
	fread(&m_MaxHP, sizeof(int), 1, File);
	fread(&m_MP, sizeof(int), 1, File);
	fread(&m_MaxMP, sizeof(int), 1, File);
	fread(&m_Exp, sizeof(int), 1, File);
	fread(&m_MaxExp, sizeof(int), 1, File);
	fread(&m_Level, sizeof(int), 1, File);
	fread(&m_Str, sizeof(int), 1, File);
	fread(&m_Dex, sizeof(int), 1, File);
	fread(&m_Int, sizeof(int), 1, File);
	fread(&m_Luk, sizeof(int), 1, File);
	fread(&m_Ap, sizeof(int), 1, File);


	if (m_Scene)
	{
		m_MainUI = m_Scene->GetViewport()->FindUIWindow<CStartSceneUI>("StartSceneUI");	

		m_ItemUI = m_Scene->GetViewport()->FindUIWindow<CInventoryUI>("InventoryUI");
		m_ItemUI->Start();
		m_ItemUI->SetEnable(false);

		m_StatUI = m_Scene->GetViewport()->FindUIWindow<CStatusUI>("StatusUI");	
		m_StatUI->SetEnable(false);

		m_EquipUI = m_Scene->GetViewport()->FindUIWindow<CEquipmentUI>("EquipmentUI");	
		m_EquipUI->SetEnable(false);

		m_QuestUI = m_Scene->GetViewport()->FindUIWindow<CQuestUI>("QuestUI");
		m_QuestUI->SetPlayer(this);
	}
}

void CPlayer2D::SetAnimation(const std::string& Name)
{
	m_Animation->SetCurrentAnimation(Name);
}

void CPlayer2D::AttackEndFunc()
{
	if (m_NormalAttack)
	{
		m_NormalAttack = false;
		m_AttackRage = false;

		CBullet* Arrow = m_Scene->CreateObject<CBullet>("Arrow");
		Arrow->SetWorldPosition(GetWorldPos().x ,GetWorldPos().y + 30.f);
		Arrow->SetAnimation("NormalAttack");
		Arrow->SetReverseX(m_Sprite->GetReverseX());
		Arrow->SetDamage(m_Damage);
		Arrow->SetCollisionProfileName("PlayerAttack");

		if (m_Sprite->GetReverseX())
			Arrow->SetDir(900.f);

		else
			Arrow->SetDir(-900.f);			

		m_MoveOn = true;
		m_Moving = true;
		m_AttackOn = false;
	}
	
	if (m_SpeedDuelShot)
	{	
		m_SpeedDuelShot = false;
		m_AttackRage = false;

		CBullet* Arrow = m_Scene->CreateObject<CBullet>("SpeedArrow");
		Arrow->SetWorldPosition(GetWorldPos().x , GetWorldPos().y + 20.f);
		Arrow->SetAnimation("SpeedDuelShotBullet");
		Arrow->SetReverseX(m_Sprite->GetReverseX());
		Arrow->SetDamage(m_Skill1Damage);
		Arrow->SetCollisionProfileName("PlayerAttack");

		CBullet* Arrow1 = m_Scene->CreateObject<CBullet>("SpeedArrow");
		Arrow1->SetWorldPosition(GetWorldPos().x, GetWorldPos().y + 40.f);
		Arrow1->SetAnimation("SpeedDuelShotBullet");
		Arrow1->SetReverseX(m_Sprite->GetReverseX());		
		Arrow1->SetDamage(m_Skill1Damage);
		Arrow1->SetCollisionProfileName("PlayerAttack");

		AddSkillMp(-10);
		
		m_SkillOn = false;
		m_Scene->GetResource()->SoundPlay("SpeedDuelShot_Use");

		if (m_Sprite->GetReverseX())
		{
			Arrow->SetDir(900.f);
			Arrow1->SetDir(880.f);
		}
		else
		{
			Arrow->SetDir(-900.f);
			Arrow1->SetDir(-880.f);
		}
	
		m_MoveOn = true;
		m_Moving = true;
		m_AttackOn = false;
	}

	m_MoveOn = true;
	m_Moving = true;
	m_AttackOn = false;
}

void CPlayer2D::AttackStartFunc()
{
	if (m_RingON)
	{		
		m_Scene->GetResource()->SoundPlay("Ring_Start");
	}
}

void CPlayer2D::RedPotionKeyFunc()
{
	if (m_HpPotionNumber > 0)
	{
		m_Scene->GetResource()->SoundPlay("PotionUse");
		AddHp(300);
	}
}

void CPlayer2D::BluePotionKeyFunc()
{
	if (m_MpPotionNumber > 0)
	{
		m_Scene->GetResource()->SoundPlay("PotionUse");
		AddMp(300);
	}
}



