#pragma once
#include "GameObject\GameObject.h"
class CPortal :
    public CGameObject
{
	friend class CScene;

protected:
	CPortal();
	CPortal(const CPortal& Obj);
	virtual ~CPortal();

private:
	CSharedPtr<class CSpriteComponent>	m_MainSprite;
	CSharedPtr<class CColliderBox2D>	m_Body;

	bool			m_PortalMove;

	class CAnimation2D* m_Animation;

	std::string m_PortalName;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Save(FILE* File);
	virtual void Load(FILE* File);
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CPortal* Clone()    const;


public:
	const std::string GetPortalName() 
	{
		return m_PortalName;
	}

	void SetPortalName(const std::string& Name)
	{
		m_PortalName = Name;
	}


private:
	void PortalMove(const CollisionResult& result);
	void PortalMoveOff(const CollisionResult& result);
};

