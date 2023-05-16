#include "UIComponent.h"
#include "../UI/UIWindow.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneManager.h"
#include "../UI/UIProgressBar.h"
#include "../UI/UIButton.h"
#include "../UI/UIImage.h"
#include "../UI/UINumber.h"
#include "../UI/UIText.h"
#include "../GameObject/GameObject.h"




CUIComponent::CUIComponent() : 
	m_Level(10),
	m_MaxHP(2000),
	m_HP(1800),
	m_MaxMP(1000),
	m_MP(800),
	m_MaxExp(1000),
	m_Exp(0)	
{
	m_ComponentType = ComponentType::Object;

	SetTypeID<CUIComponent>();
	m_ComponentTypeName = "UIComponent";
}

CUIComponent::CUIComponent(const CUIComponent& Obj)
{
}

CUIComponent::~CUIComponent()
{
}

void CUIComponent::SetWindow()
{
	m_UIWindow = nullptr;

	if (m_Scene)
		m_UIWindow = m_Scene->GetViewport()->FindUIWindow<CUIWindow>("StartUI");

	else
		m_UIWindow = CSceneManager::GetInst()->GetScene()->GetViewport()->FindUIWindow<CUIWindow>("StartUI");

}

void CUIComponent::Destroy()
{
	CObjectComponent::Destroy();
}

void CUIComponent::Start()
{
	CObjectComponent::Start();
	

	
}

bool CUIComponent::Init()
{
	if (!CComponent::Init())
		return false;


	return true;
}

void CUIComponent::FirstUpdate(float DeltaTime)
{
	CObjectComponent::FirstUpdate(DeltaTime);
}

void CUIComponent::Update(float DeltaTime)
{
	CObjectComponent::Update(DeltaTime);


	//m_UIWindow->FindWidget<CUIProgressBar>("ExpProgressBar")->SetProgressBarMax((float)m_MaxExp);
	//m_UIWindow->FindWidget<CUIProgressBar>("ExpProgressBar")->SetProgressBarMin(0.f);
	//m_UIWindow->FindWidget<CUIProgressBar>("ExpProgressBar")->SetValue((float)m_Exp);
	//m_UIWindow->FindWidget<CUINumber>("ExpNumber")->SetNumber(m_Exp);
	//m_UIWindow->FindWidget<CUINumber>("ExpValueNumber")->SetNumber(m_UIWindow->FindWidget<CUIProgressBar>("ExpProgressBar")->GetValue());



	//m_UIWindow->FindWidget<CUIProgressBar>("HpProgressBar")->SetProgressBarMax((float)m_MaxExp);
	//m_UIWindow->FindWidget<CUIProgressBar>("HpProgressBar")->SetProgressBarMin(0.f);
	//m_UIWindow->FindWidget<CUIProgressBar>("HpProgressBar")->SetValue((float)m_Exp);



	//m_UIWindow->FindWidget<CUIProgressBar>("MpProgressBar")->SetValue(Delta);

	//m_UIWindow->FindWidget<CUINumber>("LevelNumber")->SetNumber(m_Owner->get)
	//m_UIWindow->FindWidget<CUINumber>("ExpNumber")->SetValue(Delta);
	//m_UIWindow->FindWidget<CUINumber>("ExpValueNumber")->SetValue(Delta);
	//m_UIWindow->FindWidget<CUINumber>("HpNumber")->SetValue(Delta);
	//m_UIWindow->FindWidget<CUINumber>("MaxHpNumber")->SetValue(Delta);
	//m_UIWindow->FindWidget<CUINumber>("MpNumber")->SetValue(Delta);
	//m_UIWindow->FindWidget<CUINumber>("MaxMpNumber")->SetValue(Delta);


	/*
	
	m_ExpProgressBar = FindWidget<CUIProgressBar>("ExpProgressBar");
	m_HpProgressBar = FindWidget<CUIProgressBar>("HpProgressBar");
	m_MpProgressBar = FindWidget<CUIProgressBar>("MpProgressBar");
	m_LevelNumber = FindWidget<CUINumber>("LevelNumber");
	m_ExpNumber = FindWidget<CUINumber>("ExpNumber");
	m_ExpValueNumber = FindWidget<CUINumber>("ExpValueNumber");
	m_HpNumber = FindWidget<CUINumber>("HpNumber");
	m_MaxHpNumber = FindWidget<CUINumber>("MaxHpNumber");
	m_MpNumber = FindWidget<CUINumber>("MpNumber");
	m_MaxMpNumber = FindWidget<CUINumber>("MaxMpNumber");

	
	*/


}

void CUIComponent::PostUpdate(float DeltaTime)
{
	CObjectComponent::PostUpdate(DeltaTime);
}

void CUIComponent::Render()
{
	CObjectComponent::Render();
}

CUIComponent* CUIComponent::Clone() const
{
	return new CUIComponent(*this);
}

void CUIComponent::Save(FILE* File)
{
	CObjectComponent::Save(File);
}

void CUIComponent::Load(FILE* File)
{
	CObjectComponent::Load(File);
}
