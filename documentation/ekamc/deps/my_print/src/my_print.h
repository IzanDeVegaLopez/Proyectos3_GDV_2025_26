#ifndef MY_PRINT_H
#define MY_PRINT_H

#include <assert.h>
#include <stdbool.h>

#ifndef MY_PRINT_API
#ifdef _WIN32

#ifdef MY_PRINT_EXPORT
#undef MY_PRINT_IMPORT
#define MY_PRINT_IMPORT !(MY_PRINT_EXPORT)

#elif defined(MY_PRINT_IMPORT)
#undef MY_PRINT_EXPORT
#define MY_PRINT_EXPORT !(MY_PRINT_IMPORT)

#else
#define MY_PRINT_EXPORT_DEFAULT true
#define MY_PRINT_EXPORT MY_PRINT_EXPORT_DEFAULT
#define MY_PRINT_IMPORT !(MY_PRINT_EXPORT_DEFAULT)

#endif

static_assert(MY_PRINT_EXPORT || MY_PRINT_IMPORT, "Either MY_PRINT_EXPORT or MY_PRINT_IMPORT must be defined");
static_assert(!(MY_PRINT_EXPORT && MY_PRINT_IMPORT), "MY_PRINT_EXPORT and MY_PRINT_IMPORT cannot both be defined");

#if MY_PRINT_EXPORT
#define MY_PRINT_API __declspec(dllexport)
#elif MY_PRINT_IMPORT
#define MY_PRINT_API __declspec(dllimport)
#else
static_assert(false, "Invalid configuration for MY_PRINT_EXPORT and MY_PRINT_IMPORT");
#endif


#else 
#define MY_PRINT_API 

#endif
#endif

MY_PRINT_API void my_print(const char *const message);

#endif
