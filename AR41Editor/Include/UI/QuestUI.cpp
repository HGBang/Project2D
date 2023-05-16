#include "QuestUI.h"
#include "UI/UIImage.h"
#include "UI/UIButton.h"
#include "UI/UINumber.h"
#include "UI/UIText.h"
#include "Scene/Scene.h"
#include "Scene/SceneManager.h"
#include "Resource/ResourceManager.h"
#include "Resource/Sound/Sound.h"
#include "../GameObject/Player2D.h"
#include "Engine.h"
#include "Input.h"
#include "TimerManager.h"
#include "../Setting/DefaultSetting.h"
#include "../Setting/EngineShareSetting.h"
#include "../GamePlayerSaveLoad.h"

CQuestUI::CQuestUI() : 
	m_FrontQuest(false),
	m_HelenaFirstQuest(false),
	m_HelenaSecondQuest(false)
{
	m_WindowTypeName = "QuestUI";
}

CQuestUI::CQuestUI(const CQuestUI& Window) :
	CUIWindow(Window)
{
	m_QuestAlarmImage = FindWidget<CUIImage>("QuestAlarmImage");
	m_QuestAlarmText = FindWidget<CUIText>("QuestAlarmText");
	m_QuestAlarmButton = FindWidget<CUIButton>("QuestAlarmButton");
}

CQuestUI::~CQuestUI()
{
}

void CQuestUI::FirstQuestText()
{
	if (m_QuestIngListText)
	{
		lstrcpy(m_QuestText, L"못보던 젊은이구만, 혹시 나좀 도와줄수 있겟나..?\
			마을로돌아가야 하는데... \
저 버섯이 길을 막고있어서 말이야,,,,,,,,,,        내가 무기를 줄테니 이걸 한번 써보겠나 ???? 나는 쓸줄을 몰라서..                             \
자네라면 능숙하게 사용할수 있을걸세!");

		m_TextCount = (int)lstrlen(m_QuestText);

		if (m_TextIndex < m_TextCount)
		{
			m_TextTime += g_DeltaTime;

			if (m_TextTime >= 0.05f)
			{
				m_TextTime -= 0.05f;

				TCHAR Text[2] = {};
				Text[0] = m_QuestText[m_TextIndex];

				m_QuestIngListText->Append(Text);

				++m_TextIndex;

				if (m_TextIndex > 110)
					m_WeaponImageOn = true;
			}
		}
	}
}

void CQuestUI::ClassChanageText()
{
}

void CQuestUI::BossQuestText()
{
}

void CQuestUI::FirstQuestIngText()
{
	if (m_QuestIngListText)
	{
		lstrcpy(m_QuestText, L"마을에 기다리고 있는 사람이 있다네 .. 얼른 해치워 주게나");

		m_TextCount = (int)lstrlen(m_QuestText);

		if (m_TextIndex < m_TextCount)
		{
			m_TextTime += g_DeltaTime;

			if (m_TextTime >= 0.05f)
			{
				m_TextTime -= 0.05f;

				TCHAR Text[2] = {};
				Text[0] = m_QuestText[m_TextIndex];

				m_QuestIngListText->Append(Text);

				++m_TextIndex;			
			}
		}
	}
}

void CQuestUI::ClassChanageIngText()
{
}

void CQuestUI::BossQuestIngText()
{
}

void CQuestUI::FirstQuestCompleteText()
{
	if (m_QuestIngListText)
	{
		lstrcpy(m_QuestText, L"고맙네, 마을로 돌아가서 궁수 교습소로 가보게");

		m_TextCount = (int)lstrlen(m_QuestText);

		if (m_TextIndex < m_TextCount)
		{
			m_TextTime += g_DeltaTime;

			if (m_TextTime >= 0.05f)
			{
				m_TextTime -= 0.05f;

				TCHAR Text[2] = {};
				Text[0] = m_QuestText[m_TextIndex];

				m_QuestIngListText->Append(Text);

				++m_TextIndex;
			}
		}
	}
}

void CQuestUI::ClassChanageCompleteText()
{
}

void CQuestUI::BossQuestCompleteText()
{
	
}

