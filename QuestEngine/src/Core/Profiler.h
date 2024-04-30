#ifndef QUEST_CORE_PROFILER_H_INCLUDED
#define QUEST_CORE_PROFILER_H_INCLUDED

#define QE_ENABLE_PROFILING QUEST_DEBUG_MODE

#if QE_ENABLE_PROFILING
#include <tracy/Tracy.hpp>

/*
QE_PROFILE_FRAME goes at the end of the frame loop
QE_PROFILE_FUNC(name) or whatever you want to call it, goes at the top of a function you want profiled

*/
#define QE_PROFILE_FRAME		FrameMark
#define QE_PROFILE_FUNC(name)	ZoneScopedN(name)
#define QE_PROFILE_SCOPE		ZoneScoped

#else

#define QE_PROFILE_FRAME
#define QE_PROFILE_FUNC(name)
#define QE_PROFILE_SCOPE

#endif

#endif // QUEST_CORE_PROFILER_H_INCLUDED