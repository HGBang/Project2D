#include "Skelegon.h"
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

CSkelegon::CSkelegon()
{
	SetTypeID<CSkelegon>();
	m_ObjectTypeName = "Skelegon";
}

CSkelegon::CSkelegon(const CSkelegon& Obj) :
	CGameObject(Obj)
{
	m_HitBox = (CColliderBox2D*)FindComponent("Body");
	m_MainSprite = (CSpriteComponent*)FindComponent("sprite");
	m_SkillHitBox = (CColliderBox2D*)FindComponent("SkillHitBox");
}

CSkelegon::~CSkelegon()
{
	CGameObject::Destroy();
}

void CSkelegon::Start()
{
	CGameObject::Start();

	CSceneManager::GetInst()->GetScene()->GetResource()->LoadSound("Effect", "SkelegonAttack", false, "SkelegonAttack.mp3");
	CSceneManager::GetInst()->GetScene()->GetResource()->LoadSound("Effect", "SkelegonDie", false, "SkelegonDie.mp3");

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


	m_Animation = m_MainSprite->SetAnimation<CAnimation2D>("Skelegon");
	m_Animation->AddAnimation("SkelegonStand", "SkelegonStand");
	m_Animation->AddAnimation("SkelegonMove", "SkelegonMove");
	m_Animation->AddAnimation("SkelegonAttack", "SkelegonAttack");
	m_Animation->AddAnimation("SkelegonBuff", "SkelegonBuff");
	m_Animation->AddAnimation("SkelegonHit", "SkelegonHit");
	m_Animation->AddAnimation("SkelegonDie", "SkelegonDie");

	m_Animation->SetLoop("SkelegonStand", true);
	m_Animation->SetLoop("SkelegonMove", true);
	m_Animation->SetLoop("SkelegonBuff", true);


	m_Animation->SetPlayTime("SkelegonMove", 0.7f);
	m_Animation->SetPlayTime("SkelegonBuff", 1.7f);
	m_Animation->SetPlayTime("SkelegonAttack", 1.7f);
	m_Animation->SetPlayTime("SkelegonHit", 1.7f);

	m_Animation->SetCurrentEndFunction<CSkelegon>("SkelegonBuff", this, &CSkelegon::AnimationEndFunc);
	m_Animation->SetCurrentEndFunction<CSkelegon>("SkelegonAttack", this, &CSkelegon::AnimationEndFunc);
	m_Animation->SetCurrentEndFunction<CSkelegon>("SkelegonDie", this, &CSkelegon::SkelegonDie);
	m_Animation->SetCurrentEndFunction<CSkelegon>("SkelegonHit", this, &CSkelegon::SkelegonHit);


	CTimerManager::GetInst()->SetTimer(m_TimerNumber, 4.f, true, std::bind(&CSkelegon::SkelegonSkillAttack, this));
	CTimerManager::GetInst()->SetTimer(m_TimerNumber, 13.f, true, std::bind(&CSkelegon::SkelegonSkillBuff, this));
	CTimerManager::GetInst()->SetTimer(m_TimerNumber, 0.5f, true, std::bind(&CSkelegon::SkelegonSectionCheck, this));
	CTimerManager::GetInst()->SetTimer(m_TimerNumber, 5.f, true, std::bind(&CSkelegon::RandomMoveCheck, this));


	m_HitBox->SetCollisionCallback<CSkelegon>(ECollision_Result::Collision, this, &CSkelegon::HitBoxCollision);
	m_SkillHitBox->SetCollisionCallback<CSkelegon>(ECollision_Result::Collision, this, &CSkelegon::CollisionSectionCheck);
	m_SkillHitBox->SetCollisionCallback<CSkelegon>(ECollision_Result::Release, this, &CSkelegon::CollisionSectionCheckOff);



	m_SkelNotify = m_Animation->FindAnimation("SkelegonAttack");
	m_SkelNotify->AddNotify("SkelegonAttack", 7, this, &CSkelegon::SkelegonSkillNotify);

	m_Hp = 500;
	m_Alive = true;
	m_Exp = 500;

	m_Hpbar = m_MonsterBarUI->GetProGressBar(m_Hp, GetWorldPos());

	m_NameText = m_MonsterBarUI->GetMonsterNameTag(TEXT("½ºÄÌ·¹°ï"), Vector2(GetWorldPos()));


}

