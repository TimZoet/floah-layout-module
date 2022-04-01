#pragma once

////////////////////////////////////////////////////////////////
// Current target includes.
////////////////////////////////////////////////////////////////

#include "floah/properties/length.h"

namespace floah
{
    class Size
    {
    public:
        ////////////////////////////////////////////////////////////////
        // Constructors.
        ////////////////////////////////////////////////////////////////

        Size();

        Size(Length w, Length h);

        Size(const Size&);

        Size(Size&&) noexcept;

        ~Size() noexcept;

        Size& operator=(const Size&);

        Size& operator=(Size&&) noexcept;

        ////////////////////////////////////////////////////////////////
        // Getters.
        ////////////////////////////////////////////////////////////////

        /**
         * \brief Get width.
         * \return Width.
         */
        [[nodiscard]] Length& getWidth() noexcept;

        /**
         * \brief Get width.
         * \return Width.
         */
        [[nodiscard]] const Length& getWidth() const noexcept;

        /**
         * \brief Get height.
         * \return Height.
         */
        [[nodiscard]] Length& getHeight() noexcept;

        /**
         * \brief Get height.
         * \return Height.
         */
        [[nodiscard]] const Length& getHeight() const noexcept;
        
        ////////////////////////////////////////////////////////////////
        // Setters.
        ////////////////////////////////////////////////////////////////

        void setWidth(Length v);

        void setHeight(Length v);

    private:
        ////////////////////////////////////////////////////////////////
        // Member variables.
        ////////////////////////////////////////////////////////////////
        
        /**
         * \brief Width.
         */
        Length width;

        /**
         * \brief Height.
         */
        Length height;
    };
}  // namespace floah