#pragma once
#include "GameObject\GameObject.h"
class CRespawn :
    public CGameObject
{
	friend class CScene;

protected:
	CRespawn();
	CRespawn(const CRespawn& Obj);
	virtual ~CRespawn();

protected:
	float m_RespawnTime;
	bool  m_RespawnOn;
	Vector2 m_MonsterPos;
	std::string m_MonsterName;


public:
	virtual void Start();
	virtual bool Init();
	virtual void Destory();
	virtual void Save(FILE* File);
	virtual void Load(FILE* File);
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CRespawn* Clone()    const;

public:
	void SetRespawn(bool Respawn, Vector2 MonsterPos , const std::string& Name);
	void MonsterRespawnSkelegon();
	void MonsterRespawnDarkWybern();
};

