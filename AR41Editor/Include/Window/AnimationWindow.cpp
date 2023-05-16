#include "AnimationWindow.h"
#include "Editor/EditorButton.h"
#include "Editor/EditorSameLine.h"
#include "Editor/EditorLabel.h"
#include "Editor/EditorImage.h"
#include "Editor/EditorText.h"
#include "Editor/EditorInput.h"
#include "Editor/EditorListBox.h"
#include "Editor/EditorComboBox.h"
#include "Editor/EditorGUIManager.h"
#include "Editor/EditorSliderBar.h"
#include "Editor/EditorCheckBox.h"
#include "UI/UIImage.h"
#include "UI/UIWidget.h"
#include "UI/UIWindow.h"


#include "Animation/Animation2D.h"
#include "Resource/Animation/AnimationSequence2D.h"

#include "Resource/ResourceManager.h"
#include "Resource/Animation/AnimationManager.h"
#include "PathManager.h"
#include "Engine.h"

#include "Editor/EditorGUIManager.h"






CAnimationWindow::CAnimationWindow()

{
}

CAnimationWindow::~CAnimationWindow()
{
}

bool AddItem(CAnimationSequence2D* Sequence, const std::string& Name)
{
	return true;
}

bool CAnimationWindow::Init()
{

 //   AnimationCategory = CreateWidget<CEditorTree<void*>>("Animation");

	////AnimationCategory->SetHideName("Animation");

	//AnimationCategory->SetSize(400.f, 300.f);

	//AnimationCategory->AddItem(nullptr, "Animation");

	SliderNumber = 0;

	CEditorLabel* Label = CreateWidget<CEditorLabel>("원본이미지");

	Label->SetColor(50, 50, 50, 255);
	Label->SetAlign(0.5f, 0.5f);
	Label->SetSize(100.f, 30.f);

	CEditorSameLine* Line = CreateWidget<CEditorSameLine>("Animation");

	Line->SetSpacing(200.f);

    Label = CreateWidget<CEditorLabel>("Animation");

	Label->SetColor(50, 50, 50, 255);
	Label->SetAlign(0.5f, 0.5f);
	Label->SetSize(100.f, 30.f);

	m_Image = CreateWidget<CEditorImage>("OriginImage");

	m_Image->SetSize(200.f, 200.f);

	Line = CreateWidget<CEditorSameLine>( "Line");

	Line->SetSpacing(50.f);

	m_FrameImage = CreateWidget<CEditorImage>("FrameImage");

	m_FrameImage->SetSize(200.f, 200.f);

	Line = CreateWidget<CEditorSameLine>("Line");

	Line->SetSpacing(10.f);

	//m_AnimationImage = CreateWidget<CEditorImage>("AnimationImage");

	//m_AnimationImage->SetSize(200.f, 200.f);

	Line = CreateWidget<CEditorSameLine>("Line");

	Line->SetSpacing(10.f);

	m_List = CreateWidget<CEditorListBox>("Sequence List");
	m_List->SetPageItemCount(6);
	m_List->SetSize(300.f, 300.f);
	m_List->SetSelectCallback<CAnimationWindow>(this, &CAnimationWindow::ListClickCallback);
	
	CEditorButton* ImageLoadButton = CreateWidget<CEditorButton>("이미지 선택");

	ImageLoadButton->SetSize(200.f, 100.f);
	ImageLoadButton->SetClickCallback<CAnimationWindow>(this, &CAnimationWindow::LoadImageButtonClick);

	Line = CreateWidget<CEditorSameLine>("Line");

	Line->SetSpacing(50.f);

	CEditorButton* AnimationPlayButton = CreateWidget<CEditorButton>("Animation Play");

	AnimationPlayButton->SetSize(150.f, 100.f);
	AnimationPlayButton->SetClickCallback<CAnimationWindow>(this, &CAnimationWindow::LoadAnimationPlayButtonClick);

	Line = CreateWidget<CEditorSameLine>("Line");

	Line->SetSpacing(5.f);

	CEditorButton* AnimationStopButton = CreateWidget<CEditorButton>("Animation Stop");

	AnimationStopButton->SetSize(150.f, 100.f);
	AnimationStopButton->SetClickCallback<CAnimationWindow>(this, &CAnimationWindow::LoadAnimationStopButtonClick);

	Line = CreateWidget<CEditorSameLine>("Line");

	Line->SetSpacing(5.f);

	m_Speed = CreateWidget<CEditorInput>(u8"재생속도");
	m_Speed->SetInputType(EImGuiInputType::Float);
	m_Speed->SetFloat(0.01f);


	Label = CreateWidget<CEditorLabel>("애니메이션 세팅");

	Label->SetColor(50, 50, 50, 255);
	Label->SetAlign(0.5f, 0.5f);
	Label->SetSize(600.f, 30.f);


	CEditorButton* AnimationCreateButton = CreateWidget<CEditorButton>("시퀀스 생성");

	AnimationCreateButton->SetSize(170.f, 100.f);
	AnimationCreateButton->SetClickCallback<CAnimationWindow>(this, &CAnimationWindow::LoadAnimationImageButtonClick);

	Line = CreateWidget<CEditorSameLine>("Line");

	Line->SetSpacing(50.f);

	CEditorButton* FrameButton = CreateWidget<CEditorButton>("Add Frame");

	FrameButton->SetSize(170.f, 100.f);
	FrameButton->SetClickCallback<CAnimationWindow>(this, &CAnimationWindow::AddFrameButtonClick);

	Line = CreateWidget<CEditorSameLine>("Line");

	Line->SetSpacing(50.f);

	CEditorButton* FrameButton2 = CreateWidget<CEditorButton>("Add Frame All");

	FrameButton2->SetSize(170.f, 100.f);
	FrameButton2->SetClickCallback<CAnimationWindow>(this, &CAnimationWindow::AddFrameButtonClick2);

	Line = CreateWidget<CEditorSameLine>("Line");

	Line->SetSpacing(50.f);

	CEditorButton* FrameButton3 = CreateWidget<CEditorButton>("파일시퀀스 생성 (Frame)");

	FrameButton3->SetSize(170.f, 100.f);
	FrameButton3->SetClickCallback<CAnimationWindow>(this, &CAnimationWindow::FileSequenceButton);

	Label = CreateWidget<CEditorLabel>("Atlas Animation");

	Label->SetColor(255, 50, 50, 255);
	Label->SetAlign(0.5f, 0.5f);
	Label->SetSize(290.f, 30.f);

	Line = CreateWidget<CEditorSameLine>("Line");

    Line->SetSpacing(1.f);


	Label = CreateWidget<CEditorLabel>("Frame Animation");

	Label->SetColor(255, 50, 50, 255);
	Label->SetAlign(0.5f, 0.5f);
	Label->SetSize(290.f, 30.f);

	//m_CheckAtlas = CreateWidget<CEditorCheckBox>("Atlas");
	//m_CheckFrame = CreateWidget<CEditorCheckBox>("Frame");

	m_Name = CreateWidget<CEditorInput>("SequenceName");
	m_Name->SetInputType(EImGuiInputType::String);

	Line = CreateWidget<CEditorSameLine>("Line");

	Line->SetSpacing(72.f);

	m_FrameSequenceName = CreateWidget<CEditorInput>("FrameSequenceName");
	m_FrameSequenceName->SetInputType(EImGuiInputType::String);
	m_FrameSequenceName->SetSizeX(200.f);

	m_StartX = CreateWidget<CEditorInput>("StartFrameX");
	m_StartX->SetInputType(EImGuiInputType::Float);

	Line = CreateWidget<CEditorSameLine>("Line");

	Line->SetSpacing(95.f);

	m_FolderName = CreateWidget<CEditorInput>("FolderName");
	m_FolderName->SetInputType(EImGuiInputType::String);
	m_FolderName->SetSizeX(200.f);

	//m_Box = CreateWidget<CEditorCheckBox>("Reverse");
	
	m_EndX = CreateWidget<CEditorInput>("EndFrameX");
	m_EndX->SetInputType(EImGuiInputType::Float);	

	m_StartY = CreateWidget<CEditorInput>("StartFrameY");
	m_StartY->SetInputType(EImGuiInputType::Float);	

	m_EndY = CreateWidget<CEditorInput>("EndFrameY");
	m_EndY->SetInputType(EImGuiInputType::Float);		

	m_Count = CreateWidget<CEditorInput>("FrameCount");
	m_Count->SetInputType(EImGuiInputType::Int);

	m_Slider = CreateWidget<CEditorSliderBar>("Frame");

	SliderCount = 0;

	ListOn = false;

	AnimationPlay = false;

	CEditorButton* SaveSequenceButton = CreateWidget<CEditorButton>("시퀀스 저장");

	SaveSequenceButton->SetSize(150.f, 100.f);
	SaveSequenceButton->SetClickCallback<CAnimationWindow>(this, &CAnimationWindow::SaveSequenceButton);

	Line = CreateWidget<CEditorSameLine>("Line");

	Line->SetSpacing(50.f);

	CEditorButton* LoadSequenceButton = CreateWidget<CEditorButton>("시퀀스 불러오기");

	LoadSequenceButton->SetSize(150.f, 100.f);
	LoadSequenceButton->SetClickCallback<CAnimationWindow>(this, &CAnimationWindow::LoadSequenceButton);

	Line = CreateWidget<CEditorSameLine>("Line");

	Line->SetSpacing(50.f);

	CEditorButton* NewSequenceButton = CreateWidget<CEditorButton>("새로고침");

	NewSequenceButton->SetSize(150.f, 100.f);
	NewSequenceButton->SetClickCallback<CAnimationWindow>(this, &CAnimationWindow::ResetButton);
	
	//LoadButton->SetClickCallback<CDetailWindow>(this, &CDetailWindow::LoadButtonClick);
	m_AnimationList = CreateWidget<CEditorListBox>("Animation List");
	m_AnimationList->SetPageItemCount(6);
	m_AnimationList->SetSelectCallback<CAnimationWindow>(this, &CAnimationWindow::AnimationListClickCallback);
	m_AnimationList->SetSize(300.f, 300.f);

	FrameCountNum = 1;

	LoadAnimationList();
	return true;
}

