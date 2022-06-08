#pragma once

////////////////////////////////////////////////////////////////
// Standard includes.
////////////////////////////////////////////////////////////////

#include <cassert>
#include <vector>

////////////////////////////////////////////////////////////////
// Current target includes.
////////////////////////////////////////////////////////////////

#include "floah-layout/layout_element.h"
#include "floah-layout/properties/alignment.h"

namespace floah
{
    class Grid final : public LayoutElement
    {
    public:
        ////////////////////////////////////////////////////////////////
        // Constructors.
        ////////////////////////////////////////////////////////////////

        Grid();

        Grid(const Grid&);

        Grid(Grid&&) noexcept = delete;

        ~Grid() noexcept override;

        Grid& operator=(const Grid&);

        Grid& operator=(Grid&&) noexcept = delete;

        [[nodiscard]] LayoutElementPtr clone(Layout* l, LayoutElement* p) const override;

        ////////////////////////////////////////////////////////////////
        // Getters.
        ////////////////////////////////////////////////////////////////

        /**
         * \brief Get the horizontal alignment for child elements.
         * \return Horizontal alignment.
         */
        [[nodiscard]] HorizontalAlignment getHorizontalAlignment() const noexcept;

        /**
         * \brief Get the vertical alignment for child elements.
         * \return Vertical alignment.
         */
        [[nodiscard]] VerticalAlignment getVerticalAlignment() const noexcept;

        /**
         * \brief Get the number of rows.
         * \return Row count.
         */
        [[nodiscard]] size_t getRowCount() const noexcept;

        /**
         * \brief Get the number of columns.
         * \return Column count.
         */
        [[nodiscard]] size_t getColumnCount() const noexcept;

        ////////////////////////////////////////////////////////////////
        // Setters.
        ////////////////////////////////////////////////////////////////

        void setLayout(Layout* l) noexcept override;

        /**
         * \brief Set the horizontal alignment for child elements.
         * \param alignment Horizontal alignment.
         */
        void setHorizontalAlignment(HorizontalAlignment alignment) noexcept;

        /**
         * \brief Set the vertical alignment for child elements.
         * \param alignment Vertical alignment.
         */
        void setVerticalAlignment(VerticalAlignment alignment) noexcept;

        ////////////////////////////////////////////////////////////////
        // Generate.
        ////////////////////////////////////////////////////////////////

        void countBlocks(size_t& count) const noexcept override;

        void generate(std::vector<Block>& blocks, Block& block) const override;

        ////////////////////////////////////////////////////////////////
        // Rows/Cols.
        ////////////////////////////////////////////////////////////////

        /**
         * \brief Add an empty row to the end.
         */
        void appendRow();

        /**
         * \brief Add an empty column to the end.
         */
        void appendColumn();

        /**
         * \brief Add an empty row to the front. All elements are shifted down.
         */
        void prependRow();

        /**
         * \brief Add an empty column to the front. All elements are shifted right.
         */
        void prependColumn();

        /**
         * \brief Insert empty row at y. All elements with y-index >= y are shifted down.
         * \param y Row index.
         */
        void insertRow(size_t y);

        /**
         * \brief Insert empty column at x. All elements with x-index >= x are shifted right.
         * \param x Column index.
         */
        void insertColumn(size_t x);

        /**
         * \brief Remove row at y and all elements in it. All elements with y-index > y are shifted up.
         * \param y Row index.
         */
        void removeRow(size_t y);

        /**
         * \brief Remove column at x and all elements in it. All elements with x-index > x are shifted left.
         * \param x Column index.
         */
        void removeColumn(size_t x);

        /**
         * \brief Remove row at y and all elements in it, and return the list of elements. All elements with y-index > y are shifted up.
         * \param y Row index.
         * \return List of elements (can contain nullptrs when there was no element at each position).
         */
        std::vector<LayoutElementPtr> extractRow(size_t y);

        /**
         * \brief Remove column at x and all elements in it, and return the list of elements. All elements with x-index > x are shifted left.
         * \param x Column index.
         * \return List of elements (can contain nullptrs when there was no element at each position).
         */
        std::vector<LayoutElementPtr> extractColumn(size_t x);

        // TODO: Come up with better name, perhaps create various clear/reset methods in base class?
        void removeAllRowsAndColumns();

        ////////////////////////////////////////////////////////////////
        // Elements.
        ////////////////////////////////////////////////////////////////

        /**
         * \brief Get element at (x, y).
         * \param x Column index.
         * \param y Row index.
         * \return Element or nullptr if no element was inserted.
         */
        LayoutElement* get(size_t x, size_t y);

        /**
         * \brief Insert an element at (x, y). Replaces existing element, if any.
         * \tparam T Element type.
         * \param elem Element.
         * \param x Column index.
         * \param y Row index.
         * \return Element.
         */
        template<std::derived_from<LayoutElement> T>
        T& insert(std::unique_ptr<T> elem, const size_t x, const size_t y)
        {
            assert(elem);
            T& elemRef = *elem;
            insertImpl(std::move(elem), x, y);
            return elemRef;
        }

        /**
         * \brief Remove element at (x, y).
         * \param x Column index.
         * \param y Row index.
         */
        void remove(size_t x, size_t y);

        /**
         * \brief Remove element at (x, y) and return it.
         * \param x Column index.
         * \param y Row index.
         * \return Removed element (nullptr when there was no element at (x, y)).
         */
        [[nodiscard]] LayoutElementPtr extract(size_t x, size_t y);

    private:
        void insertImpl(LayoutElementPtr elem, size_t x, size_t y);

        /**
         * \brief Horizontal alignment.
         */
        HorizontalAlignment horAlign = HorizontalAlignment::Left;

        /**
         * \brief Vertical alignment.
         */
        VerticalAlignment verAlign = VerticalAlignment::Top;

        /**
         * \brief Number of rows.
         */
        size_t rowCount = 0;

        /**
         * \brief Number of columns.
         */
        size_t columnCount = 0;

        /**
         * \brief Row-major list of child elements.
         */
        std::vector<LayoutElementPtr> children;
    };
}  // namespace floah
