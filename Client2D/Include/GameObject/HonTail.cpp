#include "HonTail.h"
#include "Component/SpriteComponent.h"
#include "Input.h"
#include "Device.h"
#include "Component/TargetArm.h"
#include "Component/ColliderBox2D.h"
#include "Component/ColliderSphere2D.h"
#include "Component/ColliderOBB2D.h"
#include "Animation/Animation2Ddata.h"
#include "Scene/CameraManager.h"
#include "Component/CameraComponent.h"
#include "Scene/Scene.h"
#include "Scene/SceneManager.h"
#include "Resource/Material/Material.h"
#include "Animation/Animation2D.h"
#include "Bullet.h"
#include "HonTailHitEffect.h"
#include "HitEffect.h"
#include "Resource/Sound/Sound.h"
#include "Scene/SceneManager.h"
#include "Scene/Scene.h"
#include "Resource/Sound/SoundManager.h"
#include "Component/MovementComponent.h"
#include "Component/NavigationAgent.h"
#include "../GamePlayerSaveLoad.h"
#include "../GamePlayerPosSaveLoad.h"
#include "Player2D.h"
#include "HonTailExObj.h"

#include "../Setting/DefaultSetting.h"
#include "Engine.h"
#include "../Setting/EngineShareSetting.h"
#include "../UI/StartSceneUI.h"
#include "../UI/EquipmentUI.h"
#include "../UI/InventoryUI.h"
#include "../UI/StatusUI.h"
#include "../UI/QuestUI.h"
#include "TimerManager.h"

CHonTail::CHonTail()
{
	SetTypeID<CHonTail>();
	m_ObjectTypeName = "HonTail";
}

CHonTail::CHonTail(const CHonTail& Obj) :
	CGameObject(Obj)
{
	m_TailHitBox = (CColliderBox2D*)FindComponent("TailBody");
	m_TailSprite = (CSpriteComponent*)FindComponent("TailSprite");

	m_WingHitBox = (CColliderBox2D*)FindComponent("WingBody");
	m_WingSprite = (CSpriteComponent*)FindComponent("WingSprite");

	m_LegHitBox = (CColliderBox2D*)FindComponent("LegBody");
	m_LegSprite = (CSpriteComponent*)FindComponent("LegSprite");

	m_RightHandHitBox = (CColliderBox2D*)FindComponent("RightHandBody");
	m_RightHandSprite = (CSpriteComponent*)FindComponent("RightHandSprite");

	m_LeftHandHitBox = (CColliderBox2D*)FindComponent("LeftHandBody");
	m_LeftHandSprite = (CSpriteComponent*)FindComponent("LeftHandSprite");

	m_RightHeadHitBox = (CColliderBox2D*)FindComponent("RightHeadBody");
	m_RightHeadSprite = (CSpriteComponent*)FindComponent("RightHeadSprite");

	m_LeftHeadHitBox = (CColliderBox2D*)FindComponent("LeftHeadBody");
	m_LeftHeadSprite = (CSpriteComponent*)FindComponent("LeftHeadSprite");

	m_MainHeadHitBox = (CColliderBox2D*)FindComponent("MainHeadBody");
	m_MainHeadSprite = (CSpriteComponent*)FindComponent("MainHeadSprite");

	m_BottomMainHeadCollider = (CColliderBox2D*)FindComponent("BottomMainHeadCollider");
	m_LeftCollider = (CColliderBox2D*)FindComponent("LeftCollider");
	m_RightCollider = (CColliderBox2D*)FindComponent("RightCollider");
	m_LeftLegCollider = (CColliderBox2D*)FindComponent("LeftLegCollider");
	m_RightLegCollider = (CColliderBox2D*)FindComponent("RightLegCollider");
	m_TailCollider = (CColliderBox2D*)FindComponent("TailCollider");
}

CHonTail::~CHonTail()
{
}

