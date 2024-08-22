#pragma once

#include "Plane/Plane.h"

class Frustum
{
	public:

	Plane topFace;
	Plane bottomFace;

	Plane rightFace;
	Plane leftFace;

	Plane farFace;
	Plane nearFace;

		Frustum();
		~Frustum();
};