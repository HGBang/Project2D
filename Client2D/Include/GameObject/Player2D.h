#pragma once

#include "GameObject/GameObject.h"

class CPlayer2D :
	public CGameObject
{
	friend class CScene;

protected:
	CPlayer2D();
	CPlayer2D(const CPlayer2D& Obj);
	virtual ~CPlayer2D();

private:
	CSharedPtr<class CSpriteComponent>	m_Sprite;
	CSharedPtr<class CSpriteComponent>	m_LevelUpSprite;
	CSharedPtr<class CSceneComponent>	m_RightChild;
	CSharedPtr<class CSpriteComponent>	m_SpriteChild;
	CSharedPtr<class CCameraComponent>	m_Camera;
	CSharedPtr<class CTargetArm>		m_Arm;
	CSharedPtr<class CColliderBox2D>	m_Body;
	CSharedPtr<class CMovementComponent> m_MoveComponent;
	CSharedPtr<class CSpriteComponent> m_DeBuffSprite;

	class CStartSceneUI* m_MainUI;
	class CStatusUI* m_StatUI;
	class CInventoryUI* m_ItemUI;
	class CEquipmentUI* m_EquipUI;

	class CQuestUI* m_QuestUI;
	bool m_FrontQuestOn;
	bool m_FrontQuestComplete;
	int  m_FrontMonsterCount;

	bool m_HelenaFirstQuest;

	bool m_ClassChangeQuestOn;
	bool m_BossQuestOn;

	bool		m_HitSkillLock;
	float		m_HitSkillLockTime;

	bool		m_NormalAttack; // 플레이어 기본 공격 
	bool		m_SpeedDuelShot; // 플레이어 스피드듀얼샷 스킬 

	bool		m_AttackOn;
	bool		m_MoveOn;
	bool		m_Moving;
	bool		m_RightRopeJump;
	bool		m_LeftRopeJump;

	bool		m_RingON;
	bool		m_RingSound;

	bool		m_SkillOn;
	float		m_SkillTime;

	float		m_DebuffTime;

	float		m_RingTime;
	

	class CAnimation2D* m_Animation;
	class CAnimation2D* m_SkillAnimation;
	class CAnimation2D* m_LevelUpAnimation;
	class CAnimation2D* m_DeBuffAnimation;

	bool		m_Weapon;
	bool		m_Weapon1;
	bool		m_Weapon2;
	bool		m_AttackRage;

	float		m_TestTime;
	bool		m_Ground;
	bool		m_Jump;

	bool		m_DebuffSkillLock;
	bool		m_Hit;
	float		m_HitTime;
	float		m_RopePosX;



	bool		m_ImmuneDamage;
	float		m_ImmuneTime;
	float		m_ImmuneDamageTime;

	bool		m_LevelUp;
	bool		m_LevelUpOn;

	bool		m_RopeOn;
	bool		m_Rope;

	bool		m_Skill1Lock;
	bool		m_Skill2Lock;

	bool		m_FlashRightJump;
	bool		m_FlashLeftJump;
	float		m_FlashJumpTime;
	float		m_DivingTime;

	/// 플레이어 스테이터스

	int		m_HP;
	int		m_MaxHP;

	int		m_MP;
	int		m_MaxMP;

	int		m_Exp;
	int		m_MaxExp;

	int		m_Level;

	int		m_Damage;
	int		m_WeaponDamage;
	int		m_Skill1Damage;
	int		m_Skill2Damage;
	int		m_Str;
	int		m_Dex;
	int		m_Luk;
	int		m_Int;

	int		m_Ap;

	bool	m_StartDamagetime;
	int		m_StartDamage;

	bool	m_DamageDebuff;
	float	m_DamageDebuffTime;

	// 플레이어 물약 개수 

	int m_HpPotionNumber;
	int m_MpPotionNumber;


	// 플레이어 히트 좌우 판정
	bool m_LeftHit;
	bool m_RightHit;
	

public:
	void SetDamageDebuff(bool Debuff)
	{
		m_DamageDebuff = Debuff;
	}


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

	void AddMaxHp(int MaxHp)
	{
		m_MaxHP += MaxHp;
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
		if (m_HpPotionNumber > 0)
		{
			m_HP += hp;
			--m_HpPotionNumber;

			if (m_HP > m_MaxHP)
				m_HP = m_MaxHP;

		}
	}

	void HitHp(int hp)
	{
		if (m_HP <= 0)
			return;

		m_HP += hp;

	}

	int GetMaxMp() const
	{
		return m_MaxMP;
	}

	void AddMaxMp(int MaxMP)
	{
		m_MaxMP += MaxMP;
	}

	void SetMaxMp(int MaxMp)
	{
		m_MaxMP = MaxMp;
	}

	void SetMaxHp(int MaxHp)
	{
		m_MaxHP = MaxHp;
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
		if (m_MpPotionNumber > 0)
		{
			m_MP += Mp;
			--m_MpPotionNumber;

			if (m_MP > m_MaxMP)
				m_MP = m_MaxMP;
		}
	}

	void AddSkillMp(int Mp)
	{
		m_MP += Mp;
	}

	int GetMaxExp() const
	{
		return m_MaxExp;
	}

	void AddMaxExp(int Exp)
	{
		m_MaxExp += Exp;
	}

	int GetExp() const
	{
		return m_Exp;
	}

	int GetDamage() const
	{
		return m_Damage;
	}

	int GetAp() const
	{
		return m_Ap;
	}

	void SetExp(int Exp)
	{
		m_Exp = Exp;
	}

	void AddExp(int Exp)
	{
		m_Exp += Exp;
	}

	int GetStr() const
	{
		return m_Str;
	}

	void AddStr(int Str)
	{
		if (!m_Ap)
			return;

		m_Str += Str;
		--m_Ap;
	}

	int GetDex() const
	{
		return m_Dex;
	}

	void AddDex(int Dex)
	{
		if (!m_Ap)
			return;

		m_Dex += Dex;
		--m_Ap;
	}

	int GetInt() const
	{
		return m_Int;
	}

	void AddInt(int Int)
	{
		if (!m_Ap)
			return;

		m_Int += Int;
		--m_Ap;
	}

	int GetLuk() const
	{
		return m_Luk;
	}

	void AddLuk(int Luk)
	{
		if (!m_Ap)
			return;

		m_Luk += Luk;
		--m_Ap;
	}

	void AddAp(int Ap)
	{
		m_Ap += Ap;
	}

	bool GetLevelUpOn() const
	{
		return m_LevelUpOn;
	}		

	bool GetFrontQuestOn()
	{
		return m_FrontQuestOn;
	}

	void AddHpPotionNumber(int Number)
	{
		m_HpPotionNumber += Number;
	}

	void AddMpPotionNumber(int Number)
	{
		m_MpPotionNumber += Number;
	}

	int GetHpPotionNumber()
	{
		return m_HpPotionNumber;
	}

	int GetMpPotionNumber()
	{
		return m_MpPotionNumber;
	}

	void SetHpPotionNumber(int HpPotion)
	{
		m_HpPotionNumber = HpPotion;
	}

	void SetMpPotionNumber(int MpPotion)
	{
		m_MpPotionNumber = MpPotion;
	}

	void SetSkill1Lock(bool Lock)
	{
		m_Skill1Lock = Lock;
	}

	void SetSkill2Lock(bool Lock)
	{
		m_Skill2Lock = Lock;
	}

	bool GetSkill1Lock()
	{
		return m_Skill1Lock;
	}

	bool GetSkill2Lock()
	{
		return m_Skill2Lock;
	}

	bool GetHelenaFirstQuestOn()
	{
		return m_HelenaFirstQuest;
	}

	void SetStr(int Str)
	{
		m_Str = Str;
	}

	void SetDex(int Dex)
	{
		m_Dex = Dex;
	}

	void SetInt(int Int)
	{
		m_Int = Int;
	}

	void SetLuk(int Luk)
	{
		m_Luk = Luk;
	}

	void SetMaxExp(int Exp)
	{
		m_MaxExp = Exp;
	}

	void SetDeBuff(bool Debuff);
	


public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CPlayer2D* Clone()    const;

public:
	void SetWeapon(bool Weapon)
	{
		m_Weapon = Weapon;
	}

	void SetWeapon1(bool Weapon)
	{
		m_Weapon1 = Weapon;
	}

	void SetWeapon2(bool Weapon)
	{
		m_Weapon2 = Weapon;
	}

	bool GetWeapon()
	{
		return m_Weapon;
	}

	bool GetWeapon1()
	{
		return m_Weapon1;
	}

	bool GetWeapon2()
	{
		return m_Weapon2;
	}

	int GetMaxExp()
	{
		return m_MaxExp;
	}




public:
	void MoveUp();
	void MoveDown();
	void MoveRight();
	void MoveLeft();
	void FlashJump();
	void Ring();
	void RingEffect();
	void NormalAttack();
	void SpeedDuelShot();

	void RightUp();
	void LeftUp();
	void DownUp();
	void MoveUpUp();
	void FireUp();

	void NormalAttackUp();
	void Jump();
	void LevelUpKey();

public:
	void LevelUpEnd();

public:
	void StatUIOpen();
	void ItemUIOpen();
	void EquipUIOpen();
	void NormalChange();

public:
	void CollisionPlayer(const CollisionResult& result);
	void CollisionPlayerEnd(const CollisionResult& result);
	void Save(FILE* File);
	void Load(FILE* File);

public:
	void SetFrontQuestOn(bool Front)
	{
		m_FrontQuestOn = Front;
	}

	bool GetFrontQuestComplete() const
	{
		return m_FrontQuestComplete;
	}

	void SetFrontQuestComplete(bool Complete) 
	{
		m_FrontQuestComplete = Complete;	
	}

	void SetHelenaFirstQuestOn(bool Helena)
	{
		m_HelenaFirstQuest = Helena;
	}
	
	void AddFrontMonsterCount(int Count)
	{
		m_FrontMonsterCount += Count;
	}


	void SetClassChangeQuestOn(bool Change)
	{
		m_ClassChangeQuestOn = Change;
	}

	void SetBossQuestOn(bool Boss)
	{
		m_BossQuestOn = Boss;
	}

	void SetAnimation(const std::string& Name);
	

private:
	void AttackEndFunc();
	void AttackStartFunc();
	void RedPotionKeyFunc();
	void BluePotionKeyFunc();
};

