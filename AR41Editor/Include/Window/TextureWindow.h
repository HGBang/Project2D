#pragma once
#include "Editor\EditorWindow.h"
class CTextureWindow :
    public CEditorWindow
{
	friend class CEditorGUIManager;
	friend class CMaterialManager;

protected:
	CTextureWindow();
	virtual ~CTextureWindow();

private:
	class CEditorListBox* m_TextureList;
	std::string			m_SelectTextureItem;

	class CEditorInput* m_TextureSelectName;
	class CEditorImage* m_Texture;

	CSharedPtr<class CGameObject> m_PlayerObject;



public:
	const std::string& GetSelectTextureItem()	const
	{
		return m_SelectTextureItem;
	}


public:
	virtual bool Init();
	virtual void Update(float DeltaTime);

private:
	void TextureClickCallback(int Index, const std::string& Item);
	void TextureCreateCallback();
	void TextureColorCallback();

private:
	void LoadGameTextureName();

public:
	static float GetR();
	static float GetG();
	static float GetB();
	static float GetA();
};

