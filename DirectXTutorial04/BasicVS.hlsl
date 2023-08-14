// ���� ���̴�.

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

// float4 main(float4 position  // IA���� �������� �޾� ��. ���߿� ���������� ����ü�� ���� ���� �� ����.
// : POSITION)	// ������ ������ �ϳ��� �޾ƿ����ϱ� �̰� Position�� ���ϴ� �Ŷ�� �˷���. �ø�ƽ.
// : SV_POSITION  // �ý��ۿ��� �̰� Position�� ���ϴ� �Ŷ�� �˷���. SV : �ý��� ����.