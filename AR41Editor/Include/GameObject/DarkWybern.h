#pragma once
#include "GameObject\GameObject.h"
class CDarkWybern :
    public CGameObject
{
	friend class CScene;

protected:
	CDarkWybern();
	CDarkWybern(const CDarkWybern& Obj);
	virtual ~CDarkWybern();

protected:
	CSharedPtr<class CSpriteComponent>	m_MainSprite;
	CSharedPtr<class CColliderBox2D>	m_HitBox;
	CSharedPtr<class CColliderBox2D>	m_SkillHitBox;
	class CAnimation2D*					m_Animation;
	class CPlayer2D*					m_Player;
	class CMonsterBarUI*				m_MonsterBarUI;
	class CUIProgressBar*				m_Hpbar;
	class CUIText*						m_NameText;
	class CStartSceneUI*				m_MainUI;

protected:
	Vector3				m_PrevPos;
	Vector3				m_Move;
	Vector3				m_Pos;
	float				m_TestTime;
	bool				m_AttackSectionOn;
	bool				m_AttackOn;
	float				m_AttackTime;
	bool				m_Hit;
	float				m_HitTime;
	bool				m_MoveLeft;
	bool				m_MoveRight;
	float				m_MoveTime;
	bool				m_RightHitOn;
	bool				m_LeftHitOn;
	bool				m_RandomMoveOn;
	float				m_RandomMoveTime;


	
		
protected:
	int			m_MaxHp;
	int			m_Hp;
	int			m_Exp;
	bool		m_Alive;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Save(FILE* File);
	virtual void Load(FILE* File);
	virtual void Destroy();
	virtual void FirstUpdate(float DeltaTime);
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CDarkWybern* Clone()    const;

private:
	void DarkWybernAttackEndFunc();
	void DarkWybernDieEndFunc();
	void DarkWybernHitEndFunc();
	void AttackSectionOnFunc(const CollisionResult& result);
	void AttackSectionOffFunc(const CollisionResult& result);
	void HitBoxCollisionFunc(const CollisionResult& result);
};

