#include "stdafx.h"
#include "ModelLoader.hpp"

#include <fstream>
#include <sstream>
using std::ifstream;
using std::istringstream;

ModelLoader::ModelLoader()
{

}

struct Indexer
{
	int vertex; //The vertex ID for the face
	int iUV;	//The UV ID for the face
	int norm;	//The normal ID for the face
};
void ModelLoader::loadWaveFront(string path, Mesh& loadToThis)
{
	vector<Indexer> indexes;
	std::vector<sf::Vector2f> _textureUVsOrderd; //UVs after ordering in accordance to faces
	std::vector<sf::Vector3f> _normalsOrderd; //Normals sorted for rendering
	std::vector<sf::Vector3f> _verticesOrderd; //Verts for mesh

	std::vector<sf::Vector2f> _textureUVs; //UVs for texture
	std::vector<sf::Vector3f> _vertices; //Verts for mesh
	std::vector<sf::Vector3f> _colours; //Intrinsic colouring
	std::vector<sf::Vector3i> _faces;
	std::vector<sf::Vector3f> _normals;

	indexes.clear();
	_vertices.clear();
	_colours.clear();
	_textureUVs.clear();
	_textureUVsOrderd.clear();
	_normals.clear();

	ifstream objectFile(path.c_str());	//Stream the object (wavefront) file
	if(!objectFile) //If this fails return
	{
		return;
	}
	string tmp(std::istreambuf_iterator<char>(objectFile), (std::istreambuf_iterator<char>()));
	istringstream buffer(tmp);
	objectFile.close();


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

		string line;

		while(getline(buffer, line)) 
		{
			line.erase(line.find_last_not_of(" \n\r\t")+1);
			if(line.find_first_of("#") != -1)
			{
				continue; //This line is simply a comment in the file skip the iteration
			}

			string prefix = line.substr(0, line.find_first_of(" "));

			if(prefix.compare("vt")==0) //if we have a texture coord
			{
				line = line.substr(line.find_first_of("vt")+2);
				sf::Vector2f uv;
				uv.x = 0;
				uv.y = 0;

				istringstream s(line);

				s>>uv.x;
				s>>uv.y;
				uv.y *=-1;

				_textureUVs.push_back(uv);
			}
			if(prefix.compare("v")==0) //if we have a vertex
			{
				line = line.substr(line.find_first_of("v")+2);
				sf::Vector3f vert;

				istringstream s(line);
				s>>vert.x;
				s>>vert.y;
				s>>vert.z;
				if(vert.x<min[0])
					min[0] = vert.x;
				if(vert.y<min[1])
					min[1] = vert.y;
				if(vert.z<min[2])
					min[2] = vert.z;

				if(vert.x>max[0])
					max[0] = vert.x;
				if(vert.y>max[1])
					max[1] = vert.y;
				if(vert.z>max[2])
					max[2] = vert.z;
				_vertices.push_back(vert);
			}
			if(prefix.compare("vn")==0) //we have a normal
			{
				line = line.substr(line.find_first_of("vn")+2);
				sf::Vector3f normal;

				istringstream s(line);
				s>>normal.x;
				s>>normal.y;
				s>>normal.z;

				_normals.push_back(normal);
			}
			if(prefix.compare("f")==0)
			{
				line = line.substr(line.find_first_of("f")+2);

				Indexer newIndex;
				string currentVertex = "";
				string currentUV = "";
				string currentNorm = "";
				unsigned int step = 0;
				for(auto iter : line)
				{
					if(iter == '/')
					{
						step ++;
						continue;
					}
					else if(iter == ' ')
					{
						if(step == 2)
						{
							newIndex.vertex = atoi(currentVertex.c_str());
							newIndex.iUV = atoi(currentUV.c_str());
							newIndex.norm = atoi(currentNorm.c_str());

							indexes.push_back(newIndex);
							step = 0;
							currentVertex = "";
							currentUV = "";
							currentNorm = "";
							//End
						}
						continue;
					}
					else if(step == 0) //Vertex
					{
						currentVertex += iter;
					}
					else if(step == 1) //UV ID
					{
						currentUV += iter;
					}
					else if(step == 2) //Normal ID
					{
						currentNorm += iter;
					}
				}
				newIndex.vertex = atoi(currentVertex.c_str());
				newIndex.iUV = atoi(currentUV.c_str());
				newIndex.norm = atoi(currentNorm.c_str());

				indexes.push_back(newIndex);
				step = 0;
				currentVertex = "";
				currentUV = "";
				currentNorm = "";
			}
		}

		//now do centering
		for(size_t i=0;i<_vertices.size();i++) {
			_vertices[i].x -= min[0];
			_vertices[i].y -= min[1];
			_vertices[i].z -= min[2];

			_vertices[i].x = (_vertices[i].x/(max[0]-min[0])) -0.5f;
			_vertices[i].y = (_vertices[i].y/(max[1]-min[1])) -0.5f;
			_vertices[i].z = (_vertices[i].z/(max[2]-min[2])) -0.5f;
		}

		_faces.clear();
		int i = 0;
		int step = 0;
		for(auto iter : indexes)
		{
			_verticesOrderd.push_back(_vertices.at(iter.vertex-1));
			_textureUVsOrderd.push_back(_textureUVs.at(iter.iUV-1));
			_normalsOrderd.push_back(_normals.at(iter.norm-1));

			step ++;
			if(step == 3)
			{
				glm::vec3 v1 = glm::vec3(
						_verticesOrderd.at(i).x,
						_verticesOrderd.at(i).y,
						_verticesOrderd.at(i).z
					);

				glm::vec3 v2 = glm::vec3(
						_verticesOrderd.at(i+1).x,
						_verticesOrderd.at(i+1).y,
						_verticesOrderd.at(i+1).z
					);

				glm::vec3 v3 = glm::vec3(
						_verticesOrderd.at(i+2).x,
						_verticesOrderd.at(i+2).y,
						_verticesOrderd.at(i+2).z
					);

				glm::vec3 vCross1 = v3 - v1;
				glm::vec3 vCross2 = v2 - v1;

				glm::vec3 crossedVector = glm::cross(vCross1,vCross2);

				glm::vec3 normalVector = glm::normalize(crossedVector);

				_faces.push_back(sf::Vector3i(i,i+1,i+2));
				i+=3;
				step = 0;
			}
		}

		loadToThis.setVerts(_verticesOrderd);
		loadToThis.setIndices(_faces);
		loadToThis.setUVs(_textureUVsOrderd);
		loadToThis.setNorms(_normalsOrderd);

		return;
}