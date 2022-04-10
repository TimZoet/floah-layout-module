#include "floah-layout/elements/grid.h"

////////////////////////////////////////////////////////////////
// Current target includes.
////////////////////////////////////////////////////////////////

#include "floah-layout/utils/floah_error.h"

namespace floah
{
    ////////////////////////////////////////////////////////////////
    // Constructors.
    ////////////////////////////////////////////////////////////////

    Grid::Grid() = default;

    Grid::Grid(const Grid& other) : Element(other), horAlign(other.horAlign), verAlign(other.verAlign) {}

    Grid::~Grid() noexcept = default;

    Grid& Grid::operator=(const Grid& other)
    {
        Element::operator=(other);
        horAlign         = other.horAlign;
        verAlign         = other.verAlign;
        return *this;
    }

    ElementPtr Grid::clone(Layout* l, Element* p) const
    {
        auto elem = std::make_unique<Grid>(*this);
        elem->cloneImpl(l, p);

        elem->rowCount    = rowCount;
        elem->columnCount = columnCount;
        elem->children.reserve(children.size());
        for (const auto& c : children)
        {
            if (c) elem->children.push_back(c->clone(l, elem.get()));
        }

        return elem;
    }

    ////////////////////////////////////////////////////////////////
    // Getters.
    ////////////////////////////////////////////////////////////////

    HorizontalAlignment Grid::getHorizontalAlignment() const noexcept { return horAlign; }

    VerticalAlignment Grid::getVerticalAlignment() const noexcept { return verAlign; }

    size_t Grid::getRowCount() const noexcept { return rowCount; }

    size_t Grid::getColumnCount() const noexcept { return columnCount; }

    ////////////////////////////////////////////////////////////////
    // Setters.
    ////////////////////////////////////////////////////////////////

    void Grid::setLayout(Layout* l) noexcept
    {
        Element::setLayout(l);
        for (auto& c : children)
        {
            if (c) Element::setLayout(l, *c);
        }
    }

    void Grid::setHorizontalAlignment(const HorizontalAlignment alignment) noexcept { horAlign = alignment; }

    void Grid::setVerticalAlignment(const VerticalAlignment alignment) noexcept { verAlign = alignment; }

    ////////////////////////////////////////////////////////////////
    // Generate.
    ////////////////////////////////////////////////////////////////

    void Grid::countBlocks(size_t& count) const noexcept
    {
        count++;
        for (const auto& c : children)
        {
            if (c) c->countBlocks(count);
        }
    }

