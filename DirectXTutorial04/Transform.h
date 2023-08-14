#pragma once
#include <wrl.h>
#include <d3d11.h>
#include <DirectXMath.h>
#include "ConstantBuffer.h"

using Microsoft::WRL::ComPtr;
using namespace DirectX;

class Transform
{
public:
	ConstantBuffer transformMatrix;

	Transform() : transformMatrix() {}
	~Transform() = default;

	bool Create(ID3D11Device* device, ConstantBuffer gTransform);
	void Bind(ID3D11DeviceContext* deviceContext);

private:
	ComPtr<ID3D11Buffer> cBuffer;
};