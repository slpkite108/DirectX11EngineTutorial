// «»ºø Ω¶¿Ã¥ı.

cbuffer ConstantBuffer : register(b1)
{
	float4 pixelColor;
};

struct PSInput
{
	float4 position : SV_POSITION;
};

float4 main(PSInput input) : SV_TARGET
{
	//return float4(0.5f,0.5f,0.f,1.f);
	return pixelColor;
}