void CHonTail::Start()
{
	CGameObject::Start();

	if (m_Scene)
		m_Player = (CPlayer2D*)m_Scene->FindObject("Player2D");

	else
		m_Player = (CPlayer2D*)CSceneManager::GetInst()->GetScene()->FindObject("Player2D");

	CSceneManager::GetInst()->GetScene()->GetResource()->SetVolume("Effect", 30);
	CSceneManager::GetInst()->GetScene()->GetResource()->SetVolume("BGM", 50);
	CSceneManager::GetInst()->GetScene()->GetResource()->LoadSound("Effect", "HonTail_Die", false, "HonTail_Die.mp3");
	CSceneManager::GetInst()->GetScene()->GetResource()->LoadSound("Effect", "HonTailLeftHand_Attack", false, "HonTailLeftHand_Attack.mp3");
	CSceneManager::GetInst()->GetScene()->GetResource()->LoadSound("Effect", "HonTailLeftHand_Skill", false, "HonTailLeftHand_Skill.mp3");
	CSceneManager::GetInst()->GetScene()->GetResource()->LoadSound("Effect", "HonTailLeftHead_Attack", false, "HonTailLeftHead_Attack.mp3");
	CSceneManager::GetInst()->GetScene()->GetResource()->LoadSound("Effect", "HonTailLeftHead_Skill", false, "HonTailLeftHead_Skill.mp3");
	CSceneManager::GetInst()->GetScene()->GetResource()->LoadSound("Effect", "HonTailLeg_Attack1", false, "HonTailLeg_Attack1.mp3");
	CSceneManager::GetInst()->GetScene()->GetResource()->LoadSound("Effect", "HonTailExHit", false, "HonTailExHit.mp3");
	CSceneManager::GetInst()->GetScene()->GetResource()->LoadSound("Effect", "HonTailLeg_Attack2", false, "HonTailLeg_Attack2.mp3");
	CSceneManager::GetInst()->GetScene()->GetResource()->LoadSound("Effect", "HonTailMainHead_Attack", false, "HonTailMainHead_Attack.mp3");
	CSceneManager::GetInst()->GetScene()->GetResource()->LoadSound("Effect", "HonTailMainHead_Skill", false, "HonTailMainHead_Skill.mp3");
	CSceneManager::GetInst()->GetScene()->GetResource()->LoadSound("Effect", "HonTailRightHand_Attack", false, "HonTailRightHand_Attack.mp3");
	CSceneManager::GetInst()->GetScene()->GetResource()->LoadSound("Effect", "HonTailRightHand_Skill", false, "HonTailRightHand_Skill.mp3");
	CSceneManager::GetInst()->GetScene()->GetResource()->LoadSound("Effect", "HonTailRightHead_Attack", false, "HonTailRightHead_Attack.mp3");
	CSceneManager::GetInst()->GetScene()->GetResource()->LoadSound("Effect", "HonTailRightHead_Skill", false, "HonTailRightHead_Skill.mp3");
	CSceneManager::GetInst()->GetScene()->GetResource()->LoadSound("Effect", "HonTailTail_Attack", false, "HonTailTail_Attack.mp3");
	CSceneManager::GetInst()->GetScene()->GetResource()->LoadSound("Effect", "HonTailTail_Skill", false, "HonTailTail_Skill.mp3");
	CSceneManager::GetInst()->GetScene()->GetResource()->LoadSound("Effect", "HonTailWing_Attack", false, "HonTailWing_Attack.mp3");
	CSceneManager::GetInst()->GetScene()->GetResource()->LoadSound("Effect", "HonTailBodyDie", false, "HonTailBodyDie.mp3");
	CSceneManager::GetInst()->GetScene()->GetResource()->LoadSound("BGM", "HonTale_BGM", true, "HonTale_BGM.mp3");
	CSceneManager::GetInst()->GetScene()->GetResource()->SoundStop("HonTailFront");
	CSceneManager::GetInst()->GetScene()->GetResource()->SoundPlay("HonTale_BGM");

	m_DieAnimation = m_DieSprite->SetAnimation<CAnimation2D>("HonTailDie");
	m_DieAnimation->AddAnimation("HonTailDie", "HonTailDie");

	m_DieAnimation->SetLoop("HonTailDie", false);
	m_DieAnimation->SetPlayTime("HonTailDie", 4.5f);	

	m_TailAnimation = m_TailSprite->SetAnimation<CAnimation2D>("HonTailTail");
	m_TailAnimation->AddAnimation("HonTailTail_Stand", "HonTailTail_Stand");
	m_TailAnimation->AddAnimation("HonTailTail_Attack", "HonTailTail_Attack");
	m_TailAnimation->AddAnimation("HonTailTail_Skill", "HonTailTail_Skill");
	m_TailAnimation->AddAnimation("HonTailDie_Tail", "HonTailDie_Tail");
	m_TailAnimation->SetCurrentStartFunction("HonTailTail_Attack", this, &CHonTail::HonTailTailStartFunc);
	m_TailAnimation->SetCurrentStartFunction("HonTailDie_Tail", this, &CHonTail::HonTailTailStartFunc);
	m_TailAnimation->SetCurrentStartFunction("HonTailTail_Skill", this, &CHonTail::HonTailTailStartFunc);
	m_TailAnimation->SetCurrentEndFunction("HonTailTail_Attack", this, &CHonTail::HonTailTailEndFunc);
	m_TailAnimation->SetCurrentEndFunction("HonTailTail_Skill", this, &CHonTail::HonTailTailEndFunc);

	m_WingAnimation = m_WingSprite->SetAnimation<CAnimation2D>("HonTailWing");
	m_WingAnimation->AddAnimation("HonTailWing_Stand", "HonTailWing_Stand");
	m_WingAnimation->AddAnimation("HonTailWing_Attack", "HonTailWing_Attack");
	m_WingAnimation->AddAnimation("HonTailDie_Wing", "HonTailDie_Wing");
	m_WingAnimation->SetCurrentStartFunction("HonTailWing_Attack", this, &CHonTail::HonTailWingStartFunc);
	m_WingAnimation->SetCurrentStartFunction("HonTailDie_Wing", this, &CHonTail::HonTailWingStartFunc);
	m_WingAnimation->SetCurrentEndFunction("HonTailWing_Attack", this, &CHonTail::HonTailWingEndFunc);

	m_LegAnimation = m_LegSprite->SetAnimation<CAnimation2D>("HonTailLeg");
	m_LegAnimation->AddAnimation("HonTailLeg_Stand", "HonTailLeg_Stand");
	m_LegAnimation->AddAnimation("HonTailLeg_RightAttack", "HonTailLeg_RightAttack");
	m_LegAnimation->AddAnimation("HonTailLeg_LeftAttack", "HonTailLeg_LeftAttack");
	m_LegAnimation->AddAnimation("HonTailDie_Leg", "HonTailDie_Leg");
	m_LegAnimation->SetCurrentStartFunction("HonTailLeg_RightAttack", this, &CHonTail::HonTailLegStartFunc);
	m_LegAnimation->SetCurrentStartFunction("HonTailDie_Leg", this, &CHonTail::HonTailLegStartFunc);
	m_LegAnimation->SetCurrentStartFunction("HonTailLeg_LeftAttack", this, &CHonTail::HonTailLegStartFunc);
	m_LegAnimation->SetCurrentEndFunction("HonTailLeg_RightAttack", this, &CHonTail::HonTailLegEndFunc);
	m_LegAnimation->SetCurrentEndFunction("HonTailLeg_LeftAttack", this, &CHonTail::HonTailLegEndFunc);

	m_RightHandAnimation = m_RightHandSprite->SetAnimation<CAnimation2D>("HonTailRightHand");
	m_RightHandAnimation->AddAnimation("HonTailRightHand_Stand", "HonTailRightHand_Stand");
	m_RightHandAnimation->AddAnimation("HonTailRightHand_Attack", "HonTailRightHand_Attack");
	m_RightHandAnimation->AddAnimation("HonTailRightHand_Skill", "HonTailRightHand_Skill");
	m_RightHandAnimation->AddAnimation("HonTailDie_RightHand", "HonTailDie_RightHand");
	m_RightHandAnimation->SetCurrentStartFunction("HonTailRightHand_Attack", this, &CHonTail::HonTailRightHandStartFunc);
	m_RightHandAnimation->SetCurrentStartFunction("HonTailRightHand_Skill", this, &CHonTail::HonTailRightHandStartFunc);
	m_RightHandAnimation->SetCurrentStartFunction("HonTailDie_RightHand", this, &CHonTail::HonTailRightHandStartFunc);
	m_RightHandAnimation->SetCurrentEndFunction("HonTailRightHand_Attack", this, &CHonTail::HonTailRightHandEndFunc);
	m_RightHandAnimation->SetCurrentEndFunction("HonTailRightHand_Skill", this, &CHonTail::HonTailRightHandEndFunc);

	m_LeftHandAnimation = m_LeftHandSprite->SetAnimation<CAnimation2D>("HonTailLeftHand");
	m_LeftHandAnimation->AddAnimation("HonTailLeftHand_Stand", "HonTailLeftHand_Stand");
	m_LeftHandAnimation->AddAnimation("HonTailLeftHand_Attack", "HonTailLeftHand_Attack");
	m_LeftHandAnimation->AddAnimation("HonTailLeftHand_Skill", "HonTailLeftHand_Skill");
	m_LeftHandAnimation->AddAnimation("HonTailDie_LeftHand", "HonTailDie_LeftHand");
	m_LeftHandAnimation->SetCurrentStartFunction("HonTailLeftHand_Attack", this, &CHonTail::HonTailLeftHandStartFunc);
	m_LeftHandAnimation->SetCurrentStartFunction("HonTailLeftHand_Skill", this, &CHonTail::HonTailLeftHandStartFunc);
	m_LeftHandAnimation->SetCurrentStartFunction("HonTailDie_LeftHand", this, &CHonTail::HonTailLeftHandStartFunc);
	m_LeftHandAnimation->SetCurrentEndFunction("HonTailLeftHand_Attack", this, &CHonTail::HonTailLeftHandEndFunc);
	m_LeftHandAnimation->SetCurrentEndFunction("HonTailLeftHand_Skill", this, &CHonTail::HonTailLeftHandEndFunc);

	m_RightHeadAnimation = m_RightHeadSprite->SetAnimation<CAnimation2D>("HontailRightHead");
    m_RightHeadAnimation->AddAnimation("HonTailRightHead_Stand", "HonTailRightHead_Stand");
	m_RightHeadAnimation->AddAnimation("HonTailRightHead_Attack", "HonTailRightHead_Attack");
	m_RightHeadAnimation->AddAnimation("HonTailRightHead_Skill", "HonTailRightHead_Skill");
	m_RightHeadAnimation->AddAnimation("HonTailDie_RightHead", "HonTailDie_RightHead");
	m_RightHeadAnimation->SetCurrentStartFunction("HonTailRightHead_Attack", this, &CHonTail::HonTailRightHeadStartFunc);
	m_RightHeadAnimation->SetCurrentStartFunction("HonTailRightHead_Skill", this, &CHonTail::HonTailRightHeadStartFunc);
	m_RightHeadAnimation->SetCurrentStartFunction("HonTailDie_RightHead", this, &CHonTail::HonTailRightHeadStartFunc);
	m_RightHeadAnimation->SetCurrentEndFunction("HonTailRightHead_Attack", this, &CHonTail::HonTailRightHeadEndFunc);
	m_RightHeadAnimation->SetCurrentEndFunction("HonTailRightHead_Skill", this, &CHonTail::HonTailRightHeadEndFunc);

	m_LeftHeadAnimation = m_LeftHeadSprite->SetAnimation<CAnimation2D>("HonTailLeftHead");
	m_LeftHeadAnimation->AddAnimation("HonTailLeftHead_Stand", "HonTailLeftHead_Stand");
	m_LeftHeadAnimation->AddAnimation("HonTailLeftHead_Attack", "HonTailLeftHead_Attack");
	m_LeftHeadAnimation->AddAnimation("HonTailLeftHead_Skill", "HonTailLeftHead_Skill");
	m_LeftHeadAnimation->AddAnimation("HonTailDie_LeftHead", "HonTailDie_LeftHead");
	m_LeftHeadAnimation->SetCurrentStartFunction("HonTailLeftHead_Attack", this, &CHonTail::HonTailLeftHeadStartFunc);
	m_LeftHeadAnimation->SetCurrentStartFunction("HonTailLeftHead_Skill", this, &CHonTail::HonTailLeftHeadStartFunc);
	m_LeftHeadAnimation->SetCurrentStartFunction("HonTailDie_LeftHead", this, &CHonTail::HonTailLeftHeadStartFunc);
	m_LeftHeadAnimation->SetCurrentEndFunction("HonTailLeftHead_Attack", this, &CHonTail::HonTailLeftHeadEndFunc);
	m_LeftHeadAnimation->SetCurrentEndFunction("HonTailLeftHead_Skill", this, &CHonTail::HonTailLeftHeadEndFunc);

	m_MainHeadAnimation = m_MainHeadSprite->SetAnimation<CAnimation2D>("HontailMainHead");
	m_MainHeadAnimation->AddAnimation("HonTailMainHead_Stand", "HonTailMainHead_Stand");
	m_MainHeadAnimation->AddAnimation("HonTailMainHead_Attack", "HonTailMainHead_Attack");
	m_MainHeadAnimation->AddAnimation("HonTailMainHead_Skill", "HonTailMainHead_Skill");
	m_MainHeadAnimation->AddAnimation("HonTailMainHead_Ex", "HonTailMainHead_Ex");
	m_MainHeadAnimation->AddAnimation("HonTailDie_MainHead", "HonTailDie_MainHead");
	m_MainHeadAnimation->SetCurrentStartFunction("HonTailMainHead_Ex", this, &CHonTail::HonTailMainHeadStartFunc);
	m_MainHeadAnimation->SetCurrentStartFunction("HonTailMainHead_Attack", this, &CHonTail::HonTailMainHeadStartFunc);
	m_MainHeadAnimation->SetCurrentStartFunction("HonTailMainHead_Skill", this, &CHonTail::HonTailMainHeadStartFunc);
	m_MainHeadAnimation->SetCurrentStartFunction("HonTailDie_MainHead", this, &CHonTail::HonTailMainHeadStartFunc);
	m_MainHeadAnimation->SetCurrentEndFunction("HonTailMainHead_Ex", this, &CHonTail::HonTailMainHeadEndFunc);
	m_MainHeadAnimation->SetCurrentEndFunction("HonTailMainHead_Attack", this, &CHonTail::HonTailMainHeadEndFunc);
	m_MainHeadAnimation->SetCurrentEndFunction("HonTailMainHead_Skill", this, &CHonTail::HonTailMainHeadEndFunc);
	m_MainHeadAnimation->SetCurrentEndFunction("HonTailDie_MainHead", this, &CHonTail::HonTailAttackEndFunc);
	
	m_TailAnimation->SetLoop("HonTailTail_Stand", true);
	m_TailAnimation->SetLoop("HonTailTail_Attack", false);
	m_TailAnimation->SetLoop("HonTailTail_Skill", false);
	
	m_WingAnimation->SetLoop("HonTailWing_Stand", true);
	m_WingAnimation->SetLoop("HonTailWing_Attack", false);

	m_LegAnimation->SetLoop("HonTailLeg_Stand", true);
	m_LegAnimation->SetLoop("HonTailLeg_LeftAttack", false);
	m_LegAnimation->SetLoop("HonTailLeg_RightAttack", false);

	m_RightHandAnimation->SetLoop("HonTailRightHand_Stand", true);
	m_RightHandAnimation->SetLoop("HonTailRightHand_Attack", false);
	m_RightHandAnimation->SetLoop("HonTailRightHand_Skill", false);

	m_LeftHandAnimation->SetLoop("HonTailLeftHand_Stand", true);
	m_LeftHandAnimation->SetLoop("HonTailLeftHand_Attack", false);
	m_LeftHandAnimation->SetLoop("HonTailLeftHand_Skill", false);

	m_RightHeadAnimation->SetLoop("HonTailRightHead_Stand", true);
	m_RightHeadAnimation->SetLoop("HonTailRightHead_Attack", false);
	m_RightHeadAnimation->SetLoop("HonTailRightHead_Skill", false);

	m_LeftHeadAnimation->SetLoop("HonTailLeftHead_Stand", true);
	m_LeftHeadAnimation->SetLoop("HonTailLeftHead_Attack", false);
	m_LeftHeadAnimation->SetLoop("HonTailLeftHead_Skill", false);

	m_MainHeadAnimation->SetLoop("HonTailMainHead_Stand", true);
	m_MainHeadAnimation->SetLoop("HonTailMainHead_Attack", false);
	m_MainHeadAnimation->SetLoop("HonTailMainHead_Skill", false);
	m_MainHeadAnimation->SetLoop("HonTailMainHead_Ex", false);

	m_TailAnimation->SetPlayTime("HonTailTail_Stand", 1.2f);
	m_TailAnimation->SetPlayTime("HonTailTail_Attack", 2.9f);
	m_TailAnimation->SetPlayTime("HonTailTail_Skill", 2.9f);
	m_TailAnimation->SetPlayTime("HonTailDie_Tail", 1.2f);

	m_WingAnimation->SetPlayTime("HonTailWing_Stand", 1.2f);
	m_WingAnimation->SetPlayTime("HonTailWing_Attack", 2.2f);
	m_WingAnimation->SetPlayTime("HonTailDie_Wing", 1.2f);

	m_LegAnimation->SetPlayTime("HonTailLeg_Stand", 1.2f);
	m_LegAnimation->SetPlayTime("HonTailLeg_LeftAttack", 1.7f);
	m_LegAnimation->SetPlayTime("HonTailLeg_RightAttack", 1.9f);
	m_LegAnimation->SetPlayTime("HonTailDie_Leg", 1.2f);

	m_RightHandAnimation->SetPlayTime("HonTailRightHand_Stand", 1.5f);
	m_RightHandAnimation->SetPlayTime("HonTailRightHand_Attack", 2.2f);
	m_RightHandAnimation->SetPlayTime("HonTailRightHand_Skill", 1.5f);
	m_RightHandAnimation->SetPlayTime("HonTailDie_RightHand", 1.5f);

	m_LeftHandAnimation->SetPlayTime("HonTailLeftHand_Stand", 1.5f);
	m_LeftHandAnimation->SetPlayTime("HonTailLeftHand_Attack", 2.5f);
	m_LeftHandAnimation->SetPlayTime("HonTailLeftHand_Skill", 1.5f);
	m_LeftHandAnimation->SetPlayTime("HonTailDie_LeftHand", 1.5f);

	m_RightHeadAnimation->SetPlayTime("HonTailRightHead_Stand", 1.5f);
	m_RightHeadAnimation->SetPlayTime("HonTailRightHead_Attack", 2.5f);
	m_RightHeadAnimation->SetPlayTime("HonTailRightHead_Skill", 1.5f);
	m_RightHeadAnimation->SetPlayTime("HonTailDie_RightHead", 1.5f);

	m_LeftHeadAnimation->SetPlayTime("HonTailLeftHead_Stand", 1.5f);
	m_LeftHeadAnimation->SetPlayTime("HonTailLeftHead_Attack", 2.6f);
	m_LeftHeadAnimation->SetPlayTime("HonTailLeftHead_Skill", 1.5f);
	m_LeftHeadAnimation->SetPlayTime("HonTailDie_LeftHead", 1.5f);

	m_MainHeadAnimation->SetPlayTime("HonTailMainHead_Stand", 1.5f);
	m_MainHeadAnimation->SetPlayTime("HonTailMainHead_Attack", 3.f);
	m_MainHeadAnimation->SetPlayTime("HonTailMainHead_Skill", 1.5f);
	m_MainHeadAnimation->SetPlayTime("HonTailMainHead_Ex", 1.5f);
	m_MainHeadAnimation->SetPlayTime("HonTailDie_MainHead", 1.5f);

	m_BottomMainHeadCollider->SetCollisionCallback(ECollision_Result::Collision, this, &CHonTail::HonTailBottomCollisionFunc);
	m_LeftCollider->SetCollisionCallback(ECollision_Result::Collision, this, &CHonTail::HonTailLeftCollisionFunc);
	m_RightCollider->SetCollisionCallback(ECollision_Result::Collision, this, &CHonTail::HonTailRightCollisionFunc);
	m_LeftLegCollider->SetCollisionCallback(ECollision_Result::Collision, this, &CHonTail::HonTailLeftLegCollisionFunc);
	m_RightLegCollider->SetCollisionCallback(ECollision_Result::Collision, this, &CHonTail::HonTailRightLegCollisionFunc);

	m_BottomMainHeadCollider->SetCollisionCallback(ECollision_Result::Release, this, &CHonTail::HonTailBottomReleaseFunc);
	m_LeftCollider->SetCollisionCallback(ECollision_Result::Release, this, &CHonTail::HonTailLeftReleaseFunc);
	m_RightCollider->SetCollisionCallback(ECollision_Result::Release, this, &CHonTail::HonTailRightReleaseFunc);
	m_LeftLegCollider->SetCollisionCallback(ECollision_Result::Release, this, &CHonTail::HonTailLeftLegReleaseFunc);
	m_RightLegCollider->SetCollisionCallback(ECollision_Result::Release, this, &CHonTail::HonTailRightLegReleaseFunc);

	m_MainHeadHitBox->SetCollisionCallback(ECollision_Result::Collision, this, &CHonTail::MainHeadHitBox);
	m_LeftHeadHitBox->SetCollisionCallback(ECollision_Result::Collision, this, &CHonTail::LeftHeadHitBox);
	m_RightHeadHitBox->SetCollisionCallback(ECollision_Result::Collision, this, &CHonTail::RightHeadHitBox);
	m_LeftHandHitBox->SetCollisionCallback(ECollision_Result::Collision, this, &CHonTail::LeftHandHitBox);
	m_RightHandHitBox->SetCollisionCallback(ECollision_Result::Collision, this, &CHonTail::RightHandHitBox);
	m_TailCollider->SetCollisionCallback(ECollision_Result::Collision, this, &CHonTail::HonTailTailCollision);
	m_WingHitBox->SetCollisionCallback(ECollision_Result::Collision, this, &CHonTail::WingHitBox);
	m_LegHitBox->SetCollisionCallback(ECollision_Result::Collision, this, &CHonTail::LegHitBox);


	CTimerManager::GetInst()->SetTimer(TimerNumber, 6.5f, true, std::bind(&CHonTail::HonTailMainHeadEx, this));
	CTimerManager::GetInst()->SetTimer(TimerNumber, 4.f, true, std::bind(&CHonTail::HonTailMainHeadAttack, this));
	CTimerManager::GetInst()->SetTimer(TimerNumber, 30.f, true, std::bind(&CHonTail::HonTailMainHeadSkill, this));

	CTimerManager::GetInst()->SetTimer(TimerNumber, 13.f, true, std::bind(&CHonTail::HonTailRightHeadAttack, this));
	CTimerManager::GetInst()->SetTimer(TimerNumber, 20.f, true, std::bind(&CHonTail::HonTailRightHeadSkill, this));

	CTimerManager::GetInst()->SetTimer(TimerNumber, 13.f, true, std::bind(&CHonTail::HonTailLeftHeadAttack, this));
	CTimerManager::GetInst()->SetTimer(TimerNumber, 20.f, true, std::bind(&CHonTail::HonTailLeftHeadSkill, this));

	CTimerManager::GetInst()->SetTimer(TimerNumber, 7.f, true, std::bind(&CHonTail::HonTailRightHandAttack, this));
	CTimerManager::GetInst()->SetTimer(TimerNumber, 17.f, true, std::bind(&CHonTail::HonTailRightHandSkill, this));

	CTimerManager::GetInst()->SetTimer(TimerNumber, 7.f, true, std::bind(&CHonTail::HonTailLeftHandAttack, this));
	CTimerManager::GetInst()->SetTimer(TimerNumber, 17.f, true, std::bind(&CHonTail::HonTailLeftHandSkill, this));

	CTimerManager::GetInst()->SetTimer(TimerNumber, 8.f, true, std::bind(&CHonTail::HonTailLeftLegAttack, this));

	CTimerManager::GetInst()->SetTimer(TimerNumber, 8.f, true, std::bind(&CHonTail::HonTailRightLegAttack, this));

	CTimerManager::GetInst()->SetTimer(TimerNumber, 14.f, true, std::bind(&CHonTail::HonTailTailAttack, this));
	CTimerManager::GetInst()->SetTimer(TimerNumber, 20.f, true, std::bind(&CHonTail::HonTailTailSkill, this));

	CTimerManager::GetInst()->SetTimer(TimerNumber, 12.f, true, std::bind(&CHonTail::HonTailWingAttack, this));


	HonTail_MainHeadHp = 20000;
	HonTail_LeftHeadHp = 20000;
	HonTail_RightHeadHp = 20000;
	HonTail_LeftHandHp = 20000;
	HonTail_RightHandHp = 20000;
	HonTail_WingHp = 20000;
	HonTail_TailHp = 20000;
	HonTail_LegHp = 20000;

	HonTail_MaxHp = HonTail_MainHeadHp + HonTail_LeftHeadHp + HonTail_RightHeadHp + HonTail_LeftHandHp + HonTail_RightHandHp +
		HonTail_WingHp + HonTail_TailHp + HonTail_LegHp;

	HonTail_Hp = HonTail_MainHeadHp + HonTail_LeftHeadHp + HonTail_RightHeadHp +
		HonTail_LeftHandHp + HonTail_RightHandHp + HonTail_WingHp +
		HonTail_TailHp + HonTail_LegHp;


	m_MainHeadNotify = m_MainHeadAnimation->FindAnimation("HonTailMainHead_Attack");
	m_MainHeadNotify->AddNotify("HonTailMainHead_Attack", 19, this, &CHonTail::HonTailMainHeadNotify);
	m_MainHeadNotify = m_MainHeadAnimation->FindAnimation("HonTailMainHead_Skill");
	m_MainHeadNotify->AddNotify("HonTailMainHead_Skill", 7, this, &CHonTail::HonTailMainHeadNotify); 
	m_MainHeadNotify = m_MainHeadAnimation->FindAnimation("HonTailMainHead_Ex");
	m_MainHeadNotify->AddNotify("HonTailMainHead_Ex", 5, this, &CHonTail::HonTailMainHeadExNotify);

	m_LeftHeadNotify = m_LeftHeadAnimation->FindAnimation("HonTailLeftHead_Attack");
	m_LeftHeadNotify->AddNotify("HonTailLeftHead_Attack", 16, this, &CHonTail::HonTailLeftHeadNotify);
	m_LeftHeadNotify = m_LeftHeadAnimation->FindAnimation("HonTailLeftHead_Skill");
	m_LeftHeadNotify->AddNotify("HonTailLeftHead_Skill", 10, this, &CHonTail::HonTailLeftHeadNotify);

	m_RightHeadNotify = m_RightHeadAnimation->FindAnimation("HonTailRightHead_Attack");
	m_RightHeadNotify->AddNotify("HonTailRightHead_Attack", 16, this, &CHonTail::HonTailRightHeadNotify);
	m_RightHeadNotify = m_RightHeadAnimation->FindAnimation("HonTailRightHead_Skill");
	m_RightHeadNotify->AddNotify("HonTailRightHead_Skill", 10, this, &CHonTail::HonTailRightHeadNotify);


	m_LegNotify = m_LegAnimation->FindAnimation("HonTailLeg_LeftAttack");
	m_LegNotify->AddNotify("HonTailLeg_LeftAttack", 11, this, &CHonTail::HonTailLegNotify);

	m_LegNotify = m_LegAnimation->FindAnimation("HonTailLeg_RightAttack");
	m_LegNotify->AddNotify("HonTailLeg_RightAttack", 11, this, &CHonTail::HonTailLegNotify);

	m_WingNotify = m_WingAnimation->FindAnimation("HonTailWing_Attack");
	m_WingNotify->AddNotify("HonTailWing_Attack", 8, this, &CHonTail::HonTailWingNotify);

	m_TailNotify = m_TailAnimation->FindAnimation("HonTailTail_Attack");
	m_TailNotify->AddNotify("HonTailTail_Attack", 14, this, &CHonTail::HonTailTailNotify);

	if (m_Scene)
		m_StartSceneUI = m_Scene->GetViewport()->FindUIWindow<CStartSceneUI>("StartSceneUI");

	else
		m_StartSceneUI = CSceneManager::GetInst()->GetScene()->GetViewport()->FindUIWindow<CStartSceneUI>("StartSceneUI");


	m_StartSceneUI->SetHonTail(this);

}

