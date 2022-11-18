#pragma once

#include "PlacableActor.h"

class Goal : public PlacableActor {

public:
	Goal(int x, int y);

	virtual void Draw() override;

};
