#pragma once
#include "glm.hpp"
#include "TraderConfig.h"
#include "BaseTrader.h"

class TraderManager
{
public:
	TraderManager();
	~TraderManager();

	void CreateTrader(TraderConfig config, glm::vec2 position);

private:

};

