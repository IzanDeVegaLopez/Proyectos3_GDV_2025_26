#ifndef ENGINE_H
#define ENGINE_H

#include <stdbool.h>
#include <assert.h>

#ifndef ENGINE_PORT

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
#define ENGINE_PORT __declspec(dllexport)
#elif ENGINE_IMPORT
#define ENGINE_PORT __declspec(dllimport)
#else
static_assert(false, "Either ENGINE_EXPORT or ENGINE_IMPORT must be true");
#endif

#endif


ENGINE_PORT void engine_foo(void);
#endif
