#pragma once
#include "Mesh.h"
#include "ResourceLoader.h"
#include "InputLayout.h"
#include <string>

class Model : public Mesh
{
public:
	Model();
	~Model();

	bool InitializeBuffers(ID3D11Device* device, ID3DBlob* vertexShaderBuffer, ConstantBuffer gTransform) override;
	bool InitializeBuffers(ID3D11Device* device, ID3DBlob* vertexShaderBuffer, std::string modelFileName, ConstantBuffer gTransform);
};