#include "floah-layout/properties/length.h"

////////////////////////////////////////////////////////////////
// Standard includes.
////////////////////////////////////////////////////////////////

#include <cmath>

namespace floah
{
    ////////////////////////////////////////////////////////////////
    // Constructors.
    ////////////////////////////////////////////////////////////////

    Length::Length() = default;

    Length::Length(const int32_t v) : absLength(v) {}

    Length::Length(const float v) : relative(true), relLength(v) {}

    Length::Length(const Length&) = default;

    Length::Length(Length&&) noexcept = default;

    Length::~Length() noexcept = default;

    Length& Length::operator=(const Length&) = default;

    Length& Length::operator=(Length&&) noexcept = default;

    ////////////////////////////////////////////////////////////////
    // Getters.
    ////////////////////////////////////////////////////////////////

    int32_t Length::get() const noexcept { return absLength; }

    float Length::getRelative() const noexcept { return relLength; }

    int32_t Length::get(const int32_t base) const noexcept
    {
        return isRelative() ? static_cast<int32_t>(std::round(relLength * static_cast<float>(base))) : absLength;
    }

    bool Length::isAbsolute() const noexcept { return !relative; }

    bool Length::isRelative() const noexcept { return relative; }

    ////////////////////////////////////////////////////////////////
    // Setters.
    ////////////////////////////////////////////////////////////////

    void Length::set(const int32_t v) noexcept
    {
        absLength = v;
        relative  = false;
    }

    void Length::setRelative(const float v) noexcept
    {
        relLength = v;
        relative  = true;
    }

    void Length::makeAbsolute() noexcept { relative = false; }

    void Length::makeRelative() noexcept { relative = true; }
}  // namespace floah
