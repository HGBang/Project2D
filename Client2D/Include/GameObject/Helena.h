#pragma once
#include "GameObject\GameObject.h"
class CHelena :
    public CGameObject
{
	friend class CScene;

protected:
	CHelena();
	CHelena(const CHelena& Obj);
	virtual ~CHelena();

private:
	class CQuestUI* m_QuestUI;

private:
	CSharedPtr<class CSpriteComponent>	m_MainSprite;
	CSharedPtr<class CSpriteComponent>	m_NameSprite;
	CSharedPtr<class CColliderBox2D>	m_Body;

	class CAnimation2D* m_Animation;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CHelena* Clone()    const;

public:
	void Save(FILE* File);
	void Load(FILE* File);

private:
	void QuestMouseClickCallback(const CollisionResult& result);
};

