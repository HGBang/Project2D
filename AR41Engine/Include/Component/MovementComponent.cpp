#include "MovementComponent.h"
#include "../GameObject/GameObject.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneManager.h"
#include "TileMapComponent.h"
#include "Tile.h"
#include "ColliderSphere2D.h"
#include "ColliderBox2D.h"
#include "../Engine.h"
#include "../Input.h"

CMovementComponent::CMovementComponent() :
	m_GravityAccel(10.f)
{
	m_ComponentType = ComponentType::Object;

	SetTypeID<CMovementComponent>();
	m_ComponentTypeName = "MovementComponent";
}

CMovementComponent::CMovementComponent(const CMovementComponent& Obj)
	:CObjectComponent(Obj)
{
	m_GravityAccel = Obj.m_GravityAccel;
}

CMovementComponent::~CMovementComponent()
{
}

void CMovementComponent::SetTileMap(const std::string& Name)
{
	CGameObject* Object = nullptr;

	if (m_Scene)
		Object = m_Scene->FindObject(Name);

	else
		Object = CSceneManager::GetInst()->GetScene()->FindObject(Name);

	m_TileMap = (CTileMapComponent*)Object->FindComponent("TileMapComponent");
		
}

void CMovementComponent::SetFallStartY(float StartY)
{
	m_FallStartY = StartY;
}

void CMovementComponent::Destroy()
{
	CObjectComponent::Destroy();
}

void CMovementComponent::Start()
{
	CObjectComponent::Start();

	m_Diving = false;
	m_Ground = false;

	//SetTileMap("GameObject");

	m_PrevPos = m_Owner->GetWorldPos();;

	m_TileMap = m_Scene->GetTileMap();

}

bool CMovementComponent::Init()
{
	
	if (!CComponent::Init())
		return false;

	//m_Pos = m_Owner->GetWorldPos();

	//m_PrevPos = m_Owner->GetWorldPos();	

	return true;
}

void CMovementComponent::FirstUpdate(float DeltaTime)
{
	CObjectComponent::FirstUpdate(DeltaTime);

	m_PrevPos = m_Owner->GetWorldPos();

	m_StartTime += DeltaTime;

	if (m_StartTime > 0.5f && !m_Start)
	{
		m_Start = true;
		m_FallStartY = m_PrevPos.y;	
	}

	if (m_Start)
	{
		if (m_Gravity && !m_Ground)
		{
			m_FallTime += DeltaTime * m_GravityAccel;

			float velocity = 0.f;

			if (m_Jump)
				velocity = m_JumpVelocity * m_FallTime;

			float GravityPower = m_FallStartY + (velocity - 0.5f * GRAVITY * m_FallTime * m_FallTime);

			m_Owner->SetWorldPositionY(GravityPower);

		}
	}
}

void CMovementComponent::Update(float DeltaTime)
{
	CObjectComponent::Update(DeltaTime);
}