bool CSkelegon::Init()
{
	CGameObject::Init();

	m_HitBox				= CreateComponent<CColliderBox2D>("Body");
	m_MainSprite			= CreateComponent<CSpriteComponent>("sprite");
	m_SkillHitBox			= CreateComponent<CColliderBox2D>("SkillHitBox");

	SetRootComponent(m_HitBox);
	m_HitBox->AddChild(m_MainSprite);
	m_HitBox->AddChild(m_SkillHitBox);

	m_HitBox->SetWorldPosition(200.f, 250.f);
	m_SkillHitBox->SetBoxSize(500.f, 200.f);
	m_MainSprite->SetPivot(0.5f, 0.5f);	

	m_HitBox->SetCollisionProfile("Monster");
	m_SkillHitBox->SetCollisionProfile("MonsterAttack");

	return true;
}

void CSkelegon::Save(FILE* File)
{
	CGameObject::Save(File);
}

void CSkelegon::Load(FILE* File)
{
	CGameObject::Load(File);
}

void CSkelegon::Destroy()
{
	CGameObject::Destroy();
}

void CSkelegon::FirstUpdate(float DeltaTime)
{
	CGameObject::FirstUpdate(DeltaTime);

	m_PrevPos = GetWorldPos();

	m_TestTime += DeltaTime;

	if (m_Alive && m_MoveRight && !m_SkillAttackOn)
		SkelegonMoveRight(DeltaTime);

	if (m_Alive && m_MoveLeft && !m_SkillAttackOn)
		SkelegonMoveLeft(DeltaTime);

	if (m_Alive && m_RandomRight)
	{

		if (GetWorldPos().x > 1500.f)
			return;

		m_RandomTime += DeltaTime;

		SkelegonMoveRight(DeltaTime);

		if (m_RandomTime > 1.f)
		{
			m_RandomRight = false;
			m_RandomTime = 0.f;
		}
	}

	if (m_Alive && m_RandomLeft)
	{

		if (GetWorldPos().x < 50.f)
			return;

		SkelegonMoveLeft(DeltaTime);

		m_RandomTime += DeltaTime;

		if (m_RandomTime > 1.f)
		{
			m_RandomLeft = false;
			m_RandomTime = 0.f;
		}
	}



}

void CSkelegon::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	m_Pos = GetWorldPos();

	m_Move = m_Pos - m_PrevPos;


	if (m_Animation)
	{
		float ImageWidth, ImageHeight;
		int Count = m_Animation->GetCurrentFrame(m_Animation->GetCurrentAnimName());
		ImageWidth = (float)(m_Animation->GetCurrentAnimationSequence(m_Animation->GetCurrentAnimName())->GetTexture()->GetWidth(Count));
		ImageHeight = (float)(m_Animation->GetCurrentAnimationSequence(m_Animation->GetCurrentAnimName())->GetTexture()->GetHeight(Count));

		m_MainSprite->SetRelativeScale(ImageWidth, ImageHeight);

		m_MainSprite->SetPivot(0.5f, 0.5f);

		if (m_Animation->GetCurrentAnimName() == "SkelegonAttack")
			m_MainSprite->SetPivot(0.8f, 0.5f);

		if (m_Animation->GetCurrentAnimName() == "SkelegonBuff")
			m_MainSprite->SetPivot(0.5f, 0.38f);

		if (m_Animation->GetCurrentAnimName() == "SkelegonAttack")
			m_MainSprite->SetPivot(0.2f, 0.5f);

		if (m_Animation->GetCurrentAnimName() == "SkelegonAttack" && !m_MainSprite->GetReverseX())
			m_MainSprite->SetPivot(0.8f, 0.5f);

		if (m_Animation->GetCurrentAnimName() == "SkelegonHit")
			m_MainSprite->SetPivot(0.5f, 0.5f);
	}

}

