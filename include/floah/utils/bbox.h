#pragma once

////////////////////////////////////////////////////////////////
// Standard includes.
////////////////////////////////////////////////////////////////

#include <cstdint>
#include <limits>

namespace floah
{
    struct BBox
    {
        int32_t x0 = std::numeric_limits<int32_t>::max();
        int32_t y0 = std::numeric_limits<int32_t>::max();
        int32_t x1 = std::numeric_limits<int32_t>::min();
        int32_t y1 = std::numeric_limits<int32_t>::min();

        [[nodiscard]] int32_t width() const noexcept;

        [[nodiscard]] int32_t height() const noexcept;

        BBox& operator+=(const BBox& rhs) noexcept;
    };
}  // namespace floah
