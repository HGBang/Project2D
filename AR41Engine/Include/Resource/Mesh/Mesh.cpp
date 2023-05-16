
#include "Mesh.h"
#include "../../Device.h"
#include "../Material/Material.h"
#include "../ResourceManager.h"
#include "../../Scene/Scene.h"
#include "../../Scene/SceneResource.h"

CMesh::CMesh() :
	m_Min(FLT_MAX, FLT_MAX, FLT_MAX),
	m_Max(FLT_MIN, FLT_MIN, FLT_MIN)
{
}

CMesh::~CMesh()
{
	//소멸자 각각 메쉬컨테이이너와 슬롯사이즈만큼 반복하면서 삭제한다 . 

	size_t	Size = m_vecContainer.size();

	for (size_t i = 0; i < Size; ++i)
	{
		SAFE_DELETE(m_vecContainer[i]);
	}

	Size = m_vecMeshSlot.size();

	for (size_t i = 0; i < Size; ++i)
	{
		SAFE_DELETE(m_vecMeshSlot[i]);
	}
}

void CMesh::SetMaterial(int Container, int Subset, const std::string& Name)
{
	//메테리얼 지정 (인자는 컨테이너인덱스 , 서브셋 인덱스 ,  이름 )

	CMaterial* Material = nullptr;  //처음에 메테리얼 포인터변수 선언후 nullptr로 준다 . 
	

	if (m_Scene)
	{
		Material = m_Scene->GetResource()->FindMaterial(Name);
	}
	// 씬이 있다면 , 변수안에 씬에서 이름으로 메테리얼정보를 찾아서 넣어준다 . 

	else
	{
		Material = CResourceManager::GetInst()->FindMaterial(Name);
	}

	//씬이 없다면 , 리소스 매니저에서 메테리얼을 찾아서 넣어 준다 . 

	m_vecContainer[Container]->vecSubset[Subset].Material = Material;
	m_vecContainer[Container]->vecSubset[Subset].Slot->Material = Material;

	//그리고 해당 컨테이너 인덱스안에 서브셋, 슬롯에 각각 메테리얼 지정.
}

void CMesh::SetMaterial(int Container, int Subset, CMaterial* Material)
{
	m_vecContainer[Container]->vecSubset[Subset].Material = Material;
	m_vecContainer[Container]->vecSubset[Subset].Slot->Material = Material;
}

bool CMesh::CreateMesh(void* VtxData, int Size, int Count,
	D3D11_USAGE VtxUsage, D3D11_PRIMITIVE_TOPOLOGY Primitive,
	void* IdxData, int IdxSize, int IdxCount, D3D11_USAGE IdxUsage,
	DXGI_FORMAT Fmt)
{
	//메쉬를 만든다 .
	/* 메쉬컨테이너 구조체 선언 후, 
	* 컨테이너 안의 멤버에 각각 인자로 들어오는 정보로 메쉬를 만들어 준다 . 
	* 버텍스버퍼 사이즈 , 버텍스버퍼 갯수 , 버텍스버퍼의 도형, 버텍스버퍼의 데이터 
	* 먼저 컨테이너 안의 데이터메모리를 초기화 해주고 , 해당 데이터에 인자로들어오는 데이터와 크기를 넣어 준다 . 
	* 만약 버퍼생성이 실패했다면 false값 반환 성공했다면 , 멤버변수 컨테이너에 추가 해준다 .
	* 
	*/

	MeshContainer* Container = new MeshContainer;

	Container->VB.Size = Size;
	Container->VB.Count = Count;
	Container->Primitive = Primitive;
	Container->VB.Data = new char[Size * Count];
	memcpy(Container->VB.Data, VtxData, Size * Count);

	if (!CreateBuffer(BufferType::Vertex, VtxData, Size, Count,
		VtxUsage, &Container->VB.Buffer))
		return false;

	m_vecContainer.push_back(Container);

	/*
	* 메쉬슬롯도 채워서 만들어 준다.
	*/

	MeshSlot* Slot = new MeshSlot;

	m_vecMeshSlot.push_back(Slot);

	Slot->VB = &Container->VB;
	Slot->Primitive = Container->Primitive;

	if (IdxData != nullptr)
	{
		MeshSubset	Subset;
		Container->vecSubset.push_back(Subset);
		int Index = (int)Container->vecSubset.size() - 1;

		Container->vecSubset[Index].Slot = Slot;

		Slot->IB = &Container->vecSubset[Index].IB;

		Slot->IB->Size = IdxSize;
		Slot->IB->Count = IdxCount;
		Slot->IB->Fmt = Fmt;
		Slot->IB->Data = new char[IdxSize * IdxCount];
		memcpy(Slot->IB->Data, IdxData, IdxSize * IdxCount);

		if (!CreateBuffer(BufferType::Index, IdxData, IdxSize, IdxCount,
			IdxUsage, &Slot->IB->Buffer))
			return false;
	}

	return true;
}