void CQuestUI::HelenaFirstQuestText()
{
	if (m_QuestIngListText)
	{
		lstrcpy(m_QuestText, L"장로님을 도와줘서 정말 감사해 , 큰일날뻔했어 \
			답례로 기술을 알려줄게 \
Shift키, PageDown키를 눌러서 사용할 수 있을거야 ~      너무 많이사용하면 MP가 없어질테니 주의하도록 해 ");

		m_TextCount = (int)lstrlen(m_QuestText);

		if (m_TextIndex < m_TextCount)
		{
			m_TextTime += g_DeltaTime;

			if (m_TextTime >= 0.05f)
			{
				m_TextTime -= 0.05f;

				TCHAR Text[2] = {};
				Text[0] = m_QuestText[m_TextIndex];

				m_QuestIngListText->Append(Text);

				++m_TextIndex;

				if (m_TextIndex > 100)
					m_Skill1ImageOn = true;
			}
		}
	}
}

void CQuestUI::HelenaNoQuestText()
{
	if (m_QuestIngListText)
	{
		lstrcpy(m_QuestText, L"레벨10이 되면 다시 올래 ? ");

		m_TextCount = (int)lstrlen(m_QuestText);

		if (m_TextIndex < m_TextCount)
		{
			m_TextTime += g_DeltaTime;

			if (m_TextTime >= 0.05f)
			{
				m_TextTime -= 0.05f;

				TCHAR Text[2] = {};
				Text[0] = m_QuestText[m_TextIndex];

				m_QuestIngListText->Append(Text);

				++m_TextIndex;

			}
		}
	}
}

void CQuestUI::HelenaSecondQuestText()
{

	if (m_QuestIngListText)
	{
		lstrcpy(m_QuestText, L"레벨10이 되었구나.           정말 놀라워 \
			   우리가문의 비기를 알려줄게.  \
Space키를 눌러서 사용할 수 있을거야 ~  힘에 휘둘리지 않도록 조심해  .. 그리고 이건 내 선물이야   ");

		m_TextCount = (int)lstrlen(m_QuestText);

		if (m_TextIndex < m_TextCount)
		{
			m_TextTime += g_DeltaTime;

			if (m_TextTime >= 0.05f)
			{
				m_TextTime -= 0.05f;

				TCHAR Text[2] = {};
				Text[0] = m_QuestText[m_TextIndex];

				m_QuestIngListText->Append(Text);

				++m_TextIndex;

				if (m_TextIndex > 100)
					m_Skill2ImageOn = true;

			}
		}
	}

}

void CQuestUI::Start()
{
	CUIWindow::Start();

}

bool CQuestUI::Init()
{
	CUIWindow::Init();
	
	m_QuestAlarmImage = CreateWidget<CUIImage>("QuestAlarmImage");
	m_QuestAlarmImage->SetSize(181.f, 41.f);
	m_QuestAlarmImage->SetPos(1050.f, 350.f);
	m_QuestAlarmImage->SetTexture("QuestAlarmImage", TEXT("QuestAlarm/QuestAlarmImage.png"));

	m_QuestAlarmText = CreateWidget<CUIText>("QuestAlarmText");
	m_QuestAlarmText->SetSize(100.f, 30.f);
	m_QuestAlarmText->SetPos(1080.f, 360.f);
	m_QuestAlarmText->SetFont("Default");
	m_QuestAlarmText->SetFontSize(10.f);
	m_QuestAlarmText->SetColor(255,255,255);
	m_QuestAlarmText->SetText(TEXT("퀘스트 알림이"));

	m_QuestAlarmButton = CreateWidget<CUIButton>("QuestAlarmButton");
	m_QuestAlarmButton->SetSize(13.f, 12.f);
	m_QuestAlarmButton->SetPos(1060.f, 375.f);
	m_QuestAlarmButton->SetTexture(EButtonState::Normal, "QuestAlarmButton_Normal", TEXT("QuestAlarm/QuestAlarmButton.png"));
	m_QuestAlarmButton->SetTexture(EButtonState::Hovered, "QuestAlarmButton_Hov", TEXT("QuestAlarm/QuestAlarmButton_Hov.png"));
	m_QuestAlarmButton->SetTexture(EButtonState::Click, "QuestAlarmButton_Click", TEXT("QuestAlarm/QuestAlarmButton_Click.png"));
		
	m_QuestTitleText = CreateWidget<CUIText>("QuestTitleText");
	m_QuestTitleText->SetSize(100.f, 30.f);
	m_QuestTitleText->SetPos(1080.f, 340.f);
	m_QuestTitleText->SetFont("Default");
	m_QuestTitleText->SetFontSize(10.f);
	m_QuestTitleText->SetColor(255, 255, 255);
	m_QuestTitleText->SetText(TEXT("머쉬맘 처치"));
	m_QuestTitleText->SetEnable(false);

	m_QuestComplateText = CreateWidget<CUIText>("QuestComplateText");
	m_QuestComplateText->SetSize(100.f, 30.f);
	m_QuestComplateText->SetPos(1180.f, 340.f);
	m_QuestComplateText->SetFont("Default");
	m_QuestComplateText->SetFontSize(10.f);
	m_QuestComplateText->SetColor(255, 0, 0);
	m_QuestComplateText->SetText((TEXT("미완료")));
	m_QuestComplateText->SetEnable(false);



	return true;
}

