#include "DarkWybern.h"
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
#include <time.h>
#include "Player2D.h"
#include "HitEffect.h"
#include "Respawn.h"
#include "../UI/MonsterBarUI.h"
#include "../Scene/EditorDefaultScene.h"

#include "../Setting/DefaultSetting.h"
#include "Engine.h"
#include "../Setting/EngineShareSetting.h"
#include "../UI/StartSceneUI.h"
#include "../UI/EquipmentUI.h"
#include "../UI/InventoryUI.h"
#include "../UI/StatusUI.h"
#include "../UI/QuestUI.h"
#include "UI/UIProgressBar.h"
#include "UI/UIText.h"
#include "TimerManager.h"

CDarkWybern::CDarkWybern()
{
	SetTypeID<CDarkWybern>();
	m_ObjectTypeName = "DarkWybern";
}

CDarkWybern::CDarkWybern(const CDarkWybern& Obj) : 
	CGameObject(Obj)
{
	m_HitBox = (CColliderBox2D*)FindComponent("WybernBody");
	m_MainSprite = (CSpriteComponent*)FindComponent("WybernSprite");
	m_SkillHitBox = (CColliderBox2D*)FindComponent("WybernSkillHitBox");
}

CDarkWybern::~CDarkWybern()
{
}

void CDarkWybern::Start()
{
	CGameObject::Start();

	CSceneManager::GetInst()->GetScene()->GetResource()->LoadSound("Effect", "DarkWybernAttack", false, "DarkWybernAttack.mp3");
	CSceneManager::GetInst()->GetScene()->GetResource()->LoadSound("Effect", "DarkWybernDie", false, "DarkWybernDie.mp3");

	if (m_Scene)
	{
		m_MonsterBarUI = m_Scene->GetViewport()->FindUIWindow<CMonsterBarUI>("MonsterBarUI");
		m_MainUI = m_Scene->GetViewport()->FindUIWindow<CStartSceneUI>("StartSceneUI");
		m_Player = (CPlayer2D*)m_Scene->FindObject("Player2D");
	}

	else
	{
		m_MonsterBarUI = CSceneManager::GetInst()->GetScene()->GetViewport()->FindUIWindow<CMonsterBarUI>("MonsterBarUI");
		m_MainUI = CSceneManager::GetInst()->GetScene()->GetViewport()->FindUIWindow<CStartSceneUI>("StartSceneUI");
		m_Player = (CPlayer2D*)CSceneManager::GetInst()->GetScene()->FindObject("Player2D");
	}

	m_Alive = true;

	m_MaxHp = 500;
	m_Hp = 300;
	m_Exp = 300;


	m_Animation = m_MainSprite->SetAnimation<CAnimation2D>("DarkWybern");
	m_Animation->AddAnimation("DarkWybernStand", "DarkWybernStand");
	m_Animation->AddAnimation("DarkWybernAttack", "DarkWybernAttack");
	m_Animation->AddAnimation("DarkWybernHit", "DarkWybernHit");
	m_Animation->AddAnimation("DarkWybernDie", "DarkWybernDie");

	m_Animation->SetLoop("DarkWybernStand", true);

	m_Animation->SetPlayTime("DarkWybernAttack", 0.8f);

	m_Animation->SetCurrentEndFunction<CDarkWybern>("DarkWybernAttack", this, &CDarkWybern::DarkWybernAttackEndFunc);
	m_Animation->SetCurrentEndFunction<CDarkWybern>("DarkWybernHit", this, &CDarkWybern::DarkWybernHitEndFunc);
	m_Animation->SetCurrentEndFunction<CDarkWybern>("DarkWybernDie", this, &CDarkWybern::DarkWybernDieEndFunc);

	m_Hpbar = m_MonsterBarUI->GetProGressBar(m_Hp, GetWorldPos());

	m_NameText = m_MonsterBarUI->GetMonsterNameTag(TEXT("다크 와이번"), Vector2(GetWorldPos()));


	m_HitBox->SetCollisionCallback<CDarkWybern>(ECollision_Result::Collision, this, &CDarkWybern::HitBoxCollisionFunc);
	m_SkillHitBox->SetCollisionCallback<CDarkWybern>(ECollision_Result::Collision, this, &CDarkWybern::AttackSectionOnFunc);
	m_SkillHitBox->SetCollisionCallback<CDarkWybern>(ECollision_Result::Release, this, &CDarkWybern::AttackSectionOffFunc);

}

