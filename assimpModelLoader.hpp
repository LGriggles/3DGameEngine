#ifndef ASSIMPMODELLOADER_HPP
#define ASSIMPMODELLOADER_HPP

#include "Mesh.hpp"

#include <string>
using namespace std;


//Assimp
#include <assimp\Importer.hpp>
#include <assimp\postprocess.h>

class AssimpModelLoader
{
public:
	//void loadModels(string path, Model& LoadToThis);
	void loadModel(string path,Mesh& LoadToThis);
};


#endif