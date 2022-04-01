#pragma once

////////////////////////////////////////////////////////////////
// Standard includes.
////////////////////////////////////////////////////////////////

#include <cstdint>

namespace floah
{
    class Length
    {
    public:
        ////////////////////////////////////////////////////////////////
        // Constructors.
        ////////////////////////////////////////////////////////////////

        /**
         * \brief Construct an absolute length.
         */
        Length();

        /**
         * \brief Construct an absolute length.
         * \param v Absolute length.
         */
        explicit Length(int32_t v);

        /**
         * \brief Construct a relative length.
         * \param v Relative length.
         */
        explicit Length(float v);

        Length(const Length&);

        Length(Length&&) noexcept;

        ~Length() noexcept;

        Length& operator=(const Length&);

        Length& operator=(Length&&) noexcept;

        ////////////////////////////////////////////////////////////////
        // Getters.
        ////////////////////////////////////////////////////////////////

        /**
         * \brief Get absolute length.
         * \return Absolute length.
         */
        [[nodiscard]] int32_t get() const noexcept;

        /**
         * \brief Get relative length.
         * \return Relative length.
         */
        [[nodiscard]] float getRelative() const noexcept;

        /**
         * \brief Returns whether this length is absolute.
         * \return True if absolute.
         */
        [[nodiscard]] bool isAbsolute() const noexcept;

        /**
         * \brief Returns whether this length is relative.
         * \return True if relative.
         */
        [[nodiscard]] bool isRelative() const noexcept;

        ////////////////////////////////////////////////////////////////
        // Setters.
        ////////////////////////////////////////////////////////////////
        
        /**
         * \brief Set absolute length (does not make length absolute automatically).
         * \param v Absolute length.
         */
        void set(int32_t v);

        /**
         * \brief Set relative length (does not make length relative automatically).
         * \param v Relative length.
         */
        void setRelative(float v);

        /**
         * \brief Use absolute length value.
         */
        void makeAbsolute();

        /**
         * \brief Use relative length value.
         */
        void makeRelative();

    private:
        ////////////////////////////////////////////////////////////////
        // Member variables.
        ////////////////////////////////////////////////////////////////
        
        /**
         * \brief Whether absLength or relLength is used.
         */
        bool relative = false;

        /**
         * \brief Absolute length.
         */
        int32_t absLength = 0;

        /**
         * \brief Relative length.
         */
        float relLength = 0;
    };
}  // namespace floah