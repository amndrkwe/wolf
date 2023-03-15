#pragma once

#include <SDL2/SDL.h>
#include <stdint.h>
#include <stdbool.h>
#include <float.h>
#include <limits.h>

#define ASSERT(_e, ...) if (!(_e)) { fprintf(stderr, __VA_ARGS__); exit(1); }

// typedefs
typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef uint32_t uint;

typedef int8_t   i8;
typedef int16_t  i16;
typedef int32_t  i32;
typedef int64_t  i64;

typedef float    f32;
typedef double   f64;

typedef size_t   usize;

static uint64_t _cull_seed = 0;

// seed random_get()
static inline void random_seed(i64 seed)
{
    _cull_seed = seed;
}

// return random unsigned long long (u64)
static inline i64 random_get()
{
    _cull_seed ^= _cull_seed << 12;
    _cull_seed ^= _cull_seed >> 25;
    _cull_seed ^= _cull_seed << 27;

    return _cull_seed * 2685821657736338717;
}