#pragma once
#include "Point.h"

constexpr int kGreenColor = 10;
constexpr int kGreenColorSolid = 34;
constexpr int kRedColor = 12;
constexpr int kRedColorSolid = 68;
constexpr int kBlueColor = 9;
constexpr int kBlueColorSolid = 153;
constexpr int kRegularColor = 7;

class PlacableActor {

public:
	PlacableActor(int x, int y, int color = kRegularColor);
	virtual ~PlacableActor();

	int GetXPosition();
	int GetYPosition();
	int* GetXPositionPointer();
	int* GetYPositionPointer();
	void SetPosition(int x, int y);

	int GetColor() { return m_color; }

	void Remove() { m_IsActive = false; }
	bool IsActive() { return m_IsActive; }
	void Place(int x, int y);

	virtual void Draw() = 0;
	virtual void Update() {

	}


protected:
	Point *m_pPosition;

	bool m_IsActive;
	int m_color;
};