void CQuestUI::Update(float DeltaTime)
{
	CUIWindow::Update(DeltaTime);

	if (m_Player)
	{

		if (!m_Player->GetSkill1Lock())
		{
			if (m_Player->GetHelenaFirstQuestOn())
			{
				m_HelenaFirstQuest = true;
				m_FrontQuest = false;
			}
		}

		if (!m_Player->GetSkill2Lock())
		{
			if (m_Player->GetLevel() >= 10)
			{
				//m_ClassChangeQuest = true;
				m_HelenaSecondQuest = true;
				m_HelenaNoQuest = false;
			}
		}
		if (m_Player->GetLevel() >= 20)
			m_BossQuest = true;

		if (m_Player->GetFrontQuestComplete())
		{
			m_FrontQuestComplete = true;
			m_QuestIng = false;
		}
	}

	if (m_QuestIngListText && m_FrontQuest)
		FirstQuestText();

	if (m_QuestIng)
		FirstQuestIngText();

	if (m_HelenaFirstQuest)
		HelenaFirstQuestText();

	if (m_HelenaSecondQuest)
		HelenaSecondQuestText();

	if (m_HelenaNoQuest)
		HelenaNoQuestText();
	
	if (m_FrontQuestComplete)
	{
		m_QuestComplateText->SetText(TEXT("완료"));
		m_QuestComplateText->SetColor(0, 255, 0);
		FirstQuestCompleteText();
	}

	if (m_WeaponImageOn && m_FrontQuest)
	{		
		m_QuestItemImage = CreateWidget<CUIImage>("QuestItemImage");
		m_QuestItemImage->SetSize(35.f, 35.f);
		m_QuestItemImage->SetPos(560.f, 330.f);
		m_QuestItemImage->SetTexture("QuestItemImage", TEXT("Weapon1/WeaponEquip.png"));
		m_WeaponImageOn = false;
	}

	if (m_Skill1ImageOn && m_HelenaFirstQuest)
	{
		m_QuestItemImage = CreateWidget<CUIImage>("QuestSkill1Image");
		m_QuestItemImage->SetSize(35.f, 35.f);
		m_QuestItemImage->SetPos(560.f, 330.f);
		m_QuestItemImage->SetTexture("QuestSkillImage", TEXT("KeyIcon/SpeedDualShotIcon.png"));

		m_QuestItemImage1 = CreateWidget<CUIImage>("QuestSkillJumpImage");
		m_QuestItemImage1->SetSize(32.f, 32.f);
		m_QuestItemImage1->SetPos(600.f, 330.f);
		m_QuestItemImage1->SetTexture("QuestSkillJumpImage", TEXT("KeyIcon/FlashJumpIcon.png"));
		m_Skill1ImageOn = false;
	}

	if (m_Skill2ImageOn && m_HelenaSecondQuest)
	{
		m_QuestItemImage = CreateWidget<CUIImage>("QuestSkill2Image");
		m_QuestItemImage->SetSize(35.f, 35.f);
		m_QuestItemImage->SetPos(560.f, 330.f);
		m_QuestItemImage->SetTexture("QuestSkill2Image", TEXT("KeyIcon/RingIcon.png"));

		m_QuestWeaponImage = CreateWidget<CUIImage>("QuestWeapon2Image");
		m_QuestWeaponImage->SetSize(37.f, 36.f);
		m_QuestWeaponImage->SetPos(600.f, 330.f);
		m_QuestWeaponImage->SetTexture("QuestWeapon2Image", TEXT("Weapon2/WeaponInv.png"));
		m_Skill2ImageOn = false;
	}


}

