#pragma once
#include "ObjectComponent.h"
class CMovementComponent :
    public CObjectComponent
{
    friend class CGameObject;
    friend class CScene;

protected: 
    Vector3 m_PrevPos;
    Vector3 m_Move;
    Vector3 m_Pos;

protected:
    class CTileMapComponent* m_TileMap;
    bool        m_Gravity;
    float       m_FallTime;
    float       m_JumpVelocity;     
    float       m_FallStartY;
    float       m_GravityAccel;
    float       m_Velocity;

    Vector3     m_MyVelocity;


    bool        m_Jump;
    bool        m_Ground;
    bool        m_Diving;

    float       m_StartTime;
    bool        m_Start;



        
protected:
    CMovementComponent();
    CMovementComponent(const CMovementComponent& Obj);
    virtual ~CMovementComponent();   

public:
    void SetJump(bool Jump)
    {
        m_Jump = Jump;
    }

public:
    void SetTileMap(const std::string& Name);
    void SetFallStartY(float StartY);

public:
    virtual void Destroy();
    virtual void Start();
    virtual bool Init();
    virtual void FirstUpdate(float DeltaTime);
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render();
    virtual CMovementComponent* Clone()    const;
    virtual void Save(FILE* File);
    virtual void Load(FILE* File);

public:
    bool GetGround() 
    {
        return m_Ground;
    }

    bool GetDiving()
    {
        return m_Diving;
    }

    bool GetJump()
    {
        return m_Jump;
    }

    Vector3 GetMove() const
    {
        return m_Move;
    }


public:
    void SetGravity(bool Gravity);
    void SetJumpVelocity(float Velocity);
    void SetGround(bool Ground);
    void SetFallTime(float FallTime);
    

public:
    void AddMyVelocity(const Vector3& InVelocity);
    void MoveLeft(float Power);
    void MoveRight(float Power);
    void MoveUp(float Power);
    void MoveDown(float Power);
    

private:
    void CheckMoveRight();
    void CheckMoveLeft();
    
           
public:
    float GetVelocity() const
    {
        return m_Velocity;
    }

};

