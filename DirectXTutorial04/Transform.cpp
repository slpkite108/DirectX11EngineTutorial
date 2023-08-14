#include "Transform.h"

bool Transform::Create(ID3D11Device* device, ConstantBuffer gTransform)
{
    // ��� ����.
    D3D11_BUFFER_DESC transformBufferDesc;
    ZeroMemory(&transformBufferDesc, sizeof(transformBufferDesc));
    transformBufferDesc.ByteWidth = sizeof(ConstantBuffer);
    transformBufferDesc.CPUAccessFlags = 0;
    transformBufferDesc.MiscFlags = 0;
    transformBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    transformBufferDesc.Usage = D3D11_USAGE_DEFAULT;

    // ���� ���.
    transformMatrix.mWorld = XMMatrixTranspose(gTransform.mWorld);
    transformMatrix.mView = XMMatrixTranspose(gTransform.mView);
    transformMatrix.mProjection = XMMatrixTranspose(gTransform.mProjection);

    // ������ ���.
    D3D11_SUBRESOURCE_DATA transformBufferData;
    ZeroMemory(&transformBufferData, sizeof(transformBufferData));
    transformBufferData.pSysMem = &transformMatrix;

    // ���� ����.
    HRESULT result = device->CreateBuffer(
        &transformBufferDesc,
        &transformBufferData,
        cBuffer.GetAddressOf()
    );
    if (FAILED(result))
    {
        MessageBox(nullptr, L"��� ���� ���� ����", L"����", 0);
        return false;
    }

    return true;
}

void Transform::Bind(ID3D11DeviceContext* deviceContext)
{
    // ��� ������ ������Ʈ.
    deviceContext->UpdateSubresource(cBuffer.Get(), 0, NULL, &transformMatrix, 0, 0);

    // ��� �����Ͱ� ��� ���� ���ε�. (����.)
    deviceContext->VSSetConstantBuffers(0, 1, cBuffer.GetAddressOf());
}