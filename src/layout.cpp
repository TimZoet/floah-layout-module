#include "floah/layout.h"

////////////////////////////////////////////////////////////////
// Current target includes.
////////////////////////////////////////////////////////////////

#include "floah/utils/floah_error.h"

namespace floah
{
    ////////////////////////////////////////////////////////////////
    // Constructors.
    ////////////////////////////////////////////////////////////////

    Layout::Layout() = default;

    Layout::~Layout() noexcept = default;

    ////////////////////////////////////////////////////////////////
    // Getters.
    ////////////////////////////////////////////////////////////////

    Size& Layout::getSize() noexcept { return size; }

    const Size& Layout::getSize() const noexcept { return size; }

    Element* Layout::getRootElement() const noexcept { return root.get(); }

    ////////////////////////////////////////////////////////////////
    // ...
    ////////////////////////////////////////////////////////////////

    std::vector<Block> Layout::generate() const
    {
        if (!root) return {};

        if (size.getWidth().isRelative() || size.getHeight().isRelative())
            throw FloahError("Cannot generate. Layout must have an absolute size.");

        // Reserve enough space for all blocks to keep stable iterators.
        size_t count = 0;
        root->countBlocks(count);
        std::vector<Block> blocks;
        blocks.reserve(count);

        // Calculate absolute bounds of root.
        const auto left   = root->getOuterMargin().getLeft().get(size.getWidth().get());
        const auto top    = root->getOuterMargin().getTop().get(size.getHeight().get());
        const auto width  = root->getSize().getWidth().get(size.getWidth().get());
        const auto height = root->getSize().getWidth().get(size.getHeight().get());
        const BBox bb{.x0 = left, .y0 = top, .x1 = left + width, .y1 = top + height};

        // Create root block and recurse on children.
        auto&      block = blocks.emplace_back(root->getId(), bb);
        root->generate(blocks, block);

        return blocks;
    }

}  // namespace floah
