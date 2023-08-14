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
    // 창 만들기.
    // 장치 생성.
    if (D3DApp::Initialize() == false)
    {
        return false;
    }

    // 장면 초기화.
    if (InitializeScene() == false)
    {
        return false;
    }

    return true;
}

// 1. 메시지 처리 루프.
// 2. 엔진 루프.
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
    // 색상 고르기.
    float backgroundColor[4] = { 0.1f, 0.1f, 0.1f, 1.0f };
    
    // 지우기 (Clear) - 실제로는 덮어씌워서 색칠하기.
    // Begin Draw(Render) - DX9.
    deviceContext->ClearRenderTargetView(renderTargetView, backgroundColor);

    deviceContext->VSSetShader(vertexShader, NULL, NULL);
    deviceContext->PSSetShader(pixelShader, NULL, NULL);

    Sun.RenderBuffers(deviceContext);
    merc.RenderBuffers(deviceContext);
    // 프레임 바꾸기. FrontBuffer <-> BackBuffer.
    swapChain->Present(1, 0);
}

bool Engine::InitializeScene()
{
    gTransform = {
        DirectX::XMMatrixIdentity(),
        DirectX::XMMatrixLookAtLH(DirectX::XMVectorSet(0.f,1.f,-5.f,0.f), DirectX::XMVectorSet(0.f,1.f,0.f,0.f), DirectX::XMVectorSet(0.f,1.f,0.f,0.f)),
        DirectX::XMMatrixPerspectiveFovLH(DirectX::XM_PI / 2.0f,width / float(height),0.01f,1000.0f)
    };

    // VS 컴파일
    HRESULT result = D3DCompileFromFile(
        L"..//DirectXTutorial04//BasicVS.hlsl",
        NULL,
        NULL,
        "main", // wchar(와일드 캐릭터) 아니라서 L 안 붙여도 됨.
        "vs_5_0",
        NULL,
        NULL,
        &vertexShaderBuffer, // 컴파일 된 이진코드를 받아올 버퍼.
        NULL
    );
    if (FAILED(result)) { MessageBox(nullptr, L"정점 쉐이더 컴파일 실패", L"오류", 0); }

    // VS 생성.
    result = device->CreateVertexShader(
        vertexShaderBuffer->GetBufferPointer(), // 시작 지점 주소.
        vertexShaderBuffer->GetBufferSize(), // 얼마만큼 읽을 지.
        nullptr,
        &vertexShader
    );
    if (FAILED(result)) { MessageBox(nullptr, L"정점 쉐이더 생성 실패", L"오류", 0); }

    // VS랑 하는 방식은 똑같음. 파일명이랑 변수명만 조금씩 바꿔주자.
    // PS 컴파일.
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
    if (FAILED(result)) { MessageBox(nullptr, L"픽셀 쉐이더 컴파일 실패", L"오류", 0); }

    // PS 생성.
    result = device->CreatePixelShader(
        pixelShaderBuffer->GetBufferPointer(),
        pixelShaderBuffer->GetBufferSize(),
        nullptr,
        &pixelShader
    );
    if (FAILED(result)) { MessageBox(nullptr, L"픽셀 쉐이더 생성 실패", L"오류", 0); }

    // 정점 데이터 만들기.

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