bool CHonTail::Init()
{
	CGameObject::Init();

	m_TailHitBox = CreateComponent<CColliderBox2D>("TailBody");
	m_TailSprite = CreateComponent<CSpriteComponent>("TailSprite");

	m_WingHitBox = CreateComponent<CColliderBox2D>("WingBody");
	m_WingSprite = CreateComponent<CSpriteComponent>("WingSprite");

	m_LegHitBox = CreateComponent<CColliderBox2D>("LegBody");
	m_LegSprite = CreateComponent<CSpriteComponent>("LegSprite");

	m_RightHandHitBox = CreateComponent<CColliderBox2D>("RightHandBody");
	m_RightHandSprite = CreateComponent<CSpriteComponent>("RightHandSprite");

	m_LeftHandHitBox = CreateComponent<CColliderBox2D>("LeftHandBody");
	m_LeftHandSprite = CreateComponent<CSpriteComponent>("LeftHandSprite");

	m_RightHeadHitBox = CreateComponent<CColliderBox2D>("RightHeadBody");
	m_RightHeadSprite = CreateComponent<CSpriteComponent>("RightHeadSprite");

	m_LeftHeadHitBox = CreateComponent<CColliderBox2D>("LeftHeadBody");
	m_LeftHeadSprite = CreateComponent<CSpriteComponent>("LeftHeadSprite");

	m_MainHeadHitBox = CreateComponent<CColliderBox2D>("MainHeadBody");
	m_MainHeadSprite = CreateComponent<CSpriteComponent>("MainHeadSprite");

	m_BottomMainHeadCollider = CreateComponent<CColliderBox2D>("BottomMainHeadCollider");
	m_LeftCollider = CreateComponent<CColliderBox2D>("LeftCollider");
	m_RightCollider = CreateComponent<CColliderBox2D>("RightCollider");
	m_LeftLegCollider = CreateComponent<CColliderBox2D>("LeftLegCollider");
	m_RightLegCollider = CreateComponent<CColliderBox2D>("RightLegCollider");
	m_TailCollider = CreateComponent<CColliderBox2D>("TailCollider");

	m_DieSprite = CreateComponent<CSpriteComponent>("DieSprite");


	SetRootComponent(m_TailHitBox);
	//혼테일 기본 충돌체 
	m_TailHitBox->AddChild(m_TailSprite);
	m_TailHitBox->AddChild(m_WingHitBox);
	m_TailHitBox->AddChild(m_LegHitBox);
	m_TailHitBox->AddChild(m_RightHandHitBox);
	m_TailHitBox->AddChild(m_LeftHandHitBox);
	m_TailHitBox->AddChild(m_MainHeadHitBox);
	m_TailHitBox->AddChild(m_RightHeadHitBox);
	m_TailHitBox->AddChild(m_LeftHeadHitBox);
	m_TailHitBox->AddChild(m_DieSprite);

	//혼테일 공격영역 충돌체
	m_TailHitBox->AddChild(m_BottomMainHeadCollider);
	m_TailHitBox->AddChild(m_LeftCollider);
	m_TailHitBox->AddChild(m_RightCollider);
	m_TailHitBox->AddChild(m_LeftLegCollider);
	m_TailHitBox->AddChild(m_RightLegCollider);
	m_TailHitBox->AddChild(m_TailCollider);

	//혼테일 스프라이트 
	m_LegHitBox->AddChild(m_LegSprite);
	m_RightHandHitBox->AddChild(m_RightHandSprite);
	m_LeftHandHitBox->AddChild(m_LeftHandSprite);
	m_RightHeadHitBox->AddChild(m_RightHeadSprite);
	m_LeftHeadHitBox->AddChild(m_LeftHeadSprite);
	m_MainHeadHitBox->AddChild(m_MainHeadSprite);
	m_WingHitBox->AddChild(m_WingSprite);


	m_TailHitBox->SetCollisionProfile("Die");
	m_TailHitBox->SetWorldPosition(600.f, 300.f);

	m_WingSprite->Set2DZOffset(900.0f);
	m_RightHeadSprite->Set2DZOffset(500.f);
	m_LeftHeadSprite->Set2DZOffset(500.f);
	m_TailSprite->Set2DZOffset(500.f);
	m_LeftHandSprite->Set2DZOffset(200.f);
	m_RightHandSprite->Set2DZOffset(200.f);

	m_TailSprite->SetRelativePositionY(-280.f);

	m_WingHitBox->SetCollisionProfile("Die");
	m_WingHitBox->SetBoxSize(566.f, 148.f);

	m_LegHitBox->SetCollisionProfile("JungSY");
	m_LegHitBox->SetWorldPosition(600.f, 120.f);
	m_LegHitBox->SetBoxSize(520.f, 194.f);

	m_RightHandHitBox->SetCollisionProfile("JungSY");
	m_RightHandHitBox->SetWorldPosition(703.f, 283.f);
	m_RightHandHitBox->SetBoxSize(208.f, 134.f);

	m_LeftHandHitBox->SetCollisionProfile("JungSY");
	m_LeftHandHitBox->SetWorldPosition(495.f, 283.f);
	m_LeftHandHitBox->SetBoxSize(208.f, 134.f);

	m_RightHeadHitBox->SetCollisionProfile("JungSY");
	m_RightHeadHitBox->SetWorldPosition(705.f, 440.f);
	m_RightHeadHitBox->SetBoxSize(110.f, 234.f);

	m_LeftHeadHitBox->SetCollisionProfile("JungSY");
	m_LeftHeadHitBox->SetWorldPosition(495.f, 440.f);
	m_LeftHeadHitBox->SetBoxSize(110.f, 187.f);

	m_MainHeadHitBox->SetCollisionProfile("JungSY");
	m_MainHeadHitBox->SetWorldPosition(600.f, 490.f);
	m_MainHeadHitBox->SetBoxSize(103.f, 243.f);

	//충돌영역 초기화
	m_TailHitBox->AddChild(m_BottomMainHeadCollider);
	m_TailHitBox->AddChild(m_LeftCollider);
	m_TailHitBox->AddChild(m_RightCollider);
	m_TailHitBox->AddChild(m_LeftLegCollider);
	m_TailHitBox->AddChild(m_RightLegCollider);

	m_BottomMainHeadCollider->SetCollisionProfile("MonsterAttack");
	m_BottomMainHeadCollider->SetBoxSize(487.f, 190.f);
	m_BottomMainHeadCollider->SetRelativePosition(-5, -190.f);

	m_LeftCollider->SetCollisionProfile("MonsterAttack");
	m_LeftCollider->SetBoxSize(413.f, 404.f);
	m_LeftCollider->SetRelativePosition(-430.f, 100.f);

	m_RightCollider->SetCollisionProfile("MonsterAttack");
	m_RightCollider->SetBoxSize(422.f, 404.f);
	m_RightCollider->SetRelativePosition(440.f, 100.f);

	m_LeftLegCollider->SetCollisionProfile("MonsterAttack");
	m_LeftLegCollider->SetBoxSize(298.f, 187.f);
	m_LeftLegCollider->SetRelativePosition(-450.f , -200.f);

	m_RightLegCollider->SetCollisionProfile("MonsterAttack");
	m_RightLegCollider->SetBoxSize(340.f, 187.f);
	m_RightLegCollider->SetRelativePosition(460.f , -200.f);

	m_TailCollider->SetCollisionProfile("Monster");
	m_TailCollider->SetBoxSize(150.f, 200.f);
	m_TailCollider->SetRelativePosition(250.f, -250.f);

	m_DieSprite->SetRelativePosition(-295.f, -300.f);
	m_DieSprite->SetEnable(false);

	StartColor = 1.f;

	return true;
}

