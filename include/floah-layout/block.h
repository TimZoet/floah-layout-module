#pragma once

////////////////////////////////////////////////////////////////
// External includes.
////////////////////////////////////////////////////////////////

#include "uuid.h"

////////////////////////////////////////////////////////////////
// Current target includes.
////////////////////////////////////////////////////////////////

#include "floah-common/bbox.h"

namespace floah
{
    struct Block
    {
        /**
         * \brief Identifier of layout element from which this block was generated. Note that an element may generate multiple blocks.
         */
        uuids::uuid id;

        /**
         * \brief Bounds of layout element.
         */
        BBox bounds;

        /**
         * \brief Union of bounds of layout element and all its children. If children are outside of bounds, these childBounds can be larger than the bounds.
         */
        BBox childBounds;

        /**
         * \brief Index of first child.
         */
        size_t firstChild = 0;

        /**
         * \brief Number of children.
         */
        size_t childCount = 0;
    };
}  // namespace floah