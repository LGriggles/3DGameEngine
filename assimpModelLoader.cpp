#include "assimpModelLoader.hpp"
#include "Mesh.hpp"

#include <vector>
#include <assimp\scene.h>
#include <assimp\mesh.h>
//#include "Model.hpp"

/*void AssimpModelLoader::loadModels(string path, Model& LoadToThis)
{
	bool Ret = false;
	Assimp::Importer Importer;

	const aiScene* pScene = Importer.ReadFile(path.c_str(), 
		aiProcess_Triangulate | 
		aiProcess_GenSmoothNormals | 
		aiProcess_FlipUVs |
		aiProcess_FixInfacingNormals |
		aiProcess_GenUVCoords);

	for(int meshIter = 0; meshIter < pScene->mNumMeshes; meshIter++)
	{
		aiMesh* mesh = pScene->mMeshes[meshIter];
		if(!mesh->HasTextureCoords(0))
		{
			int i = 0;
		}
		Mesh* _mesh  = new Mesh();
		//Get the smallest and largest vectors under a standard of the value 500, used for centering the model
		float min[3]=
		{
			500,	//x minimum
			500,	//y minimum
			500,	//z minimum
		},
		max[3]=
			{
				-500,	//x maximum
				-500,	//y maximum
				-500,	//z maximum
			};

			std::vector<sf::Vector3f>* _vertNormals = new std::vector<sf::Vector3f>();
			std::vector<sf::Vector3f>* _vertices = new std::vector<sf::Vector3f>();
			std::vector<sf::Vector2f>* _uvs = new std::vector<sf::Vector2f>();
			for(int i = 0; i < mesh->mNumVertices; i++)
			{
				sf::Vector3f newVector;
				newVector.x = mesh->mVertices[i].x;
				newVector.y = mesh->mVertices[i].y;
				newVector.z = mesh->mVertices[i].z;

				if(newVector.x<min[0])
					min[0] = newVector.x;
				if(newVector.y<min[1])
					min[1] = newVector.y;
				if(newVector.z<min[2])
					min[2] = newVector.z;

				if(newVector.x>max[0])
					max[0] = newVector.x;
				if(newVector.y>max[1])
					max[1] = newVector.y;
				if(newVector.z>max[2])
					max[2] = newVector.z;

				sf::Vector3f newVectorNormals;
				newVectorNormals.x = mesh->mNormals[i].x;
				newVectorNormals.y = mesh->mNormals[i].y;
				newVectorNormals.z = mesh->mNormals[i].z;

				sf::Vector2f newVectorUV;
				newVectorUV.x = mesh->mTextureCoords[0][i].x;
				newVectorUV.y = mesh->mTextureCoords[0][i].y;

				_uvs->push_back(newVectorUV);
				_vertNormals->push_back(newVectorNormals);
				_vertices->push_back(newVector);
			}

			std::vector<sf::Vector3i>* _indices = new std::vector<sf::Vector3i>();
			for(int i = 0; i < mesh->mNumFaces; i++)
			{
				sf::Vector3i face;
				for(int k = 0; k < mesh->mFaces[i].mNumIndices; k++)
				{
					if(k == 0)
						face.x = mesh->mFaces[i].mIndices[k];
					if(k == 1)
						face.y = mesh->mFaces[i].mIndices[k];
					if(k == 2)
						face.z = mesh->mFaces[i].mIndices[k];
				}
				_indices->push_back(face);
			}

			//now do centering
			for(size_t i=0;i<_vertices->size();i++) {
				(*_vertices)[i].x -= min[0];
				(*_vertices)[i].y -= min[1];
				(*_vertices)[i].z -= min[2];

				(*_vertices)[i].x = ((*_vertices)[i].x/(max[0]-min[0])) -0.5f;
				(*_vertices)[i].y = ((*_vertices)[i].y/(max[1]-min[1])) -0.5f;
				(*_vertices)[i].z = ((*_vertices)[i].z/(max[2]-min[2])) -0.5f;
			}

			_mesh->setVerts(*_vertices);
			_mesh->setNorms(*_vertNormals);
			_mesh->setIndices(*_indices);
			_mesh->setUVs(*_uvs);

			LoadToThis._meshes.push_back(_mesh);
	}
}*/