void CQuestUI::PostUpdate(float DeltaTime)
{
	CUIWindow::PostUpdate(DeltaTime);
}

void CQuestUI::Render()
{
	CUIWindow::Render();
}

CQuestUI* CQuestUI::Clone()
{
	return new CQuestUI(*this);
}

void CQuestUI::SetQuestIng()
{
	m_QuestChatBoxImage = CreateWidget<CUIImage>("QuestChatBoxImage");
	m_QuestChatBoxImage->SetPos(400.f, 280.f);
	m_QuestChatBoxImage->SetSize(519.f, 167.f);
	m_QuestChatBoxImage->SetTexture("QuestChatBoxImage", TEXT("NpcChatBox/NpcChatBox.png"));

	m_QuestNpcImage = CreateWidget<CUIImage>("QuestNpcImage");
	m_QuestNpcImage->SetPos(450.f, 335.f);
	m_QuestNpcImage->SetSize(50.f, 73.f);
	m_QuestNpcImage->SetTexture("QuestNpcImage", TEXT("ElderNormal.png"));

	m_QuestIngListText = CreateWidget<CUIText>("QuestText");
	m_QuestIngListText->SetFont("MapleDefault");
	m_QuestIngListText->SetColor(0, 0, 0);
	m_QuestIngListText->SetSize(340.f, 30.f);
	m_QuestIngListText->SetFontSize(11.f);
	m_QuestIngListText->SetPos(560.f, 400.f);
	m_QuestIngListText->SetFontSize(12.f);
	m_QuestIngListText->SetText(TEXT(""));

	m_QuestExitButton = CreateWidget<CUIButton>("QuestExitButton");
	m_QuestExitButton->SetSize(12.f, 12.f);
	m_QuestExitButton->SetPos(890.f, 420.f);
	m_QuestExitButton->SetTexture(EButtonState::Normal, "ExitButton_Normal", TEXT("CloseButton/CloseButton_Normal.png"));
	m_QuestExitButton->SetTexture(EButtonState::Hovered, "ExitButton_Hovered", TEXT("CloseButton/CloseButton_Hov.png"));
	m_QuestExitButton->SetTexture(EButtonState::Click, "ExitButton_Click", TEXT("CloseButton/CloseButton_Click.png"));
	m_QuestExitButton->SetCallback(EButtonEventState::Click, this, &CQuestUI::QuestExitButtonClick);
}

void CQuestUI::SetFrontQuest()
{
	m_QuestChatBoxImage = CreateWidget<CUIImage>("QuestChatBoxImage");
	m_QuestChatBoxImage->SetPos(400.f, 280.f);
	m_QuestChatBoxImage->SetSize(519.f, 167.f);
	m_QuestChatBoxImage->SetTexture("QuestChatBoxImage", TEXT("NpcChatBox/NpcChatBox.png"));

	m_QuestNpcImage = CreateWidget<CUIImage>("QuestNpcImage");
	m_QuestNpcImage->SetPos(450.f, 335.f);
	m_QuestNpcImage->SetSize(50.f, 73.f);
	m_QuestNpcImage->SetTexture("QuestNpcImage", TEXT("ElderNormal.png"));

	m_QuestIngListText = CreateWidget<CUIText>("QuestText");
	m_QuestIngListText->SetFont("MapleDefault");
	m_QuestIngListText->SetColor(0, 0, 0);
	m_QuestIngListText->SetSize(340.f, 30.f);
	m_QuestIngListText->SetFontSize(11.f);
	m_QuestIngListText->SetPos(560.f, 400.f);
	m_QuestIngListText->SetFontSize(12.f);
    m_QuestIngListText->SetText(TEXT(""));

	m_QuestOkButton = CreateWidget<CUIButton>("QuestOkButton");
	m_QuestOkButton->SetSize(57.f, 16.f);
	m_QuestOkButton->SetPos(770.f, 288.f);
	m_QuestOkButton->SetTexture(EButtonState::Normal, "QuestOK_Normal", TEXT("QuestOK/QuestOK_Normal.png"));
	m_QuestOkButton->SetTexture(EButtonState::Hovered, "QuestOK_Hovered", TEXT("QuestOK/QuestOK_Hov.png"));
	m_QuestOkButton->SetTexture(EButtonState::Click, "QuestOK_Click", TEXT("QuestOK/QuestOK_Click.png"));
	m_QuestOkButton->SetCallback(EButtonEventState::Click, this, &CQuestUI::QuestOkButtonClick);

	m_QuestCancelButton = CreateWidget<CUIButton>("QuestCancelButton");
	m_QuestCancelButton->SetSize(57.f, 16.f);
	m_QuestCancelButton->SetPos(840.f, 288.f);
	m_QuestCancelButton->SetTexture(EButtonState::Normal, "QuestNo_Normal", TEXT("QuestNo/QuestNo_Normal.png"));
	m_QuestCancelButton->SetTexture(EButtonState::Hovered, "QuestNo_Hovered", TEXT("QuestNo/QuestNo_Hov.png"));
	m_QuestCancelButton->SetTexture(EButtonState::Click, "QuestNo_Click", TEXT("QuestNo/QuestNo_Click.png"));
	m_QuestCancelButton->SetCallback(EButtonEventState::Click, this, &CQuestUI::QuestCancelButtonClick);

	m_QuestExitButton = CreateWidget<CUIButton>("QuestExitButton");
	m_QuestExitButton->SetSize(12.f, 12.f);
	m_QuestExitButton->SetPos(890.f, 420.f);
	m_QuestExitButton->SetTexture(EButtonState::Normal, "ExitButton_Normal", TEXT("CloseButton/CloseButton_Normal.png"));
	m_QuestExitButton->SetTexture(EButtonState::Hovered, "ExitButton_Hovered", TEXT("CloseButton/CloseButton_Hov.png"));
	m_QuestExitButton->SetTexture(EButtonState::Click, "ExitButton_Click", TEXT("CloseButton/CloseButton_Click.png"));
	m_QuestExitButton->SetCallback(EButtonEventState::Click, this, &CQuestUI::QuestExitButtonClick);

	m_Player->SetFrontQuestOn(true);

}

