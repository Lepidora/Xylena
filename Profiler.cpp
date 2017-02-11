#include "stdafx.h"
#include "Profiler.h"

//System includes
#include <chrono>

namespace Xylena {

    std::map<std::string, time_t> Profiler::profiles;



    time_t Profiler::getCurrentTime() {
        
        using namespace std::chrono;
        return duration_cast<milliseconds> (steady_clock::now().time_since_epoch()).count();
    }

    void Profiler::start(std::string id) {
        
        time_t currentTime = getCurrentTime();

        profiles.insert(std::pair<std::string, time_t>(id, currentTime));
    }

    time_t Profiler::profile(std::string id) {

        time_t currentTime = getCurrentTime();

        auto iterator = profiles.find(id);

        if (iterator != profiles.end()) {
            time_t originalTime = iterator->second;

            return currentTime - originalTime;
        } else {
            return 0;
        }
    }

    time_t Profiler::stop(std::string id) {

        time_t currentTime = getCurrentTime();

        auto iterator = profiles.find(id);

        if (iterator != profiles.end()) {
            
            time_t originalTime = iterator->second;
            time_t difference = currentTime - originalTime;

            profiles.erase(iterator);

            return difference;
        } else {
            return 0;
        }
    }

    void Profiler::set(std::string id, time_t time) {

        auto iterator = profiles.find(id);

        if (iterator != profiles.end()) {
            iterator->second = time;
        }
    }

    void Profiler::reset(std::string id) {

        time_t currentTime = getCurrentTime();

        auto iterator = profiles.find(id);

        if (iterator != profiles.end()) {
            iterator->second = currentTime;
        }

    }

}
