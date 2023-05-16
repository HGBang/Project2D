#include "SpriteComponentWidgetList.h"
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
#include "Engine.h"

#include "Scene/Scene.h"
#include "Scene/SceneManager.h"


CSpriteComponentWidgetList::CSpriteComponentWidgetList()
{
}

CSpriteComponentWidgetList::~CSpriteComponentWidgetList()
{
}

void CSpriteComponentWidgetList::SetSpriteContent(CSpriteComponent* Sprite)
{
	//m_Sprite = Sprite;

	//m_AnimationClass->SetText(Sprite->GetAnimationName().c_str());

	//m_AnimationList->Clear();

	//std::vector<std::string> vecAnimNames;

	//Sprite->GetAnimationNames(vecAnimNames);

	//size_t Size = vecAnimNames.size();

	//for (size_t i = 0; i < Size; ++i)
	//{
	//	m_AnimationList->AddItem(vecAnimNames[i]);
	//}
}

void CSpriteComponentWidgetList::SetSelectAnimationSequence2DName(const std::string& Name)
{
	m_SequenceName->SetText(Name.c_str());
}

bool CSpriteComponentWidgetList::Init()
{

	CEditorTree<void*>* Category = CreateWidget<CEditorTree<void*>>("SpriteComponent");

	Category->SetHideName("SpriteComponent");

	Category->SetSize(400.f, 300.f);

	Category->AddItem(nullptr, "SpriteComponent");
	Category->AddItem(nullptr, "Sprite", "SpriteComponent");
	Category->AddItem(nullptr, "Animation", "SpriteComponent");

	m_Image = Category->CreateWidget<CEditorImage>("Sprite", "SpriteImage");

	Category->CreateWidget<CEditorSameLine>("Sprite", "Line");

	CEditorButton* LoadButton = Category->CreateWidget<CEditorButton>("Sprite", "이미지변경");

	LoadButton->SetClickCallback<CSpriteComponentWidgetList>(this, &CSpriteComponentWidgetList::SelectTextureButtonClick);

	CEditorSameLine* SameLine = Category->CreateWidget<CEditorSameLine>("Sprite", "Line");

	SameLine->SetSpacing(50.f);

	//m_List = Category->CreateWidget<CEditorListBox>("Sprite", "Animation List");
	//m_List->SetPageItemCount(6);
	//m_List->SetSelectCallback<CSpriteComponentWidgetList>(this, &CSpriteComponentWidgetList::ListClickCallback);

	m_AnimationClass = Category->CreateWidget<CEditorInput>("Animation", "Animation Class");
	m_AnimationClass->ReadOnly(true);
	m_AnimationClass->SetText("None");

	Category->CreateWidget<CEditorSameLine>("Animation", "Line");

	CEditorButton* Button = Category->CreateWidget<CEditorButton>("Animation", "CrateAnimation");

	Button->SetClickCallback<CSpriteComponentWidgetList>(this, &CSpriteComponentWidgetList::CreateAnimationButtonClick);
	Button->SetSize(150.f , 30.f);

	m_AnimationList = Category->CreateWidget<CEditorListBox>("Animation", "AnimationList");
	m_AnimationList->SetHideName("AnimationList");
	m_AnimationList->SetSize(300.f, 300.f);
	m_AnimationList->SetPageItemCount(6);
	m_AnimationList->SetSelectCallback<CSpriteComponentWidgetList>(this, &CSpriteComponentWidgetList::AnimationSelectCallback);

	Category->CreateWidget<CEditorSameLine>("Animation", "Line");

	CEditorGroup* AnimDataGroup = Category->CreateWidget<CEditorGroup>("Animation", "Animation2DData");

	m_PlayTime = AnimDataGroup->CreateWidget<CEditorInput>("PlayTime", 100.f, 30.f);
	m_PlayTime->SetInputType(EImGuiInputType::Float);

	m_PlayScale = AnimDataGroup->CreateWidget<CEditorInput>("PlayScale", 100.f, 30.f);
	m_PlayScale->SetInputType(EImGuiInputType::Float);

	m_SequenceName = AnimDataGroup->CreateWidget<CEditorInput>("SequenceName", 150.f, 30.f);
	m_SequenceName->ReadOnly(true);
	m_SequenceName->SetText("None");

	m_LoopCheck = AnimDataGroup->CreateWidget<CEditorCheckBox>("Loop", 100.f, 30.f);

	m_ReverseCheck = AnimDataGroup->CreateWidget<CEditorCheckBox>("Reverse", 100.f, 30.f);

    Button = Category->CreateWidget<CEditorButton>("Sprite", "애니메이션 적용");

	Button->SetSizeX(200.f);
	Button->SetClickCallback<CSpriteComponentWidgetList>(this, &CSpriteComponentWidgetList::LoadButton2Click);


	Button = Category->CreateWidget<CEditorButton>("Sprite", "Weapon 착용");

	Button->SetSizeX(200.f);
	Button->SetClickCallback<CSpriteComponentWidgetList>(this, &CSpriteComponentWidgetList::LoadButton3Click);


	//Button = AnimDataGroup->CreateWidget<CEditorButton>("AddAnimation2D", 150.f, 30.f);

	//Button->SetClickCallback<CSpriteComponentWidgetList>(this, &CSpriteComponentWidgetList::AddAnimation2DData);

	//AnimDataGroup->CreateWidget<CEditorSameLine>("Line");

	//Button = AnimDataGroup->CreateWidget<CEditorButton>("DeleteAnimation2D", 150.f, 30.f);

	//Button->SetClickCallback<CSpriteComponentWidgetList>(this, &CSpriteComponentWidgetList::DeleteAnimation2DData);

	//Button = AnimDataGroup->CreateWidget<CEditorButton>("ModifyAnimation2D", 150.f, 30.f);

	//Button->SetClickCallback<CSpriteComponentWidgetList>(this, &CSpriteComponentWidgetList::ModifyAnimation2DData);


	LoadAnimationSequence();

	return true;
}

