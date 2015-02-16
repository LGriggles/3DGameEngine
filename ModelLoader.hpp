#ifndef MODELLOADER_HPP
#define MODELLOADER_HPP

//C++
#include <string>
using std::string;

//3DGameEngine
#include "Mesh.hpp"

/*! Loads OBJ file model data in */
class ModelLoader {
public:
	ModelLoader();										
	void loadWaveFront(string path,Mesh& LoadToThis);	//!< Loads a .OBJ file from the specified path onto the specified LoadToThis mesh
};



#endif // !MODELLOADER_HPP
