#ifndef SCENE_H
#define SCENE_H

//C++
#include <vector>
using std::vector;

//GLM
#include <GL\glew.h>

//SFML
#include <SFML\System.hpp>
#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <SFML\OpenGL.hpp>
#include <gtx\transform.hpp>

//3DGameEngine
#include "SoundManager.hpp"
#include "Mesh.hpp"
#include "Actor.hpp"
#include "Camera.hpp"
#include "Shader.hpp"
#include "TestingGrounds.hpp"
#include "Texture.hpp"

/*! A shader renderer */
class ShaderRenderer
{
public:
	GLuint programHandle;
	vector<Actor *> _activeObjects;
	Shader* _myShader;
};

/*! The game world */
class Scene
{
private:

	sf::Font _engineFont; //!< Engine's default font
	sf::Text _loadingText; //!< loading text

	float _cameraSpeed;  //!< Camera speed
	sf::Thread* newThread;


	SoundManager _soundManager;	//!< Manages the scene's sound
	enum StateScene {
		SPLASHSCENE,
		RUNNING,
		LOADINGSCENE,
		OPENGLGENERATES,
	} _sceneState;			//!< current state of the scene
	bool _shiftWalk;		//!< Shift walk
	bool _paused;			//!< Is the scene paused
	bool _wireFrame;		//!< Specifies if wireframe mode is on or off

	std::vector<sf::Vector2f>	_textureUVs;	//!< UVs for texture
	std::vector<sf::Vector3f>	_vertices;		//!< Verts for mesh
	vector<sf::Vector3f>		_vertNorms;		//!< Vertex normals
	std::vector<sf::Vector3i>	_indices;		//!< Indices

	Shader _shaderTexture;		//!< Shader for texturing
	Shader _shaderColour;		//!< Shader for colouring in accordance to normals
	Mesh _planeMesh;			//!< A flat 2D plane
	Mesh _testModelLoadOne;		//!< A loaded mesh
	Mesh _testModelLoadTwo;		//!< A loaded mesh
	Mesh _testModelLoadThree;	//!< A loaded mesh
	Mesh _testModelLoadFour;	//!< A loaded mesh
	vector<ShaderRenderer*> _shaderRenderers;
public:
	Scene();
	~Scene();
	void init();			//!< Initialize the scene
	void update();			//!< Update the scene
	void draw();			//!< Draw the scene
	void runningInit();		//!< Called drawing running of the scene for intialization
	void runningUpdate();	//!< The running update
	void render();			//!< Rendering
	void setState(StateScene newSceneState);	//!< Set the state
	void winAPIinput(unsigned int input);		//!< Windows API callbacks
	void setWireFrame(bool wireframe);			//!< Set the wireframe mode
	void switchWireFrame();						//!< Switch the wireframe mode
private:
	vector<Shader> _shaderList;			//!< List of cached shaders
	vector<Actor *> _activeObjects;		//!< Active objects in the scene
	Camera _cameraOne, _cameraTwo;		//!< The two cameras
	Camera *_activeCamera;				//!< The currently active camera
	glm::vec3 _lightPoint;				//!< The position of the light
	//Test objects and textures below
	Actor* _objectOne;
	Actor* _objectTwo;
	Actor* _objectThree;
	Actor* _objectFour;
	Actor* _objectGround;
	Actor* _rotatingCube;
	Actor* _rotatingCubeTwo;
	Actor* _skyBox;
	Actor* _loadingScreen;
	GLuint ProjectionViewModelMatrixID;
	Texture testTexture;
	Texture secondTexture;
	Texture thirdTexture;
	Texture fourthTexture;
	Texture groundTexture;
	Texture _skyBoxTexture;
	Texture _loadingTexture;
public:
	template<class T_ACTORTYPE>
	Actor& createActor(glm::vec3 position,Texture& texture, Mesh& mesh, int shaderIndex)
	{
		Actor* temp = new T_ACTORTYPE();
		temp->drawingInstance.giveTexture(texture);
		temp->init();
		temp->drawingInstance.giveMesh(mesh);

		temp->_transform.setPosition(position);
		_shaderRenderers[shaderIndex]->_activeObjects.push_back(temp);
		_activeObjects.push_back(temp);
		return *temp;
	}	//!< Create an actor from the templated type, the templated class must derive from the Actor base class


	void clearActors()
	{
		for(auto iterShaders : _shaderRenderers)
		{
			iterShaders->_activeObjects.clear();
		}
	}
};
#endif // !SCENE_H
