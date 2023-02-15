#pragma once
#include "common/Types.h"

namespace Newton
{
	class Object
	{
	private:
		Vec3 m_Position;
	public:
		Object();
		~Object();

		virtual Vec3 GetPosition() = 0;
	};
}