#pragma once

////////////////////////////////////////////////////////////////
// Standard includes.
////////////////////////////////////////////////////////////////

#include <cassert>
#include <concepts>
#include <vector>

////////////////////////////////////////////////////////////////
// Current target includes.
////////////////////////////////////////////////////////////////

#include "floah-layout/block.h"
#include "floah-layout/layout_element.h"
#include "floah-common/size.h"

namespace floah
{
    class Layout
    {
    public:
        ////////////////////////////////////////////////////////////////
        // Constructors.
        ////////////////////////////////////////////////////////////////
        // TODO: Implement some kind of clone.
        Layout();

        Layout(const Layout&) = delete;

        Layout(Layout&&) noexcept = delete;

        ~Layout() noexcept;

        Layout& operator=(const Layout&) = delete;

        Layout& operator=(Layout&&) noexcept = delete;

        ////////////////////////////////////////////////////////////////
        // Getters.
        ////////////////////////////////////////////////////////////////

        /**
         * \brief Get the absolute size of the layout.
         * \return Absolute size.
         */
        [[nodiscard]] Size& getSize() noexcept;

        /**
         * \brief Get the absolute size of the layout.
         * \return Absolute size.
         */
        [[nodiscard]] const Size& getSize() const noexcept;

        /**
         * \brief Get the absolute offset of the layout.
         * \return Absolute offset.
         */
        [[nodiscard]] Size& getOffset() noexcept;

        /**
         * \brief Get the absolute offset of the layout.
         * \return Absolute offset.
         */
        [[nodiscard]] const Size& getOffset() const noexcept;

        /**
         * \brief Get the root layout element.
         * \return LayoutElement or nullptr.
         */
        [[nodiscard]] LayoutElement* getRootElement() const noexcept;

        ////////////////////////////////////////////////////////////////
        // Setters.
        ////////////////////////////////////////////////////////////////

        template<std::derived_from<LayoutElement> T>
        T& setRoot(std::unique_ptr<T> elem)
        {
            assert(elem);
            auto& elemRef = *elem;
            root          = std::move(elem);
            root->setLayout(this);
            return elemRef;
        }

        ////////////////////////////////////////////////////////////////
        // ...
        ////////////////////////////////////////////////////////////////

        [[nodiscard]] std::vector<Block> generate() const;

    private:
        ////////////////////////////////////////////////////////////////
        // Member variables.
        ////////////////////////////////////////////////////////////////

        Size size;

        Size offset;

        LayoutElementPtr root;
    };
}  // namespace floah