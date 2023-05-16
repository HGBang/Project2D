#pragma once
#include "GameObject\GameObject.h"

class CSkillEffect :
    public CGameObject
{
	friend class CScene;

protected:
	CSkillEffect();
	CSkillEffect(const CSkillEffect& Obj);
	virtual ~CSkillEffect();

private:
	CSharedPtr<class CSpriteComponent>	m_MainSprite;
	class CAnimation2D* m_Animation;


public:
	virtual void Start();
	virtual bool Init();
	virtual void Destory();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CSkillEffect* Clone() const;

public:
	void SetAnimation(const std::string& Name, float PlayTime = 1.0f, bool Loop = true);
	void SetReverseX(bool Reverse);

private:
	void SkillEffectStartFunc();
	void SkillEffectEndFunc();

};

