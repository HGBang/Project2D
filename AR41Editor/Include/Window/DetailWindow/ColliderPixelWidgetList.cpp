#include "ColliderPixelWidgetList.h"
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

CColliderPixelWidgetList::CColliderPixelWidgetList()
{
}

CColliderPixelWidgetList::~CColliderPixelWidgetList()
{
}

bool CColliderPixelWidgetList::Init()
{
	CEditorTree<void*>* Category = CreateWidget<CEditorTree<void*>>("ColliderComponent");

	Category->SetHideName("ColliderComponent");

	Category->SetSize(400.f, 300.f);

	Category->AddItem(nullptr, "ColliderPixel");

	m_PixelColliderList = Category->CreateWidget<CEditorListBox>("ColliderPixel", "Collider");
	m_PixelColliderList->SetPageItemCount(3);
	m_PixelColliderList->SetSizeX(200.f);

	m_PixelColliderList->SetSelectCallback<CColliderPixelWidgetList>(this, &CColliderPixelWidgetList::ColliderListClickCallBack);

	CEditorSameLine* Line = Category->CreateWidget<CEditorSameLine>("ColliderPixel", "Line");

	Line->SetSpacing(10.f);

	CEditorButton* ColliderButton = Category->CreateWidget<CEditorButton>("ColliderPixel", "수정");

	ColliderButton->SetClickCallback<CColliderPixelWidgetList>(this, &CColliderPixelWidgetList::ColliderClickButton);
	ColliderButton->SetSizeY(72.f);

	Line = Category->CreateWidget<CEditorSameLine>("ColliderPixel", "Line");

	Line->SetSpacing(10.f);

	ColliderButton = Category->CreateWidget<CEditorButton>("ColliderPixel", "취소");

	ColliderButton->SetClickCallback<CColliderPixelWidgetList>(this, &CColliderPixelWidgetList::ColliderCancelButton);
	ColliderButton->SetSizeY(72.f);

	CEditorLabel* Label = Category->CreateWidget<CEditorLabel>("ColliderPixel", "Collider Info");
	Label->SetColor(255, 50, 50, 255);
	Label->SetAlign(0.5f, 0.5f);
	Label->SetSize(400.f, 30.f);


	m_PixelName = Category->CreateWidget<CEditorInput>("ColliderPixel", "ColliderName");

	Line = Category->CreateWidget<CEditorSameLine>("ColliderPixel", "Line");

	Line->SetSpacing(30.f);

	Label = Category->CreateWidget<CEditorLabel>("ColliderPixel", "Color Collision");
	Label->SetColor(255, 0, 0, 255);
	Label->SetAlign(0.5f, 0.5f);
	Label->SetSize(200.f, 26.f);


	m_PixelRed = Category->CreateWidget<CEditorInput>("ColliderPixel", "RED");
	m_PixelRed->SetInputType(EImGuiInputType::Int);

	Line = Category->CreateWidget<CEditorSameLine>("ColliderPixel", "Line");

	Line->SetSpacing(102.5f);

	m_PixelColorIgnore = Category->CreateWidget<CEditorCheckBox>("ColliderPixel", "Ignore");

	Line = Category->CreateWidget<CEditorSameLine>("ColliderPixel", "Line");

	Line->SetSpacing(10.f);

	m_PixelColorConfirm = Category->CreateWidget<CEditorCheckBox>("ColliderPixel", "Confirm");

	m_PixelGreen = Category->CreateWidget<CEditorInput>("ColliderPixel", "GREEN");
	m_PixelGreen->SetInputType(EImGuiInputType::Int);

	Line = Category->CreateWidget<CEditorSameLine>("ColliderPixel", "Line");

	Line->SetSpacing(82.f);

	Label = Category->CreateWidget<CEditorLabel>("ColliderPixel", "Alpha Collision");
	Label->SetColor(255, 0, 0, 255);
	Label->SetAlign(0.5f, 0.5f);
	Label->SetSize(200.f, 26.f);

	m_PixelBlue = Category->CreateWidget<CEditorInput>("ColliderPixel", "BLUE");
	m_PixelBlue->SetInputType(EImGuiInputType::Int);

	Line = Category->CreateWidget<CEditorSameLine>("ColliderPixel", "Line");

	Line->SetSpacing(92.5f);

	m_PixelAlphaIgnore = Category->CreateWidget<CEditorCheckBox>("ColliderPixel", "Ignore");

	Line = Category->CreateWidget<CEditorSameLine>("ColliderPixel", "Line");

	Line->SetSpacing(10.f);

	m_PixelAlphaConfirm = Category->CreateWidget<CEditorCheckBox>("ColliderPixel", "Confirm");


	m_PixelAlpha = Category->CreateWidget<CEditorInput>("ColliderPixel", "Alpha");
	m_PixelAlpha->SetInputType(EImGuiInputType::Int);


	Label = Category->CreateWidget<CEditorLabel>("ColliderPixel", "Default Channel");

	Label->SetColor(50, 50, 50, 255);
	Label->SetAlign(0.5f, 0.5f);
	Label->SetSize(130.f, 30.f);

	Line = Category->CreateWidget<CEditorSameLine>("ColliderPixel", "Line");

	Line->SetSpacing(50.f);

	Label = Category->CreateWidget<CEditorLabel>("ColliderPixel", "Player Channel");

	Label->SetColor(50, 50, 50, 255);
	Label->SetAlign(0.5f, 0.5f);
	Label->SetSize(130.f, 30.f);

	Line = Category->CreateWidget<CEditorSameLine>("ColliderPixel", "Line");

	Line->SetSpacing(50.f);

	Label = Category->CreateWidget<CEditorLabel>("ColliderPixel", "Monster Channel");

	Label->SetColor(50, 50, 50, 255);
	Label->SetAlign(0.5f, 0.5f);
	Label->SetSize(130.f, 30.f);


	m_PixelDefaultChannelCheck = Category->CreateWidget<CEditorCheckBox>("ColliderPixel", "Default");

	Line = Category->CreateWidget<CEditorSameLine>("ColliderPixel", "Line");

	Line->SetSpacing(97.f);

	m_PixelPlayerChannelCheck = Category->CreateWidget<CEditorCheckBox>("ColliderPixel", "Player");

	Line = Category->CreateWidget<CEditorSameLine>("ColliderPixel", "Line");

	Line->SetSpacing(103.f);

	m_PixelMonsterChannelCheck = Category->CreateWidget<CEditorCheckBox>("ColliderPixel", "Monster");


	m_PixelMouseChannelCheck = Category->CreateWidget<CEditorCheckBox>("ColliderPixel", "Mouse");


	Line = Category->CreateWidget<CEditorSameLine>("ColliderPixel", "Line");

	Line->SetSpacing(104.f);

	m_PixelPlayerAttackChannelCheck = Category->CreateWidget<CEditorCheckBox>("ColliderPixel", "PlayerAttack");

	Line = Category->CreateWidget<CEditorSameLine>("ColliderPixel", "Line");

	Line->SetSpacing(56.f);

	m_PixelMonsterAttackChannelCheck = Category->CreateWidget<CEditorCheckBox>("ColliderPixel", "MonsterAttack");

	Label = Category->CreateWidget<CEditorLabel>("ColliderPixel", "Ignore Channel");
	Label->SetColor(255, 50, 50, 255);
	Label->SetAlign(0.5f, 0.5f);
	Label->SetSize(400.f, 30.f);

	m_PixelIgnoreList = Category->CreateWidget<CEditorListBox>("ColliderPixel", "");
	m_PixelIgnoreList->SetSizeX(200.f);
	m_PixelIgnoreList->SetPageItemCount(3);

	return true;
}

