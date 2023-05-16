#pragma once
#include "ObjectComponent.h"

class CUIComponent :
    public CObjectComponent
{
    friend class CGameObject;
    friend class CScene;


protected:
    CUIComponent();
    CUIComponent(const CUIComponent& Obj);
    virtual ~CUIComponent();

private:
    class CUIWindow* m_UIWindow;
    class CPlayer2D* m_Player;

    float Delta;

public:
    void SetWindow();

public:
    virtual void Destroy();
    virtual void Start();
    virtual bool Init();
    virtual void FirstUpdate(float DeltaTime);
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render();
    virtual CUIComponent* Clone()    const;
    virtual void Save(FILE* File);
    virtual void Load(FILE* File);




public:
	/// 플레이어 스테이터스
	int		m_HP;
	int		m_MaxHP;

	int		m_MP;
	int		m_MaxMP;

	int		m_Exp;
	int		m_MaxExp;

	int		m_Level;


public:
	int GetLevel() const
	{
		return m_Level;
	}

	void SetLevel(int Level)
	{
		m_Level = Level;
	}

	void AddLevel(int Level)
	{
		m_Level += Level;
	}

	int GetMaxHp() const
	{
		return m_MaxHP;
	}

	void SetMaxHp(int MaxHp)
	{
		m_MaxHP = MaxHp;
	}

	int GetHp() const
	{
		return m_HP;
	}

	void SetHp(int Hp)
	{
		m_HP = Hp;
	}

	void AddHp(int hp)
	{
		m_HP += hp;
	}

	int GetMaxMp() const
	{
		return m_MaxMP;
	}

	void SetMaxMp(int MaxMP)
	{
		m_MaxMP = MaxMP;
	}

	int GetMp() const
	{
		return m_MP;
	}

	void SetMp(int Mp)
	{
		m_MP = Mp;
	}

	void AddMp(int Mp)
	{
		m_MP += Mp;
	}

	int GetMaxExp() const
	{
		return m_MaxExp;
	}

	void SetMaxExp(int Exp)
	{
		m_MaxExp = Exp;
	}

	int GetExp() const
	{
		return m_Exp;
	}

	void SetExp(int Exp)
	{
		m_Exp = Exp;
	}

	void AddExp(int Exp)
	{
		m_Exp += Exp;
	}

};