void CAnimationWindow::Update(float DeltaTime)
{
	CEditorWindow::Update(DeltaTime);
	
	if (!ListOn)
	{
		m_FrameImage->SetImageStart(m_StartX->GetFloat(), m_StartY->GetFloat());
		m_FrameImage->SetImageEnd(m_EndX->GetFloat(), m_EndY->GetFloat());
	}		
	
	if (0 < m_Slider->GetInt())
	{
		if (m_Sequence->GetAnim2DType() == EAnimation2DType::Atlas)
		{
			m_FrameImage->SetImageStart(m_StartX->GetFloat() , m_StartY->GetFloat());
			m_FrameImage->SetImageEnd(m_EndX->GetFloat() , m_EndY->GetFloat());
		}

		else
		{

		}

		if (m_Sequence->GetAnim2DType() == EAnimation2DType::Frame)
		{
			CTexture* Texture = m_Sequence->GetTexture();


			std::string FileName = "TestNameTestNameTestNameTestNameTestNameTestNameTestNameTestNameTestNameTestNameTestNameTestNameTestNTestNameTestNameTestNameTestNameTestNameTestNameTestNameTestNameTestNameTestNameTestNameTestNameTestNameTestNameTestName";
			std::string RealName = FileName.c_str() + m_Slider->GetInt();

			m_FrameImage->SetTexture(RealName, Texture->GetFileName(m_Slider->GetInt() -1), 
				Texture->GetPathName(m_Slider->GetInt()-1));
			m_FrameImage->SetImageStart(m_StartX->GetFloat(), m_StartY->GetFloat());
			m_FrameImage->SetImageEnd(m_EndX->GetFloat(), m_EndY->GetFloat());
		}

		else
		{

		}
	}

	if (AnimationCheck)
	{
		if (m_Sequence->GetAnim2DType() == EAnimation2DType::Atlas)
		{
			int i = m_Sequence->GetFrameCount() - 1;

			m_Slider->SetInt3(i);

			float StartX = (float)m_Sequence->GetFrameData(m_Slider->GetInt()).Start.x;
			float StartY = (float)m_Sequence->GetFrameData(m_Slider->GetInt()).Start.y;
			float EndX = (float)m_Sequence->GetFrameData(m_Slider->GetInt()).End.x;
			float EndY = (float)m_Sequence->GetFrameData(m_Slider->GetInt()).End.y;


			m_StartX->SetFloat(StartX);
			m_StartY->SetFloat(StartY);
			m_EndX->SetFloat(EndX);
			m_EndY->SetFloat(EndY);
		}

		if (m_Sequence->GetAnim2DType() == EAnimation2DType::Frame)
		{
			CTexture* Texture = m_Sequence->GetTexture();
			//std::string FileName = "TestNameTestNameTestNameTestNameTestNameTestNameTestNameTestNameTestNameTestNameTestNameTestNameTestNTestNameTestNameTestNameTestNameTestNameTestNameTestNameTestNameTestNameTestNameTestNameTestNameTestNameTestNameTestName";
			//std::string RealName = FileName.c_str() + FrameCountNum;

			int FrameSize = Texture->GetImageCount();

			m_Slider->SetInt3(FrameSize - 1);

			

			float StartX = 0.f;
			float StartY = 0.f;
			float EndX = (float)Texture->GetWidth(m_Slider->GetInt());
			float EndY = (float)Texture->GetHeight(m_Slider->GetInt());

			m_StartX->SetFloat(StartX);
			m_StartY->SetFloat(StartY);
			m_EndX->SetFloat(EndX);
			m_EndY->SetFloat(EndY);
		}
	}

	
	if (AnimationPlay)
	{

		if (m_Sequence->GetAnim2DType() == EAnimation2DType::Atlas)
		{
			Time += DeltaTime;

			if (Time > m_Speed->GetFloat())
			{

				if (AnimationIndex <= m_Sequence->GetFrameCount())
				{
					m_Slider->SetInt(AnimationIndex);

					++AnimationIndex;

					Time = 0.f;
				}

				if (AnimationIndex == m_Sequence->GetFrameCount())
				{
					AnimationIndex = 0;
					Time = 0.f;
				}
			}

			float StartX = (float)m_Sequence->GetFrameData(AnimationIndex).Start.x;
			float StartY = (float)m_Sequence->GetFrameData(AnimationIndex).Start.y;
			float EndX = (float)m_Sequence->GetFrameData(AnimationIndex).End.x;
			float EndY = (float)m_Sequence->GetFrameData(AnimationIndex).End.y;

			m_FrameImage->SetTexture(m_Sequence->GetTexture());
			m_FrameImage->SetImageStart(StartX, StartY);
			m_FrameImage->SetImageEnd(EndX, EndY);

			m_StartX->SetFloat(StartX);
			m_StartY->SetFloat(StartY);
			m_EndX->SetFloat(EndX);
			m_EndY->SetFloat(EndY);
		}

		if (m_Sequence->GetAnim2DType() == EAnimation2DType::Frame)
		{
			{
				CTexture* Texture = m_Sequence->GetTexture();

				int FrameCount = Texture->GetImageCount();

				FrameTime += DeltaTime;

				if (FrameTime > m_Speed->GetFloat())
				{
					std::string FileName = "TestNameTestNameTestNameTestNameTestNameTestNameTestNameTestNameTestNameTestNameTestNameTestNameTestNTestNameTestNameTestNameTestNameTestNameTestNameTestNameTestNameTestNameTestNameTestNameTestNameTestNameTestNameTestName";
					std::string RealName = FileName.c_str() + FrameCountNum;

					m_FrameImage->SetTexture(RealName, 
					Texture->GetFileName(FrameCountNum), Texture->GetPathName(FrameCountNum));
			

					FrameTime = 0.f;

					++FrameCountNum;

					m_Slider->SetInt(FrameCountNum - 1);

					if (FrameCountNum == FrameCount)
						FrameCountNum = 0;

				}
			}

		}
	}

		

	/*	if (!AnimationPlay)
		{
			if(m_Sequence)
			{


				if (m_Slider->GetInt() > 0)
				{
					if (m_Slider->GetInt() <= m_Sequence->GetFrameCount())
					{
						float StartX = (float)m_Sequence->GetFrameData(m_Slider->GetInt() - 1).Start.x;
						float StartY = (float)m_Sequence->GetFrameData(m_Slider->GetInt() - 1).Start.y;
						float EndX = (float)m_Sequence->GetFrameData(m_Slider->GetInt() - 1).End.x;
						float EndY = (float)m_Sequence->GetFrameData(m_Slider->GetInt() - 1).End.y;

						m_FrameImage->SetImageStart(StartX, StartY);
						m_FrameImage->SetImageEnd(EndX, EndY);
					}
				}

				else
				{

				}
			}
		}*/
	
}