void CColliderPixelWidgetList::Render()
{
	CComponentWidgetList::Render();
}

void CColliderPixelWidgetList::SetAddColiderList(const std::string& Name)
{
	m_PixelColliderList->AddItem(Name);
}

void CColliderPixelWidgetList::ColliderListClickCallBack(int Index, const std::string& Item)
{
	m_SelectListItem = Item;

	CSceneComponent* Component = m_DetailWindow->GetSelectComponent();

	if (Component->GetComponentTypeName() == m_SelectListItem)
	{
		if (m_SelectListItem == "ColliderPixel")
		{
			CColliderPixel* Pixel = (CColliderPixel*)Component;

			m_PixelName->SetText("Pixel");
			m_PixelName->ReadOnly(true);

			const PixelInfo Info = Pixel->GetInfo();

			m_PixelRed->SetInt(Info.TypeColor[0]);
			m_PixelGreen->SetInt(Info.TypeColor[1]);
			m_PixelBlue->SetInt(Info.TypeColor[2]);
			m_PixelAlpha->SetInt(Info.TypeColor[3]);

			if (Info.PixelColorCollisionType == EPixelCollision_Type::Color_Confirm)
			{
				m_PixelColorConfirm->SetTrue(true);
			}

			else if (Info.PixelColorCollisionType == EPixelCollision_Type::Color_Ignore)
			{
				m_PixelColorIgnore->SetTrue(true);
			}

			if (Info.PixelColorCollisionType == EPixelCollision_Type::Alpha_Confirm)
			{
				m_PixelAlphaConfirm->SetTrue(true);
			}

			else if (Info.PixelColorCollisionType == EPixelCollision_Type::Alpha_Ignore)
			{
				m_PixelAlphaIgnore->SetTrue(true);
			}

			if (Pixel->GetCollisionProfile()->Channel->Name == "Default")
			{
				m_PixelDefaultChannelCheck->SetTrue(true);
			}

			if (Pixel->GetCollisionProfile()->Channel->Name == "Mouse")
			{
				m_PixelMouseChannelCheck->SetTrue(true);
			}

			if (Pixel->GetCollisionProfile()->Channel->Name == "Player")
			{
				m_PixelPlayerChannelCheck->SetTrue(true);

				m_PixelIgnoreList->AddItem("Player");
				m_PixelIgnoreList->AddItem("PlayerAttack");
			}

			if (Pixel->GetCollisionProfile()->Channel->Name == "Monster")
			{
				m_PixelMonsterChannelCheck->SetTrue(true);
				m_PixelIgnoreList->AddItem("Monster");
				m_PixelIgnoreList->AddItem("MonsterAttack");
			}

			if (Pixel->GetCollisionProfile()->Channel->Name == "PlayerAttack")
			{
				m_PixelPlayerAttackChannelCheck->SetTrue(true);
				m_PixelIgnoreList->AddItem("Player");
				m_PixelIgnoreList->AddItem("PlayerAttack");

			}

			if (Pixel->GetCollisionProfile()->Channel->Name == "MonsterAttack")
			{
				m_PixelMonsterAttackChannelCheck->SetTrue(true);
				m_PixelIgnoreList->AddItem("Monster");
				m_PixelIgnoreList->AddItem("MonsterAttack");
			}
		}
	}

	else if ("새로고침" == m_SelectListItem)
	{
		Clear();
		
	}
}

