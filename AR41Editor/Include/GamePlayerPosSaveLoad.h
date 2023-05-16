#pragma once

#include "EngineInfo.h"

class CGamePlayerPosSaveLoad
{
protected:
	class CPlayer2D* m_Player;

	Vector2 m_PlayerPos;

public:
	void Save();
	void Load();

	DECLARE_SINGLE(CGamePlayerPosSaveLoad)
};

