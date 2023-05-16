
#include "Bullet.h"
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
#include "Scene/SceneManager.h"
#include "Animation/Animation2D.h"
#include "../UI/StartSceneUI.h"
#include "TestMonster.h"
#include "HonTail.h"

#include "Engine.h"
#include <time.h>



CBullet::CBullet()
{
	SetTypeID<CBullet>();

	m_ObjectTypeName = "Bullet";
}

CBullet::CBullet(const CBullet& Obj) :
	CGameObject(Obj)
{
}

CBullet::~CBullet()
{	
}

void CBullet::SetCollisionProfileName(const std::string& Name)
{
	m_Body->SetCollisionProfile(Name);
}

void CBullet::Start()
{
	CGameObject::Start();

	m_Animation = m_Sprite->SetAnimation<CAnimation2D>("Ring_Arrow");
 	m_Animation->AddAnimation("Ring_Arrow", "Ring_Arrow");
	m_Animation->AddAnimation("NormalAttack", "NormalAttack");
	m_Animation->AddAnimation("SpeedDuelShotBullet", "SpeedDuelShotBullet");

	m_Animation->SetLoop("NormalAttack", true);
	m_Animation->SetPlayTime("NormalAttack", 0.1f);

	m_Animation->SetLoop("Ring_Arrow", true);
	m_Animation->SetPlayTime("Ring_Arrow", 0.1f);

	m_Animation->SetLoop("SpeedDuelShotBullet", true);
	m_Animation->SetPlayTime("SpeedDuelShotBullet", 0.1f);


	m_Body->SetCollisionCallback<CBullet>(ECollision_Result::Collision, this, &CBullet::CollisionBullet);

	
}

bool CBullet::Init()
{
	CGameObject::Init();

	m_Body = CreateComponent<CColliderSphere2D>("BulletBody");
	m_Sprite = CreateComponent<CSpriteComponent>("BulletSprite");

	m_Distance = 1.f;

	m_Body->AddChild(m_Sprite);
	m_Body->SetRadius(0.f);

	m_Sprite->SetPivot(0.5f, 0.5f);

	//m_Sprite->SetRelativeScale(75.f, 20.f);	




	if (m_Scene)
		m_MainUI = m_Scene->GetViewport()->FindUIWindow<CStartSceneUI>("StartSceneUI");

	else
		m_MainUI = CSceneManager::GetInst()->GetScene()->GetViewport()->FindUIWindow<CStartSceneUI>("StartSceneUI");
		
	
	m_Dir = 700.f;

	return true;
}

void CBullet::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	AddWorldPosition(GetWorldAxis(AXIS_X) * m_Dir * DeltaTime);

	m_Distance -= DeltaTime;

	if (m_Distance < 0.f)
	{
		Destroy();
	}


	if (m_Animation)
	{
		float ImageWidth, ImageHeight;
		int Count = m_Animation->GetCurrentFrame(m_Animation->GetCurrentAnimName());
		ImageWidth = (float)(m_Animation->GetCurrentAnimationSequence(m_Animation->GetCurrentAnimName())->GetTexture()->GetWidth(Count));
		ImageHeight = (float)(m_Animation->GetCurrentAnimationSequence(m_Animation->GetCurrentAnimName())->GetTexture()->GetHeight(Count));

		m_Sprite->SetRelativeScale(ImageWidth, ImageHeight);
	}



	


}

void CBullet::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CBullet* CBullet::Clone() const
{
	return new CBullet(*this);
}

void CBullet::SetDir(float Dir)
{
	m_Dir = Dir;
}

void CBullet::SetAnimation(const std::string& Name)
{
	m_Animation->ChangeAnimation(Name);
}

void CBullet::SetReverseX(bool Reverse)
{
	m_Sprite->SetReverseX(Reverse);
}

const std::string& CBullet::GetAnimationName()
{
	return m_Animation->GetCurrentAnimName();
}

void CBullet::CollisionBullet(const CollisionResult& result)
{


	CTestMonster* Monster = (CTestMonster*)result.Dest->GetOwner();
	CHonTail* HonTail = (CHonTail*)result.Dest->GetOwner();

	if (result.Dest->GetOwner()->GetName() == "TestMonster")
	{
		if (Monster->GetAlive())
		{
			Vector2 BulletPos = GetWorldPos();

			m_MainUI->SetDamageNumber(BulletPos, m_Damage);

			Destroy();
		}
	}

	if (result.Dest->GetOwner()->GetName() == "HonTail")
	{
			Vector2 BulletPos = GetWorldPos();

			if (CEngine::GetInst()->GetNumber() < 20)
			{
				m_Damage = m_Damage * 2;

       			m_MainUI->SetCriticalDamageNumber(BulletPos, m_Damage);

				Destroy();
			}

			else
			{
				m_MainUI->SetDamageNumber(BulletPos, m_Damage);
				Destroy();
			}				
	}

	if (result.Dest->GetOwner()->GetName() == "Skelegon")
	{
		Vector2 BulletPos = GetWorldPos();

		if (CEngine::GetInst()->GetNumber() < 20)
		{
			m_Damage = m_Damage * 2;

			m_MainUI->SetCriticalDamageNumber(BulletPos, m_Damage);

			Destroy();
		}

		else
		{
			m_MainUI->SetDamageNumber(BulletPos, m_Damage);

			Destroy();
		}
	}

	if (result.Dest->GetOwner()->GetName() == "DarkWybern")
	{
		Vector2 BulletPos = GetWorldPos();

		if (CEngine::GetInst()->GetNumber() < 20)
		{
			m_Damage = m_Damage * 2;

			m_MainUI->SetCriticalDamageNumber(Vector2(BulletPos.x,BulletPos.y + 30.f), m_Damage);

			Destroy();		
		}

		else
		{
			m_MainUI->SetDamageNumber(Vector2(BulletPos.x, BulletPos.y + 30.f), m_Damage);
			
			Destroy();
		}
	}



}