bool CDarkWybern::Init()
{
	CGameObject::Init();

	m_HitBox = CreateComponent<CColliderBox2D>("WybernBody");
	m_MainSprite = CreateComponent<CSpriteComponent>("WybernSprite");
	m_SkillHitBox = CreateComponent<CColliderBox2D>("WybernSkillHitBox");

	SetRootComponent(m_HitBox);
	m_HitBox->AddChild(m_MainSprite);
	m_HitBox->AddChild(m_SkillHitBox);

	m_HitBox->SetWorldPosition(600.f, 250.f);
	m_HitBox->SetBoxSize(100.f, 200.f);
	m_SkillHitBox->SetBoxSize(500.f, 200.f);
	m_MainSprite->SetPivot(0.5f, 0.5f);

	m_HitBox->SetCollisionProfile("Monster");
	m_SkillHitBox->SetCollisionProfile("MonsterAttack");

	return true;
}

void CDarkWybern::Save(FILE* File)
{
	CGameObject::Save(File);
}

void CDarkWybern::Load(FILE* File)
{
	CGameObject::Load(File);
}

void CDarkWybern::Destroy()
{
	CGameObject::Destroy();
}

void CDarkWybern::FirstUpdate(float DeltaTime)
{
	CGameObject::FirstUpdate(DeltaTime);

	m_PrevPos = GetWorldPos();

	if (!m_AttackOn && !m_AttackSectionOn && !m_MoveLeft && !m_MoveRight && m_Alive)
		m_RandomMoveOn = true;

	else
		m_RandomMoveOn = false;

	if (m_RandomMoveOn)
	{	
		int Count = CEngine::GetInst()->GetNumber();

		if (Count > 50 && GetWorldPos().x > 200.f)
		{
			m_MoveLeft = true;
			m_RandomMoveOn = false;
		}

		if (Count < 50 && GetWorldPos().x < 1300.f)
		{
			m_MoveRight = true;
			m_RandomMoveOn = false;
		}
	}

	if (m_MoveLeft && !m_Hit)
	{
		m_MoveTime += DeltaTime;

		AddWorldPositionX(-50.f * DeltaTime);

		if (m_MoveTime > 3.f)
		{
			m_MoveLeft = false;
			m_MoveTime = 0.f;
		}
	}

	if (m_MoveRight && !m_Hit)
	{
		m_MoveTime += DeltaTime;

		AddWorldPositionX(50.f * DeltaTime);

		if (m_MoveTime > 3.f)
		{
			m_MoveRight = false;
			m_MoveTime = 0.f;
		}
	}
}

void CDarkWybern::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	m_Pos = GetWorldPos();

	m_Move = m_Pos - m_PrevPos;

	if (m_Alive && m_AttackSectionOn && !m_AttackOn)
	{
		m_AttackTime += DeltaTime;

		if (m_AttackTime > 3.5f)
		{
			m_AttackOn = true;

			if (m_Player->GetWorldPos().x > GetWorldPos().x)
			{
				m_MainSprite->SetReverseX(true);
				m_Animation->ChangeAnimation("DarkWybernAttack");
				m_AttackTime = 0.f;
				m_Scene->GetResource()->SoundPlay("DarkWybernAttack");
			}

			else
			{
				m_MainSprite->SetReverseX(false);
				m_Animation->ChangeAnimation("DarkWybernAttack");
				m_AttackTime = 0.f;
				m_Scene->GetResource()->SoundPlay("DarkWybernAttack");
			}
		}
	}

	if (m_Animation)
	{
		float ImageWidth, ImageHeight;
		int Count = m_Animation->GetCurrentFrame(m_Animation->GetCurrentAnimName());
		ImageWidth = (float)(m_Animation->GetCurrentAnimationSequence(m_Animation->GetCurrentAnimName())->GetTexture()->GetWidth(Count));
		ImageHeight = (float)(m_Animation->GetCurrentAnimationSequence(m_Animation->GetCurrentAnimName())->GetTexture()->GetHeight(Count));

		m_MainSprite->SetRelativeScale(ImageWidth, ImageHeight);

		m_MainSprite->SetPivot(0.5f, 0.5f);
	}

	if (m_Alive && m_Hp <= 0)
	{
		m_Alive = false;
		m_HitBox->SetCollisionProfile("Die");
		m_Animation->ChangeAnimation("DarkWybernDie");
		m_Scene->GetResource()->SoundPlay("DarkWybernDie");	
	}

}

