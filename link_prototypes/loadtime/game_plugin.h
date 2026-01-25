#ifndef GAME_PLUGIN_H
#define GAME_PLUGIN_H

#include "engine.h"

#ifndef PLUGIN_PORT

#ifdef PLUGIN_EXPORT
#undef PLUGIN_IMPORT
#define PLUGIN_IMPORT (!PLUGIN_EXPORT)
#elif defined(PLUGIN_IMPORT)
#undef PLUGIN_EXPORT
#define PLUGIN_EXPORT (!PLUGIN_IMPORT)
#else
#define PLUGIN_EXPORT_DEFAULT true
#define PLUGIN_EXPORT PLUGIN_EXPORT_DEFAULT
#define PLUGIN_IMPORT (!PLUGIN_EXPORT)
#endif

static_assert(PLUGIN_EXPORT || PLUGIN_IMPORT, "Either PLUGIN_EXPORT or PLUGIN_IMPORT must be true");
static_assert(PLUGIN_EXPORT != PLUGIN_IMPORT, "PLUGIN_EXPORT and PLUGIN_IMPORT cannot both be true or both be false");

#if PLUGIN_EXPORT
#define PLUGIN_PORT __declspec(dllexport)
#elif PLUGIN_IMPORT
#define PLUGIN_PORT __declspec(dllimport)
#else
static_assert(false, "Either PLUGIN_EXPORT or PLUGIN_IMPORT must be true");
#endif

#endif


PLUGIN_PORT void game_plugin_foo(const engine_context ctx);
PLUGIN_PORT void game_plugin_callback(void);

#endif