void CHonTail::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	TestTime += DeltaTime;

	if (!m_Start)
	{
		if (TestTime > 0.2f)
		{
			TestTime = 0.f;

			float Start = StartColor / 10.f;

			CMaterial* Material1 = m_MainHeadSprite->GetMaterial(0);
			CMaterial* Material2 = m_RightHeadSprite->GetMaterial(0);
			CMaterial* Material3 = m_LeftHeadSprite->GetMaterial(0);
			CMaterial* Material4 = m_RightHandSprite->GetMaterial(0);
			CMaterial* Material5 = m_LeftHandSprite->GetMaterial(0);
			CMaterial* Material6 = m_LegSprite->GetMaterial(0);
			CMaterial* Material7 = m_TailSprite->GetMaterial(0);
			CMaterial* Material8 = m_WingSprite->GetMaterial(0);

			Material1->SetOpacity(Start);
			Material2->SetOpacity(Start);
			Material3->SetOpacity(Start);
			Material4->SetOpacity(Start);
			Material5->SetOpacity(Start);
			Material6->SetOpacity(Start);
			Material7->SetOpacity(Start);
			Material8->SetOpacity(Start);

			++StartColor;

			if (StartColor == 11.f)
				m_Start = true;
		}
	}

	
	if (!m_HonTailStart)
	{
		m_TailHitBox->SetWorldPosition(650.f,390.f);
		m_HonTailStart = true;
	}

	HonTailWingUpdate();
	HonTailMainHeadUpdate();
	HonTailRightHeadUpdate();
	HonTailLeftHeadUpdate();
	HonTailRightHandHeadUpdate();
	HonTailLeftHandUpdate();
	HonTailLegUpdate();	
	HonTailTailUpdate();
}

void CHonTail::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);

	HonTail_Hp = HonTail_MainHeadHp + HonTail_LeftHeadHp + HonTail_RightHeadHp +
		HonTail_LeftHandHp + HonTail_RightHandHp + HonTail_WingHp +
		HonTail_TailHp + HonTail_LegHp;


	if (HonTailDie)
	{
		HonTailDieAnimation();
		HonTailDie = false;
	}

	if (m_DieAnimation)
	{

		if (m_DieAnimation)
		{
			float ImageWidth, ImageHeight;
			int Count = m_DieAnimation->GetCurrentFrame(m_DieAnimation->GetCurrentAnimName());
			ImageWidth = (float)(m_DieAnimation->GetCurrentAnimationSequence(m_DieAnimation->GetCurrentAnimName())->GetTexture()->GetWidth(Count));
			ImageHeight = (float)(m_DieAnimation->GetCurrentAnimationSequence(m_DieAnimation->GetCurrentAnimName())->GetTexture()->GetHeight(Count));

			m_DieSprite->SetWorldScale(ImageWidth, ImageHeight);				
		}
	}

}

CHonTail* CHonTail::Clone() const
{
	return new CHonTail(*this);
}

void CHonTail::HonTailMainHeadUpdate()
{
	if (m_MainHeadAnimation)
	{
		float ImageWidth, ImageHeight;
		int Count = m_MainHeadAnimation->GetCurrentFrame(m_MainHeadAnimation->GetCurrentAnimName());
		ImageWidth = (float)(m_MainHeadAnimation->GetCurrentAnimationSequence(m_MainHeadAnimation->GetCurrentAnimName())->GetTexture()->GetWidth(Count));
		ImageHeight = (float)(m_MainHeadAnimation->GetCurrentAnimationSequence(m_MainHeadAnimation->GetCurrentAnimName())->GetTexture()->GetHeight(Count));

		m_MainHeadSprite->SetWorldScale(ImageWidth, ImageHeight);

		if (m_MainHeadAnimation->GetCurrentAnimName() == "HonTailMainHead_Attack")
			m_MainHeadSprite->SetPivot(0.5f, 0.67f);

		else if (m_MainHeadAnimation->GetCurrentAnimName() == "HonTailMainHead_Ex")
			m_MainHeadSprite->SetPivot(0.47f, 0.52f);

		else
			m_MainHeadSprite->SetPivot(0.5f, 0.5f);
	}
}

void CHonTail::HonTailRightHeadUpdate()
{
	if (m_RightHeadAnimation)
	{
		float ImageWidth, ImageHeight;
		int Count = m_RightHeadAnimation->GetCurrentFrame(m_RightHeadAnimation->GetCurrentAnimName());
		ImageWidth = (float)(m_RightHeadAnimation->GetCurrentAnimationSequence(m_RightHeadAnimation->GetCurrentAnimName())->GetTexture()->GetWidth(Count));
		ImageHeight = (float)(m_RightHeadAnimation->GetCurrentAnimationSequence(m_RightHeadAnimation->GetCurrentAnimName())->GetTexture()->GetHeight(Count));

		m_RightHeadSprite->SetWorldScale(ImageWidth, ImageHeight);

		if (m_RightHeadAnimation->GetCurrentAnimName() == "HonTailRightHead_Attack")
			m_RightHeadSprite->SetPivot(0.2f, 0.8f);

		else
			m_RightHeadSprite->SetPivot(0.5f, 0.5f);
	}
}

void CHonTail::HonTailLeftHeadUpdate()
{
	if (m_LeftHeadAnimation)
	{
		float ImageWidth, ImageHeight;
		int Count = m_LeftHeadAnimation->GetCurrentFrame(m_LeftHeadAnimation->GetCurrentAnimName());
		ImageWidth = (float)(m_LeftHeadAnimation->GetCurrentAnimationSequence(m_LeftHeadAnimation->GetCurrentAnimName())->GetTexture()->GetWidth(Count));
		ImageHeight = (float)(m_LeftHeadAnimation->GetCurrentAnimationSequence(m_LeftHeadAnimation->GetCurrentAnimName())->GetTexture()->GetHeight(Count));

		m_LeftHeadSprite->SetWorldScale(ImageWidth, ImageHeight);

		if (m_LeftHeadAnimation->GetCurrentAnimName() == "HonTailLeftHead_Attack")
			m_LeftHeadSprite->SetPivot(0.7f, 0.8f);

		else
			m_LeftHeadSprite->SetPivot(0.5f, 0.5f);
	}
}