void CSpriteComponentWidgetList::SelectTextureButtonClick()
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
		//m_Image = Category->FindWidget<CEditorImage>("OriginImage");

		if (m_Image)
		{
			TCHAR wTexName[256] = {};

			_wsplitpath_s(FullPath, 0, 0, 0, 0, wTexName, 256, 0, 0);

			char TexName[256] = {};

			int Length = (int)WideCharToMultiByte(CP_ACP, 0, wTexName, -1, nullptr, 0, nullptr, nullptr);

			WideCharToMultiByte(CP_ACP, 0, wTexName, -1, TexName, Length, nullptr, nullptr);

			CSceneComponent* Component = m_DetailWindow->GetSelectComponent();

			CSpriteComponent* Sprite = (CSpriteComponent*)Component;

			const std::string Name = (const std::string)TexName;

			CMaterial* Material = Sprite->GetMaterial(0);

		
			Material->SetTextureFullPath(0, 0, (int)EShaderBufferType::Pixel, TexName, FullPath);
			
			/*	Material->AddTexture(0, (int)EShaderBufferType::Pixel, "DefaultTexture",
					TEXT("teemo.png"));*/

			//(CSpriteComponent*)Component->SetTextureFullPath(TexName, FullPath);
		
			/*m_Image->SetName(m_Name->GetText());
			m_FrameImage->SetName(m_Name->GetText());*/
		}
	}
}

void CSpriteComponentWidgetList::ListClickCallback(int Index, const std::string& Item)
{
}

