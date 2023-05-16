#pragma once

#include "GameObject/GameObject.h"


class CTestPlayer2D :
	public CGameObject
{
	friend class CScene;

protected:
	CTestPlayer2D();
	CTestPlayer2D(const CTestPlayer2D& Obj);
	virtual ~CTestPlayer2D();

private:
	CSharedPtr<class CSpriteComponent>	m_Sprite;
	CSharedPtr<class CSpriteComponent>	m_SkillSprite;
	CSharedPtr<class CSceneComponent>	m_RightChild;
	CSharedPtr<class CSpriteComponent>	m_SpriteChild;
	CSharedPtr<class CCameraComponent>	m_Camera;
	CSharedPtr<class CTargetArm>		m_Arm;
	CSharedPtr<class CColliderBox2D>	m_Body;

	bool		m_TextureSize;

	Vector3		m_PrevPos;
	Vector3		m_Move;
	Vector3		m_PrevMove;
	Vector3		m_Pos;

	float		m_AttackTime;

	bool		m_Attack;
	bool		m_MoveOn;
	//bool		m_MoveLeftOn;

	bool		m_SkillOn;
	bool		m_Start1;

	float		m_SkillTime;

	class CAnimation2D* m_Animation;

	class CAnimation2D* m_SkillAnimation;

	bool		m_Weapon;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CTestPlayer2D* Clone()    const;



public:
	void MoveUp();
	void MoveDown();
	void MoveRight();
	void MoveLeft();
	void Fire();
	void FireEffect();

	void RightUp();
	void LeftUp();
	void FireUp();

};

