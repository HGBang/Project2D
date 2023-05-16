#include "DamageUI.h"
#include "UI/UIButton.h"
#include "UI/UIText.h"
#include "UI/UIProgressBar.h"
#include "UI/UINumber.h"
#include "UI/UIImage.h"
#include "UI/UIDamageNumber.h"
#include "../Scene/LoadingSceneInfo.h"
#include "Scene/SceneManager.h"
#include "Scene/Scene.h"
#include "Engine.h"
#include "../GameObject/Player2D.h"
#include "Resource/Texture/Texture.h"


CDamageUI::CDamageUI()
{
}

CDamageUI::CDamageUI(const CDamageUI& Window)
{
}

CDamageUI::~CDamageUI()
{
	CUIWindow::Start();
}

void CDamageUI::Start()
{
}

bool CDamageUI::Init()
{
	return true;
}

void CDamageUI::Update(float DeltaTime)
{
	CUIWindow::Update(DeltaTime);

    m_Pos = m_Player->GetWorldPos();
}

void CDamageUI::PostUpdate(float DeltaTime)
{
	CUIWindow::PostUpdate(DeltaTime);
}

void CDamageUI::Render()
{
	CUIWindow::Render();
}

CDamageUI* CDamageUI::Clone() const
{
	return new CDamageUI(*this);
}

void CDamageUI::Save(FILE* File)
{
	CUIWindow::Save(File);
}

void CDamageUI::Load(FILE* File)
{
	CUIWindow::Load(File);
}

void CDamageUI::SetDamageNumber(Vector2 Pos, int Damage)
{
    ++DamageNumberID;

    std::string Number = std::to_string(DamageNumberID);

    DamageID = Number;

    std::vector<const TCHAR*>	vecFileNames;

    for (int i = 0; i < 10; ++i)
    {
        TCHAR* FileName = new TCHAR[MAX_PATH];

        memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);

        wsprintf(FileName, TEXT("Damage_Number/Damage_Number%d.png"), i);

        vecFileNames.push_back(FileName);
    }

    CUIDamageNumber* DamageNumber = CreateWidget<CUIDamageNumber>(DamageID);

    DamageNumber->SetTexture("DamageNumber", vecFileNames);
    DamageNumber->SetSize(37.f, 38.f);

    for (int i = 0; i < 10; ++i)
    {
        DamageNumber->AddFrameData(Vector2(0.f, 0.f), Vector2(37.f, 38.f));
    }

    size_t Size = vecFileNames.size();

    for (size_t i = 0; i < Size; ++i)
    {
        SAFE_DELETE(vecFileNames[i]);
    }

    DamageNumber->SetPos(Pos);

    DamageNumber->SetNumber(Damage);
}


