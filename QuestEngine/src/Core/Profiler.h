#pragma once

#define QE_ENABLE_PROFILING QE_DEBUG_MODE

#if QE_ENABLE_PROFILING
#include "ThirdParty/Tracy.h"

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
