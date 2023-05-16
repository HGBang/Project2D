#include "TextureWindow.h"
#include "Editor/EditorButton.h"
#include "Editor/EditorSameLine.h"
#include "Editor/EditorLabel.h"
#include "Editor/EditorImage.h"
#include "Editor/EditorText.h"
#include "Editor/EditorInput.h"
#include "Editor/EditorListBox.h"
#include "Editor/EditorComboBox.h"
#include "Editor/EditorTree.h"
#include "PathManager.h"
#include "Scene/SceneManager.h"
#include "Scene/Scene.h"
#include "../GameObject/Monster.h"
#include "../GameObject/Player2D.h"
#include "ObjectWindow.h"
#include "ComponentWindow.h"
#include "Editor/EditorGUIManager.h"

#include "Component/SpriteComponent.h"
#include "Component/CameraComponent.h"
#include "Component/TargetArm.h"

#include "Component/Component.h"
#include "TransformWindow.h"
#include "Editor/EditorGUIManager.h"
#include "Component/SceneComponent.h"
#include "Component/PrimitiveComponent.h"
#include "Resource/Material/Material.h"
#include "DetailWindow.h"
#include "Resource/Material/Material.h"
#include "Resource/Material/MaterialManager.h"
#include "Resource/Texture/Texture.h"
#include "Resource/Texture/TextureManager.h"

static float i1;
static float i2;
static float i3;
static float i4;

CTextureWindow::CTextureWindow()
{
}

CTextureWindow::~CTextureWindow()
{
}

bool CTextureWindow::Init()
{



	CEditorLabel* Label = CreateWidget<CEditorLabel>("TextureWindow");

	Label->SetColor(255, 0, 0, 255);
	Label->SetAlign(0.5f, 0.5f);
	Label->SetSizeY(30.f);
	Label->SetSizeX(150.f);

	CEditorSameLine* Line = CreateWidget<CEditorSameLine>("Line");

	CEditorButton* Button = CreateWidget<CEditorButton>("이미지변경", 150.f, 30.f);

	Button->SetColor(29, 47, 73, 255);
	Button->SetClickCallback<CTextureWindow>(this, &CTextureWindow::TextureCreateCallback);

	m_TextureList = CreateWidget<CEditorListBox>("TextureListBox");

	m_TextureList->SetHideName("TextureListBox");

	m_TextureList->SetSize(200.f, 300.f);
	m_TextureList->SetPageItemCount(6);
	m_TextureList->SetSelectCallback<CTextureWindow>(this, &CTextureWindow::TextureClickCallback);

	Line = CreateWidget<CEditorSameLine>("Line");


	m_Texture = CreateWidget<CEditorImage>(m_SelectTextureItem);

	CEditorButton* Button1 = CreateWidget<CEditorButton>("BaseColor 변경");


	Button1->SetSize(300.f, 30.f);
	Button1->SetClickCallback<CTextureWindow>(this, &CTextureWindow::TextureColorCallback);

	i1 = 0.f;
	i2 = 0.f;
	i3 = 0.f;
	i4 = 0.f;

	LoadGameTextureName();

	
	return true;
}

void CTextureWindow::Update(float DeltaTime)
{
	CEditorWindow::Update(DeltaTime);
			
	ImGui::SliderFloat("R", &i1, 0.f, 255.f, "Red = %.0f");

	ImGui::SliderFloat("G", &i2, 0.f, 255.f, "Green = %.0f");

	ImGui::SliderFloat("B", &i3, 0.f, 255.f, "Blue = %.0f");

	ImGui::SliderFloat("Alpha", &i4, 0.f, 255.f, "Alpha = %.0f");

	
}

void CTextureWindow::TextureClickCallback(int Index, const std::string& Item)
{
	

		m_SelectTextureItem = Item;
			
		m_Texture->SetTexture(m_SelectTextureItem);
					
		
}

