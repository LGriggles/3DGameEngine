#include "stdafx.h"

//SFML
#include <SFML\System.hpp>

//3DGameEngine
#include "Scene.hpp"
#include "InputHandler.hpp"
#include "resource.h"
#include "ModelLoader.hpp"

#include "RacingCar.h"

//GLM
#include <glm.hpp>

enum ShaderTextureUniforms
{
	PROJECTION,
	VIEW,
	MODEL,
	LIGHTPOSITION,
};

//RUNTIME CALLS
void Scene::runningInit()
{
	clearActors();
	ModelLoader modelLoader;
	modelLoader.loadWaveFront("Resources/Models/LOL.obj",_testModelLoadOne);
	modelLoader.loadWaveFront("Resources/Models/GoronLink.obj",_testModelLoadThree);
	modelLoader.loadWaveFront("Resources/Models/DekuLink.obj",_testModelLoadTwo);

	testTexture.init("Resources/Models/LOL.png");
	secondTexture.init("Resources/Models/DekuLink_grp.png");
	thirdTexture.init("Resources/Models/GoronLink_grp.png");
	fourthTexture.init("Resources/Models/texture_diffuse.jpg");
	groundTexture.init("Resources/texture1.jpg");
	_skyBoxTexture.init("Resources/space.png");

	//Create actors on the scene
	_objectOne = &createActor<RacingCar>(glm::vec3(0,0,0), secondTexture, _testModelLoadTwo,0);
	_objectTwo = &createActor<Actor>(glm::vec3(2.6,1,-4), testTexture, _testModelLoadOne,0);
	createActor<Actor>(glm::vec3(-1.0f,0.0f,0.0), thirdTexture, _testModelLoadThree,0);
	_rotatingCubeTwo = &createActor<Actor>(glm::vec3(2.5,1,0), fourthTexture, _testModelLoadFour,1);
	Actor* temp = &createActor<Actor>(glm::vec3(0,-0.5f,0), groundTexture, _planeMesh,0);
	_rotatingCube = &createActor<Actor>(glm::vec3(5,32,0.0f), fourthTexture, _testModelLoadFour,0);
	_skyBox = &createActor<Actor>(glm::vec3(0.0,0.0,0.0f), _skyBoxTexture, _testModelLoadFour,0);
	_skyBox->_transform.setScale(glm::vec3(30,50,30));
	temp->_transform.setScale(glm::vec3(20,1,20));
	_cameraTwo.setTarget(_objectOne->_transform._position);

	for(unsigned int i = 0; i < 4; i++)
	{
		createActor<Actor>(glm::vec3(i,0,-4),fourthTexture,_testModelLoadFour,0);
	}
	for(int k = 0; k < 4; k++)
	{
		createActor<Actor>(glm::vec3(4,0,-4+k),fourthTexture,_testModelLoadFour,0);
	}
	for(unsigned int i = 0; i < 2; i++)
	{
		createActor<Actor>(glm::vec3(0.5+i,1,-4),fourthTexture,_testModelLoadFour,0);
	}
	_lightPoint = glm::vec3(10,10,10);
	_soundManager.playSound(0);
	
	setState(StateScene::OPENGLGENERATES);
}

