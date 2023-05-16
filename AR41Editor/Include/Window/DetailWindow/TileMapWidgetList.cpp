#include "TileMapWidgetList.h"
#include "Editor/EditorTree.h"
#include "Editor/EditorButton.h"
#include "Editor/EditorSameLine.h"
#include "Editor/EditorImage.h"
#include "Editor/EditorInput.h"
#include "Editor/EditorListBox.h"
#include "Editor/EditorCheckBox.h"
#include "Editor/EditorComboBox.h"
#include "../Animation2DWindow.h"
#include "Editor/EditorGUIManager.h"
#include "../DetailWindow.h"
#include "Component/SpriteComponent.h"
#include "Component/CameraComponent.h"
#include "Animation/Animation2D.h"
#include "Resource/ResourceManager.h"
#include "Resource/Animation/AnimationManager.h"
#include "Resource/Animation/AnimationSequence2D.h"
#include "Component/TileMapComponent.h"
#include "Input.h"
#include "../../Editor.h"
#include "Engine.h"
#include "Scene/SceneManager.h"
#include "Scene/Scene.h"
#include "Scene/CameraManager.h"
#include "Editor/EditorLabel.h"
#include "PathManager.h"

CTileMapWidgetList::CTileMapWidgetList()
{
}

CTileMapWidgetList::~CTileMapWidgetList()
{
}

void CTileMapWidgetList::SetTileMapComponent(CTileMapComponent* TileMap)
{
	m_TileMap = TileMap;
}

TCHAR* CTileMapWidgetList::StringToTCHAR(const std::string& Name)
{
	size_t origsize = 0, convertedChars = 0;
	origsize = strlen(Name.c_str()) + 1;
	wchar_t* t = new wchar_t[origsize];
	mbstowcs_s(&convertedChars, t, origsize, Name.c_str(), _TRUNCATE);

	return (TCHAR*)t;
}

