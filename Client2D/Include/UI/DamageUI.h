#pragma once
#include "UI\UIWindow.h"
class CDamageUI :
    public CUIWindow
{
	friend class CSceneViewport;
	friend class CScene;


protected:
	CDamageUI();
	CDamageUI(const CDamageUI& Window);
	virtual ~CDamageUI();

protected:
	class CPlayer2D* m_Player;

	float DamageEnableTime;
	std::string DamageID;
	int DamageNumberID;

public:
	void SetPlayer(CPlayer2D* Player)
	{
		m_Player = Player;
	}

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render();
	virtual CDamageUI* Clone() const;
	virtual void Save(FILE* File);
	virtual void Load(FILE* File);

public:
	void SetDamageNumber(Vector2 Pos, int Damage);

};

