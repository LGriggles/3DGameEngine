#include "DestroyableBlock.hpp"
#include "stdafx.h"
#include "DestroyableBlock.hpp"
#include "InputHandler.hpp"
#include "CollisionEngine.hpp"
#include "Scene.hpp"

DestroyabeBlock::DestroyabeBlock(void)
{
}

DestroyabeBlock::~DestroyabeBlock(void)
{
}

void DestroyabeBlock::init()
{
}

void DestroyabeBlock::update()
{
	switch(_blockState)
	{
	case BlockState::NORMAL:

		break;

	case BlockState::DESTROYING:
		_transform.setScale(Transform::lerp(glm::vec3(3,3,3),_transform._scale,0.39f));
		if(_transform._scale.x > 2.9 && _transform._scale.y > 2.9 && _transform._scale.z > 2.9)
		{
			if(_transform._scale.x < 3.1 && _transform._scale.y < 3.1 && _transform._scale.z < 3.1)
			{
				_blockState = BlockState::DESTROYED;
			}
		}
		break;

	case BlockState::DESTROYED:
		destroyMe();
		break;
	}
}

void DestroyabeBlock::destroyed()
{

}