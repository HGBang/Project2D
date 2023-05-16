#include "EditorCheckBox.h"

CEditorCheckBox::CEditorCheckBox()
{
}

CEditorCheckBox::~CEditorCheckBox()
{
}

bool CEditorCheckBox::Init()
{
	

	return true;
}

void CEditorCheckBox::Render()
{
	ImGui::Checkbox(m_Name.c_str(), &m_True);
	
}