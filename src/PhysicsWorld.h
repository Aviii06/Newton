#pragma once
#include "common/Types.h"
#include "Object.h"

namespace Newton
{
	class PhysicsWorld
	{
	private:
		Vector<Object> m_Objects;
	public:
		PhysicsWorld();

		void AddObject(const Object& object);

		void Step(float deltaTime);
	};
}
