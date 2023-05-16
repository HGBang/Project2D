#pragma once
#include "Editor\EditorWindow.h"
class CSceneWindow :
    public CEditorWindow
{
	friend class CEditorGUIManager;

protected:
	CSceneWindow();
	virtual ~CSceneWindow();

private:
	class CEditorListBox* m_SceneList;
	std::string			m_SelectSceneItem;

	class CEditorInput* m_SceneSaveName;
	class CEditorInput* m_SceneSelectName;


	// 纠积己
	class CEditorListBox*	m_SceneCreateList;
	std::string				m_SelectSceneInfoItem;
	class CEditorButton*	m_SceneCreateButton;
	class CEditorInput*		m_CreateSceneName;




public:
	const std::string& GetSelectSceneItem()	const
	{
		return m_SelectSceneItem;
	}


public:
	virtual bool Init();
	virtual void Update(float DeltaTime);

public:
	void SceneChange();
	void SceneSave();
	void SceneClickCallback(int Index, const std::string& Item);
	void LoadSceneDirectory();
	

public: // 纠积己
	void SceneInfoListCallback(int Index, const std::string& Item);
	void SceneCreateButtonCallback();
	void LoadSceneInfo();
	
	

};

