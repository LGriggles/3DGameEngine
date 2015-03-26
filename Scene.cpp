#include "stdafx.h"

//SFML
#include <SFML\System.hpp>

//3DGameEngine
#include "Scene.hpp"
#include "InputHandler.hpp"
#include "resource.h"
#include "assimpModelLoader.hpp"
#include "DestroyableBlock.hpp"

#include "RacingCar.h"
#include "DebugCursor.h"


enum ActorTypes
{
	BLOCK,
	DESTROYBLOCK,
	PLAYER,
	BOMB,
	DEBUGCURSOR,
	GROUND,
};

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
	_actorManager.instantiateFactory<RacingCar>(ActorTypes::PLAYER);
	_actorManager.instantiateFactory<Actor>(ActorTypes::BLOCK);
	_actorManager.instantiateFactory<Actor>(ActorTypes::BOMB);
	_actorManager.instantiateFactory<Actor>(ActorTypes::DESTROYBLOCK);
	_actorManager.instantiateFactory<Actor>(ActorTypes::DEBUGCURSOR);
	_actorManager.instantiateFactory<Actor>(ActorTypes::GROUND);

	AssimpModelLoader modelLoader;
	modelLoader.loadModel("Resources/Models/LOL.obj",_testModelLoadOne);
	modelLoader.loadModel("Resources/Models/Bomb.obj",_testModelLoadThree);
	modelLoader.loadModel("Resources/Models/DekuLink.obj",_testModelLoadTwo);

	testTexture.init("Resources/Models/LOL.png");
	secondTexture.init("Resources/Models/DekuLink_grp.png");
	thirdTexture.init("Resources/Models/bombTex.png");
	metalTexture.init("Resources/Models/metalBlock3.png");
	brickTexture.init("Resources/Models/brickBlock3.png");
	groundTexture.init("Resources/gameboard3.png");
	_skyBoxTexture.init("Resources/space.png");

	_debugCursor = &createActor(glm::vec3(3,2,3), brickTexture, _testModelLoadFour, 0, sf::Vector2i(0, 0),ActorTypes::DEBUGCURSOR);
	_debugCursor->_collision._depth = 1.3;
	_debugCursor->_collision._width = 1.3;
	_debugCursor->_collision._length = 1.3;
	//Create actors on the scene
	Actor* temp = &createActor(glm::vec3(0,-0.5f,0), groundTexture, _planeMesh,0,ActorTypes::GROUND);
	temp->_transform.setScale(glm::vec3(20,1,20));
	_collisionEngine._colliders.push_back(temp);
	temp->_collision._width = 20*3;
	temp->_collision._length = 20*3;
	temp->_collision._depth = 1;
	//_cameraTwo.setTarget(_objectOne->_transform._position);
	//_cameraTwo.setTarget(_objectOne->_transform._position);

	for(unsigned int i = 0; i < 17; i++)
	{
		block = &createActor(glm::vec3((i*3),2,(0)),metalTexture,_testModelLoadFour,0,ActorTypes::DESTROYBLOCK);
		_collisionEngine._colliders.push_back(block);
		block->_collision._width = 3;
		block->_collision._length = 3;
		block->_collision._depth = 3;
		block = &createActor(glm::vec3((i*3),2,(16*3)),metalTexture,_testModelLoadFour,0,ActorTypes::DESTROYBLOCK);
		_collisionEngine._colliders.push_back(block);
		block->_collision._width = 3;
		block->_collision._length = 3;
		block->_collision._depth = 3;
	}
	for(unsigned int k = 0; k < 17; k++)
	{
		block = &createActor(glm::vec3((0),2,(k*3)),metalTexture,_testModelLoadFour,0,ActorTypes::DESTROYBLOCK);
		_collisionEngine._colliders.push_back(block);
		block->_collision._width = 3;
		block->_collision._length = 3;
		block->_collision._depth = 3;
		block = &createActor(glm::vec3((16*3),2,(k*3)),metalTexture,_testModelLoadFour,0,ActorTypes::DESTROYBLOCK);
		_collisionEngine._colliders.push_back(block);
		block->_collision._width = 3;
		block->_collision._length = 3;
		block->_collision._depth = 3;
	}
	for(unsigned int i = 0; i < 7; i++)
	{
		for(int k = 0; k < 7; k++)
		{
			block = &createActor(glm::vec3(6+(i*6),2,6+(k*6)),metalTexture,_testModelLoadFour,0,ActorTypes::DESTROYBLOCK);
			_collisionEngine._colliders.push_back(block);
			block->_collision._width = 3;
			block->_collision._length = 3;
			block->_collision._depth = 3;
		}
	}

	for(unsigned int i = 0; i < 15; i++)
	{
		int tmp = i;
		if (isOdd(i)){
			for(int k = 0; k < 15; k++)
			{
				block = &createActor(glm::vec3(3+(i*3),2,3+(k*3)), brickTexture,_testModelLoadFour,0, sf::Vector2i(i, k),ActorTypes::DESTROYBLOCK);
				_collisionEngine._colliders.push_back(block);
				block->_collision._width = 3;
				block->_collision._length = 3;
				block->_collision._depth = 3;
				block->_collision.isActive = true;
				block->drawingInstance.setHasMesh(true);
			}
		}
		else{
			for(int k = 0; k < 8; k++)
			{
				block = &createActor(glm::vec3(3+(i*3),2,3+(k*6)), brickTexture,_testModelLoadFour,0, sf::Vector2i(i, k*2),ActorTypes::DESTROYBLOCK);
				_collisionEngine._colliders.push_back(block);
				block->_collision._width = 3;
				block->_collision._length = 3;
				block->_collision._depth = 3;
				block->_collision.isActive = true;
				block->drawingInstance.setHasMesh(true);
			}
		}
	}

	_lightPoint = glm::vec3(10,30,10);
	_soundManager.playSound(0);

	setState(StateScene::OPENGLGENERATES);
}

