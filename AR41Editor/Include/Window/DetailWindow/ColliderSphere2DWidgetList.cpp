#include "ColliderSphere2DWidgetList.h"
#include "Editor/EditorTree.h"
#include "Editor/EditorButton.h"
#include "Editor/EditorImage.h"
#include "Editor/EditorInput.h"
#include "Editor/EditorSameLine.h"
#include "Editor/EditorListBox.h"
#include "SpriteComponentWidgetList.h"
#include "Editor/EditorTree.h"
#include "Editor/EditorButton.h"
#include "Editor/EditorSameLine.h"
#include "Editor/EditorImage.h"
#include "Editor/EditorInput.h"
#include "Editor/EditorListBox.h"
#include "../Animation2DWindow.h"
#include "Editor/EditorGUIManager.h"
#include "../DetailWindow.h"
#include "Component/SpriteComponent.h"
#include "Editor/EditorGUIManager.h"
#include "../Animation2DWindow.h"
#include "Editor/EditorCheckBox.h"
#include "Resource/Animation/AnimationManager.h"
#include "Resource/Animation/AnimationSequence2D.h"
#include "Resource/ResourceManager.h"
#include "Animation/Animation2D.h"
#include "PathManager.h"
#include "Editor/EditorLabel.h"
#include "Editor/EditorSliderBar.h"

#include "Component/Collider.h"
#include "Component/Collider2D.h"
#include "Component/ColliderBox2D.h"
#include "Component/ColliderOBB2D.h"
#include "Component/ColliderSphere2D.h"
#include "Component/ColliderPixel.h"

CColliderSphere2DWidgetList::CColliderSphere2DWidgetList()
{
}

CColliderSphere2DWidgetList::~CColliderSphere2DWidgetList()
{
}

