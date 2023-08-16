#include "ColorBuffer.h"

bool ColorBuffer::Create(ID3D11Device* device)
{
    // 상수 버퍼.
    D3D11_BUFFER_DESC colorBufferDesc;
    ZeroMemory(&colorBufferDesc, sizeof(colorBufferDesc));
    colorBufferDesc.ByteWidth = sizeof(XMFLOAT4);
    colorBufferDesc.CPUAccessFlags = 0;
    colorBufferDesc.MiscFlags = 0;
    colorBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    colorBufferDesc.Usage = D3D11_USAGE_DEFAULT;

    // 단위 행렬.
    color = XMFLOAT4(1.f,0.f,1.f,1.f);//purple

    // 데이터 담기.
    D3D11_SUBRESOURCE_DATA colorBufferData;
    ZeroMemory(&colorBufferData, sizeof(colorBufferData));
    colorBufferData.pSysMem = &color;

    // 버퍼 생성.
    HRESULT result = device->CreateBuffer(
        &colorBufferDesc,
        &colorBufferData,
        cBuffer.GetAddressOf()
    );
    if (FAILED(result))
    {
        MessageBox(nullptr, L"상수 버퍼 생성 실패", L"오류", 0);
        return false;
    }

    return true;
}

void ColorBuffer::Bind(ID3D11DeviceContext* deviceContext)
{
    // 행렬 데이터 업데이트.
    deviceContext->UpdateSubresource(cBuffer.Get(), 0, NULL, &color, 0, 0);

    // 행렬 데이터가 담긴 버퍼 바인딩. (설정.)
    deviceContext->PSSetConstantBuffers(1, 1, cBuffer.GetAddressOf());
}