void CMovementComponent::PostUpdate(float DeltaTime)
{
	CObjectComponent::PostUpdate(DeltaTime);

	m_Pos = m_Owner->GetWorldPos();

	m_Move = m_Pos - m_PrevPos;

	Vector2 MousePos = CInput::GetInst()->GetMouseWorldPos();

	if (0.1f < abs(m_Move.y))
		m_Diving = true;

	if (m_TileMap)
	{
		if (m_Move.x != 0.f)
		{
			if (m_Move.x > 0.f && !m_Jump)
				CheckMoveRight();

			if (m_Move.x < 0.f && !m_Jump)
				CheckMoveLeft();
		}

			if (m_Gravity && m_Move.y <= 0.f )
			{

				Vector3 Pos = m_Owner->GetRootComponent()->GetWorldPos();
				Vector3 Size = m_Owner->GetRootComponent()->GetWorldScale();
				CColliderBox2D* Collider = (CColliderBox2D*)m_Owner->GetRootComponent();

				Vector2 BoxSize = Collider->GetBoxSize();

				Vector2 Pivot = m_Owner->GetRootComponent()->GetPivot();

				CTile* Tile = m_TileMap->GetTile(Pos);

				Vector3 TilePos = Tile->GetPos();

				if (Tile)
				{
					float PrevBottom = m_PrevPos.y - (BoxSize.y * 0.5f);
					float CurBottom = Pos.y - (BoxSize.y * 0.5f);

					float PrevLeft = m_PrevPos.x - (BoxSize.x * 0.5f);
					float CurLeft = Pos.x - (BoxSize.x * 0.5f);

					float PrevRight = m_PrevPos.x + (BoxSize.x * 0.5f);
					float CurRight = Pos.x + (BoxSize.x * 0.5f);

					float ResultLeft = PrevLeft < CurLeft ? PrevLeft : CurLeft;
					float ResultRight = PrevRight > CurRight ? PrevRight : CurRight;
					float ResultTop = PrevBottom < CurBottom ? PrevBottom : CurBottom;
					float ResultBottom = PrevBottom > CurBottom ? PrevBottom : CurBottom;

					int LeftIndex = m_TileMap->GetTileIndexX(Vector2(ResultLeft, Pos.y));
					int RightIndex = m_TileMap->GetTileIndexX(Vector2(ResultRight, Pos.y));
					int TopIndex = m_TileMap->GetTileIndexY(Vector2(Pos.x, ResultTop));
					int BottomIndex = m_TileMap->GetTileIndexY(Vector2(Pos.x, ResultBottom));

					LeftIndex = LeftIndex < 0 ? 0 : LeftIndex;
					TopIndex = TopIndex < 0 ? 0 : TopIndex;
					RightIndex = RightIndex > m_TileMap->GetCountX() - 1 ? m_TileMap->GetCountX() - 1 : RightIndex;
					BottomIndex = BottomIndex > m_TileMap->GetCountY() - 1 ? m_TileMap->GetCountY() - 1 : BottomIndex;

					if (LeftIndex <= m_TileMap->GetCountX() - 1 && TopIndex <= m_TileMap->GetCountY() - 1 &&
						RightIndex >= 0 && BottomIndex >= 0)
					{

						bool Check = false;

						for (int i = TopIndex; i <= BottomIndex; ++i)
						{
							for (int j = LeftIndex; j <= RightIndex; ++j)
							{
								CTile* Tile = m_TileMap->GetTile(j, i);

								if (!Tile)
									continue;

								if (Tile->GetTileOption() == ETileOption::Wall)
								{
									Check = true;

									m_FallTime = 0.f;

									Vector3 TilePos = Tile->GetPos();

									float TileTop = TilePos.y + (m_TileMap->GetTileSize().y);

									m_Owner->SetWorldPositionY(TileTop + (BoxSize.y * 0.5f + 0.005f));

									m_Ground = true;

									m_Jump = false;

									m_Diving = false;

									break;
								}
							}

							if (Check)
								break;
						}

						if (!Check)
						{

							if (m_Ground)
							{
								m_FallTime = 0.f;
								m_FallStartY = m_Owner->GetWorldPos().y;
							}

							m_Ground = false;

						}

					}

				}

			}
	}
	
}

void CMovementComponent::Render()
{
	CObjectComponent::Render();
}

CMovementComponent* CMovementComponent::Clone() const
{
	return new CMovementComponent(*this);
}

void CMovementComponent::Save(FILE* File)
{
	CObjectComponent::Save(File);
}

void CMovementComponent::Load(FILE* File)
{
	CObjectComponent::Load(File);
}

void CMovementComponent::SetGravity(bool Gravity)
{
	m_Gravity = Gravity;
}

void CMovementComponent::SetJumpVelocity(float Velocity)
{
	m_JumpVelocity = Velocity;
}

void CMovementComponent::SetGround(bool Ground)
{
	m_Ground = Ground;
}

void CMovementComponent::SetFallTime(float FallTime)
{
	m_FallTime = FallTime;
}

void CMovementComponent::AddMyVelocity(const Vector3& InVelocity)
{
	m_MyVelocity += InVelocity;
}

