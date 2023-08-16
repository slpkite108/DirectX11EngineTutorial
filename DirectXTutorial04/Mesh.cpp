#include "Mesh.h"

Mesh::Mesh()
    : vertexBuffer(), indexBuffer(), inputLayout(),
    transform(), // transform(TransformBuffer())랑 같음.
    position(XMFLOAT3(0.f, 0.f, 0.f)),
    rotation(XMFLOAT3(0.f, 0.f, 0.f)),
    scale(XMFLOAT3(1.f, 1.f, 1.f)),
    colorBuffer(),
    color(XMFLOAT4(1.f,0.f,1.f,1.f))
{
}

Mesh::~Mesh()
{
}


void Mesh::RenderBuffers(ID3D11DeviceContext* deviceContext)
{
    BindBuffers(deviceContext);
    DrawBuffers(deviceContext);
}

void Mesh::BindBuffers(ID3D11DeviceContext* deviceContext)
{
    vertexBuffer.Bind(deviceContext);
    indexBuffer.Bind(deviceContext);
    inputLayout.Bind(deviceContext);

    deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST); // 선을 그릴 때는 LineList.

    transform.Bind(deviceContext);
    colorBuffer.Bind(deviceContext);
}

void Mesh::DrawBuffers(ID3D11DeviceContext* deviceContext)
{
    // Draw
    //deviceContext->Draw(vertexCount, 0); // 이게 DrawCall이다.
    deviceContext->DrawIndexed(indexBuffer.Count(), 0, 0);
}

void Mesh::UpdateBuffers(ID3D11DeviceContext* deviceContext)
{
    transform.transformMatrix.mWorld = XMMatrixTranspose(XMMatrixMultiply(XMMatrixMultiply(XMMatrixScalingFromVector(XMLoadFloat3(&scale)), XMMatrixRotationRollPitchYawFromVector(XMLoadFloat3(&rotation))), XMMatrixTranslationFromVector(XMLoadFloat3(&position))));
    colorBuffer.color = color;
}

void Mesh::UpdateCustomMatrix(ID3D11DeviceContext* deviceContext, XMMATRIX cTransform)
{
    transform.transformMatrix.mWorld = XMMatrixTranspose(cTransform);
    colorBuffer.color = color;
}

void Mesh::SetPosition(float x, float y, float z)
{
    position = XMFLOAT3(x, y, z);
}

void Mesh::SetPosition(XMFLOAT3 position)
{
    this->position = position;
}

void Mesh::SetRotation(float x, float y, float z)
{
    rotation = XMFLOAT3(x, y, z);
}

void Mesh::SetRotation(XMFLOAT3 rotation)
{
    this->rotation = rotation;
}

void Mesh::SetScale(float x, float y, float z)
{
    scale = XMFLOAT3(x, y, z);
}

void Mesh::SetScale(XMFLOAT3 scale)
{
    this->scale = scale;
}

void Mesh::SetColor(float r, float g, float b, float a)
{
    color = XMFLOAT4(r,g,b,a);
}

void Mesh::SetColor(XMFLOAT4 color)
{
    this->color = color;
}