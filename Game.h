#pragma once

//System includes
#include <memory>

namespace Xylena {

	class Game {
	public:
		virtual void initialize() = 0;
		virtual void onStop() = 0;
	};

	//Typedef
	typedef std::shared_ptr<Game> GamePtr;

}