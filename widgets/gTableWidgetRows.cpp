/*!
 * =============================================================================
 *
 *   @file: gTableWidgetRows.cpp
 *
 *   @date: December, 2023
 *
 * @author: Gino Francesco Bogo
 *
 * =============================================================================
 */

#include "gTableWidgetRows.hpp"

#include "gTableWidget.hpp"
#include "gTableWidgetRow.hpp"

#include <algorithm> // max, min

gTableWidgetRows::gTableWidgetRows(gTableWidget* parent) {
    m_parent   = parent;
    f_setupRow = nullptr;
}

gTableWidgetRows::~gTableWidgetRows() {
    clearAll();
}

void gTableWidgetRows::clearAll() {
    auto N = count();

    while (N-- > 0) {
        delete takeAt(0);
        m_parent->removeRow(0);
    }
}

void gTableWidgetRows::insertRow(int row, gTableWidgetRow* item) {
    auto row_count = m_parent->rowCount();

    row = std::max(row, 0);
    row = std::min(row, row_count);

    insert(row, item);
    m_parent->insertRow(row);

    connectRowToTable(row);
}

void gTableWidgetRows::insertRow(int row) {
    auto item = new gTableWidgetRow(this, f_setupRow);
    insertRow(row, item);
}

void gTableWidgetRows::removeRow(int row) {
    auto row_count = m_parent->rowCount();

    row = std::max(row, 0);
    row = std::min(row, row_count);

    delete takeAt(row);
    m_parent->removeRow(row);
}

void gTableWidgetRows::cutRow(int row) {
    copyRow(row);
    removeRow(row);
}

void gTableWidgetRows::copyRow(int row) {
    auto row_count = m_parent->rowCount();

    if ((0 <= row) && (row < row_count)) {
        m_clipboard = at(row)->values();
    }
}

void gTableWidgetRows::pasteRow(int row) {
    if (m_clipboard.isEmpty()) {
        return;
    }

    auto* item = new gTableWidgetRow(this, f_setupRow);
    item->setValues(m_clipboard);
    insertRow(row, item);
}

void gTableWidgetRows::moveUpRow(int row) {
    auto temp = m_clipboard;
    cutRow(row);
    pasteRow(row - 1);
    m_clipboard = temp;
}

void gTableWidgetRows::moveDownRow(int row) {
    auto temp = m_clipboard;
    cutRow(row);
    pasteRow(row + 1);
    m_clipboard = temp;
}

void gTableWidgetRows::connectRowToTable(int row) {
    auto row_ptr = at(row);

    auto N = row_ptr->count();
    for (decltype(N) col{0}; col < N; ++col) {
        auto _item = row_ptr->at(col);

        switch (_item->type()) {
            case gTableWidgetBase::ITEM: {
                m_parent->setItem(row, col, _item->toItem());
            } break;

            case gTableWidgetBase::CELL: {
                m_parent->setCellWidget(row, col, _item->toCell());
            } break;

            case gTableWidgetBase::CBOX: {
                m_parent->setCellWidget(row, col, _item->toCBox());
            } break;

            case gTableWidgetBase::DATE: {
                m_parent->setCellWidget(row, col, _item->toDate());
            } break;

            default: {
                // ERROR: wrong condition detected.
            } break;
        }
    }
}
