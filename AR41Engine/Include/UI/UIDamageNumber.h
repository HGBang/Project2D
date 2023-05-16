#pragma once
#include "UIWidget.h"
class CUIDamageNumber :
    public CUIWidget
{
    friend class CUIWindow;
    friend class CScene;

protected:
    CUIDamageNumber();
    CUIDamageNumber(const CUIDamageNumber& Button);
    virtual ~CUIDamageNumber();

protected:
    UIWidgetImageInfo   m_TextureInfo;
    unsigned int                 m_Number;
    std::vector<unsigned int>    m_vecNumber;

    float m_DestroyTime;
    
    float m_StartOpacity;
    float m_OpcityTime;

    Vector2 m_WorldPos;


public:
    void SetNumber(int Number)
    {
        m_Number = Number;
    }

    void AddNumber(int Number)
    {
        m_Number += Number;
    }

    void SetUIPos(const Vector2& Pos);
   
    

public:
    void SetTexture(CTexture* Texture);
    bool SetTexture(const std::string& Name, const TCHAR* FileName,
        const std::string& PathName = TEXTURE_PATH);
    bool SetTextureFullPath(const std::string& Name, const TCHAR* FullPath);
    bool SetTexture(const std::string& Name, const std::vector<const TCHAR*>& vecFileName,
        const std::string& PathName = TEXTURE_PATH);
    bool SetTextureFullPath(const std::string& Name, const std::vector<const TCHAR*>& vecFullPath);
    void SetImageTint(const Vector4& Tint);
    void SetImageTint(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
    void AddFrameData(const Vector2& Start, const Vector2& End);
    void SetPlayTime(float PlayTime);
    void SetPlayScale(float PlayScale);


public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render();
    virtual CUIDamageNumber* Clone();
    virtual void Save(FILE* File);
    virtual void Load(FILE* File);
};

