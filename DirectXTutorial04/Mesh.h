#pragma once

#include "Vertex.h"
#include <d3d11.h>
#include <wrl.h>
#include "ConstantBuffer.h"
#include "Transform.h"
#include <DirectXMath.h>

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "InputLayout.h"
#include "ColorBuffer.h"


using Microsoft::WRL::ComPtr;
using namespace DirectX;

class Mesh
{
public:
	Mesh();
	virtual ~Mesh();

	// 순수 가상 함수, = 인터페이스.
	virtual bool InitializeBuffers(ID3D11Device* device, ID3DBlob* vertexShaderBuffer, ConstantBuffer gTransform) = 0;

	// Render = (Bind + Draw)
	virtual void RenderBuffers(ID3D11DeviceContext* deviceContext);

	// 드로우/업데이트 관련 편의 함수.
	virtual void BindBuffers(ID3D11DeviceContext* deviceContext);
	virtual void DrawBuffers(ID3D11DeviceContext* deviceContext);

	virtual void UpdateBuffers(ID3D11DeviceContext* deviceContext);
	virtual void UpdateCustomMatrix(ID3D11DeviceContext* deviceContext, XMMATRIX cTransform);

	// Getter / Setter
	XMFLOAT3& Position() { return position; }
	void SetPosition(float x, float y, float z);
	void SetPosition(XMFLOAT3 position);

	XMFLOAT3& Rotation() { return rotation; }
	void SetRotation(float x, float y, float z);
	void SetRotation(XMFLOAT3 rotation);

	XMFLOAT3& Scale() { return scale; }
	void SetScale(float x, float y, float z);
	void SetScale(XMFLOAT3 scale);

	XMFLOAT4& Color() { return color; }
	void SetColor(float r, float g, float b, float a);
	void SetColor(XMFLOAT4 color);


protected:
	//int vertexCount;				// 정점 개수.
	//ComPtr<ID3D11Buffer> vertexBuffer;		// 정점 버퍼.
	//ComPtr<ID3D11InputLayout> inputLayout; // 입력 레이아웃.

	VertexBuffer vertexBuffer;
	IndexBuffer indexBuffer;
	InputLayout inputLayout;

	// 트랜스폼 버퍼.
	Transform transform;

	// 트랜스폼 데이터.
	XMFLOAT3 position;
	XMFLOAT3 rotation;
	XMFLOAT3 scale;

	ColorBuffer colorBuffer;
	//색성정보
	XMFLOAT4 color;
};