bool CColliderSphere2DWidgetList::Init()
{
	CEditorTree<void*>* Category = CreateWidget<CEditorTree<void*>>("ColliderComponent");

	Category->SetHideName("ColliderComponent");

	Category->SetSize(400.f, 300.f);

	Category->AddItem(nullptr, "Collider");

	m_ColliderList = Category->CreateWidget<CEditorListBox>("Collider", "Collider");
	m_ColliderList->SetPageItemCount(3);
	m_ColliderList->SetSizeX(200.f);

	m_ColliderList->SetSelectCallback<CColliderSphere2DWidgetList>(this, &CColliderSphere2DWidgetList::ColliderListClickCallBack);

	CEditorSameLine* Line = Category->CreateWidget<CEditorSameLine>("Collider", "Line");

	Line->SetSpacing(10.f);

	CEditorButton* ColliderButton = Category->CreateWidget<CEditorButton>("Collider", "수정");

	ColliderButton->SetClickCallback<CColliderSphere2DWidgetList>(this, &CColliderSphere2DWidgetList::ColliderClickButton);
	ColliderButton->SetSizeY(72.f);

	Line = Category->CreateWidget<CEditorSameLine>("Collider", "Line");

	Line->SetSpacing(10.f);

	ColliderButton = Category->CreateWidget<CEditorButton>("Collider", "취소");

	ColliderButton->SetClickCallback<CColliderSphere2DWidgetList>(this, &CColliderSphere2DWidgetList::ColliderCancelButton);
	ColliderButton->SetSizeY(72.f);

	CEditorLabel* Label = Category->CreateWidget<CEditorLabel>("Collider", "Collider Info");
	Label->SetColor(255, 50, 50, 255);
	Label->SetAlign(0.5f, 0.5f);
	Label->SetSize(400.f, 30.f);

	m_Name = Category->CreateWidget<CEditorInput>("Collider", "ColliderName");

	Line = Category->CreateWidget<CEditorSameLine>("Collider", "Line");

	Line->SetSpacing(10.f);

	m_TypeName = Category->CreateWidget<CEditorInput>("Collider", "ColliderType");

	Line = Category->CreateWidget<CEditorSameLine>("Collider", "Line");

	Line->SetSpacing(10.f);

	m_DetailCheck = Category->CreateWidget<CEditorCheckBox>("Collider", u8"크기 상세 조절");


	m_Radius = Category->CreateWidget<CEditorInput>("Collider", "Radius");
	m_Radius->SetInputType(EImGuiInputType::Float);

	Line = Category->CreateWidget<CEditorSameLine>("Collider", "Line");

	Line->SetSpacing(10.f);

	m_SliderBarX = Category->CreateWidget<CEditorSliderBar>("Collider", "SliderX");



	Label = Category->CreateWidget<CEditorLabel>("Collider", "Default Channel");

	Label->SetColor(50, 50, 50, 255);
	Label->SetAlign(0.5f, 0.5f);
	Label->SetSize(130.f, 30.f);

	Line = Category->CreateWidget<CEditorSameLine>("Collider", "Line");

	Line->SetSpacing(50.f);

	Label = Category->CreateWidget<CEditorLabel>("Collider", "Player Channel");

	Label->SetColor(50, 50, 50, 255);
	Label->SetAlign(0.5f, 0.5f);
	Label->SetSize(130.f, 30.f);

	Line = Category->CreateWidget<CEditorSameLine>("Collider", "Line");

	Line->SetSpacing(50.f);

	Label = Category->CreateWidget<CEditorLabel>("Collider", "Monster Channel");

	Label->SetColor(50, 50, 50, 255);
	Label->SetAlign(0.5f, 0.5f);
	Label->SetSize(130.f, 30.f);


	m_DefaultChannelCheck = Category->CreateWidget<CEditorCheckBox>("Collider", "Default");

	Line = Category->CreateWidget<CEditorSameLine>("Collider", "Line");

	Line->SetSpacing(97.f);

	m_PlayerChannelCheck = Category->CreateWidget<CEditorCheckBox>("Collider", "Player");

	Line = Category->CreateWidget<CEditorSameLine>("Collider", "Line");

	Line->SetSpacing(103.f);

	m_MonsterChannelCheck = Category->CreateWidget<CEditorCheckBox>("Collider", "Monster");


	m_MouseChannelCheck = Category->CreateWidget<CEditorCheckBox>("Collider", "Mouse");


	Line = Category->CreateWidget<CEditorSameLine>("Collider", "Line");

	Line->SetSpacing(104.f);

	m_PlayerAttackChannelCheck = Category->CreateWidget<CEditorCheckBox>("Collider", "PlayerAttack");

	Line = Category->CreateWidget<CEditorSameLine>("Collider", "Line");

	Line->SetSpacing(56.f);

	m_MonsterAttackChannelCheck = Category->CreateWidget<CEditorCheckBox>("Collider", "MonsterAttack");

	Label = Category->CreateWidget<CEditorLabel>("Collider", "Ignore Channel");
	Label->SetColor(255, 50, 50, 255);
	Label->SetAlign(0.5f, 0.5f);
	Label->SetSize(400.f, 30.f);

	m_IgnoreList = Category->CreateWidget<CEditorListBox>("Collider", "");
	m_IgnoreList->SetSizeX(200.f);
	m_IgnoreList->SetPageItemCount(3);

	Sphere2DUpdate = false;

	return true;
}

void CColliderSphere2DWidgetList::Render()
{
	CComponentWidgetList::Render();

	if (Sphere2DUpdate)
	{
		CSceneComponent* Component = m_DetailWindow->GetSelectComponent();

		CColliderSphere2D* Sphere = (CColliderSphere2D*)Component;
		Sphere->SetRadius(m_Radius->GetFloat());

		if (m_DetailCheck->GetTrue())
		{
			m_SliderBarX->SetInt3(500);		
			m_Radius->SetFloat((float)m_SliderBarX->GetInt());
		
		}
	}
}

