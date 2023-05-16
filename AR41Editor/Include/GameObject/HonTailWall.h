#pragma once
#include "GameObject\GameObject.h"
class CHonTailWall :
    public CGameObject
{
	friend class CScene;

protected:
	CHonTailWall();
	CHonTailWall(const CHonTailWall& Obj);
	virtual ~CHonTailWall();

private:
	CSharedPtr<class CSpriteComponent>	m_MainSprite;


public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CHonTailWall* Clone() const;
};