void CAnimationWindow::InputClear()
{
	m_StartX->SetFloat(0.f);
	m_StartY->SetFloat(0.f);
	m_EndX->SetFloat(0.f);
	m_EndY->SetFloat(0.f);
	m_Count->SetInt(0);
	m_Name->SetName("");
}

TCHAR* CAnimationWindow::StringToTCHAR(const std::string& Name)
{
	size_t origsize = 0, convertedChars = 0;
	origsize = strlen(Name.c_str()) + 1;
	wchar_t* t = new wchar_t[origsize];	
	mbstowcs_s(&convertedChars, t, origsize, Name.c_str(), _TRUNCATE);

	return (TCHAR*)t;
}


void CAnimationWindow::LoadImageButtonClick()
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
		m_Image = FindWidget<CEditorImage>("OriginImage");

		if (m_Image)
		{
			TCHAR wTexName[256] = {};

			_wsplitpath_s(FullPath, 0, 0, 0, 0, wTexName, 256, 0, 0);

			char TexName[256] = {};

			int Length = (int)WideCharToMultiByte(CP_ACP, 0, wTexName, -1, nullptr, 0, nullptr, nullptr);

			WideCharToMultiByte(CP_ACP, 0, wTexName, -1, TexName, Length, nullptr, nullptr);
						
			m_Image->SetTextureFullPath(TexName, FullPath);
			m_FrameImage->SetTextureFullPath(TexName, FullPath);
			/*m_Image->SetName(m_Name->GetText());
			m_FrameImage->SetName(m_Name->GetText());*/						
		}
	}
}

