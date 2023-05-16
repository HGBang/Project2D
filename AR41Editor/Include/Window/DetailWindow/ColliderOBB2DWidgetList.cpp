#include "ColliderOBB2DWidgetList.h"
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

CColliderOBB2DWidgetList::CColliderOBB2DWidgetList()
{
}

CColliderOBB2DWidgetList::~CColliderOBB2DWidgetList()
{
}

bool CColliderOBB2DWidgetList::Init()
{
	CEditorTree<void*>* Category = CreateWidget<CEditorTree<void*>>("ColliderComponent");

	Category->SetHideName("ColliderComponent");

	Category->SetSize(400.f, 300.f);

	Category->AddItem(nullptr, "Collider");

	m_ColliderList = Category->CreateWidget<CEditorListBox>("Collider", "Collider");
	m_ColliderList->SetPageItemCount(3);
	m_ColliderList->SetSizeX(200.f);

	m_ColliderList->SetSelectCallback<CColliderOBB2DWidgetList>(this, &CColliderOBB2DWidgetList::ColliderListClickCallBack);

	CEditorSameLine* Line = Category->CreateWidget<CEditorSameLine>("Collider", "Line");

	Line->SetSpacing(10.f);

	CEditorButton* ColliderButton = Category->CreateWidget<CEditorButton>("Collider", "수정");

	ColliderButton->SetClickCallback<CColliderOBB2DWidgetList>(this, &CColliderOBB2DWidgetList::ColliderClickButton);
	ColliderButton->SetSizeY(72.f);

	Line = Category->CreateWidget<CEditorSameLine>("Collider", "Line");

	Line->SetSpacing(10.f);

	ColliderButton = Category->CreateWidget<CEditorButton>("Collider", "취소");

	ColliderButton->SetClickCallback<CColliderOBB2DWidgetList>(this, &CColliderOBB2DWidgetList::ColliderCancelButton);
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


	m_StartX = Category->CreateWidget<CEditorInput>("Collider", "BoxSizeX");
	m_StartX->SetInputType(EImGuiInputType::Float);

	Line = Category->CreateWidget<CEditorSameLine>("Collider", "Line");

	Line->SetSpacing(10.f);

	m_SliderBarX = Category->CreateWidget<CEditorSliderBar>("Collider", "SliderX");


	m_StartY = Category->CreateWidget<CEditorInput>("Collider", "BoxSizeY");
	m_StartY->SetInputType(EImGuiInputType::Float);

	Line = Category->CreateWidget<CEditorSameLine>("Collider", "Line");

	Line->SetSpacing(10.f);

	m_SliderBarY = Category->CreateWidget<CEditorSliderBar>("Collider", "SliderY");

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

	OBB2DUpdate = false;

	return true;
}