void CDarkWybern::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);

	CCameraComponent* Camera = CSceneManager::GetInst()->GetScene()->GetCameraManager()->GetCurrentCamera();

	if (m_Alive && m_LeftHitOn)
	{
		m_LeftHitOn = false;
		if (GetWorldPos().x < 1550.f)
		AddWorldPositionX(5.f);
	}

	if (m_Alive && m_RightHitOn)
	{
		m_RightHitOn = false;
		if(GetWorldPos().x > 10.f)
		AddWorldPositionX(-5.f);
	}
	
	if (m_Hit)
	{
		m_HitTime += DeltaTime;

		if (m_HitTime > 1.f)
		{
			m_Hit = false;

			if (m_Alive && !m_AttackOn)
				m_Animation->ChangeAnimation("DarkWybernStand");

			m_HitTime = 0.f;
		}
	}

	if (m_Hpbar)
	{
		Vector2 WorldPos = GetWorldPos();
		Vector2 CameraWorldPos = Camera->GetWorldPos();
		Vector2 RealPos = WorldPos - CameraWorldPos;

		m_Hpbar->SetUIPos(RealPos);
		m_Hpbar->SetValue((float)m_Hp);
		m_NameText->SetPos(Vector2(RealPos.x - 15.f, RealPos.y - 80.f));
	}

	if (m_Alive && m_Move.x < 0 && !m_Hit)
	{
		m_MainSprite->SetReverseX(false);
	}

	if (m_Alive && m_Move.x > 0 && !m_Hit)
	{
		m_MainSprite->SetReverseX(true);
	}

}

CDarkWybern* CDarkWybern::Clone() const
{
	return new CDarkWybern(*this);
}

void CDarkWybern::DarkWybernAttackEndFunc()
{
	if (m_Alive)
	{
		if (m_MainSprite->GetReverseX())
		{
			HonTailHitEffect* HitEffect = m_Scene->CreateObject<HonTailHitEffect>("HonTailHitEffect");
			HitEffect->SetWorldPosition(m_Player->GetWorldPos().x - 20.f, m_Player->GetWorldPos().y + 30.f);
			HitEffect->SetAnimation("DarkWybernHitEffect");
			HitEffect->SetCollisionProfile("JungSY");
		}

		else
		{
			HonTailHitEffect* HitEffect = m_Scene->CreateObject<HonTailHitEffect>("HonTailHitEffect");
			HitEffect->SetWorldPosition(m_Player->GetWorldPos().x + 20.f, m_Player->GetWorldPos().y + 30.f);
			HitEffect->SetAnimation("DarkWybernHitEffect");
			HitEffect->SetCollisionProfile("JungSY");
		}

		m_AttackOn = false;
		m_Animation->ChangeAnimation("DarkWybernStand");
	}

}

void CDarkWybern::DarkWybernDieEndFunc()
{
	m_MainUI->SetExp(m_Exp);
	
	m_NameText->SetEnable(false);
	m_Hpbar->SetEnable(false);	

	int Number = CEngine::GetInst()->GetNumber();

	CRespawn* Respawn = m_Scene->CreateObject<CRespawn>("Respawn");
	Respawn->SetRespawn(true, Vector2(100.f + (float)Number * 10, GetWorldPos().y), "DarkWybern");

	Destroy();
}

