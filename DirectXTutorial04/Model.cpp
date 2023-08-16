#include "Model.h"

#include <vector>


Model::Model()
{
}

Model::~Model()
{
}

bool Model::InitializeBuffers(ID3D11Device* device, ID3DBlob* vertexShaderBuffer, ConstantBuffer gTransform)
{
    Vertex vertices[] =
    {
        DirectX::XMFLOAT3(0.0f, 0.5f, 0.5f),
        DirectX::XMFLOAT3(0.5f, -0.5f, 0.5f),
        DirectX::XMFLOAT3(-0.5f, -0.5f, 0.5f)
    };

    if (vertexBuffer.Initialize(device, vertices, ARRAYSIZE(vertices), sizeof(Vertex)) == false)
    {
        return false;
    }

    // �ε��� ���� ����.
    unsigned int indices[] =
    {
        0, 1, 2
    };

    if (indexBuffer.Initialize(device, indices, ARRAYSIZE(indices)) == false)
    {
        return false;
    }

    // ������ ���� �� ����� (�Է� ���̾ƿ�).
    D3D11_INPUT_ELEMENT_DESC layout[] =
    {
        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0}
    };
    if (inputLayout.Initialize(device, layout, ARRAYSIZE(layout), vertexShaderBuffer) == false)
    {
        return false;
    }

    // ��� ����.
    if (transform.Create(device, gTransform) == false)
    {
        return false;
    }

    if (colorBuffer.Create(device) == false)
    {
        return false;
    }

    return true;
}

bool Model::InitializeBuffers(ID3D11Device* device, ID3DBlob* vertexShaderBuffer, std::string modelFileName, ConstantBuffer gTransform)
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    // ���ҽ� �ε�.
    ResourceLoader::LoadModel(modelFileName, &vertices, &indices);

    // ���ؽ� ���� ����.
    if (vertexBuffer.Initialize(device, vertices.data(), vertices.size(), sizeof(Vertex)) == false)
    {
        return false;
    }

    // �ε��� ���� ����.
    if (indexBuffer.Initialize(device, indices.data(), indices.size()) == false)
    {
        return false;
    }

    // ������ ���� �� ����� (�Է� ���̾ƿ�).
    D3D11_INPUT_ELEMENT_DESC layout[] =
    {
        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0} // �տ� position�� float 4���� 12����Ʈ�ϱ� 12.
    };
    if (inputLayout.Initialize(device, layout, ARRAYSIZE(layout), vertexShaderBuffer) == false)
    {
        return false;
    }

    // ��� ����.
    if (transform.Create(device,gTransform) == false)
    {
        return false;
    }

    if (colorBuffer.Create(device) == false)
    {
        return false;
    }

    return true;
}
