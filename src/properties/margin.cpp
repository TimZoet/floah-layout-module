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

    ////////////////////////////////////////////////////////////////
    // Setters.
    ////////////////////////////////////////////////////////////////

    void Margin::set(const int32_t l, const int32_t t, const int32_t r, const int32_t b) noexcept
    {
        left.set(l);
        top.set(t);
        right.set(r);
        bottom.set(b);
    }
}  // namespace floah