void CSkelegon::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);

	if (m_Alive && m_LeftHitOn)
	{
		m_LeftHitOn = false;
		AddWorldPositionX(5.f);
	}

	if (m_Alive && m_RightHitOn)
	{
		m_RightHitOn = false;
		AddWorldPositionX(-5.f);
	}

	if (m_Alive && m_Move.x > 0.f && !m_SkillAttackOn)
	{
		m_Animation->ChangeAnimation("SkelegonMove");
		m_MainSprite->SetReverseX(true);
	}

	else if (m_Alive && m_Move.x < 0.f && !m_SkillAttackOn)
	{
		m_Animation->ChangeAnimation("SkelegonMove");
		m_MainSprite->SetReverseX(false);
	}

	else if (m_Alive && m_Move.x == 0.f && !m_SkillAttackOn)
	{
		m_Animation->ChangeAnimation("SkelegonStand");	
		//m_MainSprite->SetReverseX(!m_MainSprite->GetReverseX());
	}

	if (!m_AttackSectionOn && m_MoveLeft || m_MoveRight)
	{
		m_MovingTime += DeltaTime;
		if (m_MovingTime > 3.5f)
		{
			m_MoveLeft = false;
			m_MoveRight = false;
			m_MovingTime = 0.f;
		}
	}

	CCameraComponent* Camera = CSceneManager::GetInst()->GetScene()->GetCameraManager()->GetCurrentCamera();

	if (m_Hpbar)
	{
		Vector2 WorldPos = GetWorldPos();
		Vector2 CameraWorldPos = Camera->GetWorldPos();
		Vector2 RealPos = WorldPos - CameraWorldPos;

		m_Hpbar->SetUIPos(RealPos);
		m_Hpbar->SetValue((float)m_Hp);
		m_NameText->SetPos(Vector2(RealPos.x - 15.f, RealPos.y - 80.f));
	}


	if (m_Hit)
	{
		m_HitTime += DeltaTime;

		if (m_HitTime > 1.f)
		{
			m_Hit = false;

			if(m_Alive && !m_SkillAttackOn)
			m_Animation->ChangeAnimation("SkelegonStand");

			m_HitTime = 0.f;
		}
	}

	if (m_Alive && m_Hp <= 0)
	{
		m_Alive = false;
		m_HitBox->SetCollisionProfile("Die");
		m_Animation->ChangeAnimation("SkelegonDie");
		m_Scene->GetResource()->SoundPlay("SkelegonDie");
		//m_MainSprite->SetReverseX(m_MainSprite->GetReverseX());
	}

}

CSkelegon* CSkelegon::Clone() const
{
	return new CSkelegon(*this);
}

void CSkelegon::CollisionSectionCheck(const CollisionResult& result)
{

	m_AttackSectionOn = true;
}

void CSkelegon::CollisionSectionCheckOff(const CollisionResult& result)
{

	m_AttackSectionOn = false;

}

void CSkelegon::HitBoxCollision(const CollisionResult& result)
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
				//m_MainSprite->SetReverseX(true);
				Effect->SetRelativePosition(Pos.x + 50.f, Pos.y + 20.f);

				if(!m_SkillAttackOn)
				m_Animation->ChangeAnimation("SkelegonHit");
		
			}

			else
			{
				//m_MainSprite->SetReverseX(false);
				Effect->SetRelativePosition(Pos.x - 50.f, Pos.y + 20.f);		

				if(!m_SkillAttackOn)
				m_Animation->ChangeAnimation("SkelegonHit");
			}
		}

		if (BulletName == "SpeedDuelShotBullet")
		{
			CHitEffect* Effect = m_Scene->CreateObject<CHitEffect>("HitEffect");
			Effect->SetAnimation("SpeedDualShotHit");

			if (m_HitBox->GetWorldPos().x < result.Dest->GetWorldPos().x)
			{
				//m_MainSprite->SetReverseX(true);
				Effect->SetRelativePosition(Pos.x + 50.f, Pos.y + 20.f);
				m_RightHitOn = true;

				if(!m_SkillAttackOn)
				m_Animation->ChangeAnimation("SkelegonHit");
			}

			else
			{
				//m_MainSprite->SetReverseX(false);
				Effect->SetRelativePosition(Pos.x - 50.f, Pos.y + 20.f);
				m_LeftHitOn = true;

				if(!m_SkillAttackOn)
				m_Animation->ChangeAnimation("SkelegonHit");
			}
		}

		if (BulletName == "Ring_Arrow")
		{
			CHitEffect* Effect = m_Scene->CreateObject<CHitEffect>("HitEffect");
			Effect->SetAnimation("Ring_Effect");

			if (m_HitBox->GetWorldPos().x < result.Dest->GetWorldPos().x)
			{
				//m_MainSprite->SetReverseX(false);
				Effect->SetRelativePosition(Pos.x + 50.f, Pos.y + 20.f);
				m_RightHitOn = true;
				m_MainSprite->SetReverseX(true);

				if(!m_SkillAttackOn)
				m_Animation->ChangeAnimation("SkelegonHit");
			}
			else
			{
				//m_MainSprite->SetReverseX(true);
				Effect->SetRelativePosition(Pos.x - 50.f, Pos.y + 20.f);
				m_LeftHitOn = true;

				if(!m_SkillAttackOn)
				m_Animation->ChangeAnimation("SkelegonHit");
			}
		}


		m_Hpbar->SetEnable(true);
		m_NameText->SetEnable(true);
		m_Hp -= Damage;
	}

	

}

