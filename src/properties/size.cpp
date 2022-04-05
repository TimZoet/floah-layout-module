#include "floah-layout/properties/size.h"

#include <utility>

namespace floah
{
    ////////////////////////////////////////////////////////////////
    // Constructors.
    ////////////////////////////////////////////////////////////////

    Size::Size() = default;

    Size::Size(Length w, Length h) : width(std::move(w)), height(std::move(h)) {}

    Size::Size(const Size&) = default;

    Size::Size(Size&&) noexcept = default;

    Size::~Size() noexcept = default;

    Size& Size::operator=(const Size&) = default;

    Size& Size::operator=(Size&&) noexcept = default;

    ////////////////////////////////////////////////////////////////
    // Getters.
    ////////////////////////////////////////////////////////////////

    Length& Size::getWidth() noexcept { return width; }

    const Length& Size::getWidth() const noexcept { return width; }

    Length& Size::getHeight() noexcept { return height; }

    const Length& Size::getHeight() const noexcept { return height; }

    ////////////////////////////////////////////////////////////////
    // Setters.
    ////////////////////////////////////////////////////////////////

    void Size::setWidth(Length v) { width = std::move(v); }

    void Size::setHeight(Length v) { height = std::move(v); }

}  // namespace floah
