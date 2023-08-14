#include "ResourceLoader.h"

#include <wrl.h>
using Microsoft::WRL::ComPtr;

ResourceLoader::ResourceLoader()
{

}
ResourceLoader::~ResourceLoader()
{

}

void ResourceLoader::LoadModel(std::string filename, std::vector<Vertex>* vertices, std::vector<unsigned int>* indices)
{
	// 리소스 경로 추가.
	//filename = std::string(".//res//models//") + filename;
	filename = std::string("C://Users//Nature//git//DirectX//res//model//") + filename;
	// 옵션 설정.

	const aiScene* scene = aiImportFile(
		filename.c_str(),
		aiProcess_JoinIdenticalVertices |
		aiProcess_ValidateDataStructure |
		aiProcess_ImproveCacheLocality |
		aiProcess_RemoveRedundantMaterials |
		aiProcess_GenUVCoords |
		aiProcess_TransformUVCoords |
		aiProcess_FindInstances |
		aiProcess_LimitBoneWeights |
		aiProcess_OptimizeMeshes |
		aiProcess_GenSmoothNormals |
		aiProcess_SplitLargeMeshes |
		aiProcess_Triangulate | // 폴리곤이 사각형이면, 삼각형을 쪼갬. 엔진에서도 다 그럼.
		aiProcess_ConvertToLeftHanded |
		aiProcess_SortByPType
	);

	// 임포트.
	if (scene != nullptr)
	{
		const aiMesh* mesh = scene->mMeshes[0]; // 원래는 여러 개 있을 수도 있어서, 루프 돌아야 함.
		vertices->reserve(mesh->mNumVertices);
		indices->reserve((size_t)(mesh->mNumFaces) * 3);

		// 정점 배열 채우기.
		for (int ix = 0; ix < mesh->mNumVertices; ix++)
		{
			// 위치 읽어오기
			DirectX::XMFLOAT3 position = DirectX::XMFLOAT3(
				mesh->mVertices[ix].x,
				mesh->mVertices[ix].y,
				mesh->mVertices[ix].z
			);
			Vertex vertex;
			vertex.Position = position;
			vertices->push_back(vertex);
		}

		for (unsigned int ix = 0; ix < mesh->mNumFaces; ix++)
		{
			const aiFace& face = mesh->mFaces[ix];
			indices->push_back(face.mIndices[0]);
			indices->push_back(face.mIndices[1]);
			indices->push_back(face.mIndices[2]);
		}
	}
	else
	{
		MessageBox(nullptr, L"모델 로드 실패", L"오류", 0);
		throw std::exception("모델 로드 실패");
	}
}

std::wstring ResourceLoader::GetExtension(std::wstring str)
{
	size_t size = str.rfind('.', str.length());
	if (size != std::wstring::npos)
	{
		return (str.substr(size + 1, str.length() - size));
	}
	return std::wstring();
}
