#pragma once
#include "PrimitiveComponent.h"
#include "../Animation/Animation2D.h"
class CSpriteComponent :
    public CPrimitiveComponent
{
    friend class CGameObject;
    friend class CScene;

protected:
    CSpriteComponent();
    CSpriteComponent(const CSpriteComponent& component);
    virtual ~CSpriteComponent();

protected:
    CSharedPtr<CAnimation2D> m_Animation;
    bool    m_TextureSize;

public:
    std::string GetAnimationName() const
    {
        if (!m_Animation)
            return "None";

        return m_Animation->GetAnimationClassName();
    }

    void GetAnimationNames(std::vector<std::string>& vecNames)
    {
        if (!m_Animation)
            return;

        m_Animation->GetAnimationNames(vecNames);
    }

    CAnimation2D* GetAnimation()    const
    {
        return m_Animation;
    }

    bool GetTextureSize() const
    {
        return m_TextureSize;
    }

public:
    bool SetTexture(class CTexture* Texture);
    bool SetTexture(const std::string& Name, const TCHAR* FileName,
        const std::string& PathName = TEXTURE_PATH);
    bool SetTextureFullPath(const std::string& Name, const TCHAR* FullPath);
    bool SetTexture(const std::string& Name, const std::vector<const TCHAR*>& vecFileName,
        const std::string& PathName = TEXTURE_PATH);
    bool SetTextureFullPath(const std::string& Name, const std::vector<const TCHAR*>& vecFullPath);
    void SetTextureFrameIndex(int Index);
    class CTexture* GetTexture(int Index = 0) const;

public:
    bool SetChangeWidthHeight(bool Change);


public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render();
    virtual CSpriteComponent* Clone()    const;
    virtual void Save(FILE* File);
    virtual void Load(FILE* File);

public:
    template <typename T>
    T* SetAnimation(const std::string& Name)
    {
        T* Anim = new T;

        Anim->SetName(Name);
        Anim->m_Owner = this;

        if (!Anim->Init())
        {
            SAFE_DELETE_ARRAY(Anim);
            return nullptr;
        }

        m_Animation = Anim;

        return Anim;

    }

public:
    bool GetReverseX() const
    {
        return m_ReverseX;
    }

    void SetReverseX(bool Reverse)
    {
        m_ReverseX = Reverse;
    }

    void Set2DZOffset(float In2DZOffset);

private:
    bool        m_ReverseX;



};

