#include "DetailWindow.h"
#include "Editor/EditorWidget.h"
#include "Editor/EditorWindow.h"
#include "Editor/EditorButton.h"
#include "Editor/EditorSameLine.h"
#include "Editor/EditorLabel.h"
#include "Editor/EditorImage.h"
#include "Editor/EditorText.h"
#include "Editor/EditorTree.h"
#include "Editor/EditorInput.h"
#include "Editor/EditorListBox.h"
#include "Editor/EditorComboBox.h"
#include "Editor/EditorCheckBox.h"
#include "Editor/EditorSliderBar.h"
#include "Component/SceneComponent.h"
#include "Component/SpriteComponent.h"
#include "Component/TargetArm.h"
#include "Component/CameraComponent.h"
#include "Component/Collider.h"
#include "Component/Collider2D.h"
#include "Component/ColliderBox2D.h"
#include "Component/ColliderSphere2D.h"
#include "Component/ColliderOBB2D.h"
#include "Component/ColliderPixel.h"
#include "Component/TileMapComponent.h"
#include "PathManager.h"
#include "Engine.h"

#include "AnimationWindow.h"
#include "Editor/EditorGUIManager.h"
#include "Resource/ResourceManager.h"

#include "DetailWindow/CameraWidgetList.h"
#include "DetailWindow/ComponentWidgetList.h"
#include "DetailWindow/SceneComponentWidgetList.h"
#include "DetailWindow/SpriteComponentWidgetList.h"
#include "DetailWindow/TargetArmWidgetList.h"
#include "DetailWindow/PrimitiveWidgetList.h"
#include "DetailWindow/ColliderBox2DWidgetList.h"
#include "DetailWindow/ColliderOBB2DWidgetList.h"
#include "DetailWindow/ColliderSphere2DWidgetList.h"
#include "DetailWindow/ColliderPixelWidgetList.h"
#include "DetailWindow/TileMapWidgetList.h"

CDetailWindow::CDetailWindow()
{
}

CDetailWindow::~CDetailWindow()
{
	ClearWidget();

	size_t	Size = m_vecComponentWidgetList.size();

	for (size_t i = 0; i < Size; ++i)
	{
		AddWidget(m_vecComponentWidgetList[i]);
	}
}

CComponentWidgetList* CDetailWindow::GetComponentWidgetList(const std::string& Name)
{
	size_t	Size = m_vecComponentWidgetList.size();

	for (size_t i = 0; i < Size; ++i)
	{
		if (m_vecComponentWidgetList[i]->GetName() == Name)
			return m_vecComponentWidgetList[i];
	}

	return nullptr;
}

void CDetailWindow::SetSelectComponent(CSceneComponent* Component)
{
	if (m_SelectComponent && Component)
	{
		if (m_SelectComponent != Component)
		{
			ClearWidget();

			ChangeWidget(Component);
		}
	}
	m_SelectComponent = Component;
}

bool CDetailWindow::Init()
{
	m_vecComponentWidgetList.resize((size_t)ESceneComponentType::Max);

	for (int i = 0; i < (int)ESceneComponentType::Max; ++i)
	{
		CreateEditorWidgetList((ESceneComponentType)i);
	}

	ClearWidget();

	return true;
}

void CDetailWindow::Update(float DeltaTime)
{
	CEditorWindow::Update(DeltaTime);	

	if (m_SelectComponent)
	{
		if (!m_SelectComponent->GetActive())
		{
			m_SelectComponent = nullptr;
			ClearWidget();
		}
	}

}

