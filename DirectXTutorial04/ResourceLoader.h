#pragma once

#include <string>

#include <d3d11.h>
#include <Windows.h>
#include "Vertex.h"
#include <DirectXMath.h>


// assimp 라이브러리.

#include <assimp/Importer.hpp>
#include <assimp/cimport.h>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <vector>

class ResourceLoader
{
public:
	ResourceLoader();
	~ResourceLoader();

	// 모델 로딩.
	static void LoadModel(std::string filename, std::vector<Vertex>* vertices, std::vector<unsigned int>* indices);

	static std::wstring GetExtension(std::wstring str);

};

