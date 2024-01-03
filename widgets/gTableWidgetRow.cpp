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

QStringList gTableWidgetRow::values() {
    QStringList values;

    auto N = this->count();
    for (decltype(N) i{0}; i < N; ++i) {
        auto* _item = at(i);

        switch (_item->type()) {
            case gTableWidgetBase::ITEM: {
                values.append(_item->toItem()->text());
            } break;

            case gTableWidgetBase::CELL: {
                values.append(_item->toCell()->title());
            } break;

            case gTableWidgetBase::DATE: {
                values.append(_item->toDate()->date());
            } break;

            case gTableWidgetBase::CBOX: {
                values.append(_item->toCBox()->index());
            } break;

            default: {
                // ERROR: wrong condition detected.
            } break;
        }
    }

    return values;
}

void gTableWidgetRow::setValues(const QStringList& values) {

    auto N = this->count();
    for (decltype(N) i{0}; i < N; ++i) {
        auto* _item = at(i);

        switch (_item->type()) {
            case gTableWidgetBase::ITEM: {
                _item->toItem()->setText(values.at(i));
            } break;

            case gTableWidgetBase::CELL: {
                _item->toCell()->setTitle(values.at(i));
            } break;

            case gTableWidgetBase::DATE: {
                _item->toDate()->setDate(values.at(i));
            } break;

            case gTableWidgetBase::CBOX: {
                _item->toCBox()->setIndex(values.at(i));
            } break;

            default: {
                // ERROR: wrong condition detected.
            } break;
        }
    }
}
