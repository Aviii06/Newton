#include "PhysicsWorld.h"
#define MAX_OBJECTS 1000

namespace Newton
{
	PhysicsWorld::PhysicsWorld()
	{
		m_Objects.reserve(MAX_OBJECTS);
	}
	void PhysicsWorld::Step(float deltaTime)
	{
		for (auto&& object : m_Objects)
		{
			auto massInverse = object->getInvInertia().asDiagonal();
			object->getVelocities() += timeStep * (massInverse * object->getForces());
		}
	}
}
