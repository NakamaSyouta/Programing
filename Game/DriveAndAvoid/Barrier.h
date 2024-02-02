#pragma once

#include"Vector2D.h"

class Barrier
{
private:
	int imager;
	float life_span;

public:
	Barrier();
	~Barrier();

	void Draw(const Vector2D& location);
	bool lsFinished(float speed);
};