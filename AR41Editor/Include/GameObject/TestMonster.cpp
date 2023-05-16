#include "TestMonster.h"
#include "Component/SpriteComponent.h"
#include "Input.h"
#include "Device.h"
#include "Scene/SceneManager.h"
#include "Scene/Scene.h"
#include "Component/TargetArm.h"
#include "Component/ColliderBox2D.h"
#include "Component/ColliderSphere2D.h"
#include "Component/ColliderOBB2D.h"
#include "Scene/CameraManager.h"
#include "Component/CameraComponent.h"
#include "Scene/Scene.h"
#include "Resource/Material/Material.h"
#include "Animation/Animation2D.h"
#include "HitEffect.h"
#include "Bullet.h"
#include "Player2D.h"
#include "../UI/MonsterBarUI.h"
#include "UI/UIProgressBar.h"
#include "UI/UIText.h"
#include "../UI/StartSceneUI.h"


CTestMonster::CTestMonster() :
	m_Hp(100),
	m_Exp(10)
{
	SetTypeID<CTestMonster>();

	m_ObjectTypeName = "TestMonster";
}

CTestMonster::CTestMonster(const CTestMonster& Obj) :
	CGameObject(Obj)
{
	m_Sprite = (CSpriteComponent*)FindComponent("Sprite");
	m_Body = (CColliderSphere2D*)FindComponent("Body");
	m_SpriteChild = (CSpriteComponent*)FindComponent("SpriteChild");
}

CTestMonster::~CTestMonster()
{
	
}

void CTestMonster::Start()
{
	CGameObject::Start();

	CSceneManager::GetInst()->GetScene()->GetResource()->LoadSound("Effect", "MushmomDie", false, "MushmomDie.mp3");

	m_Animation = m_Sprite->SetAnimation<CAnimation2D>("MushmomWalk");
	m_Animation->AddAnimation("MushmomWalk", "MushmomWalk");
	m_Animation->SetLoop("MushmomWalk", true);
	m_Animation->SetPlayTime("MushmomWalk", 1.f);

	m_Animation->AddAnimation("MushmomHit", "MushmomHit");
	m_Animation->AddAnimation("MushmomDie", "MushmomDie");

	m_Animation->SetCurrentAnimation("MushmomWalk");
	m_Animation->SetCurrentEndFunction("MushmomDie", this, &CTestMonster::DieFunc);
	m_Animation->SetPlayTime("MushmomDie", 0.5f);

	m_Body->SetCollisionCallback<CTestMonster>(ECollision_Result::Collision, this, &CTestMonster::CollisionMonster);

	if (m_Scene)
		m_MonsterBarUI = m_Scene->GetViewport()->FindUIWindow<CMonsterBarUI>("MonsterBarUI");

	else
		m_MonsterBarUI = CSceneManager::GetInst()->GetScene()->GetViewport()->FindUIWindow<CMonsterBarUI>("MonsterBarUI");

	if (m_Scene)
		m_MainUI = m_Scene->GetViewport()->FindUIWindow<CStartSceneUI>("StartSceneUI");

	else
		m_MainUI = CSceneManager::GetInst()->GetScene()->GetViewport()->FindUIWindow<CStartSceneUI>("StartSceneUI");

	m_Hp = 100;
	m_Alive = true;
	m_Exp = 100;

	m_Hpbar = m_MonsterBarUI->GetProGressBar(m_Hp, GetWorldPos());

	m_NameText = m_MonsterBarUI->GetMonsterNameTag(TEXT("¸Ó½¬¸¾"), Vector2(GetWorldPos()));



	
}

bool CTestMonster::Init()
{
	CGameObject::Init();

	m_Body = CreateComponent<CColliderSphere2D>("Body");
	m_Sprite = CreateComponent<CSpriteComponent>("Sprite");
	m_SpriteChild = CreateComponent<CSpriteComponent>("SpriteChild");

	SetRootComponent(m_Body);

	m_Body->AddChild(m_Sprite);
	m_Body->SetWorldPosition(400.f, 500.f);
	m_Body->SetCollisionProfile("Monster");

	m_Sprite->SetPivot(0.5f, 0.f);
	m_Sprite->SetRelativeScale(100.f, 100.f);
	m_Sprite->SetRelativePosition(0.f, -50.f);

	m_Sprite->AddChild(m_SpriteChild);

	m_SpriteChild->SetPivot(0.5f, 0.f);
	m_SpriteChild->SetRelativeScale(100.f, 100.f);
	m_SpriteChild->SetRelativePosition(0.f, -50.f);
	m_SpriteChild->GetMaterial(0)->SetOpacity(0.f);	




	return true;
}

