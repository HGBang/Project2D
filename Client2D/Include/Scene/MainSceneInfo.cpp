
#include "MainSceneInfo.h"
#include "Scene/Scene.h"
#include "../GameObject/Player2D.h"
#include "../Monster.h"
#include "../GameObject/TestMonster.h"


CMainSceneInfo::CMainSceneInfo()
{
}

CMainSceneInfo::~CMainSceneInfo()
{
}

bool CMainSceneInfo::Init()
{
	CSceneInfo::Init();
	
	CPlayer2D* Player = m_Owner->CreateObject<CPlayer2D>("Player2D");	

	SetPlayerObject(Player);

	CTestMonster* Monster = m_Owner->CreateObject<CTestMonster>("Monster");


	return true;
}
