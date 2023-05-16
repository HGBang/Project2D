#pragma once
#include "EditorWidget.h"
class CEditorCheckBox :
    public CEditorWidget
{
	friend class CEditorWindow;
	friend class CEditorGroup;

	template <typename T>
	friend class CEditorTreeItem;

protected:
	CEditorCheckBox();
	virtual ~CEditorCheckBox();

private:
	bool	m_LoopTrue;
	bool	m_ReverseTrue;
	bool	m_True;


public:
	void SetTrue(bool True)
	{
		m_True = True;
	}

public:
	bool GetTrue() const
	{
		return m_True;
	}


public:
	virtual bool Init();
	virtual void Render();
};