void CHonTail::HonTailRightHandHeadUpdate()
{
	if (m_RightHandAnimation)
	{
		std::string AnimName = m_RightHandAnimation->GetCurrentAnimName();

		float ImageWidth, ImageHeight;
		int Count = m_RightHandAnimation->GetCurrentFrame(m_RightHandAnimation->GetCurrentAnimName());
		ImageWidth = (float)(m_RightHandAnimation->GetCurrentAnimationSequence(m_RightHandAnimation->GetCurrentAnimName())->GetTexture()->GetWidth(Count));
		ImageHeight = (float)(m_RightHandAnimation->GetCurrentAnimationSequence(m_RightHandAnimation->GetCurrentAnimName())->GetTexture()->GetHeight(Count));

		m_RightHandSprite->SetWorldScale(ImageWidth, ImageHeight);
		

		if(AnimName == "HonTailRightHand_Attack")
			m_RightHandSprite->SetPivot(0.28f, 0.55f);

		else if(AnimName == "HonTailRightHand_Skill")
			m_RightHandSprite->SetPivot(0.28f, 0.62f);

		else
			m_RightHandSprite->SetPivot(0.5f, 0.5f);		
	}
}

void CHonTail::HonTailLeftHandUpdate()
{
	if (m_LeftHandAnimation)
	{

		std::string AnimName = m_LeftHandAnimation->GetCurrentAnimName();

		float ImageWidth, ImageHeight;
		int Count = m_LeftHandAnimation->GetCurrentFrame(m_LeftHandAnimation->GetCurrentAnimName());
		ImageWidth = (float)(m_LeftHandAnimation->GetCurrentAnimationSequence(m_LeftHandAnimation->GetCurrentAnimName())->GetTexture()->GetWidth(Count));
		ImageHeight = (float)(m_LeftHandAnimation->GetCurrentAnimationSequence(m_LeftHandAnimation->GetCurrentAnimName())->GetTexture()->GetHeight(Count));

		m_LeftHandSprite->SetWorldScale(ImageWidth, ImageHeight);

		if (AnimName == "HonTailLeftHand_Attack")
			m_LeftHandSprite->SetPivot(0.72f, 0.55f);

		else if(AnimName == "HonTailLeftHand_Skill")
			m_LeftHandSprite->SetPivot(0.69f, 0.41f);

		else
			m_LeftHandSprite->SetPivot(0.5f, 0.5f);		
	}
}

void CHonTail::HonTailLegUpdate()
{
	if (m_LegAnimation)
	{
		std::string AnimName = m_LegAnimation->GetCurrentAnimName();

		float ImageWidth, ImageHeight;
		int Count = m_LegAnimation->GetCurrentFrame(m_LegAnimation->GetCurrentAnimName());
		ImageWidth = (float)(m_LegAnimation->GetCurrentAnimationSequence(m_LegAnimation->GetCurrentAnimName())->GetTexture()->GetWidth(Count));
		ImageHeight = (float)(m_LegAnimation->GetCurrentAnimationSequence(m_LegAnimation->GetCurrentAnimName())->GetTexture()->GetHeight(Count));

		m_LegSprite->SetWorldScale(ImageWidth, ImageHeight);

		if (AnimName == "HonTailLeg_LeftAttack")
			m_LegSprite->SetPivot(0.54f, 0.42f);

		else if (AnimName == "HonTailLeg_RightAttack")
			m_LegSprite->SetPivot(0.435f, 0.45f);

		else
			m_LegSprite->SetPivot(0.5f, 0.5f);
	}
}

void CHonTail::HonTailWingUpdate()
{
	if (m_WingAnimation)
	{

		std::string AnimName = m_WingAnimation->GetCurrentAnimName();

		float ImageWidth, ImageHeight;
		int Count = m_WingAnimation->GetCurrentFrame(m_WingAnimation->GetCurrentAnimName());
		ImageWidth = (float)(m_WingAnimation->GetCurrentAnimationSequence(m_WingAnimation->GetCurrentAnimName())->GetTexture()->GetWidth(Count));
		ImageHeight = (float)(m_WingAnimation->GetCurrentAnimationSequence(m_WingAnimation->GetCurrentAnimName())->GetTexture()->GetHeight(Count));

		m_WingSprite->SetWorldScale(ImageWidth, ImageHeight);

		if (AnimName == "HonTailWing_Attack")
			m_WingSprite->SetPivot(0.475f, 0.37f);

		else
		m_WingSprite->SetPivot(0.5f, 0.7f);		
		//m_WingSprite->SetRelativePositionZ(1000.f);	
	}
}

void CHonTail::HonTailTailUpdate()
{
	if (m_TailAnimation)
	{
		float ImageWidth, ImageHeight;
		int Count = m_TailAnimation->GetCurrentFrame(m_TailAnimation->GetCurrentAnimName());
		ImageWidth = (float)(m_TailAnimation->GetCurrentAnimationSequence(m_TailAnimation->GetCurrentAnimName())->GetTexture()->GetWidth(Count));
		ImageHeight = (float)(m_TailAnimation->GetCurrentAnimationSequence(m_TailAnimation->GetCurrentAnimName())->GetTexture()->GetHeight(Count));

		m_TailSprite->SetWorldScale(ImageWidth, ImageHeight);
		
	/*	m_TailSprite->SetPivot(0.5f, 0.5f);*/
	}
}

void CHonTail::HonTailAttackStartFunc()
{

}

void CHonTail::HonTailAttackEndFunc()
{

}

void CHonTail::HonTailBottomCollisionFunc(const CollisionResult& result)
{
	m_BottomSectionCollision = true;
}

void CHonTail::HonTailLeftCollisionFunc(const CollisionResult& result)
{
	m_LeftSectionCollision = true;
}

void CHonTail::HonTailRightCollisionFunc(const CollisionResult& result)
{
	m_RightSectionCollision = true;
}

void CHonTail::HonTailLeftLegCollisionFunc(const CollisionResult& result)
{
	m_LeftLegSectionCollision = true;
}

void CHonTail::HonTailRightLegCollisionFunc(const CollisionResult& result)
{
	m_RightLegSectionCollision = true;
}

void CHonTail::HonTailBottomReleaseFunc(const CollisionResult& result)
{
	m_BottomSectionCollision = false;
}

void CHonTail::HonTailLeftReleaseFunc(const CollisionResult& result)
{
	m_LeftSectionCollision = false;
}

void CHonTail::HonTailRightReleaseFunc(const CollisionResult& result)
{
	m_RightSectionCollision = false;
}

void CHonTail::HonTailLeftLegReleaseFunc(const CollisionResult& result)
{
	m_LeftLegSectionCollision = false;
}

void CHonTail::HonTailRightLegReleaseFunc(const CollisionResult& result)
{
	m_RightLegSectionCollision = false;
}



void CHonTail::HonTailMainHeadEx()
{

	if (!MainHeadDie)
	{
		if (!HonTail_MainHeadSkill && !HonTail_MainHeadAttack && !HonTail_MainHeadEx)
		{
			m_MainHeadAnimation->ChangeAnimation("HonTailMainHead_Ex");
			HonTail_MainHeadEx = true;
		}
	}

}

void CHonTail::HonTailMainHeadAttack()
{	
	if (!MainHeadDie)
	{
		if (m_BottomSectionCollision && !HonTail_MainHeadAttack && !HonTail_MainHeadSkill &&!HonTail_MainHeadEx)
		{
			m_MainHeadAnimation->ChangeAnimation("HonTailMainHead_Attack");
			HonTail_MainHeadAttack = true;

		}
	}
}

void CHonTail::HonTailMainHeadSkill()
{
	if (!MainHeadDie)
	{
		if (!HonTail_MainHeadSkill && !HonTail_MainHeadAttack && !HonTail_MainHeadSkill && !HonTail_MainHeadEx)
		{
			m_MainHeadAnimation->ChangeAnimation("HonTailMainHead_Skill");
			HonTail_MainHeadSkill = true;
		}
	}
}

void CHonTail::HonTailLeftHeadAttack()
{
	if (!LeftHeadDie)
	{
		if (m_LeftLegSectionCollision && !HonTail_LeftHeadAttack && !HonTail_LeftHeadSkill)
		{
			m_LeftHeadAnimation->ChangeAnimation("HonTailLeftHead_Attack");
			HonTail_LeftHeadAttack = true;
		}
	}
}

void CHonTail::HonTailLeftHeadSkill()
{
	if (!LeftHeadDie)
	{
		if (m_LeftSectionCollision && !HonTail_LeftHeadAttack && !HonTail_LeftHeadSkill)
		{
			m_LeftHeadAnimation->ChangeAnimation("HonTailLeftHead_Skill");
			HonTail_LeftHeadSkill = true;
		}
	}
}

void CHonTail::HonTailRightHeadAttack()
{
	if (!RightHeadDie)
	{
		if (m_RightLegSectionCollision && !HonTail_RightHeadAttack && !HonTail_RightHeadSkill)
		{
			m_RightHeadAnimation->ChangeAnimation("HonTailRightHead_Attack");
			HonTail_RightHeadAttack = true;
		}
	}
}

void CHonTail::HonTailRightHeadSkill()
{
	if (!RightHeadDie)
	{
		if (m_RightSectionCollision && !HonTail_RightHeadAttack && !HonTail_RightHeadSkill)
		{
			m_RightHeadAnimation->ChangeAnimation("HonTailRightHead_Skill");
			HonTail_RightHeadSkill = true;
		}
	}
}

void CHonTail::HonTailLeftHandAttack()
{
	if (!LeftHandDie)
	{
		if (m_LeftSectionCollision && !HonTail_HandAttack && !HonTail_HandSkill)
		{
			m_LeftHandAnimation->ChangeAnimation("HonTailLeftHand_Attack");
			HonTail_HandAttack = true;
			
			HonTailHitEffect* HitEffect = m_Scene->CreateObject<HonTailHitEffect>("HonTailHitEffect");
			HitEffect->SetWorldPosition(m_Player->GetWorldPos().x +10.f, m_Player->GetWorldPos().y + 50.f);
		}
	}
}

void CHonTail::HonTailLeftHandSkill()
{
	if (!LeftHandDie)
	{
		if (m_LeftSectionCollision && !HonTail_HandAttack && !HonTail_HandSkill)
		{
			m_LeftHandAnimation->ChangeAnimation("HonTailLeftHand_Skill");
			HonTail_HandSkill = true;

			m_Player->SetDeBuff(true);
		}
	}
}

void CHonTail::HonTailWingAttack()
{
	if (!WingDie)
	{
		if (m_LeftSectionCollision || m_RightSectionCollision && !HonTail_WingAttack)
		{
			m_WingAnimation->ChangeAnimation("HonTailWing_Attack");
			HonTail_WingAttack = true;
		}
	}
}

void CHonTail::HonTailDieAnimation()
{
	m_Scene->GetResource()->SoundPlay("HonTail_Die");

	m_DieSprite->SetEnable(true);
	m_DieAnimation->SetCurrentAnimation("HonTailDie");

	m_MainHeadSprite->SetEnable(false);
	m_LeftHeadSprite->SetEnable(false);
	m_RightHeadSprite->SetEnable(false);
	m_LeftHandSprite->SetEnable(false);
	m_RightHandSprite->SetEnable(false);
	m_LegSprite->SetEnable(false);
	m_WingSprite->SetEnable(false);
	m_TailSprite->SetEnable(false);

}