void CMesh::Render()
{
	/*렌더링
	
	멤버변수 메쉬슬롯안에 사이즈 만큼 반복문

	디바이스에서 컨텍스트를 가져오고 , 입력어셈블러에 도형을 추가한다 ( 메쉬슬롯별 도형을 가져온다 )
	입력어셈블러에 버텍스버퍼를 추가한다 , 메쉬슬롯에서 버텍스버퍼를 가져오고 , 스트라이드와 오프셋레퍼런스값을 줌 

	만약에 메쉬슬롯에 인덱스버퍼도 있다면 , 인덱스버퍼도 추가해준다 . 

	*/
	size_t	Size = m_vecMeshSlot.size();

	for (size_t i = 0; i < Size; ++i)
	{
		unsigned int	Stride = (unsigned int)m_vecMeshSlot[i]->VB->Size;
		unsigned int	Offset = 0;

		CDevice::GetInst()->GetContext()->IASetPrimitiveTopology(m_vecMeshSlot[i]->Primitive);
		CDevice::GetInst()->GetContext()->IASetVertexBuffers(0, 1,
			&m_vecMeshSlot[i]->VB->Buffer, &Stride, &Offset);

		if (m_vecMeshSlot[i]->IB)
		{
			CDevice::GetInst()->GetContext()->IASetIndexBuffer(
				m_vecMeshSlot[i]->IB->Buffer, m_vecMeshSlot[i]->IB->Fmt,
				0);
			CDevice::GetInst()->GetContext()->DrawIndexed(
				m_vecMeshSlot[i]->IB->Count, 0, 0);
		}

		else
		{
			CDevice::GetInst()->GetContext()->IASetIndexBuffer(
				nullptr, DXGI_FORMAT_UNKNOWN, 0);
			CDevice::GetInst()->GetContext()->Draw(
				m_vecMeshSlot[i]->VB->Count, 0);
		}
	}
}

void CMesh::Render(int SlotNumber)
{
	unsigned int	Stride = (unsigned int)m_vecMeshSlot[SlotNumber]->VB->Size;
	unsigned int	Offset = 0;

	CDevice::GetInst()->GetContext()->IASetPrimitiveTopology(m_vecMeshSlot[SlotNumber]->Primitive);
	CDevice::GetInst()->GetContext()->IASetVertexBuffers(0, 1,
		&m_vecMeshSlot[SlotNumber]->VB->Buffer, &Stride, &Offset);

	if (m_vecMeshSlot[SlotNumber]->IB)
	{
		CDevice::GetInst()->GetContext()->IASetIndexBuffer(
			m_vecMeshSlot[SlotNumber]->IB->Buffer, m_vecMeshSlot[SlotNumber]->IB->Fmt,
			0);
		CDevice::GetInst()->GetContext()->DrawIndexed(
			m_vecMeshSlot[SlotNumber]->IB->Count, 0, 0);
	}

	else
	{
		CDevice::GetInst()->GetContext()->IASetIndexBuffer(
			nullptr, DXGI_FORMAT_UNKNOWN, 0);
		CDevice::GetInst()->GetContext()->Draw(
			m_vecMeshSlot[SlotNumber]->VB->Count, 0);
	}
}

