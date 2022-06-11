#pragma once


#include <cassert>

#ifndef NDEBUG
#define assertMessage(exp, msg) assert((exp && msg))
#else
#define assertMessage(exp, msg)
#endif
