#ifndef ACTORMANAGER_HPP
#define ACTORMANAGER_HPP

#include "Actor.hpp"
#include <vector>
using std::vector;

class ActorFactory
{
public:
	vector<Actor*>	_instantiatedActors;	// Actors existing in memory
	vector<Actor*>	_activeActors;			// Actors that are currently running their logic
	vector<Actor*>	_deletionList;			// Delete these from active next frame
	vector<Actor*>	_creationList;			//create an actor on the scene

	ActorFactory()
	{

	}

	template<class T_ACTORTYPE>
	void instantiateMemory(int actorID,Texture& texture, Mesh& mesh)
	{
		int repeat = 1000;
		while(repeat>0)
		{
			T_ACTORTYPE* instActor = new T_ACTORTYPE;
			Actor* newActor = (Actor*)instActor;
			_instantiatedActors.push_back(newActor);

			
			newActor->_actorID = actorID;
			newActor->setGridLocked(false);
			newActor->setGridPos(sf::Vector2i(0,0));
			newActor->drawingInstance.giveTexture(texture);
			newActor->init();
			newActor->drawingInstance.giveMesh(mesh);

			repeat --;
		}
	}

	void init()
	{

	}

	void update()
	{
		for(Actor* iter : _activeActors)
		{
			iter->update();
			if(iter->_destroyed)
			{
				_deletionList.push_back(iter);
			}
		}
		deletionListUpdate();
	}

	Actor* createActor()
	{
		if(_instantiatedActors.size() == 0)
		{
			int i = 0;
		}
		Actor* newActor = _instantiatedActors.at(0);
		_instantiatedActors.erase(_instantiatedActors.begin());
		newActor->_destroyed = false;
		_activeActors.push_back(newActor);
		return newActor;
	}

	void deletionListUpdate()
	{
		while(_creationList.size() > 0)
		{
			Actor* newActor = _creationList.at(0);
			_activeActors.push_back(newActor);
			_creationList.erase(_creationList.begin());
		}

		for(Actor* iter : _deletionList)
		{
			for(int i = 0; i < _activeActors.size(); i++)
			{
				if(_activeActors.at(i) == iter)
				{
					_activeActors.erase(_activeActors.begin() + i);
				}
			}
		}
		_deletionList.clear();
	}
};

class ActorManager
{
public:
	ActorFactory* _actorFactories[100];
	vector<ActorFactory*> _activeFactories;

	ActorManager()
	{
		int i =0;

	}

	template <class T_ACTORTYPE>
	void instantiateFactory(int actorID,Texture& texture, Mesh& mesh)
	{
		_actorFactories[actorID] = new ActorFactory();
		_actorFactories[actorID]->instantiateMemory<T_ACTORTYPE>(actorID,texture,mesh);
		_activeFactories.push_back(_actorFactories[actorID]);
	}

	void update()
	{
		for(auto iter : _activeFactories)
		{
			iter->update();
		}
	}


	Actor* createActor(int _actorID)
	{
		Actor* newActor = _actorFactories[_actorID]->createActor();

		return newActor;
	}

};


#endif