#pragma once

#include <SFML/Config.hpp>
#include <cstdint>

#define CACTO_MAJOR_VERSION 0
#define CACTO_MINOR_VERSION 1
#define CACTO_PATCH_VERSION 0

#define CACTO_API_EXPORT SFML_API_EXPORT
#define CACTO_API_IMPORT SFML_API_IMPORT

#define nameof(symbol) #symbol
#define M_PI 3.14159265358979323846

namespace cacto
{

    using i8t = std::int8_t;
    using i16t = std::int16_t;
    using i32t = std::int32_t;
    using i64t = std::int64_t;

    using u8t = std::uint8_t;
    using u16t = std::uint16_t;
    using u32t = std::uint32_t;
    using u64t = std::uint64_t;

    using f32t = float;
    using f64t = double;
    using f128t = long double;

    using c8t = char;
    using c16t = char16_t;
    using c32t = char32_t;

    using s8t = const char *;
    using s16t = const char16_t *;
    using s32t = const char32_t *;

    using szt = std::size_t;

}