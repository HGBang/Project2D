#pragma once
#include "GameObject\GameObject.h"
class CHitEffect :
    public CGameObject
{
	friend class CScene;

protected:
	CHitEffect();
	CHitEffect(const CHitEffect& Obj);
	virtual ~CHitEffect();

private:
	CSharedPtr<class CSpriteComponent>	m_Sprite;
	class CAnimation2D* m_HitAnimation;


public:
	void SetCollisionProfileName(const std::string& Name);

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void Destory();
	virtual void PostUpdate(float DeltaTime);
	virtual CHitEffect* Clone()    const;


public:
	void SetAnimation(const std::string& Name);

private:
	void SoundPlay();


};