void CDarkWybern::DarkWybernHitEndFunc()
{
	//if (m_Alive && !m_AttackOn)
	//{
	//	m_Animation->ChangeAnimation("DarkWybernStand");
	//}
}

void CDarkWybern::AttackSectionOnFunc(const CollisionResult& result)
{
	m_AttackSectionOn = true;
}

void CDarkWybern::AttackSectionOffFunc(const CollisionResult& result)
{
	m_AttackSectionOn = false;
}

void CDarkWybern::HitBoxCollisionFunc(const CollisionResult& result)
{
	if (m_Player->GetWorldPos().x < GetWorldPos().x)
	{
		m_MoveLeft = true;
	}

	else
		m_MoveRight = true;


	if (m_Hp > 0 && result.Dest->GetCollisionProfile()->Channel->Name == "PlayerAttack")
	{
		CBullet* Bullet = (CBullet*)result.Dest->GetOwner();
		int Damage = Bullet->GetDamage();

		m_Hit = true;


		std::string BulletName = Bullet->GetAnimationName();

		Vector3 Pos = GetWorldPos();

		if (BulletName == "NormalAttack")
		{
			CHitEffect* Effect = m_Scene->CreateObject<CHitEffect>("HitEffect");
			Effect->SetAnimation("NormalAttackHit");

			if (m_HitBox->GetWorldPos().x < result.Dest->GetWorldPos().x)
			{
				m_RightHitOn = true;
				m_MainSprite->SetReverseX(true);
				Effect->SetRelativePosition(Pos.x + 50.f, Pos.y + 20.f);
		

				if (!m_AttackOn)
					m_Animation->ChangeAnimation("DarkWybernHit");

			}

			else
			{
				m_LeftHitOn = true;
				m_MainSprite->SetReverseX(false);
				Effect->SetRelativePosition(Pos.x - 50.f, Pos.y + 20.f);
			

				if (!m_AttackOn)
					m_Animation->ChangeAnimation("DarkWybernHit");
			}
		}

		if (BulletName == "SpeedDuelShotBullet")
		{
			CHitEffect* Effect = m_Scene->CreateObject<CHitEffect>("HitEffect");
			Effect->SetAnimation("SpeedDualShotHit");

			if (m_HitBox->GetWorldPos().x < result.Dest->GetWorldPos().x)
			{
				m_RightHitOn = true;
				m_MainSprite->SetReverseX(true);
				Effect->SetRelativePosition(Pos.x + 50.f, Pos.y + 20.f);			

				if (!m_AttackOn)
					m_Animation->ChangeAnimation("DarkWybernHit");
			}

			else
			{
				m_LeftHitOn = true;
				m_MainSprite->SetReverseX(false);
				Effect->SetRelativePosition(Pos.x - 50.f, Pos.y + 20.f);		

				if (!m_AttackOn)
					m_Animation->ChangeAnimation("DarkWybernHit");
			}
		}

		if (BulletName == "Ring_Arrow")
		{
			CHitEffect* Effect = m_Scene->CreateObject<CHitEffect>("HitEffect");
			Effect->SetAnimation("Ring_Effect");

			if (m_HitBox->GetWorldPos().x < result.Dest->GetWorldPos().x)
			{
				m_RightHitOn = true;
				m_MainSprite->SetReverseX(true);
				Effect->SetRelativePosition(Pos.x + 50.f, Pos.y + 20.f);				
			

				if (!m_AttackOn)
					m_Animation->ChangeAnimation("DarkWybernHit");
			}
			else
			{
				m_LeftHitOn = true;
				m_MainSprite->SetReverseX(false);
				Effect->SetRelativePosition(Pos.x - 50.f, Pos.y + 20.f);			

				if (!m_AttackOn)
					m_Animation->ChangeAnimation("DarkWybernHit");
			}
		}


		m_Hpbar->SetEnable(true);
		m_NameText->SetEnable(true);
		m_Hp -= Damage;
	}
}
