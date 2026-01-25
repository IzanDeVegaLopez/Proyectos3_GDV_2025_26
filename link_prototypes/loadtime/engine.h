#ifndef ENGINE_H
#define ENGINE_H

#include <stdbool.h>
#include <assert.h>

#include "game_plugin.h"

#if PLUGIN_IMPORT
void engine_foo(void);
#endif

typedef void engine_foo_func(void);

typedef struct engine_context {
    engine_foo_func* foo;
} engine_context;

#endif
