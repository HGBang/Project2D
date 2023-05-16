#pragma once
#include "GameObject\GameObject.h"


class CBullet :
    public CGameObject
{
	friend class CScene;

protected:
	CBullet();
	CBullet(const CBullet& Obj);
	virtual ~CBullet();

private:
	CSharedPtr<class CSpriteComponent>	m_Sprite;
	CSharedPtr<class CColliderSphere2D>	m_Body;
	class CStartSceneUI* m_MainUI;
	class CAnimation2D* m_Animation;
	float	m_Dir;
	int m_Damage;
	unsigned int CriticalCount;

	float	m_Distance;

public:
	void SetCollisionProfileName(const std::string& Name);

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CBullet* Clone()    const;
	void SetDir(float Dir);
	void SetDamage(int Damage)
	{
		m_Damage = Damage;
	}

	int GetDamage() const
	{
		return m_Damage;
	}

public:
	void SetAnimation(const std::string& Name);
	void SetReverseX(bool Reverse);
	const std::string& GetAnimationName();



private:
	void CollisionBullet(const CollisionResult& result);
};

