#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <windows.h>

// game_plugin.h here could be a header belonging to the engine
// the header imposes an interface that plugins must implement
#include "game_plugin.h"
#include "engine.h"

static uint32_t engine_value = 42;
void engine_foo(void) {
    printf("Hello from engine! With value: %u\n", engine_value);
}

// Pedro Pablo Gómez Martín does not like this one simple trick (this way of linking)
int engine_main(void) {
    game_plugin_foo();
    engine_value = 67;
    game_plugin_callback();
    return 0;
}
