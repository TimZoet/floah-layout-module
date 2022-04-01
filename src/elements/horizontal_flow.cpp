#include "floah/elements/horizontal_flow.h"

////////////////////////////////////////////////////////////////
// Current target includes.
////////////////////////////////////////////////////////////////

#include "floah/utils/floah_error.h"

namespace floah
{
    ////////////////////////////////////////////////////////////////
    // Constructors.
    ////////////////////////////////////////////////////////////////

    HorizontalFlow::HorizontalFlow() = default;

    HorizontalFlow::HorizontalFlow(const HorizontalFlow& other) :
        Element(other), horAlign(other.horAlign), verAlign(other.verAlign)
    {
    }

    HorizontalFlow::~HorizontalFlow() noexcept = default;

    HorizontalFlow& HorizontalFlow::operator=(const HorizontalFlow& other)
    {
        Element::operator=(other);
        horAlign         = other.horAlign;
        verAlign         = other.verAlign;
        return *this;
    }

    ElementPtr HorizontalFlow::clone(Layout* l, Element* p) const
    {
        auto elem = std::make_unique<HorizontalFlow>(*this);
        elem->cloneImpl(l, p);

        elem->children.reserve(children.size());
        for (const auto& c : children) elem->children.push_back(c->clone(l, elem.get()));

        return elem;
    }

    ////////////////////////////////////////////////////////////////
    // Getters.
    ////////////////////////////////////////////////////////////////

    HorizontalAlignment HorizontalFlow::getHorizontalAlignment() const noexcept { return horAlign; }

    VerticalAlignment HorizontalFlow::getVerticalAlignment() const noexcept { return verAlign; }

    size_t HorizontalFlow::getChildCount() const noexcept { return children.size(); }

    ////////////////////////////////////////////////////////////////
    // Setters.
    ////////////////////////////////////////////////////////////////

    void HorizontalFlow::setLayout(Layout* l) noexcept
    {
        Element::setLayout(l);
        for (auto& c : children) Element::setLayout(l, *c);
    }

    void HorizontalFlow::setHorizontalAlignment(const HorizontalAlignment alignment) noexcept { horAlign = alignment; }

    void HorizontalFlow::setVerticalAlignment(const VerticalAlignment alignment) noexcept { verAlign = alignment; }

    ////////////////////////////////////////////////////////////////
    // Elements.
    ////////////////////////////////////////////////////////////////

    Element& HorizontalFlow::get(const size_t index) const
    {
        if (index >= children.size()) throw FloahError("Cannot get element. Index is out of range.");

        return *children[index];
    }

    void HorizontalFlow::remove(const size_t index)
    {
        if (index >= children.size()) throw FloahError("Cannot remove element. Index is out of range.");

        children.erase(children.begin() + index);
    }

    ElementPtr HorizontalFlow::extract(const size_t index)
    {
        if (index >= children.size()) throw FloahError("Cannot extract element. Index is out of range.");

        auto elem = std::move(children[index]);
        children.erase(children.begin() + index);
        removeChild(*elem);
        return elem;
    }

    void HorizontalFlow::appendImpl(ElementPtr elem)
    {
        makeChild(*elem);
        children.push_back(std::move(elem));
    }

    void HorizontalFlow::prependImpl(ElementPtr elem) { insertImpl(std::move(elem), 0); }

    void HorizontalFlow::insertImpl(ElementPtr elem, const size_t index)
    {
        makeChild(*elem);
        children.insert(children.begin() + std::min(children.size(), index), std::move(elem));
    }
}  // namespace floah
