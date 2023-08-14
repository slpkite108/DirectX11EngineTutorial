// 정점 쉐이더.

cbuffer MatrixBuffer : register(b0)
{
	matrix world;
	matrix view;
	matrix projection;
}

struct vs_input
{
	float4 position : POSITION;
};

struct vs_output
{
	float4 position : SV_POSITION;
};

vs_output main(vs_input input)
{
	vs_output output;
	output.position = mul(input.position,world);
	output.position = mul(output.position, view);
	output.position = mul(output.position, projection);
	return output;
}

// float4 main(float4 position  // IA에서 포지션을 받아 옴. 나중에 복잡해지면 구조체로 만들어서 받을 수 있음.
// : POSITION)	// 지금은 포지션 하나만 받아왔으니까 이게 Position을 뜻하는 거라고 알려줌. 시멘틱.
// : SV_POSITION  // 시스템에게 이게 Position을 뜻하는 거라고 알려줌. SV : 시스템 벨류.