#include "BSP.h"

std::vector<Plane> BSP::bspPlanes;

void BSP::AddPlaneToBSP(glm::vec3 point, glm::vec3 normal)
{
	Plane plane = { point,normal };
	bspPlanes.push_back(plane);
}