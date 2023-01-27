#pragma once
#include "common/Types.h"

class UI
{
private:
	static void(*m_OnUpdate)();
public:
	UI() = default;
	UI* Init();
	void Update();
	//TODO: Implement events
//	virtual void OnEvent(Event& event) = 0;
};
