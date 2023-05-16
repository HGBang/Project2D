
#include "TargetArm.h"
#include "../Device.h"

CTargetArm::CTargetArm() :
	m_TargetDistance(0.f)
{
	SetTypeID<CTargetArm>();

	m_ComponentTypeName = "TargetArm";
}

CTargetArm::CTargetArm(const CTargetArm& component) :
	CSceneComponent(component)
{
	m_TargetDistance = component.m_TargetDistance;
	m_TargetOffset = component.m_TargetOffset;
	m_TargetDistanceAxis = component.m_TargetDistanceAxis;
}

CTargetArm::~CTargetArm()
{
}

void CTargetArm::Destroy()
{
	CSceneComponent::Destroy();
}

void CTargetArm::Start()
{
	CSceneComponent::Start();
}

bool CTargetArm::Init()
{
	CSceneComponent::Init();

	m_Speed = -1000.f;

	return true;
}

void CTargetArm::Update(float DeltaTime)
{
	CSceneComponent::Update(DeltaTime);

	Resolution RS = CDevice::GetInst()->GetResolution();

	float Width = (float)RS.Width / 2.f;
	float Height = (float)RS.Height / 2.7f;

	Vector2 rsHalf = Vector2(Width, Height);		
	Vector3 targetArmPos = GetWorldPos();

		if (m_Parent)
		{			
			Vector3	ParentPos = m_Parent->GetWorldPos();	
			
			m_TargetOffset;
					
			float Xend = targetArmPos.x + (float)RS.Width;

			float XStart = targetArmPos.x;

			if (m_CameraMaxX < Xend)
			{
				float XValue =  Xend - m_CameraMaxX;
				m_TargetOffset.x -= XValue;
			}
			else if (m_CameraMaxX >= Xend && abs(m_TargetOffset.x) > 640 )
			{
				 float XValue = m_CameraMaxX - Xend ;

				m_TargetOffset.x += XValue;
			}		

			if (m_CameraMinX > XStart)
			{
				float XValue = m_CameraMinX - XStart;

				m_TargetOffset.x += XValue;
			}
			else if (m_CameraMinX <= XStart && ::abs(m_TargetOffset.x) < 630)
			{
				float XValue = XStart - m_CameraMinX;
				//m_TargetOffset.x -= XValue;				
				m_TargetOffset.x = max(-630, m_TargetOffset.x - XValue);		
				
			}
					
			float Yend = targetArmPos.y  + (float)RS.Height;

			if (m_CameraMaxY <= Yend)
			{
				float YValue = Yend - m_CameraMaxY;

				m_TargetOffset.y -= YValue;
			}

			else if (m_CameraMaxY >= Yend && abs(m_TargetOffset.y) > 600)
			{
				float YValue = m_CameraMaxY - Yend;

				m_TargetOffset.y += YValue;
			}

			float YStart = targetArmPos.y;

			if (m_CameraMinY > YStart)
			{
				float YValue = m_CameraMinY + YStart;

				m_TargetOffset.y -= YValue;
			}

			else if (m_CameraMinY < YStart && abs(m_TargetOffset.y) < 100)
			{
				float YValue = m_CameraMinY - YStart;

				m_TargetOffset.y += YValue;
			}

			Vector3 Pos = ParentPos - GetWorldAxis(m_TargetDistanceAxis) * m_TargetDistance;			

			SetWorldPosition(Pos + m_TargetOffset);			
		}

	
}

void CTargetArm::PostUpdate(float DeltaTime)
{
	CSceneComponent::PostUpdate(DeltaTime);

	//Camera 의 LocalPosiition 을 000으로고정
	size_t childSize = m_vecChild.size();

	for(size_t i = 0 ;i< childSize;i++)
	{
		m_vecChild[i]->SetRelativePosition(Vector3(0.0f, 0.0f,-2.0f));
	}
	
}

void CTargetArm::Render()
{
	CSceneComponent::Render();
}

CTargetArm* CTargetArm::Clone() const
{
	return new CTargetArm(*this);
}

void CTargetArm::Save(FILE* File)
{
	CSceneComponent::Save(File);

	fwrite(&m_TargetOffset, sizeof(Vector3), 1, File);
	fwrite(&m_TargetDistance, sizeof(float), 1, File);
	fwrite(&m_TargetDistanceAxis, sizeof(AXIS), 1, File);
}

void CTargetArm::Load(FILE* File)
{
	CSceneComponent::Load(File);

	fread(&m_TargetOffset, sizeof(Vector3), 1, File);
	fread(&m_TargetDistance, sizeof(float), 1, File);
	fread(&m_TargetDistanceAxis, sizeof(AXIS), 1, File);

	CameraPos = Vector3(0.f, 0.f, 0.f);
}