void CHonTail::HonTailRightHandAttack()
{
	if (!RightHandDie)
	{
		if (m_RightSectionCollision && !HonTail_HandAttack && !HonTail_HandSkill)
		{
			m_RightHandAnimation->ChangeAnimation("HonTailRightHand_Attack");
			HonTail_HandAttack = true;

			HonTailHitEffect* HitEffect = m_Scene->CreateObject<HonTailHitEffect>("HonTailHitEffect");
			HitEffect->SetWorldPosition(m_Player->GetWorldPos().x - 20.f, m_Player->GetWorldPos().y + 50.f);

		}
	}
}

void CHonTail::HonTailRightHandSkill()
{
	if (!RightHandDie)
	{
		if (m_RightSectionCollision && !HonTail_HandAttack && !HonTail_HandSkill)
		{
			m_RightHandAnimation->ChangeAnimation("HonTailRightHand_Skill");
			HonTail_HandSkill = true;

			m_Player->SetDeBuff(true);
		}
	}
}

void CHonTail::HonTailRightLegAttack()
{
	if (!LegDie)
	{
		if (m_RightLegSectionCollision && !HonTail_LegAttack)
		{
			m_LegAnimation->ChangeAnimation("HonTailLeg_RightAttack");
			HonTail_LegAttack = true;
		}
	}
}

void CHonTail::HonTailLeftLegAttack()
{
	if (!LegDie)
	{
		if (m_LeftLegSectionCollision && !HonTail_LegAttack)
		{
			m_LegAnimation->ChangeAnimation("HonTailLeg_LeftAttack");
			HonTail_LegAttack = true;

		}
	}
}

void CHonTail::HonTailTailAttack()
{
	if (!TailDie)
	{
		if (m_RightLegSectionCollision && !HonTail_TailAttack && !HonTail_TailSkill)
		{
			m_TailAnimation->ChangeAnimation("HonTailTail_Attack");
			HonTail_TailAttack = true;
		}
	}
}

void CHonTail::HonTailTailSkill()
{
	if (!TailDie)
	{
		if (m_RightLegSectionCollision && !HonTail_TailAttack && !HonTail_TailSkill)
		{
			m_TailAnimation->ChangeAnimation("HonTailTail_Skill");
			HonTail_TailSkill = true;
			m_Player->SetDamageDebuff(true);
		}
	}
}

void CHonTail::HonTailMainHeadStartFunc()
{
	if (m_MainHeadAnimation->GetCurrentAnimName() == "HonTailMainHead_Attack")
		m_Scene->GetResource()->SoundPlay("HonTailMainHead_Attack");

	if (m_MainHeadAnimation->GetCurrentAnimName() == "HonTailMainHead_Skill")
		m_Scene->GetResource()->SoundPlay("HonTailMainHead_Skill");

	if (m_MainHeadAnimation->GetCurrentAnimName() == "HonTailMainHead_Ex")
		m_Scene->GetResource()->SoundPlay("HonTailExHit");

	if (m_MainHeadAnimation->GetCurrentAnimName() == "HonTailDie_MainHead")
	{
		MainHeadDie = true;
		HonTailDie = true;
		m_Scene->GetResource()->SoundPlay("HonTailBodyDie");
	}
}

void CHonTail::HonTailMainHeadEndFunc()
{
	if (m_MainHeadAnimation->GetCurrentAnimName() == "HonTailMainHead_Attack" ||
		m_MainHeadAnimation->GetCurrentAnimName() == "HonTailMainHead_Skill" ||
		m_MainHeadAnimation->GetCurrentAnimName() == "HonTailMainHead_Ex")
	{
		m_MainHeadAnimation->ChangeAnimation("HonTailMainHead_Stand");

		if (HonTail_MainHeadAttack)
		{
			HonTail_MainHeadAttack = false;
		}

		else if (HonTail_MainHeadSkill)
			HonTail_MainHeadSkill = false;

		else if (HonTail_MainHeadEx)
			HonTail_MainHeadEx = false;


	}
}

void CHonTail::HonTailLeftHeadStartFunc()
{
	if (m_LeftHeadAnimation->GetCurrentAnimName() == "HonTailLeftHead_Attack")
		m_Scene->GetResource()->SoundPlay("HonTailLeftHead_Attack");

	if (m_LeftHeadAnimation->GetCurrentAnimName() == "HonTailLeftHead_Skill")
		m_Scene->GetResource()->SoundPlay("HonTailLeftHead_Skill");

	if (m_LeftHeadAnimation->GetCurrentAnimName() == "HonTailDie_LeftHead")
	{
		LeftHeadDie = true;
		m_Scene->GetResource()->SoundPlay("HonTailBodyDie");
	}
}

void CHonTail::HonTailLeftHeadEndFunc()
{
	if (m_LeftHeadAnimation->GetCurrentAnimName() == "HonTailLeftHead_Attack" ||
		m_LeftHeadAnimation->GetCurrentAnimName() == "HonTailLeftHead_Skill")
	{
		m_LeftHeadAnimation->ChangeAnimation("HonTailLeftHead_Stand");

		if (HonTail_LeftHeadAttack)
		{
			HonTail_LeftHeadAttack = false;	
		}

		if (HonTail_LeftHeadSkill)
			HonTail_LeftHeadSkill = false;

	}
}

void CHonTail::HonTailRightHeadStartFunc()
{
	if (m_RightHeadAnimation->GetCurrentAnimName() == "HonTailRightHead_Attack")
		m_Scene->GetResource()->SoundPlay("HonTailRightHead_Attack");

	if (m_RightHeadAnimation->GetCurrentAnimName() == "HonTailRightHead_Skill")
		m_Scene->GetResource()->SoundPlay("HonTailRightHead_Skill");

	if (m_RightHeadAnimation->GetCurrentAnimName() == "HonTailDie_RightHead")	
		m_Scene->GetResource()->SoundPlay("HonTailBodyDie");
	
}

void CHonTail::HonTailRightHeadEndFunc()
{
	if (m_RightHeadAnimation->GetCurrentAnimName() == "HonTailRightHead_Attack" ||
		m_RightHeadAnimation->GetCurrentAnimName() == "HonTailRightHead_Skill")
	{
		m_RightHeadAnimation->ChangeAnimation("HonTailRightHead_Stand");

		if (HonTail_RightHeadAttack)
		{
			HonTail_RightHeadAttack = false;
		}

		if (HonTail_RightHeadSkill)
			HonTail_RightHeadSkill = false;
	}

}

void CHonTail::HonTailRightHandStartFunc()
{
	if (m_RightHandAnimation->GetCurrentAnimName() == "HonTailRightHand_Attack")
		m_Scene->GetResource()->SoundPlay("HonTailRightHand_Attack");

	if (m_RightHandAnimation->GetCurrentAnimName() == "HonTailRightHand_Skill")
		m_Scene->GetResource()->SoundPlay("HonTailRightHand_Skill");

	if (m_RightHandAnimation->GetCurrentAnimName() == "HonTailDie_RightHand")
		m_Scene->GetResource()->SoundPlay("HonTailBodyDie");
	
}

void CHonTail::HonTailRightHandEndFunc()
{
	if (m_RightHandAnimation->GetCurrentAnimName() == "HonTailRightHand_Attack" ||
		m_RightHandAnimation->GetCurrentAnimName() == "HonTailRightHand_Skill")
	{
		m_RightHandAnimation->ChangeAnimation("HonTailRightHand_Stand");

		if (HonTail_HandAttack)
			HonTail_HandAttack = false;

		if (HonTail_HandSkill)
			HonTail_HandSkill = false;
	}
}

void CHonTail::HonTailLeftHandStartFunc()
{
	if (m_LeftHandAnimation->GetCurrentAnimName() == "HonTailLeftHand_Attack")
		m_Scene->GetResource()->SoundPlay("HonTailRightHand_Attack");

	if (m_LeftHandAnimation->GetCurrentAnimName() == "HonTailLeftHand_Skill")
		m_Scene->GetResource()->SoundPlay("HonTailRightHand_Skill");

	if (m_LeftHandAnimation->GetCurrentAnimName() == "HonTailDie_LeftHand")	
		m_Scene->GetResource()->SoundPlay("HonTailBodyDie");
	
}

void CHonTail::HonTailLeftHandEndFunc()
{
	if (m_LeftHandAnimation->GetCurrentAnimName() == "HonTailLeftHand_Attack" ||
		m_LeftHandAnimation->GetCurrentAnimName() == "HonTailLeftHand_Skill")
	{
		m_LeftHandAnimation->ChangeAnimation("HonTailLeftHand_Stand");

		if (HonTail_HandAttack)
			HonTail_HandAttack = false;

		if (HonTail_HandSkill)
			HonTail_HandSkill = false;
	}
}

void CHonTail::HonTailLegStartFunc()
{
	if (m_LegAnimation->GetCurrentAnimName() == "HonTailLeg_LeftAttack")
		m_Scene->GetResource()->SoundPlay("HonTailLeg_Attack1");

	if (m_LegAnimation->GetCurrentAnimName() == "HonTailLeg_RightAttack")
		m_Scene->GetResource()->SoundPlay("HonTailLeg_Attack2");

	if (m_LegAnimation->GetCurrentAnimName() == "HonTailDie_Leg")
			m_Scene->GetResource()->SoundPlay("HonTailBodyDie");	
}

void CHonTail::HonTailLegEndFunc()
{
	if (m_LegAnimation->GetCurrentAnimName() == "HonTailLeg_LeftAttack")
	{
		m_LegAnimation->ChangeAnimation("HonTailLeg_Stand");

		if (HonTail_LegAttack)
			HonTail_LegAttack = false;
	}

	if (m_LegAnimation->GetCurrentAnimName() == "HonTailLeg_RightAttack")
	{
		m_LegAnimation->ChangeAnimation("HonTailLeg_Stand");

		if (HonTail_LegAttack)
			HonTail_LegAttack = false;
	}
}

void CHonTail::HonTailTailStartFunc()
{
	if (m_TailAnimation->GetCurrentAnimName() == "HonTailTail_Attack")
		m_Scene->GetResource()->SoundPlay("HonTailTail_Attack");

	if (m_TailAnimation->GetCurrentAnimName() == "HonTailTail_Skill")
		m_Scene->GetResource()->SoundPlay("HonTailTail_Skill");

	if (m_TailAnimation->GetCurrentAnimName() == "HonTailDie_Tail")
		m_Scene->GetResource()->SoundPlay("HonTailBodyDie");

}

void CHonTail::HonTailTailEndFunc()
{
	if (m_TailAnimation->GetCurrentAnimName() == "HonTailTail_Attack" ||
		m_TailAnimation->GetCurrentAnimName() == "HonTailTail_Skill")
	{
		m_TailAnimation->ChangeAnimation("HonTailTail_Stand");

		if (HonTail_TailAttack)
		{
			HonTail_TailAttack = false;
		}

		if (HonTail_TailSkill)
			HonTail_TailSkill = false;
	}
}

void CHonTail::HonTailWingStartFunc()
{
	if (m_WingAnimation->GetCurrentAnimName() == "HonTailWing_Attack")
		m_Scene->GetResource()->SoundPlay("HonTailWing_Attack");

	if (m_WingAnimation->GetCurrentAnimName() == "HonTailDie_Wing")		
		m_Scene->GetResource()->SoundPlay("HonTailBodyDie");	
}

void CHonTail::HonTailWingEndFunc()
{
	if (m_WingAnimation->GetCurrentAnimName() == "HonTailWing_Attack")
	{
		m_WingAnimation->ChangeAnimation("HonTailWing_Stand");		

		if (HonTail_WingAttack)
			HonTail_WingAttack = false;
	}
}

