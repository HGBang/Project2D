#pragma once
#include "EditorWidget.h"
class CEditorSliderBar :
    public CEditorWidget
{
	friend class CEditorWindow;
	friend class CEditorGroup;

	template <typename T>
	friend class CEditorTreeItem;

protected:
	CEditorSliderBar();
	virtual ~CEditorSliderBar();

private:

	int		m_Int;

	int		m_Int2;

	int		m_Int3;

	char	m_SliderName;
	

public:
	void SetInt(int Int)
	{
		m_Int = Int;
	}

	void SetInt2(int Int)
	{
		m_Int2 = Int;
	}

	void SetInt3(int Int)
	{
		m_Int3 = Int;
	}

	int GetInt()
	{
		return m_Int;
	}

	

public:
	virtual bool Init();
	virtual void Render();
};