void CAnimationWindow::LoadAnimationImageButtonClick()
{
	if (ListOn)
		ListOn = false;

	CResourceManager::GetInst()->CreateAnimationSequence2D(m_Name->GetText(), m_FrameImage->GetTexture());
	
	m_List->AddItem(m_Name->GetText());
	
	AnimationCheck = false;		
}

void CAnimationWindow::AddFrameButtonClick()
{
	if (m_Sequence)
	{	
		if (m_Sequence->GetAnim2DType() == EAnimation2DType::Atlas)
		{
			float StartX = m_StartX->GetFloat();
			float StartY = m_StartY->GetFloat();
			float EndX = m_EndX->GetFloat();
			float EndY = m_EndY->GetFloat();

			m_Sequence = CResourceManager::GetInst()->FindAnimationSequence2D(m_Name->GetText());
			//m_Name->SetName(m_Sequence->GetName());
			m_Sequence->AddFrame(StartX, StartY, EndX, EndY);
			

			m_Slider->SetInt3(m_Sequence->GetFrameCount());
		}

		else
		{

		}

	}
}

void CAnimationWindow::AddFrameButtonClick2()
{

	if (m_Sequence)
	{		
			float StartX = m_StartX->GetFloat();
			float StartY = m_StartY->GetFloat();
			float EndX = m_EndX->GetFloat();
			float EndY = m_EndY->GetFloat();

			m_Sequence = CResourceManager::GetInst()->FindAnimationSequence2D(m_Name->GetText());
			//m_Name->SetName(m_Sequence->GetName());

			for (int i = 0; i < m_Count->GetInt(); ++i)
			{
				CResourceManager::GetInst()->AddAnimationSequence2DFrame(m_Name->GetText(),
					Vector2(i * StartX, StartY), Vector2((i + 1) * EndX, EndY));
			}

			m_Slider->SetInt3(m_Count->GetInt()-1);
	}
}

