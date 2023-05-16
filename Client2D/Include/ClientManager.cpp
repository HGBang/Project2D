#include "ClientManager.h"
#include "Scene/SceneManager.h"
#include "Scene/MainSceneInfo.h"
#include "Input.h"
#include "Setting/EngineShareSetting.h"

CClientManager::CClientManager()
{
}

CClientManager::~CClientManager()
{
    CEngine::DestroyInst();
   
}

bool CClientManager::Init(HINSTANCE hInst)
{
    if (!CEngine::GetInst()->Init(hInst, TEXT("Client2D"), TEXT("Client2D"), IDI_ICON1,
        IDI_ICON1, 1280, 720, 1280, 720, true))
    {
        return false;
    }

    CEngineShareSetting::Setting();

    CInput::GetInst()->AddBindKey("MoveUp", 'W');
    CInput::GetInst()->AddBindKey("MoveDown", 'S');

    CInput::GetInst()->AddBindKey("Rotation", 'A');
    CInput::GetInst()->AddBindKey("RotationInv", 'D');

    // SceneInfo »ý¼º
    CSceneManager::GetInst()->GetScene()->Load("GameStart.scn", SCENE_PATH);  

    return true;
}

int CClientManager::Run()
{
    return CEngine::GetInst()->Run();
}