void CMovementComponent::MoveLeft(float Power)
{
	m_Owner->GetRootComponent()->AddWorldPosition(m_Owner->GetRootComponent()->GetWorldAxis(AXIS_X) * -Power * g_DeltaTime);
}

void CMovementComponent::MoveRight(float Power)
{
	m_Owner->GetRootComponent()->AddWorldPosition(m_Owner->GetRootComponent()->GetWorldAxis(AXIS_X) * Power * g_DeltaTime);
}

void CMovementComponent::MoveUp(float Power)
{
	m_Owner->GetRootComponent()->AddWorldPosition(m_Owner->GetRootComponent()->GetWorldAxis(AXIS_Y) * Power * g_DeltaTime);
}

void CMovementComponent::MoveDown(float Power)
{
	m_Owner->GetRootComponent()->AddWorldPosition(m_Owner->GetRootComponent()->GetWorldAxis(AXIS_Y) * Power * g_DeltaTime);
}

void CMovementComponent::CheckMoveRight()
{
	Vector3 Pos = m_Owner->GetWorldPos();

	CColliderBox2D* Collider = (CColliderBox2D*)m_Owner->GetRootComponent();

	Vector2 BoxSize = Collider->GetBoxSize();

	Vector2 LT = Vector2(Pos.x - (BoxSize.x * 0.5f), Pos.y + (BoxSize.y * 0.5f));
	Vector2 RB = Vector2(Pos.x + (BoxSize.x * 0.5f), Pos.y - (BoxSize.y * 0.5f));

	Vector2 PrevLT = Vector2(m_PrevPos.x - (BoxSize.x * 0.5f), m_PrevPos.y + (BoxSize.y * 0.5f));
	Vector2 PrevRB = Vector2(m_PrevPos.x + (BoxSize.x * 0.5f), m_PrevPos.y - (BoxSize.y * 0.5f));

	Vector2 ResultLT, ResultRB;

	ResultRB = RB;

	ResultLT.x = PrevRB.x;
	ResultLT.y = LT.y < PrevLT.y ? LT.y : PrevLT.y;

	ResultRB.y = RB.y > PrevRB.y ? RB.y : PrevRB.y;
	

	int LeftIndex = m_TileMap->GetTileIndexX(Vector2(ResultLT.x, Pos.y));
	int TopIndex = m_TileMap->GetTileIndexY(Vector2(Pos.x, ResultLT.y));
	int RightIndex = m_TileMap->GetTileIndexX(Vector2(ResultRB.x, Pos.y));
	int BottomIndex = m_TileMap->GetTileIndexY(Vector2(Pos.x, ResultRB.y));

	LeftIndex = LeftIndex < 0 ? 0 : LeftIndex;
	TopIndex = TopIndex < 0 ? 0 : TopIndex;
	RightIndex = RightIndex > m_TileMap->GetCountX() - 1 ? m_TileMap->GetCountX() - 1 : RightIndex;
	BottomIndex = BottomIndex > m_TileMap->GetCountY() - 1 ? m_TileMap->GetCountY() - 1 : BottomIndex;

	if (LeftIndex <= m_TileMap->GetCountX() - 1 && TopIndex <= m_TileMap->GetCountY() - 1 &&
		RightIndex >= 0 && BottomIndex >= 0)
	{
		bool SideCollisionCheck = false;

		for (int i = BottomIndex; i <= TopIndex; ++i)
		{
			for (int j = LeftIndex; j <= RightIndex; ++j)
			{
				CTile* Tile = m_TileMap->GetTile(j, i);

				if (Tile->GetTileOption() != ETileOption::Wall)
					continue;

				Vector2 TilePos = Tile->GetPos();
				Vector2 TileSize = m_TileMap->GetTileSize();

				if (TilePos.y - 0.001f <= RB.y && RB.y <= TilePos.y + 0.001f)
					continue;

				if (LT.x <= TilePos.x + (TileSize.x * 2.f) && LT.y <= TilePos.y + (TileSize.y * 2.f) && 
					RB.x >= TilePos.x && RB.y >= TilePos.y - (TileSize.y * 2.f) )
				{
					SideCollisionCheck = true;

					float MoveX = TilePos.x - RB.x - 0.001f;
				
					m_Owner->SetWorldPositionX(m_Owner->GetWorldPos().x + MoveX);
					m_Move.x += MoveX;										

					break;
				}
			}

			if (SideCollisionCheck)
				break;
		}

	}

}

