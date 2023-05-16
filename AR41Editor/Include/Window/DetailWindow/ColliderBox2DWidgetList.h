#pragma once
#include "ComponentWidgetList.h"
#include "../DetailWindow.h"

class CColliderBox2DWidgetList : public CComponentWidgetList
{
	friend class CEditorWindow;
	friend class CEditorGroup;

protected:
	CColliderBox2DWidgetList();
	virtual ~CColliderBox2DWidgetList();

private:
	class CEditorListBox* m_ColliderList;
	class CEditorInput* m_Name;
	class CEditorInput* m_TypeName;
	class CEditorCheckBox* m_DetailCheck;
	class CEditorInput* m_StartX;
	class CEditorInput* m_StartY;
	class CEditorSliderBar* m_SliderBarX;
	class CEditorSliderBar* m_SliderBarY;
	
	class CEditorCheckBox* m_DefaultChannelCheck;
	class CEditorCheckBox* m_PlayerChannelCheck;
	class CEditorCheckBox* m_MouseChannelCheck;
	class CEditorCheckBox* m_MonsterChannelCheck;
	class CEditorCheckBox* m_MonsterAttackChannelCheck;
	class CEditorCheckBox* m_PlayerAttackChannelCheck;
	
	class CEditorListBox* m_IgnoreList;
	
	float m_PrevSizeX;
	float m_PrevSizeY;

	bool	Box2DUpdate;

	std::string m_SelectListItem;

public:
	void ColliderListClickCallBack(int Index, const std::string& Item);
	void ColliderClickButton();
	void ColliderCancelButton();

public:
	void Clear();
	void SetAddColiderList(const std::string& Name);


public:
	virtual bool Init();
	virtual void Render();
};

