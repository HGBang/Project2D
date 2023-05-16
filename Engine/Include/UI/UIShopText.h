#pragma once
#include "UIWidget.h"
#include "../Resource/Font/Font.h"

enum class Text_align_H
{
    Left,
    Center,
    Right
};

enum class Text_align_V
{
    Top,
    Middle,
    Bottom
};

class CUIShopText :
    public CUIWidget
{
    friend class CUIWindow;
    friend class CScene;

public:
    CUIShopText();
    CUIShopText(const CUIShopText& Text);
    virtual ~CUIShopText();

protected:
    TCHAR* m_Text;
    int m_TextCount;
    int m_TextCapacity;

    bool m_TextTime;

protected:
    CSharedPtr<CFont> m_Font;
    IDWriteTextLayout* m_Layout;
    ID2D1SolidColorBrush* m_Brush;
    ID2D1RenderTarget* m_RenderTarget;
    float   m_FontSize;
    bool    m_Transparency;
    float   m_Opacity;
    Vector4 m_Color;

    // Shadow
    bool    m_ShadowEnable;
    ID2D1SolidColorBrush* m_ShadowBrush;
    bool    m_ShadowTransparency;
    float   m_ShadowOpacity;
    Vector4 m_ShadowColor;
    Vector2 m_ShadowOffset;

    Text_align_H m_AlignH;
    Text_align_V m_AlignV;

    bool m_Monster;

public:
    const TCHAR* GetText() const
    {
        return m_Text;
    }

    int GetTextCount() const
    {
        return m_TextCount;
    }

    void SetTextTime(bool Time)
    {
        m_TextTime = Time;       
    }

public:
    void SetText(const TCHAR* Text)
    {
        int Length = lstrlen(Text);

        if (Length + 1 > m_TextCapacity)
        {
            m_TextCapacity = Length + 1;

            SAFE_DELETE_ARRAY(m_Text);

            m_Text = new TCHAR[m_TextCapacity];

            memset(m_Text, 0, sizeof(TCHAR) * m_TextCapacity);
        }

        lstrcpy(m_Text, Text);
        m_TextCount = Length;

        CreateLayout();
    }

    void SetTextNumber(int Number)
    {
        std::string StrNum = std::to_string(Number);

        TCHAR* TCHARNum = StringToTCHAR(StrNum);

        SetText(TCHARNum);

        SAFE_DELETE(TCHARNum);
    }

    TCHAR* StringToTCHAR(const std::string& Name);


    void Append(const TCHAR* Text)
    {
        int Length = lstrlen(Text) + m_TextCount;

        if (Length + 1 > m_TextCapacity)
        {
            m_TextCapacity = Length + 1;

            SAFE_DELETE_ARRAY(m_Text);

            TCHAR* NewText = new TCHAR[m_TextCapacity];

            memset(NewText, 0, sizeof(TCHAR) * m_TextCapacity);

            lstrcpy(NewText, m_Text);

            SAFE_DELETE_ARRAY(m_Text);

            m_Text = NewText;
        }

        lstrcat(m_Text, Text);
        m_TextCount += lstrlen(Text);

        CreateLayout();
    }

    void Pop_back()
    {
        if (m_TextCount > 0)
        {
            --m_TextCount;
            m_Text[m_TextCount] = 0;

            CreateLayout();
        }
    }

    void Clear()
    {
        if (m_TextCount > 0)
        {
            m_TextCount = 0;

            memset(m_Text, 0, sizeof(TCHAR) * m_TextCapacity);

            CreateLayout();
        }
    }

public:
    virtual void SetSize(const Vector2& Size)
    {
        CUIWidget::SetSize(Size);

        CreateLayout();
    }

    virtual void SetSize(float x, float y)
    {
        CUIWidget::SetSize(x, y);

        CreateLayout();
    }

public:
    void SetFont(const std::string& Name);
    void SetFontSize(float Size);
    void SetAlignH(Text_align_H Align);
    void SetAlignV(Text_align_V Align);
    void SetColor(unsigned char r, unsigned char g, unsigned char b);
    void SetColor(const Vector4& Color);
    void SetColor(unsigned int Color);
    void SetTransparency(bool Transparency);
    void SetOpacity(float Opacity);

    void SetShadowEnable(bool Enable);
    void SetShadowOffset(const Vector2& Offset);
    void SetShadowOffset(float x, float y);
    void SetShadowColor(unsigned char r, unsigned char g, unsigned char b);
    void SetShadowColor(const Vector4& Color);
    void SetShadowColor(unsigned int Color);
    void SetShadowTransparency(bool Transparency);
    void SetShadowOpacity(float Opacity);

private:
    void CreateLayout();


public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render();
    virtual CUIShopText* Clone();
    virtual void Save(FILE* File);
    virtual void Load(FILE* File);
};

