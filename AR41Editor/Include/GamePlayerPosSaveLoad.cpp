#include "GamePlayerPosSaveLoad.h"
#include "PathManager.h"
#include "GameObject/Player2D.h"
#include "GameObject/GameObject.h"
#include "Scene/Scene.h"
#include "Scene/SceneManager.h"
#include "UI/EquipmentUI.h"
#include "UI/InventoryUI.h"

DEFINITION_SINGLE(CGamePlayerPosSaveLoad)

CGamePlayerPosSaveLoad::CGamePlayerPosSaveLoad()
{

}

CGamePlayerPosSaveLoad::~CGamePlayerPosSaveLoad()
{

}

void CGamePlayerPosSaveLoad::Save()
{
	m_Player = (CPlayer2D*)CSceneManager::GetInst()->GetScene()->FindObject("Player2D");

	m_PlayerPos = m_Player->GetWorldPos();
}

void CGamePlayerPosSaveLoad::Load()
{
	m_Player = (CPlayer2D*)CSceneManager::GetInst()->GetScene()->FindObject("Player2D");

	if (m_PlayerPos == Vector2(0.f, 0.f))
		m_Player->SetWorldPosition(500.f, 500.f);

	else
	m_Player->SetWorldPosition(m_PlayerPos.x, m_PlayerPos.y);
}