void CHonTail::HonTailTailCollision(const CollisionResult& result)
{

    if (result.Dest->GetOwner()->GetName() == "Bullet")
	{

		if (HonTail_TailHp >= 0 && !TailDie)
		{
			CBullet* Bullet = (CBullet*)result.Dest->GetOwner();

			int Damage = Bullet->GetDamage();

			std::string BulletName = Bullet->GetAnimationName();

			HonTail_TailHp -= Damage;

			if (HonTail_TailHp <= 0)
			{
				m_TailCollider->SetCollisionProfile("Die");
				TailDie = true;
				m_TailAnimation->ChangeAnimation("HonTailDie_Tail");		
				
				m_LegHitBox->SetCollisionProfile("Monster");
			
			}

			Vector3 Pos = GetWorldPos();

			if (BulletName == "NormalAttack")
			{
				CHitEffect* Effect = m_Scene->CreateObject<CHitEffect>("HitEffect");
				Effect->SetAnimation("NormalAttackHit");

				if (m_TailSprite->GetWorldPos().x < result.Dest->GetWorldPos().x)
				{
					m_TailSprite->SetReverseX(false);
					Effect->SetRelativePosition(Bullet->GetWorldPos());
				}				
			}

			if (BulletName == "SpeedDuelShotBullet")
			{
				CHitEffect* Effect = m_Scene->CreateObject<CHitEffect>("HitEffect");
				Effect->SetAnimation("SpeedDualShotHit");

				if (m_TailSprite->GetWorldPos().x < result.Dest->GetWorldPos().x)
				{
					m_TailSprite->SetReverseX(false);
					Effect->SetRelativePosition(Bullet->GetWorldPos());
				}
			}

			if (BulletName == "Ring_Arrow")
			{
				CHitEffect* Effect = m_Scene->CreateObject<CHitEffect>("HitEffect");
				Effect->SetAnimation("Ring_Effect");

				if (m_TailSprite->GetWorldPos().x < result.Dest->GetWorldPos().x)
				{
					m_TailSprite->SetReverseX(false);
					Effect->SetRelativePosition(Bullet->GetWorldPos());
				}
			}
		}
	}
}


void CHonTail::WingHitBox(const CollisionResult& result)
{
	if (result.Dest->GetOwner()->GetName() == "Bullet")
	{

		if (HonTail_WingHp >= 0 && !WingDie)
		{
			CBullet* Bullet = (CBullet*)result.Dest->GetOwner();

			int Damage = Bullet->GetDamage();

			std::string BulletName = Bullet->GetAnimationName();

			HonTail_WingHp -= Damage;

			if (HonTail_WingHp <= 0)
			{
				m_WingHitBox->SetCollisionProfile("Die");
				WingDie = true;
				m_WingAnimation->ChangeAnimation("HonTailDie_Wing");
			
				m_RightHandHitBox->SetCollisionProfile("Monster");
			
			}

			Vector3 Pos = GetWorldPos();

			if (BulletName == "NormalAttack")
			{
				CHitEffect* Effect = m_Scene->CreateObject<CHitEffect>("HitEffect");
				Effect->SetAnimation("NormalAttackHit");

				if (m_WingSprite->GetWorldPos().x < result.Dest->GetWorldPos().x)
				{
					m_WingSprite->SetReverseX(false);
					Effect->SetRelativePosition(Bullet->GetWorldPos());
				}

				else
				{
					Effect->SetRelativePosition(Bullet->GetWorldPos());
				}


			}

			if (BulletName == "SpeedDuelShotBullet")
			{
				CHitEffect* Effect = m_Scene->CreateObject<CHitEffect>("HitEffect");
				Effect->SetAnimation("SpeedDualShotHit");

				if (m_WingSprite->GetWorldPos().x < result.Dest->GetWorldPos().x)
				{
					m_WingSprite->SetReverseX(false);
					Effect->SetRelativePosition(Bullet->GetWorldPos());
				}

				else
				{
					Effect->SetRelativePosition(Bullet->GetWorldPos());
				}
			}

			if (BulletName == "Ring_Arrow")
			{
				CHitEffect* Effect = m_Scene->CreateObject<CHitEffect>("HitEffect");
				Effect->SetAnimation("Ring_Effect");

				if (m_WingSprite->GetWorldPos().x < result.Dest->GetWorldPos().x)
				{
					m_WingSprite->SetReverseX(false);
					Effect->SetRelativePosition(Bullet->GetWorldPos());
				}

				else
				{
					Effect->SetRelativePosition(Bullet->GetWorldPos());
				}
			}
		}
	}
}

void CHonTail::LegHitBox(const CollisionResult& result)
{
	if (result.Dest->GetOwner()->GetName() == "Bullet")
	{

		if (HonTail_LegHp >= 0 && !LegDie)
		{
			CBullet* Bullet = (CBullet*)result.Dest->GetOwner();

			int Damage = Bullet->GetDamage();

			std::string BulletName = Bullet->GetAnimationName();

			HonTail_LegHp -= Damage;

			if (HonTail_LegHp <= 0)
			{
				m_LegHitBox->SetCollisionProfile("Die");
				LegDie = true;
				m_LegAnimation->ChangeAnimation("HonTailDie_Leg");
			
				m_WingHitBox->SetCollisionProfile("Monster");
			
			}

			Vector3 Pos = GetWorldPos();

			if (BulletName == "NormalAttack")
			{
				CHitEffect* Effect = m_Scene->CreateObject<CHitEffect>("HitEffect");
				Effect->SetAnimation("NormalAttackHit");

				if (m_LegSprite->GetWorldPos().x < result.Dest->GetWorldPos().x)
				{			
					Effect->SetRelativePosition(Bullet->GetWorldPos());
				}

				else
				{				
					Effect->SetRelativePosition(Bullet->GetWorldPos());
				}


			}

			if (BulletName == "SpeedDuelShotBullet")
			{
				CHitEffect* Effect = m_Scene->CreateObject<CHitEffect>("HitEffect");
				Effect->SetAnimation("SpeedDualShotHit");

				if (m_LegSprite->GetWorldPos().x < result.Dest->GetWorldPos().x)
				{			
					Effect->SetRelativePosition(Bullet->GetWorldPos());
				}

				else
				{				
					Effect->SetRelativePosition(Bullet->GetWorldPos());
				}
			}

			if (BulletName == "Ring_Arrow")
			{
				CHitEffect* Effect = m_Scene->CreateObject<CHitEffect>("HitEffect");
				Effect->SetAnimation("Ring_Effect");

				if (m_LegSprite->GetWorldPos().x < result.Dest->GetWorldPos().x)
				{		
					Effect->SetRelativePosition(Bullet->GetWorldPos());
				}

				else
				{				
					Effect->SetRelativePosition(Bullet->GetWorldPos());
				}
			}
		}
	}
}

void CHonTail::LeftHandHitBox(const CollisionResult& result)
{
	if (result.Dest->GetOwner()->GetName() == "Bullet")
	{

		if (HonTail_LeftHandHp >= 0 && !LeftHandDie)
		{
			CBullet* Bullet = (CBullet*)result.Dest->GetOwner();

			int Damage = Bullet->GetDamage();

			std::string BulletName = Bullet->GetAnimationName();

			HonTail_LeftHandHp -= Damage;

			if (HonTail_LeftHandHp <= 0)
			{			
				LeftHandDie = true;
				m_LeftHandAnimation->ChangeAnimation("HonTailDie_LeftHand");
				m_LeftHandHitBox->SetCollisionProfile("Die");

				m_LeftHeadHitBox->SetCollisionProfile("Monster");
			
			}

			Vector3 Pos = GetWorldPos();

			if (BulletName == "NormalAttack")
			{
				CHitEffect* Effect = m_Scene->CreateObject<CHitEffect>("HitEffect");
				Effect->SetAnimation("NormalAttackHit");

				if (m_LeftHandSprite->GetWorldPos().x < result.Dest->GetWorldPos().x)
				{		
					Effect->SetRelativePosition(Bullet->GetWorldPos());
				}

				else
				{
					Effect->SetRelativePosition(Bullet->GetWorldPos());
				}


			}

			if (BulletName == "SpeedDuelShotBullet")
			{
				CHitEffect* Effect = m_Scene->CreateObject<CHitEffect>("HitEffect");
				Effect->SetAnimation("SpeedDualShotHit");

				if (m_LeftHandSprite->GetWorldPos().x > result.Dest->GetWorldPos().x)
				{		
					Effect->SetRelativePosition(Bullet->GetWorldPos());
				}
			
			}

			if (BulletName == "Ring_Arrow")
			{
				CHitEffect* Effect = m_Scene->CreateObject<CHitEffect>("HitEffect");
				Effect->SetAnimation("Ring_Effect");

				if (m_LeftHandSprite->GetWorldPos().x < result.Dest->GetWorldPos().x)
				{			
					Effect->SetRelativePosition(Bullet->GetWorldPos());
				}

				else
				{
					Effect->SetRelativePosition(Bullet->GetWorldPos());
				}
			}
		}
	}
}

void CHonTail::RightHandHitBox(const CollisionResult& result)
{
	if (result.Dest->GetOwner()->GetName() == "Bullet")
	{

		if (HonTail_RightHandHp >= 0 && !RightHandDie)
		{
			CBullet* Bullet = (CBullet*)result.Dest->GetOwner();

			int Damage = Bullet->GetDamage();

			std::string BulletName = Bullet->GetAnimationName();

			HonTail_RightHandHp -= Damage;

			if (HonTail_RightHandHp <= 0)
			{		
				RightHandDie = true;
				m_RightHandHitBox->SetCollisionProfile("Die");
				m_RightHandAnimation->ChangeAnimation("HonTailDie_RightHand");

				m_RightHeadHitBox->SetCollisionProfile("Monster");
			
			}

			Vector3 Pos = GetWorldPos();

			if (BulletName == "NormalAttack")
			{
				CHitEffect* Effect = m_Scene->CreateObject<CHitEffect>("HitEffect");
				Effect->SetAnimation("NormalAttackHit");

				if (m_RightHandSprite->GetWorldPos().x < result.Dest->GetWorldPos().x)
				{		
					Effect->SetRelativePosition(Bullet->GetWorldPos());
				}

				else
				{
					Effect->SetRelativePosition(Pos.x - 100.f, Pos.y - 250.f);
				}


			}

			if (BulletName == "SpeedDuelShotBullet")
			{
				CHitEffect* Effect = m_Scene->CreateObject<CHitEffect>("HitEffect");
				Effect->SetAnimation("SpeedDualShotHit");

				if (m_RightHandSprite->GetWorldPos().x < result.Dest->GetWorldPos().x)
				{			
					Effect->SetRelativePosition(Pos.x + 300.f, Pos.y - 250.f);
				}

				else
				{
					Effect->SetRelativePosition(Pos.x - 100.f, Pos.y - 250.f);
				}
			}

			if (BulletName == "Ring_Arrow")
			{
				CHitEffect* Effect = m_Scene->CreateObject<CHitEffect>("HitEffect");
				Effect->SetAnimation("Ring_Effect");

				if (m_RightHandSprite->GetWorldPos().x < result.Dest->GetWorldPos().x)
				{		
					Effect->SetRelativePosition(Bullet->GetWorldPos());
				}

				else
				{
					Effect->SetRelativePosition(Bullet->GetWorldPos());
				}
			}
		}
	}
}