void CAnimationWindow::ListClickCallback(int Index, const std::string& Item)
{
		ResetButton();

		m_SelectSequenceListItem = Item;

		m_Sequence = CResourceManager::GetInst()->FindAnimationSequence2D(m_SelectSequenceListItem);
	
		CTexture* Texture = m_Sequence->GetTexture();

		if (m_Sequence->GetAnim2DType() == EAnimation2DType::Atlas)
		{
			m_Image->SetTexture(m_Sequence->GetTexture());
			m_FrameImage->SetTexture(m_Sequence->GetTexture());

			int Count = m_Sequence->GetFrameCount();

			m_Name->SetText(m_Sequence->GetName().c_str());

			m_Slider->SetInt3(Count);
		}

		if (m_Sequence->GetAnim2DType() == EAnimation2DType::Frame)
		{
			m_Image->SetTexture("Test123", Texture->GetFileName(0), Texture->GetPathName(0));
			m_FrameImage->SetTexture("Test1235", Texture->GetFileName(0), Texture->GetPathName(0));

			int Count = m_Sequence->GetFrameCount();

			m_FrameSequenceName->SetText(m_Sequence->GetName().c_str());

			m_Count->SetInt(Count);

			m_Slider->SetInt3(Count);

			AnimationCheck = true;
		}

	
		
		////InputClear();	
		//ListOn = true;
		//AnimationPlay = false;
	

	//else if (m_Sequence->GetAnim2DType() == EAnimation2DType::Frame)
	//{
	//	m_CheckFrame->SetTrue(true);

	//	//m_Image->SetTexture(m_Sequence->GetTexture());
	//	m_FrameImage->SetTexture(m_Sequence->GetTexture());

	//	AnimationPlay = false;

	//	int Count = m_Sequence->GetFrameCount();

	//	m_Name->SetText(m_Sequence->GetName().c_str());

	//	m_Slider->SetInt3(Count);
	//}


}