//Running state
void Scene::runningUpdate()
{

	//Camera navigation
	if(EngineInput::keyboardInput.isKeyHeld(sf::Keyboard::D))
	{
		if(!_shiftWalk)
		{
			_activeCamera->StrafeRight(_cameraSpeed);
		}
		else
		{
			_activeCamera->StrafeRight(_cameraSpeed/2);
		}
	}
	if(EngineInput::keyboardInput.isKeyHeld(sf::Keyboard::A))
	{	
		if(!_shiftWalk)
		{
			_activeCamera->StrafeLeft(_cameraSpeed);
		}
		else
		{
			_activeCamera->StrafeLeft(_cameraSpeed/2);
		}
	}
	if(EngineInput::keyboardInput.isKeyHeld(sf::Keyboard::W))
	{
		if(!_shiftWalk)
		{
			_activeCamera->GoForward(_cameraSpeed);
		}
		else
		{
			_activeCamera->GoForward(_cameraSpeed/2);
		}
	}
	if(EngineInput::keyboardInput.isKeyHeld(sf::Keyboard::S))
	{	
		if(!_shiftWalk)
		{
			_activeCamera->GoBackward(_cameraSpeed);
		}
		else
		{
			_activeCamera->GoBackward(_cameraSpeed/2);
		}
	}
	if(EngineInput::keyboardInput.isKeyHeld(sf::Keyboard::LShift) || EngineInput::keyboardInput.isKeyHeld(sf::Keyboard::RShift))
	{
		_shiftWalk = true;
	}
	else
	{
		_shiftWalk = false;
	}
	if(EngineInput::keyboardInput.isKeyPressed(sf::Keyboard::B))
	{
		switchWireFrame();
	}

	//Add a game object
	if(EngineInput::keyboardInput.isKeyPressed(sf::Keyboard::K))
	{	
		createActor<JumpingObject>(_activeCamera->getPosition(),testTexture,_testModelLoadOne,0);
	}

	//Switch cameras
	if(EngineInput::keyboardInput.isKeyPressed(sf::Keyboard::C))
	{
		if(_activeCamera == &_cameraOne)
		{
			_activeCamera = &_cameraTwo;
		}
		else
		{
			_activeCamera = &_cameraOne;
		}
	}

	//Send camera home 0,0,0
	if(EngineInput::keyboardInput.isKeyPressed(sf::Keyboard::H))
	{
		_activeCamera->setPosition(glm::vec3(0,0,0));
	}
	//Pause game
	if(EngineInput::keyboardInput.isKeyPressed(sf::Keyboard::P))
	{
		switch(_paused)
		{
		case 0:
			_paused = true;
			break;
		case 1:
			_paused = false;
			break;
		}
	}

	//Update the active camera
	_activeCamera->update();

	if(!_paused)
	{
		//Rotate the cubes
		_rotatingCube->_transform.rotate(glm::vec3(0,0.05f,0));
		_rotatingCubeTwo->_transform.rotate(glm::vec3(0,0.05f,0));
		_objectTwo->_transform.rotate(glm::vec3(0,0.05f,0));
		if(EngineInput::keyboardInput.isKeyPressed(sf::Keyboard::LAlt))
		{
						EngineInput::mouseInput.setMousePosition(sf::Vector2i(
				(240/2),
				(320/2))
				);
		}
		if(EngineInput::keyboardInput.isKeyHeld(sf::Keyboard::LAlt))
		{
			double mouseX = EngineInput::mouseInput.getMousePosition().x-(240/2);
			double mouseY = EngineInput::mouseInput.getMousePosition().y-(320/2);
			_activeCamera->rotate((float)mouseX,(float)mouseY);
			EngineInput::mouseInput.setMousePosition(sf::Vector2i(
				(240/2),
				(320/2))
				);
		}
		//update all game objects
		for(auto it : _activeObjects)
		{
			it->update();
		}
	}
}