bool CTileMapWidgetList::Init()
{
	CEditorTree<void*>* Category = CreateWidget<CEditorTree<void*>>("TileMapComponent");

	Category->SetHideName("TileMapComponent");

	Category->SetSize(400.f, 300.f);

	Category->AddItem(nullptr, "TileMapComponent");
	Category->AddItem(nullptr, "TileMap", "TileMapComponent");



	CEditorGroup* CreateGroup = Category->CreateWidget<CEditorGroup>("TileMap",
		"CreateGroup");

	CEditorLabel* Label = CreateGroup->CreateWidget<CEditorLabel>("Tile Shape");
	Label->SetSize(120.f, 30.f);
	Label->SetColor(200, 0, 0, 255);

	m_ShapeCombo = CreateGroup->CreateWidget<CEditorComboBox>("TileShape",
		120.f, 30.f);
	m_ShapeCombo->SetHideName("TileShape");
	m_ShapeCombo->AddItem("사각형");
	m_ShapeCombo->AddItem("마름모");
	m_ShapeCombo->Sort(false);
	m_ShapeCombo->SetSelectPrevViewName(true);
	m_ShapeCombo->SetSelect(1);
	m_ShapeCombo->SetPrevViewName("마름모");

	m_ShapeCombo->SetSelectCallback<CTileMapWidgetList>(this, &CTileMapWidgetList::SetShapeCallback);

	Label = CreateGroup->CreateWidget<CEditorLabel>("Tile Count");
	Label->SetSize(120.f, 30.f);
	Label->SetColor(200, 0, 0, 255);

	m_CountX = CreateGroup->CreateWidget<CEditorInput>("CountX", 100.f, 30.f);
	m_CountX->SetInputType(EImGuiInputType::Int);

	m_CountX->SetInt(100);

	

	m_CountY = CreateGroup->CreateWidget<CEditorInput>("CountY", 100.f, 30.f);
	m_CountY->SetInputType(EImGuiInputType::Int);

	m_CountY->SetInt(100);

	

	Label = CreateGroup->CreateWidget<CEditorLabel>("Tile Size");
	Label->SetSize(120.f, 30.f);
	Label->SetColor(200, 0, 0, 255);

	m_TileSizeX = CreateGroup->CreateWidget<CEditorInput>("SizeX", 100.f, 30.f);
	m_TileSizeX->SetInputType(EImGuiInputType::Float);

	m_TileSizeX->SetFloat(160.f);



	m_TileSizeY = CreateGroup->CreateWidget<CEditorInput>("SizeY", 100.f, 30.f);
	m_TileSizeY->SetInputType(EImGuiInputType::Float);

	m_TileSizeY->SetFloat(80.f);

	CEditorButton* Button = CreateGroup->CreateWidget<CEditorButton>("CreateTileMap", 150.f, 40.f);

	Button->SetClickCallback<CTileMapWidgetList>(this, &CTileMapWidgetList::CreateTileMapClick);

	Category->CreateWidget<CEditorSameLine>("TileMap", "Line");

	CEditorGroup* EditGroup = Category->CreateWidget<CEditorGroup>("TileMap",
		"EditGroup");

	Label = EditGroup->CreateWidget<CEditorLabel>("Option Select");
	Label->SetSize(120.f, 30.f);
	Label->SetColor(200, 0, 0, 255);

	m_TileEditCombo = EditGroup->CreateWidget<CEditorComboBox>("EditMode",
		120.f, 30.f);
	m_TileEditCombo->SetHideName("EditMode");
	m_TileEditCombo->AddItem("이미지");
	m_TileEditCombo->AddItem("옵션");
	m_TileEditCombo->AddItem("이미지 지우기");
	m_TileEditCombo->Sort(false);
	m_TileEditCombo->SetSelectPrevViewName(true);
	m_TileEditCombo->SetSelect(1);
	m_TileEditCombo->SetPrevViewName("옵션");

	m_TileEditCombo->SetSelectCallback<CTileMapWidgetList>(this, &CTileMapWidgetList::SetEditModeCallback);

	EditGroup->CreateWidget<CEditorSameLine>("Line");

	m_TileOptionCombo = EditGroup->CreateWidget<CEditorComboBox>("TileOption",
		120.f, 30.f);
	m_TileOptionCombo->SetHideName("TileOption");
	m_TileOptionCombo->AddItem("일반");
	m_TileOptionCombo->AddItem("이동불가");
	m_TileOptionCombo->Sort(false);
	m_TileOptionCombo->SetSelectPrevViewName(true);
	m_TileOptionCombo->SetSelect(0);
	m_TileOptionCombo->SetPrevViewName("일반");

	//m_TileEditCombo->SetSelectCallback<CTileMapWidgetList>(this, &CTileMapWidgetList::SetEditModeCallback);


	Label = EditGroup->CreateWidget<CEditorLabel>("Tile FrameList");
	Label->SetSize(120.f, 30.f);
	Label->SetColor(200, 0, 0, 255);

	m_TileFrameList = EditGroup->CreateWidget<CEditorListBox>("FrameList",
		150.f, 400.f);
	m_TileFrameList->SetPageItemCount(5);
	m_TileFrameList->SetHideName("FrameList");



	m_TileFrameList->Sort(false);

	m_TileFrameList->SetSelectCallback<CTileMapWidgetList>(this, &CTileMapWidgetList::SetFrameListCallback);

	m_FrameTileFolderName = EditGroup->CreateWidget<CEditorInput>("FolderName");
	m_FrameTileFolderName->SetInputType(EImGuiInputType::String);

	m_FrameTileImageName = EditGroup->CreateWidget<CEditorInput>("ImageName");
	m_FrameTileImageName->SetInputType(EImGuiInputType::String);

	m_FrameTileCount = EditGroup->CreateWidget<CEditorInput>("FrameCount");
	m_FrameTileCount->SetInputType(EImGuiInputType::Int);

	Label = EditGroup->CreateWidget<CEditorLabel>("이미지 미리보기");
	Label->SetSize(120.f, 30.f);
	Label->SetColor(200, 0, 0, 255);

	m_TileFrameImage = EditGroup->CreateWidget<CEditorImage>("TileFrameImage");

	Button = CreateGroup->CreateWidget<CEditorButton>("타일 이미지 불러오기", 150.f, 40.f);

	Button->SetClickCallback<CTileMapWidgetList>(this, &CTileMapWidgetList::SetTileTextureButton);

	Button = CreateGroup->CreateWidget<CEditorButton>("타일 프레임 불러오기", 150.f, 40.f);

	Button->SetClickCallback<CTileMapWidgetList>(this, &CTileMapWidgetList::SetTileArrayTextureButton);

	Button = CreateGroup->CreateWidget<CEditorButton>("타일 전체 지우기 ", 150.f, 40.f);

	Button->SetClickCallback<CTileMapWidgetList>(this, &CTileMapWidgetList::TileAllDeleteButton);

	Button = CreateGroup->CreateWidget<CEditorButton>("배경 이미지 변경하기", 150.f, 40.f);
	Button->SetClickCallback<CTileMapWidgetList>(this, &CTileMapWidgetList::TileBackTextureChangeButton);

	return true;
}

