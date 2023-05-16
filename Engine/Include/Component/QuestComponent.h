#pragma once
#include "ObjectComponent.h"

class CQuestComponent :
    public CObjectComponent
{
    friend class CGameObject;
    friend class CScene;

protected:
    int  m_PlayerLevel;
    bool FrontQuest;
    bool ClassChangeQuest;
    bool FinalBossQuest;


protected:
    CQuestComponent();
    CQuestComponent(const CQuestComponent& Obj);
    virtual ~CQuestComponent();

public:
    void SetLevel(int Level)
    {
        m_PlayerLevel = Level;
    }


public:
    virtual void Destroy();
    virtual void Start();
    virtual bool Init();
    virtual void FirstUpdate(float DeltaTime);
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render();
    virtual CQuestComponent* Clone()    const;
    virtual void Save(FILE* File);
    virtual void Load(FILE* File);
};

