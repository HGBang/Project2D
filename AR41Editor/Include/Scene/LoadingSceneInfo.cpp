
#include "LoadingSceneInfo.h"
#include "Scene/SceneManager.h"
#include "Scene/Scene.h"
#include "Scene/SceneViewport.h"
#include "../UI/LoadingUI.h"
#include "Thread/ThreadManager.h"
#include "Thread/LoadingThread.h"
#include "Thread/ThreadQueue.h"
#include "Thread/DataStream.h"




CLoadingSceneInfo::CLoadingSceneInfo()
{
}

CLoadingSceneInfo::~CLoadingSceneInfo()
{
}

bool CLoadingSceneInfo::Init()
{
	m_LoadingUI = m_Owner->GetViewport()->CreateUIWindow<CLoadingUI>("LoadingUI");

	return true;
}

void CLoadingSceneInfo::Update(float DeltaTime)
{
	CSceneInfo::Update(DeltaTime);

	if (!m_LoadingQueue->empty())
	{
		int	Header, Size;
		unsigned char	Data[1024] = {};

		m_LoadingQueue->pop(&Header, &Size, Data);

		CDataStream	stream;
		stream.SetBuffer(Data);

		float	Rate = 0.f;

		stream.GetData<float>(&Rate, 4);

		m_LoadingUI->SetLoadingPercent(Rate);

	}
	
	if (m_LoadingThread->IsLoadComplete())
	{
		CSceneManager::GetInst()->ChangeNextScene();
	}
	
}

void CLoadingSceneInfo::SceneChangeComplete()
{
	m_LoadingThread = CThreadManager::GetInst()->CreateThread<CLoadingThread>("Loading");

	m_LoadingThread->SetLoadingSceneFileName("Main1.scn");

	m_LoadingQueue = m_LoadingThread->GetQueue();

	m_LoadingThread->Start();
}
