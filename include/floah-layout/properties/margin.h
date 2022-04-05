#pragma once

////////////////////////////////////////////////////////////////
// Current target includes.
////////////////////////////////////////////////////////////////

#include "floah-layout/properties/length.h"

namespace floah
{
    class Margin
    {
    public:
        ////////////////////////////////////////////////////////////////
        // Constructors.
        ////////////////////////////////////////////////////////////////

        Margin();

        Margin(const Margin&);

        Margin(Margin&&) noexcept;

        ~Margin() noexcept;

        Margin& operator=(const Margin&);

        Margin& operator=(Margin&&) noexcept;

        ////////////////////////////////////////////////////////////////
        // Getters.
        ////////////////////////////////////////////////////////////////

        /**
         * \brief Get left margin.
         * \return Left margin.
         */
        [[nodiscard]] Length& getLeft() noexcept;

        /**
         * \brief Get left margin.
         * \return Left margin.
         */
        [[nodiscard]] const Length& getLeft() const noexcept;

        /**
         * \brief Get top margin.
         * \return Top margin.
         */
        [[nodiscard]] Length& getTop() noexcept;

        /**
         * \brief Get top margin.
         * \return Top margin.
         */
        [[nodiscard]] const Length& getTop() const noexcept;

        /**
         * \brief Get right margin.
         * \return Right margin.
         */
        [[nodiscard]] Length& getRight() noexcept;

        /**
         * \brief Get right margin.
         * \return Right margin.
         */
        [[nodiscard]] const Length& getRight() const noexcept;

        /**
         * \brief Get bottom margin.
         * \return Bottom margin.
         */
        [[nodiscard]] Length& getBottom() noexcept;

        /**
         * \brief Get bottom margin.
         * \return Bottom margin.
         */
        [[nodiscard]] const Length& getBottom() const noexcept;

        ////////////////////////////////////////////////////////////////
        // Setters.
        ////////////////////////////////////////////////////////////////

        /**
         * \brief Set all margins.
         * \param l Left.
         * \param t Top.
         * \param r Right.
         * \param b Bottom.
         */
        void set(int32_t l, int32_t t, int32_t r, int32_t b) noexcept;

    private:
        ////////////////////////////////////////////////////////////////
        // Member variables.
        ////////////////////////////////////////////////////////////////

        Length left;

        Length top;

        Length right;

        Length bottom;
    };
}  // namespace floah