//Running state
void Scene::runningUpdate()
{
	_actorManager.update();
	if(EngineInput::keyboardInput.isKeyPressed(sf::Keyboard::N))
	{
		((RacingCar*)_objectOne)->_playerState = RacingCar::TELEPORTATION;
	}
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
	if(EngineInput::keyboardInput.isKeyPressed(sf::Keyboard::Space))
	{
		_objectOne = &createActor(_debugCursor->_transform._position, secondTexture, _testModelLoadTwo,0,ActorTypes::PLAYER);
		_objectOne->_collision._depth = 2.6;
		_objectOne->_collision._width = 2.6;
		_objectOne->_collision._length = 2.6;
		((RacingCar*)_objectOne)->_teleportEndPosition = _objectOne->_transform._position;
	}
	/*if(EngineInput::keyboardInput.isKeyPressed(sf::Keyboard::M))
	{
		for(auto it : _activeObjects)
		{
			if (it->isGridLocked() && it->getGridPos() == _debugCursor->getGridPos())
			{
				it->_collision.isActive = true;
				it->drawingInstance.setHasMesh(true);
				it->drawingInstance.giveMesh(_testModelLoadFour);
				it->drawingInstance.giveTexture(brickTexture);
				_debugCursor->drawingInstance.giveTexture(secondTexture);
			}
		}
	}
	if(EngineInput::keyboardInput.isKeyPressed(sf::Keyboard::U))
	{
		for(auto it : _activeObjects)
		{
			if (it->isGridLocked() && it->getGridPos() == _debugCursor->getGridPos())
			{ 
				it->_collision.isActive = true;
				it->drawingInstance.setHasMesh(true);
				it->drawingInstance.giveMesh(_testModelLoadFour);
				it->drawingInstance.giveTexture(metalTexture);
				_debugCursor->drawingInstance.giveTexture(secondTexture);
			}
		}
	}*/
	if(EngineInput::keyboardInput.isKeyPressed(sf::Keyboard::Num0))
	{
		metalTexture.init("Resources/Models/metalBlock1.png");
		brickTexture.init("Resources/Models/brickBlock1.png");
		groundTexture.init("Resources/gameboard1.png");
		metalTexture.GenerateTexture();
		brickTexture.GenerateTexture();
		groundTexture.GenerateTexture();
	}

	if(EngineInput::keyboardInput.isKeyPressed(sf::Keyboard::G))
	{
		_activeCamera->getRotation();
		_activeCamera->getPosition();
		std::cout << "lol" << std::endl;
	}

	//if(EngineInput::keyboardInput.isKeyPressed(sf::Keyboard::I))
	//{
	//	for(auto it : _activeObjects)
	//	{
	//		if (it->isGridLocked() && it->getGridPos() == _debugCursor->getGridPos())
	//		{ 
	//			it->_collision.isActive = false;
	//			it->drawingInstance.setHasMesh(false);
	//			//it-> 
	//			it->drawingInstance.giveTexture(metalTexture);
	//			_debugCursor->drawingInstance.giveTexture(secondTexture);
	//			_debugCursor->drawingInstance.setHasMesh(true);
	//		}
	//	}
	//}
	//if(EngineInput::keyboardInput.isKeyPressed(sf::Keyboard::L))
	//{
	//	sf::Vector2i playerPos = sf::Vector2i(glm::floor((_objectOne->_transform._position.x + 1.5) / 3) - 1, glm::floor((_objectOne->_transform._position.z + 1.5) / 3) - 1);
	//	for(auto it : _activeObjects)
	//	{
	//		if (it->isGridLocked() && it->getGridPos() == playerPos)
	//		{
	//			it->_actorID = ActorTypes::BOMB;
	//			it->_collision.isActive = false;
	//			it->drawingInstance.giveMesh(_testModelLoadThree);
	//			it->drawingInstance.giveTexture(thirdTexture);
	//			_debugCursor->drawingInstance.giveTexture(secondTexture);
	//			_debugCursor->drawingInstance.setHasMesh(true);
	//		}
	//	}
	//}

	//Add a game object
	if(EngineInput::keyboardInput.isKeyPressed(sf::Keyboard::K))
	{	
		//for(auto it : _activeObjects)
		//{
		//	if (it->getActorType() == ActorTypes::BOMB)
		//	{ 
		//		it->_collision.isActive = false;
		//		it->drawingInstance.setHasMesh(false);
		//		destroyBricks(it->getGridPos(), 0, -1, 4);
		//		destroyBricks(it->getGridPos(), 0, 1, 4);
		//		destroyBricks(it->getGridPos(), -1, 0, 4);
		//		destroyBricks(it->getGridPos(), 1, 0, 4);
		//		//it->drawingInstance.giveTexture(thirdTexture);
		//		_debugCursor->drawingInstance.giveTexture(secondTexture);
		//		_debugCursor->drawingInstance.setHasMesh(true);
		//	}
		//}
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
		
	}
}