void CSpriteComponentWidgetList::LoadButton2Click()
{

	std::string SequenceName = m_AnimationListSelect;

	std::string SequenceFullName = SequenceName + ".Src";

	char Name[256] = {};

	const PathInfo* animPath = CPathManager::GetInst()->FindPath(ANIMATION2D_PATH);

	CResourceManager::GetInst()->CreateAnimationSequence2D(SequenceName, nullptr);

	if (animPath)
	{
		std::string SequenceFullName = animPath->PathMultibyte;
		SequenceFullName += SequenceName;
		SequenceFullName += ".Src";
		CResourceManager::GetInst()->LoadSequence2D(SequenceName, SequenceFullName.c_str());
	}

	CSceneComponent* Component = m_DetailWindow->GetSelectComponent();

	

	CSpriteComponent* spComp = ((CSpriteComponent*)Component);

	CAnimation2D* curAnim = spComp->GetAnimation();

	if (curAnim)
	{
		curAnim->AddAnimation(m_AnimationListSelect, m_AnimationListSelect);

		if (m_LoopCheck->GetTrue())
			curAnim->SetLoop(m_AnimationListSelect, true);

		curAnim->SetPlayTime(m_AnimationListSelect, m_PlayTime->GetFloat());
		curAnim->SetPlayScale(m_AnimationListSelect, m_PlayScale->GetFloat());

		curAnim->SetCurrentAnimation(m_AnimationListSelect);
	}
	else
	{
		CAnimation2D* Anim = spComp->SetAnimation<CAnimation2D>(m_AnimationListSelect);

		Anim->AddAnimation(m_AnimationListSelect, m_AnimationListSelect);

		if (m_LoopCheck->GetTrue())
			Anim->SetLoop(m_AnimationListSelect, true);

		Anim->SetPlayTime(m_AnimationListSelect, m_PlayTime->GetFloat());
		Anim->SetPlayScale(m_AnimationListSelect, m_PlayScale->GetFloat());

		Anim->SetCurrentAnimation(m_AnimationListSelect);
	}

	

}

void CSpriteComponentWidgetList::LoadAnimationSequence()
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

	strcat_s(Directory, "Bin/Animation2D/");

	for (const auto& file : std::filesystem::directory_iterator(Directory))
	{
		char	Name[64] = {};
		char	FullPath[MAX_PATH] = {};
		char	Ext[_MAX_EXT] = {};

		strcpy_s(FullPath, file.path().generic_string().c_str());

		_splitpath_s(FullPath, nullptr, 0, nullptr, 0, Name, 64, Ext, _MAX_EXT);

		//if (strcmp(Ext, ".cpp") == 0)
		//	continue;

		m_AnimationList->AddItem(Name);
	}
}

void CSpriteComponentWidgetList::CreateAnimationButtonClick()
{
	CAnimation2DWindow* Animation2DWindow = CEditorGUIManager::GetInst()->FindEditorWindow<CAnimation2DWindow>("Animation2DWindow");

	std::string Name = Animation2DWindow->GetAnimation2DSelectName();
	
	if (Name.empty())
		return;

	CSpriteComponent* Sprite = (CSpriteComponent*)m_DetailWindow->GetSelectComponent();

	if (Name == "Animation2D")
	{
		Sprite->SetAnimation<CAnimation2D>("Animation2D");
		m_AnimationClass->SetText("Animation2D");
	}

}

void CSpriteComponentWidgetList::AnimationSelectCallback(int Index, const std::string& Item)
{
	m_AnimationListSelect = Item;

	m_SequenceName->SetText(m_AnimationListSelect.c_str());

}

void CSpriteComponentWidgetList::AddAnimation2DData()
{
	/*CAnimation2D* Animation = m_Sprite->GetAnimation();

	if (Animation->FindAnimation(m_Animation2DDataName->GetText()))
		return;

	CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D(
		m_SequenceName->GetText());

	if (!Sequence)
		return;

	Animation->AddAnimation(m_Animation2DDataName->GetText(),
		Sequence, m_PlayTime->GetFloat(), m_PlayScale->GetFloat(),
		m_LoopCheck->GetTrue(), m_ReverseCheck->GetTrue());

	m_AnimationList->AddItem(m_Animation2DDataName->GetText());*/
}

void CSpriteComponentWidgetList::DeleteAnimation2DData()
{
}

void CSpriteComponentWidgetList::ModifyAnimation2DData()
{
}

void CSpriteComponentWidgetList::LoadButton3Click()
{
	m_Player = CSceneManager::GetInst()->GetScene()->GetSceneInfo()->GetPlayer();
		
}
