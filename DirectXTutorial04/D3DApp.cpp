#include "D3DApp.h"

D3DApp::D3DApp(HINSTANCE hInstance, int width, int height, std::wstring title)
{
    // Window Ŭ������ �� ����.
    Window::SetInstance(hInstance);
    Window::SetWidth(width);
    Window::SetHeight(height);
    Window::SetTitle(title);
}

D3DApp::~D3DApp()
{

}

bool D3DApp::Initialize()
{
    if (Window::InitializeWindow() == false)
    {
        return false;
    }
    if (InitializeDirect3D() == false)
    {
        return false;
    }
    return true;
}

bool D3DApp::InitializeDirect3D()
{
    // ��ġ ����.
    // Device - ����.
    // DeviceContext - ��, ��ġ ����.
    // SwapChain - ǥ��.

    // ���� ü�� ���� ����. �������� �ʹ� ���Ƽ� ����ü�� ����������.
    DXGI_SWAP_CHAIN_DESC swapChainDesc;
    ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
    swapChainDesc.BufferCount = 1;                          // ����� 1��. Double Buffering. Screen Tearing. ����Ʈ����, ���۹� ���ļ� �� 2�� ���ٴ� ��.
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;    // ��� ����. ȭ�� ��¿����� ���ٴ� ��.
    swapChainDesc.OutputWindow = Window::WindowHandle();    // ����� ������ ����.
    swapChainDesc.Windowed = true;                          // â ��� ����.
    swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;    // ����Ʈ���ۿ� ����۸� �ٲ� ��, ȿ�� �� ���ٴ� ��. (���� ���� �� ��).

    swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;   // Ÿ��. RGBA�� 8��Ʈ�� ���. (0~255 ��.) UNORM�� ����ȭ. (0~255 ���� 0~1�� �ٲ�.)
    swapChainDesc.BufferDesc.Width = Window::Width();               // �ʺ�.
    swapChainDesc.BufferDesc.Height = Window::Height();             // ����.

    swapChainDesc.SampleDesc.Count = 1;             // ��Ƽ ���ø� ���� 1��. (�� ���ٴ� ��.) Anti-Alasing.
    swapChainDesc.SampleDesc.Quality = 0;           // Count - 1.

    // ��ġ ����.
    HRESULT result = D3D11CreateDeviceAndSwapChain(
        nullptr,
        D3D_DRIVER_TYPE_HARDWARE, // �׷��� ���ӱ�. ���� �̰Ÿ� ��. ���� �� ȣȯ�Ѵٰ� ���� ����.
        nullptr,
        0,
        nullptr,
        0,
        D3D11_SDK_VERSION,
        &swapChainDesc,
        &swapChain,
        &device,
        NULL,
        &deviceContext
    );

    // ���� �˻�.
    if (FAILED(result))
    {
        MessageBox(nullptr, L"��ġ ���� ����", L"����", 0);
        return false;
    }

    // ����� ����?���ٴ� ���� �޾ƿ���. 
    // �츮�� ����ۿ� �ٷ� �� �׸�. View�� ���� ���������� ������.
    // ����� ������ �����ؼ� �ִϱ� ����.
    ID3D11Texture2D* backbufferTexture;
    result = swapChain->GetBuffer(
        0,
        __uuidof(ID3D11Texture2D), // Ÿ�� ���� ���. uuidof : ���⿡ ���۹� ���� �޶�.
        (LPVOID*)(&backbufferTexture) // Ÿ�Կ� ������� �ּҰ��� �ް� ���� �� void ������.
    );

    // ���� �˻�.
    if (FAILED(result))
    {
        MessageBox(nullptr, L"����� ���� �����µ� ����", L"����", 0);
        return false;
    }

    // ���� Ÿ�� ��(View)
    // ����ۿ� ���� �������� ���ϱ� ������ �並 ���� ���� ����.
    result = device->CreateRenderTargetView(
        backbufferTexture, // ���⿡ ���� �ְ�,
        nullptr,
        &renderTargetView // �ű⿡ ���缭 �����ش޶�.
    );

    // ���� �˻�.
    if (FAILED(result))
    {
        MessageBox(nullptr, L"���� Ÿ�� �� ���� ����", L"����", 0);
        return false;
    }

    //depth
    D3D11_TEXTURE2D_DESC descDepth;
    ZeroMemory(&descDepth, sizeof(descDepth));
    descDepth.Width = (float)Window::Width();
    descDepth.Height = (float)Window::Height();
    descDepth.MipLevels = 1;
    descDepth.ArraySize = 1;
    descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    descDepth.SampleDesc.Count = 1;
    descDepth.SampleDesc.Quality = 0;
    descDepth.Usage = D3D11_USAGE_DEFAULT;
    descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    descDepth.CPUAccessFlags = 0;
    descDepth.MiscFlags = 0;

    result = device->CreateTexture2D(
        &descDepth,
        NULL,
        &depthBuffer
    );

    if (FAILED(result))
    {
        MessageBox(nullptr, L"���� ���� ���� ����", L"����", 0);
        return false;
    }

    //stencilbuffer
    D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
    ZeroMemory(&descDSV, sizeof(descDSV));
    descDSV.Format = descDepth.Format;
    descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
    descDSV.Texture2D.MipSlice = 0;

    result = device->CreateDepthStencilView(
        depthBuffer,
        &descDSV,
        &depthStencilView
    );

    if (FAILED(result))
    {
        MessageBox(nullptr, L"���ٽ� �� ���� ����", L"����", 0);
        return false;
    }

    // �ӽ� ����(���ҽ�) ����.
    backbufferTexture->Release(); // delete Ű����� �ϴ� ���� ������, Release�� �ؾ� �����ϰ� ���� ����.

    // ���� Ÿ�� �� �Ҵ�.(����)
    deviceContext->OMSetRenderTargets( // OM : Output Merger �����شٴ� �ǹ�. ��� ���� ���� ��ȯ �� ��.
        1, // ȭ���� 4���� �����ٸ�, 4�� �Էµ�.
        &renderTargetView,
        depthStencilView
    );

    // ����Ʈ(ȭ��) - ũ�� ����.
    viewport.TopLeftX = 0;
    viewport.TopLeftY = 0;
    viewport.Width = (float)Window::Width();
    viewport.Height = (float)Window::Height();

    viewport.MinDepth = 0.0f;
    viewport.MaxDepth = 1.0f;

    // ����Ʈ �Ҵ�.
    deviceContext->RSSetViewports(1, &viewport); // RS : �����Ͷ�����

    return true;
}
