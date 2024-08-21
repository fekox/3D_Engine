#pragma once

#include "Camera/Camera.h"
#include "Plane/Plane.h"

using namespace camera;

class OcclusionCulling
{
private:
	static Camera* camera;

public:
	OcclusionCulling();
	~OcclusionCulling();

	static void Init(Camera* camera);
	static void Update();

	static void SetCamera(Camera* camera);

	static Plane up;
	static Plane down;
	static Plane left;
	static Plane right;
	static Plane front;
	static Plane back;

};