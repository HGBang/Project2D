#pragma once
#include "GameObject\GameObject.h"

class CHonTail :
    public CGameObject
{
	friend class CScene;

protected:
	unsigned int TimerNumber;

	class CPlayer2D* m_Player;
	class CStartSceneUI* m_StartSceneUI;

	CSharedPtr<class CColliderBox2D> m_BottomMainHeadCollider;
	CSharedPtr<class CColliderBox2D> m_LeftCollider;
	CSharedPtr<class CColliderBox2D> m_RightCollider;
	CSharedPtr<class CColliderBox2D> m_LeftLegCollider;
	CSharedPtr<class CColliderBox2D> m_RightLegCollider;
	CSharedPtr<class CColliderBox2D> m_TailCollider;

	CSharedPtr<class CSpriteComponent>	m_MainHeadSprite;
	CSharedPtr<class CColliderBox2D>	m_MainHeadHitBox;
	class CAnimation2D* m_MainHeadAnimation;	
	class CAnimation2DData* m_MainHeadNotify;

	CSharedPtr<class CSpriteComponent>	m_RightHeadSprite;
	CSharedPtr<class CColliderBox2D>	m_RightHeadHitBox;
	class CAnimation2D* m_RightHeadAnimation;
	class CAnimation2DData* m_RightHeadNotify;

	CSharedPtr<class CSpriteComponent>	m_LeftHeadSprite;
	CSharedPtr<class CColliderBox2D>	m_LeftHeadHitBox;
	class CAnimation2D* m_LeftHeadAnimation;	
	class CAnimation2DData* m_LeftHeadNotify;

	CSharedPtr<class CSpriteComponent>	m_WingSprite;
	CSharedPtr<class CColliderBox2D>	m_WingHitBox;
	class CAnimation2D* m_WingAnimation;
	class CAnimation2DData* m_WingNotify;

	CSharedPtr<class CSpriteComponent>	m_RightHandSprite;
	CSharedPtr<class CColliderBox2D>	m_RightHandHitBox;
	class CAnimation2D* m_RightHandAnimation;

	CSharedPtr<class CSpriteComponent>	m_LeftHandSprite;
	CSharedPtr<class CColliderBox2D>	m_LeftHandHitBox;
	class CAnimation2D* m_LeftHandAnimation;

	CSharedPtr<class CSpriteComponent>	m_LegSprite;
	CSharedPtr<class CColliderBox2D>	m_LegHitBox;
	class CAnimation2D* m_LegAnimation;
	CAnimation2DData* m_LegNotify;

	CSharedPtr<class CSpriteComponent>	m_TailSprite;
	CSharedPtr<class CColliderBox2D>	m_TailHitBox;
	class CAnimation2D* m_TailAnimation;
	class CAnimation2DData* m_TailNotify;

	CSharedPtr<class CSpriteComponent> m_DieSprite;
	class CAnimation2D* m_DieAnimation;

	//섹션별 충돌여부 확인 변수
	bool m_LeftSectionCollision;
	bool m_RightSectionCollision;
	bool m_BottomSectionCollision;
	bool m_LeftLegSectionCollision;
	bool m_RightLegSectionCollision;

	//부위별 공격 또는 스킬 여부 확인 변수 

	bool HonTail_MainHeadAttack;
	bool HonTail_MainHeadSkill;
	bool HonTail_MainHeadEx;

	bool HonTail_LeftHeadAttack;
	bool HonTail_LeftHeadSkill;

	bool HonTail_RightHeadAttack;
	bool HonTail_RightHeadSkill;

	bool HonTail_HandAttack;
	bool HonTail_HandSkill;

	bool HonTail_LegAttack;

	bool HonTail_WingAttack;

	bool HonTail_TailAttack;
	bool HonTail_TailSkill;

	// 혼테일 HP
	int HonTail_MaxHp;
	int HonTail_Hp;
	int HonTail_MainHeadHp;
	int HonTail_LeftHeadHp;
	int HonTail_RightHeadHp;
	int HonTail_LeftHandHp;
	int HonTail_RightHandHp;
	int HonTail_WingHp;
	int HonTail_TailHp;
	int HonTail_LegHp;

	// 혼테일 부위별 격파 여부
	bool HonTailDie;
	bool MainHeadDie;
	bool MainHeadAttackOn; // 메인헤드 공격가능여부 ( 메인헤드는 맨마지막에 격파가능 )
	bool RightHeadDie;
	bool LeftHeadDie;
	bool RightHandDie;
	bool LeftHandDie;
	bool TailDie;
	bool LegDie;
	bool WingDie;

	bool m_HonTailStart;


	float TestTime;

	float StartColor;
	
	bool m_Start;

protected:
	CHonTail();
	CHonTail(const CHonTail& Obj);
	virtual ~CHonTail();

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CHonTail* Clone()    const;

public:
	int GetHonTailMaxHp()
	{
		return HonTail_MaxHp;
	}

	int GetHonTailHp()
	{
		return HonTail_Hp;
	}

	

private:
	void HonTailMainHeadUpdate();
	void HonTailRightHeadUpdate();
	void HonTailLeftHeadUpdate();
	void HonTailRightHandHeadUpdate();
	void HonTailLeftHandUpdate();
	void HonTailLegUpdate();
	void HonTailWingUpdate();
	void HonTailTailUpdate();
	void HonTailDieAnimation();


	

private:
	void HonTailAttackStartFunc();
	void HonTailAttackEndFunc();
	void HonTailTailCollision(const CollisionResult& result);
	void HonTailBottomCollisionFunc(const CollisionResult& result);
	void HonTailLeftCollisionFunc(const CollisionResult& result);
	void HonTailRightCollisionFunc(const CollisionResult& result);
	void HonTailLeftLegCollisionFunc(const CollisionResult& result);
	void HonTailRightLegCollisionFunc(const CollisionResult& result);

	void HonTailBottomReleaseFunc(const CollisionResult& result);
	void HonTailLeftReleaseFunc(const CollisionResult& result);
	void HonTailRightReleaseFunc(const CollisionResult& result);
	void HonTailLeftLegReleaseFunc(const CollisionResult& result);
	void HonTailRightLegReleaseFunc(const CollisionResult& result);

private:
	void HonTailMainHeadExNotify();
	void HonTailMainHeadNotify();
	void HonTailLeftHeadNotify();
	void HonTailRightHeadNotify();
	void HonTailLegNotify();
	void HonTailWingNotify();
	void HonTailTailNotify();



private:
	void HonTailMainHeadEx();
	void HonTailMainHeadAttack();
	void HonTailMainHeadSkill();
	void HonTailLeftHeadAttack();
	void HonTailLeftHeadSkill();
	void HonTailRightHeadAttack();
	void HonTailRightHeadSkill();
	void HonTailLeftHandAttack();
	void HonTailLeftHandSkill();
	void HonTailRightHandAttack();
	void HonTailRightHandSkill();
	void HonTailRightLegAttack();
	void HonTailLeftLegAttack();
	void HonTailTailAttack();
	void HonTailTailSkill();
	void HonTailWingAttack();

private:
	void HonTailMainHeadStartFunc();
	void HonTailMainHeadEndFunc();

	void HonTailRightHeadStartFunc();
	void HonTailRightHeadEndFunc();

	void HonTailLeftHeadStartFunc();
	void HonTailLeftHeadEndFunc();

	void HonTailRightHandStartFunc();
	void HonTailRightHandEndFunc();

	void HonTailLeftHandStartFunc();
	void HonTailLeftHandEndFunc();

	void HonTailLegStartFunc();
	void HonTailLegEndFunc();

	void HonTailTailStartFunc();
	void HonTailTailEndFunc();

	void HonTailWingStartFunc();
	void HonTailWingEndFunc();

private:
	void WingHitBox(const CollisionResult& result);
	void LegHitBox(const CollisionResult& result);
	void LeftHandHitBox(const CollisionResult& result);
	void RightHandHitBox(const CollisionResult& result);
	void LeftHeadHitBox(const CollisionResult& result);
	void RightHeadHitBox(const CollisionResult& result);
	void MainHeadHitBox(const CollisionResult& result);

};

