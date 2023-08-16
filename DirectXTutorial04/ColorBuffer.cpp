#include "ColorBuffer.h"

bool ColorBuffer::Create(ID3D11Device* device)
{
    // ��� ����.
    D3D11_BUFFER_DESC colorBufferDesc;
    ZeroMemory(&colorBufferDesc, sizeof(colorBufferDesc));
    colorBufferDesc.ByteWidth = sizeof(XMFLOAT4);
    colorBufferDesc.CPUAccessFlags = 0;
    colorBufferDesc.MiscFlags = 0;
    colorBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    colorBufferDesc.Usage = D3D11_USAGE_DEFAULT;

    // ���� ���.
    color = XMFLOAT4(1.f,0.f,1.f,1.f);//purple

    // ������ ���.
    D3D11_SUBRESOURCE_DATA colorBufferData;
    ZeroMemory(&colorBufferData, sizeof(colorBufferData));
    colorBufferData.pSysMem = &color;

    // ���� ����.
    HRESULT result = device->CreateBuffer(
        &colorBufferDesc,
        &colorBufferData,
        cBuffer.GetAddressOf()
    );
    if (FAILED(result))
    {
        MessageBox(nullptr, L"��� ���� ���� ����", L"����", 0);
        return false;
    }

    return true;
}

void ColorBuffer::Bind(ID3D11DeviceContext* deviceContext)
{
    // ��� ������ ������Ʈ.
    deviceContext->UpdateSubresource(cBuffer.Get(), 0, NULL, &color, 0, 0);

    // ��� �����Ͱ� ��� ���� ���ε�. (����.)
    deviceContext->PSSetConstantBuffers(1, 1, cBuffer.GetAddressOf());
}