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


using Microsoft::WRL::ComPtr;
using namespace DirectX;

class Mesh
{
public:
	Mesh();
	virtual ~Mesh();

	// ���� ���� �Լ�, = �������̽�.
	virtual bool InitializeBuffers(ID3D11Device* device, ID3DBlob* vertexShaderBuffer, ConstantBuffer gTransform) = 0;

	// Render = (Bind + Draw)
	virtual void RenderBuffers(ID3D11DeviceContext* deviceContext);

	// ��ο�/������Ʈ ���� ���� �Լ�.
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


protected:
	//int vertexCount;				// ���� ����.
	//ComPtr<ID3D11Buffer> vertexBuffer;		// ���� ����.
	//ComPtr<ID3D11InputLayout> inputLayout; // �Է� ���̾ƿ�.

	VertexBuffer vertexBuffer;
	IndexBuffer indexBuffer;
	InputLayout inputLayout;

	// Ʈ������ ����.
	Transform transform;

	// Ʈ������ ������.
	XMFLOAT3 position;
	XMFLOAT3 rotation;
	XMFLOAT3 scale;
};