void CQuestUI::SetFrontQuestComplete()
{
	m_QuestChatBoxImage = CreateWidget<CUIImage>("QuestChatBoxImage");
	m_QuestChatBoxImage->SetPos(400.f, 280.f);
	m_QuestChatBoxImage->SetSize(519.f, 167.f);
	m_QuestChatBoxImage->SetTexture("QuestChatBoxImage", TEXT("NpcChatBox/NpcChatBox.png"));

	m_QuestNpcImage = CreateWidget<CUIImage>("QuestNpcImage");
	m_QuestNpcImage->SetPos(450.f, 335.f);
	m_QuestNpcImage->SetSize(50.f, 73.f);
	m_QuestNpcImage->SetTexture("QuestNpcImage", TEXT("ElderNormal.png"));

	m_QuestIngListText = CreateWidget<CUIText>("QuestText");
	m_QuestIngListText->SetFont("MapleDefault");
	m_QuestIngListText->SetColor(0, 0, 0);
	m_QuestIngListText->SetSize(340.f, 30.f);
	m_QuestIngListText->SetFontSize(11.f);
	m_QuestIngListText->SetPos(560.f, 400.f);
	m_QuestIngListText->SetFontSize(12.f);
	m_QuestIngListText->SetText(TEXT(""));

	m_QuestExitButton = CreateWidget<CUIButton>("QuestExitButton");
	m_QuestExitButton->SetSize(12.f, 12.f);
	m_QuestExitButton->SetPos(890.f, 420.f);
	m_QuestExitButton->SetTexture(EButtonState::Normal, "ExitButton_Normal", TEXT("CloseButton/CloseButton_Normal.png"));
	m_QuestExitButton->SetTexture(EButtonState::Hovered, "ExitButton_Hovered", TEXT("CloseButton/CloseButton_Hov.png"));
	m_QuestExitButton->SetTexture(EButtonState::Click, "ExitButton_Click", TEXT("CloseButton/CloseButton_Click.png"));
	m_QuestExitButton->SetCallback(EButtonEventState::Click, this, &CQuestUI::QuestExitButtonClick);

	m_QuestComplateButton = CreateWidget<CUIButton>("QuestCompleteButton");
	m_QuestComplateButton->SetSize(72.f, 16.f);
	m_QuestComplateButton->SetPos(770.f, 288.f);
	m_QuestComplateButton->SetTexture(EButtonState::Normal, "QuestCompleteButton_Normal", TEXT("QuestCompleteButton/QuestCompleteButton_Normal.png"));
	m_QuestComplateButton->SetTexture(EButtonState::Hovered, "QuestCompleteButton_Hov", TEXT("QuestCompleteButton/QuestCompleteButton_Hov.png"));
	m_QuestComplateButton->SetTexture(EButtonState::Click, "QuestCompleteButton_Click", TEXT("QuestCompleteButton/QuestCompleteButton_Click.png"));
	m_QuestComplateButton->SetCallback(EButtonEventState::Click, this, &CQuestUI::QuestCompleteClick);

}

