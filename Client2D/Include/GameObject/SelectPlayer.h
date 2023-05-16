#pragma once
#include "GameObject\GameObject.h"
class CSelectPlayer :
    public CGameObject
{
	friend class CScene;

protected:
	CSelectPlayer();
	CSelectPlayer(const CSelectPlayer& Obj);
	virtual ~CSelectPlayer();

private:
	CSharedPtr<class CSpriteComponent>	m_Sprite;
	CSharedPtr<class CSpriteComponent>	m_Effect;
	CSharedPtr<class CColliderBox2D>	m_Body;
	class CAnimation2D* m_Animation;
	class CAnimation2D* m_EffectAnimation;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CSelectPlayer* Clone()    const;

public:
	void Save(FILE* File);
	void Load(FILE* File);

public:
};

