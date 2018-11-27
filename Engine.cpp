//Essential includes
#include "stdafx.h"
#include "Engine.h"

//System includes
#include <chrono>

//OpenGL includes
//#include <GLFW\glfw3.h>

//Local includes
#include "Input.h"
#include "Update.h"
#include "Render.h"
#include "Collision.h"
#include "ShaderHandler.h"
#include "GLTypes.h"
#include "DefaultShaders.h"
#include "EventHandler.h"
#include "StageHandler.h"
#include "Scheduler.h"

#ifdef __APPLE__

#import <Foundation/Foundation.h>

#endif

//Definitions
#ifndef MS_PER_UPDATE
    #define MS_PER_UPDATE 10
#endif // !MS_PER_UPDATE

namespace Xylena {

	//Static variable initialisation
	GamePtr Engine::game = nullptr;

	//Indicates whether the main loop should run next update - used for closing the game
	bool keepRunning;

	Engine::Engine() {}

	Engine::~Engine() {}

	//Contains the main game loop. Called by the game that is passed in through initialize()
	void Engine::run() {
        
        /*Scheduler::start();
        
        Scheduler::enqueueMain(block({
            mainLoop();
        }));*/
        
        mainLoop();
    }
    
    void Engine::mainLoop() {

        //Profiler::start()

		//Convenience for code getting current time
		using namespace std::chrono;

		//Keeps track of tick lag
        time_t tickPrevious = Profiler::getCurrentTime();
		//time_t previousTime = duration_cast<milliseconds> (steady_clock::now().time_since_epoch()).count();
		double timeLag = 0.0;

        //FPS tracker
        time_t nextFPStime = duration_cast<milliseconds> (steady_clock::now().time_since_epoch()).count() + 1000;
        int frames = 0;
        int updates = 0;
        int fps = 0;
        int ups = 0;

        int renderms = 0;
        int bufferms = 0;

		//Main loop
		while (!keepRunning) {

            Profiler::start("updates");

            Profiler::start("timecalc");

			//Calculates tick lag
            time_t currentTime = Profiler::getCurrentTime();
            time_t elapsedTime = currentTime - tickPrevious;
            tickPrevious = currentTime;
			timeLag += elapsedTime;

            time_t timeTime = Profiler::stop("timecalc");

            Profiler::start("input");

			//Process game input
			Input::processInput();
            
            //Process game events
            EventHandler::processEvents();

            time_t inputTime = Profiler::stop("input");

            //printf("Input time: %03ims\n", Profiler::stop("input"));

            Profiler::start("delag");

			//De-lag loop for game updates
			while (timeLag >= MS_PER_UPDATE) {
				Update::update();
				timeLag -= MS_PER_UPDATE;
                updates++;
			}

            time_t delagTime = Profiler::stop("delag");

            time_t updateTime = Profiler::stop("updates");

            Profiler::start("renderms");
            time_t renderTimeStart = duration_cast<milliseconds> (steady_clock::now().time_since_epoch()).count();
            
            //Calculate collision
            Collision::calculateCollisions();
            
            //Clean up stages post-update and collisions
            StageHandler::clean();

			//Render game objects
			Render::render(timeLag / MS_PER_UPDATE);
            
            
            time_t renderTime = Profiler::stop("renderms");
            //time_t renderTime = renderTimeStart - duration_cast<milliseconds> (steady_clock::now().time_since_epoch()).count();
            //time_t renderTime = 50;
            //time_t updateTime = 20;
            time_t bufferTime = Profiler::stop("bufferswap");

            //printf("Buffer swap time: %02I64dms Render time: %02I64dms Update time: %02I64dms\n", bufferTime, renderTime, updateTime);
            //printf("Buffer swap time: %02ims Render time: %02ims Update time: %02ims Input time: %02ims Delag time: %02ims Timecalc time: %02ims\n", bufferTime, renderTime, updateTime, inputTime, updateTime, timeTime);
            //time_t bufferTime = Profiler::stop("bufferswap");

            

            //FPS calculation
            currentTime = Profiler::getCurrentTime();
            if (currentTime > nextFPStime) {
                nextFPStime = currentTime + 1000;
                fps = frames;
                ups = updates;

                frames = 0;
                updates = 0;

                //int avgRenderMs = renderms / fps;
                //int avgBufferMs = bufferms / fps;

                //printf("Average Render Time: %i. Average Buffer Wait: %i. FPS:%i\n", avgRenderMs, avgRenderMs, fps);

                renderms = 0;
                bufferms = 0;

                printf("FPS: %i\n", fps);
                //printf("UPS: %i\n", ups);
            } else {
                frames++;
                renderms += renderTime;
                //bufferms += bufferTime;

            }

			glfwPollEvents();

		}

		game->onStop();
	}

	void Engine::stop() {
		keepRunning = false;
	}

	void Engine::initialize(GamePtr _game) {
        
#ifdef __APPLE__

        NSString *resourcePath = [[NSBundle mainBundle] resourcePath];
        [[NSFileManager defaultManager] changeCurrentDirectoryPath:resourcePath];
        
#endif

        Scheduler::setMaxWorkers(Scheduler::hardwareThreads());
        Scheduler::initialize();
        
        Render::initRenderer();

		game = _game;
		game->initialize();
		
        //Init the built in simple shaders
        ShaderHandler::compileProgram("simple", defaultSimpleVert, defaultSimpleFrag);

	}
}