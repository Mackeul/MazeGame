#pragma once
#include "PlacableActor.h"

class Key : public PlacableActor {
public:
	Key(int x, int y, int color)
		: PlacableActor(x, y, color)
	{

	}

	virtual void Draw() override;
};