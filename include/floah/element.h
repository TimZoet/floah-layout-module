#pragma once

////////////////////////////////////////////////////////////////
// Standard includes.
////////////////////////////////////////////////////////////////

#include <memory>

////////////////////////////////////////////////////////////////
// Current target includes.
////////////////////////////////////////////////////////////////

#include "floah/properties/margin.h"
#include "floah/properties/size.h"

namespace floah
{
    class Layout;
    class Element;

    using ElementPtr = std::unique_ptr<Element>;

    class Element
    {
        friend class Layout;

    public:
        ////////////////////////////////////////////////////////////////
        // Constructors.
        ////////////////////////////////////////////////////////////////

        Element();

        Element(const Element&);

        Element(Element&&) noexcept = delete;

        virtual ~Element() noexcept;

        Element& operator=(const Element&);

        Element& operator=(Element&&) noexcept = delete;

        /**
         * \brief Clone this element to a new layout and/or parent element.
         * \param l New layout to place element in.
         * \param p Parent element.
         * \return Cloned element.
         */
        [[nodiscard]] virtual ElementPtr clone(Layout* l, Element* p) const;

    protected:
        virtual void cloneImpl(Layout* l, Element* p);

    public:
        ////////////////////////////////////////////////////////////////
        // Getters.
        ////////////////////////////////////////////////////////////////

        [[nodiscard]] Layout* getLayout() const noexcept;

        [[nodiscard]] Element* getParent() const noexcept;

        [[nodiscard]] Size& getSize() noexcept;

        [[nodiscard]] const Size& getSize() const noexcept;

        [[nodiscard]] Margin& getInnerMargin() noexcept;

        [[nodiscard]] const Margin& getInnerMargin() const noexcept;

        [[nodiscard]] Margin& getOuterMargin() noexcept;

        [[nodiscard]] const Margin& getOuterMargin() const noexcept;

        ////////////////////////////////////////////////////////////////
        // Setters.
        ////////////////////////////////////////////////////////////////

    protected:
        /**
         * \brief Recursively set layout.
         * \param l Layout.
         */
        virtual void setLayout(Layout* l) noexcept;

        void setLayout(Layout* l, Element& elem) noexcept;

        /**
         * \brief Make other element a child of this element.
         * \param elem Other element.
         */
        void makeChild(Element& elem);

        /**
         * \brief Remove this element as parent of other element.
         * \param elem Other element.
         */
        void removeChild(Element& elem);

        ////////////////////////////////////////////////////////////////
        // Member variables.
        ////////////////////////////////////////////////////////////////

        Layout* layout = nullptr;

        Element* parent = nullptr;

        Size size;

        Margin innerMargin;

        Margin outerMargin;
    };
}  // namespace floah
