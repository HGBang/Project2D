#pragma once
#include "GameObject/GameObject.h"

class CSkelegon :
    public CGameObject
{
	friend class CScene;

protected:
	CSkelegon();
	CSkelegon(const CSkelegon& Obj);
	virtual ~CSkelegon();

protected:
	unsigned int		m_TimerNumber;
	Vector3				m_PrevPos;
	Vector3				m_Move;
	Vector3				m_Pos;
	float				m_TestTime;
	bool				m_AttackSectionOn;
	float				m_MovingTime;
	bool				m_MoveLeft;
	bool				m_MoveRight;
	bool				m_SkillAttackOn;
	bool				m_Hit;
	float				m_HitTime;
	bool				m_Alive;
	bool				m_RandomRight;
	bool				m_RandomLeft;
	float				m_RandomTime;
	bool				m_RightHitOn;
	bool				m_LeftHitOn;

protected:
	int					m_Exp;
	int					m_MaxHp;
	int					m_Hp;
	int					m_Damage;

protected:
	CSharedPtr<class CSpriteComponent>	m_MainSprite;
	CSharedPtr<class CColliderBox2D>	m_HitBox;
	CSharedPtr<class CColliderBox2D>	m_SkillHitBox;
	class CAnimation2D*				    m_Animation;
	class CAnimation2DData*				m_SkelNotify;
	class CPlayer2D*					m_Player;

	class CMonsterBarUI* m_MonsterBarUI;
	class CUIProgressBar* m_Hpbar;
	class CUIText* m_NameText;
	class CStartSceneUI* m_MainUI;


public:
	virtual void Start();
	virtual bool Init();
	virtual void Save(FILE* File);
	virtual void Load(FILE* File);
	virtual void Destroy();
	virtual void FirstUpdate(float DeltaTime);
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CSkelegon* Clone()    const;

private:
	void CollisionSectionCheck(const CollisionResult& result);
	void CollisionSectionCheckOff(const CollisionResult& result);
	void HitBoxCollision(const CollisionResult& result);
	void SkelegonSkillAttack();
	void SkelegonSkillNotify();
	void SkelegonSkillBuff();
	void SkelegonDie();
	void SkelegonHit();
	

private:
	void AnimationEndFunc();
	void SkelegonMoveLeft(float DeltaTime);
	void SkelegonMoveRight(float DeltaTime);
	void SkelegonSectionCheck();
	void RandomMoveCheck();
};

