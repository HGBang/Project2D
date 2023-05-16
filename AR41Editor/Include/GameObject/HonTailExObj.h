#pragma once
#include "GameObject\GameObject.h"
class CHonTailExObj :
    public CGameObject
{
	friend class CScene;

protected:
	CHonTailExObj();
	CHonTailExObj(const CHonTailExObj& Obj);
	virtual ~CHonTailExObj();

private:
	CSharedPtr<class CColliderBox2D>	m_HitBox;
	CSharedPtr<class CSpriteComponent>	m_MainSprite;
	class CAnimation2D* m_Animation;
	class CAnimation2DData* m_Notify;
	bool	m_CollisionOn;


public:
	virtual void Start();
	virtual bool Init();
	virtual void Destory();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CHonTailExObj* Clone() const;

private:
	void ExNotify();
	void CollisionOn(const CollisionResult& result);
	void CollisionOff(const CollisionResult& result);
	void AnimationEndFunc();

};