void CTileMapWidgetList::Render()
{
	CComponentWidgetList::Render();

	if (GetAsyncKeyState('W') & 0x8000)
	{
		CCameraComponent* Camera = CSceneManager::GetInst()->GetScene()->GetCameraManager()->GetCurrentCamera();

		Camera->AddWorldPositionY(500.f * g_DeltaTime);
	}

	if (GetAsyncKeyState('S') & 0x8000)
	{
		CCameraComponent* Camera = CSceneManager::GetInst()->GetScene()->GetCameraManager()->GetCurrentCamera();

		Camera->AddWorldPositionY(-500.f * g_DeltaTime);
	}

	if (GetAsyncKeyState('D') & 0x8000)
	{
		CCameraComponent* Camera = CSceneManager::GetInst()->GetScene()->GetCameraManager()->GetCurrentCamera();

		Camera->AddWorldPositionX(500.f * g_DeltaTime);
	}

	if (GetAsyncKeyState('A') & 0x8000)
	{
		CCameraComponent* Camera = CSceneManager::GetInst()->GetScene()->GetCameraManager()->GetCurrentCamera();

		Camera->AddWorldPositionX(-500.f * g_DeltaTime);
	}

	// 마우스의 월드위치를 얻어온다.
	Vector2 Pos = CInput::GetInst()->GetMouseWorldPos();

	int	Index = m_TileMap->GetTileIndex(Pos);

	m_TileMap->SetEditorMouseOnTile(Index);

	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		switch ((ETileEditMode)m_TileEditCombo->GetSelectIndex())
		{
		case ETileEditMode::Image:			
			m_TileMap->ChangeTileFrame(Pos, m_TileFrameList->GetSelectIndex());
			break;

		case ETileEditMode::Option:
			m_TileMap->ChangeTileOption(Pos, (ETileOption)m_TileOptionCombo->GetSelectIndex());
			break;

		case ETileEditMode::ImageDelete:
			m_TileMap->DeleteTile(Pos);
			break;
		}
	}
}

void CTileMapWidgetList::CreateTileMapClick()
{	
	//m_TileMap->SetTileBackTextureFullPath("Default", TEXT("Henesis.png"));

	m_TileMap->CreateTile((ETileShape)m_ShapeCombo->GetSelectIndex(),
		m_CountX->GetInt(), m_CountY->GetInt(),
		Vector2(m_TileSizeX->GetFloat(), m_TileSizeY->GetFloat()));

	CTexture* Texture = m_TileMap->GetTileMaterial()->GetTexture(0);

	m_TileFrameImage->SetTexture(Texture);

	m_TileFrameImage->SetImageStart(0.f, 0.f);
	m_TileFrameImage->SetImageEnd(m_TileSizeX->GetFloat(), m_TileSizeY->GetFloat());	

	//m_TileMap->SetTileBaseColor(Vector4(1.f, 0.f, 0.f, 1.f));
}

void CTileMapWidgetList::SetShapeCallback(int Index, const std::string& Item)
{
}

void CTileMapWidgetList::SetEditModeCallback(int Index, const std::string& Item)
{

}

void CTileMapWidgetList::SetFrameListCallback(int Index, const std::string& Item)
{
	CMaterial* Material = m_TileMap->GetTileMaterial();

	Material->GetTexture()->GetImageType();

		if (Material->GetTexture()->GetImageType() == EImageType::Frame)
		{
			m_TileFrameImage->SetImageIndex(Index);
		}
}

