#include "floah-layout/elements/vertical_flow.h"

////////////////////////////////////////////////////////////////
// Current target includes.
////////////////////////////////////////////////////////////////

#include "floah-common/floah_error.h"

namespace floah
{
    ////////////////////////////////////////////////////////////////
    // Constructors.
    ////////////////////////////////////////////////////////////////

    VerticalFlow::VerticalFlow() = default;

    VerticalFlow::VerticalFlow(const VerticalFlow& other) :
        LayoutElement(other), horAlign(other.horAlign), verAlign(other.verAlign)
    {
    }

    VerticalFlow::~VerticalFlow() noexcept = default;

    VerticalFlow& VerticalFlow::operator=(const VerticalFlow& other)
    {
        LayoutElement::operator=(other);
        horAlign               = other.horAlign;
        verAlign               = other.verAlign;
        return *this;
    }

    LayoutElementPtr VerticalFlow::clone(Layout* l, LayoutElement* p) const
    {
        auto elem = std::make_unique<VerticalFlow>(*this);
        elem->cloneImpl(l, p);

        elem->children.reserve(children.size());
        for (const auto& c : children) elem->children.push_back(c->clone(l, elem.get()));

        return elem;
    }

    ////////////////////////////////////////////////////////////////
    // Getters.
    ////////////////////////////////////////////////////////////////

    HorizontalAlignment VerticalFlow::getHorizontalAlignment() const noexcept { return horAlign; }

    VerticalAlignment VerticalFlow::getVerticalAlignment() const noexcept { return verAlign; }

    size_t VerticalFlow::getChildCount() const noexcept { return children.size(); }

    ////////////////////////////////////////////////////////////////
    // Setters.
    ////////////////////////////////////////////////////////////////

    void VerticalFlow::setLayout(Layout* l) noexcept
    {
        LayoutElement::setLayout(l);
        for (auto& c : children) LayoutElement::setLayout(l, *c);
    }

    void VerticalFlow::setHorizontalAlignment(const HorizontalAlignment alignment) noexcept { horAlign = alignment; }

    void VerticalFlow::setVerticalAlignment(const VerticalAlignment alignment)
    {
        if (alignment == VerticalAlignment::Middle)
            throw FloahError("Cannot set alignment. Middle not supported for vertical alignment.");
        verAlign = alignment;
    }

    ////////////////////////////////////////////////////////////////
    // Generate.
    ////////////////////////////////////////////////////////////////

    void VerticalFlow::countBlocks(size_t& count) const noexcept
    {
        count++;
        for (const auto& c : children) c->countBlocks(count);
    }

    void VerticalFlow::generate(std::vector<Block>& blocks, Block& block) const
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

        // Start at top or bottom of bounds.
        int32_t y = 0;
        switch (verAlign)
        {
        case VerticalAlignment::Top: y = bounds.y0 + topMargin; break;
        case VerticalAlignment::Middle:
            throw FloahError("Cannot generate. Middle not supported for vertical alignment.");
        case VerticalAlignment::Bottom: y = bounds.y1 - bottomMargin;
        }

        // Offset from left or right of bounds, or center around vertical axis.
        int32_t x = 0;
        switch (horAlign)
        {
        case HorizontalAlignment::Left: x = bounds.x0 + leftMargin; break;
        case HorizontalAlignment::Center: x = (bounds.x0 + leftMargin + bounds.x1 - rightMargin) / 2; break;
        case HorizontalAlignment::Right: x = bounds.x1 - rightMargin;
        }

        for (const auto& c : children)
        {
            // Calculate absolute size of child.
            const auto cWidth  = c->getSize().getWidth().get(width);
            const auto cHeight = c->getSize().getHeight().get(height);

            BBox b;

            switch (verAlign)
            {
            // Append to bottom of elements and move y further down.
            case VerticalAlignment::Top:
                b.y0 = y + c->getOuterMargin().getTop().get(height);
                b.y1 = b.y0 + cHeight;
                y    = b.y1 + c->getOuterMargin().getBottom().get(height);
                break;
            case VerticalAlignment::Middle: break;
            // Append to top of elements and move y further up.
            case VerticalAlignment::Bottom:
                b.y1 = y - c->getOuterMargin().getBottom().get(height);
                b.y0 = b.y1 - cHeight;
                y    = b.y0 - c->getOuterMargin().getTop().get(height);
                break;
            }

            switch (horAlign)
            {
            // Offset from left of parent.
            case HorizontalAlignment::Left:
                b.x0 = x + c->getOuterMargin().getLeft().get(width);
                b.x1 = b.x0 + cWidth;
                break;
            // Center around middle of parent.
            case HorizontalAlignment::Center:
                b.x0 = x - (cWidth + 1) / 2;  // Add 1 so odd widths are respected.
                b.x1 = x + cWidth / 2;
                break;
            // Offset from right of parent.
            case HorizontalAlignment::Right:
                b.x1 = x - c->getOuterMargin().getRight().get(width);
                b.x0 = b.x0 - cWidth;
                break;
            }

            blocks.emplace_back(c->getId(), b);
        }

        for (size_t i = 0; i < children.size(); i++) { children[i]->generate(blocks, blocks[block.firstChild + i]); }
    }

    ////////////////////////////////////////////////////////////////
    // Elements.
    ////////////////////////////////////////////////////////////////

    LayoutElement& VerticalFlow::get(const size_t index) const
    {
        if (index >= children.size()) throw FloahError("Cannot get element. Index is out of range.");

        return *children[index];
    }

    void VerticalFlow::remove(const size_t index)
    {
        if (index >= children.size()) throw FloahError("Cannot remove element. Index is out of range.");

        children.erase(children.begin() + index);
    }

    LayoutElementPtr VerticalFlow::extract(const size_t index)
    {
        if (index >= children.size()) throw FloahError("Cannot extract element. Index is out of range.");

        auto elem = std::move(children[index]);
        children.erase(children.begin() + index);
        removeChild(*elem);
        return elem;
    }

    void VerticalFlow::appendImpl(LayoutElementPtr elem)
    {
        makeChild(*elem);
        children.push_back(std::move(elem));
    }

    void VerticalFlow::prependImpl(LayoutElementPtr elem) { insertImpl(std::move(elem), 0); }

    void VerticalFlow::insertImpl(LayoutElementPtr elem, const size_t index)
    {
        makeChild(*elem);
        children.insert(children.begin() + std::min(children.size(), index), std::move(elem));
    }
}  // namespace floah
