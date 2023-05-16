#include "BlendState.h"
#include "../Device.h"

CBlendState::CBlendState() :
	m_SampleMask(0xffffffff),
	m_PrevSampleMask(0),
	m_BlendFactor{},
	m_PrevBlendFactor{}
{
	m_Type = ERenderStateType::Blend;
	SetTypeID<CBlendState>();
}

CBlendState::~CBlendState()
{
}

void CBlendState::AddBlendInfo(bool BlendEnable, D3D11_BLEND SrcBlend,
	D3D11_BLEND DestBlend, D3D11_BLEND_OP BlendOp, D3D11_BLEND SrcAlphaBlend,
	D3D11_BLEND DestAlphaBlend, D3D11_BLEND_OP BlendAlphaOp, UINT8 WriteMask)
{

	D3D11_RENDER_TARGET_BLEND_DESC	Desc = {};

	Desc.BlendEnable = BlendEnable;
	Desc.SrcBlend = SrcBlend;
	Desc.DestBlend = DestBlend;
	Desc.BlendOp = BlendOp;
	Desc.SrcBlendAlpha = SrcAlphaBlend;
	Desc.DestBlendAlpha = DestAlphaBlend;
	Desc.BlendOpAlpha = BlendAlphaOp;
	Desc.RenderTargetWriteMask = WriteMask;

	m_vecDesc.push_back(Desc);
}

bool CBlendState::CreateState(bool AlphaToCoverageEnable, bool IndependentBlendEnable)
{
	if (m_vecDesc.empty())
		return false;

	D3D11_BLEND_DESC Desc = {};

	Desc.AlphaToCoverageEnable = AlphaToCoverageEnable;
	Desc.IndependentBlendEnable = IndependentBlendEnable;

	memcpy(Desc.RenderTarget, &m_vecDesc[0], sizeof(D3D11_RENDER_TARGET_BLEND_DESC) * m_vecDesc.size());

	if (FAILED(CDevice::GetInst()->GetDevice()->CreateBlendState(&Desc, (ID3D11BlendState**)&m_State)))
		return false;

	return true;
}

void CBlendState::SetState()
{
	CDevice::GetInst()->GetContext()->OMGetBlendState((ID3D11BlendState**)&m_PrevState,
		m_PrevBlendFactor, &m_PrevSampleMask);

	CDevice::GetInst()->GetContext()->OMSetBlendState((ID3D11BlendState*)m_State,
		m_BlendFactor, m_SampleMask);
}

void CBlendState::ResetState()
{
	CDevice::GetInst()->GetContext()->OMSetBlendState((ID3D11BlendState*)m_PrevState,
		m_PrevBlendFactor, m_PrevSampleMask);

	SAFE_RELEASE(m_PrevState);
}
