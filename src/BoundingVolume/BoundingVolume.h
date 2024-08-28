#pragma once

#include "Frustum/Frustum.h"
#include "Transform/Transform.h"
#include "Plane/Plane.h"

class BoundingVolume
{
	public:

		BoundingVolume();
		~BoundingVolume();

		virtual bool IsOnFrustum(Frustum camFrustum, Transform transform) = 0;

		virtual bool IsOnOrForwardPlane(Plane plane) = 0;

		bool IsOnFrustum(Frustum camFrustum);
};

