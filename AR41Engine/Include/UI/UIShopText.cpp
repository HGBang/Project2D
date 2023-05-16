#include "UIShopText.h"
#include "../Resource/ResourceManager.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Input.h"
#include "../Device.h"
#include "../Engine.h"

CUIShopText::CUIShopText() :
    m_Layout(nullptr),
    m_Brush(nullptr),
    m_RenderTarget(nullptr),
    m_FontSize(10.f),
    m_Transparency(false),
    m_Opacity(1.f),
    m_Color(Vector4::White),
    m_ShadowEnable(false),
    m_ShadowBrush(nullptr),
    m_ShadowTransparency(false),
    m_ShadowOpacity(1.f),
    m_AlignH(Text_align_H::Left),
    m_AlignV(Text_align_V::Top),
    m_ShadowOffset(1.f, 1.f)
{
    m_Color.w = m_Opacity;
    m_ShadowColor = m_ShadowOpacity;

    m_TextCapacity = 512;
    m_TextCount = 0;
    m_Text = new TCHAR[m_TextCapacity];

    m_WidgetTypeName = "UIShopText";
}

CUIShopText::CUIShopText(const CUIShopText& Text) :
    CUIWidget(Text)
{
    m_Font = Text.m_Font;
    m_Layout = nullptr;
    m_Brush = Text.m_Brush;
    m_RenderTarget = Text.m_RenderTarget;
    m_FontSize = Text.m_FontSize;
    m_Transparency = Text.m_Transparency;
    m_Opacity = Text.m_Opacity;
    m_Color = Text.m_Color;

    m_ShadowEnable = Text.m_ShadowEnable;
    m_ShadowBrush = Text.m_ShadowBrush;
    m_ShadowTransparency = Text.m_ShadowTransparency;
    m_ShadowOpacity = Text.m_ShadowOpacity;
    m_ShadowColor = Text.m_ShadowColor;
    m_ShadowOffset = Text.m_ShadowOffset;
    m_AlignH = Text.m_AlignH;
    m_AlignV = Text.m_AlignV;

    m_TextCapacity = Text.m_TextCapacity;
    m_TextCount = Text.m_TextCount;

    m_Text = new TCHAR[m_TextCapacity];

    lstrcpy(m_Text, Text.m_Text);

    CreateLayout();
}

CUIShopText::~CUIShopText()
{
    SAFE_RELEASE(m_Layout);
    SAFE_DELETE_ARRAY(m_Text);
}

TCHAR* CUIShopText::StringToTCHAR(const std::string& Name)
{
    size_t origsize = 0, convertedChars = 0;
    origsize = strlen(Name.c_str()) + 1;
    wchar_t* t = new wchar_t[origsize];
    mbstowcs_s(&convertedChars, t, origsize, Name.c_str(), _TRUNCATE);

    return (TCHAR*)t;
}

void CUIShopText::SetFont(const std::string& Name)
{
    if (m_Scene)
    {
        m_Font = m_Scene->GetResource()->FindFont(Name);
    }

    else
    {
        m_Font = CResourceManager::GetInst()->FindFont(Name);
    }

    CreateLayout();
}

void CUIShopText::SetFontSize(float Size)
{
    m_FontSize = Size;

    CreateLayout();
}

void CUIShopText::SetAlignH(Text_align_H Align)
{
    m_AlignH = Align;

    CreateLayout();
}

void CUIShopText::SetAlignV(Text_align_V Align)
{
    m_AlignV = Align;

    CreateLayout();
}

void CUIShopText::SetColor(unsigned char r, unsigned char g, unsigned char b)
{
    m_Color.x = r / 255.f;
    m_Color.y = g / 255.f;
    m_Color.z = b / 255.f;

    if (m_Scene)
    {
        m_Scene->GetResource()->CreateFontColor(m_Color);
        m_Brush = m_Scene->GetResource()->FindFontColor(m_Color);
    }

    else
    {
        CResourceManager::GetInst()->CreateFontColor(m_Color);
        m_Brush = CResourceManager::GetInst()->FindFontColor(m_Color);
    }
}

void CUIShopText::SetColor(const Vector4& Color)
{
    m_Color.x = Color.x;
    m_Color.y = Color.y;
    m_Color.z = Color.z;

    if (m_Scene)
    {
        m_Scene->GetResource()->CreateFontColor(m_Color);
        m_Brush = m_Scene->GetResource()->FindFontColor(m_Color);
    }

    else
    {
        CResourceManager::GetInst()->CreateFontColor(m_Color);
        m_Brush = CResourceManager::GetInst()->FindFontColor(m_Color);
    }
}

