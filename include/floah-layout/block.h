#pragma once

////////////////////////////////////////////////////////////////
// Standard includes.
////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////
// External includes.
////////////////////////////////////////////////////////////////

#include "uuid.h"

////////////////////////////////////////////////////////////////
// Current target includes.
////////////////////////////////////////////////////////////////

#include "floah-layout/utils/bbox.h"

namespace floah
{
    struct Block
    {
        /**
         * \brief Element identifier.
         */
        uuids::uuid id;

        /**
         * \brief Bounds of element.
         */
        BBox bounds;

        /**
         * \brief Union of bounds of element and all its children.
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