void CMesh::RenderInstancing(int Count)
{
	size_t	Size = m_vecMeshSlot.size();

	for (size_t i = 0; i < Size; ++i)
	{
		unsigned int	Stride = (unsigned int)m_vecMeshSlot[i]->VB->Size;
		unsigned int	Offset = 0;

		CDevice::GetInst()->GetContext()->IASetPrimitiveTopology(m_vecMeshSlot[i]->Primitive);
		CDevice::GetInst()->GetContext()->IASetVertexBuffers(0, 1,
			&m_vecMeshSlot[i]->VB->Buffer, &Stride, &Offset);

		if (m_vecMeshSlot[i]->IB)
		{
			CDevice::GetInst()->GetContext()->IASetIndexBuffer(
				m_vecMeshSlot[i]->IB->Buffer, m_vecMeshSlot[i]->IB->Fmt,
				0);
			CDevice::GetInst()->GetContext()->DrawIndexedInstanced(
				m_vecMeshSlot[i]->IB->Count, Count, 0, 0, 0);
		}

		else
		{
			CDevice::GetInst()->GetContext()->IASetIndexBuffer(
				nullptr, DXGI_FORMAT_UNKNOWN, 0);
			CDevice::GetInst()->GetContext()->DrawInstanced(
				m_vecMeshSlot[i]->VB->Count, Count, 0, 0);
		}
	}
}

void CMesh::RenderInstancing(int Count, int SlotNumber)
{
	unsigned int	Stride = (unsigned int)m_vecMeshSlot[SlotNumber]->VB->Size;
	unsigned int	Offset = 0;

	CDevice::GetInst()->GetContext()->IASetPrimitiveTopology(m_vecMeshSlot[SlotNumber]->Primitive);
	CDevice::GetInst()->GetContext()->IASetVertexBuffers(0, 1,
		&m_vecMeshSlot[SlotNumber]->VB->Buffer, &Stride, &Offset);

	if (m_vecMeshSlot[SlotNumber]->IB)
	{
		CDevice::GetInst()->GetContext()->IASetIndexBuffer(
			m_vecMeshSlot[SlotNumber]->IB->Buffer, m_vecMeshSlot[SlotNumber]->IB->Fmt,
			0);
		CDevice::GetInst()->GetContext()->DrawIndexedInstanced(
			m_vecMeshSlot[SlotNumber]->IB->Count, Count, 0, 0, 0);
	}

	else
	{
		CDevice::GetInst()->GetContext()->IASetIndexBuffer(
			nullptr, DXGI_FORMAT_UNKNOWN, 0);
		CDevice::GetInst()->GetContext()->DrawInstanced(
			m_vecMeshSlot[SlotNumber]->VB->Count, Count, 0, 0);
	}
}

bool CMesh::CreateBuffer(BufferType Type, void* Data, int Size,
	int Count, D3D11_USAGE Usage, ID3D11Buffer** Buffer)
{
	D3D11_BUFFER_DESC	Desc = {};

	Desc.ByteWidth = Size * Count;
	Desc.Usage = Usage;

	if (Type == BufferType::Vertex)
		Desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	else
		Desc.BindFlags = D3D11_BIND_INDEX_BUFFER;

	if (Usage == D3D11_USAGE_DYNAMIC)
		Desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	else if (Usage == D3D11_USAGE_STAGING)
		Desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE | D3D11_CPU_ACCESS_READ;

	D3D11_SUBRESOURCE_DATA	BufferData = {};

	BufferData.pSysMem = Data;

	if (FAILED(CDevice::GetInst()->GetDevice()->CreateBuffer(&Desc, &BufferData,
		Buffer)))
		return false;

	if (Type == BufferType::Vertex)
	{
		// 정점은 위치 12바이트가 항상 먼저 들어와 있을 것이다.
		char* VertexData = (char*)Data;

		for (int i = 0; i < Count; ++i)
		{
			Vector3* Pos = (Vector3*)VertexData;
			VertexData += Size;

			if (m_Min.x > Pos->x)
				m_Min.x = Pos->x;

			if (m_Min.y > Pos->y)
				m_Min.y = Pos->y;

			if (m_Min.z > Pos->z)
				m_Min.z = Pos->z;

			if (m_Max.x < Pos->x)
				m_Max.x = Pos->x;

			if (m_Max.y < Pos->y)
				m_Max.y = Pos->y;

			if (m_Max.z < Pos->z)
				m_Max.z = Pos->z;
		}
	}

	return true;
}