void AssimpModelLoader::loadModel(string path,Mesh& LoadToThis)
{
	bool Ret = false;
	Assimp::Importer Importer;

	const aiScene* pScene = Importer.ReadFile(path.c_str(), 
		aiProcess_Triangulate | 
		aiProcess_GenSmoothNormals | 
		aiProcess_FlipUVs |
		aiProcess_FixInfacingNormals);
	aiMesh* mesh = pScene->mMeshes[0];

	//Get the smallest and largest vectors under a standard of the value 500, used for centering the model
	float min[3]=
	{
		500,	//x minimum
		500,	//y minimum
		500,	//z minimum
	},
	max[3]=
		{
			-500,	//x maximum
			-500,	//y maximum
			-500,	//z maximum
		};

		std::vector<sf::Vector3f>* _vertNormals = new std::vector<sf::Vector3f>();
		std::vector<sf::Vector3f>* _vertices = new std::vector<sf::Vector3f>();
		std::vector<sf::Vector2f>* _uvs = new std::vector<sf::Vector2f>();
		mesh->mNumAnimMeshes;
		for(int i = 0; i < mesh->mNumVertices; i++)
		{
			sf::Vector3f newVector;
			newVector.x = mesh->mVertices[i].x;
			newVector.y = mesh->mVertices[i].y;
			newVector.z = mesh->mVertices[i].z;

			if(newVector.x<min[0])
				min[0] = newVector.x;
			if(newVector.y<min[1])
				min[1] = newVector.y;
			if(newVector.z<min[2])
				min[2] = newVector.z;

			if(newVector.x>max[0])
				max[0] = newVector.x;
			if(newVector.y>max[1])
				max[1] = newVector.y;
			if(newVector.z>max[2])
				max[2] = newVector.z;

			sf::Vector3f newVectorNormals;
			newVectorNormals.x = mesh->mNormals[i].x;
			newVectorNormals.y = mesh->mNormals[i].y;
			newVectorNormals.z = mesh->mNormals[i].z;

			sf::Vector2f newVectorUV;
			newVectorUV.x = mesh->mTextureCoords[0][i].x;
			newVectorUV.y = mesh->mTextureCoords[0][i].y;

			_uvs->push_back(newVectorUV);
			_vertNormals->push_back(newVectorNormals);
			_vertices->push_back(newVector);
		}

		std::vector<sf::Vector3i>* _indices = new std::vector<sf::Vector3i>();
		for(int i = 0; i < mesh->mNumFaces; i++)
		{
			sf::Vector3i face;
			for(int k = 0; k < mesh->mFaces[i].mNumIndices; k++)
			{
				if(k == 0)
					face.x = mesh->mFaces[i].mIndices[k];
				if(k == 1)
					face.y = mesh->mFaces[i].mIndices[k];
				if(k == 2)
					face.z = mesh->mFaces[i].mIndices[k];
			}
			_indices->push_back(face);
		}

		//now do centering
		for(size_t i=0;i<_vertices->size();i++) {
			(*_vertices)[i].x -= min[0];
			(*_vertices)[i].y -= min[1];
			(*_vertices)[i].z -= min[2];

			(*_vertices)[i].x = ((*_vertices)[i].x/(max[0]-min[0])) -0.5f;
			(*_vertices)[i].y = ((*_vertices)[i].y/(max[1]-min[1])) -0.5f;
			(*_vertices)[i].z = ((*_vertices)[i].z/(max[2]-min[2])) -0.5f;
		}

		LoadToThis.setVerts(*_vertices);
		LoadToThis.setNorms(*_vertNormals);
		LoadToThis.setIndices(*_indices);
		LoadToThis.setUVs(*_uvs);
}