//ENGINE CALLS
void Scene::init()
{
	ModelLoader modelLoader;
	modelLoader.loadWaveFront("Resources/Models/mesh.obj",_testModelLoadFour);
	_testModelLoadFour.generateMesh();

	_cameraSpeed = 0.1f;
	int introSoundID = _soundManager.loadSound("Resources/introSound.wav");

	_sceneState = StateScene::LOADINGSCENE;
	_activeCamera = &_cameraOne; //Set the camera
	_cameraOne.init();
	_cameraTwo.init();

	_shiftWalk = true;

	//Define 2D flat plane mesh
	_vertices.push_back(sf::Vector3f(-1,0,1));
	_vertices.push_back(sf::Vector3f(-1,0,-1));
	_vertices.push_back(sf::Vector3f(1,0,-1));
	_vertices.push_back(sf::Vector3f(1,0,1));
	_indices.push_back(sf::Vector3i(0,1,2));
	_indices.push_back(sf::Vector3i(0,2,3));
	_textureUVs.push_back(sf::Vector2f(0,0));
	_textureUVs.push_back(sf::Vector2f(1,0));
	_textureUVs.push_back(sf::Vector2f(1,1));
	_textureUVs.push_back(sf::Vector2f(1,0));
	//Set up the mesh
	_planeMesh.setVerts(_vertices);
	_planeMesh.setIndices(_indices);
	_planeMesh.setUVs(_textureUVs);
	_planeMesh.generateMesh();
	//Make way for new shape
	_vertices.clear();
	_indices.clear(); 
	_textureUVs.clear();

	//Set up shaders
	_shaderTexture.createShader("Resources/Shaders/textureShader.vert","Resources/Shaders/textureShader.frag");
	_shaderTexture.storeUniform(ShaderTextureUniforms::PROJECTION,"projectionMatrix");
	_shaderTexture.storeUniform(ShaderTextureUniforms::VIEW,"viewMatrix");
	_shaderTexture.storeUniform(ShaderTextureUniforms::MODEL,"modelMatrix");
	_shaderTexture.storeUniform(ShaderTextureUniforms::LIGHTPOSITION,"lightPosition");

	_shaderColour.createShader("Resources/Shaders/basic.vert","Resources/Shaders/basic.frag");
	_shaderColour.storeUniform(ShaderTextureUniforms::PROJECTION,"projectionMatrix");
	_shaderColour.storeUniform(ShaderTextureUniforms::VIEW,"viewMatrix");
	_shaderColour.storeUniform(ShaderTextureUniforms::MODEL,"modelMatrix");

	ShaderRenderer* shaderRenderer = new ShaderRenderer();
	shaderRenderer = new ShaderRenderer();
	shaderRenderer->programHandle = _shaderTexture.getProgramID();
	_shaderRenderers.push_back(shaderRenderer);
	shaderRenderer->_myShader = &_shaderTexture;

	shaderRenderer = new ShaderRenderer();
	shaderRenderer->programHandle = _shaderColour.getProgramID();
	_shaderRenderers.push_back(shaderRenderer);
	shaderRenderer->_myShader = &_shaderColour;
	_loadingTexture.init("Resources/texture2.png");
	_loadingTexture.GenerateTexture();
	_loadingScreen = &createActor<Actor>(glm::vec3(1.5,1,-0.5f),_loadingTexture,_testModelLoadFour,0);
	_loadingScreen->_transform.setScale(glm::vec3(1,1,1));
	_loadingScreen->_transform.rotate(glm::vec3(0,-4,0));

	newThread = new sf::Thread(&Scene::runningInit, this);
	newThread->launch();
}

//Scene states
void Scene::update()
{
	switch(_sceneState)
	{
	case StateScene::SPLASHSCENE:
		break;

	case StateScene::LOADINGSCENE:
		_activeCamera->update();
		_loadingScreen->_transform.rotate(glm::vec3(0,0.01f,0));
		break;

	case StateScene::OPENGLGENERATES:
		_testModelLoadTwo.generateMesh();
		_testModelLoadOne.generateMesh();
		_testModelLoadThree.generateMesh();

		testTexture.GenerateTexture();
		secondTexture.GenerateTexture();
		thirdTexture.GenerateTexture();
		fourthTexture.GenerateTexture();
		groundTexture.GenerateTexture();
		_skyBoxTexture.GenerateTexture();
		setState(StateScene::RUNNING);
		break;

	case StateScene::RUNNING:
		runningUpdate();
		break;
	}
}


