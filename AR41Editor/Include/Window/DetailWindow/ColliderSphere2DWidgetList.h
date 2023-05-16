#pragma once
#include "ComponentWidgetList.h"
class CColliderSphere2DWidgetList :
    public CComponentWidgetList
{
	friend class CEditorWindow;
	friend class CEditorGroup;

protected:
	CColliderSphere2DWidgetList();
	virtual ~CColliderSphere2DWidgetList();

private:
	class CEditorListBox* m_ColliderList;
	class CEditorInput* m_Name;
	class CEditorInput* m_TypeName;
	class CEditorCheckBox* m_DetailCheck;
	class CEditorInput* m_Radius;
	class CEditorSliderBar* m_SliderBarX;


	class CEditorCheckBox* m_DefaultChannelCheck;
	class CEditorCheckBox* m_PlayerChannelCheck;
	class CEditorCheckBox* m_MouseChannelCheck;
	class CEditorCheckBox* m_MonsterChannelCheck;
	class CEditorCheckBox* m_MonsterAttackChannelCheck;
	class CEditorCheckBox* m_PlayerAttackChannelCheck;

	class CEditorListBox* m_IgnoreList;

	float m_PrevSizeX;
	float m_PrevSizeY;

	bool	Sphere2DUpdate;

	std::string m_SelectListItem;

public:
	virtual bool Init();
	virtual void Render();

public:
	void ColliderListClickCallBack(int Index, const std::string& Item);
	void ColliderClickButton();
	void ColliderCancelButton();

public:
	void Clear();
	void SetAddColiderList(const std::string& Name);
};