void CMovementComponent::CheckMoveLeft()
{
	Vector3 Pos = m_Owner->GetWorldPos();

	CColliderBox2D* Collider = (CColliderBox2D*)m_Owner->GetRootComponent();

	Vector2 BoxSize = Collider->GetBoxSize();

	Vector2 LT = Vector2(Pos.x - (BoxSize.x * 0.5f), Pos.y + (BoxSize.y * 0.5f));
	Vector2 RB = Vector2(Pos.x + (BoxSize.x * 0.5f), Pos.y - (BoxSize.y * 0.5f));

	Vector2 PrevLT = Vector2(m_PrevPos.x - (BoxSize.x * 0.5f), m_PrevPos.y + (BoxSize.y * 0.5f));
	Vector2 PrevRB = Vector2(m_PrevPos.x + (BoxSize.x * 0.5f), m_PrevPos.y - (BoxSize.y * 0.5f));

	Vector2 ResultLT, ResultRB;

	ResultLT = LT;

	ResultLT.y = LT.y < PrevLT.y ? LT.y : PrevLT.y;

	ResultRB.x = PrevLT.x;
	ResultRB.y = RB.y > PrevRB.y ? RB.y : PrevRB.y;

	int LeftIndex = m_TileMap->GetTileIndexX(Vector2(ResultLT.x, Pos.y));
	int TopIndex = m_TileMap->GetTileIndexY(Vector2(Pos.x, ResultLT.y));
	int RightIndex = m_TileMap->GetTileIndexX(Vector2(ResultRB.x, Pos.y));
	int BottomIndex = m_TileMap->GetTileIndexY(Vector2(Pos.x, ResultRB.y));

	LeftIndex = LeftIndex < 0 ? 0 : LeftIndex;
	TopIndex = TopIndex < 0 ? 0 : TopIndex;
	RightIndex = RightIndex > m_TileMap->GetCountX() - 1 ? m_TileMap->GetCountX() - 1 : RightIndex;
	BottomIndex = BottomIndex > m_TileMap->GetCountY() - 1 ? m_TileMap->GetCountY() - 1 : BottomIndex;


	if (LeftIndex <= m_TileMap->GetCountX() - 1 && TopIndex <= m_TileMap->GetCountY() - 1 &&
		RightIndex >= 0 && BottomIndex >= 0)
	{
		bool SideCollisionCheck = false;

		for (int i = BottomIndex; i <= TopIndex; ++i)
		{
			for (int j = RightIndex; j >= LeftIndex; --j)
			{
				CTile* Tile = m_TileMap->GetTile(j, i);

				if (Tile->GetTileOption() != ETileOption::Wall)
					continue;

				Vector2 TilePos = Tile->GetPos();
				Vector2 TileSize = m_TileMap->GetTileSize();

				if (TilePos.y - 0.001f <= RB.y && RB.y <= TilePos.y + 0.001f)
					continue;

				if (LT.x <= TilePos.x + (TileSize.x * 2.f) && LT.y <= TilePos.y + (TileSize.y * 2.f) &&
					RB.x >= TilePos.x && RB.y >= TilePos.y - (TileSize.y * 2.f))
				{
					SideCollisionCheck = true;

					float MoveX = TilePos.x + TileSize.x  - LT.x + 0.001f;

					m_Owner->SetWorldPositionX(m_Owner->GetWorldPos().x + MoveX);
					m_Move.x += MoveX;
					break;
				}
			}

			if (SideCollisionCheck)
				break;
		}

	}

}
