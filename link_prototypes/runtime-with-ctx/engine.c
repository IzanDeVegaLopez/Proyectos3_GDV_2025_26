#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <windows.h>

#include "engine.h"

static uint32_t engine_value = 42;
void engine_foo(void) {
    printf("Hello from engine! With value: %u\n", engine_value);
}

int main(void) {
    const HMODULE game_plugin = LoadLibraryA("game_plugin");
    if (game_plugin == NULL) {
        fprintf(stderr, "Failed to load game_plugin.dll\n");
        exit(EXIT_FAILURE);
    }


    const engine_context ctx = { .foo = engine_foo };
    
    typedef void game_plugin_foo_func(const engine_context ctx);
    typedef void game_plugin_callback_func(void);
    game_plugin_foo_func *const game_plugin_foo =
        (game_plugin_foo_func *const)(void *)GetProcAddress(game_plugin, "game_plugin_foo");
    if (game_plugin_foo == NULL) {
        fprintf(stderr, "Failed to get game_plugin_foo address\n");
        exit(EXIT_FAILURE);
    }
    game_plugin_callback_func *const game_plugin_callback =
        (game_plugin_callback_func *const)GetProcAddress(game_plugin, "game_plugin_callback");
    if (game_plugin_callback == NULL) {
        fprintf(stderr, "Failed to get game_plugin_callback address\n");
        exit(EXIT_FAILURE);
    }


    game_plugin_foo(ctx);
    engine_value = 67;
    game_plugin_callback();
    

    const BOOL freed = FreeLibrary(game_plugin);
    if (!freed) {
        fprintf(stderr, "Failed to free game_plugin.dll\n");
        exit(EXIT_FAILURE);
    }
    return 0;
}
