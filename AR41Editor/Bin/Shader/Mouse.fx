#include "Share.fx"

cbuffer MouseCBuffer : register(b12)
{
    matrix g_MouseWVP; 
};

struct VS_INPUT_UV
{
    float3 Pos : POSITION;
    float2 UV : TEXCOORD;
};


struct VS_OUTPUT_UV
{
    float4 Pos : SV_POSITION;
    float2 UV : TEXCOORD;
};


VS_OUTPUT_UV MouseVS(VS_INPUT_UV input)
{
    VS_OUTPUT_UV output = (VS_OUTPUT_UV) 0;

    output.Pos = mul(float4(input.Pos, 1.f), g_MouseWVP);
  
    output.UV = input.UV;

    return output;
}

PS_OUTPUT_SINGLE MousePS(VS_OUTPUT_UV input)
{
    PS_OUTPUT_SINGLE output = (PS_OUTPUT_SINGLE) 0;

    float4 TextureColor = g_BaseTexture.Sample(g_PointSmp, input.UV);

    output.Color.rgb = TextureColor.rgb * g_MtrlBaseColor.rgb;

    output.Color.a = TextureColor.a * g_MtrlOpacity;

    return output;
}