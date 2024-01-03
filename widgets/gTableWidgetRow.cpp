/*!
 * =============================================================================
 *
 *   @file: gTableWidgetRow.cpp
 *
 *   @date: December, 2023
 *
 * @author: Gino Francesco Bogo
 *
 * =============================================================================
 */

#include "gTableWidgetRow.hpp"

#include "gTableWidgetRows.hpp"

gTableWidgetRow::gTableWidgetRow(gTableWidgetRows* parent, func_setupRow setupRow) {
    m_parent = parent;

    if (setupRow != nullptr) {
        setupRow(this);
    }
}

gTableWidgetRow::~gTableWidgetRow() {
    clearAll();
}

void gTableWidgetRow::clearAll() {
    // NOTE: "gTableWidgetRow" items are removed by "gTableWidget" direclty.
    clear();
}

QStringList gTableWidgetRow::cellData() {
    QStringList cellData;

    auto N = this->count();
    for (decltype(N) i{0}; i < N; ++i) {
        auto* _item = at(i);

        switch (_item->type()) {
            case gTableWidgetBase::ITEM: {
                cellData.append(_item->toItem()->text());
            } break;

            case gTableWidgetBase::CELL: {
                cellData.append(_item->toCell()->title());
            } break;

            case gTableWidgetBase::DATE: {
                cellData.append(_item->toDate()->date());
            } break;

            case gTableWidgetBase::CBOX: {
                cellData.append(_item->toCBox()->index());
            } break;

            case gTableWidgetBase::ICON: {
                cellData.append(_item->toIcon()->index());
            } break;

            default: {
                // ERROR: wrong condition detected.
            } break;
        }
    }

    return cellData;
}

void gTableWidgetRow::setCellData(const QStringList& cellData) {

    auto N = this->count();
    for (decltype(N) i{0}; i < N; ++i) {
        auto* _item = at(i);

        switch (_item->type()) {
            case gTableWidgetBase::ITEM: {
                _item->toItem()->setText(cellData.at(i));
            } break;

            case gTableWidgetBase::CELL: {
                _item->toCell()->setTitle(cellData.at(i));
            } break;

            case gTableWidgetBase::DATE: {
                _item->toDate()->setDate(cellData.at(i));
            } break;

            case gTableWidgetBase::CBOX: {
                _item->toCBox()->setIndex(cellData.at(i));
            } break;

            case gTableWidgetBase::ICON: {
                _item->toIcon()->setIndex(cellData.at(i));
            } break;

            default: {
                // ERROR: wrong condition detected.
            } break;
        }
    }
}
