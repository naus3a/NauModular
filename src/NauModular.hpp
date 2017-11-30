#include "rack.hpp"

#if (defined(__APPLE__) && defined(__MACH__))
#define TARGET_OSX    
#elif (defined(unix) || defined(__unix__) || defined(__unix))
#define TARGET_LINUX
#elif (defined(__WINDOWS__) || defined(__WIN32__) || defined(_WIN32) || defined(_WIN64))
#define TARGET_WINDOWS
#else
#define TARGET_UNKNOWN
#endif

#include <time.h>

#if defined(TARGET_OSX)
#include <mach/clock.h>
#include <mach/mach.h>
#include <mach/mach_time.h>
#include <mach/clock_types.h>
#endif

using namespace rack;

extern Plugin * plugin;

namespace NauModular{
#ifdef TARGET_OSX
   static clock_serv_t cs;
#endif
    static void init();
    float getTimef();
    static void getMonotonicTime(uint64_t & seconds, uint64_t & nanos);
};

struct TensionWidget : ModuleWidget{
	TensionWidget();
};

struct FunctionWidget : ModuleWidget{
	FunctionWidget();
};

struct PerlinWidget : ModuleWidget{
	PerlinWidget();
};
