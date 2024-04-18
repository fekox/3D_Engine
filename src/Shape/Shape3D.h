#pragma once
#include "Tools/DLL-Exp/dll-Exp-Inp.h"
#include <GL/glew.h>
#include "Entity/Entity3D.h"

using namespace entity3D;

namespace shape3D
{
	class EXPORT Shape3D final : public Entity3D
	{
		private:

		public:
		Material* material;

		enum Shapes3D
		{
			Cube,
			Pyramid
		};

		Shape3D(Shapes3D typeShapes, Material* material, Renderer* render, Vector3 newPosition, Vector3 newScale, Vector3 newRotation);
		~Shape3D();

		void CreateCube();
		void CreatePyramid();
		void Draw();
	};
}
