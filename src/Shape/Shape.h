#pragma once
#include "Tools/DLL-Exp/dll-Exp-Inp.h"
#include <GL/glew.h>
#include "Entity/Entity2D.h"

using namespace Entity2D;

namespace shape
{
	class EXPORT Shape final : public Entity2D
	{
	private:

	public:

		enum Shapes2D
		{
			Triangle,
			Square,
		};

		Shape(Shapes2D typeShapes, Vector4 rgba, Renderer* render, Vector3 newPosition, Vector3 newScale, Vector3 newRotation);
		~Shape();
		void createTriangle();
		void createRectangle();
		void Draw();
	};
}