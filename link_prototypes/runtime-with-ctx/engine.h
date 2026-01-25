#ifndef ENGINE_H
#define ENGINE_H

#include <stdbool.h>
#include <assert.h>

#ifdef ENGINE_EXPORT
#undef ENGINE_IMPORT
#define ENGINE_IMPORT (!ENGINE_EXPORT)
#elif defined(ENGINE_IMPORT)
#undef ENGINE_EXPORT
#define ENGINE_EXPORT (!ENGINE_IMPORT)
#else
#define ENGINE_EXPORT_DEFAULT true
#define ENGINE_EXPORT ENGINE_EXPORT_DEFAULT
#define ENGINE_IMPORT (!ENGINE_EXPORT)
#endif

static_assert(ENGINE_EXPORT || ENGINE_IMPORT, "Either ENGINE_EXPORT or ENGINE_IMPORT must be true");
static_assert(ENGINE_EXPORT != ENGINE_IMPORT, "ENGINE_EXPORT and ENGINE_IMPORT cannot both be true or both be false");


#if ENGINE_EXPORT
void engine_foo(void);
// [...] Rest of engine API declarations for export can go here
#endif

typedef void engine_foo_func(void);
typedef struct engine_context {
    engine_foo_func *foo;
} engine_context;

#endif