void Scene::draw()
{	
	switch(_sceneState)
	{
	case StateScene::LOADINGSCENE:
		{
			glUseProgram(_shaderTexture.getProgramID());
			glBindTexture(GL_TEXTURE_2D,_loadingScreen->drawingInstance.getTexture().getTextureHandle());
			Mesh& temp = _loadingScreen->drawingInstance.getMesh();

			temp.getMatrix() = glm::translate(_loadingScreen->_transform._position);

			temp.getMatrix() = glm::rotate(temp.getMatrix(), _loadingScreen->_transform._rotation.x, glm::vec3(1.f,0.f,0.f));
			temp.getMatrix() = glm::rotate(temp.getMatrix(), _loadingScreen->_transform._rotation.y, glm::vec3(0.f,1.f,0.f));
			temp.getMatrix() = glm::rotate(temp.getMatrix(), _loadingScreen->_transform._rotation.z, glm::vec3(0.f,0.f,1.f));
			temp.getMatrix() = glm::scale(temp.getMatrix(),_loadingScreen->_transform._scale);

			glUniformMatrix4fv(_shaderTexture.getStoredUniform(ShaderTextureUniforms::PROJECTION),1, GL_FALSE, &_activeCamera->getProjectionMatrix()[0][0]);
			glUniformMatrix4fv(_shaderTexture.getStoredUniform(ShaderTextureUniforms::VIEW),1,	GL_FALSE, &_activeCamera->getViewMatrix()[0][0]);
			glUniformMatrix4fv(_shaderTexture.getStoredUniform(ShaderTextureUniforms::MODEL),1,	GL_FALSE, &temp.getMatrix()[0][0]);
			glUniform3f(_shaderTexture.getStoredUniform(ShaderTextureUniforms::LIGHTPOSITION),_lightPoint.x,_lightPoint.y,_lightPoint.z);
			_loadingScreen->drawingInstance.getMesh().Draw();
		}
		break;
	case StateScene::SPLASHSCENE:
		{

		}
		break;

	case StateScene::RUNNING:
		{
			for(ShaderRenderer* shaderIter : _shaderRenderers)
			{
				glUseProgram(shaderIter->programHandle);

				for(Actor* it : shaderIter->_activeObjects)
				{
					if(it->drawingInstance.hasMesh())	//Does this drawing instance have a mesh?
					{
						if(it->drawingInstance.hasTexture())	//Does this drawing instance have a texture?
						{
							glBindTexture(GL_TEXTURE_2D,it->drawingInstance.getTexture().getTextureHandle());
						}
						Mesh& temp = it->drawingInstance.getMesh();

						temp.getMatrix() = it->_transform.getTransMatrix();

						glUniformMatrix4fv(shaderIter->_myShader->getStoredUniform(ShaderTextureUniforms::PROJECTION),1, GL_FALSE, &_activeCamera->getProjectionMatrix()[0][0]);
						glUniformMatrix4fv(shaderIter->_myShader->getStoredUniform(ShaderTextureUniforms::VIEW),1,	GL_FALSE, &_activeCamera->getViewMatrix()[0][0]);
						glUniformMatrix4fv(shaderIter->_myShader->getStoredUniform(ShaderTextureUniforms::MODEL),1,	GL_FALSE, &temp.getMatrix()[0][0]);
						glUniform3f(shaderIter->_myShader->getStoredUniform(ShaderTextureUniforms::LIGHTPOSITION),_lightPoint.x,_lightPoint.y,_lightPoint.z);
						it->drawingInstance.getMesh().Draw();
					}
				}
			}
		}
		break;
	}
}

void Scene::winAPIinput(unsigned int input)
{
	switch(input)
	{
	case ID_CAMERAS_CAMERAONE:
			_activeCamera = &_cameraOne;
		break;

	case ID_CAMERAS_CAMERATWO:
			_activeCamera = &_cameraTwo;
		break;

	case ID_OBJECT_CREATE:
			createActor<JumpingObject>(_activeCamera->getPosition(),testTexture,_testModelLoadOne,0);
		break;

	case ID_MODE_REAL:
			setWireFrame(false);
			_paused = false;
		break;

	case ID_MODE_DEBUG:
			setWireFrame(true);
			_paused = true;
		break;
	}
}

void Scene::setState(StateScene newSceneState)
{
	_sceneState = newSceneState;
}


void Scene::setWireFrame(bool wireFrame)
{
	_wireFrame = wireFrame;
	switch(_wireFrame)
		{
		case false:
				glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
			break;

		case true:
				glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
			break;
		}
}

void Scene::switchWireFrame()
{
		switch(_wireFrame)
		{
		case false:
				glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
				_wireFrame = true;
			break;

		case true:
				glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
				_wireFrame = false;
			break;
		}
}

Scene::Scene()
{
	_paused = false;
}

Scene::~Scene()
{

}