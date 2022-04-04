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

    void HorizontalFlow::setHorizontalAlignment(const HorizontalAlignment alignment)
    {
        if (alignment == HorizontalAlignment::Center)
            throw FloahError("Cannot set alignment. Center not supported for horizontal alignment.");
        horAlign = alignment;
    }

    void HorizontalFlow::setVerticalAlignment(const VerticalAlignment alignment) noexcept { verAlign = alignment; }

    ////////////////////////////////////////////////////////////////
    // Generate.
    ////////////////////////////////////////////////////////////////

    void HorizontalFlow::countBlocks(size_t& count) const noexcept
    {
        count++;
        for (const auto& c : children) c->countBlocks(count);
    }

    void HorizontalFlow::generate(std::vector<Block>& blocks, Block& block) const
    {
        if (children.empty()) return;

        block.firstChild = blocks.size();
        block.childCount = children.size();

        const auto& bounds = block.bounds;

        // Total width is bounds.width minus left and right margin.
        const auto boundsWidth = bounds.width();
        const auto leftMargin  = innerMargin.getLeft().get(boundsWidth);
        const auto rightMargin = innerMargin.getRight().get(boundsWidth);
        const auto width       = boundsWidth - leftMargin - rightMargin;

        // Total height is bounds.height minus top and bottom margin.
        const auto boundsHeight = bounds.height();
        const auto topMargin    = innerMargin.getTop().get(boundsHeight);
        const auto bottomMargin = innerMargin.getBottom().get(boundsHeight);
        const auto height       = boundsHeight - topMargin - bottomMargin;

        // Start at left or right of bounds.
        int32_t x = 0;
        switch (horAlign)
        {
        case HorizontalAlignment::Left: x = bounds.x0 + leftMargin; break;
        case HorizontalAlignment::Center:
            throw FloahError("Cannot generate. Center not supported for horizontal alignment.");
        case HorizontalAlignment::Right: x = bounds.x1 - rightMargin;
        }

        // Start at left or right of bounds, or center around middle.
        int32_t y = 0;
        switch (verAlign)
        {
        case VerticalAlignment::Top: y = bounds.y0 + topMargin; break;
        case VerticalAlignment::Middle: y = (bounds.y0 + topMargin + bounds.y1 - bottomMargin) / 2; break;
        case VerticalAlignment::Bottom: y = bounds.y1 - bottomMargin;
        }

        BBox childBounds;
        for (const auto& c : children)
        {
            // Calculate absolute size of child.
            const auto cWidth  = c->getSize().getWidth().get(width);
            const auto cHeight = c->getSize().getHeight().get(height);

            BBox b;

            switch (horAlign)
            {
            // Append to right of elements and move x further right.
            case HorizontalAlignment::Left:
                b.x0 = x + c->getOuterMargin().getLeft().get(width);
                b.x1 = b.x0 + cWidth;
                x    = b.x1 + c->getOuterMargin().getRight().get(width);
                break;
            case HorizontalAlignment::Center: break;
            // Append to left of elements and move x further left.
            case HorizontalAlignment::Right:
                b.x1 = x - c->getOuterMargin().getRight().get(width);
                b.x0 = b.x1 - cWidth;
                x    = b.x0 - c->getOuterMargin().getLeft().get(width);
                break;
            }

            switch (verAlign)
            {
            // Offset from top of parent.
            case VerticalAlignment::Top:
                b.y0 = y + c->getOuterMargin().getTop().get(height);
                b.y1 = b.y0 + cHeight;
                break;
            // Center around middle of parent.
            case VerticalAlignment::Middle:
                b.y0 = y - (cHeight + 1) / 2;  // Add 1 so odd heights are respected.
                b.y1 = y + cHeight / 2;
                break;
            // Offset from bottom of parent.
            case VerticalAlignment::Bottom:
                b.y1 = y - c->getOuterMargin().getBottom().get(height);
                b.y0 = b.y0 - cHeight;
                break;
            }

            // Accumulate bounds of children.
            childBounds += b;

            blocks.emplace_back(c->getId(), b);
        }

        block.childBounds = childBounds;

        for (size_t i = 0; i < children.size(); i++) { children[i]->generate(blocks, blocks[block.firstChild + i]); }
    }

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
