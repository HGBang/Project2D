#pragma once

#include "EngineInfo.h"
#include "EngineSetting.h"

class CEngine
{
private:
	HINSTANCE	m_hInst;
	HWND		m_hWnd;
	Resolution	m_WindowRS;
	float		m_ClearColor[4];
	static bool	m_Loop;
	static bool m_UITextTime;
	static std::string  m_UIText;
	class CTimer* m_Timer;
	static bool		m_EditorMode;
	static std::function<bool(HWND, UINT, WPARAM, LPARAM)>	m_WndProcFunc;
	CEngineSetting* m_Setting;	
	static unsigned int m_Number;



public:
	float GetFPS()	const;

	static unsigned int GetNumber()
	{
		return m_Number;
	}


	static std::string GetUIText()
	{
		return m_UIText;
	}

	static void SetUITextMode(bool Mode)
	{
		m_UITextTime = Mode;		
	}

	static bool GetEditorMode()	
	{
		return m_EditorMode;
	}

	static void EnableEditor()
	{
		m_EditorMode = true;
	}

	Resolution GetWindowResolution()	const
	{
		return m_WindowRS;
	}

	HWND GetWindowHandle()	const
	{
		return m_hWnd;
	}

	HINSTANCE GetWindowInstance()	const
	{
		return m_hInst;
	}

public:
	bool Init(HINSTANCE hInst, const TCHAR* Title,
		const TCHAR* ClassName, int IconID, int SmallIconID,
		unsigned int WindowWidth,
		unsigned int WindowHeight,
		unsigned int DeviceWidth, unsigned int DeviceHeight,
		bool WindowMode = true, int MenuID = 0);
	int Run();

private:
	void Logic();
	void Input(float DeltaTime);
	bool FirstUpdate(float DeltaTime);
	bool Update(float DeltaTime);
	bool PostUpdate(float DeltaTime);
	bool Collision(float DeltaTime);
	void Render(float DeltaTime);
	

public:
	static void ClearText()
	{
		m_UIText.clear();
	}


private:
	void Register(const TCHAR* ClassName, int IconID, int SmallIconID, int MenuID);
	bool Create(const TCHAR* Title, const TCHAR* ClassName);

private:
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

public:
	template <typename T>
	static void SetWndProcCallback(T* Obj, bool(T::* Func)(HWND, UINT, WPARAM, LPARAM))
	{
		m_WndProcFunc = std::bind(Func, Obj, std::placeholders::_1, std::placeholders::_2,
			std::placeholders::_3, std::placeholders::_4);
	}

	template <typename T>
	void SetEngineSetting()
	{
		SAFE_DELETE(m_Setting);

		m_Setting = new T;

		m_Setting->Init();
	}

	DECLARE_SINGLE(CEngine)
};