void CQuestUI::SetHelenaFirstQuest()
{
	m_QuestChatBoxImage = CreateWidget<CUIImage>("QuestChatBoxImage");
	m_QuestChatBoxImage->SetPos(400.f, 280.f);
	m_QuestChatBoxImage->SetSize(519.f, 167.f);
	m_QuestChatBoxImage->SetTexture("QuestChatBoxImage", TEXT("NpcChatBox/NpcChatBox.png"));

	m_QuestNpcImage = CreateWidget<CUIImage>("QuestHeleneImage");
	m_QuestNpcImage->SetPos(450.f, 335.f);
	m_QuestNpcImage->SetSize(78.f, 80.f);
	m_QuestNpcImage->SetTexture("QuestHeleneImage", TEXT("Helena/Helena0.png"));

	m_QuestIngListText = CreateWidget<CUIText>("QuestText");
	m_QuestIngListText->SetFont("MapleDefault");
	m_QuestIngListText->SetColor(0, 0, 0);
	m_QuestIngListText->SetSize(340.f, 30.f);
	m_QuestIngListText->SetFontSize(11.f);
	m_QuestIngListText->SetPos(560.f, 400.f);
	m_QuestIngListText->SetFontSize(12.f);
	m_QuestIngListText->SetText(TEXT(""));

	m_QuestOkButton = CreateWidget<CUIButton>("QuestOkButton");
	m_QuestOkButton->SetSize(57.f, 16.f);
	m_QuestOkButton->SetPos(770.f, 288.f);
	m_QuestOkButton->SetTexture(EButtonState::Normal, "QuestOK_Normal", TEXT("QuestOK/QuestOK_Normal.png"));
	m_QuestOkButton->SetTexture(EButtonState::Hovered, "QuestOK_Hovered", TEXT("QuestOK/QuestOK_Hov.png"));
	m_QuestOkButton->SetTexture(EButtonState::Click, "QuestOK_Click", TEXT("QuestOK/QuestOK_Click.png"));
	m_QuestOkButton->SetCallback(EButtonEventState::Click, this, &CQuestUI::QuestOkButtonClick);

	m_QuestExitButton = CreateWidget<CUIButton>("QuestExitButton");
	m_QuestExitButton->SetSize(12.f, 12.f);
	m_QuestExitButton->SetPos(890.f, 420.f);
	m_QuestExitButton->SetTexture(EButtonState::Normal, "ExitButton_Normal", TEXT("CloseButton/CloseButton_Normal.png"));
	m_QuestExitButton->SetTexture(EButtonState::Hovered, "ExitButton_Hovered", TEXT("CloseButton/CloseButton_Hov.png"));
	m_QuestExitButton->SetTexture(EButtonState::Click, "ExitButton_Click", TEXT("CloseButton/CloseButton_Click.png"));
	m_QuestExitButton->SetCallback(EButtonEventState::Click, this, &CQuestUI::QuestExitButtonClick);
}

