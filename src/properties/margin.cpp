#include "floah/properties/margin.h"

namespace floah
{
    ////////////////////////////////////////////////////////////////
    // Constructors.
    ////////////////////////////////////////////////////////////////

    Margin::Margin() = default;

    Margin::Margin(const Margin&) = default;

    Margin::Margin(Margin&&) noexcept = default;

    Margin::~Margin() noexcept = default;

    Margin& Margin::operator=(const Margin&) = default;

    Margin& Margin::operator=(Margin&&) noexcept = default;

    ////////////////////////////////////////////////////////////////
    // Getters.
    ////////////////////////////////////////////////////////////////

    Length& Margin::getLeft()  noexcept { return left; }

    const Length& Margin::getLeft() const noexcept { return left; }

    Length& Margin::getTop() noexcept { return top; }

    const Length& Margin::getTop() const noexcept { return top; }

    Length& Margin::getRight() noexcept { return right; }

    const Length& Margin::getRight() const noexcept { return right; }

    Length& Margin::getBottom() noexcept { return bottom; }

    const Length& Margin::getBottom() const noexcept { return bottom; }
}  // namespace floah
