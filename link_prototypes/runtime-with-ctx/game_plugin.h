#ifndef GAME_PLUGIN_H
#define GAME_PLUGIN_H

#include "engine.h"

__declspec(dllexport) void game_plugin_foo(const engine_context ctx);
__declspec(dllexport) void game_plugin_callback(void);

#endif
