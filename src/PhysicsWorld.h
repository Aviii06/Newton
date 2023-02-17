#pragma once
#include "common/Types.h"
#include "Object.h"
#include "TimeIntegrator.h"

namespace Newton
{
	class PhysicsWorld
	{
	private:
		TimeIntegrator* m_TimeIntegrator;
		Vector<Object*> m_Objects;
	public:
		PhysicsWorld();

		void AddObject(const Object& object);

		void Step(float deltaTime);
	};
}