void CColliderOBB2DWidgetList::Render()
{
	CComponentWidgetList::Render();

	if (OBB2DUpdate)
	{
		CSceneComponent* Component = m_DetailWindow->GetSelectComponent();

		CColliderOBB2D* Box = (CColliderOBB2D*)Component;
		Box->SetBoxHalfSize(m_StartX->GetFloat(), m_StartY->GetFloat());

		if (m_DetailCheck->GetTrue())
		{
			m_SliderBarX->SetInt3(500);
			m_SliderBarY->SetInt3(500);
			m_StartX->SetFloat((float)m_SliderBarX->GetInt());
			m_StartY->SetFloat((float)m_SliderBarY->GetInt());
		}
	}


}
void CColliderOBB2DWidgetList::ColliderListClickCallBack(int Index, const std::string& Item)
{
	m_SelectListItem = Item;

	CSceneComponent* Component = m_DetailWindow->GetSelectComponent();

	OBB2DUpdate = true;

	if (Component->GetComponentTypeName() == m_SelectListItem)
	{
		if (m_SelectListItem == "ColliderOBB2D")
		{
			CColliderOBB2D* Box = (CColliderOBB2D*)Component;

			m_Name->SetText("OBB2D");
			m_Name->ReadOnly(true);

			m_TypeName->SetInputType(EImGuiInputType::String);
			m_TypeName->SetText("OBB");
			m_TypeName->ReadOnly(true);

			Vector2 BoxSize = Box->GetHalfSize();			

			m_StartX->SetFloat(BoxSize.x);
			m_StartY->SetFloat(BoxSize.y);

			m_PrevSizeX = BoxSize.x;
			m_PrevSizeY = BoxSize.y;

			m_SliderBarX->SetInt((int)m_StartX->GetFloat());
			m_SliderBarY->SetInt((int)m_StartY->GetFloat());


			if (Box->GetCollisionProfile()->Channel->Name == "Default")
			{
				m_DefaultChannelCheck->SetTrue(true);
			}

			if (Box->GetCollisionProfile()->Channel->Name == "Mouse")
			{
				m_MouseChannelCheck->SetTrue(true);
			}

			if (Box->GetCollisionProfile()->Channel->Name == "Player")
			{
				m_PlayerChannelCheck->SetTrue(true);

				m_IgnoreList->AddItem("Player");
				m_IgnoreList->AddItem("PlayerAttack");
			}

			if (Box->GetCollisionProfile()->Channel->Name == "Monster")
			{
				m_MonsterChannelCheck->SetTrue(true);
				m_IgnoreList->AddItem("Monster");
				m_IgnoreList->AddItem("MonsterAttack");
			}

			if (Box->GetCollisionProfile()->Channel->Name == "PlayerAttack")
			{
				m_PlayerAttackChannelCheck->SetTrue(true);

				m_IgnoreList->AddItem("Player");
				m_IgnoreList->AddItem("PlayerAttack");

			}

			if (Box->GetCollisionProfile()->Channel->Name == "MonsterAttack")
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
		OBB2DUpdate = false;
	}
}

void CColliderOBB2DWidgetList::ColliderClickButton()
{
	CSceneComponent* Component = m_DetailWindow->GetSelectComponent();

	CColliderOBB2D* Box = (CColliderOBB2D*)Component;
	Box->SetBoxHalfSize(m_StartX->GetFloat(), m_StartY->GetFloat());

	if (m_DefaultChannelCheck->GetTrue())
	{
		Box->SetCollisionProfile("Default");
	}

	if (m_MouseChannelCheck->GetTrue())
	{
		Box->SetCollisionProfile("Mouse");
	}

	if (m_PlayerChannelCheck->GetTrue())
	{
		Box->SetCollisionProfile("Player");
	}

	if (m_MonsterChannelCheck->GetTrue())
	{
		Box->SetCollisionProfile("Monster");
	}

	if (m_PlayerAttackChannelCheck->GetTrue())
	{
		Box->SetCollisionProfile("PlayerAttack");
	}

	if (m_MonsterAttackChannelCheck->GetTrue())
	{
		Box->SetCollisionProfile("MonsterAttack");
	}

	m_IgnoreList->Clear();
	Clear();
}

void CColliderOBB2DWidgetList::ColliderCancelButton()
{
	if (m_SelectListItem == "ColliderOBB2D")
	{
		m_StartX->SetFloat(m_PrevSizeX);
		m_StartY->SetFloat(m_PrevSizeY);

		m_PrevSizeX = 0;
		m_PrevSizeY = 0;
	}
}

void CColliderOBB2DWidgetList::Clear()
{
	m_Name->SetText("");
	m_TypeName->SetText("");
	m_TypeName->SetFloat(0.f);
	m_StartX->SetFloat(0.f);
	m_StartY->SetFloat(0.f);
	m_SliderBarX->SetInt(0);
	m_SliderBarY->SetInt(0);

	OBB2DUpdate = false;

	m_DetailCheck->SetTrue(false);

	m_DefaultChannelCheck->SetTrue(false);
	m_MouseChannelCheck->SetTrue(false);
	m_PlayerChannelCheck->SetTrue(false);
	m_PlayerAttackChannelCheck->SetTrue(false);
	m_MonsterChannelCheck->SetTrue(false);
	m_MonsterAttackChannelCheck->SetTrue(false);

	m_IgnoreList->Clear();
}

void CColliderOBB2DWidgetList::SetAddColiderList(const std::string& Name)
{
	m_ColliderList->AddItem(Name);
}