void CUIShopText::SetColor(unsigned int Color)
{
    m_Color.x = ((Color >> 16) & 0x000000ff) / 255.f;
    m_Color.y = ((Color >> 8) & 0x000000ff) / 255.f;
    m_Color.z = (Color & 0x000000ff) / 255.f;

    if (m_Scene)
    {
        m_Scene->GetResource()->CreateFontColor(m_Color);
        m_Brush = m_Scene->GetResource()->FindFontColor(m_Color);
    }

    else
    {
        CResourceManager::GetInst()->CreateFontColor(m_Color);
        m_Brush = CResourceManager::GetInst()->FindFontColor(m_Color);
    }
}

void CUIShopText::SetTransparency(bool Transparency)
{
    m_Transparency = Transparency;
}

void CUIShopText::SetOpacity(float Opacity)
{
    m_Opacity = Opacity;
}

void CUIShopText::SetShadowEnable(bool Enable)
{
    m_ShadowEnable = Enable;
}

void CUIShopText::SetShadowOffset(const Vector2& Offset)
{
    m_ShadowOffset = Offset;
}

void CUIShopText::SetShadowOffset(float x, float y)
{
    m_ShadowOffset = Vector2(x, y);
}

void CUIShopText::SetShadowColor(unsigned char r, unsigned char g, unsigned char b)
{
    m_ShadowColor.x = r / 255.f;
    m_ShadowColor.y = g / 255.f;
    m_ShadowColor.z = b / 255.f;

    if (m_Scene)
    {
        m_Scene->GetResource()->CreateFontColor(m_ShadowColor);
        m_ShadowBrush = m_Scene->GetResource()->FindFontColor(m_ShadowColor);
    }

    else
    {
        CResourceManager::GetInst()->CreateFontColor(m_ShadowColor);
        m_ShadowBrush = CResourceManager::GetInst()->FindFontColor(m_ShadowColor);
    }
}

void CUIShopText::SetShadowColor(const Vector4& Color)
{
    m_ShadowColor.x = Color.x;
    m_ShadowColor.y = Color.y;
    m_ShadowColor.z = Color.z;

    if (m_Scene)
    {
        m_Scene->GetResource()->CreateFontColor(m_ShadowColor);
        m_ShadowBrush = m_Scene->GetResource()->FindFontColor(m_ShadowColor);
    }

    else
    {
        CResourceManager::GetInst()->CreateFontColor(m_ShadowColor);
        m_ShadowBrush = CResourceManager::GetInst()->FindFontColor(m_ShadowColor);
    }
}

void CUIShopText::SetShadowColor(unsigned int Color)
{
    m_ShadowColor.x = ((Color >> 16) & 0x000000ff) / 255.f;
    m_ShadowColor.y = ((Color >> 8) & 0x000000ff) / 255.f;
    m_ShadowColor.z = (Color & 0x000000ff) / 255.f;

    if (m_Scene)
    {
        m_Scene->GetResource()->CreateFontColor(m_ShadowColor);
        m_ShadowBrush = m_Scene->GetResource()->FindFontColor(m_ShadowColor);
    }

    else
    {
        CResourceManager::GetInst()->CreateFontColor(m_ShadowColor);
        m_ShadowBrush = CResourceManager::GetInst()->FindFontColor(m_ShadowColor);
    }
}

void CUIShopText::SetShadowTransparency(bool Transparency)
{
    m_ShadowTransparency = Transparency;
}

void CUIShopText::SetShadowOpacity(float Opacity)
{
    m_ShadowOpacity = Opacity;
}

void CUIShopText::CreateLayout()
{
    SAFE_RELEASE(m_Layout);

    m_Layout = m_Font->CreateLayout(m_Text, m_Size.x, m_Size.y);

    DWRITE_TEXT_RANGE   Range = {};

    Range.startPosition = 0;
    Range.length = lstrlen(m_Text);

    m_Layout->SetFontSize(m_FontSize, Range);

    switch (m_AlignH)
    {
    case Text_align_H::Left:
        m_Layout->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
        break;
    case Text_align_H::Center:
        m_Layout->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
        break;
    case Text_align_H::Right:
        m_Layout->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_TRAILING);
        break;
    }

    switch (m_AlignV)
    {
    case Text_align_V::Top:
        m_Layout->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
        break;
    case Text_align_V::Middle:
        m_Layout->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
        break;
    case Text_align_V::Bottom:
        m_Layout->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_FAR);
        break;
    }
}

void CUIShopText::Start()
{
    CUIWidget::Start();
}

bool CUIShopText::Init()
{
    if (!CUIWidget::Init())
        return false;

    m_RenderTarget = CDevice::GetInst()->Get2DTarget();

    // SetFont("Default");

    SetFont("MapleDefault");

    SetColor(m_Color);
    SetShadowColor(m_ShadowColor);

    CreateLayout();

    return true;
}