void CDetailWindow::ChangeWidget(CSceneComponent* Component)
{

	if (Component->GetComponentTypeName() == "SceneComponent")
	{
		AddWidget(m_vecComponentWidgetList[(int)ESceneComponentType::Scene]);
	}

	if (Component->GetComponentTypeName() == "SpriteComponent")
	{
		AddWidget(m_vecComponentWidgetList[(int)ESceneComponentType::Sprite]);

	/*	((CSpriteComponentWidgetList*)m_vecComponentWidgetList[(int)ESceneComponentType::Sprite])->
			SetSpriteContent((CSpriteComponent*)Component);*/
	}

	if (Component->GetComponentTypeName() == "ColliderBox2D")
	{
		AddWidget(m_vecComponentWidgetList[(int)ESceneComponentType::Box2D]);

		((CColliderBox2DWidgetList*)m_vecComponentWidgetList[(int)ESceneComponentType::Box2D])->SetAddColiderList("ColliderBox2D");
		((CColliderBox2DWidgetList*)m_vecComponentWidgetList[(int)ESceneComponentType::Box2D])->SetAddColiderList("새로고침");
	}

	if (Component->GetComponentTypeName() == "ColliderOBB2D")
	{
		AddWidget(m_vecComponentWidgetList[(int)ESceneComponentType::OBB2D]);

		((CColliderOBB2DWidgetList*)m_vecComponentWidgetList[(int)ESceneComponentType::OBB2D])->SetAddColiderList("ColliderOBB2D");
		((CColliderOBB2DWidgetList*)m_vecComponentWidgetList[(int)ESceneComponentType::OBB2D])->SetAddColiderList("새로고침");
	}

	if (Component->GetComponentTypeName() == "ColliderSphere2D")
	{
		AddWidget(m_vecComponentWidgetList[(int)ESceneComponentType::Sphere2D]);

		((CColliderSphere2DWidgetList*)m_vecComponentWidgetList[(int)ESceneComponentType::Sphere2D])->SetAddColiderList("ColliderSphere2D");
		((CColliderSphere2DWidgetList*)m_vecComponentWidgetList[(int)ESceneComponentType::Sphere2D])->SetAddColiderList("새로고침");
	}

	if (Component->GetComponentTypeName() == "ColliderPixel")
	{
		AddWidget(m_vecComponentWidgetList[(int)ESceneComponentType::Pixel]);

		((CColliderPixelWidgetList*)m_vecComponentWidgetList[(int)ESceneComponentType::Pixel])->SetAddColiderList("ColliderPixel");
		((CColliderPixelWidgetList*)m_vecComponentWidgetList[(int)ESceneComponentType::Pixel])->SetAddColiderList("새로고침");
	}

	if (Component->GetComponentTypeName() == "TargetArmComponent")
	{
		AddWidget(m_vecComponentWidgetList[(int)ESceneComponentType::TargetArm]);
	}

	if (Component->GetComponentTypeName() == "TileMapComponent")
	{
		AddWidget(m_vecComponentWidgetList[(int)ESceneComponentType::TileMap]);

		CTileMapWidgetList* TileMapWidget = (CTileMapWidgetList*)m_vecComponentWidgetList[(int)ESceneComponentType::TileMap];

		TileMapWidget->SetTileMapComponent((CTileMapComponent*)Component);
	}

}


void CDetailWindow::CreateEditorWidgetList(ESceneComponentType Type)
{
	CComponentWidgetList* WidgetList = nullptr;

	switch (Type)
	{
	case ESceneComponentType::Scene:
		WidgetList = CreateWidgetEmpty<CSceneComponentWidgetList>("SceneComponent");
		break;
	case ESceneComponentType::Primitive:
		WidgetList = CreateWidgetEmpty<CPrimitiveWidgetList>("PrimitiveComponent");
		break;
	case ESceneComponentType::Sprite:
		WidgetList = CreateWidgetEmpty<CSpriteComponentWidgetList>("SpriteComponent");
		break;
	case ESceneComponentType::Camera:
		WidgetList = CreateWidgetEmpty<CCameraWidgetList>("CameraComponent");
		break;
	case ESceneComponentType::Box2D:
		WidgetList = CreateWidgetEmpty<CColliderBox2DWidgetList>("ColliderBox2D");
		break;
	case ESceneComponentType::OBB2D:
		WidgetList = CreateWidgetEmpty<CColliderOBB2DWidgetList>("ColliderOBB2D");
		break;
	case ESceneComponentType::Sphere2D:
		WidgetList = CreateWidgetEmpty<CColliderSphere2DWidgetList>("ColliderSphere2D");
		break;
	case ESceneComponentType::Pixel:
		WidgetList = CreateWidgetEmpty<CColliderPixelWidgetList>("ColliderPixel");
		break;
	case ESceneComponentType::Collider:
		//WidgetList = CreateWidgetEmpty<CSceneComponentWidgetList>("SceneComponent");
		break;
	case ESceneComponentType::Collider2D:
		//WidgetList = CreateWidgetEmpty<CSceneComponentWidgetList>("SceneComponent");
		break;
	case ESceneComponentType::Collider3D:
		//WidgetList = CreateWidgetEmpty<CColliderBox2DWidgetList>("ColliderBox2D");
		break;
	case ESceneComponentType::TargetArm:
		//WidgetList = CreateWidgetEmpty<CSceneComponentWidgetList>("SceneComponent");
		break;
	case ESceneComponentType::TileMap:
		WidgetList = CreateWidgetEmpty<CTileMapWidgetList>("TileMapComponent");
		break;
	}

	if (!WidgetList)
		return;

	WidgetList->m_DetailWindow = this;

	m_vecComponentWidgetList[(int)Type] = WidgetList;
}
