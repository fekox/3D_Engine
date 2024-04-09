#pragma once
#include "Tools/Frame/Frame.h"
#include "Tools/Time.h"
#include "Tools/DLL-Exp/dll-Exp-Inp.h"
#include <iostream>
#include <vector>

using namespace frame;
using namespace std;

namespace animation
{
	class EXPORT Animation
	{
	private:
		float animationDuration;
		float currentTime;
		int currentFrame;
		vector<Frame>frames;

	public:

		Animation();

		void AddFrame(
			float xPosition, float yPosition,
			float frameWidth, float frameHeight,
			float spriteWidth, float spriteHeight,
			float durationTime);

		void AddFrame(
			float xPosition, float yPosition,
			float frameWidth, float frameHeight,
			float spriteWidth, float spriteHeight,
			float durationTime, int frameCount);

		void UpdateAnimation();

		int GetCurrentFrame();

		vector<Frame> GetFrames();
	};
}