void CTestMonster::Destroy()
{
	CGameObject::Destroy();
}

void CTestMonster::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	float ImageWidth, ImageHeight;
	int Count = m_Animation->GetCurrentFrame(m_Animation->GetCurrentAnimName());
	ImageWidth = (float)(m_Animation->GetCurrentAnimationSequence(m_Animation->GetCurrentAnimName())->GetTexture()->GetWidth(Count));
	ImageHeight = (float)(m_Animation->GetCurrentAnimationSequence(m_Animation->GetCurrentAnimName())->GetTexture()->GetHeight(Count));

	m_Sprite->SetRelativeScale(ImageWidth, ImageHeight);

	//m_Sprite->AddRelativeRotationZ(180.f * DeltaTime);

	if (m_Hit)
	{
		m_HitTime += DeltaTime;

		if (m_HitTime > 1.f)
		{
			m_Hit = false;
			m_Animation->ChangeAnimation("MushmomWalk");			
			m_HitTime = 0.f;
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
		m_NameText->SetPos(Vector2(RealPos.x -15.f, RealPos.y -80.f));
	}

	if (m_Alive && m_Hp <= 0)
	{
		m_Alive = false;
		m_DieSound = true;
		m_Animation->ChangeAnimation("MushmomDie");
	}

	if (m_DieSound)
	{
		m_Scene->GetResource()->SoundPlay("MushmomDie");
		m_DieSound = false;
	}
	
	//m_Body->AddWorldPositionX(50.f * DeltaTime);

}


void CTestMonster::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CTestMonster* CTestMonster::Clone() const
{
	return new CTestMonster(*this);
}

void CTestMonster::CollisionMonster(const CollisionResult& result)
{
	if (m_Hp > 0)
	{
		CBullet* Bullet = (CBullet*)result.Dest->GetOwner();
		int Damage = Bullet->GetDamage();

		m_Hit = true;

		m_Animation->ChangeAnimation("MushmomHit");
		
		std::string BulletName = Bullet->GetAnimationName();

		Vector3 Pos = GetWorldPos();

		if (BulletName == "NormalAttack")
		{
			CHitEffect* Effect = m_Scene->CreateObject<CHitEffect>("HitEffect");
			Effect->SetAnimation("NormalAttackHit");

			if (m_Sprite->GetWorldPos().x < result.Dest->GetWorldPos().x)
			{
				m_Sprite->SetReverseX(true);
				Effect->SetRelativePosition(Pos.x + 50.f, Pos.y + 20.f);
			}

			else
			{
				m_Sprite->SetReverseX(false);
				Effect->SetRelativePosition(Pos.x - 50.f, Pos.y + 20.f);
			}
		}

		if (BulletName == "SpeedDuelShotBullet")
		{
			CHitEffect* Effect = m_Scene->CreateObject<CHitEffect>("HitEffect");
			Effect->SetAnimation("SpeedDualShotHit");

			if (m_Sprite->GetWorldPos().x < result.Dest->GetWorldPos().x)
			{
				m_Sprite->SetReverseX(true);
				Effect->SetRelativePosition(Pos.x + 50.f, Pos.y + 20.f);
			}

			else
			{
				m_Sprite->SetReverseX(false);
				Effect->SetRelativePosition(Pos.x - 50.f, Pos.y + 20.f);
			}
		}

		if (BulletName == "Ring_Arrow")
		{
			CHitEffect* Effect = m_Scene->CreateObject<CHitEffect>("HitEffect");
			Effect->SetAnimation("Ring_Effect");

			if (m_Sprite->GetWorldPos().x < result.Dest->GetWorldPos().x)
			{
				m_Sprite->SetReverseX(true);
				Effect->SetRelativePosition(Pos.x + 50.f, Pos.y + 20.f);
			}
			else
			{
				m_Sprite->SetReverseX(false);
				Effect->SetRelativePosition(Pos.x - 50.f, Pos.y + 20.f);
			}
		}
		

		m_Hpbar->SetEnable(true);
		m_NameText->SetEnable(true);
		m_Hp -= Damage;
	}
}

void CTestMonster::DieFunc()
{

	Destroy();
	m_Hpbar->SetEnable(false);
	m_NameText->SetEnable(false);
	CPlayer2D* Player = (CPlayer2D*)m_Scene->FindObject("Player2D");
	Player->AddFrontMonsterCount(1);
	m_MainUI->SetExp(m_Exp);

}
