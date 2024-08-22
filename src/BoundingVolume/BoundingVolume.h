#pragma once

#include "Frustum/Frustum.h"
#include "Transform/Transform.h"
#include "Plane/Plane.h"

class BoundingVolume
{
	public:

		BoundingVolume();
		~BoundingVolume();

		virtual bool IsOnFrustum(const Frustum& camFrustum, const Transform& transform) const = 0;

		virtual bool IsOnOrForwardPlane(const Plane& plane) const = 0;

		bool IsOnFrustum(const Frustum& camFrustum) const;
};