//ENGINE CALLS
void Scene::init()
{
	AssimpModelLoader modelLoader;
	modelLoader.loadModel("Resources/Models/mesh.obj",_testModelLoadFour);
	_testModelLoadFour.generateMesh();

	_cameraSpeed = 0.1f;
	int introSoundID = _soundManager.loadSound("Resources/introSound.wav");

	_sceneState = StateScene::LOADINGSCENE;
	_activeCamera = &_cameraOne; //Set the camera
	_cameraOne.init();
	_cameraTwo.init();

	_shiftWalk = true;

	//Define 2D flat plane mesh
	_vertices.push_back(sf::Vector3f(-0.06,0.2,2.25));
	_vertices.push_back(sf::Vector3f(-0.06,0.2,-0.06));
	_vertices.push_back(sf::Vector3f(2.25,0.2,-0.06));
	_vertices.push_back(sf::Vector3f(2.25,0.2,2.25));
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
	//_loadingScreen = &createActor(glm::vec3(1.5,1,-0.5f),_loadingTexture,_testModelLoadFour,0,999);
	//_loadingScreen->_transform.setScale(glm::vec3(1,1,1));
	//_loadingScreen->_transform.rotate(glm::vec3(0,-4,0));

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
		//_loadingScreen->_transform.rotate(glm::vec3(0,0.01f,0));
		break;

	case StateScene::OPENGLGENERATES:
		_testModelLoadTwo.generateMesh();
		_testModelLoadOne.generateMesh();
		_testModelLoadThree.generateMesh();

		testTexture.GenerateTexture();
		secondTexture.GenerateTexture();
		thirdTexture.GenerateTexture();
		metalTexture.GenerateTexture();
		brickTexture.GenerateTexture();
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
			/*glUseProgram(_shaderTexture.getProgramID());
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
			_loadingScreen->drawingInstance.getMesh().Draw();*/
		}
		break;
	case StateScene::SPLASHSCENE:
		{

		}
		break;

	case StateScene::RUNNING:
		{
			glUseProgram(_shaderTexture.getProgramID());
			for(auto factoryIter : _actorManager._activeFactories)
			{
				for(auto actorIter : factoryIter->_activeActors)
				{
					if(actorIter->drawingInstance.hasMesh())	//Does this drawing instance have a mesh?
					{
						if(actorIter->drawingInstance.hasTexture())	//Does this drawing instance have a texture?
						{
							glBindTexture(GL_TEXTURE_2D,actorIter->drawingInstance.getTexture().getTextureHandle());
						}
						Mesh& temp = actorIter->drawingInstance.getMesh();

						temp.getMatrix() = actorIter->_transform.getTransMatrix();

						glUniformMatrix4fv(_shaderTexture.getStoredUniform(ShaderTextureUniforms::PROJECTION),1, GL_FALSE, &_activeCamera->getProjectionMatrix()[0][0]);
						glUniformMatrix4fv(_shaderTexture.getStoredUniform(ShaderTextureUniforms::VIEW),1,	GL_FALSE, &_activeCamera->getViewMatrix()[0][0]);
						glUniformMatrix4fv(_shaderTexture.getStoredUniform(ShaderTextureUniforms::MODEL),1,	GL_FALSE, &temp.getMatrix()[0][0]);
						glUniform3f(_shaderTexture.getStoredUniform(ShaderTextureUniforms::LIGHTPOSITION),_lightPoint.x,_lightPoint.y,_lightPoint.z);
						actorIter->drawingInstance.getMesh().Draw();
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

void Scene::destroyBricks(sf::Vector2i pos, int x, int y, int length)
{
	//for(auto it : _activeObjects)
	//{
	//	if (it->isGridLocked() && it->getGridPos() == sf::Vector2i(pos.x + x, pos.y + y))
	//	{ 
	//		if(it->getActorType() == ActorTypes::DESTROYBLOCK){
	//			it->_collision.isActive = false;
	//			it->drawingInstance.setHasMesh(false);
	//		}
	//		if (length > 0 && it->getActorType() != ActorTypes::BLOCK)
	//		{
	//			destroyBricks(sf::Vector2i(pos.x+x, pos.y+y), x, y, length-1);
	//		}
	//	}
	//}
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
	glOrtho(0.0f, 4.0f, 4.0f, 0.0f, 0.0f, 1.0f);
}

Scene::~Scene()
{

}