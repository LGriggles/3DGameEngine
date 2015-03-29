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
#include "ActorManager.hpp"
#include "CollisionEngine.hpp"
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
	CollisionEngine _collisionEngine;

	Shader _shaderTexture;		//!< Shader for texturing
	Shader _shaderColour;		//!< Shader for colouring in accordance to normals
	Mesh _planeMesh;			//!< A flat 2D plane
	Mesh _testModelLoadOne;		//!< A loaded mesh
	Mesh _testModelLoadTwo;		//!< A loaded mesh
	Mesh _testModelLoadThree;	//!< A loaded mesh
	Mesh _testModelLoadFour;	//!< A loaded mesh
	vector<ShaderRenderer*> _shaderRenderers;
public:
	ActorManager _actorManager;
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
	Camera _cameraOne, _cameraTwo;		//!< The two cameras
	Camera *_activeCamera;				//!< The currently active camera
	glm::vec3 _lightPoint;				//!< The position of the light
	//Test objects and textures below
	Actor* _objectOne;
	Actor* _objectGround;
	Actor* _loadingScreen;
	Actor* _debugCursor;
	Actor* block;
	GLuint ProjectionViewModelMatrixID;
	Texture testTexture;
	Texture secondTexture;
	Texture thirdTexture;
	Texture metalTexture;
	Texture brickTexture;
	Texture groundTexture;
	Texture _skyBoxTexture;
	Texture _loadingTexture;

	void destroyBricks (sf::Vector2i pos, int x, int y, int size);

public:

	Actor& createActor(glm::vec3 position,int actorID)
	{
		Actor* temp =_actorManager.createActor(actorID);
		temp->_actorID = actorID;
		temp->_gameScene = this;
		temp->setGridLocked(false);
		temp->_collisionEngine = &_collisionEngine;
		temp->init();

		temp->_transform.setPosition(position);
		return *temp;
	}

	Actor& createActor(glm::vec3 position,Texture& texture, Mesh& mesh, int shaderIndex, int actorID)
	{
		Actor* temp =_actorManager.createActor(actorID);
		temp->_actorID = actorID;
		temp->_gameScene = this;
		temp->setGridLocked(false);
		temp->setGridPos(sf::Vector2i(0,0));
		temp->_collisionEngine = &_collisionEngine;
		temp->drawingInstance.giveTexture(texture);
		temp->init();
		temp->drawingInstance.giveMesh(mesh);

		temp->_transform.setPosition(position);
		return *temp;
	}	//!< Create an actor from the templated type, the templated class must derive from the Actor base class


	Actor& createActor(glm::vec3 position,Texture& texture, Mesh& mesh, int shaderIndex, sf::Vector2i grid, int actorID)
	{
		Actor* temp =_actorManager.createActor(actorID);
		temp->_actorID = actorID;
		temp->_gameScene = this;
		temp->setGridLocked(true);
		temp->setGridPos(grid);
		temp->_collisionEngine = &_collisionEngine;
		temp->drawingInstance.giveTexture(texture);
		temp->init();
		temp->drawingInstance.giveMesh(mesh);

		temp->_transform.setPosition(position);
		return *temp;
	}	//!< Create an actor from the templated type, the templated class must derive from the Actor base class

	bool isOdd( int integer )
	{

		if ( integer % 2== 0 )
			return true;
		else
			return false;
	}

	void clearActors()
	{

	}
};
#endif // !SCENE_H