void CSkelegon::SkelegonSkillAttack()
{
	if (m_Hp > 0)
	{
		if (!m_SkillAttackOn && m_AttackSectionOn && m_Active)
		{
			m_SkillAttackOn = true;
			m_Animation->ChangeAnimation("SkelegonAttack");
			m_Scene->GetResource()->SoundPlay("SkelegonAttack");
		}
	}
}

void CSkelegon::SkelegonSkillNotify()
{
	HonTailHitEffect* HitEffect = m_Scene->CreateObject<HonTailHitEffect>("HonTailHitEffect");
	HitEffect->SetWorldPosition(m_Player->GetWorldPos().x - 20.f, m_Player->GetWorldPos().y + 30.f);
	HitEffect->SetAnimation("SkelegonHitEffect");
	HitEffect->SetCollisionProfile("JungSY");
}

void CSkelegon::SkelegonSkillBuff()
{
	if (m_Hp > 0)
	{
		if (!m_SkillAttackOn && m_AttackSectionOn && m_Alive)
		{
			m_SkillAttackOn = true;
			m_Animation->ChangeAnimation("SkelegonBuff");

			m_Damage += 100;
		}
	}
}

void CSkelegon::SkelegonDie()
{
	m_MainUI->SetExp(m_Exp);	

	m_Hpbar->SetEnable(false);
   	m_NameText->SetEnable(false);


	int Number = CEngine::GetInst()->GetNumber();

	CRespawn* Respawn = m_Scene->CreateObject<CRespawn>("Respawn");
	Respawn->SetRespawn(true, Vector2((float)Number * 10, 250.f), "Skelegon");

	CTimerManager::GetInst()->DestroyInst();


	Destroy();
}

void CSkelegon::SkelegonHit()
{
	if (m_Alive)
	{
		m_Animation->ChangeAnimation("SkelegonStand");
	}
}


void CSkelegon::AnimationEndFunc()
{
	m_SkillAttackOn = false;

	if (m_Alive)
		m_Animation->ChangeAnimation("SkelegonStand");
}

void CSkelegon::SkelegonMoveLeft(float DeltaTime)
{
	AddWorldPositionX(-100.f * DeltaTime);
}

void CSkelegon::SkelegonMoveRight(float DeltaTime)
{
	AddWorldPositionX(100.f * DeltaTime);
}

void CSkelegon::SkelegonSectionCheck()
{
	if (m_Alive && m_AttackSectionOn)
	{				
		if (m_Player->GetWorldPos().x > GetWorldPos().x)
		{
			m_MoveRight = true;
		}

		else
		{
			m_MoveLeft = true;
		}
	}
}

void CSkelegon::RandomMoveCheck()
{
	if (!m_MoveLeft && !m_MoveRight && !m_SkillAttackOn && !m_AttackSectionOn)
	{
		int RandomCount = CEngine::GetInst()->GetNumber();

		if (RandomCount > 50)
			m_RandomLeft = true;

		else
			m_RandomRight = true;
	}

}
