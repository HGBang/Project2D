#include "EditorSliderBar.h"
CEditorSliderBar::CEditorSliderBar() 
{
}

CEditorSliderBar::~CEditorSliderBar()
{
}

bool CEditorSliderBar::Init()
{
	

	m_Int2 = 0;

	m_Int3 = 5;

	return true;
}

void CEditorSliderBar::Render()
{
	ImGui::SliderInt(m_Name.c_str(), &m_Int, m_Int2, m_Int3);


}