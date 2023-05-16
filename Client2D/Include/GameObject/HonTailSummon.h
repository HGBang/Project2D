#pragma once
#include "GameObject\GameObject.h"

class CHonTailSummon :
    public CGameObject
{
	friend class CScene;

protected:
	CHonTailSummon();
	CHonTailSummon(const CHonTailSummon& Obj);
	virtual ~CHonTailSummon();

private:
	CSharedPtr<class CColliderBox2D>	m_Body;
	CSharedPtr<class CSpriteComponent>	m_MainSprite;
	int DeadCount;


public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CHonTailSummon* Clone() const;

private:
	void HonTailSummonCallBack(const CollisionResult& result);
};

