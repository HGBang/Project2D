#pragma once
#include "GameObject\GameObject.h"
class HonTailHitEffect :
    public CGameObject
{
	friend class CScene;

protected:
	HonTailHitEffect();
	HonTailHitEffect(const HonTailHitEffect& Obj);
	virtual ~HonTailHitEffect();

private:
	CSharedPtr<class CSpriteComponent>	m_HonTailHitEffectSprite;
	CSharedPtr<class CColliderBox2D> m_HonTailHitCollider;
	class CAnimation2D* m_HitEffectAnimation;
	int		m_Damage;
	int		m_MpDamage;
	int		m_RandomDamage;
	class CPlayer2D* m_Player;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual HonTailHitEffect* Clone()    const;

public:
	void SetAnimation(const std::string& Name);
	void SetCollisionProfile(const std::string& Name);
	const std::string GetCurrentAnimName();



private:
	void Destory();
	void EffectEndFuc();
	void EffectNotify();

public:
	int GetHitDamage()
	{
		return m_Damage;
	}

	int GetHitMpDamage()

	{
		return m_MpDamage;
	}
};

