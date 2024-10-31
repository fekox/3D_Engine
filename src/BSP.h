#pragma once
#include "Tools/DLL-Exp/dll-Exp-Inp.h"
#include <Plane/Plane.h>
#include <vector>

using namespace std;

static class EXPORT BSP
{
public:

	static vector<Plane> bspPlanes;

	static void AddPlaneToBSP(glm::vec3 point, glm::vec3 normal);
};

