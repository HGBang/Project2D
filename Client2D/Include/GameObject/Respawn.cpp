#include "Respawn.h"
#include "Scene/Scene.h"
#include "Scene/SceneManager.h"
#include "Skelegon.h"
#include "DarkWybern.h"

CRespawn::CRespawn()
{
	SetTypeID<CRespawn>();
	m_ObjectTypeName = "Respawn";
}

CRespawn::CRespawn(const CRespawn& Obj) :
	CGameObject(Obj)
{
}

CRespawn::~CRespawn()
{
}

void CRespawn::Start()
{
	CGameObject::Start();
}

bool CRespawn::Init()
{
	return true;
}

void CRespawn::Destory()
{
	CGameObject::Destroy();
}

void CRespawn::Save(FILE* File)
{
}

void CRespawn::Load(FILE* File)
{
}

void CRespawn::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	if (m_RespawnOn)
	{
		m_RespawnTime += DeltaTime;

		if (m_RespawnTime > 4.f)
		{
			

			if (m_MonsterName == "Skelegon")
			{
				m_RespawnOn = false;
				m_RespawnTime = 0.f;

				MonsterRespawnSkelegon();
			
			}


			if (m_MonsterName == "DarkWybern")
			{

				m_RespawnOn = false;
				m_RespawnTime = 0.f;
				MonsterRespawnDarkWybern();
			
			}


		}

	}
}

void CRespawn::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CRespawn* CRespawn::Clone() const
{
	return new CRespawn(*this);
}

void CRespawn::SetRespawn(bool Respawn, Vector2 MonsterPos, const std::string& Name)
{
	m_RespawnOn = Respawn;
	m_MonsterPos = MonsterPos;
	m_MonsterName = Name;
}

void CRespawn::MonsterRespawnDarkWybern()
{
	CDarkWybern* DarkWybern = m_Scene->CreateObject<CDarkWybern>("DarkWybern");
	DarkWybern->SetWorldPosition(m_MonsterPos);
}

void CRespawn::MonsterRespawnSkelegon()
{
	CSkelegon* Skelegon = m_Scene->CreateObject<CSkelegon>("Skelegon");
	Skelegon->SetWorldPosition(m_MonsterPos);
}
