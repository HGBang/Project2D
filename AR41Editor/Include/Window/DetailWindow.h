#pragma once
#include "Editor\EditorWindow.h"


class CDetailWindow :
    public CEditorWindow
{
	friend class CEditorGUIManager;

protected:
	CDetailWindow();
	virtual ~CDetailWindow();

protected:
	std::vector<class CComponentWidgetList*> m_vecComponentWidgetList;


public:
	class CComponentWidgetList* GetComponentWidgetList(const std::string& Name);

	class CSceneComponent* GetSelectComponent() const
	{
		return m_SelectComponent;
	}

	CSharedPtr<class CSceneComponent> m_SelectComponent;

	class CEditorInput* m_StartX;
	class CEditorInput* m_StartY;
	class CEditorInput* m_EndX;
	class CEditorInput* m_EndY;
	class CEditorInput* m_Name;
	class CEditorInput* m_TypeName;
	class CEditorInput* m_Count;
	class CEditorListBox* m_List;
	class CEditorListBox* m_ColliderList;
	class CEditorListBox* m_IgnoreList;

	class CEditorCheckBox* m_MouseChannelCheck;
	class CEditorCheckBox* m_DefaultChannelCheck;
	class CEditorCheckBox* m_PlayerChannelCheck;
	class CEditorCheckBox* m_MonsterChannelCheck;
	class CEditorCheckBox* m_PlayerAttackChannelCheck;
	class CEditorCheckBox* m_MonsterAttackChannelCheck;
	class CEditorCheckBox* m_DetailCheck;

	class CEditorSliderBar* m_SliderBarX;
	class CEditorSliderBar* m_SliderBarY;

	// ÇÈ¼¿Ãæµ¹
	class CEditorInput* m_PixelName;
	class CEditorInput* m_PixelRed;
	class CEditorInput* m_PixelGreen;
	class CEditorInput* m_PixelBlue;
	class CEditorInput* m_PixelAlpha;
	class CEditorCheckBox* m_PixelColorIgnore;
	class CEditorCheckBox* m_PixelColorConfirm;
	class CEditorCheckBox* m_PixelAlphaIgnore;
	class CEditorCheckBox* m_PixelAlphaConfirm;
	class CEditorListBox* m_PixelColliderList;

	class CEditorCheckBox* m_PixelMouseChannelCheck;
	class CEditorCheckBox* m_PixelDefaultChannelCheck;
	class CEditorCheckBox* m_PixelPlayerChannelCheck;
	class CEditorCheckBox* m_PixelMonsterChannelCheck;
	class CEditorCheckBox* m_PixelPlayerAttackChannelCheck;
	class CEditorCheckBox* m_PixelMonsterAttackChannelCheck;
	class CEditorCheckBox* m_PixelDetailCheck;

	class CEditorListBox* m_PixelIgnoreList;


	bool	m_BoxUpdate;
	bool	m_SphereUpdate;
	bool	m_OBBUpdate;	
	bool	m_DetailStart;

	float	m_PrevSizeX;
	float	m_PrevSizeY;
	

	std::string			m_SelectListItem;
	



public:
	void SetSelectComponent(class CSceneComponent* Component);
	CSceneComponent* GetSelectComponent()
	{
		return m_SelectComponent;
	}

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);

public:
	void CreateSceneComponentWidget();
	void CreateSpriteComponentWidget();
	void CreateCameraComponentWidget();
	void CreateTargetArmComponentWidget();
	void CreateColliderComponentWidget();
	void CreatPixelColliderComponentWidget();
	void ChangeWidget(class CSceneComponent* Component);


public:
	void LoadButtonClick();
	void LoadButton1Click();
	void LoadButton2Click();

public:
	void Clear();

public:
	void ListClickCallback(int Index, const std::string& Item);
	void LoadAnimationSequence();
	void ColliderListClickCallBack(int Index, const std::string& Item);
	void ColliderClickButton();
	void ColliderCancelButton();

public:
	void CreateEditorWidgetList(ESceneComponentType Type);
};