void CAnimationWindow::LoadAnimationPlayButtonClick()
{
	if (m_Sequence)
	{
		
		if (m_SelectSequenceListItem.c_str())
		{
			m_Sequence = CResourceManager::GetInst()->FindAnimationSequence2D(m_SelectSequenceListItem);

			AnimationPlay = true;

			AnimationCheck = false;
		}		
	}
}

void CAnimationWindow::LoadAnimationStopButtonClick()
{
	if (m_Sequence)
	{
		if (m_SelectSequenceListItem.c_str())
		{
			m_Sequence = CResourceManager::GetInst()->FindAnimationSequence2D(m_SelectSequenceListItem);

			AnimationPlay = false;

			AnimationCheck = true;
		}
	}
}

void CAnimationWindow::SaveSequenceButton()
{
	if (m_SelectSequenceListItem.c_str())
	{
		m_Sequence = CResourceManager::GetInst()->FindAnimationSequence2D(m_SelectSequenceListItem);

		const PathInfo* animPath = CPathManager::GetInst()->FindPath(ANIMATION2D_PATH);

		if (animPath)
		{
			std::string SequenceFullName = animPath->PathMultibyte;
			SequenceFullName += m_Sequence->GetName().c_str();
			SequenceFullName += ".Src";
			m_Sequence->Save(SequenceFullName.c_str());
		}

		m_AnimationList->AddItem(m_Sequence->GetName());

	}
}

