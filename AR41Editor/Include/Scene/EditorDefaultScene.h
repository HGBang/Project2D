#pragma once

#include "Scene/SceneInfo.h"



class CEditorDefaultScene :
    public CSceneInfo
{

public:
    CEditorDefaultScene();
    ~CEditorDefaultScene();

private:
    class CUINumber* m_Number;

    float RespawnTime;
    

public:
    virtual bool Init();

public:
    void RespawnSkelegon(const Vector2& MonsterPos);
};

