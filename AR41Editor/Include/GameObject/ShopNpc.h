#pragma once
#include "GameObject\GameObject.h"

class CShopNpc :
    public CGameObject
{
	friend class CScene;

protected:
	CShopNpc();
	CShopNpc(const CShopNpc& Obj);
	virtual ~CShopNpc();

private:
	class CShopUI* m_ShopUI;


private:
	CSharedPtr<class CSpriteComponent>	m_MainSprite;
	CSharedPtr<class CColliderBox2D>	m_Body;

	class CAnimation2D* m_Animation;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CShopNpc* Clone()    const;

private:
	void ShopMouseClick(const CollisionResult& result);
};