void CAnimationWindow::LoadSequenceButton()
{
	OPENFILENAME ofn = { };

	TCHAR	FullPath[MAX_PATH] = {};
	TCHAR	InitPath[MAX_PATH] = {};

	TCHAR	Filter[] = TEXT("모든파일\0*.*");

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = CEngine::GetInst()->GetWindowHandle();
	ofn.lpstrFilter = Filter;
	ofn.lpstrFile = FullPath;
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrInitialDir = CPathManager::GetInst()->FindPath(ANIMATION2D_PATH)->Path;

	if (GetOpenFileName(&ofn) != 0)
	{
			TCHAR wSequenceName[256] = {};

			_wsplitpath_s(FullPath, 0, 0, 0, 0, wSequenceName, 256, 0, 0);

			char SequenceName[256] = {};

			int Length = (int)WideCharToMultiByte(CP_ACP, 0, wSequenceName, -1, nullptr, 0, nullptr, nullptr);

			WideCharToMultiByte(CP_ACP, 0, wSequenceName, -1, SequenceName, Length, nullptr, nullptr);

			//m_Image->SetTextureFullPath(TexName, FullPath);
			//m_FrameImage->SetTextureFullPath(TexName, FullPath);

			/*m_Image->SetName(m_Name->GetText());
			m_FrameImage->SetName(m_Name->GetText());*/
			//const PathInfo* animPath = CPathManager::GetInst()->FindPath(ANIMATION2D_PATH);
					
			std::string SequenceFullName = SequenceName;
				SequenceFullName += ".Src";

			CResourceManager::GetInst()->CreateAnimationSequence2D(SequenceName, nullptr);
			m_Sequence = CResourceManager::GetInst()->FindAnimationSequence2D(SequenceName);

			m_Sequence->Load(SequenceFullName.c_str(), ANIMATION2D_PATH);

			m_List->AddItem(m_Sequence->GetName());

	}
	
}

void CAnimationWindow::AnimationListClickCallback(int Index, const std::string& Item)
{
	m_SelectAnimationListItem = Item;

	if (m_Sequence)
	{
		m_FrameImage->SetTexture(m_Sequence->GetTexture());
		m_Image->SetTexture(m_Sequence->GetTexture());

		m_Slider->SetInt3(m_Sequence->GetFrameCount());
	}
}

void CAnimationWindow::LoadAnimationList()
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

		if (strcmp(Ext, ".ini") == 0)
			continue;
		
		m_AnimationList->AddItem(Name);
	}
}

void CAnimationWindow::ResetButton()
{

	AnimationCheck = false;
	AnimationPlay = false;

	m_Sequence = nullptr;
	//m_FrameImage = nullptr;
	//m_Image = nullptr;

	m_SelectAnimationListItem = "";
	m_SelectSequence = nullptr;
	m_SelectSequenceListItem = "";
	
	m_StartX->SetFloat(0.f);
	m_StartY->SetFloat(0.f);
	m_EndX->SetFloat(0.f);
	m_EndY->SetFloat(0.f);
	m_Name->SetText("");
	m_Count->SetFloat(0.f);
	m_Slider->SetInt3(0);
	m_Slider->SetInt(0);

	m_FrameSequenceName->SetText("");
	m_FolderName->SetText("");
	m_Count->SetInt(0);

	AnimationIndex = 0;
	
	FrameCountNum = 0;

}

void CAnimationWindow::FileSequenceButton()
{	
		
	std::string FullName = m_FolderName->GetText();

	std::string FileFullName = FullName + '/' + m_FrameSequenceName->GetText() + "%d.png";
	
	TCHAR* RealName = StringToTCHAR(FileFullName);

	std::vector<const TCHAR*> vecFileName;

	for (int i = 0; i < m_Count->GetInt(); ++i)
	{
		TCHAR* FileName = new TCHAR[MAX_PATH];

		memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);

		wsprintf(FileName, RealName, i);

		vecFileName.push_back(FileName);
	}

	SAFE_DELETE(RealName);	

	CResourceManager::GetInst()->CreateAnimationSequence2D(
		m_FrameSequenceName->GetText() , m_FrameSequenceName->GetText(), vecFileName);

	float StartX = m_StartX->GetFloat();
	float StartY = m_StartY->GetFloat();
	float EndX = m_EndX->GetFloat();
	float EndY = m_EndY->GetFloat();
	int Count = m_Count->GetInt();

	CResourceManager::GetInst()->AddAnimationSequence2DFrameAll(m_FrameSequenceName->GetText(), Count,
		Vector2(0.f,0.f), Vector2(240.f, 320.f));

	for (int i = 0; i <= Count -1; ++i)
	{
    SAFE_DELETE_ARRAY(vecFileName[i]);
	}

	vecFileName.clear();
	
	m_List->AddItem(m_FrameSequenceName->GetText());

	m_FrameSequenceName->SetText("");
	m_FolderName->SetText("");
	m_Count->SetInt(0);
}

