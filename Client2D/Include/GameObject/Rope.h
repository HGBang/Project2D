#pragma once
#include "GameObject\GameObject.h"

class CRope :
    public CGameObject
{
	friend class CScene;

protected:
	CRope();
	CRope(const CRope& Obj);
	virtual ~CRope();

private:
	CSharedPtr<class CColliderBox2D>	m_Body;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Save(FILE* File);
	virtual void Load(FILE* File);
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CRope* Clone()    const;


};