    void Grid::generate(std::vector<Block>& blocks, Block& block) const
    {
        if (children.empty()) return;

        // Count number of children.
        for (const auto& c : children)
        {
            if (c) block.childCount++;
        }
        if (block.childCount == 0) return;
        block.firstChild = blocks.size();

        const auto& bounds = block.bounds;

        // Total width is bounds.width minus left and right margin.
        const auto boundsWidth = bounds.width();
        const auto leftMargin  = innerMargin.getLeft().get(boundsWidth);
        const auto rightMargin = innerMargin.getRight().get(boundsWidth);
        const auto width       = boundsWidth - leftMargin - rightMargin;
        const auto cellWidth   = width / static_cast<int32_t>(columnCount);
        const auto x           = bounds.x0 + leftMargin;

        // Total height is bounds.height minus top and bottom margin.
        const auto boundsHeight = bounds.height();
        const auto topMargin    = innerMargin.getTop().get(boundsHeight);
        const auto bottomMargin = innerMargin.getBottom().get(boundsHeight);
        const auto height       = boundsHeight - topMargin - bottomMargin;
        const auto cellHeight   = height / static_cast<int32_t>(rowCount);
        const auto y            = bounds.y0 + topMargin;

        for (int32_t j = 0; j < static_cast<int32_t>(rowCount); j++)
        {
            for (int32_t i = 0; i < static_cast<int32_t>(columnCount); i++)
            {
                const auto& c = children[i + j * columnCount];
                if (!c) continue;

                // Calculate absolute size of child.
                const auto cWidth  = c->getSize().getWidth().get(width) / static_cast<int32_t>(columnCount);
                const auto cHeight = c->getSize().getHeight().get(height) / static_cast<int32_t>(rowCount);

                BBox b;

                const auto center = cellWidth * i + cellWidth / 2;
                switch (horAlign)
                {
                // Align to left of grid cell.
                case HorizontalAlignment::Left:
                    b.x0 = x + cellWidth * i + c->getOuterMargin().getLeft().get(cellWidth);
                    b.x1 = b.x0 + cWidth;
                    break;
                // Align around center of grid cell.
                case HorizontalAlignment::Center:
                    b.x0 = x + center - (cWidth + 1) / 2;  // Add 1 so odd widths are respected.
                    b.x1 = x + center + cWidth / 2;
                    break;
                // Align to right of grid cell.
                case HorizontalAlignment::Right:
                    b.x1 = x + cellWidth * (i + 1) - c->getOuterMargin().getRight().get(cellWidth);
                    b.x0 = b.x1 - cWidth;
                    break;
                }

                const auto middle = cellHeight * j + cellHeight / 2;
                switch (verAlign)
                {
                // Align to top of grid cell.
                case VerticalAlignment::Top:
                    b.y0 = y + cellHeight * j + c->getOuterMargin().getTop().get(cellHeight);
                    b.y1 = b.y0 + cHeight;
                    break;
                // Align around middle of grid cell.
                case VerticalAlignment::Middle:
                    b.y0 = y + middle - (cHeight + 1) / 2;  // Add 1 so odd heights are respected.
                    b.y1 = y + middle + cHeight / 2;
                    break;
                // Align to bottom of grid cell.
                case VerticalAlignment::Bottom:
                    b.y1 = y + cellHeight * (i + 1) - c->getOuterMargin().getBottom().get(cellHeight);
                    b.y0 = b.y1 - cWidth;
                    break;
                }

                blocks.emplace_back(c->getId(), b);
            }
        }

        size_t offset = 0;
        for (size_t j = 0; j < rowCount; j++)
        {
            for (size_t i = 0; i < columnCount; i++)
            {
                const auto& c = children[i + j * columnCount];
                if (!c) continue;

                c->generate(blocks, blocks[block.firstChild + offset++]);
            }
        }
    }

    ////////////////////////////////////////////////////////////////
    // Rows/Cols.
    ////////////////////////////////////////////////////////////////

    void Grid::appendRow() { insertRow(rowCount); }

    void Grid::appendColumn() { insertColumn(columnCount); }

    void Grid::prependRow() { insertRow(0); }

    void Grid::prependColumn() { insertColumn(0); }

    void Grid::insertRow(size_t y)
    {
        y = std::min(rowCount, y);
        rowCount++;

        // Resize, resulting in empty row at end.
        // 0 1 2 3
        // 4 5 6 7
        // - - - -
        children.resize(columnCount * rowCount);

        // 0 1 2 3
        // - - - -  <-- Shift all rows with index >= y.
        // 4 5 6 7
        const auto shift = (rowCount - 1 - y) * columnCount;
        for (size_t i = 0; i < shift; i++)
        {
            children[columnCount * rowCount - 1 - i] =
              std::move(children[columnCount * rowCount - 1 - i - columnCount]);
        }
    }

    void Grid::insertColumn(const size_t x)
    {
        columnCount++;
        children.resize(rowCount * columnCount);

        for (size_t j = 0; j < rowCount; j++)
        {
            for (size_t i = 0; i < columnCount; i++)
            {
                const auto   j2       = rowCount - j - 1;
                const auto   i2       = columnCount - i - 1;
                const size_t newIndex = i2 + j2 * columnCount;

                if (i2 < x)
                {
                    const size_t oldIndex = i2 + j2 * (columnCount - 1);
                    children[newIndex]    = std::move(children[oldIndex]);
                }
                else if (i2 == x)
                {
                    children[newIndex].reset();
                }
                else if (i2 > x)
                {
                    const size_t oldIndex = i2 - 1 + j2 * (columnCount - 1);
                    children[newIndex]    = std::move(children[oldIndex]);
                }
            }
        }
    }

