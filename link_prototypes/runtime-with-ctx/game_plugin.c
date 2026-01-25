#include <stdio.h>
#include "game_plugin.h"
#include "engine.h"

static engine_context engine_ctx = {0};

void game_plugin_foo(const engine_context ctx) {
    printf("Hello from game plugin! THIS WORKS AS INITIALISATION\n");
    engine_ctx = ctx;
}

void game_plugin_callback(void) {
    printf("Game plugin callback invoking engine:\n");
    engine_ctx.foo();
}
