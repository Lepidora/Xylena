#pragma once

//System includes
#include <map>
#include <string>

namespace Xylena {

    class Profiler {
    private:
        static std::map<std::string, time_t> profiles;
    public:
        Profiler() {};
        ~Profiler() {};
        
        static time_t getCurrentTime();

        static void start(std::string id);
        static time_t profile(std::string id);
        static time_t stop(std::string id);

        static void set(std::string id, time_t time);
        static void reset(std::string id);
    };
}
