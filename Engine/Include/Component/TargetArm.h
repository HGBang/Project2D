#pragma once

#include "SceneComponent.h"

class CTargetArm :
	public CSceneComponent
{
	friend class CGameObject;
	friend class CScene;

protected:
	CTargetArm();
	CTargetArm(const CTargetArm& component);
	virtual ~CTargetArm();

protected:
	Vector3		m_TargetOffset;
	float		m_TargetDistance;
	AXIS		m_TargetDistanceAxis;
	float		m_Speed;
	bool		m_Setting;
	Vector3		CameraPos;

	float		m_CameraMinX;
	float		m_CameraMaxX;
	float		m_CameraMinY;
	float		m_CameraMaxY;

public:
	void SetTargetDistanceAxis(AXIS Axis)
	{
		m_TargetDistanceAxis = Axis;
	}

	void SetTargetDistance(float Distance)
	{
		m_TargetDistance = Distance;
	}

	void SetTargetOffset(const Vector3& Offset)
	{
		m_TargetOffset = Offset;
	}

	void SetTargetOffset(float x, float y, float z)
	{
		m_TargetOffset = Vector3(x, y, z);
	}

	Vector3 GetTargetOffset()
	{
		return m_TargetOffset;
	}

	void SetCameraMinMax(float MinX, float MaxX, float MinY, float MaxY)
	{
		m_CameraMinX = MinX;
		m_CameraMaxX = MaxX;
		m_CameraMinY = MinY;
		m_CameraMaxY = MaxY;

		m_Setting = true;
	}

public:
	virtual void Destroy();
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render();
	virtual CTargetArm* Clone()    const;
	virtual void Save(FILE* File);
	virtual void Load(FILE* File);
};

