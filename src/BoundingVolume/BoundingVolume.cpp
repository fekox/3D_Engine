#include "BoundingVolume.h"

BoundingVolume::BoundingVolume()
{
}

BoundingVolume::~BoundingVolume()
{
}

bool BoundingVolume::IsOnFrustum(Frustum camFrustum)
{
	return (IsOnOrForwardPlane(camFrustum.leftFace) &&
			IsOnOrForwardPlane(camFrustum.rightFace) &&
			IsOnOrForwardPlane(camFrustum.topFace) &&
			IsOnOrForwardPlane(camFrustum.bottomFace) &&
			IsOnOrForwardPlane(camFrustum.nearFace) &&
			IsOnOrForwardPlane(camFrustum.farFace));
}