void CQuestUI::SetHelenaNoQuest()
{
	m_QuestChatBoxImage = CreateWidget<CUIImage>("QuestChatBoxImage");
	m_QuestChatBoxImage->SetPos(400.f, 280.f);
	m_QuestChatBoxImage->SetSize(519.f, 167.f);
	m_QuestChatBoxImage->SetTexture("QuestChatBoxImage", TEXT("NpcChatBox/NpcChatBox.png"));

	m_QuestNpcImage = CreateWidget<CUIImage>("QuestHeleneImage");
	m_QuestNpcImage->SetPos(450.f, 335.f);
	m_QuestNpcImage->SetSize(78.f, 80.f);
	m_QuestNpcImage->SetTexture("QuestHeleneImage", TEXT("Helena/Helena0.png"));

	m_QuestIngListText = CreateWidget<CUIText>("QuestText");
	m_QuestIngListText->SetFont("MapleDefault");
	m_QuestIngListText->SetColor(0, 0, 0);
	m_QuestIngListText->SetSize(340.f, 30.f);
	m_QuestIngListText->SetFontSize(11.f);
	m_QuestIngListText->SetPos(560.f, 400.f);
	m_QuestIngListText->SetFontSize(12.f);
	m_QuestIngListText->SetText(TEXT(""));

	m_QuestOkButton = CreateWidget<CUIButton>("QuestOkButton");
	m_QuestOkButton->SetSize(57.f, 16.f);
	m_QuestOkButton->SetPos(770.f, 288.f);
	m_QuestOkButton->SetTexture(EButtonState::Normal, "QuestOK_Normal", TEXT("QuestOK/QuestOK_Normal.png"));
	m_QuestOkButton->SetTexture(EButtonState::Hovered, "QuestOK_Hovered", TEXT("QuestOK/QuestOK_Hov.png"));
	m_QuestOkButton->SetTexture(EButtonState::Click, "QuestOK_Click", TEXT("QuestOK/QuestOK_Click.png"));
	m_QuestOkButton->SetCallback(EButtonEventState::Click, this, &CQuestUI::QuestOkButtonClick);

	m_QuestExitButton = CreateWidget<CUIButton>("QuestExitButton");
	m_QuestExitButton->SetSize(12.f, 12.f);
	m_QuestExitButton->SetPos(890.f, 420.f);
	m_QuestExitButton->SetTexture(EButtonState::Normal, "ExitButton_Normal", TEXT("CloseButton/CloseButton_Normal.png"));
	m_QuestExitButton->SetTexture(EButtonState::Hovered, "ExitButton_Hovered", TEXT("CloseButton/CloseButton_Hov.png"));
	m_QuestExitButton->SetTexture(EButtonState::Click, "ExitButton_Click", TEXT("CloseButton/CloseButton_Click.png"));
	m_QuestExitButton->SetCallback(EButtonEventState::Click, this, &CQuestUI::QuestExitButtonClick);
}

void CQuestUI::SetHelenaSecondQuest()
{
	m_QuestChatBoxImage = CreateWidget<CUIImage>("QuestChatBoxImage");
	m_QuestChatBoxImage->SetPos(400.f, 280.f);
	m_QuestChatBoxImage->SetSize(519.f, 167.f);
	m_QuestChatBoxImage->SetTexture("QuestChatBoxImage", TEXT("NpcChatBox/NpcChatBox.png"));

	m_QuestNpcImage = CreateWidget<CUIImage>("QuestHeleneImage");
	m_QuestNpcImage->SetPos(450.f, 335.f);
	m_QuestNpcImage->SetSize(78.f, 80.f);
	m_QuestNpcImage->SetTexture("QuestHeleneImage", TEXT("Helena/Helena0.png"));

	m_QuestIngListText = CreateWidget<CUIText>("QuestText");
	m_QuestIngListText->SetFont("MapleDefault");
	m_QuestIngListText->SetColor(0, 0, 0);
	m_QuestIngListText->SetSize(340.f, 30.f);
	m_QuestIngListText->SetFontSize(11.f);
	m_QuestIngListText->SetPos(560.f, 400.f);
	m_QuestIngListText->SetFontSize(12.f);
	m_QuestIngListText->SetText(TEXT(""));

	m_QuestOkButton = CreateWidget<CUIButton>("QuestOkButton");
	m_QuestOkButton->SetSize(57.f, 16.f);
	m_QuestOkButton->SetPos(770.f, 288.f);
	m_QuestOkButton->SetTexture(EButtonState::Normal, "QuestOK_Normal", TEXT("QuestOK/QuestOK_Normal.png"));
	m_QuestOkButton->SetTexture(EButtonState::Hovered, "QuestOK_Hovered", TEXT("QuestOK/QuestOK_Hov.png"));
	m_QuestOkButton->SetTexture(EButtonState::Click, "QuestOK_Click", TEXT("QuestOK/QuestOK_Click.png"));
	m_QuestOkButton->SetCallback(EButtonEventState::Click, this, &CQuestUI::QuestOkButtonClick);

	m_QuestExitButton = CreateWidget<CUIButton>("QuestExitButton");
	m_QuestExitButton->SetSize(12.f, 12.f);
	m_QuestExitButton->SetPos(890.f, 420.f);
	m_QuestExitButton->SetTexture(EButtonState::Normal, "ExitButton_Normal", TEXT("CloseButton/CloseButton_Normal.png"));
	m_QuestExitButton->SetTexture(EButtonState::Hovered, "ExitButton_Hovered", TEXT("CloseButton/CloseButton_Hov.png"));
	m_QuestExitButton->SetTexture(EButtonState::Click, "ExitButton_Click", TEXT("CloseButton/CloseButton_Click.png"));
	m_QuestExitButton->SetCallback(EButtonEventState::Click, this, &CQuestUI::QuestExitButtonClick);
}



