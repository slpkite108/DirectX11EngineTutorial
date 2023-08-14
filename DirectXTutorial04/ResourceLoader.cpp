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
	// ���ҽ� ��� �߰�.
	//filename = std::string(".//res//models//") + filename;
	filename = std::string("C://Users//Nature//git//DirectX//res//model//") + filename;
	// �ɼ� ����.

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
		aiProcess_Triangulate | // �������� �簢���̸�, �ﰢ���� �ɰ�. ���������� �� �׷�.
		aiProcess_ConvertToLeftHanded |
		aiProcess_SortByPType
	);

	// ����Ʈ.
	if (scene != nullptr)
	{
		const aiMesh* mesh = scene->mMeshes[0]; // ������ ���� �� ���� ���� �־, ���� ���ƾ� ��.
		vertices->reserve(mesh->mNumVertices);
		indices->reserve((size_t)(mesh->mNumFaces) * 3);

		// ���� �迭 ä���.
		for (int ix = 0; ix < mesh->mNumVertices; ix++)
		{
			// ��ġ �о����
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
		MessageBox(nullptr, L"�� �ε� ����", L"����", 0);
		throw std::exception("�� �ε� ����");
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
