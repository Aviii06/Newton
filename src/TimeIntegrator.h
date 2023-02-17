#pragma once

namespace Newton
{
	class TimeIntegrator
	{
	public:
		virtual void step(float deltaTime) = 0;
	};
}