void CUIShopText::Update(float DeltaTime)
{
    CUIWidget::Update(DeltaTime);


    if (m_TextTime)
    {        

        CEngine::GetInst()->SetUITextMode(true);

        std::string Text = CEngine::GetInst()->GetUIText();

        TCHAR* RealText = StringToTCHAR(Text);

        SetText(RealText);

        SAFE_DELETE(RealText);
    }

    if (!m_TextTime)
    {
        CEngine::GetInst()->SetUITextMode(false);
    }


}

void CUIShopText::PostUpdate(float DeltaTime)
{
    CUIWidget::PostUpdate(DeltaTime);
}

void CUIShopText::Render()
{
    m_RenderTarget->BeginDraw();

    Resolution RS = CDevice::GetInst()->GetResolution();

    D2D1_POINT_2F   Point;
    Point.x = m_RenderPos.x;
    Point.y = RS.Height - m_RenderPos.y - m_Size.y;

    if (m_ShadowEnable)
    {
        D2D1_POINT_2F   ShadowPoint = Point;

        ShadowPoint.x += m_ShadowOffset.x;
        ShadowPoint.y += m_ShadowOffset.y;

        if (m_ShadowTransparency)
            m_ShadowBrush->SetOpacity(m_ShadowOpacity);

        else
            m_ShadowBrush->SetOpacity(1.f);

        m_RenderTarget->DrawTextLayout(ShadowPoint, m_Layout, m_ShadowBrush,
            D2D1_DRAW_TEXT_OPTIONS_NONE);
    }

    if (m_Transparency)
        m_Brush->SetOpacity(m_Opacity);

    else
        m_Brush->SetOpacity(1.f);

    m_RenderTarget->DrawTextLayout(Point, m_Layout, m_Brush, D2D1_DRAW_TEXT_OPTIONS_NONE);


    m_RenderTarget->EndDraw();
}

CUIShopText* CUIShopText::Clone()
{
    return new CUIShopText(*this);
}

void CUIShopText::Save(FILE* File)
{
    CUIWidget::Save(File);

    fwrite(&m_TextCapacity, sizeof(int), 1, File);
    fwrite(&m_TextCount, sizeof(int), 1, File);
    fwrite(m_Text, sizeof(TCHAR), m_TextCount, File);

    int Length = (int)m_Font->GetName().length();

    fwrite(&Length, sizeof(int), 1, File);
    fwrite(m_Font->GetName().c_str(), 1, Length, File);

    fwrite(&m_FontSize, sizeof(float), 1, File);
    fwrite(&m_Transparency, sizeof(bool), 1, File);
    fwrite(&m_Opacity, sizeof(float), 1, File);
    fwrite(&m_Color, sizeof(Vector4), 1, File);

    fwrite(&m_ShadowEnable, sizeof(bool), 1, File);
    fwrite(&m_ShadowTransparency, sizeof(bool), 1, File);
    fwrite(&m_ShadowOpacity, sizeof(float), 1, File);
    fwrite(&m_ShadowColor, sizeof(Vector4), 1, File);
    fwrite(&m_ShadowOffset, sizeof(Vector2), 1, File);

    fwrite(&m_AlignH, sizeof(Text_align_H), 1, File);
    fwrite(&m_AlignV, sizeof(Text_align_V), 1, File);
}

void CUIShopText::Load(FILE* File)
{
    CUIWidget::Load(File);

    SAFE_DELETE_ARRAY(m_Text);

    fread(&m_TextCapacity, sizeof(int), 1, File);
    fread(&m_TextCount, sizeof(int), 1, File);

    m_Text = new TCHAR[m_TextCapacity];

    memset(m_Text, 0, sizeof(TCHAR) * m_TextCapacity);

    fread(m_Text, sizeof(TCHAR), m_TextCount, File);

    int Length = 0;
    char    FontName[256] = {};

    fread(&Length, sizeof(int), 1, File);
    fread(FontName, 1, Length, File);

    SetFont(FontName);

    fread(&m_FontSize, sizeof(float), 1, File);
    fread(&m_Transparency, sizeof(bool), 1, File);
    fread(&m_Opacity, sizeof(float), 1, File);
    fread(&m_Color, sizeof(Vector4), 1, File);

    fread(&m_ShadowEnable, sizeof(bool), 1, File);
    fread(&m_ShadowTransparency, sizeof(bool), 1, File);
    fread(&m_ShadowOpacity, sizeof(float), 1, File);
    fread(&m_ShadowColor, sizeof(Vector4), 1, File);
    fread(&m_ShadowOffset, sizeof(Vector2), 1, File);

    fread(&m_AlignH, sizeof(Text_align_H), 1, File);
    fread(&m_AlignV, sizeof(Text_align_V), 1, File);

    SetColor(m_Color);
    SetShadowColor(m_ShadowColor);

    m_RenderTarget = CDevice::GetInst()->Get2DTarget();

    CreateLayout();
}
