#pragma once
#include "Editor\EditorWindow.h"
#include "Editor/EditorTree.h"
#include "Animation/Animation2D.h"
#include "Resource/Animation/AnimationSequence2D.h"
#include "UI/UIWindow.h"
#include "UI/UIWidget.h"


class CAnimationWindow :
    public CEditorWindow
{
	friend class CEditorGUIManager;
	friend class CAnimation2D;
	friend class CAnimationSequence2D;
	friend class CEditorSliderBar;
	friend class CUIWindow;
	friend class CUIWidget;

protected:
	CAnimationWindow();
	virtual ~CAnimationWindow();

private:
	CEditorTree<CAnimationSequence2D*>*     m_Tree;
	CSharedPtr<CAnimationSequence2D>		m_SelectSequence;
	std::vector<class CEditorWidget*> m_vecSpriteComponent;
	CEditorTree<void*>* AnimationCategory;

	int SliderCount;

	class CEditorListBox* m_List;
	class CEditorListBox* m_AnimationList;

	class CEditorInput* m_StartX;
	class CEditorInput* m_StartY;
	class CEditorInput* m_EndX;
	class CEditorInput* m_EndY;
	class CEditorInput* m_Name;
	class CEditorInput* m_Count;

	class CEditorImage* m_Image;
	class CEditorImage* m_FrameImage;

	CSharedPtr<class CUIImage> m_UIImage;
	//class CEditorImage* m_AnimationImage;
	
	class CEditorSliderBar* m_Slider;

	class CEditorCheckBox* m_Box;

	class CAnimationSequence2D* m_Sequence;

	std::string			m_SelectSequenceListItem;
	std::string			m_SelectAnimationListItem;

	float Time;

	int SliderNumber;

	bool ListOn;

	bool AnimationPlay;

	int AnimationIndex;

	bool AnimationCheck;

	float Speed;

	class CEditorInput* m_Speed;

	class CEditorCheckBox* m_CheckAtlas;
	class CEditorCheckBox* m_CheckFrame;
	class CEditorInput* m_FolderName;
	class CEditorInput* m_FrameSequenceName;

	float FrameTime;

	int FrameCountNum;


public:
	class CAnimationSequence2D* GetSelectSequence() const
	{
		return m_SelectSequence;
	}

public:
	bool AddItem(CAnimationSequence2D* Sequence, const std::string& Name);

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	
public:
	void InputClear();

public:
	TCHAR* StringToTCHAR(const std::string& Name);

public:
	void TreeCallback(CEditorTreeItem<CAnimationSequence2D*>* Node, const std::string& Item);
	void LoadImageButtonClick();
	void LoadAnimationImageButtonClick();
	void AddFrameButtonClick();
	void AddFrameButtonClick2();
	void ListClickCallback(int Index, const std::string& Item);
	void LoadAnimationPlayButtonClick();
	void LoadAnimationStopButtonClick();
	void SaveSequenceButton();
	void LoadSequenceButton();
	void AnimationListClickCallback(int Index, const std::string& Item);
	void LoadAnimationList();
	void ResetButton();
	void FileSequenceButton();
	
};

