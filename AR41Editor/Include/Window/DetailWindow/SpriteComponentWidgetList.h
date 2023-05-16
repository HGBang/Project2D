#pragma once
#include "ComponentWidgetList.h"
class CSpriteComponentWidgetList :
    public CComponentWidgetList
{
	friend class CEditorWindow;
	friend class CEditorGroup;

protected:
	CSpriteComponentWidgetList();
	virtual ~CSpriteComponentWidgetList();

private:
	class CEditorImage* m_Image;
	class CEditorListBox* m_List;
	class CEditorInput* m_PlayTime;
	class CEditorInput* m_PlayScale;
	class CEditorInput* m_AnimationClass;
	class CEditorListBox* m_AnimationList;
	class CEditorCheckBox* m_ReverseCheck;
	class CEditorCheckBox* m_LoopCheck;
	class CEditorInput* m_SequenceName;
	class CEditorInput* m_Animation2DDataName;
	class CGameObject* m_Player;

	class CSpriteComponent* m_Sprite;

	std::string	m_AnimationListSelect;

public:
	void SetSpriteContent(class CSpriteComponent* Sprite);
	void SetSelectAnimationSequence2DName(const std::string& Name);

public:
	virtual bool Init();

private:
	void SelectTextureButtonClick();
	void ListClickCallback(int Index, const std::string& Item);
	void LoadButton2Click();
	void LoadAnimationSequence();
	void CreateAnimationButtonClick();
	void AnimationSelectCallback(int Index, const std::string& Item);
	void AddAnimation2DData();
	void DeleteAnimation2DData();
	void ModifyAnimation2DData();
	void LoadButton3Click();
};

