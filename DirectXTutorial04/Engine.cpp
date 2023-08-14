#include "Engine.h"
#include <d3dcompiler.h>

Engine::Engine(HINSTANCE hInstance, int width, int height, std::wstring title)
    : D3DApp(hInstance, width, height, title),width(width),height(height)
{

}

Engine::~Engine()
{
}

bool Engine::Initialize()
{
    // â �����.
    // ��ġ ����.
    if (D3DApp::Initialize() == false)
    {
        return false;
    }

    // ��� �ʱ�ȭ.
    if (InitializeScene() == false)
    {
        return false;
    }

    return true;
}

// 1. �޽��� ó�� ����.
// 2. ���� ����.
int Engine::Run()
{
    MSG msg;
    ZeroMemory(&msg, sizeof(msg));

    while (msg.message != WM_QUIT)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE) == TRUE)
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            Update();
            DrawScene();
        }
    }

    return 0;
}

void Engine::Update()
{
    static float t = 0;
    t += 0.01;
    
    DirectX::XMMATRIX cT = XMMatrixMultiply(XMMatrixMultiply(XMMatrixScaling(merc.Scale().x, merc.Scale().y,merc.Scale().z), XMMatrixTranslation(1.0f, 0.f, 0.f)), XMMatrixRotationRollPitchYaw(0.f, t*3, 0.f));
    Sun.UpdateBuffers(deviceContext);
    merc.UpdateCustomMatrix(deviceContext,cT);
}

void Engine::DrawScene()
{
    // ���� ����.
    float backgroundColor[4] = { 0.1f, 0.1f, 0.1f, 1.0f };
    
    // ����� (Clear) - �����δ� ������� ��ĥ�ϱ�.
    // Begin Draw(Render) - DX9.
    deviceContext->ClearRenderTargetView(renderTargetView, backgroundColor);

    deviceContext->VSSetShader(vertexShader, NULL, NULL);
    deviceContext->PSSetShader(pixelShader, NULL, NULL);

    Sun.RenderBuffers(deviceContext);
    merc.RenderBuffers(deviceContext);
    // ������ �ٲٱ�. FrontBuffer <-> BackBuffer.
    swapChain->Present(1, 0);
}

bool Engine::InitializeScene()
{
    gTransform = {
        DirectX::XMMatrixIdentity(),
        DirectX::XMMatrixLookAtLH(DirectX::XMVectorSet(0.f,1.f,-5.f,0.f), DirectX::XMVectorSet(0.f,1.f,0.f,0.f), DirectX::XMVectorSet(0.f,1.f,0.f,0.f)),
        DirectX::XMMatrixPerspectiveFovLH(DirectX::XM_PI / 2.0f,width / float(height),0.01f,1000.0f)
    };

    // VS ������
    HRESULT result = D3DCompileFromFile(
        L"..//DirectXTutorial04//BasicVS.hlsl",
        NULL,
        NULL,
        "main", // wchar(���ϵ� ĳ����) �ƴ϶� L �� �ٿ��� ��.
        "vs_5_0",
        NULL,
        NULL,
        &vertexShaderBuffer, // ������ �� �����ڵ带 �޾ƿ� ����.
        NULL
    );
    if (FAILED(result)) { MessageBox(nullptr, L"���� ���̴� ������ ����", L"����", 0); }

    // VS ����.
    result = device->CreateVertexShader(
        vertexShaderBuffer->GetBufferPointer(), // ���� ���� �ּ�.
        vertexShaderBuffer->GetBufferSize(), // �󸶸�ŭ ���� ��.
        nullptr,
        &vertexShader
    );
    if (FAILED(result)) { MessageBox(nullptr, L"���� ���̴� ���� ����", L"����", 0); }

    // VS�� �ϴ� ����� �Ȱ���. ���ϸ��̶� ������ ���ݾ� �ٲ�����.
    // PS ������.
    result = D3DCompileFromFile(
        L"..//DirectXTutorial04//BasicPS.hlsl",
        NULL,
        NULL,
        "main",
        "ps_5_0",
        NULL,
        NULL,
        &pixelShaderBuffer,
        NULL
    );
    if (FAILED(result)) { MessageBox(nullptr, L"�ȼ� ���̴� ������ ����", L"����", 0); }

    // PS ����.
    result = device->CreatePixelShader(
        pixelShaderBuffer->GetBufferPointer(),
        pixelShaderBuffer->GetBufferSize(),
        nullptr,
        &pixelShader
    );
    if (FAILED(result)) { MessageBox(nullptr, L"�ȼ� ���̴� ���� ����", L"����", 0); }

    // ���� ������ �����.

    //if (model.InitializeBuffers(device, vertexShaderBuffer, gTransform)==false)
    if (Sun.InitializeBuffers(device, vertexShaderBuffer, "sphere.fbx", gTransform) == false)
    {
        return false;
    }
    Sun.SetPosition(0.f, 0.f, 0.f);
    Sun.SetScale(0.5f, 0.5f, 0.5f);

    if (merc.InitializeBuffers(device, vertexShaderBuffer, "sphere.fbx", gTransform) == false)
    {
        return false;
    }
    merc.SetScale(0.1f, 0.1f, 0.1f);
   
    return true;
}
