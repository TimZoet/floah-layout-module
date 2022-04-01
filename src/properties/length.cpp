#include "floah/properties/length.h"

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

    bool Length::isAbsolute() const noexcept { return !relative; }

    bool Length::isRelative() const noexcept { return relative; }

    ////////////////////////////////////////////////////////////////
    // Setters.
    ////////////////////////////////////////////////////////////////

    void Length::set(const int32_t v) { absLength = v; }

    void Length::setRelative(const float v) { relLength = v; }

    void Length::makeAbsolute() { relative = false; }

    void Length::makeRelative() { relative = true; }
}  // namespace floah
