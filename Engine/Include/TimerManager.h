#pragma once
#include "EngineInfo.h"

struct TimerData
{	
	unsigned int	TimerID;	//Ÿ�̸� �ĺ���
	float			Interval;	//Ÿ�̸� �ֱ�
	bool			Loop;		//Ÿ�̸ӹݺ�	

	//RunTimeData
	float			Current;
	bool			Pause;
	std::function<void(void)> Func;

	bool		PendingKill;


	TimerData(unsigned int Id , float interval, bool loop, std::function<void(void)> OnFunc)
		: TimerID(Id)
		, Interval(interval)
		, Loop(loop)
		, Current(0.0f)
		, Func(OnFunc)
		,Pause(false)
	{
	}

};


class CTimerManager
{

	
protected:
	std::list<TimerData> m_TimerList;
	unsigned int	m_TimerCount;
	
	float m_TimerTime;


public:
	bool Init();
	void Update(float DeltaTime);
	void PostUpdate(float DeltaTime);


public:
	void SetTimer(unsigned int& OutId, float Interval, bool Loop, std::function<void(void)> BindFunc);

	//�ش� Ÿ�̸� ����
	void RemoveTimer(const unsigned int& InID);

	void PauseTimer(const unsigned int& InID);

	void ResumeTimer(const unsigned int& InID);

	void ClearAllTimer();

	float GetRemainTime(const unsigned int& InID);

	DECLARE_SINGLE(CTimerManager)
};

