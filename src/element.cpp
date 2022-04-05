#include "floah-layout/element.h"

////////////////////////////////////////////////////////////////
// External includes.
////////////////////////////////////////////////////////////////

#include "uuid_system_generator.h"

namespace floah
{
    ////////////////////////////////////////////////////////////////
    // Constructors.
    ////////////////////////////////////////////////////////////////

    Element::Element() : id(uuids::uuid_system_generator{}()) {}

    Element::Element(const Element& other) :
        id(uuids::uuid_system_generator{}()),
        size(other.size),
        innerMargin(other.innerMargin),
        outerMargin(other.outerMargin)
    {
    }

    Element::~Element() noexcept = default;

    Element& Element::operator=(const Element& other)
    {
        size        = other.size;
        innerMargin = other.innerMargin;
        outerMargin = other.outerMargin;
        return *this;
    }

    ElementPtr Element::clone(Layout* l, Element* p) const
    {
        auto elem = std::make_unique<Element>(*this);
        elem->cloneImpl(l, p);
        return elem;
    }

    void Element::cloneImpl(Layout* l, Element* p)
    {
        layout = l;
        parent = p;
    }

    ////////////////////////////////////////////////////////////////
    // Getters.
    ////////////////////////////////////////////////////////////////

    const uuids::uuid& Element::getId() const noexcept { return id; }

    Layout* Element::getLayout() const noexcept { return layout; }

    Element* Element::getParent() const noexcept { return parent; }

    Size& Element::getSize() noexcept { return size; }

    const Size& Element::getSize() const noexcept { return size; }

    Margin& Element::getInnerMargin() noexcept { return innerMargin; }

    const Margin& Element::getInnerMargin() const noexcept { return innerMargin; }

    Margin& Element::getOuterMargin() noexcept { return outerMargin; }

    const Margin& Element::getOuterMargin() const noexcept { return outerMargin; }

    ////////////////////////////////////////////////////////////////
    // Setters.
    ////////////////////////////////////////////////////////////////

    void Element::setLayout(Layout* l) noexcept { layout = l; }

    void Element::setLayout(Layout* l, Element& elem) noexcept { elem.setLayout(l); }

    void Element::makeChild(Element& elem)
    {
        if (elem.layout != layout) elem.setLayout(layout);
        elem.parent = this;
    }

    void Element::removeChild(Element& elem)
    {
        if (elem.layout != nullptr) elem.setLayout(nullptr);
        elem.parent = nullptr;
    }

    ////////////////////////////////////////////////////////////////
    // Generate.
    ////////////////////////////////////////////////////////////////

    void Element::countBlocks(size_t& count) const noexcept { count++; }

    void Element::generate(std::vector<Block>&, Block&) const {}
}  // namespace floah
