#include <stdio.h>
#include "game_plugin.h"
#include "engine.h"

void game_plugin_foo(void) {
    printf("Hello from game plugin!\n");
}

void game_plugin_callback(void) {
    printf("Game plugin callback invoking engine:\n");
    engine_foo();
}

int main(void) {
    return engine_main();
}