void CTextureWindow::TextureCreateCallback()
{
	CTransformWindow* TransformWindow = CEditorGUIManager::GetInst()->FindEditorWindow<CTransformWindow>("TransformWindow");

	CComponentWindow* ComponentWindow = CEditorGUIManager::GetInst()->FindEditorWindow<CComponentWindow>("ComponentWindow");

	CObjectWindow* ObjectWindow = CEditorGUIManager::GetInst()->FindEditorWindow<CObjectWindow>("ObjectWindow");

	const std::string TextureName = GetSelectTextureItem();

	CComponent* m_SelectComponent = ComponentWindow->GetSelectComponent();

	const std::string fileName = TextureName + "png";

	CScene* Scene = CSceneManager::GetInst()->GetScene();

	CGameObject* Object = ObjectWindow->GetSelectObject();

	if (Object->GetName() == "Player2D")
	{

		if (m_SelectComponent)
		{


			if (TextureName.length())
			{
				CPrimitiveComponent* PrimitiveComponent = (CPrimitiveComponent*)m_SelectComponent;
				
				//CMaterial* Material = CMaterialManager::CreateMaterial<CMaterial>();

				CMaterial* Material = PrimitiveComponent->GetMaterial(0);
						
							

				//CMaterial* Material = CreateMaterial<CMaterial>("DefaultTexture");
			
				
				Material->AddTexture(0, (int)EShaderBufferType::Pixel, TextureName, (TCHAR*)&fileName);
												
				Material->SetBaseColor(1.f, 1.f, 1.f, 1.f);

				Material->SetScene(Scene);
				
			
				//Material->SetTexture(0, (int)EShaderBufferType::Pixel, TextureName, Scene->GetResource()->FindTexture(TextureName));

				if (i1 > 0 || i2 > 0 || i3 > 0 || i4 > 0)
				{

					Material->SetBaseColorUnsignedChar((unsigned char)GetR(), (unsigned char)GetG(),
						(unsigned char)GetB(), (unsigned char)GetA());
							

				}


				/*	if (i1 > 0|| i2 > 0 || i3 > 0 || i4 > 0)
						{
							Material->SetBaseColorUnsignedChar((unsigned char)GetR(), (unsigned char)GetG(),
								(unsigned char)GetB(), (unsigned char)GetA());

						}*/


			}

		}
	}

	if (Object->GetName() == "Monster")
	{
		if (m_SelectComponent)
		{


			if (TextureName.length())
			{
				CPrimitiveComponent* PrimitiveComponent1 = (CPrimitiveComponent*)m_SelectComponent;
				CMaterial* Material1 = PrimitiveComponent1->GetMaterial(0);
				

				Material1->AddTexture(0, (int)EShaderBufferType::Pixel, TextureName, (TCHAR*)&fileName);


				if (i1 > 0 || i2 > 0 || i3 > 0 || i4 > 0)
				{

					Material1->SetBaseColorUnsignedChar((unsigned char)GetR(), (unsigned char)GetG(),
						(unsigned char)GetB(), (unsigned char)GetA());

				}


				/*	if (i1 > 0|| i2 > 0 || i3 > 0 || i4 > 0)
						{
							Material->SetBaseColorUnsignedChar((unsigned char)GetR(), (unsigned char)GetG(),
								(unsigned char)GetB(), (unsigned char)GetA());

						}*/


			}

		}
	}

	i1 = 0.f;
	i2 = 0.f;
	i3 = 0.f;
	i4 = 0.f;

	

}

void CTextureWindow::TextureColorCallback()
{
	TextureCreateCallback();
}

void CTextureWindow::LoadGameTextureName()
{
	const PathInfo* Info = CPathManager::GetInst()->FindPath(ROOT_PATH);

	char	Path[MAX_PATH] = {};

	strcpy_s(Path, Info->PathMultibyte);

	int	Length = (int)strlen(Path);

	// Root Path에서 Bin\을 지워준다.
	for (int i = Length - 2; i >= 0; --i)
	{
		if (Path[i] == '/' || Path[i] == '\\')
		{
			memset(&Path[i + 1], 0, sizeof(TCHAR) * (Length - i - 1));
			break;
		}
	}

	char	Directory[MAX_PATH] = {};

	strcpy_s(Directory, Path);

	// Editor의 GameObject폴더에 있는 파일을 읽어온다.
	strcat_s(Directory, "Bin/Texture/");

	for (const auto& file : std::filesystem::directory_iterator(Directory))
	{
		char	Name[64] = {};
		char	FullPath[MAX_PATH] = {};
		char	Ext[_MAX_EXT] = {};

		strcpy_s(FullPath, file.path().generic_string().c_str());

		_splitpath_s(FullPath, nullptr, 0, nullptr, 0, Name, 64, Ext, _MAX_EXT);

		if (strcmp(Ext, ".cpp") == 0)
			continue;

		else if (strcmp(Name, "Decal") == 0 ||
			strcmp(Name, "Diablos_Lair_Floor_TRS") == 0 ||
			strcmp(Name, "Explosion") == 0 ||
			strcmp(Name, "LandScape") == 0 ||
			strcmp(Name, "Mouse") == 0 ||
			strcmp(Name, "Monster") == 0 ||
			strcmp(Name, "Particle") == 0 || 
			strcmp(Name, "Sky") == 0)
			continue;

		m_TextureList->AddItem(Name);
	}

}

float CTextureWindow::GetR()
{
	return i1;
}

float CTextureWindow::GetG()
{
	return i2;
}

float CTextureWindow::GetB()
{
	return i3;
}

float CTextureWindow::GetA()
{
	return i4;
}