void CTileMapWidgetList::SetTileTextureButton()
{
	OPENFILENAME ofn = { };

	TCHAR	FullPath[MAX_PATH] = {};
	TCHAR	InitPath[MAX_PATH] = {};

	TCHAR	Filter[] = TEXT("모든파일\0*.*\0PNG\0*.png\0JPG\0*.jpg\0BMP\0*.bmp");

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = CEngine::GetInst()->GetWindowHandle();
	ofn.lpstrFilter = Filter;
	ofn.lpstrFile = FullPath;
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrInitialDir = CPathManager::GetInst()->FindPath(TEXTURE_PATH)->Path;


	if (GetOpenFileName(&ofn) != 0)
	{
			TCHAR wTexName[256] = {};

			_wsplitpath_s(FullPath, 0, 0, 0, 0, wTexName, 256, 0, 0);

			char TexName[256] = {};

			int Length = (int)WideCharToMultiByte(CP_ACP, 0, wTexName, -1, nullptr, 0, nullptr, nullptr);

			WideCharToMultiByte(CP_ACP, 0, wTexName, -1, TexName, Length, nullptr, nullptr);
			

			const std::string Name = (const std::string)TexName;

			CMaterial* Material = m_TileMap->GetTileMaterial();

			Material->SetTextureFullPath(0, 0, (int)EShaderBufferType::Pixel, TexName, FullPath);

			//Material = m_TileMap->GetMaterial(0);

			CTexture* Texture = m_TileMap->GetTileMaterial()->GetTexture(0);

			m_TileFrameImage->SetTexture(Texture);

			m_TileFrameImage->SetImageStart(0.f, 0.f);
			m_TileFrameImage->SetImageEnd(m_TileSizeX->GetFloat(), m_TileSizeY->GetFloat());
			
	}
}

void CTileMapWidgetList::SetTileArrayTextureButton()
{
	std::string FullName = m_FrameTileFolderName->GetText();

	std::string FileFullName = FullName + '/' + m_FrameTileImageName->GetText() + "%d.png";

	TCHAR* RealName = StringToTCHAR(FileFullName);

	std::vector<const TCHAR*> vecFileName;

	for (int i = 0; i < m_FrameTileCount->GetInt(); ++i)
	{
		TCHAR* FileName = new TCHAR[MAX_PATH];

		memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);

		wsprintf(FileName, RealName, i);

		vecFileName.push_back(FileName);
	}

	CMaterial* Material = m_TileMap->GetTileMaterial();
	Material->SetTextureArray(0, 10, (int)EShaderBufferType::Pixel, m_FrameTileFolderName->GetText(), vecFileName);

	SAFE_DELETE(RealName);

	for (int i = 0; i <= m_FrameTileCount->GetInt() - 1; ++i)
	{
		SAFE_DELETE_ARRAY(vecFileName[i]);
	}

	vecFileName.clear();

	for (int i = 0; i <= m_FrameTileCount->GetInt(); ++i)
	{
		char	Number[32] = {};

		_itoa_s(i, Number, 10);

		m_TileFrameList->AddItem(Number);
	}

}

void CTileMapWidgetList::TileAllDeleteButton()
{
	m_TileMap->DeleteAllTile();
}

void CTileMapWidgetList::TileBackTextureChangeButton()
{
	OPENFILENAME ofn = { };

	TCHAR	FullPath[MAX_PATH] = {};
	TCHAR	InitPath[MAX_PATH] = {};

	TCHAR	Filter[] = TEXT("모든파일\0*.*\0PNG\0*.png\0JPG\0*.jpg\0BMP\0*.bmp");

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = CEngine::GetInst()->GetWindowHandle();
	ofn.lpstrFilter = Filter;
	ofn.lpstrFile = FullPath;
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrInitialDir = CPathManager::GetInst()->FindPath(TEXTURE_PATH)->Path;


	if (GetOpenFileName(&ofn) != 0)
	{
		TCHAR wTexName[256] = {};

		_wsplitpath_s(FullPath, 0, 0, 0, 0, wTexName, 256, 0, 0);

		char TexName[256] = {};

		int Length = (int)WideCharToMultiByte(CP_ACP, 0, wTexName, -1, nullptr, 0, nullptr, nullptr);

		WideCharToMultiByte(CP_ACP, 0, wTexName, -1, TexName, Length, nullptr, nullptr);


		const std::string Name = (const std::string)TexName;

		CMaterial* Material = m_TileMap->GetMaterial(0);

		Material->SetTextureFullPath(0, 0, (int)EShaderBufferType::Pixel, TexName, FullPath);

		//Material = m_TileMap->GetMaterial(0);

		CTexture* Texture = m_TileMap->GetTileMaterial()->GetTexture(0);

		m_TileFrameImage->SetTexture(Texture);

		m_TileFrameImage->SetImageStart(0.f, 0.f);
		m_TileFrameImage->SetImageEnd((float)(Texture->GetWidth()), (float)(Texture->GetHeight()));

	}
}