void CHonTail::LeftHeadHitBox(const CollisionResult& result)
{
	if (result.Dest->GetOwner()->GetName() == "Bullet")
	{

		if (HonTail_LeftHeadHp >= 0 && !LeftHeadDie)
		{
			CBullet* Bullet = (CBullet*)result.Dest->GetOwner();

			int Damage = Bullet->GetDamage();

			std::string BulletName = Bullet->GetAnimationName();

			HonTail_LeftHeadHp -= Damage;

			if (HonTail_LeftHeadHp <= 0)
			{
				m_LeftHeadHitBox->SetCollisionProfile("Die");
				LeftHeadDie = true;
				m_LeftHeadAnimation->ChangeAnimation("HonTailDie_LeftHead");

				m_MainHeadHitBox->SetCollisionProfile("Monster");
			
			}

			Vector3 Pos = GetWorldPos();

			if (BulletName == "NormalAttack")
			{
				CHitEffect* Effect = m_Scene->CreateObject<CHitEffect>("HitEffect");
				Effect->SetAnimation("NormalAttackHit");

				if (m_LeftHeadSprite->GetWorldPos().x < result.Dest->GetWorldPos().x)
				{			
					Effect->SetRelativePosition(Bullet->GetWorldPos());
				}

				else
				{
					Effect->SetRelativePosition(Bullet->GetWorldPos());
				}


			}

			if (BulletName == "SpeedDuelShotBullet")
			{
				CHitEffect* Effect = m_Scene->CreateObject<CHitEffect>("HitEffect");
				Effect->SetAnimation("SpeedDualShotHit");

				if (m_LeftHeadSprite->GetWorldPos().x < result.Dest->GetWorldPos().x)
				{
					Effect->SetRelativePosition(Bullet->GetWorldPos());
				}

				else
				{
					Effect->SetRelativePosition(Bullet->GetWorldPos());
				}
			}

			if (BulletName == "Ring_Arrow")
			{
				CHitEffect* Effect = m_Scene->CreateObject<CHitEffect>("HitEffect");
				Effect->SetAnimation("Ring_Effect");

				if (m_LeftHeadSprite->GetWorldPos().x < result.Dest->GetWorldPos().x)
				{
					Effect->SetRelativePosition(Bullet->GetWorldPos());
				}

				else
				{
					Effect->SetRelativePosition(Bullet->GetWorldPos());
				}
			}
		}
	}
}

void CHonTail::RightHeadHitBox(const CollisionResult& result)
{
	if (result.Dest->GetOwner()->GetName() == "Bullet")
	{

		if (HonTail_RightHeadHp >= 0 && !RightHeadDie)
		{
			CBullet* Bullet = (CBullet*)result.Dest->GetOwner();

			int Damage = Bullet->GetDamage();

			std::string BulletName = Bullet->GetAnimationName();

			HonTail_RightHeadHp -= Damage;

			if (HonTail_RightHeadHp <= 0)
			{
				m_RightHeadHitBox->SetCollisionProfile("Die");
				RightHeadDie = true;
				m_RightHeadAnimation->ChangeAnimation("HonTailDie_RightHead");

				m_LeftHandHitBox->SetCollisionProfile("Monster");

			}

			Vector3 Pos = GetWorldPos();

			if (BulletName == "NormalAttack")
			{
				CHitEffect* Effect = m_Scene->CreateObject<CHitEffect>("HitEffect");
				Effect->SetAnimation("NormalAttackHit");

				if (m_RightHeadSprite->GetWorldPos().x < result.Dest->GetWorldPos().x)
				{
					Effect->SetRelativePosition(Bullet->GetWorldPos());
				}

				else
				{
					Effect->SetRelativePosition(Bullet->GetWorldPos());
				}


			}

			if (BulletName == "SpeedDuelShotBullet")
			{
				CHitEffect* Effect = m_Scene->CreateObject<CHitEffect>("HitEffect");
				Effect->SetAnimation("SpeedDualShotHit");

				if (m_RightHeadSprite->GetWorldPos().x < result.Dest->GetWorldPos().x)
				{
					Effect->SetRelativePosition(Bullet->GetWorldPos());
				}

				else
				{
					Effect->SetRelativePosition(Bullet->GetWorldPos());
				}
			}

			if (BulletName == "Ring_Arrow")
			{
				CHitEffect* Effect = m_Scene->CreateObject<CHitEffect>("HitEffect");
				Effect->SetAnimation("Ring_Effect");

				if (m_RightHeadSprite->GetWorldPos().x < result.Dest->GetWorldPos().x)
				{
					Effect->SetRelativePosition(Bullet->GetWorldPos());
				}

				else
				{
					Effect->SetRelativePosition(Bullet->GetWorldPos());
				}
			}
		}
	}
}

void CHonTail::MainHeadHitBox(const CollisionResult& result)
{


		if (result.Dest->GetOwner()->GetName() == "Bullet")
		{

			if (HonTail_MainHeadHp >= 0 && !MainHeadDie)
			{
				CBullet* Bullet = (CBullet*)result.Dest->GetOwner();

				int Damage = Bullet->GetDamage();

				std::string BulletName = Bullet->GetAnimationName();

				HonTail_MainHeadHp -= Damage;

				if (HonTail_MainHeadHp <= 0)
				{
					m_MainHeadHitBox->SetCollisionProfile("Die");
					MainHeadDie = true;
					m_MainHeadAnimation->ChangeAnimation("HonTailDie_MainHead");					
				}

				Vector3 Pos = GetWorldPos();

				if (BulletName == "NormalAttack")
				{
					CHitEffect* Effect = m_Scene->CreateObject<CHitEffect>("HitEffect");
					Effect->SetAnimation("NormalAttackHit");

					if (m_MainHeadSprite->GetWorldPos().x < result.Dest->GetWorldPos().x)
					{
						Effect->SetRelativePosition(Bullet->GetWorldPos());
					}

					else
					{
						Effect->SetRelativePosition(Bullet->GetWorldPos());
					}
				}

				if (BulletName == "SpeedDuelShotBullet")
				{
					CHitEffect* Effect = m_Scene->CreateObject<CHitEffect>("HitEffect");
					Effect->SetAnimation("SpeedDualShotHit");

					if (m_MainHeadSprite->GetWorldPos().x < result.Dest->GetWorldPos().x)
					{
						Effect->SetRelativePosition(Bullet->GetWorldPos());
					}

					else
					{
						Effect->SetRelativePosition(Bullet->GetWorldPos());
					}
				}

				if (BulletName == "Ring_Arrow")
				{
					CHitEffect* Effect = m_Scene->CreateObject<CHitEffect>("HitEffect");
					Effect->SetAnimation("Ring_Effect");

					if (m_MainHeadSprite->GetWorldPos().x < result.Dest->GetWorldPos().x)
					{
						Effect->SetRelativePosition(Bullet->GetWorldPos());
					}

					else
					{
						Effect->SetRelativePosition(Bullet->GetWorldPos());
					}
				}
			}
		}
	
}

void CHonTail::HonTailMainHeadExNotify()
{

	float PlayerPosX = m_Player->GetWorldPos().x;


	CHonTailExObj* ExObj = m_Scene->CreateObject<CHonTailExObj>("HonTailExObj");
	ExObj->SetWorldPosition(PlayerPosX, 400.f);

}


void CHonTail::HonTailMainHeadNotify()
{
	if (m_BottomSectionCollision)
	{
		HonTailHitEffect* HitEffect = m_Scene->CreateObject<HonTailHitEffect>("HonTailHitEffect");
		HitEffect->SetCollisionProfile("JungSY");
		HitEffect->SetAnimation("HonTailMainHead_Hit");
		HitEffect->SetWorldPosition(m_Player->GetWorldPos());
	}

	else
	{
		HonTailHitEffect* HitEffect = m_Scene->CreateObject<HonTailHitEffect>("HonTailHitEffect");
		HitEffect->SetCollisionProfile("JungSY");
		HitEffect->SetAnimation("HonTailMainHeadSkill_Hit");
		HitEffect->SetWorldPosition(GetWorldPos());
	}
}

void CHonTail::HonTailLeftHeadNotify()
{
	if (m_LeftLegSectionCollision)
	{
		HonTailHitEffect* HitEffect = m_Scene->CreateObject<HonTailHitEffect>("HonTailHitEffect");
		HitEffect->SetWorldPosition(m_Player->GetWorldPos().x + 10.f, m_Player->GetWorldPos().y + 50.f);
		HitEffect->SetAnimation("HonTailLeftHead_Hit");
		HitEffect->SetCollisionProfile("JungSY");
	}

	else
	{
		HonTailHitEffect* HitEffect = m_Scene->CreateObject<HonTailHitEffect>("HonTailHitEffect");
		HitEffect->SetWorldPosition(m_Player->GetWorldPos().x - 10.f, m_Player->GetWorldPos().y + 50.f);
		HitEffect->SetAnimation("HonTailLeftHeadSkill_Hit");
		HitEffect->SetCollisionProfile("JungSY");
	}
}

void CHonTail::HonTailRightHeadNotify()
{
	if (m_RightLegSectionCollision)
	{		
		HonTailHitEffect* HitEffect = m_Scene->CreateObject<HonTailHitEffect>("HonTailHitEffect");
		HitEffect->SetWorldPosition(m_Player->GetWorldPos().x - 10.f, m_Player->GetWorldPos().y + 50.f);
		HitEffect->SetAnimation("HonTailRightHead_Hit");
		HitEffect->SetCollisionProfile("JungSY");
	}

	else
	{
		HonTailHitEffect* HitEffect = m_Scene->CreateObject<HonTailHitEffect>("HonTailHitEffect");
		HitEffect->SetWorldPosition(m_Player->GetWorldPos().x - 10.f, m_Player->GetWorldPos().y + 50.f);
		HitEffect->SetAnimation("HonTailRightHeadSkill_Hit");
		HitEffect->SetCollisionProfile("JungSY");
	}


}

void CHonTail::HonTailLegNotify()
{
	if (m_LeftLegSectionCollision)
	{
		if (m_LegAnimation->GetCurrentAnimName() == "HonTailLeg_LeftAttack")
		{
			HonTailHitEffect* HitEffect = m_Scene->CreateObject<HonTailHitEffect>("HonTailHitEffect");
			HitEffect->SetWorldPosition(m_Player->GetWorldPos().x + 20.f, m_Player->GetWorldPos().y + 30.f);
			HitEffect->SetAnimation("HonTailLeg_Hit");
			HitEffect->SetCollisionProfile("JungSY");
		}
	}

	if (m_RightLegSectionCollision)
	{
		if (m_LegAnimation->GetCurrentAnimName() == "HonTailLeg_RightAttack")
		{
			HonTailHitEffect* HitEffect = m_Scene->CreateObject<HonTailHitEffect>("HonTailHitEffect");
			HitEffect->SetWorldPosition(m_Player->GetWorldPos().x - 20.f, m_Player->GetWorldPos().y + 30.f);
			HitEffect->SetAnimation("HonTailLeg_Hit");
			HitEffect->SetCollisionProfile("JungSY");
		}
	}
}

void CHonTail::HonTailWingNotify()
{
	if (m_RightSectionCollision || m_LeftSectionCollision)
	{
		HonTailHitEffect* HitEffect = m_Scene->CreateObject<HonTailHitEffect>("HonTailHitEffect");
		HitEffect->SetWorldPosition(m_Player->GetWorldPos().x - 20.f, m_Player->GetWorldPos().y + 30.f);
		HitEffect->SetAnimation("HonTailWing_Hit");
		HitEffect->SetCollisionProfile("JungSY");
	}
}

void CHonTail::HonTailTailNotify()
{
	if (m_RightLegSectionCollision)
	{
		HonTailHitEffect* HitEffect = m_Scene->CreateObject<HonTailHitEffect>("HonTailHitEffect");
		HitEffect->SetWorldPosition(m_Player->GetWorldPos().x - 20.f, m_Player->GetWorldPos().y + 30.f);
		HitEffect->SetAnimation("HonTailTail_Hit");
		HitEffect->SetCollisionProfile("JungSY");
	}
}