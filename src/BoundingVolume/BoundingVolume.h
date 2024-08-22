#pragma once

#include <GLFW/glfw3.h>
#include "..\libs\glm\include\glm.hpp"
#include "..\libs\glm\include\gtc\matrix_transform.hpp"
#include "..\libs\glm\include\gtc\type_ptr.hpp"

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