void CQuestUI::QuestOkButtonClick()
{
	ClearUI();

	if (m_FrontQuest)
	{
		m_FrontQuest = false;
		m_QuestIng = true;
		m_QuestTitleText->SetEnable(true);
		m_QuestComplateText->SetEnable(true);

	}	

	if (m_ClassChangeQuest)
		m_ClassChangeQuest = false;
	
	if (m_BossQuest)
		m_BossQuest = false;

	if (!m_FrontQuest && m_HelenaFirstQuest)
	{
		m_HelenaFirstQuest = false;
		m_HelenaNoQuest = true;

		m_Player->SetSkill1Lock(true);	
		m_Player->SetHelenaFirstQuestOn(false);
	}

	if (m_HelenaSecondQuest)
	{
		m_HelenaSecondQuest = false;
		m_HelenaNoQuest = false;

		m_Player->SetSkill2Lock(true);
	}



}

void CQuestUI::QuestCancelButtonClick()
{
	ClearUI();
}

void CQuestUI::QuestExitButtonClick()
{
	ClearUI();
}

void CQuestUI::QuestCompleteClick()
{
	ClearUI();	

	m_QuestIng = false;
	m_FrontQuest = false;

	m_Player->SetFrontQuestComplete(false);


	m_FrontQuestComplete = false;
	m_NoQuest = true;
	
	m_QuestTitleText->SetText(TEXT(""));
	m_QuestComplateText->SetText(TEXT(""));

	m_Player->SetHelenaFirstQuestOn(true);

	CGamePlayerSaveLoad::GetInst()->Save();

	CSceneManager::GetInst()->GetScene()->GetResource()->SoundStop("FrontScene");

	CScene* Scene = CSceneManager::GetInst()->GetScene();

	CSceneManager::GetInst()->CreateNextScene(true);

	CScene* NextScene = CSceneManager::GetInst()->GetNextScene();

	NextScene->Load("Henesis.scn", SCENE_PATH);

	//CEngineShareSetting::Setting();
		
}

void CQuestUI::ClearUI()
{
	m_QuestChatBoxImage->Destroy();

	m_QuestNpcImage->Destroy();

	if(m_QuestOkButton)
	m_QuestOkButton->Destroy();

	if(m_QuestCancelButton)
	m_QuestCancelButton->Destroy();

	if (m_QuestComplateButton)
		m_QuestComplateButton->Destroy();

	m_QuestIngListText->Destroy();	

	m_QuestExitButton->Destroy();

	if(m_QuestItemImage)
	m_QuestItemImage->Destroy();

	if (m_QuestItemImage1)
		m_QuestItemImage1->Destroy();

	if (m_QuestWeaponImage)
		m_QuestWeaponImage->Destroy();

	m_QuestItemImage = nullptr;
	m_QuestItemImage1 = nullptr;
	m_QuestChatBoxImage = nullptr;
	m_QuestNpcImage = nullptr;
	m_QuestOkButton = nullptr;
	m_QuestCancelButton = nullptr;
	m_QuestIngListText = nullptr;
	m_QuestExitButton = nullptr;
	m_QuestComplateButton = nullptr;
	m_QuestWeaponImage = nullptr;

	m_TextIndex = 0;
}


void CQuestUI::Save(FILE* File)
{
	CUIWindow::Save(File);
}

void CQuestUI::Load(FILE* File)
{
	CUIWindow::Load(File);

	m_FrontQuest = true;

	m_QuestAlarmImage = FindWidget<CUIImage>("QuestAlarmImage");
	m_QuestAlarmText = FindWidget<CUIText>("QuestAlarmText");
	m_QuestAlarmButton = FindWidget<CUIButton>("QuestAlarmButton");
	m_QuestTitleText = FindWidget<CUIText>("QuestTitleText");
	m_QuestComplateText = FindWidget<CUIText>("QuestComplateText");

}