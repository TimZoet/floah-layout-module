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
#include "floah-layout/properties/size.h"

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

        [[nodiscard]] Size& getSize() noexcept;

        [[nodiscard]] const Size& getSize() const noexcept;

         [[nodiscard]] Size& getOffset() noexcept;

        [[nodiscard]] const Size& getOffset() const noexcept;

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