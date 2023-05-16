#include "TimerManager.h"

DEFINITION_SINGLE(CTimerManager)

CTimerManager::CTimerManager()
{
	m_TimerCount = 0;		// Invalid ID
}

CTimerManager::~CTimerManager()
{
}

bool CTimerManager::Init()
{
	return true;
}

void CTimerManager::Update(float DeltaTime)
{
	
		std::list<TimerData>::iterator iter = m_TimerList.begin();
		std::list<TimerData>::iterator iterEnd = m_TimerList.end();
		for (; iter != iterEnd;)
		{
			(*iter).Current += DeltaTime;

			if ((*iter).Current >= (*iter).Interval)
			{
				(*iter).Func(); // RemoveTimer
							

				if ((*iter).Loop)
				{
					(*iter).Current = 0.0f;
				}
				else 
				{
					iter = m_TimerList.erase(iter);
					iterEnd = m_TimerList.end();
					continue;
				}
			}

			iter++;
		}
	
}

void CTimerManager::PostUpdate(float DeltaTime)
{

}



void CTimerManager::SetTimer(unsigned int& OutId, float Interval, bool Loop, std::function<void(void)> BindFunc)
{
	m_TimerCount++;	
	OutId = m_TimerCount;
	m_TimerList.push_back(TimerData(OutId, Interval, Loop, BindFunc));
}

void CTimerManager::RemoveTimer(const unsigned int& InID)
{

}

void CTimerManager::PauseTimer(const unsigned int& InID)
{
}

void CTimerManager::ResumeTimer(const unsigned int& InID)
{
}

void CTimerManager::ClearAllTimer()
{
}

float CTimerManager::GetRemainTime(const unsigned int& InID)
{
	return 0.0f;
}