void CColliderSphere2DWidgetList::ColliderListClickCallBack(int Index, const std::string& Item)
{
	m_SelectListItem = Item;

	CSceneComponent* Component = m_DetailWindow->GetSelectComponent();

	Sphere2DUpdate = true;

	if (Component->GetComponentTypeName() == m_SelectListItem)
	{
		if (m_SelectListItem == "ColliderSphere2D")
		{
			CColliderSphere2D* Sphere = (CColliderSphere2D*)Component;

			m_Name->SetText("Sphere2D");
			m_Name->ReadOnly(true);

			m_TypeName->SetInputType(EImGuiInputType::String);
			m_TypeName->SetText("Sphere");
			m_TypeName->ReadOnly(true);

			Sphere2DInfo Info = Sphere->GetInfo();

			m_Radius->SetFloat(Info.Radius);

			m_PrevSizeX = Info.Radius;
			
			m_SliderBarX->SetInt((int)m_Radius->GetFloat());


			if (Sphere->GetCollisionProfile()->Channel->Name == "Default")
			{
				m_DefaultChannelCheck->SetTrue(true);
			}

			if (Sphere->GetCollisionProfile()->Channel->Name == "Mouse")
			{
				m_MouseChannelCheck->SetTrue(true);
			}

			if (Sphere->GetCollisionProfile()->Channel->Name == "Player")
			{
				m_PlayerChannelCheck->SetTrue(true);

				m_IgnoreList->AddItem("Player");
				m_IgnoreList->AddItem("PlayerAttack");
			}

			if (Sphere->GetCollisionProfile()->Channel->Name == "Monster")
			{
				m_MonsterChannelCheck->SetTrue(true);
				m_IgnoreList->AddItem("Monster");
				m_IgnoreList->AddItem("MonsterAttack");
			}

			if (Sphere->GetCollisionProfile()->Channel->Name == "PlayerAttack")
			{
				m_PlayerAttackChannelCheck->SetTrue(true);

				m_IgnoreList->AddItem("Player");
				m_IgnoreList->AddItem("PlayerAttack");

			}

			if (Sphere->GetCollisionProfile()->Channel->Name == "MonsterAttack")
			{
				m_MonsterAttackChannelCheck->SetTrue(true);

				m_IgnoreList->AddItem("Monster");
				m_IgnoreList->AddItem("MonsterAttack");
			}
		}
	}

	if ("새로고침" == m_SelectListItem)
	{
		Clear();
		Sphere2DUpdate = false;
	}
}

void CColliderSphere2DWidgetList::ColliderClickButton()
{
	CSceneComponent* Component = m_DetailWindow->GetSelectComponent();

	CColliderSphere2D* Sphere = (CColliderSphere2D*)Component;
	Sphere->SetRadius(m_Radius->GetFloat());

	if (m_DefaultChannelCheck->GetTrue())
	{
		Sphere->SetCollisionProfile("Default");
	}

	if (m_MouseChannelCheck->GetTrue())
	{
		Sphere->SetCollisionProfile("Mouse");
	}

	if (m_PlayerChannelCheck->GetTrue())
	{
		Sphere->SetCollisionProfile("Player");
	}

	if (m_MonsterChannelCheck->GetTrue())
	{
		Sphere->SetCollisionProfile("Monster");
	}

	if (m_PlayerAttackChannelCheck->GetTrue())
	{
		Sphere->SetCollisionProfile("PlayerAttack");
	}

	if (m_MonsterAttackChannelCheck->GetTrue())
	{
		Sphere->SetCollisionProfile("MonsterAttack");
	}

	m_IgnoreList->Clear();
	Clear();
}

void CColliderSphere2DWidgetList::ColliderCancelButton()
{
	if (m_SelectListItem == "ColliderSphere2D")
	{
		m_Radius->SetFloat(m_PrevSizeX);
		
		m_PrevSizeX = 0;	
	}
}

void CColliderSphere2DWidgetList::Clear()
{
	m_Name->SetText("");
	m_TypeName->SetText("");
	m_TypeName->SetFloat(0.f);
	m_Radius->SetFloat(0.f);
	m_SliderBarX->SetInt(0);
	Sphere2DUpdate = false;

	m_DetailCheck->SetTrue(false);

	m_DefaultChannelCheck->SetTrue(false);
	m_MouseChannelCheck->SetTrue(false);
	m_PlayerChannelCheck->SetTrue(false);
	m_PlayerAttackChannelCheck->SetTrue(false);
	m_MonsterChannelCheck->SetTrue(false);
	m_MonsterAttackChannelCheck->SetTrue(false);

	m_IgnoreList->Clear();
}

void CColliderSphere2DWidgetList::SetAddColiderList(const std::string& Name)
{
	m_ColliderList->AddItem(Name);
}
