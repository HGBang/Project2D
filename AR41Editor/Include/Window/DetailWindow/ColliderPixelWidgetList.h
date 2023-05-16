#pragma once
#include "ComponentWidgetList.h"
class CColliderPixelWidgetList :
    public CComponentWidgetList
{
	friend class CEditorWindow;
	friend class CEditorGroup;

protected:
	CColliderPixelWidgetList();
	virtual ~CColliderPixelWidgetList();

private:
	class CEditorListBox* m_PixelColliderList;
	class CEditorListBox* m_PixelIgnoreList;

	class CEditorInput* m_PixelName;
	class CEditorInput* m_PixelRed;
	class CEditorInput* m_PixelBlue;
	class CEditorInput* m_PixelGreen;
	class CEditorInput* m_PixelAlpha;

	class CEditorCheckBox* m_PixelColorIgnore;
	class CEditorCheckBox* m_PixelColorConfirm;

	class CEditorCheckBox* m_PixelAlphaIgnore;
	class CEditorCheckBox* m_PixelAlphaConfirm;

	class CEditorCheckBox* m_PixelDefaultChannelCheck;
	class CEditorCheckBox* m_PixelPlayerChannelCheck;
	class CEditorCheckBox* m_PixelMouseChannelCheck;
	class CEditorCheckBox* m_PixelMonsterChannelCheck;
	class CEditorCheckBox* m_PixelMonsterAttackChannelCheck;
	class CEditorCheckBox* m_PixelPlayerAttackChannelCheck;

	std::string		m_SelectListItem;

public:
	virtual bool Init();
	virtual void Render();

public:
	void SetAddColiderList(const std::string& Name);

public:
	void ColliderListClickCallBack(int Index, const std::string& Item);
	void ColliderClickButton();
	void ColliderCancelButton();
	void Clear();

};

