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
    clear();
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
        m_clipboard = at(row)->cellData();
    }
}

void gTableWidgetRows::pasteRow(int row) {
    if (m_clipboard.isEmpty()) {
        return;
    }

    auto* item = new gTableWidgetRow(this, f_setupRow);
    item->setCellData(m_clipboard);
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

QList<QStringList> gTableWidgetRows::cellsData() {
    QList<QStringList> list;

    auto N = count();
    for (decltype(N) i{0}; i < N; ++i) {
        list.append(at(i)->cellData());
    }

    return list;
}

void gTableWidgetRows::setCellsData(const QList<QStringList>& list) {
    auto N = count();
    for (decltype(N) i{0}; i < N; ++i) {
        at(i)->setCellData(list.at(i));
    }
}

QList<gTableWidgetRow*> gTableWidgetRows::filterRows(int col, const QString& data) const {
    QList<gTableWidgetRow*> list;

    auto N = count();
    for (decltype(N) i{0}; i < N; ++i) {
        auto* row_ptr  = at(i);
        auto* item_ptr = row_ptr->at(col);

        switch (item_ptr->type()) {
            case gTableWidgetBase::ITEM: {
                if (data == item_ptr->toItem()->text())
                    list.append(row_ptr);
            } break;

            case gTableWidgetBase::CELL: {
                if (data == item_ptr->toCell()->title())
                    list.append(row_ptr);
            } break;

            case gTableWidgetBase::CBOX: {
                if (data == item_ptr->toCBox()->index())
                    list.append(row_ptr);
            } break;

            case gTableWidgetBase::DATE: {
                if (data == item_ptr->toDate()->date())
                    list.append(row_ptr);
            } break;

            case gTableWidgetBase::ICON: {
                if (data == item_ptr->toIcon()->index())
                    list.append(row_ptr);
            } break;

            default: {
                // ERROR: wrong condition detected.
            } break;
        }
    }

    return list;
}

void gTableWidgetRows::connectRowToTable(int row) {
    auto* row_ptr = at(row);

    auto N = row_ptr->count();
    for (decltype(N) col{0}; col < N; ++col) {
        auto item_ptr = row_ptr->at(col);

        switch (item_ptr->type()) {
            case gTableWidgetBase::ITEM: {
                m_parent->setItem(row, col, item_ptr->toItem());
            } break;

            case gTableWidgetBase::CELL: {
                m_parent->setCellWidget(row, col, item_ptr->toCell());
            } break;

            case gTableWidgetBase::CBOX: {
                m_parent->setCellWidget(row, col, item_ptr->toCBox());
            } break;

            case gTableWidgetBase::DATE: {
                m_parent->setCellWidget(row, col, item_ptr->toDate());
            } break;

            case gTableWidgetBase::ICON: {
                m_parent->setCellWidget(row, col, item_ptr->toIcon());
            } break;

            default: {
                // ERROR: wrong condition detected.
            } break;
        }
    }
}