    void Grid::removeRow(const size_t y)
    {
        if (y >= rowCount) throw FloahError("Cannot remove row. Index is out of range.");

        if (rowCount > 0)
        {
            children.erase(children.begin() + y * columnCount, children.begin() + (y + 1) * columnCount);
            rowCount--;
        }
    }

    void Grid::removeColumn(const size_t x)
    {
        if (x >= columnCount) throw FloahError("Cannot remove column. Index is out of range.");

        columnCount--;

        for (size_t j = 0; j < rowCount; j++)
        {
            for (size_t i = 0; i < columnCount; i++)
            {
                const auto newIndex = i + j * columnCount;

                if (i < x)
                {
                    const auto oldIndex = i + j * (columnCount + 1);
                    children[newIndex]  = std::move(children[oldIndex]);
                }
                else
                {
                    const auto oldIndex = i + 1 + j * (columnCount + 1);
                    children[newIndex]  = std::move(children[oldIndex]);
                }
            }
        }

        children.resize(rowCount * columnCount);
    }

    std::vector<ElementPtr> Grid::extractRow(const size_t y)
    {
        if (y >= rowCount) throw FloahError("Cannot extract row. Index is out of range.");

        std::vector<ElementPtr> elems;
        elems.reserve(columnCount);

        for (size_t x = 0; x < columnCount; x++) elems.push_back(std::move(*(children.begin() + y * columnCount + x)));
        children.erase(children.begin() + y * columnCount, children.begin() + (y + 1) * columnCount);

        rowCount--;

        for (auto& c : elems)
        {
            if (c) removeChild(*c);
        }

        return elems;
    }

    std::vector<ElementPtr> Grid::extractColumn(const size_t x)
    {
        if (x >= columnCount) throw FloahError("Cannot extract column. Index is out of range.");

        std::vector<ElementPtr> elems;
        elems.reserve(rowCount);

        columnCount--;

        // 0 1 2  0  1 2
        // 3 4 5 --> 4 5
        // 6 7 8     7 8

        // 0 1 2  1  0 2
        // 3 4 5 --> 3 5
        // 6 7 8     6 8

        // 0 1 2  2  0 1
        // 3 4 5 --> 3 4
        // 6 7 8     6 7

        for (size_t j = 0; j < rowCount; j++)
        {
            elems.push_back(std::move(children[x + j * (columnCount + 1)]));

            for (size_t i = 0; i < columnCount; i++)
            {
                const auto newIndex = i + j * columnCount;

                if (i < x)
                {
                    const auto oldIndex = i + j * (columnCount + 1);
                    children[newIndex]  = std::move(children[oldIndex]);
                }
                else
                {
                    const auto oldIndex = i + 1 + j * (columnCount + 1);
                    children[newIndex]  = std::move(children[oldIndex]);
                }
            }
        }

        children.resize(rowCount * columnCount);

        for (auto& c : elems)
        {
            if (c) removeChild(*c);
        }

        return elems;
    }

    void Grid::removeAllRowsAndColumns()
    {
        children.clear();
        rowCount    = 0;
        columnCount = 0;
    }

    ////////////////////////////////////////////////////////////////
    // Elements.
    ////////////////////////////////////////////////////////////////

    Element* Grid::get(const size_t x, const size_t y)
    {
        if (x >= columnCount || y >= rowCount) throw FloahError("Cannot get element. Index is out of range.");

        return children[x + y * columnCount].get();
    }

    void Grid::remove(const size_t x, const size_t y)
    {
        if (x >= columnCount || y >= rowCount) throw FloahError("Cannot remove element. Index is out of range.");

        children[x + y * columnCount].reset();
    }

    ElementPtr Grid::extract(const size_t x, const size_t y)
    {
        if (x >= columnCount || y >= rowCount) throw FloahError("Cannot extract element. Index is out of range.");

        auto elem = std::move(children[x + y * columnCount]);
        if (elem) removeChild(*elem);
        return elem;
    }

    void Grid::insertImpl(ElementPtr elem, const size_t x, const size_t y)
    {
        if (x >= columnCount || y >= rowCount) throw FloahError("Cannot insert element. Index is out of range.");

        makeChild(*elem);
        children[x + y * columnCount] = std::move(elem);
    }

}  // namespace floah
