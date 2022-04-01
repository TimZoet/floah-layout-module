#pragma once

////////////////////////////////////////////////////////////////
// Standard includes.
////////////////////////////////////////////////////////////////

#include <cassert>
#include <vector>

////////////////////////////////////////////////////////////////
// Current target includes.
////////////////////////////////////////////////////////////////

#include "floah/element.h"
#include "floah/properties/alignment.h"

namespace floah
{
    class HorizontalFlow final : public Element
    {
    public:
        ////////////////////////////////////////////////////////////////
        // Constructors.
        ////////////////////////////////////////////////////////////////

        HorizontalFlow();

        HorizontalFlow(const HorizontalFlow&);

        HorizontalFlow(HorizontalFlow&&) noexcept = delete;

        ~HorizontalFlow() noexcept override;

        HorizontalFlow& operator=(const HorizontalFlow&);

        HorizontalFlow& operator=(HorizontalFlow&&) noexcept = delete;

        [[nodiscard]] ElementPtr clone(Layout* l, Element* p) const override;

        ////////////////////////////////////////////////////////////////
        // Getters.
        ////////////////////////////////////////////////////////////////

        /**
         * \brief Get the horizontal alignment for child elements.
         * \return Horizontal alignment.
         */
        [[nodiscard]] HorizontalAlignment getHorizontalAlignment() const noexcept;

        /**
         * \brief Get the vertical alignment for child elements.
         * \return Vertical alignment.
         */
        [[nodiscard]] VerticalAlignment getVerticalAlignment() const noexcept;

        /**
         * \brief Get the number of child elements.
         * \return Child count.
         */
        [[nodiscard]] size_t getChildCount() const noexcept;

        ////////////////////////////////////////////////////////////////
        // Setters.
        ////////////////////////////////////////////////////////////////

        void setLayout(Layout* l) noexcept override;

        /**
         * \brief Set the horizontal alignment for child elements.
         * \param alignment Horizontal alignment.
         */
        void setHorizontalAlignment(HorizontalAlignment alignment) noexcept;

        /**
         * \brief Set the vertical alignment for child elements.
         * \param alignment Vertical alignment.
         */
        void setVerticalAlignment(VerticalAlignment alignment) noexcept;

        ////////////////////////////////////////////////////////////////
        // Elements.
        ////////////////////////////////////////////////////////////////

        /**
         * \brief Get element at index.
         * \param index Index.
         * \return Element.
         */
        [[nodiscard]] Element& get(size_t index) const;

        /**
         * \brief Add an element to the end.
         * \tparam T Element type.
         * \param elem Element.
         * \return Element.
         */
        template<std::derived_from<Element> T>
        T& append(std::unique_ptr<T> elem)
        {
            assert(elem);
            T& elemRef = *elem;
            appendImpl(std::move(elem));
            return elemRef;
        }

        /**
         * \brief Add an element to the front. All elements are shifted right.
         * \tparam T Element type.
         * \param elem Element.
         * \return Element.
         */
        template<std::derived_from<Element> T>
        T& prepend(std::unique_ptr<T> elem)
        {
            assert(elem);
            T& elemRef = *elem;
            prependImpl(std::move(elem));
            return elemRef;
        }

        /**
         * \brief Insert an element at index. All elements at position >= index are shifted right.
         * \tparam T Element type.
         * \param elem Element.
         * \param index Index.
         * \return Element.
         */
        template<std::derived_from<Element> T>
        T& insert(std::unique_ptr<T> elem, const size_t index)
        {
            assert(elem);
            T& elemRef = *elem;
            insertImpl(std::move(elem), index);
            return elemRef;
        }

        /**
         * \brief Remove element at index. All elements at position > index are shifted left.
         * \param index Index.
         */
        void remove(size_t index);

        /**
         * \brief Remove element at index and return it. All elements at position > index are shifted left.
         * \param index Index.
         * \return Removed element.
         */
        [[nodiscard]] ElementPtr extract(size_t index);

    private:
        void appendImpl(ElementPtr elem);

        void prependImpl(ElementPtr elem);

        void insertImpl(ElementPtr elem, size_t index);

        /**
         * \brief Horizontal alignment.
         */
        HorizontalAlignment horAlign = HorizontalAlignment::Left;

        /**
         * \brief Vertical alignment.
         */
        VerticalAlignment verAlign = VerticalAlignment::Top;

        /**
         * \brief List of child elements.
         */
        std::vector<ElementPtr> children;
    };
}  // namespace floah
