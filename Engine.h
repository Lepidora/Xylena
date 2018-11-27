#pragma once

#include "Game.h"

namespace Xylena {

	class Engine {
	private:
		static GamePtr game;
        
        static void mainLoop();
        
	public:
		Engine();
		~Engine();

		static void run();
		static void stop();

		static void initialize(GamePtr game);

	};
}