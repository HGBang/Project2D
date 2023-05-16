#pragma once
#include "GameObject\GameObject.h"
class CElderNpc :
    public CGameObject
{
	friend class CScene;

protected:
	CElderNpc();
	CElderNpc(const CElderNpc& Obj);
	virtual ~CElderNpc();

private:
	class CQuestUI* m_QuestUI;
	bool			m_FrontQuestOn;
	bool			m_ChangeClassQuestOn;
	bool			m_BossQuestOn;
	bool			m_QuestIng;
	bool			m_QuestClickOn;



private:
	CSharedPtr<class CSpriteComponent>	m_MainSprite;
	CSharedPtr<class CSpriteComponent>	m_QuestSprite;
	CSharedPtr<class CColliderBox2D>	m_Body;

	class CAnimation2D* m_Animation;
	class CAnimation2D* m_QuestAnimation;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CElderNpc* Clone()    const;

public:
	void Save(FILE* File);
	void Load(FILE* File);

private:
	void QuestMouseClickCallback(const CollisionResult& result);
	void QuestMouseClickOffCallback(const CollisionResult& result);

};

