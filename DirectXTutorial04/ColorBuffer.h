#pragma once
#include <wrl.h>
#include <d3d11.h>
#include <DirectXMath.h>

using Microsoft::WRL::ComPtr;
using namespace DirectX;

class ColorBuffer
{
public:
	XMFLOAT4 color;

	ColorBuffer() : color() {}
	~ColorBuffer() = default;

	bool Create(ID3D11Device* device);
	void Bind(ID3D11DeviceContext* deviceContext);

private:
	ComPtr<ID3D11Buffer> cBuffer;
};