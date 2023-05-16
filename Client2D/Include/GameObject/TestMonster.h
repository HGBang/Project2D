#pragma once
#include "GameObject\GameObject.h"

class CTestMonster :
    public CGameObject
{
	friend class CScene;

protected:
	CTestMonster();
	CTestMonster(const CTestMonster& Obj);
	virtual ~CTestMonster();

private:
	CSharedPtr<class CSpriteComponent>	m_Sprite;
	CSharedPtr<class CSpriteComponent>	m_SpriteChild;
	CSharedPtr<class CColliderSphere2D>	m_Body;
	class CAnimation2D* m_Animation;
	class CAnimation2D* m_HitAnimation;

	class CMonsterBarUI* m_MonsterBarUI;
	class CUIProgressBar* m_Hpbar;
	class CUIText* m_NameText;
	class CStartSceneUI* m_MainUI;

	float	m_NamePosX;
	float	m_NamePosY;

	int m_MaxHp;
	int m_Hp;
	int m_Exp;

	bool m_Hit;
	bool m_Alive;
	bool m_DieSound;

	float m_HitTime;

	

public:
	virtual void Start();
	virtual bool Init();
	virtual void Destroy();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CTestMonster* Clone()    const;

public:
	void CollisionMonster(const CollisionResult& result);
	bool GetHit()
	{
		return m_Hit;
	}

	bool GetAlive()
	{
		return m_Alive;
	}

private:
	void DieFunc();


};

