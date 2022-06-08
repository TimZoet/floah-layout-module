#include "floah-layout/layout_element.h"

////////////////////////////////////////////////////////////////
// External includes.
////////////////////////////////////////////////////////////////

#include "uuid_system_generator.h"

namespace floah
{
    ////////////////////////////////////////////////////////////////
    // Constructors.
    ////////////////////////////////////////////////////////////////

    LayoutElement::LayoutElement() : id(uuids::uuid_system_generator{}()) {}

    LayoutElement::LayoutElement(const LayoutElement& other) :
        id(uuids::uuid_system_generator{}()),
        size(other.size),
        innerMargin(other.innerMargin),
        outerMargin(other.outerMargin)
    {
    }

    LayoutElement::~LayoutElement() noexcept = default;

    LayoutElement& LayoutElement::operator=(const LayoutElement& other)
    {
        size        = other.size;
        innerMargin = other.innerMargin;
        outerMargin = other.outerMargin;
        return *this;
    }

    LayoutElementPtr LayoutElement::clone(Layout* l, LayoutElement* p) const
    {
        auto elem = std::make_unique<LayoutElement>(*this);
        elem->cloneImpl(l, p);
        return elem;
    }

    void LayoutElement::cloneImpl(Layout* l, LayoutElement* p)
    {
        layout = l;
        parent = p;
    }

    ////////////////////////////////////////////////////////////////
    // Getters.
    ////////////////////////////////////////////////////////////////

    const uuids::uuid& LayoutElement::getId() const noexcept { return id; }

    Layout* LayoutElement::getLayout() const noexcept { return layout; }

    LayoutElement* LayoutElement::getParent() const noexcept { return parent; }

    Size& LayoutElement::getSize() noexcept { return size; }

    const Size& LayoutElement::getSize() const noexcept { return size; }

    Margin& LayoutElement::getInnerMargin() noexcept { return innerMargin; }

    const Margin& LayoutElement::getInnerMargin() const noexcept { return innerMargin; }

    Margin& LayoutElement::getOuterMargin() noexcept { return outerMargin; }

    const Margin& LayoutElement::getOuterMargin() const noexcept { return outerMargin; }

    ////////////////////////////////////////////////////////////////
    // Setters.
    ////////////////////////////////////////////////////////////////

    void LayoutElement::setLayout(Layout* l) noexcept { layout = l; }

    void LayoutElement::setLayout(Layout* l, LayoutElement& elem) noexcept { elem.setLayout(l); }

    void LayoutElement::makeChild(LayoutElement& elem)
    {
        if (elem.layout != layout) elem.setLayout(layout);
        elem.parent = this;
    }

    void LayoutElement::removeChild(LayoutElement& elem)
    {
        if (elem.layout != nullptr) elem.setLayout(nullptr);
        elem.parent = nullptr;
    }

    ////////////////////////////////////////////////////////////////
    // Generate.
    ////////////////////////////////////////////////////////////////

    void LayoutElement::countBlocks(size_t& count) const noexcept { count++; }

    void LayoutElement::generate(std::vector<Block>&, Block&) const {}
}  // namespace floah