void CColliderPixelWidgetList::ColliderClickButton()
{
	CSceneComponent* Component = m_DetailWindow->GetSelectComponent();

	if (Component->GetComponentTypeName() == m_SelectListItem)
	{
		CColliderPixel* Pixel = (CColliderPixel*)Component;


		unsigned int R, G, B, A;

		R = m_PixelRed->GetInt();
		G = m_PixelGreen->GetInt();
		B = m_PixelBlue->GetInt();
		A = m_PixelAlpha->GetInt();

		Pixel->SetPixelColor(R, G, B);
		Pixel->SetPixelAlpha(A);


		if (m_PixelColorIgnore->GetTrue())
		{
			Pixel->SetPixelColorCollisionType(EPixelCollision_Type::Color_Ignore);
		}

		if (m_PixelColorConfirm->GetTrue())
		{
			Pixel->SetPixelColorCollisionType(EPixelCollision_Type::Color_Confirm);
		}

		if (m_PixelAlphaIgnore->GetTrue())
		{
			Pixel->SetPixelAlphaCollisionType(EPixelCollision_Type::Alpha_Ignore);
		}

		if (m_PixelAlphaConfirm->GetTrue())
		{
			Pixel->SetPixelAlphaCollisionType(EPixelCollision_Type::Alpha_Confirm);
		}


		if (m_PixelDefaultChannelCheck->GetTrue())
		{
			Pixel->SetCollisionProfile("Default");
		}

		if (m_PixelMouseChannelCheck->GetTrue())
		{
			Pixel->SetCollisionProfile("Mouse");
		}

		if (m_PixelPlayerChannelCheck->GetTrue())
		{
			Pixel->SetCollisionProfile("Player");
		}

		if (m_PixelMonsterChannelCheck->GetTrue())
		{
			Pixel->SetCollisionProfile("Monster");
		}

		if (m_PixelPlayerAttackChannelCheck->GetTrue())
		{
			Pixel->SetCollisionProfile("PlayerAttack");
		}

		if (m_PixelMonsterAttackChannelCheck->GetTrue())
		{
			Pixel->SetCollisionProfile("MonsterAttack");
		}

		m_PixelIgnoreList->Clear();
	}
}

void CColliderPixelWidgetList::ColliderCancelButton()
{
}

void CColliderPixelWidgetList::Clear()
{
	m_PixelRed->SetInt(0);
	m_PixelBlue->SetInt(0);
	m_PixelGreen->SetInt(0);
	m_PixelAlpha->SetInt(0);

	m_PixelColorIgnore->SetTrue(false);
	m_PixelColorConfirm->SetTrue(false);

	m_PixelAlphaIgnore->SetTrue(false);
	m_PixelAlphaConfirm->SetTrue(false);

	m_PixelIgnoreList->Clear();

	m_PixelDefaultChannelCheck->SetTrue(false);
	m_PixelPlayerChannelCheck->SetTrue(false);
	m_PixelMouseChannelCheck->SetTrue(false);
	m_PixelMonsterChannelCheck->SetTrue(false);
	m_PixelMonsterAttackChannelCheck->SetTrue(false);
	m_PixelPlayerAttackChannelCheck->SetTrue(false);
}
